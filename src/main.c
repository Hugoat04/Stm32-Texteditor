#include "headers/uart.h"
#include "headers/gpio.h"


int main(){
	
	uart2_init();

	while(1){
		if (flag == 1){
			uart2_send(uart2_buffer);
			flag = 0;
		}

	}
}

