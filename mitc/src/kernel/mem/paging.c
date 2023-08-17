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
    for (; va < (uintptr_t)va + size; va += PAGE_SIZE, pa += PAGE_SIZE) {
        pte_t *pte = pgdir_walk(pgdir, (void *)va, 1);

        if (!pte) {
            panic("page_map_region: pte should exist");
        }
        if (*pte & PTE_P) {
            panic("page_map_region: page already mapped");
        }
        *pte = pa | perm | PTE_P;
    }
}







#include <include/mem.h>
#include <include/clib/memory.h>
#include <include/assert.h>
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
            if (page_to_kernel_vaddr(pp) == NULL) {
                panic("NULLL");
            }
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