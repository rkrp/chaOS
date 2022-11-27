#include "idt.h"
#include "printk.h"

static ids_t *idt = (ids_t *)0x1000;
//static idtr_t idtr;

void setInterruptDescriptor(ids_t *ids, 
                            uint64_t address, 
                            uint8_t ist,
                            uint8_t attrs) {
    ids->offset_1 = address & 0xffff;
    ids->offset_2 = (address >> 16) & 0xffff;
    ids->offset_3 = (address >> 32) & 0xffffffff;
    ids->zero = 0;
    ids->ist = ist;
    ids->selector = 5 * 8; // 5 is the index of 64-bit code segment set by limine
    ids->type_attributes = attrs;
}

void init_all_idt(void* handler_addr) {
    for(int i = 0 ; i < 256 ; i++) {
        setInterruptDescriptor(idt + i, (uint64_t) handler_addr, 0, 0x8E);
    }
}

void load_idt() {
    printk("IDTR size: %d\n", sizeof(idtr_t));

    init_all_idt(&idt_handler);
    lidt(idt, (256 * sizeof(ids_t)) - 1);

}


__attribute__((interrupt)) void idt_handler(void* frame) {
    (void) frame;
    printk("PANIC!\n");
    __asm__ volatile ("1: jmp 1b");
}
