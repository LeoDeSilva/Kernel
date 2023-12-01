#include "VGA.h"
#include "ports.h"

#include <stdint.h>

// Screen device I/O ports
#define VGA_CTRL_REGISTER 0x3D4
#define VGA_DATA_REGISTER 0x3D5

#define VGA_OFFSET_LOW 0x0f
#define VGA_OFFSET_HIGH 0x0e

uint8_t ATTR_BYTE;

uint16_t VGA_get_offset(int col, int row) { 
    return 2 * (row * MAX_COLS + col); 
}

int VGA_get_offset_row(uint16_t offset) { 
    return offset / (2*MAX_COLS); 
}

int VGA_get_offset_col(uint16_t offset) { 
    return (offset - (VGA_get_offset_row(offset)*2*MAX_COLS))/2; 
}

void VGA_set_col(uint8_t attr_byte) {
    ATTR_BYTE = attr_byte;
}

uint16_t VGA_get_cursor_offset() {
    p_outb(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
    uint16_t offset = p_inb(VGA_DATA_REGISTER) << 8;

    p_outb(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
    offset |= p_inb(VGA_DATA_REGISTER);
    return offset * 2;
}

void VGA_set_cursor_offset(uint16_t offset) {
    offset /= 2;
    p_outb(VGA_CTRL_REGISTER, VGA_OFFSET_HIGH);
    p_outb(VGA_DATA_REGISTER, offset >> 8);
    p_outb(VGA_CTRL_REGISTER, VGA_OFFSET_LOW);
    p_outb(VGA_DATA_REGISTER, offset & 0xff);
}

void VGA_set_char(char ch, uint16_t offset) {
    uint8_t* vidmem = (uint8_t*)VIDEO_ADDRESS;

    vidmem[offset] = ch;
    vidmem[offset+1] = ATTR_BYTE;
}

void VGA_clear_screen() {
    uint8_t *vidmem = (uint8_t*)VIDEO_ADDRESS;
    for (int offset = 0; offset < MAX_COLS*MAX_ROWS*2; offset+=2) {
        vidmem[offset] = ' ';
        vidmem[offset+1] = ATTR_BYTE;
    }

    VGA_set_cursor_offset(0);
}
