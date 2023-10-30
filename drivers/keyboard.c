#include "keyboard.h"
#include "../cpu/ports.h"
#include "../cpu/isr.h"
#include "../libc/string.h"
#include "../libc/function.h"
#include "../libc/io.h"
#include "screen.h"
#include "event.h"

static char key_buffer[256];

#define SC_MAX 57
const char *sc_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
    "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E", 
        "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl", 
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", 
        "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", 
        "/", "RShift", "Keypad *", "LAlt", "Spacebar"};

const char sc_ascii[] = { '?', '?', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V', 
        'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

void flush_key_buffer() {
    key_buffer[0] = '\0';
}

static void keyboard_callback(registers_t *regs) {
    uint8_t scancode = port_byte_in(0x60);
    if (scancode > SC_MAX) return; // TODO: handle keyups
    
    Event e;
    e.type = KEY_DOWN;

    if (scancode == BACKSPACE || scancode == ENTER) {
        e.data.keydown.scancode = scancode;
        e.data.keydown.keycode = '?';
    } else {
        char keycode = sc_ascii[(int)scancode];
        e.data.keydown.scancode = scancode;
        e.data.keydown.keycode = keycode;
    }

    push_event(e);

    UNUSED(regs);
    UNUSED(key_buffer);
}

// static void buffer_keyboard_callback(registers_t *regs) {
//     uint8_t scancode = port_byte_in(0x60); // PIC leaves the scancode in port 0x60
//     if (scancode > SC_MAX) return;
//
//     if (scancode == BACKSPACE) {
//         if (strlen(key_buffer) > 0) {
//             key_buffer[strlen(key_buffer)-1] = '\0';
//             kprint_backspace();
//         }
//     } else if (scancode == ENTER) {
//         kprint("\n");
//         on_submit(key_buffer);
//     } else {
//         char letter = sc_ascii[(int)scancode];
//         if (letter != '?') {
//             append(key_buffer, letter);
//             kprint_letter(letter);
//         }
//     }
//
//     UNUSED(regs);
// }

void init_keyboard(){
    register_interrupt_handler(IRQ1, keyboard_callback);
}
