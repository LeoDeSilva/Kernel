#include "../drivers/screen.h"

void main() {
    clear_screen();
    print_string("Hello World!", 12, 35, 0x0f);
}