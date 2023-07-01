#include "kernel/IDT/IDT.hpp"
#include "kernel/IDT/interrupts.hpp"
#include <stddef.h>

void IDT::init()
{
    for (size_t i = 0; i < IDT_SIZE; i++) {
        this->idt[i] = (struct idt_entry) {
            .call_low = 0,
            .segment = 0,
            .always_null = 0,
            .flags = 0,
            .call_high = 0
        };
    }
    this->idt_descriptor = (struct idt_descriptor) {
        .size = sizeof(struct idt_entry) * IDT_SIZE - 1,
        .idt = (struct idt_entry *) &this->idt
    };

    this->fillEntries();
    this->enableAllEntries();
    this->pic.remap();
    this->disableEntry(0x80);
    this->lidt();
    this->sti();
}

void IDT::enableEntry(uint8_t index)
{
    this->idt[index].flags |= IDT_FLAG_PRESENT;
}

inline void IDT::sti()
{
    asm volatile("sti");
}

inline void IDT::disableEntry(uint8_t index)
{
    this->idt[index].flags &= ~IDT_FLAG_PRESENT;
}

inline void IDT::createIdtEntry(uint8_t index, void (*call)(), uint16_t segment, uint8_t flags)
{
    this->idt[index] = (struct idt_entry) {
        .call_low = (uint16_t)(((uint32_t) call) & 0xffff),
        .segment = segment,
        .always_null = 0,
        .flags = flags,
        .call_high = (uint16_t)(((uint32_t) call) >> 16)
    };
}

inline void IDT::lidt()
{
    asm volatile("lidt (%0)" : : "r" (&this->idt_descriptor));
}

void IDT::fillEntries()
{
    this->createIdtEntry(0, isr0, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(1, isr1, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(2, isr2, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(3, isr3, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(4, isr4, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(5, isr5, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(6, isr6, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(7, isr7, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(8, isr8, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(9, isr9, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(10, isr10, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(11, isr11, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(12, isr12, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(13, isr13, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(14, isr14, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(15, isr15, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(16, isr16, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(17, isr17, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(18, isr18, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(19, isr19, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(20, isr20, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(21, isr21, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(22, isr22, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(23, isr23, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(24, isr24, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(25, isr25, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(26, isr26, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(27, isr27, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(28, isr28, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(29, isr29, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(30, isr30, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(31, isr31, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(32, irq0, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(33, irq1, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(34, irq2, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(35, irq3, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(36, irq4, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(37, irq5, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(38, irq6, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(39, irq7, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(40, irq8, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(41, irq9, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(42, irq10, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(43, irq11, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(44, irq12, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(45, irq13, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(46, irq14, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(47, irq15, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
}

void IDT::enableAllEntries(void)
{
    for (size_t i = 0; i < IDT_SIZE; i++) {
        this->idt[i].flags |= IDT_FLAG_PRESENT;
    }
}