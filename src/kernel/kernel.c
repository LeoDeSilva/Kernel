#include "../drivers/VGA.h"
#include "../lib/stdlib.h"

void fizzbuzz() {
    for (int i = 1; i <= 100; i++) {
        if (i % 3 == 0 && i % 5 == 0) {
            kprintf("Fizzbuzz");
        } else if (i % 3 == 0) {
            kprintf("Fizz");
        } else if (i % 5 == 0) {
            kprintf("Buzz");
        } else {
            kprintf(iota(i));
        }

        kprintf("\n");
    }

    kprintf("Done!");
}

int main() {
    VGA_set_col(0x07);
    VGA_clear_screen();

    kprintf(":Honeycomb:\n");
    kprintf("a pet project operating system\n\n");

    kprintf("$");
}
