extern int main(void);
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

void NMI(void) {

}

void hard_fault(void) {

}

typedef void (*isr_t)(void);

__attribute((used, section(".vectors")))
static const isr_t vector_table[10]={

	(isr_t)&_estack,
	reset_handler,
	NMI,
	hard_fault,

};
