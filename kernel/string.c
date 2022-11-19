#include <stddef.h>

size_t strlen(char* str) {
    char* ptr = str;
    while(*ptr++);
    return ptr - str - 1;
}

void strcat(char* dst, char* src) {
    size_t dstlen = strlen(dst);
    for(size_t i = 0 ; i < strlen(src) ; i++) {
        dst[dstlen++] = src[i];
    }
    dst[dstlen] = '\0';
}

void memcpy(char* dst, char* src, size_t len) {
    for(size_t i = 0; i < len ; i++)
        dst[i] = src[i];
}

int memcmp(const void* a, const void* b, size_t len) {
    char *s1 = (char *) a;
    char *s2 = (char *) b;
    for(size_t i = 0 ; i < len ; i++) {
        if(s1[i] != s2[i])
            return s1[i] - s2[i];
    }
    return 0;
}