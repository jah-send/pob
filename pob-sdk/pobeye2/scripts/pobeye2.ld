MEMORY 
{
	flash	: ORIGIN = 0, LENGTH = 120K
	/* baptiste 2009.12.20 32 bytes are reserved for iap command */
	ram		: ORIGIN = 0x40000000, LENGTH = 0x0000FFE0
}


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
	/* bug lib c 19/10/09 romain */
   .eh_frame       : ONLY_IF_RO 
   { KEEP (*(.eh_frame)) 
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
	} >ram
	
	/* baptiste 2009.12.20 added stack aera for lpc2106 */
	/* __stack_end__ = end of bss section + stack size */
	.stack ALIGN(256) :
    {
		. += 0x2000;
		__stack_end__ = .;
	} > ram
  
	/* Align here to ensure that the .bss section occupies space up to
	_end.  Align after .bss to ensure correct alignment even if the
	.bss section disappears because there are no input sections.  */
	. = ALIGN(32 / 8);

}
	. = ALIGN(32 / 8);
	_end = .;
	_bss_end__ = . ; __bss_end__ = . ; __end__ = . ;
	PROVIDE (end = .);

	

