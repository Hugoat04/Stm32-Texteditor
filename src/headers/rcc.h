#ifndef RCC
#define RCC


#define RCC_BASE 	(0x40023800UL)

#define RCC_APB1RSTR 	(*(volatile unsigned int *) (RCC_BASE + 0x20))
#define RCC_APB1ENR	(*(volatile unsigned int *) (RCC_BASE + 0x40))
#define RCC_AHB1ENR 	(*(volatile unsigned int *) (RCC_BASE + 0x30))

#endif
