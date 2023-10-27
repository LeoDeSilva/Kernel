#include "../drivers/screen.h"
#include "utils.h"
#include "../cpu/isr.h"
#include "../cpu/idt.h"

void main() {
    isr_install();
    __asm__ __volatile__("int $0"); 
    __asm__ __volatile__("int $3"); 
    // clear_screen(WHITE_ON_BLACK);
    // print_at("10 X = \"Hello World\"", 0, 0);
    // print_at("20 PRINT X", 0, 1);
    // print_at("30 GOTO 10", 0, 2);
    // print("\n\n");

    // for(int i = 0;; i++) {
    //     char* out_str = iota(i);
    //     print(out_str);
    //     print(" Hello World\n");
    //     for (int i = 0; i < 50000000; i++) {}
    // }
}