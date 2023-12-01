#ifndef VGA_H
#define VGA_H

#include <stdint.h>

#define VIDEO_ADDRESS 0xb8000

#define MAX_COLS 80
#define MAX_ROWS 25

#define WHITE_ON_BLACK 0x0f

uint16_t VGA_get_offset(int col, int row);
int VGA_get_offset_row(uint16_t offset);
int VGA_get_offset_col(uint16_t offset);

void VGA_set_col(uint8_t attr_byte);
void VGA_set_char(char ch, uint16_t offset);
void VGA_clear_screen();

uint16_t VGA_get_cursor_offset();
void VGA_set_cursor_offset(uint16_t offset);

#endif
