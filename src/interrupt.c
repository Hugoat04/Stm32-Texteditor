
void _isr_enable(void){

	__asm volatile ("cpsie i" : : :"memory");

}


void _isr_disable(void){

	__asm volatile ("cpsid i" : : :"memory");

}
