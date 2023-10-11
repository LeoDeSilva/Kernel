#include "screen.h"
#include "../kernel/low_level.h"

int get_screen_offset(int row, int col) {
    int offset = (row * MAX_COLS + col) * 2;
    return offset;
}

int get_cursor_offset() {
    // High byte of cursor offset (data 14) low byte (data 15)
    port_byte_out(REG_SCREEN_CTRL, 14);
    int offset = port_byte_in(REG_SCREEN_DATA) << 8; /* High byte: << 8 */
    port_byte_out(REG_SCREEN_CTRL, 15);
    offset += port_byte_in(REG_SCREEN_DATA);
    return offset * 2; /* Position * size of character cell */
}

void set_cursor_offset(int offset) {
    offset /= 2;
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (unsigned char)(offset & 0xff));
}

void hide_cursor() {
    port_byte_out(REG_SCREEN_CTRL, 0x0A);
    port_byte_out(REG_SCREEN_DATA, 0x20);
}

void print_char(char ch, int offset, char attr_byte) {
    char* VIDEO_MEMORY = (char*)0xb8000;
    *(VIDEO_MEMORY + offset) = ch;
}

void print_string(char* str, int row, int col, char attr_byte) {
    int offset = get_screen_offset(row, col);

    int i = 0;
    while (str[i] != 0) {
        print_char(str[i], offset, attr_byte);
        offset += 2;
        i++;
    }
}

void clear_screen() {
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            int offset = get_screen_offset(row, col);
            print_char(' ', offset, WHITE_ON_BLACK);
        }
    }
}