#include "screen.h"
#include "../kernel/low_level.h"

int get_screen_offset(int row, int col) {
    int offset = (row * MAX_COLS + col) * 2;
    return offset;
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