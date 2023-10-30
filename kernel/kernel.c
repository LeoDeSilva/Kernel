#include "../drivers/screen.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"
#include "../libc/io.h"
#include "../drivers/keyboard.h"
#include "../libc/string.h"
#include "../drivers/event.h"

void init_shell() {
    clear_screen(0x00);
    kprint(":HONEYCOMB:\n");
    kprint("A barebones pet project operating system\n\n");

    static char* input_buf;
    while (1) {
        kprint(">>");
        readline(input_buf);

        kprint(input_buf);
        kprint("\n");

        if (strcmp(input_buf, "CLS") == 0) {
            clear_screen(WHITE_ON_BLACK);
        }
    }
}

void main() {
    isr_install();
    irq_install();

    clear_screen(WHITE_ON_BLACK);

    Event event;
    while (1) {
        event = pop_event();
        if (event.type != NIL) {
            switch (event.data.keydown.scancode) {
                case BACKSPACE:
                    kprint_backspace();
                    break;
                case ENTER:
                    kprint("\n");
                    break;
                default:
                    char keycode = event.data.keydown.keycode;
                    kprint_letter(keycode);
                    break;
            }
        }
    }

    // init_shell();
}
