

MEMORY {
   flash : ORIGIN = 0, LENGTH = 120K
   ram : ORIGIN = 0x40000000, LENGTH = 64K
   }

__stack_end__ = 0x40000000 + 64K - 4;
SECTIONS {
  . = 0;
  startup : { *(.startup)} >flash
  prog : {
         *(.text)
         *(.rodata)
         *(.rodata*)
         *(.glue_7)
         *(.glue_7t)
         } >flash
  __end_of_text__ = .;
  .data : {
         __data_beg__ = .;
         __data_beg_src__ = __end_of_text__;
         *(.data)
         __data_end__ = .;
         } >ram AT>flash
  .bss : {
         __bss_beg__ = .;
         *(.bss)
         } >ram
    /* Align here to ensure that the .bss section occupies space up to
       _end.  Align after .bss to ensure correct alignment even if the
       .bss section disappears because there are no input sections.  */
    . = ALIGN(32 / 8);
   }
   . = ALIGN(32 / 8);
   _end = .;
   _bss_end__ = . ; __bss_end__ = . ; __end__ = . ;
   PROVIDE (end = .);

/*
INPUT( -lc -lgcc)
*/


PROVIDE( undefined_instruction_exception = endless_loop);
PROVIDE( software_interrupt_exception = endless_loop);
PROVIDE( prefetch_abort_exception = endless_loop);
PROVIDE( data_abort_exception = endless_loop);
PROVIDE( reserved_exception = endless_loop);
PROVIDE( interrupt_exception = endless_loop);
PROVIDE( fast_interrupt_exception = endless_loop);



PROVIDE( PINSEL0 = 0xE002C000);
PROVIDE( IODIR = 0xE0028008);
PROVIDE( IOCLR = 0xE002800C);
PROVIDE( IOSET = 0xE0028004);

/* UART 0 */

PROVIDE( U0RBR = 0xE000C000);
PROVIDE( U0THR = 0xE000C000);
PROVIDE( U0IER = 0xE000C004);
PROVIDE( U0IIR = 0xE000C008);
PROVIDE( U0FCR = 0xE000C008);
PROVIDE( U0LCR = 0xE000C00C);
PROVIDE( U0LSR = 0xE000C014);
PROVIDE( U0SCR = 0xE000C01C);
PROVIDE( U0DLL = 0xE000C000);
PROVIDE( U0DLM = 0xE000C004);

/* UART 1 */

PROVIDE( U1RBR = 0xE0010000);
PROVIDE( U1THR = 0xE0010000);
PROVIDE( U1IER = 0xE0010004);
PROVIDE( U1IIR = 0xE0010008);
PROVIDE( U1FCR = 0xE0010008);
PROVIDE( U1LCR = 0xE001000C);
PROVIDE( U1LSR = 0xE0010014);
PROVIDE( U1SCR = 0xE001001C);
PROVIDE( U1DLL = 0xE0010000);
PROVIDE( U1DLM = 0xE0010004);

/* PLL */

PROVIDE( PLLCON = 0xE01FC080);
PROVIDE( PLLCFG = 0xE01FC084);
PROVIDE( PLLSTAT = 0xE01FC088);
PROVIDE( PLLFEED = 0xE01FC08C);

/* MAM */

PROVIDE( MAMCR = 0xE01FC000);
PROVIDE( MAMTIM = 0xE01FC004);

/* VPB */

PROVIDE( VPBDIV = 0xE01FC100);

/* TIMER 0 */

PROVIDE( T0IR = 0xE0004000);
PROVIDE( T0TCR = 0xE0004004);
PROVIDE( T0TC = 0xE0004008);
PROVIDE( T0PR = 0xE000400C);
PROVIDE( T0PC = 0xE0004010);
PROVIDE( T0MCR = 0xE0004014);
PROVIDE( T0MR0 = 0xE0004018);
PROVIDE( T0MR1 = 0xE000401C);
PROVIDE( T0MR2 = 0xE0004020);
PROVIDE( T0MR3 = 0xE0004024);
PROVIDE( T0CCR = 0xE0004028);
PROVIDE( T0CR0 = 0xE000402C);
PROVIDE( T0CR1 = 0xE0004030);
PROVIDE( T0CR2 = 0xE0004034);
PROVIDE( T0EMR = 0xE000403C);

/* FAST IO */

PROVIDE( GPIO_IOPIN = 0x3FFFC014);
PROVIDE( GPIO_IOSET = 0x3FFFC018);
PROVIDE( GPIO_IODIR = 0x3FFFC000);
PROVIDE( GPIO_IOCLR = 0x3FFFC01C);

PROVIDE( POB_IO = 0x3FFFC014);
PROVIDE( POB_IODIR = 0x3FFFC000);
PROVIDE( POB_IOSET = 0x3FFFC018);
PROVIDE( POB_IOCLR = 0x3FFFC01C);

PROVIDE( SCS = 0xE01FC1A0);

