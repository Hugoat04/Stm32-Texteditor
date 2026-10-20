#include "headers/sdcard.h"

buffer CMD0 = {.buffer={(char) 0b01000000, (char) 0b00000000, (char) 0b00000000, (char) 0b00000000, (char) 0b00000000, (char) 0b10010101}, .position=6};
buffer ini = {.buffer={0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF}, .position = 10};

int sd_init(void){

    spi1_init();
    spi1_send(&ini,0);

    spi1_cs_disable();
    spi1_send(&CMD0, 1);
    spi1_cs_enable();
}


void spi1_response_handle(int resp_length){
    unsigned char done = 0;
    unsigned char response;
    unsigned char offset = 0;
    unsigned short shift_helper;
    spi_rx_buffer.position = 0;

    while(!done){
        SPI1->DR = 0xFF;
        while(!(SPI1->SR & 0x01));
        response = SPI1->DR;

        if (response != 0xFF){
            for (int i = 0; i <= resp_length; i++){
                spi_rx_buffer.buffer[spi_rx_buffer.position++] = response;
                SPI1->DR = 0xFF;
                while(!(SPI1->SR & 0x01));
                response = SPI1->DR;
            }
            done = 1;
        }
    }

    for(;!(~(spi_rx_buffer.buffer[0] << offset) & (0X80));offset++);

    if (offset > 0){
        for(int i = 0; i < resp_length; i++){
            shift_helper = ((short) spi_rx_buffer.buffer[i] << 8) & (spi_rx_buffer.buffer[i]);
            spi_rx_buffer.buffer[i] = (char) ((shift_helper << offset) >> 8);
        }
    }

    spi_rx_buffer.position = resp_length;

}