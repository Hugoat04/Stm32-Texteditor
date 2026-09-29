#include "headers/uart.h"
#include "headers/rcc.h"
#include "headers/gpio.h"
#include "headers/dma.h"

#define UART2_BASE      0x40004400UL

#define UART2_STATUS    (*(volatile unsigned int *) (UART2_BASE + 0x00))
#define UART2_DATA      (*(volatile unsigned int *) (UART2_BASE + 0x04))
#define UART2_BRR       (*(volatile unsigned int *) (UART2_BASE + 0x08))
#define UART2_CR1       (*(volatile unsigned int *) (UART2_BASE + 0x0C))
#define UART2_CR2       (*(volatile unsigned int *) (UART2_BASE + 0x10))
#define UART2_CR3       (*(volatile unsigned int *) (UART2_BASE + 0x14))
#define UART2_GTPR      (*(volatile unsigned int *) (UART2_BASE + 0x18))

#define BUFFER 100

char uart2_rx_buffer[BUFFER] = {};
short old_pos = 0;

// initializing UART2 and the DMA
void uart2_init(void){
	// set up the GPIO pins for UART2
	RCC_APB1ENR |= (1 << 17);
	RCC_AHB1ENR |= 0x01 | (1 << 21);
	GPIOA_MODE |= (0x1 << 5) | (0x1 << 7);
	GPIOA_OSPEEDR |= (0b11 << 4) | (0b11 << 6);
	GPIOA_AFRL |= (0x07 << 8) | (0x07 << 12);
	
	// set up the DMA
	DMA_S5CR |= (0x04 << 25) | (0x02 << 16) | (0x01 << 10) | (0x01 << 8);
	DMA_S5NDTR |= 100;
	DMA_S5PAR = (unsigned int) &UART2_DATA;
	DMA_S5M0AR = (unsigned int) uart2_rx_buffer;
	DMA_S5CR |= 1;

	// set UART2
	UART2_BRR |= 0x0683;

	//UART2_CR1 |= 0b0010000000101100;
	UART2_CR1 |= (0x01 << 2) | (0x01 << 3) | (0x01 << 5) | (0x01 << 13);
	UART2_CR3 |= (0x01 << 6) | (0x01 << 7);
	
	GPIOA_MODE |= (0x01 << 10);
}

// Sends data via UART
void uart2_send(const char *str){
	
	while (!(UART2_STATUS & (1 << 7)));	
	for (;*str != '\0';){
		UART2_DATA = *str;
		while (!(UART2_STATUS & (1 << 7)));
		str++;	
	}
}

// Reads data stored by the DMA
void uart2_recieve(char * str){
	
	short current_pos = BUFFER - (short)DMA_S5NDTR;
	int pos = 0;

	if(current_pos != old_pos){
		
		if(current_pos < old_pos){
			for (short i = old_pos; i < BUFFER; i++){
				str[pos++] = uart2_rx_buffer[i];
			}

			old_pos = 0;
		}

		for (short i = old_pos; i < current_pos; i++){
			str[pos++] = uart2_rx_buffer[i];
		}	
			
		old_pos = current_pos;
	}
	str[pos]='\0';
}

void usart2_rx_isr(void){
	
	GPIOA_OUT ^= (0x01 << 5);
}

