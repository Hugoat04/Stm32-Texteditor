#ifndef UART_H
#define UART_H

#include "buffer.h"

extern buffer rx_buffer;
extern buffer tx_buffer;

// Registers for UART2
#define UART2_BASE      0x40004400UL

typedef struct {

	volatile unsigned int SR;
	volatile unsigned int DR;
	volatile unsigned int BRR;
	volatile unsigned int CR1;
	volatile unsigned int CR2;
	volatile unsigned int CR3;
	volatile unsigned int GTPR;

} uart_regs;

#define UART2    ((uart_regs *) (UART2_BASE))

// UART functions
void uart2_init(void);
void uart2_send(void);

#endif
