#include "headers/uart.h"
#include "headers/gpio.h"
#include "headers/spi.h"
#include "headers/ascii.h"
#include "headers/buffer.h"
#include "headers/sdcard.h"


int main(){
	
	uart2_init();
	

	while(1){

		if (ASCII_CTRL.LF == 1 || ASCII_CTRL.CR == 1){
			ASCII_CTRL.LF = 0;
			ASCII_CTRL.CR = 0;
			sd_init();
			spi_rx_buffer.buffer[0] += 48;
			uart2_send(&spi_rx_buffer);
			uart_rx_buffer.position = 0;

		}
	}
}