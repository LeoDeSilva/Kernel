#include "../drivers/screen.h"
#include "utils.h"

void main() {
    //TODO: scrolling behaviour
    clear_screen();
    // for (int row = 0; row < MAX_ROWS; row++) {
    //     print_at(int_to_ascii(row), 0, row);
    // }

    print_at("10 X = \"Hello World\"", 0, 0);
    print_at("20 PRINT X", 0, 1);
    print_at("30 GOTO 10", 0, 2);
    print("\n\n");

    for(int i = 0;; i++) {
        char* out_str = iota(i);
        print(out_str);
        print(" Hello World\n");
        for (int i = 0; i < 50000000; i++) {}
    }
}