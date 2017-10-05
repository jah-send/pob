/* Linker script
 *
 * 2009.06.02: set correct memory size
 */

MEMORY 
{
	flash	: ORIGIN = 0, LENGTH = 32K
	ram		: ORIGIN = 0x40000000, LENGTH = 8K
}

/*__stack_end__ = 0x40000000 + 8K - 128;*/

SECTIONS 
{
	. = 0;
	startup : { *(.startup)} >flash

	prog : 
	{
		*(.text)
		*(.rodata)
		*(.rodata*)
		*(.glue_7)
		*(.glue_7t)
	} >flash

	__end_of_text__ = .;

	.data : 
	{
		__data_beg__ = .;
		__data_beg_src__ = __end_of_text__;
		*(.data)
		__data_end__ = .;
	} >ram AT>flash

	.bss : 
	{
		__bss_beg__ = .;
		*(.bss)
		_bss_end__ = . ; __bss_end__ = . ;
	} >ram
	
	/* 2010.03.15 Add stack for fix potential bug ? */
	.stack ALIGN(256) :
    {
		. += 0x400;
		__stack_end__ = .;
	} > ram

	/* Align here to ensure that the .bss section occupies space up to
	_end.  Align after .bss to ensure correct alignment even if the
	.bss section disappears because there are no input sections.  */
	. = ALIGN(32 / 8);
}
	. = ALIGN(32 / 8);
	_end = .;
	 __end__ = . ;
	PROVIDE (end = .);


