#ifndef INTERRUPT
#define INTERRUPT

#define NVIC_ISER1 	(*(volatile unsigned int *) (0xe000e104UL))

void _isr_enable(void);
void _isr_disable(void);

#endif
