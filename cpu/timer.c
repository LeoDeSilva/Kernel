#include "timer.h"
#include "../drivers/screen.h"
#include "../kernel/utils.h"
#include "isr.h"

u32 tick = 0;

static void timer_callback(registers_t regs) {
    tick++;
    print("Tick: ");
    print(iota(tick));

    print("\n");
}

void init_timer(u32 freq) {
    register_interrupt_handler(IRQ0, timer_callback);

    /* Get the PIT value: hardware clock at 1193180 Hz */
    // The value we send to the PIT is the value to divide it's input clock
    // (1193180 Hz) by, to get our required frequency. Important to note is
    // that the divisor must be small enough to fit into 16-bits. 
    u32 divisor = 1193180 / freq;
    u8 low  = (u8)(divisor & 0xFF);
    u8 high = (u8)((divisor >> 8) & 0xFF);

    /* Send the command */
    port_byte_out(0x43, 0x36); /* PIT Command port */

    // send the frequency divisor
    port_byte_out(0x40, low);
    port_byte_out(0x40, high);
}