#include "headers/uart.h"
#include "headers/gpio.h"


int main(){
	
	uart2_init();
	char arr[101];

	while(1){
		uart2_recieve(arr);	
		
		if(*arr != '\0'){
			uart2_send(arr);
		}
		for(int i = 0; i < 200000; i++);
	}
}
