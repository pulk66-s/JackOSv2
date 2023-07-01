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
        .idt = this->idt
    };

    this->fillEntries();
    this->enableAllEntries();
    this->pic.remap();
    this->lidt();
    this->sti();
}

void IDT::enableEntry(uint8_t index)
{
    this->idt[index].flags |= IDT_FLAG_PRESENT;
}

void IDT::sti()
{
    asm volatile("sti");
}

void IDT::disableEntry(uint8_t index)
{
    this->idt[index].flags &= ~IDT_FLAG_PRESENT;
}

void IDT::createIdtEntry(uint8_t index, void *call, uint16_t segment, uint8_t flags)
{
    this->idt[index] = (struct idt_entry) {
        .call_low = ((uint32_t)call) & 0xFFFF,
        .segment = segment,
        .always_null = 0,
        .flags = flags,
        .call_high = ((uint32_t)call >> 16) & 0xFFFF
    };
}

void IDT::lidt()
{
    asm volatile("lidt (%0)" : : "r" (&this->idt_descriptor));
}

void IDT::fillEntries()
{
    this->createIdtEntry(0, (void *)isr0, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(1, (void *)isr1, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(2, (void *)isr2, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(3, (void *)isr3, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(4, (void *)isr4, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(5, (void *)isr5, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(6, (void *)isr6, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(7, (void *)isr7, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(8, (void *)isr8, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(9, (void *)isr9, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(10, (void *)isr10, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(11, (void *)isr11, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(12, (void *)isr12, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(13, (void *)isr13, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(14, (void *)isr14, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(15, (void *)isr15, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(16, (void *)isr16, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(17, (void *)isr17, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(18, (void *)isr18, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(19, (void *)isr19, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(20, (void *)isr20, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(21, (void *)isr21, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(22, (void *)isr22, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(23, (void *)isr23, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(24, (void *)isr24, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(25, (void *)isr25, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(26, (void *)isr26, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(27, (void *)isr27, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(28, (void *)isr28, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(29, (void *)isr29, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(30, (void *)isr30, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(31, (void *)isr31, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(32, (void *)irq0, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(33, (void *)irq1, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(34, (void *)irq2, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(35, (void *)irq3, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(36, (void *)irq4, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(37, (void *)irq5, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(38, (void *)irq6, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(39, (void *)irq7, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(40, (void *)irq8, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(41, (void *)irq9, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(42, (void *)irq10, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(43, (void *)irq11, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(44, (void *)irq12, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(45, (void *)irq13, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(46, (void *)irq14, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
    this->createIdtEntry(47, (void *)irq15, IDT_USED_SEGMENT, IDT_FLAG_RING0 | IDT_FLAG_GATE_32BIT_INT);
}

void IDT::enableAllEntries(void)
{
    for (size_t i = 0; i < IDT_SIZE; i++) {
        this->idt[i].flags |= IDT_FLAG_PRESENT;
    }
}