#include "headers/spi.h"
#include "headers/rcc.h"
#include "headers/gpio.h"
#include "headers/dma.h"
#include "headers/interrupt.h"

spi_regs *SPI1 = (spi_regs *) 0x40013000;

void spi_init(void){

    SPI1->CR1 |= (0x01 << 6) | (0x01 << 2);    

}