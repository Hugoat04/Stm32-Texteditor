#include "headers/uart.h"
#include "headers/rcc.h"
#include "headers/gpio.h"
#include "headers/dma.h"
#include "headers/interrupt.h"
#include "headers/ascii.h"


#define UART2_BASE      0x40004400UL

#define UART2_STATUS    (*(volatile unsigned int *) (UART2_BASE + 0x00))
#define UART2_DATA      (*(volatile unsigned int *) (UART2_BASE + 0x04))
#define UART2_BRR       (*(volatile unsigned int *) (UART2_BASE + 0x08))
#define UART2_CR1       (*(volatile unsigned int *) (UART2_BASE + 0x0C))
#define UART2_CR2       (*(volatile unsigned int *) (UART2_BASE + 0x10))
#define UART2_CR3       (*(volatile unsigned int *) (UART2_BASE + 0x14))
#define UART2_GTPR      (*(volatile unsigned int *) (UART2_BASE + 0x18))

uart_regs *UART2 = (uart_regs *) UART2_BASE;

uart_buffer rx_buffer = {0};
uart_buffer tx_buffer = {0};
uart_buffer  empty_buffer = {0};

ascii_ctrl ASCII_CTRL = {0};


// initializing UART2 and the DMA
void uart2_init(void){
	// set up the GPIO pins for UART2
	RCC_APB1ENR |= (1 << 17);
	RCC_AHB1ENR |= 0x01 | (0x01 << 21);
	GPIOA_MODE |= (0x1 << 5) | (0x1 << 7);
	GPIOA_OSPEEDR |= (0b11 << 4) | (0b11 << 6);
	GPIOA_AFRL |= (0x07 << 8) | (0x07 << 12);
	
	// set DMA for TX
	DMA_S6CR |= (0x04 << 25) | (0x02 << 16) | (0x01 << 10) | (0x01 << 6) |(0x01 << 4); // | (0x01 << 3);
	DMA_S6NDTR |= BUFFER_SIZE;
	DMA_S6PAR = (unsigned int) &UART2_DATA;
	DMA_S6M0AR = (unsigned int) tx_buffer.buffer;
	NVIC_ISER0 |= (0x01 << 17);
	

	// set UART2
	UART2_BRR |= 0x08B;
	UART2_CR1 |= (0x01 << 2) | (0x01 << 3) | (0x01 << 5) | (0x01 << 13);
	NVIC_ISER1 |= (0x01 << 6);

	GPIOA_MODE |= (0x01 << 10);
}

// Sends data via UART
void uart2_send(){

	UART2_STATUS &= ~(0x01 << 6);
	DMA_S6NDTR |= tx_buffer.position;
	UART2_CR3 |= (0x01 << 7);
	DMA_S6CR |= 0x01;

}

// DMA interrupt handler for when the DMA transfer is complete
void dma1_stream6_full(void){
	GPIOA_OUT ^= (1 << 5);
	while(!(UART2_STATUS & (0x01 << 6)));

	UART2_CR3 &= ~(0x01 << 7);
	DMA_S6CR &= ~(0x01);
	DMA_HIFCR |= (0x01 << 21);
	

}

// UART RX interrupt will handle incoming dat// UART RX interrupt will handle incoming data
void usart2_rx_isr(void){
	char c = UART2_DATA;	

	switch(c){
	   	case 0x0:		ASCII_CTRL.NUL = 1;
                    	break;

		case 0x01:		ASCII_CTRL.SOH = 1;
						break;

		case 0x02:	  	ASCII_CTRL.STX = 1;
            	        break;
				
		case 0x03:  	ASCII_CTRL.ETX = 1;
            	    	break;

		case 0x04:      ASCII_CTRL.EOT = 1;
                        break;

		case 0x05:      ASCII_CTRL.ENQ = 1;
                    	break;

		case 0x06:      ASCII_CTRL.ACK = 1;
                        break;

		case 0x07:      ASCII_CTRL.BEL = 1;
                        break;

		case 0x08:      ASCII_CTRL.BS = 1;
						if ( rx_buffer.position > 0) 
							rx_buffer.buffer[--(rx_buffer.position)] = 0;
                        break;

		case 0x09:      ASCII_CTRL.HT = 1;
						rx_buffer.buffer[rx_buffer.position++] = c;
						rx_buffer.buffer[rx_buffer.position] = 0;
                        break;

		case 0x0a:      ASCII_CTRL.LF = 1;
		                rx_buffer.buffer[rx_buffer.position++] = c;
        		        rx_buffer.buffer[rx_buffer.position] = 0;
                        break;

		case 0x0b:      ASCII_CTRL.VT = 1;
                        break;

		case 0x0c:      ASCII_CTRL.FF = 1;
                        break;

		case 0x0d:    	ASCII_CTRL.CR = 1;
						rx_buffer.buffer[rx_buffer.position++] = c;
                        rx_buffer.buffer[rx_buffer.position] = 0;
                        break;

		case 0x0e:      ASCII_CTRL.SO = 1;   
		                break;

		case 0x0f:      ASCII_CTRL.SI = 1;
                        break;

		case 0x10:      ASCII_CTRL.DLE = 1;
                        break;

		case 0x11:      ASCII_CTRL.DC1 = 1;
                        break;

		case 0x12:      ASCII_CTRL.DC2 = 1;
						break;

        case 0x13:      ASCII_CTRL.DC3 = 1;
                        break;

        case 0x14:      ASCII_CTRL.DC4 = 1;
                        break;

        case 0x15:      ASCII_CTRL.NAK = 1;
                        break;

        case 0x16:      ASCII_CTRL.SYN = 1;
                        break;

        case 0x17:      ASCII_CTRL.ETB = 1;
                        break;

        case 0x18:      ASCII_CTRL.CAN = 1;
                        break;

        case 0x19:      ASCII_CTRL.EM = 1;
                        break;

        case 0x1a:      ASCII_CTRL.SUB = 1;
                        break;

        case 0x1b:      ASCII_CTRL.ESC = 1;
                        break;

        case 0x1c:      ASCII_CTRL.FS = 1;
                        break;

		case 0x1d:      ASCII_CTRL.GS = 1;
                        break;

        case 0x1e:      ASCII_CTRL.RS = 1;
                        break;

        case 0x1f:      ASCII_CTRL.US = 1;
                        break;

		case 0x7F:      if (rx_buffer.position > 0)
							rx_buffer.buffer[--(rx_buffer.position)] = 0;
                        break;

		default:		rx_buffer.buffer[rx_buffer.position++] = c;
        		        rx_buffer.buffer[rx_buffer.position] = 0;

	}

	if (rx_buffer.position == BUFFER_SIZE)
		rx_buffer.FULL = 1;

}
