#include "mem.h"
#include <stdint.h>

void memcpy(void *source, void *dest, int nbytes) {
    int i;
    for (i = 0; i < nbytes; i++) {
        *((uint8_t*) dest + i) = *((uint8_t*) source + i);
    }
}
