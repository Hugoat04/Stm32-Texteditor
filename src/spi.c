#include "headers/spi.h"
#include "headers/rcc.h"
#include "headers/gpio.h"
#include "headers/dma.h"
#include "headers/interrupt.h"

buffer spi_rx_buffer = {0};

void spi1_dma_send(buffer *tx_buffer, short resp_length);
void spi1_normal_send(buffer *tx_buffer, short resp_length);
void (*spi1_send)(buffer *, short);

void spi1_init(void){

    // set up the GPIO pins for SPI1
    RCC->APB2ENR |= (0x01 << 12);
    RCC->AHB1ENR |= 0x01;
    GPIOA->MODER |= (0x01 << 8) | (0x02 << 10) | (0x02 << 12) | (0x02 << 14);
    GPIOA->OSPEEDR |= (0b11 << 8) | (0b11 << 10) | (0b11 << 12) | (0b11 << 14);
    GPIOA->AFRL |= (0x05 << 20) | (0x05 << 24) | (0x05 << 28);

    // set SPI1 to SPI mode 0
    SPI1->CR1 |= (0x01 << 9) | (0x01 << 8) | (0x01 << 6) | (0x07 << 3) | (0x01 << 2);
    SPI1->CR2 |= (0x01 << 6);
    GPIOA->ODR |= (0x01 << 4);
    
    spi1_send = &spi1_normal_send;

}

// CS control (inverted!!)
void spi1_cs_enable(void){
    GPIOA->BSRR |= (0x01 << 4);
}

void spi1_cs_disable(void){
    GPIOA->BSRR |= (0x01 << (4 + 16));
}

/*
 *
 * SPI normal
 *
*/

void spi1_normal_send(buffer *tx_buffer, short resp_length){
    
    spi_rx_buffer.position = 0;

    for(int i = 0; i < tx_buffer->position; i++){
    
        while(!(SPI1->SR & (0x01 << 1)));
        SPI1->DR = tx_buffer->buffer[i];

        while(!(SPI1->SR & 0x01));
        spi_rx_buffer.buffer[spi_rx_buffer.position++] = SPI1->DR;
    }
    
    if(resp_length > 0){
        spi1_response_handle(resp_length);
    }
}

/*
 *
 * SPI through DMA
 *
*/

void spi1_dma_init(void){

    // Enable DMA2 RCC
    RCC->AHB1ENR |= (0x01 << 22);

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

    // Enable DMA for SPI
    SPI1->CR2 &= ~(0x01 << 6);
    SPI1->CR2 |= (0x01 << 1) | 0x01;

    spi1_send = &spi1_dma_send;

}

void spi1_dma_deinit(void){

    SPI1->CR2 &= ~((0x01 << 1) | 0x01);
    SPI1->CR2 |= (0x01 << 6);
    RCC->AHB1ENR &= ~(0x01 << 22);
    NVIC_ISER1 &= ~(0x01 << 24);
    spi1_send = &spi1_normal_send;

}

// Will send a buffer and ready the DMA for the reception
void spi1_dma_send(buffer *tx_buffer, short resp_length){

    DMA2->LIFCR = (0x03d << 22);
    DMA2->S[3].NDTR = tx_buffer->position;
    DMA2->S[3].M0AR = (unsigned int) tx_buffer->buffer;

    DMA2->S[0].NDTR = tx_buffer->position + resp_length;
    spi_rx_buffer.position = tx_buffer->position + resp_length;

    DMA2->S[0].CR |= 0x01;
    DMA2->S[3].CR |= 0x01;
    
}

// SPI RX DMA ISR (also handles the TX line)
void dma2_stream0_full_isr(void){

    while(SPI1->SR & (0x01 << 7));
    DMA2->S[3].CR &= ~(0x01);
    DMA2->S[0].CR &= ~(0x01);
    DMA2->LIFCR = (0x03d << 22)| 0x03d;
    
    spi_rx_buffer.EOT = 1;
    
}