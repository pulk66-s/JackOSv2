#include "kernel/IDT/Handler/ISRHandler.hpp"

ISRHandler::ISRHandler() {
    for (int i = 0; i < ISR_SIZE; i++) {
        for (int j = 0; j < ISR_MAX_CALLBACKS; j++) {
            callbacks[i][j] = nullptr;
        }
    }
}

void ISRHandler::handle(struct registers *regs) {
    // if (this->callbacks[regs->interrupt]) {
    //     for (int i = 0; i < ISR_MAX_CALLBACKS; i++) {
    //         if (this->callbacks[regs->interrupt][i]) {
    //             this->callbacks[regs->interrupt][i](regs);
    //         }
    //     }
    // }
}

void ISRHandler::addCallback(int isr, handler callback) {
    for (int i = 0; i < ISR_MAX_CALLBACKS; i++) {
        if (callbacks[isr][i] == nullptr) {
            callbacks[isr][i] = callback;
            return;
        }
    }
}