#include "../drivers/screen.h"
#include "utils.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"
#include "../cpu/timer.h"
#include "../drivers/keyboard.h"

void main() {
    isr_install();
    asm volatile("sti"); // set interrupt flag (enable interrupts)

    // init_timer(50);
    init_keyboard();
}