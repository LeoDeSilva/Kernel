#include "../drivers/screen.h"

void memcpy(char *source, char *dest, int nbytes) {
    int i;
    for (i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);
    }
}

char* iota(int n) {
    int i = 0;
    char* str = 0;

    if (n == 0) {
        str[0] = '0';
        str[1] = '\0';
        return str;
    }

    while (n > 0) {
        str[i++] = n % 10 + '0';
        n /= 10;
    }

    int length = i;
    for (i = 0; i < length/2; i++) {
        char c = str[i];
        str[i] = str[length-i-1]; 
        str[length-i-1] = c;
    }

    str[length] = '\0';
    return str;
}