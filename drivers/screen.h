#include "../cpu/types.h"

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

#define WHITE_ON_BLACK 0x0f

// Screen device I/O ports
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

void print_at(char* msg, int col, int row);
void print(char* msg);
void clear_screen(u8 colour);
int handle_scrolling(int offset);

int get_screen_offset(int col, int row);
int get_cursor_offset();
void set_cursor_offset(int offset);
void hide_cursor();

void print_char(char ch, int col, int row, char attr_byte);
int get_offset(int col, int row);
int get_offset_row(int offset);
int get_offset_col(int offset);