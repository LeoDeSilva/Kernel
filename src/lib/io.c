#include "io.h"
#include "../drivers/VGA.h"
#include "mem.h"
#include "string.h"

#include <stdint.h>

void kprintf(char *str) {
    uint16_t offset = VGA_get_cursor_offset();
    for (char *p = str; *p != '\0'; p++) {
        switch (*p) {
            case '\n':
                offset = VGA_get_offset(0, VGA_get_offset_row(offset)+1);
                break;

            default:
                VGA_set_char(*p, offset);
                offset += 2;
                break;
        }

        while (offset >= MAX_COLS*MAX_ROWS*2) {
            for (int i = 1; i < MAX_ROWS; i++)
                memcpy(
                        (void*)(VIDEO_ADDRESS + VGA_get_offset(0, i)),
                        (void*)(VIDEO_ADDRESS + VGA_get_offset(0, i-1)),
                        MAX_COLS*2
                  );

            for (int col = 0; col < MAX_COLS; col++)
                VGA_set_char(' ', VGA_get_offset(col, MAX_ROWS-1));

            offset = VGA_get_offset(0,MAX_ROWS-1);
        }
    }

    VGA_set_cursor_offset(offset);
}
