#include "io.h"
#include "../drivers/keyboard.h"
#include "../drivers/screen.h"
#include "../drivers/event.h"
#include "../libc/mem.h"
#include "../libc/string.h"

void readline(char *buf) {
    int read = 1;

    Event event;
    char key_buffer[256];
    key_buffer[0] = '\0';

    while (read) {
        event = pop_event();
        if (event.type != NIL) {
            switch (event.data.keydown.scancode) {
                case BACKSPACE:
                    if (strlen(key_buffer) > 0) {
                        key_buffer[strlen(key_buffer)-1] = '\0';
                        kprint_backspace();
                    }
                    break;
                case ENTER:
                    kprint("\n");
                    read = 0;
                    break;
                default:
                    char key = event.data.keydown.keycode;
                    if (key != '?') {
                        concat(key_buffer, key);
                        kprint_letter(key);
                    }
                    break;
            }
        }
    }

    memcpy((uint8_t*)key_buffer, (uint8_t*)buf, 256);
    return;
}
