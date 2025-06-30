#include "chaos-core.h"
#include "limine.h"
#include "printk.h"
#include "string.h"

#include <stdarg.h>
#include "dev/serial.h"


// The Limine requests can be placed anywhere, but it is important that
// the compiler does not optimise them away, so, usually, they should
// be made volatile or equivalent.

static volatile struct limine_terminal_request terminal_request = {
    .id = LIMINE_TERMINAL_REQUEST,
    .revision = 0
};

inline void puts_terminal(char *str, size_t len) {
    struct limine_terminal *terminal = terminal_request.response->terminals[0];
    terminal_request.response->write(terminal, str, len);
}

inline void puts_serial(char *str, size_t len) {

    for(size_t i = 0; i < len; i++) {
        // Wait until the transmit buffer is empty
        while((inb(COM1_LINE_STATUS) & 0x20) == 0);
        outb(COM1_TRANSMIT_BUFFER, str[i]);
    }
}

inline void puts(char *str, size_t len) {
    puts_terminal(str, len);
    puts_serial(str, len);
}

size_t printk(char *format, ...) {
    char buffer[256];
    size_t ret = 0;
    va_list arg;
    va_start(arg, format);
    ret = vsnprintk(buffer, sizeof(buffer), format, arg);
    puts(buffer, ret);
    va_end(arg);
    return ret;
}

char* int_to_dec_str(int32_t num, char* ret, size_t len) {
    bool negative = num < 0;
    if(negative)
        num *= -1;
    char* str = uint_to_dec_str((uint32_t) num, ret, len);
    if(negative) {
        *(str - 1) = '-';
        return str - 1;
    } else {
        return str;
    }
}

char* uint_to_dec_str(uint32_t num, char* ret, size_t len) {
    int i = len - 1;
    ret[i] = 0;
    while(i--) {
        ret[i] = 0x30 + (num % 10);
        num = num / 10;
        if(num == 0) {
            // We have succeeded
            return &ret[i];
        }
    }
    // If we reach here, it is truncated
    return 0;
}

char* int_to_hex(uint64_t num, char* ret, size_t len) {
    int i = len - 1;
    ret[i] = 0;
    while(i--) {
        ret[i] = get_hex_digit(num & 0xf);
        num = num >> 4;
        if(num == 0) {
            // Add 0x before returning
            ret[i-1] = 'x';
            ret[i-2] = '0';

            return &ret[i-2];
        }
    }
    // If we reach here, it is truncated
    return 0;
}

/** 
 * num must be [0, 15]
*/
char get_hex_digit(uint8_t num) {
    if(num <=9) {
        return 0x30 + num;
    } 
    
    switch (num) {
        case 10: return 'a';
        case 11: return 'b';
        case 12: return 'c';
        case 13: return 'd';
        case 14: return 'e';
        case 15: return 'f';
        default: return 'Y';
    }
}

size_t snprintk(char *str, size_t size, char * format, ...) {
    size_t ret = 0;
    va_list arg;
    va_start(arg, format);
    ret = vsnprintk(str, size, format, arg);
    va_end(arg);
    return ret;
}

size_t vsnprintk(char *str, size_t size, char * format, va_list arg) {
    uint32_t out_index = 0;
    char num_buffer[32]; // To parse and temporarily store numbers
    char* converted;
    
    for(char* c = format; *c != '\0' ; c++) {
        if(out_index >= size) {
            goto ret;
        }
        
        /* Proceed until we get to % char */
        if(*c != '%') {
            str[out_index++] = *c;
            continue;
        }

        
        c++; // To get to the modifier

        switch (*c) {
            case 'u':
                uint32_t u_val = va_arg(arg, uint32_t);
                converted = uint_to_dec_str(u_val, num_buffer, sizeof(num_buffer));
                break;
            case 'd':
                int32_t d_val = va_arg(arg, int32_t);
                converted = int_to_dec_str(d_val, num_buffer, sizeof(num_buffer));
                break;
            case 'p':
                void* addr = va_arg(arg, void*);
                converted = int_to_hex((uint64_t) addr, num_buffer, sizeof(num_buffer));
                break;
            case 's':
                converted = va_arg(arg, char *);
                break;
            default:
                converted = "";
        }

        memcpy(str + out_index, converted, strlen(converted));
        out_index += strlen(converted);
    }

ret:
    str[out_index] = '\0';
    return out_index;
}