#include <mem.h>
#include <lib/mem.h>
#include <drivers/vga.h>

static uint8_t *memory_block_start;
static size_t memory_block_size;

/**
 * @brief           The physical memory management block structure
 * @param   start   The start address of the block
 * @param   size    The size of the block
*/
void init_physical_memory(phys_addr start, size_t size)
{
    memory_block_start = start;
    memory_block_size = size;
    memset(memory_block_start, MAX_UINT8, memory_block_size);
}

/**
 * @brief           Check if the current block is free
 * @param   block   The start address of the block
 * @return          1 if the block is free, 0 otherwise
*/
static int is_block_free(phys_addr *block)
{
    for (phys_addr *addr = block; addr < block + sizeof(phys_addr); addr++) {
        if (*addr != MAX_UINT8) {
            return 0;
        }
    }
    return 1;
}

/**
 * @brief           Find the first block that is free and has the size of the given block
 * @param   size    The size of the block
 * @return          The start address of the block
*/
static phys_addr *find_free_block(size_t size)
{
    int y = 0;
    for (uint8_t *block = memory_block_start; block < memory_block_start + memory_block_size; block += size) {
        int is_all_block_free = 1;
        vga_print(20, y++, 0x0F, "block: ");

        for (uint8_t *addr = block; addr < block + size; addr++) {
            if (*addr != MAX_UINT8) {
                is_all_block_free = 0;
                break;
            }
        }
        if (is_all_block_free) {
            return block;
        }
    }
    return NULL;
}

/**
 * @brief           Allocate a block of physical memory
 * @param   size    The size of the block
 * @return          The start address of the block
*/
phys_addr *alloc_physical_block(size_t size)
{
    phys_addr *block = find_free_block(size);

    if (!block) {
        vga_clear();
        vga_print(0, 0, 0x0F, "No more physical memory available\n");
        for (;;);
    }
    vga_printn(20, 10, 0x0F, block);
    memset(block, 0, size);
    return block;
}

/**
 * @brief           Free a block of physical memory
 * @param   block   The start address of the block
 * @param   size    The size of the block
*/
void free_physical_block(phys_addr *block, size_t size)
{
    memset(block, MAX_UINT8, size);
}
