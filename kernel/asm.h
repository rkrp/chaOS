#ifndef CHAOS_ASM_H
#define CHAOS_ASM_H

static inline void lidt(void* base, uint16_t size)
{   
    struct {
        uint16_t length;
        void*    base;
    } __attribute__((packed)) IDTR = { size, base };

    __asm__ ( "lidt %0" : : "m"(IDTR) );
}
#endif