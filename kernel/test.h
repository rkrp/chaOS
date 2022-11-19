#ifdef CHAOS_TEST
#include "printk.h"
void test_entry(void);
void Assert_Failed();

#define TEST_VALIDATE(x, msg) \
    if (!(x)) { \
        Assert_Failed(msg); \
    } \
    printk("PASS: %s\n", msg);
#endif