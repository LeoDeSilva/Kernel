#include "../drivers/screen.h"
#include "../libc/function.h"
#include "../cpu/ports.h"
#include "timer.h"
#include "isr.h"

uint32_t tick = 0;

static void timer_callback(registers_t regs) {
    tick++;
    UNUSED(regs);
}

void init_timer(uint32_t freq) {
    register_interrupt_handler(IRQ0, timer_callback);

    uint32_t divisor = 1193180 / freq;       /* Calculate our divisor */
    port_byte_out(0x43, 0x36);             /* Set our command byte 0x36 */
    port_byte_out(0x40, divisor & 0xFF);   /* Set low byte of divisor */
    port_byte_out(0x40, divisor >> 8);     /* Set high byte of divisor */
}