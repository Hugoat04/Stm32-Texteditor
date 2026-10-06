#include "headers/uart.h"
#include "headers/gpio.h"
#include "headers/spi.h"
#include "headers/ascii.h"


int main(){
	
	char c[] = "HELLO!";

	uart2_init();
	spi1_init();

	while(1){
		if (ASCII_CTRL.LF == 1 || ASCII_CTRL.CR == 1){
			ASCII_CTRL.LF = 0;
			ASCII_CTRL.CR = 0;
			tx_buffer = rx_buffer;
			uart2_send();
			rx_buffer.position = 0;
		}
		
		spi1_send(c);

		for (int i = 0; i < 1000000; i++);

	}
}

