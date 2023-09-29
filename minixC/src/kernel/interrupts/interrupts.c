#include <interrupts.h>
#include <drivers/vga.h>

static struct idt_entry idt[IDT_ENTRIES];
static struct idt_ptr idt_ptr;

/**
 * @brief       Fill an entry of the IDT
 * @param   nb  The number of the entry
 * @param   isr The address of the ISR
*/
static void idt_fill_entry(uint8_t nb, uint32_t isr)
{
    idt[nb].isr_low = isr & 0xFFFF;
    idt[nb].kernel_cs = 0x08;
    idt[nb].reserved = 0;
    idt[nb].attributes = 0x8E;
    idt[nb].isr_high = (isr >> 16) & 0xFFFF;
}

/**
 * @brief       Setup the interrupt descriptor table.
*/
void idt_setup()
{
    idt_fill_entry(0, (uint32_t)isr0);
    idt_fill_entry(1, (uint32_t)isr1);
    idt_fill_entry(2, (uint32_t)isr2);
    idt_fill_entry(3, (uint32_t)isr3);
    idt_fill_entry(4, (uint32_t)isr4);
    idt_fill_entry(5, (uint32_t)isr5);
    idt_fill_entry(6, (uint32_t)isr6);
    idt_fill_entry(7, (uint32_t)isr7);
    idt_fill_entry(8, (uint32_t)isr8);
    idt_fill_entry(9, (uint32_t)isr9);
    idt_fill_entry(10, (uint32_t)isr10);
    idt_fill_entry(11, (uint32_t)isr11);
    idt_fill_entry(12, (uint32_t)isr12);
    idt_fill_entry(13, (uint32_t)isr13);
    idt_fill_entry(14, (uint32_t)isr14);
    idt_fill_entry(15, (uint32_t)isr15);
    idt_fill_entry(16, (uint32_t)isr16);
    idt_fill_entry(17, (uint32_t)isr17);
    idt_fill_entry(18, (uint32_t)isr18);
    idt_fill_entry(19, (uint32_t)isr19);
    idt_fill_entry(20, (uint32_t)isr20);
    idt_fill_entry(21, (uint32_t)isr21);
    idt_fill_entry(22, (uint32_t)isr22);
    idt_fill_entry(23, (uint32_t)isr23);
    idt_fill_entry(24, (uint32_t)isr24);
    idt_fill_entry(25, (uint32_t)isr25);
    idt_fill_entry(26, (uint32_t)isr26);
    idt_fill_entry(27, (uint32_t)isr27);
    idt_fill_entry(28, (uint32_t)isr28);
    idt_fill_entry(29, (uint32_t)isr29);
    idt_fill_entry(30, (uint32_t)isr30);
    idt_fill_entry(31, (uint32_t)isr31);

    idt_ptr.limit = sizeof(idt) - 1;
    idt_ptr.base = (uint32_t)&idt;
    __asm__ volatile("lidt %0" : : "m"(idt_ptr));
    __asm__ volatile("sti");
}

/**
 * @brief       This file handles the interrupt request.
 * @param   nb  The number of the interrupt.
*/
extern void exception_handler(uint8_t nb)
{
}
