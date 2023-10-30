#include <stdint.h>

#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

#define WHITE_ON_BLACK 0x0f

// Screen device I/O ports
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

void clear_screen(uint8_t colour);
void kprint(char* msg);
void kprint_letter(char ch);
void kprint_backspace();
void kprint_at(char* msg, int col, int row);
