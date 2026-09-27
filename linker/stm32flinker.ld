ENTRY(reset_handler) 


MEMORY {
	rom (rx) : ORIGIN = 0x08000000, LENGTH = 512k /* flash memory on the stm32f466re starts at address 0x08000000*/
	ram (rwx): ORIGIN = 0x20000000, LENGTH = 128k
}

_estack = ORIGIN(ram) + LENGTH(ram);	/* The stack pointer starts at the end of RAM and grows down */

SECTIONS {
	

	/* section for vectors like the reset handler and interrupts */
	.vectors : ALIGN(4) {
		KEEP(*(.vectors))
		. = ALIGN(4);	
	}

	/* The code will live here */
	.text : ALIGN(4) {	
		*(.text*)
		.  = ALIGN(4);
		_etext = .;
	} > rom

	/* initilized variables will live here */
	_sdata = LOADADDR(.data);
	.data : ALIGN(4) {
		_data = .;
		*(.data*)
		. = ALIGN(4);
		_edata = .;
	} > ram AT > rom


	/* uninitilized variables will live here */
	.bss : ALIGN(4) {
		_sbss = .;
		*(.bss*)
		. = ALIGN(4);
		_ebss = .;
	} > ram 
	_end = .;
}
