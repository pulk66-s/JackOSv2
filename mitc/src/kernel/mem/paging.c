/**
 * @file        paging.c
 * @brief       Pagination system file
 * 
 * @details
 * This file contains everything about the pagination system. As the MIT 6.828
 * does with JOS kernel, we will do a 2-level pagination system. The first level
 * is the page directory, which is a 4KB(1024 entries) array. Each entry is a
 * page table. The second level is the page table of size 4KB(4096 bytes).
*/

#include <include/mem.h>
#include <include/mmu.h>
#include <include/pmap.h>
#include <include/memlayout.h>
#include <include/clib/memory.h>
#include <include/x86.h>

extern pde_t *kern_page_dir;

// Physical pages linked list
static struct page_info *pages;

// Free physical pages linked list
static struct page_info *page_free_list;

/**
 * @brief       Return all the pages
 * @return      All the pages
*/
struct page_info *get_all_pages(void) {
    return pages;
}

/**
 * @brief               Initialize the pagination system
 * @param    nb_pages   Number of pages to allocate
 * @return              0 on success, -1 on error
*/
void pagination_init(size_t nb_pages) {
    size_t size = nb_pages * sizeof(struct page_info);
    struct nvram_info *info = nvram_get_info();

    pages = (struct page_info *)boot_alloc(size);
    memset(pages, 0, size);

    size_t i = 0;

    pages[0].ref = 1;
    for (i = 1; i < info->npages_basemem; i++) {
        pages[i].ref = 0;
        pages[i].link = page_free_list;
        page_free_list = &pages[i];
    }
    for (i = IOPHYSMEM / PAGE_SIZE; i < EXTPHYSMEM / PAGE_SIZE; i++) {
        pages[i].ref = 1;
    }
    for (i = EXTPHYSMEM / PAGE_SIZE; i < nb_pages; i++) {
        if (i < PHYS_ADDR(boot_alloc(0)) / PAGE_SIZE) {
            pages[i].ref = 1;
        } else {
            pages[i].ref = 0;
            pages[i].link = page_free_list;
            page_free_list = &pages[i];
        }
    }
}

/**
 * @brief       Return the physical address of the page
 * @param   pp  Page to get the physical address
 * @return      Physical address of the page
*/
physaddr_t page_to_phys_addr(struct page_info *pp) {
    return (pp - pages) << PAGE_SHIFT;
}

/**
 * @brief       Return the page info of the physical address
 * @param   pa  Physical address
 * @return      Page info of the physical address
*/
struct page_info *phys_addr_to_page(physaddr_t pa) {
    if (PAGE_NUMBER(pa) >= get_nvram_nbpages()) {
        panic("pa2page called with invalid pa");
    }
    return &pages[PAGE_NUMBER(pa)];
}

/**
 * @brief       Return kernel virtual address of a page info
 * @param   pp  Page info to get the kernel virtual address
 * @return      A pointer to the kernel virtual address of the page info
*/
void *page_to_kernel_vaddr(struct page_info *pp) {
    return KERNEL_ADDR(page_to_phys_addr(pp));
}

/**
 * @brief           Allocate a page with the flags
 * @param   flags   Flags of the page
 * @return          struct page_info that describe the page, NULL on error
*/
struct page_info *page_alloc(int flags) {
    if (!page_free_list) {
        return NULL;
    }

    struct page_info *page = page_free_list;

    page_free_list = page->link;
    page->link = NULL;
    if (flags & ALLOC_ZERO) {
        memset(page_to_kernel_vaddr(page), 0, PAGE_SIZE);
    }
    return page;
}

/**
 * @brief           Free the given page
 * @param   pp      Page to free
*/
void page_free(struct page_info *pp) {
    if (pp->ref != 0) {
        panic("freeing page with nonzero ref count");
    }
    if (pp->link) {
        panic("freeing page on free list");
    }
    pp->link = page_free_list;
    page_free_list = pp;
}

/**
 * @brief           Decrement the amount of ref of the page. If ref == 0, free the page
 * @param   pp      Page to decrement the ref
*/
void page_decref(struct page_info *pp) {
    if (--pp->ref == 0) {
        page_free(pp);
    }
}

/**
 * @brief           Return the corresponding page table entry of the virtual address
 * @param   pgdir   Page directory to get the page table entry
 * @param   va      Virtual address to get the page table entry
 * @param   create  If create == 1, create the page table entry if it doesn't exist
 * @return          The corresponding page table entry of the virtual address
*/
pte_t *pgdir_walk(pde_t *pgdir, const void *va, int create) {
    pde_t *directory = &pgdir[PAGE_DIR_INDEX(va)];
    uint32_t *table;

    if (!(*directory & PTE_P)) {
        if (!create) {
            return NULL;
        }
        
        struct page_info *pp = page_alloc(ALLOC_ZERO);

        if (!pp) {
            return NULL;
        }
        pp->ref++;
        *directory = page_to_phys_addr(pp) | PTE_P | PTE_W | PTE_U;
    }
    table = KERNEL_ADDR(PTE_ADDR(*directory));
    return (pte_t *)(table + PAGE_TABLE_INDEX(va));
}

/**
 * @brief           Map a virtual paged region to a physical region
 * @param   pgdir   Page directory to map the region
 * @param   va      Virtual starting address
 * @param   size    Size of the region
 * @param   pa      Physical starting address
 * @param   perm    Permissions of the region
*/
void page_map_region(pde_t *pgdir, uintptr_t va, size_t size, physaddr_t pa, int perm) {
	for (size_t i = 0; i < size / PAGE_SIZE; i++) {
        pte_t *pte;

        if ((pte = pgdir_walk(pgdir, (void *)va, 1)) == NULL) {
            panic("boot_map_region: allocation failure");
        }
        *pte = pa | perm | PTE_P;
        va += PAGE_SIZE;
        pa += PAGE_SIZE;
    }
}

struct page_info *page_lookup(pde_t *pgdir, void *va, pte_t **pte_store)
{
    pte_t *pte;

    if ((pte = pgdir_walk(pgdir, va, 0)) == NULL || (*pte & PTE_P) == 0) {
        return NULL;
    }
    if (pte_store) {
        *pte_store = pte;
    }
    return phys_addr_to_page(PTE_ADDR(*pte));
}

void tlb_invalidate(pde_t *pgdir, void *va)
{
	// Flush the entry only if we're modifying the current address space.
	// For now, there is only one address space, so always invalidate.
	invlpg(va);
}


void page_remove(pde_t *pgdir, void *va)
{
    struct page_info *pp;
    pte_t *pte;

    if ((pp = page_lookup(pgdir, va, &pte)) == NULL) {
        return;
    }
    page_decref(pp);
    *pte = 0;
    tlb_invalidate(pgdir, va);
}


int page_insert(pde_t *pgdir, struct page_info *pp, void *va, int perm)
{
    pte_t *pte;

    if ((pte = pgdir_walk(pgdir, va, 1)) == NULL) {
        return -1;
    }
    pp->ref++;
    if (*pte & PTE_P) {
        page_remove(pgdir, va);
    }
    *pte = page_to_phys_addr(pp) | perm | PTE_P;
    return 0;
}





#include <include/mem.h>
#include <include/clib/memory.h>
#include <include/assert.h>

physaddr_t check_va2pa(pde_t *pgdir, uintptr_t va)
{
	pte_t *p;

	pgdir = &pgdir[PAGE_DIR_INDEX(va)];
	if (!(*pgdir & PTE_P))
		return ~0;
	p = (pte_t*) KERNEL_ADDR(PTE_ADDR(*pgdir));
	if (!(p[PAGE_TABLE_INDEX(va)] & PTE_P))
		return ~0;
	return PTE_ADDR(p[PAGE_TABLE_INDEX(va)]);
}


void check_page_free_list(int only_low_memory)
{
	struct page_info *pp;
	unsigned pdx_limit = only_low_memory ? 1 : 1024;
	int nfree_basemem = 0, nfree_extmem = 0;
	char *first_free_page;

	if (!page_free_list)
		panic("'page_free_list' is a null pointer!");

	if (only_low_memory) {
		// Move pages with lower addresses first in the free
		// list, since entry_pgdir does not map all pages.
		struct page_info *pp1, *pp2;
		struct page_info **tp[2] = { &pp1, &pp2 };
		for (pp = page_free_list; pp; pp = pp->link) {
			int pagetype = PAGE_DIR_INDEX(page_to_phys_addr(pp)) >= pdx_limit;
			*tp[pagetype] = pp;
			tp[pagetype] = &pp->link;
		}
		*tp[1] = 0;
		*tp[0] = pp2;
		page_free_list = pp1;
	}

	// if there's a page that shouldn't be on the free list,
	// try to make sure it eventually causes trouble.
	for (pp = page_free_list; pp; pp = pp->link) {
		if (PAGE_DIR_INDEX(page_to_phys_addr(pp)) < pdx_limit) {
			memset(page_to_kernel_vaddr(pp), 0x97, 128);
        }
    }

	first_free_page = (char *) boot_alloc(0);
	for (pp = page_free_list; pp; pp = pp->link) {
		// check that we didn't corrupt the free list itself
		assert(pp >= pages);
		assert(pp < pages + get_nvram_nbpages());
		assert(((char *) pp - (char *) pages) % sizeof(*pp) == 0);

		// check a few pages that shouldn't be on the free list
		assert(page_to_phys_addr(pp) != 0);
		assert(page_to_phys_addr(pp) != IOPHYSMEM);
		assert(page_to_phys_addr(pp) != EXTPHYSMEM - PAGE_SIZE);
		assert(page_to_phys_addr(pp) != EXTPHYSMEM);
		assert(page_to_phys_addr(pp) < EXTPHYSMEM || (char *) page_to_kernel_vaddr(pp) >= first_free_page);

		if (page_to_phys_addr(pp) < EXTPHYSMEM)
			++nfree_basemem;
		else
			++nfree_extmem;
	}

	assert(nfree_basemem > 0);
	assert(nfree_extmem > 0);
}

void
check_page_alloc(void)
{
	struct page_info *pp, *pp0, *pp1, *pp2;
	int nfree;
	struct page_info *fl;
	char *c;
	int i;

	if (!pages)
		panic("'pages' is a null pointer!");

	// check number of free pages
	for (pp = page_free_list, nfree = 0; pp; pp = pp->link)
		++nfree;

	// should be able to allocate three pages
	pp0 = pp1 = pp2 = 0;
	assert((pp0 = page_alloc(0)));
	assert((pp1 = page_alloc(0)));
	assert((pp2 = page_alloc(0)));

	assert(pp0);
	assert(pp1 && pp1 != pp0);
	assert(pp2 && pp2 != pp1 && pp2 != pp0);
	assert(page_to_phys_addr(pp0) < nb_total_pages*PAGE_SIZE);
	assert(page_to_phys_addr(pp1) < nb_total_pages*PAGE_SIZE);
	assert(page_to_phys_addr(pp2) < nb_total_pages*PAGE_SIZE);

	// temporarily steal the rest of the free pages
	fl = page_free_list;
	page_free_list = 0;

	// should be no free memory
	assert(!page_alloc(0));

	// free and re-allocate?
	page_free(pp0);
	page_free(pp1);
	page_free(pp2);
	pp0 = pp1 = pp2 = 0;
	assert((pp0 = page_alloc(0)));
	assert((pp1 = page_alloc(0)));
	assert((pp2 = page_alloc(0)));
	assert(pp0);
	assert(pp1 && pp1 != pp0);
	assert(pp2 && pp2 != pp1 && pp2 != pp0);
	assert(!page_alloc(0));

	// test flags
	memset(page_to_kernel_vaddr(pp0), 1, PAGE_SIZE);
	page_free(pp0);
	assert((pp = page_alloc(ALLOC_ZERO)));
	assert(pp && pp0 == pp);
	c = page_to_kernel_vaddr(pp);
	for (i = 0; i < PAGE_SIZE; i++)
		assert(c[i] == 0);

	// give free list back
	page_free_list = fl;

	// free the pages we took
	page_free(pp0);
	page_free(pp1);
	page_free(pp2);

	// number of free pages should be the same
	for (pp = page_free_list; pp; pp = pp->link)
		--nfree;
	assert(nfree == 0);

	kcons_prints("check_page_alloc() succeeded!\n");
}


// check page_insert, page_remove, &c
void
check_page(void)
{
	struct page_info *pp, *pp0, *pp1, *pp2;
	struct page_info *fl;
	pte_t *ptep, *ptep1;
	void *va;
	int i;
	extern pde_t entry_pgdir[];

	// should be able to allocate three pages
	pp0 = pp1 = pp2 = 0;
	assert((pp0 = page_alloc(0)));
	assert((pp1 = page_alloc(0)));
	assert((pp2 = page_alloc(0)));

	assert(pp0);
	assert(pp1 && pp1 != pp0);
	assert(pp2 && pp2 != pp1 && pp2 != pp0);

	// temporarily steal the rest of the free pages
	fl = page_free_list;
	page_free_list = 0;

	// should be no free memory
	assert(!page_alloc(0));

	// there is no page allocated at address 0
	assert(page_lookup(kern_page_dir, (void *) 0x0, &ptep) == NULL);

	// there is no free memory, so we can't allocate a page table
	assert(page_insert(kern_page_dir, pp1, 0x0, PTE_W) < 0);

	// free pp0 and try again: pp0 should be used for page table
	page_free(pp0);
	assert(page_insert(kern_page_dir, pp1, 0x0, PTE_W) == 0);
	assert(PTE_ADDR(kern_page_dir[0]) == page_to_phys_addr(pp0));
	assert(check_va2pa(kern_page_dir, 0x0) == page_to_phys_addr(pp1));
	assert(pp1->ref == 1);
	assert(pp0->ref == 1);

	// should be able to map pp2 at PAGE_SIZE because pp0 is already allocated for page table
	assert(page_insert(kern_page_dir, pp2, (void*) PAGE_SIZE, PTE_W) == 0);
	assert(check_va2pa(kern_page_dir, PAGE_SIZE) == page_to_phys_addr(pp2));
	assert(pp2->ref == 1);

	// should be no free memory
	assert(!page_alloc(0));

	// should be able to map pp2 at PAGE_SIZE because it's already there
	assert(page_insert(kern_page_dir, pp2, (void*) PAGE_SIZE, PTE_W) == 0);
	assert(check_va2pa(kern_page_dir, PAGE_SIZE) == page_to_phys_addr(pp2));
	assert(pp2->ref == 1);

	// pp2 should NOT be on the free list
	// could happen in ref counts are handled sloppily in page_insert
	assert(!page_alloc(0));

	// check that pgdir_walk returns a pointer to the pte
	ptep = (pte_t *) KERNEL_ADDR(PTE_ADDR(kern_page_dir[PAGE_DIR_INDEX(PAGE_SIZE)]));
	assert(pgdir_walk(kern_page_dir, (void*)PAGE_SIZE, 0) == ptep+PAGE_TABLE_INDEX(PAGE_SIZE));

	// should be able to change permissions too.
	assert(page_insert(kern_page_dir, pp2, (void*) PAGE_SIZE, PTE_W|PTE_U) == 0);
	assert(check_va2pa(kern_page_dir, PAGE_SIZE) == page_to_phys_addr(pp2));
	assert(pp2->ref == 1);
	assert(*pgdir_walk(kern_page_dir, (void*) PAGE_SIZE, 0) & PTE_U);
	assert(kern_page_dir[0] & PTE_U);

	// should be able to remap with fewer permissions
	assert(page_insert(kern_page_dir, pp2, (void*) PAGE_SIZE, PTE_W) == 0);
	assert(*pgdir_walk(kern_page_dir, (void*) PAGE_SIZE, 0) & PTE_W);
	assert(!(*pgdir_walk(kern_page_dir, (void*) PAGE_SIZE, 0) & PTE_U));

	// should not be able to map at PAGE_TABLE_SIZE because need free page for page table
	assert(page_insert(kern_page_dir, pp0, (void*) PAGE_TABLE_SIZE, PTE_W) < 0);

	// insert pp1 at PAGE_SIZE (replacing pp2)
	assert(page_insert(kern_page_dir, pp1, (void*) PAGE_SIZE, PTE_W) == 0);
	assert(!(*pgdir_walk(kern_page_dir, (void*) PAGE_SIZE, 0) & PTE_U));

	// should have pp1 at both 0 and PAGE_SIZE, pp2 nowhere, ...
	assert(check_va2pa(kern_page_dir, 0) == page_to_phys_addr(pp1));
	assert(check_va2pa(kern_page_dir, PAGE_SIZE) == page_to_phys_addr(pp1));
	// ... and ref counts should reflect this
	assert(pp1->ref == 2);
	assert(pp2->ref == 0);

	// pp2 should be returned by page_alloc
	assert((pp = page_alloc(0)) && pp == pp2);

	// unmapping pp1 at 0 should keep pp1 at PAGE_SIZE
	page_remove(kern_page_dir, 0x0);
	assert(check_va2pa(kern_page_dir, 0x0) == ~0);
	assert(check_va2pa(kern_page_dir, PAGE_SIZE) == page_to_phys_addr(pp1));
	assert(pp1->ref == 1);
	assert(pp2->ref == 0);

	// unmapping pp1 at PAGE_SIZE should free it
	page_remove(kern_page_dir, (void*) PAGE_SIZE);
	assert(check_va2pa(kern_page_dir, 0x0) == ~0);
	assert(check_va2pa(kern_page_dir, PAGE_SIZE) == ~0);
	assert(pp1->ref == 0);
	assert(pp2->ref == 0);

	// so it should be returned by page_alloc
	assert((pp = page_alloc(0)) && pp == pp1);

	// should be no free memory
	assert(!page_alloc(0));

	// forcibly take pp0 back
	assert(PTE_ADDR(kern_page_dir[0]) == page_to_phys_addr(pp0));
	kern_page_dir[0] = 0;
	assert(pp0->ref == 1);
	pp0->ref = 0;

	// check pointer arithmetic in pgdir_walk
	page_free(pp0);
	va = (void*)(PAGE_SIZE * 1024 + PAGE_SIZE);
	ptep = pgdir_walk(kern_page_dir, va, 1);
	ptep1 = (pte_t *) KERNEL_ADDR(PTE_ADDR(kern_page_dir[PAGE_DIR_INDEX(va)]));
	assert(ptep == ptep1 + PAGE_TABLE_INDEX(va));
	kern_page_dir[PAGE_DIR_INDEX(va)] = 0;
	pp0->ref = 0;

	// check that new page tables get cleared
	memset(page_to_kernel_vaddr(pp0), 0xFF, PAGE_SIZE);
	page_free(pp0);
	pgdir_walk(kern_page_dir, 0x0, 1);
	ptep = (pte_t *) page_to_kernel_vaddr(pp0);
	for(i=0; i<1024; i++)
		assert((ptep[i] & PTE_P) == 0);
	kern_page_dir[0] = 0;
	pp0->ref = 0;

	// give free list back
	page_free_list = fl;

	// free the pages we took
	page_free(pp0);
	page_free(pp1);
	page_free(pp2);

	kcons_prints("check_page() succeeded!\n");
}

extern char bootstacktop[], bootstack[];

void
check_kern_pgdir(void)
{
	uint32_t i, n;
	pde_t *pgdir;

	pgdir = kern_page_dir;

	// check pages array
	n = ROUNDUP(get_nvram_nbpages()*sizeof(struct page_info), PAGE_SIZE);
	for (i = 0; i < n; i += PAGE_SIZE)
		assert(check_va2pa(pgdir, UPAGES + i) == PHYS_ADDR(pages) + i);


	// check phys mem
	for (i = 0; i < get_nvram_nbpages() * PAGE_SIZE; i += PAGE_SIZE)
		assert(check_va2pa(pgdir, KERNEL_BASE + i) == i);

	// check kernel stack
	for (i = 0; i < KSTKSIZE; i += PAGE_SIZE)
		assert(check_va2pa(pgdir, KSTACKTOP - KSTKSIZE + i) == PHYS_ADDR(bootstack) + i);
	assert(check_va2pa(pgdir, KSTACKTOP - PAGE_TABLE_SIZE) == ~0);

	// check PDE permissions
	for (i = 0; i < 1024; i++) {
		switch (i) {
		case PAGE_DIR_INDEX(USER_VIRT_PAGE_ADDR):
		case PAGE_DIR_INDEX(KSTACKTOP-1):
		case PAGE_DIR_INDEX(UPAGES):
			assert(pgdir[i] & PTE_P);
			break;
		default:
			if (i >= PAGE_DIR_INDEX(KERNEL_BASE)) {
				assert(pgdir[i] & PTE_P);
				assert(pgdir[i] & PTE_W);
			} else
				assert(pgdir[i] == 0);
			break;
		}
	}
	kcons_prints("check_kern_pgdir() succeeded!\n");
}
