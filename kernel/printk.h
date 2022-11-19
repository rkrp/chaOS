#include "chaos-core.h"
#include <stdarg.h>

void puts(char *str, size_t len);
size_t snprintk(char *str, size_t size, char * format, ...);
size_t vsnprintk(char *str, size_t size, char * format, va_list arg);
size_t printk(char *format, ...);
char* uint_to_dec_str(uint32_t num, char* ret, size_t len);
char* int_to_dec_str(int32_t num, char* ret, size_t len);
char* int_to_hex(uint64_t num, char* ret, size_t len);
char get_hex_digit(uint8_t num);