#include "../drivers/screen.h"
#include "low_level.h"

void main() {
    clear_screen();
    print_string("Hello World!", 0, 0, 0x0f);
    set_cursor_offset(get_screen_offset(0,0));
}