#ifndef GPIO
#define GPIO

#define GPIOA_BASE      0x40020000UL

typedef struct {
    volatile unsigned int MODER;
    volatile unsigned int OTYPER;
    volatile unsigned int OSPEEDR;
    volatile unsigned int PUPDR;
    volatile unsigned int IDR;
    volatile unsigned int ODR;
    volatile unsigned int BSRR;
    volatile unsigned int LCKR;
    volatile unsigned int AFRL;
    volatile unsigned int AFRH;

} gpio_regs;

#define GPIOA    ((gpio_regs *) (GPIOA_BASE))

#endif 
