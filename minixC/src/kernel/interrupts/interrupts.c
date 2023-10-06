#include <interrupts.h>
#include <drivers/vga.h>
#include <drivers/pic.h>

static struct idt_entry idt[IDT_ENTRIES] = {0};
static struct idt_ptr idt_ptr;
static isr_callback callback[IDT_ENTRIES][MAX_CALLBAC_PER_ENTRY] = {0};

static void fill_all_entries();

/**
 * @brief       Fill an entry of the IDT
 * @param   nb  The number of the entry
 * @param   isr The address of the ISR
*/
static inline void idt_fill_entry(uint8_t nb, uint32_t isr)
{
    idt[nb].isr_low = isr & 0xFFFF;
    idt[nb].kernel_cs = 0x08;
    idt[nb].reserved = 0;
    idt[nb].attributes = 0x80 | 0x0E;
    idt[nb].isr_high = (isr >> 16) & 0xFFFF;
}

#define PIC1		0x20		/* IO base address for master PIC */
#define PIC2		0xA0		/* IO base address for slave PIC */
#define PIC1_COMMAND	PIC1
#define PIC1_DATA	(PIC1+1)
#define PIC2_COMMAND	PIC2
#define PIC2_DATA	(PIC2+1)

/* reinitialize the PIC controllers, giving them specified vector offsets
   rather than 8h and 70h, as configured by default */
 
#define ICW1_ICW4	0x01		/* Indicates that ICW4 will be present */
#define ICW1_SINGLE	0x02		/* Single (cascade) mode */
#define ICW1_INTERVAL4	0x04		/* Call address interval 4 (8) */
#define ICW1_LEVEL	0x08		/* Level triggered (edge) mode */
#define ICW1_INIT	0x10		/* Initialization - required! */
 
#define ICW4_8086	0x01		/* 8086/88 (MCS-80/85) mode */
#define ICW4_AUTO	0x02		/* Auto (normal) EOI */
#define ICW4_BUF_SLAVE	0x08		/* Buffered mode/slave */
#define ICW4_BUF_MASTER	0x0C		/* Buffered mode/master */
#define ICW4_SFNM	0x10		/* Special fully nested (not) */

void remap_pic(int offset1, int offset2)
{
	uint8_t a1, a2;
 
	a1 = pic_read(PIC1_DATA);                        // save masks
	a2 = pic_read(PIC2_DATA);
 
	pic_write(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);  // starts the initialization sequence (in cascade mode)
	pic_wait();
	pic_write(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	pic_wait();
	pic_write(PIC1_DATA, offset1);                 // ICW2: Master PIC vector offset
	pic_wait();
	pic_write(PIC2_DATA, offset2);                 // ICW2: Slave PIC vector offset
	pic_wait();
	pic_write(PIC1_DATA, 4);                       // ICW3: tell Master PIC that there is a slave PIC at IRQ2 (0000 0100)
	pic_wait();
	pic_write(PIC2_DATA, 2);                       // ICW3: tell Slave PIC its cascade identity (0000 0010)
	pic_wait();
 
	pic_write(PIC1_DATA, ICW4_8086);               // ICW4: have the PICs use 8086 mode (and not 8080 mode)
	pic_wait();
	pic_write(PIC2_DATA, ICW4_8086);
	pic_wait();
 
	pic_write(PIC1_DATA, a1);   // restore saved masks.
	pic_write(PIC2_DATA, a2);
}

/**
 * @brief       Setup the interrupt descriptor table.
*/
void idt_setup()
{
    fill_all_entries();
    remap_pic(0x20, 0x28);
    idt_ptr.limit = sizeof(idt) - 1;
    idt_ptr.base = (uint32_t)&idt;
    __asm__ volatile("lidt %0" : : "m"(idt_ptr));
    __asm__ volatile("sti");
}

/**
 * @brief       This file handles the interrupt.
 * @param   nb  The number of the interrupt.
*/
extern void isr_handler(struct registers *regs)
{
    for (size_t i = 0; i < MAX_CALLBAC_PER_ENTRY; i++) {
        if (callback[regs->interrupt][i] != 0) {
            callback[regs->interrupt][i](regs);
        }
    }
}

/**
 * @brief       This file handles the interrupt request.
 * @param   nb  The number of the interrupt.
*/
extern void irq_handler(struct registers *regs)
{
    if (regs->interrupt >= 40) {
        pic_write(0xa0, 0x20);
    }
    pic_write(0x20, 0x20);
    for (size_t i = 0; i < MAX_CALLBAC_PER_ENTRY; i++) {
        if (callback[regs->interrupt][i] != 0) {
            callback[regs->interrupt][i](regs);
        }
    }
}

/**
 * @brief   Enable an interrupt.
 * @param   nb  The number of the interrupt.
*/
void enable_interrupt(uint8_t nb)
{
    idt[nb].attributes |= 128;
}

/**
 * @brief   Add a callback to an interrupt.
*/
void set_callback(int nb, isr_callback cb)
{
    for (size_t i = 0; i < MAX_CALLBAC_PER_ENTRY; i++) {
        if (callback[nb][i] == 0) {
            callback[nb][i] = cb;
            return;
        }
    }
}

/**
 * @brief       Fill all the entries of the IDT with default values.
*/
static void fill_all_entries()
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
    idt_fill_entry(32, (uint32_t)irq0);
    idt_fill_entry(33, (uint32_t)irq1);
    idt_fill_entry(34, (uint32_t)irq2);
    idt_fill_entry(35, (uint32_t)irq3);
    idt_fill_entry(36, (uint32_t)irq4);
    idt_fill_entry(37, (uint32_t)irq5);
    idt_fill_entry(38, (uint32_t)irq6);
    idt_fill_entry(39, (uint32_t)irq7);
    idt_fill_entry(40, (uint32_t)irq8);
    idt_fill_entry(41, (uint32_t)irq9);
    idt_fill_entry(42, (uint32_t)irq10);
    idt_fill_entry(43, (uint32_t)irq11);
    idt_fill_entry(44, (uint32_t)irq12);
    idt_fill_entry(45, (uint32_t)irq13);
    idt_fill_entry(46, (uint32_t)irq14);
    idt_fill_entry(47, (uint32_t)irq15);
}
