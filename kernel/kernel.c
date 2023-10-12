#include "../drivers/screen.h"
#include "utils.h"

void main() {
    //TODO: scrolling behaviour
    clear_screen();
    for (int row = 0; row < 100; row++) {
        print_at(int_to_ascii(row), 0, row);
        for (int i = 0; i < 40000000; i++) {}
    }
}