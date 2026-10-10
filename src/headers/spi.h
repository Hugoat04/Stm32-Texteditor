#ifndef SPI_H
#define SPI_H

#include "buffer.h"

extern buffer spi_rx_buffer;

#define SPI1_BASE      0x40013000UL

typedef struct {

    volatile unsigned int CR1;
    volatile unsigned int CR2;
    volatile unsigned int SR;
    volatile unsigned int DR;
    volatile unsigned int CRCPR;
    volatile unsigned int RXCRCR;
    volatile unsigned int TXCRCR;
    volatile unsigned int I2SCFGR;
    volatile unsigned int I2SPR;
    
}spi_regs;

#define SPI1    ((spi_regs *) (SPI1_BASE))

void spi1_init(void);
void spi1_send(char *);
void spi1_reveive(char *);

#endif 