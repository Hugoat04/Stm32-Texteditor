#include "headers/spi.h"
#include "headers/rcc.h"
#include "headers/gpio.h"
#include "headers/dma.h"
#include "headers/interrupt.h"

buffer spi_rx_buffer = {0};

#include "headers/uart.h"
void spi1_init(void){

    // set up the GPIO pins for SPI1
    RCC->APB2ENR |= (0x01 << 12);
    RCC->AHB1ENR |= 0x01 | (0x01 << 22);
    GPIOA->MODER |= (0x01 << 8) | (0x02 << 10) | (0x02 << 12) | (0x02 << 14);
    GPIOA->OSPEEDR |= (0b11 << 8) | (0b11 << 10) | (0b11 << 12) | (0b11 << 14);
    GPIOA->AFRL |= (0x05 << 20) | (0x05 << 24) | (0x05 << 28);

    // DMA
    DMA2->S[0].CR |= (0x03 << 25) | (0x03 << 16) | (0x01 << 10);
    DMA2->S[0].NDTR |= 100;
	DMA2->S[0].PAR = (unsigned int) &SPI1->DR;
	DMA2->S[0].M0AR = (unsigned int) spi_rx_buffer.buffer;

    // set SPI1 to SPI mode 0
    SPI1->CR1 |= (0x01 << 9) | (0x01 << 8) | (0x01 << 6) | (0x07 << 3) | (0x01 << 2);
    SPI1->CR2 |= 0x01;
    GPIOA->ODR |= (0x01 << 4);
    
}

void spi1_send(char * c){

    DMA2->S[0].CR &= ~(0x01);
    while (DMA2->S[0].CR & 1u);
    DMA2->LIFCR = 0x03d;
    DMA2->S[0].CR |= 0x01;
    
    GPIOA->BSRR |= (0x01 << (4 + 16));
    
    for(;*c != '\0';){
        SPI1->DR = *c;
        while (!(SPI1->SR & (0x02)));
        c++;
    }

    while (SPI1->SR & ( 0x01 << 7));
    GPIOA->BSRR |= (0x01 << 4);

    spi_rx_buffer.buffer[100] = 0;
    spi_rx_buffer.position = 100;

}