#ifndef DMA
#define DMA

// DMA1

#define DMA1_BASE	(0x40026000UL)

#define DMA_LISR	(*(volatile unsigned int *) (DMA1_BASE + 0x00)
#define DMA_HISR	(*(volatile unsigned int *) (DMA1_BASE + 0x04)
#define DMA_LIFCR	(*(volatile unsigned int *) (DMA1_BASE + 0x08)
#define DMA_HIFCR	(*(volatile unsigned int *) (DMA1_BASE + 0x0c)

#define DMA_S5CR	(*(volatile unsigned int *) (DMA1_BASE + 0x010 + (0x18 * 5)))
#define DMA_S6CR	(*(volatile unsigned int *) (DMA1_BASE + 0x010 + (0x18 * 6)))

#define DMA_S5NDTR	(*(volatile unsigned int *) (DMA1_BASE + 0x014 + (0x18 * 5)))
#define DMA_S6NDTR	(*(volatile unsigned int *) (DMA1_BASE + 0x014 + (0x18 * 6)))

#define DMA_S5PAR	(*(volatile unsigned int *) (DMA1_BASE + 0x018 + (0x18 * 5)))
#define DMA_S6PAR	(*(volatile unsigned int *) (DMA1_BASE + 0x018 + (0x18 * 6)))

#define DMA_S5M0AR	(*(volatile unsigned int *) (DMA1_BASE + 0x01c + (0x18 * 5)))
#define DMA_S6M0AR	(*(volatile unsigned int *) (DMA1_BASE + 0x01c + (0x18 * 6)))

#define DMA_S5FCR	(*(volatile unsigned int *) (DMA1_BASE + 0x024 + (0x18 * 5)))
#define DMA_S6FCR	(*(volatile unsigned int *) (DMA1_BASE + 0x024 + (0x18 * 6)))





#endif
