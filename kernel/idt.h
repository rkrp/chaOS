#ifndef CHAOS_IDT_H
#define CHAOS_IDT_H

#include "chaos-core.h"


void load_idt(void);
void idt_handler(void *);

typedef struct __attribute__((packed)) {
   uint16_t offset_1;        // offset bits 0..15
   uint16_t selector;        // a code segment selector in GDT or LDT
   uint8_t  ist;             // bits 0..2 holds Interrupt Stack Table offset, rest of bits zero.
   uint8_t  type_attributes; // gate type, dpl, and p fields
   uint16_t offset_2;        // offset bits 16..31
   uint32_t offset_3;        // offset bits 32..63
   uint32_t zero;            // reserved
} ids_t;

typedef struct __attribute__((packed)) {
   uint16_t size;
   void* offset;
} idtr_t;

#endif