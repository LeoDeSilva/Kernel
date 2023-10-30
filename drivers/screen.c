#include "../libc/mem.h"
#include "screen.h"
#include "../cpu/ports.h"

void clear_screen(uint8_t colour);
int handle_scrolling(int offset);

int get_screen_offset(int col, int row);
int get_cursor_offset();
void set_cursor_offset(int offset);
void hide_cursor();

void print_char(char ch, int col, int row, char attr_byte);
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);

// Public 
void clear_screen(uint8_t colour) {
    for (int row = 0; row < MAX_ROWS; row++) {
        for (int col = 0; col < MAX_COLS; col++) {
            print_char(' ', col, row, colour);
        }
    }

    set_cursor_offset(0);
}


void kprint_at(char* msg, int col, int row) {
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

void kprint(char* msg) {
    kprint_at(msg, -1, -1);
}

void kprint_letter(char ch) {
    char str[2] = {ch, '\0'};
    kprint(str);
}

void kprint_backspace() {
    int offset = get_cursor_offset()-2;
    int row = get_offset_row(offset);
    int col = get_offset_col(offset);
    print_char(' ', col, row, WHITE_ON_BLACK);
    set_cursor_offset(offset);
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
                (uint8_t*)(VIDEO_ADDRESS + get_offset(0, i)), 
                (uint8_t*)(VIDEO_ADDRESS + get_offset(0, i-1)), 
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
