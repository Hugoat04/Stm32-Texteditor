#ifndef RCC_H
#define RCC_H


#define RCC_BASE 	(0x40023800UL)

typedef struct {
    volatile unsigned int CR;
    volatile unsigned int PLLCFGR;
    volatile unsigned int CFGR;
    volatile unsigned int CIR;
    volatile unsigned int AHB1RSTR;
    volatile unsigned int AHB2RSTR;
    volatile unsigned int AHB3RSTR;
    volatile unsigned int RESERVED0;
    volatile unsigned int APB1RSTR;
    volatile unsigned int APB2RSTR;
    volatile unsigned int RESERVED1[2];
    volatile unsigned int AHB1ENR;
    volatile unsigned int AHB2ENR;
    volatile unsigned int AHB3ENR;
    volatile unsigned int RESERVED2;
    volatile unsigned int APB1ENR;
    volatile unsigned int APB2ENR;
    
} rcc_regs;

#define RCC    ((rcc_regs *) (RCC_BASE))

#endif
