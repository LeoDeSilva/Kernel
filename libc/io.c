#include "io.h"
#include "../drivers/keyboard.h"
#include "../drivers/screen.h"
#include "../libc/mem.h"
#include "../libc/string.h"

int read = 0;
char* input_buf;

void on_submit(char *key_buffer) {
    memcpy((uint8_t*)key_buffer, (uint8_t*)input_buf, strlen(key_buffer));
    input_buf[strlen(key_buffer)] = '\0';
    read = 0;
}

void readline(char *buf) {
    read = 1;
    input_buf[0] = '\0'; 

    flush_key_buffer();

    while (read) { }

    memcpy((uint8_t*)input_buf, (uint8_t*)buf, strlen(input_buf));
    buf[strlen(input_buf)] = '\0';
}
