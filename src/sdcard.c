#include "headers/sdcard.h"


int sd_init(void){

    spi1_init();
//    spi1_send(CMD0, CMD0_RESPONSE);

}


void spi1_response_handle(int resp_length){
    char done = 0;

    while(!done){
        SPI1->DR = 0xFF;
        while(!(SPI1->SR & 0x01));
        
    }

}