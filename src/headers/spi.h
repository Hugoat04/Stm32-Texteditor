#ifndef SPI_H
#define SPI_H


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

extern spi_regs *SPI1;

void spi_init(void);

#endif 