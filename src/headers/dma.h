#ifndef DMA_H
#define DMA_H

#define DMA1_BASE	(0x40026000UL)
#define DMA2_BASE	(0x40026400UL)

typedef struct {
    volatile unsigned int CR;
    volatile unsigned int NDTR;
    volatile unsigned int PAR;
    volatile unsigned int M0AR;
    volatile unsigned int M1AR;
    volatile unsigned int FCR;

} dma_stream_regs;

typedef struct {
    volatile unsigned int LISR;
    volatile unsigned int HISR;
    volatile unsigned int LIFCR;
    volatile unsigned int HIFCR;
    
    volatile dma_stream_regs S[8];

} dma_regs;

#define DMA1    ((dma_regs *) (DMA1_BASE))
#define DMA2    ((dma_regs *) (DMA2_BASE))

#endif
