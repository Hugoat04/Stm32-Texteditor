#include "headers/uart.h"
#include "headers/rcc.h"
#include "headers/gpio.h"
#include "headers/dma.h"
#include "headers/interrupt.h"


#define UART2_BASE      0x40004400UL

#define UART2_STATUS    (*(volatile unsigned int *) (UART2_BASE + 0x00))
#define UART2_DATA      (*(volatile unsigned int *) (UART2_BASE + 0x04))
#define UART2_BRR       (*(volatile unsigned int *) (UART2_BASE + 0x08))
#define UART2_CR1       (*(volatile unsigned int *) (UART2_BASE + 0x0C))
#define UART2_CR2       (*(volatile unsigned int *) (UART2_BASE + 0x10))
#define UART2_CR3       (*(volatile unsigned int *) (UART2_BASE + 0x14))
#define UART2_GTPR      (*(volatile unsigned int *) (UART2_BASE + 0x18))


volatile char uart2_buffer[BUFFER_SIZE] = {};
volatile short pos = 0;
volatile int flag = 0;

// initializing UART2 and the DMA
void uart2_init(void){
	// set up the GPIO pins for UART2
	RCC_APB1ENR |= (1 << 17);
	RCC_AHB1ENR |= 0x01;
	GPIOA_MODE |= (0x1 << 5) | (0x1 << 7);
	GPIOA_OSPEEDR |= (0b11 << 4) | (0b11 << 6);
	GPIOA_AFRL |= (0x07 << 8) | (0x07 << 12);
	
	// set UART2
	UART2_BRR |= 0x0683;
	UART2_CR1 |= (0x01 << 2) | (0x01 << 3) | (0x01 << 5) | (0x01 << 13);
	NVIC_ISER1 |= (0x01 << 6);

	GPIOA_MODE |= (0x01 << 10);
}

// Sends data via UART
void uart2_send(volatile char *str){
	
	while (!(UART2_STATUS & (1 << 7)));	
	for (;*str != '\0';){
		UART2_DATA = *str;
		while (!(UART2_STATUS & (1 << 7)));
		str++;	
	}

}

// UART RX interrupt will handle incoming dat// UART RX interrupt will handle incoming data
void usart2_rx_isr(void){
	char c = UART2_DATA;	
	if (c == '\n' || c == '\r'){
		flag = 1;
		uart2_buffer[pos++] = c;
		uart2_buffer[pos] = 0;
		pos = 0;
		GPIOA_OUT ^= (0x01 << 5);
	} else {
		uart2_buffer[pos++] = c;
		uart2_buffer[pos] == 1;
	}
}

