#include "keyboard.h"
#include "../cpu/ports.h"
#include "../cpu/isr.h"
#include "../libc/string.h"
#include "../libc/function.h"
#include "../libc/io.h"
#include "screen.h"
#include "event.h"

static char key_buffer[256];
int shift_held = 0;

#define SC_MAX 57
const char *sc_name[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6", 
    "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E", 
        "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl", 
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`", 
        "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".", 
        "/", "RShift", "Keypad *", "LAlt", "Spacebar"};

const char sc_ascii[] = { '\0', '\0', '1', '2', '3', '4', '5', '6',     
    '7', '8', '9', '0', '-', '=', '\0', '\0', 'q', 'w', 'e', 'r', 't', 'y', 
        'u', 'i', 'o', 'p', '[', ']', '\0', '\0', 'a', 's', 'd', 'f', 'g', 
        'h', 'j', 'k', 'l', ';', '\'', '`', '\0', '\\', 'z', 'x', 'c', 'v', 
        'b', 'n', 'm', ',', '.', '/', '\0', '\0', '\0', ' '};

const char sc_shift_ascii[] = { '\0', '\0', '!', '@', '#', '$', '%', '^',     
    '&', '*', '(', ')', '_', '+', '\0', '\0', 'Q', 'W', 'E', 'R', 'T', 'Y', 
        'U', 'I', 'O', 'P', '{', '}', '\0', '\0', 'A', 'S', 'D', 'F', 'G', 
        'H', 'J', 'K', 'L', ':', '"', '~', '\0', '|', 'Z', 'X', 'C', 'V', 
        'B', 'N', 'M', '<', '>', '?', '\0', '\0', '\0', ' '};

void flush_key_buffer() {
    key_buffer[0] = '\0';
}

static void keyboard_callback(registers_t *regs) {
    uint8_t scancode = port_byte_in(0x60);

    if (scancode == 170) shift_held = 0;
    if (scancode > SC_MAX) return; // TODO: handle keyups
    
    Event e;
    e.type = KEY_DOWN;

    if (scancode == BACKSPACE || scancode == ENTER) {
        e.data.keydown.scancode = scancode;
        e.data.keydown.keycode = '\0';
    } else if (scancode == LSHIFT || scancode == RSHIFT) {
        shift_held = 1;
        e.data.keydown.scancode = scancode;
        e.data.keydown.keycode = '\0';
    } else {
        char keycode = shift_held ? sc_shift_ascii[(int)scancode] : sc_ascii[(int)scancode];
        e.data.keydown.scancode = scancode;
        e.data.keydown.keycode = keycode;
    }

    push_event(e);
    kprint_letter((char)0);

    UNUSED(regs);
    UNUSED(key_buffer);
}

void init_keyboard(){
    register_interrupt_handler(IRQ1, keyboard_callback);
}
