#ifndef __JACKOS_KERNEL_IDT_TYPES_HPP__
    #define __JACKOS_KERNEL_IDT_TYPES_HPP__

    #include <stdint.h>

    /**
     * @brief The size of the IDT in entry (idt_entry)
    */
        #define IDT_SIZE 256

    /**
     * @brief the GDT segment used by the IDT It's the kernel code segment
     * 0x08 = kernel code segment in GDT
    */
        #define IDT_USED_SEGMENT 0x08

/**
 * @brief This is the structure of an IDT entry.
 * The IDT entry is 8 bytes long. (Protected mode)
 * The IDT contains IDT_SIZE entries.
 * It contains:
 *  - 2 bytes for the callback low bytes address
 *  - 2 bytes for the segment selector
 *  - 1 byte for the zero
 *  - 1 byte for the type
 *  - 2 bytes for the callback high bytes address
*/
struct idt_entry {
    uint16_t call_low;
    uint16_t segment;
    uint8_t always_null;
    uint8_t flags;
    uint16_t call_high;
} __attribute__((packed));

/**
 * @brief IDT descriptor, must be describe the IDT,
 * it contains:
 *  - size: the size of the IDT - 1
 *  - idt: the address of the IDT
 * The IDT descriptor is used by the lidt instruction.
*/
struct idt_descriptor {
    uint16_t size;
    struct idt_entry *idt;
} __attribute__((packed));

/**
 * @brief This is the structure of all the data provides by the STUB.
 * The STUB is a small functions that is called after the interrupts,
 * to make the transition from asm to C.
 * This structure contains all the content pushed in the stack
*/
struct registers {
    uint32_t ds;
    uint32_t edi, esi, ebp, useless, ebx, edx, ecx, eax;
    uint32_t interrupt, error;
    uint32_t eip, cs, eflags, esp, ss;
} __attribute__((packed));

/**
 * @brief This is the enum of all the flags of the IDT entries.
 * The flags are used to describe the IDT entry permissions and othe
 * informations.
*/
enum IDT_FLAGS {
    IDT_FLAG_GATE_32BIT_INT     = 0xe,
    IDT_FLAG_RING0              = (0 << 5),
    IDT_FLAG_PRESENT            = 0x80
};

/**
 * @brief This is a typedef to a function pointer.
 * It will launch the function when an interrupt is called.
*/
typedef void (*isrHandler)(registers *regs);

#endif
