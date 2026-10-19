#include "headers/uart.h"
#include "headers/gpio.h"
#include "headers/spi.h"
#include "headers/ascii.h"
#include "headers/buffer.h"


int main(){
	
	uart2_init();
	spi1_init();
//	spi1_dma_init();
	while(1){

		if (ASCII_CTRL.LF == 1 || ASCII_CTRL.CR == 1){
			ASCII_CTRL.LF = 0;
			ASCII_CTRL.CR = 0;
			spi_rx_buffer = empty_buffer;
			spi1_send(&uart_rx_buffer,0);
//			while (spi_rx_buffer.EOT == 0);
			spi_rx_buffer.EOT = 0;
			uart2_send(&spi_rx_buffer);
			uart_rx_buffer.position = 0;

		}
	}
}