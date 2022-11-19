#include "chaos-core.h"
#include "test.h"
#include "string.h"
#include "printk.h"

#ifdef CHAOS_TEST


void Assert_Failed(char* msg) {
    printk("Failed: %s\n", msg);
    
    for (;;) {
        __asm__("hlt");
    }
}

void Test_vsnprintk() {
    char buffer[256];
    int ret;
    ret = snprintk(buffer, sizeof(buffer), "Today is %s", "Saturday.");
    TEST_VALIDATE(ret == 18, "vsnprintk_STR");
    ret = memcmp(buffer, "Today is Saturday.\x00", 19);
    TEST_VALIDATE(ret == 0, "vsnprintk_STR");

    ret = snprintk(buffer, sizeof(buffer), "Today is %uth %s.", 19, "November");
    TEST_VALIDATE(ret == 23, "vsnprintk_INT_STR");
    ret = memcmp(buffer, "Today is 19th November.\x00", 24);
    TEST_VALIDATE(ret == 0, "vsnprintk_INT_STR");

    uint8_t* ptr = (uint8_t *) 0xcafebabe11223344;
    ret = snprintk(buffer, sizeof(buffer), "This ptr value is %p", ptr);
    ret = memcmp(buffer, "This ptr value is 0xcafebabe11223344\x00", 37);
    TEST_VALIDATE(ret == 0, "vsnprintk_PTR");

    uint32_t foo = 0x241231ab;
    ret = snprintk(buffer, sizeof(buffer), "Hex value is %p", foo);
    ret = memcmp(buffer, "Hex value is 0x241231ab\x00", 24);
    TEST_VALIDATE(ret == 0, "vsnprintk_HEX_INT");
}

void Test_uint_to_dec_str() {
    char buffer[128];
    int ret;
    printk("Testing int_to_dec_str(12345)\n");
    char* num = uint_to_dec_str(12345, buffer, sizeof(buffer));
    ret = memcmp(num, "12345\x00", 6);
    TEST_VALIDATE(ret == 0, "UINT_TO_DEC_STR");


    printk("Testing int_to_dec_str(5324224)\n");
    num = uint_to_dec_str(5324224, buffer, sizeof(buffer));
    ret = memcmp(num, "5324223\x00", 8);
    TEST_VALIDATE(ret != 0, "UINT_TO_DEC_STR");
}

void Test_int_to_hex() {
    char buffer[128];
    int ret;
    printk("Testing int_to_hex(12345)\n");
    char* num = int_to_hex(12345, buffer, sizeof(buffer));
    ret = memcmp(num, "0x3039\x00", 7);
    TEST_VALIDATE(ret == 0, "INT_TO_HEX_12345");
}

void Test_int_to_dec_str() {
    char buffer[128];
    int ret;
    printk("Testing int_to_dec_str(12345)\n");
    char* num = int_to_dec_str(12345, buffer, sizeof(buffer));
    ret = memcmp(num, "12345\x00", 6);
    TEST_VALIDATE(ret == 0, "INT_TO_DEC_STR");

    printk("Testing int_to_dec_str(5324224)\n");
    num = int_to_dec_str(-224, buffer, sizeof(buffer));
    ret = memcmp(num, "-224\x00", 5);
    TEST_VALIDATE(ret == 0, "INT_TO_DEC_STR_-224");
}

void Test_memcmp() {
    char buf1[] = {13, 5, 4, 11, 1, 9, 10, 2, 6, 0, 12, 8, 3, 7};
    char buf2[] = {13, 5, 4, 11, 1, 9, 10, 2, 6, 0, 12, 8, 3, 7};
    int ret = 0;
    printk("Testing memcmp success\n");
    ret = memcmp(buf1, buf2, sizeof(buf1));
    TEST_VALIDATE(ret == 0, "memcmp_TEST");

    buf2[12] = 0xff;
    printk("Testing memcmp success\n");
    ret = memcmp(buf1, buf2, sizeof(buf1));
    TEST_VALIDATE(ret != 0, "memcmp_TEST");
}

void test_entry() {
    printk("Starting tests..\n");
    Test_memcmp();
    Test_uint_to_dec_str();
    Test_int_to_dec_str();
    Test_int_to_hex();
    Test_vsnprintk();
    printk("All test have suceeded!\n");
}

#endif