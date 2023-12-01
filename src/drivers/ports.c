#include "ports.h"
#include <stdint.h>

uint8_t p_inb(uint16_t port) {
    uint8_t result;
    asm("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void p_outb(uint16_t port, uint8_t data) {
    asm("out %%al, %%dx" : :"a" (data), "d" (port));
}

uint16_t p_inw(uint16_t port) {
    uint16_t result;
    asm("in %%dx, %%al" : "=a" (result) : "d" (port));
    return result;
}

void p_outw(uint16_t port, uint16_t data) {
    asm("out %%al, %%dx" : :"a" (data), "d" (port));
}
