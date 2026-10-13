#include "headers/spi.h"
#include "headers/rcc.h"
#include "headers/gpio.h"
#include "headers/dma.h"
#include "headers/interrupt.h"

buffer spi_rx_buffer = {0};

void spi1_init(void){

    // set up the GPIO pins for SPI1
    RCC->APB2ENR |= (0x01 << 12);
    RCC->AHB1ENR |= 0x01 | (0x01 << 22);
    GPIOA->MODER |= (0x01 << 8) | (0x02 << 10) | (0x02 << 12) | (0x02 << 14);
    GPIOA->OSPEEDR |= (0b11 << 8) | (0b11 << 10) | (0b11 << 12) | (0b11 << 14);
    GPIOA->AFRL |= (0x05 << 20) | (0x05 << 24) | (0x05 << 28);

    // DMA for SPI RX
    DMA2->S[0].CR |= (0x03 << 25) | (0x03 << 16) | (0x01 << 10) | (0x01 << 4);
    DMA2->S[0].NDTR = BUFFER_SIZE;
	DMA2->S[0].PAR = (unsigned int) &SPI1->DR;
	DMA2->S[0].M0AR = (unsigned int) spi_rx_buffer.buffer;
    NVIC_ISER1 |= (0x01 << 24);

    // DMA for SPI TX
    DMA2->S[3].CR |= (0x03 << 25) | (0x03 << 16) | (0x01 << 10) | (0x01 << 6);
    DMA2->S[3].NDTR |= BUFFER_SIZE;
	DMA2->S[3].PAR = (unsigned int) &SPI1->DR;

    // set SPI1 to SPI mode 0
    SPI1->CR1 |= (0x01 << 9) | (0x01 << 8) | (0x01 << 6) | (0x00 << 3) | (0x01 << 2);
    SPI1->CR2 |= (0x01 << 1) | 0x01;
    GPIOA->ODR |= (0x01 << 4);
    
}

// Will send a buffer and ready the DMA for the reception
void spi1_send(buffer *tx_buffer){

    DMA2->LIFCR = (0x03d << 22);
    DMA2->S[3].NDTR = tx_buffer->position;
    DMA2->S[3].M0AR = (unsigned int) tx_buffer->buffer;

    DMA2->S[0].NDTR = tx_buffer->position;
    spi_rx_buffer.position = tx_buffer->position;
    GPIOA->BSRR |= (0x01 << (4 + 16));

    DMA2->S[0].CR |= 0x01;
    DMA2->S[3].CR |= 0x01;
    
}

// SPI RX DMA ISR (also handles the TX line)
void dma2_stream0_full_isr(void){

    while(SPI1->SR & (0x01 << 7));
    DMA2->S[3].CR &= ~(0x01);
    DMA2->S[0].CR &= ~(0x01);
    DMA2->LIFCR = (0x03d << 22)| 0x03d;

    GPIOA->BSRR |= (0x01 << 4);
    
    spi_rx_buffer.EOT = 1;
    
}