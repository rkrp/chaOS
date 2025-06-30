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

static inline void outb(uint16_t port, uint8_t value)
{
    __asm__ volatile ("outb %0, %1" : : "a"(value), "Nd"(port));
}

static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    __asm__ volatile ("inb %1, %0" : "=a"(ret) : "Nd"(port));
    return ret;
}
#endif