#ifndef IDT_H
#define IDT_H

#include <stdint.h>
#include "type.h"

#define KERNEL_CS 0x08

typedef struct {
    uint16_t low_offset;
    uint16_t selector;
    uint8_t always0;

    // Bit 7: "Interrupt is present"
    // Bits 6-5: Privilege level of caller (0=kernel..3=user)
    // Bit 4: Set to 0 for interrupt gates
    // Bits 3-0: bits 1110 = decimal 14 = "32 bit interrupt gate" */
    uint8_t flags;
    uint16_t high_offset;
} __attribute__((packed)) idt_gate_t ;

// asm instruct lidt reads idt_register_t reference to idt rather than the idt itself
typedef struct {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed)) idt_register_t;

#define IDT_ENTRIES 256
extern idt_gate_t idt[IDT_ENTRIES];
extern idt_register_t idt_reg;

void set_idt_gate(int n, uint32_t handler);
void set_idt();

#endif