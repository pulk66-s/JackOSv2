#ifndef __JACKOS_KERNEL_GDT_TYPES_HPP__
    #define __JACKOS_KERNEL_GDT_TYPES_HPP__

    #include <stdint.h>

    #define NO_GDT_DESCRIPTORS     8

struct base {
    uint16_t low;
    uint8_t middle, high;
};

struct gdt_entry {
    uint16_t segment_limit;              // segment limit first 0-15 bits
    uint16_t base_low;                   // base first 0-15 bits
    uint8_t base_middle;                 // base 16-23 bits
    uint8_t access;                      // access byte
    uint8_t granularity;                 // high 4 bits (flags) low 4 bits (limit 4 last bits)(limit is 20 bit wide)
    uint8_t base_high;                   // base 24-31 bits
} __attribute__((packed));

struct gdt_descriptor {
    uint16_t limit;                      // limit size of all GDT segments
    struct gdt_entry *gdt;               // base address of the first GDT segment
} __attribute__((packed));

#endif