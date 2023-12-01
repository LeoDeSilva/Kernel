#ifndef PORTS_H
#define PORTS_H

#include <stdint.h>

uint8_t p_inb(uint16_t port);
void p_outb(uint16_t port, uint8_t data);

uint16_t p_inw(uint16_t port);
void p_outw(uint16_t port, uint16_t data);


#endif
