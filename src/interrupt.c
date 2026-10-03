
void _isr_enable(void){

	__asm volatile ("cpsie i" : : :"memory");

}


void _isr_disable(void){

	__asm volatile ("cpsid i" : : :"memory");

}

void *memcpy(void *dest, const void *src, unsigned int n) {
	unsigned char *d = dest;
	const unsigned char *s = src;
	while (n--) {
		*d++ = *s++;
	}
	return dest;
}