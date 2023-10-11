#define VIDEO_ADDRESS 0xb8000
#define MAX_ROWS 25
#define MAX_COLS 80

#define WHITE_ON_BLACK 0x0f

// Screen device I/O ports
#define REG_SCREEN_CTRL 0x3D4
#define REG_SCREEN_DATA 0x3D5

int get_screen_offset(int row, int col);
void print_char(char ch, int offset, char attr_byte);
void print_string(char* str, int row, int col, char attr_byte);
void clear_screen();