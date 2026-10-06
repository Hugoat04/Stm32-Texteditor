#include "headers/spi.h"
#include "headers/rcc.h"
#include "headers/gpio.h"
#include "headers/dma.h"
#include "headers/interrupt.h"



void spi1_init(void){

    // set up the GPIO pins for SPI1
    RCC->APB2ENR |= (0x01 << 12);
    RCC->AHB1ENR |= (0x01 << 0);// | (0x01 << 21);
    GPIOA->MODER |= (0x01 << 8) | (0x02 << 10) | (0x02 << 12) | (0x02 << 14);
    GPIOA->OSPEEDR |= /*(0b11 << 8) |*/ (0b11 << 10) | (0b11 << 12) | (0b11 << 14);
    GPIOA->AFRL |= (0x05 << 16) | (0x05 << 20) | (0x05 << 24) | (0x05 << 28);

    // set SPI1 to SPI mode 0
    SPI1->CR1 |= (0x01 << 9) | (0x01 << 8) | (0x01 << 6) | (0x01 << 2);
    GPIOA->ODR |= (0x01 << 4);

}

void spi1_send(char * c){
    
    GPIOA->BSRR |= (0x01 << (4 + 16));
    
    for(;*c != '\0';){
        SPI1->DR = *c;
        while (!(SPI1->SR & (0x02)));
        c++;
    }

    while (SPI1->SR & ( 0x01 << 7));

    GPIOA->BSRR |= (0x01 << 4);

}

void spi1_reveive(char *){

    
}