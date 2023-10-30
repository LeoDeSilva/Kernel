#include "string.h"

int strlen(char s[]) {
    int i = 0;
    while (s[i])
        i++;
    return i;
}

// returns <0 if a<b, 0 if a==b, and >0 if a>b
int strcmp(char a[], char b[]) {
    int i;
    for (i = 0; a[i] == b[i]; i++) {
        if (a[i] == '\0') return 0;
    }

    return a[i] - b[i];
}

void append(char s[], char ch) {
    int len = strlen(s);
    s[len] = ch;
    s[len+1] = '\0';
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
