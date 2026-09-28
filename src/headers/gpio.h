#ifndef GPIO
#define GPIO

#define GPIOA_BASE      0x40020000UL
#define GPIOA_MODE      (*(volatile int *) (GPIOA_BASE + 0x00))
#define GPIOA_OUT       (*(volatile int *) (GPIOA_BASE + 0x14))
#define GPIOA_AFRL      (*(volatile int *) (GPIOA_BASE + 0x20))
#define GPIOA_PUPDR     (*(volatile int *) (GPIOA_BASE + 0x0c))
#define GPIOA_OSPEEDR   (*(volatile int *) (GPIOA_BASE + 0x08))


#endif 
