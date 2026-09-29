extern int main(void);
extern void usart2_rx_isr(void);
extern unsigned int _estack, _etext, _sdata, _edata, _sbss, _ebss;

// initializes C runtime environment and calls main
void reset_handler(void) {
	
	unsigned int *init_values_ptr = &_etext;
        unsigned int *data_ptr = &_sdata;

	// Copies initilized variables from flash to RAM
        if (init_values_ptr != data_ptr) {
                for (; data_ptr < &_edata;) {
                        *data_ptr++ = *init_values_ptr++;
                }
        }

	// sets all variables in the bss section to zero
	for (unsigned int *i = &_sbss; i <= &_ebss;){
		*i++ = 0;
	}
	
	// calls main
	main();

	while(1);

}

// Non-Maskable Interrupt empty for now
void NMI(void) {

}

// Hard Fault Handler empty for now
void hard_fault(void) {

}

void usart2_handler(void){
	usart2_rx_isr();
}

typedef void (*isr_t)(void);

// Vector Table
__attribute((used, section(".vectors")))
static const isr_t vector_table[120]={

	(isr_t)&_estack,
	reset_handler,
	NMI,
	hard_fault,
	0,	// MemManage
        0,	// BusFault
        0,	// UsageFault
        0,	
        0,
	0,
	0,
        0,	// SVCall
        0,	// DebugMonitor
        0,	
        0,	// PendSV
        0,	// Systick
        0,	// WWDG
        0,	// PVD
        0,	// TAMP_STAMP
        0,	// RTC_WKUP
        0,	// FLASH
	0,      // RCC
        0,      // EXTI0
        0,      // EXTI1
        0,      // EXTI2
        0,	// EXTI3
        0,      // EXTI4
        0,      // DMA1_Stream0
        0,      // DMA1_Stream1
        0,      // DMA1_Stream2      
        0,      // DMA1_Stream3      
        0,      // DMA1_Stream4    
        0,      // DMA1_Stream5      
        0,      // DMA1_Stream6      
        0,      // ADC
        0,      // CAN1_TX
        0,      // CAN1_RX0
        0,      // CAN1_RX1
        0,      // CAN1_SCE
        0,      // EXTI9_5
        0,      // TIM1_BRK_TIM9
        0,      // TIM1_UP_TIM10
        0,      // TIM1_TRG_COM_TIM11
        0,      // TIM_CC
        0,      // TIM2
        0,      // TIM3     
        0,      // TIM4
        0,      // I2C1_EV
        0,      // I2C1_ER
        0,      // I2C2_EV
        0,      // I2C2_ER
        0,      // SPI1
        0,      // SPI2
        0,      // USART1
        usart2_handler,      // USART2
        0,      // USART3
        0,      // EXTI15_10



};
