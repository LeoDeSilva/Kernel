#include "../drivers/screen.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"
#include "../libc/io.h"
#include "../drivers/keyboard.h"
#include "../libc/string.h"
#include "../drivers/event.h"

void main() {
    isr_install();
    irq_install();

    clear_screen(WHITE_ON_BLACK);

    char input_buf[256];

    kprint(":Honeycomb:\n");
    kprint("a pet project operating system\n\n");
    while (1) {
        kprint(">>");
        readline(input_buf);

        kprint(input_buf);
        kprint("\n");

        if (strcmp(input_buf, "cls") == 0) {
            clear_screen(WHITE_ON_BLACK);
        }
    }
}
