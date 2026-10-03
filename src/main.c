#include "headers/uart.h"
#include "headers/gpio.h"


int main(){
	
	uart2_init();

	while(1){
		if (ASCII_CTRL.LF == 1 || ASCII_CTRL.CR == 1){
			ASCII_CTRL.LF = 0;
			ASCII_CTRL.CR = 0;
			tx_buffer = rx_buffer;
			uart2_send();
			rx_buffer.position = 0;
		}

	}
}

