#include "kernel/IDT/Handler/IRQHandler.hpp"

namespace JO::Kernel::IDT::Handler {
    IRQHandler::IRQHandler() {
        for (int i = 0; i < IRQ_SIZE; i++) {
            for (int j = 0; j < IRQ_MAX_CALLBACKS; j++) {
                callbacks[i][j] = nullptr;
            }
        }
    }

    void IRQHandler::handle(struct registers *regs) {
        // if (regs->interrupt >= 40) {
        //     this->pic.outb(0xa0, 0x20);
        // }
        // this->pic.inb(0x20, 0x20);
        // if (this->callbacks[regs->interrupt]) {
        //     for (int i = 0; i < IRQ_MAX_CALLBACKS; i++) {
        //         if (this->callbacks[regs->interrupt][i]) {
        //             this->callbacks[regs->interrupt][i](regs);
        //         }
        //     }
        // }
    }

    void IRQHandler::addCallback(int irq, handler callback) {
        for (int i = 0; i < IRQ_MAX_CALLBACKS; i++) {
            if (callbacks[irq][i] == nullptr) {
                callbacks[irq][i] = callback;
                return;
            }
        }
}
}