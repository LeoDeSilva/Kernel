#include "../libc/mem.h"
#include "screen.h"
#include "ports.h"

// Public 
void clear_screen(u8 colour) {
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            int offset = get_offset(col, row);
            print_char(' ', col, row, colour);
        }
    }

    set_cursor_offset(0);
}

void print_at(char* msg, int col, int row) {
    if (col >= 0 && row >= 0) {
        set_cursor_offset(get_offset(col, row));
    }

    int i = 0;
    while (msg[i]) {
        print_char(msg[i++], col, row, WHITE_ON_BLACK);
        int cursor_offset = get_cursor_offset();
        row = get_offset_row(cursor_offset);
        col = get_offset_col(cursor_offset);
    }
}

void print(char* msg) {
    print_at(msg, -1, -1);
}

// Private
void print_char(char ch, int col, int row, char attr_byte) {
    unsigned char *vidmem = (unsigned char*) VIDEO_ADDRESS;

    if (!attr_byte) {
        attr_byte = WHITE_ON_BLACK;
    }

    int offset;
    if (col >=0 && row >= 0) {
        offset = handle_scrolling(get_offset(col, row));
    } else {
        offset = handle_scrolling(get_cursor_offset());
    }

    if (ch == '\n') {
        int rows = get_offset_row(offset);
        offset = get_offset(0, rows+1);
    } else {
        vidmem[offset] = ch;
        vidmem[offset+1] = attr_byte;
        offset += 2;
    }

    offset = handle_scrolling(offset);
    set_cursor_offset(offset);
}

int handle_scrolling(int offset) {
   while (offset >= MAX_ROWS * MAX_COLS * 2) {
        // for each row, (starting at index 1) memcpy to row above
        // intialise empty last row & set cursor to beginning of last row
        int i;
        for (i = 1; i < MAX_ROWS; i++) {
            memcpy(
                (char*)(VIDEO_ADDRESS + get_offset(0, i)), 
                (char*)(VIDEO_ADDRESS + get_offset(0, i-1)), 
                MAX_COLS*2);
        }

        char* final_line = (char*)(VIDEO_ADDRESS + get_offset(0, MAX_ROWS-1));
        for (i = 0; i < MAX_COLS*2; i++) final_line[i] = 0;

        offset = get_offset(0, MAX_ROWS-1);
    }

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

int get_offset(int col, int row) { return 2 * (row * MAX_COLS + col); }
int get_offset_row(int offset) { return offset / (2 * MAX_COLS); }
int get_offset_col(int offset) { return (offset - (get_offset_row(offset)*2*MAX_COLS))/2; }
