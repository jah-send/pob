//
// lpc2106 and lpc2103 hardware definition.
//
// baptiste & pierre @ pob-technology
//

/** \anchor lpc210x
 *
 * @brief LPC210x Microcontroller.
 *
 * @file
 *
 * The POB-Robotics-Suite uses the LPC2103 microcontroller from NXP.
 * This file include all the definition to access the microcontroller memory and functionnality.
 *
 * Don't use this file if you don't know the low-level hardware of the microcontroller.
 *
 */
#ifndef __LPC210x_H
#define __LPC210x_H

#define FASTIO 1    /* we are on a lpc2103: use the fast input/output! */

/* Pin Connect Block */
#define PINSEL0        (*((volatile unsigned long *) 0xE002C000))
#define PINSEL1        (*((volatile unsigned long *) 0xE002C004))

#ifndef FASTIO
/* Slow Input/Output on LPC2106 */
 	#define GPIO_IOPIN         (*((volatile unsigned long *) 0xE0028000))       /* GPIO Pin value reg  */
 	#define GPIO_IOSET         (*((volatile unsigned long *) 0xE0028004))       /* GPIO Output set reg */
 	#define GPIO_IODIR         (*((volatile unsigned long *) 0xE0028008))       /* GPIO Direction cntrl reg */
 	#define GPIO_IOCLR         (*((volatile unsigned long *) 0xE002800C))       /* GPIO Output clear reg */

#else
/* Fast Input/Output on LPC2106-rev01 */
	#define GPIO_IOPIN         (*((volatile unsigned long *) 0x3FFFC014))       /* fast GPIO Pin value reg  */
 	#define GPIO_IOSET         (*((volatile unsigned long *) 0x3FFFC018))       /* fast GPIO Output set reg */
 	#define GPIO_IODIR         (*((volatile unsigned long *) 0x3FFFC000))       /* fast GPIO Direction reg */
 	#define GPIO_IOCLR         (*((volatile unsigned long *) 0x3FFFC01C))       /* fast GPIO Output clear reg */

	#define GPIO_IOPIN_LOW	   (*((volatile unsigned short *) 0x3FFFC014))		/* fast GPIO pin0 to pin15 */
	#define GPIO_IOPIN_HIGH	   (*((volatile unsigned short *) 0x3FFFC016))		/* fast GPIO pin16 to pin31 */
 #endif

/* system configuration (lpc2106-rev01) */
#define SCS				(*((volatile unsigned long *) 0xE01FC1A0))


/* General Purpose Input/Output (GPIO) */
#define IOPIN          GPIO_IOPIN
#define IOSET          GPIO_IOSET
#define IODIR          GPIO_IODIR
#define IOCLR          GPIO_IOCLR

/* Memory Accelerator Module (MAM) */
#define MAMCR          (*((volatile unsigned char *) 0xE01FC000))
#define MAMTIM         (*((volatile unsigned char *) 0xE01FC004))
#define MAMMAP         (*((volatile unsigned char *) 0xE01FC040))

/* Phase Locked Loop (PLL) */
#define PLLCON         (*((volatile unsigned char *) 0xE01FC080))
#define PLLCFG         (*((volatile unsigned char *) 0xE01FC084))
#define PLLSTAT        (*((volatile unsigned short*) 0xE01FC088))
#define PLLFEED        (*((volatile unsigned char *) 0xE01FC08C))

/* VPB Divider */
#define VPBDIV         (*((volatile unsigned char *) 0xE01FC100))


/* Universal Asynchronous Receiver Transmitter 0 (UART0) */
#define UART0_RBR      (*((volatile unsigned char *) 0xE000C000))
#define UART0_THR      (*((volatile unsigned char *) 0xE000C000))
#define UART0_IER      (*((volatile unsigned char *) 0xE000C004))
#define UART0_IIR      (*((volatile unsigned char *) 0xE000C008))
#define UART0_FCR      (*((volatile unsigned char *) 0xE000C008))
#define UART0_LCR      (*((volatile unsigned char *) 0xE000C00C))
#define UART0_MCR      (*((volatile unsigned char *) 0xE000C010))
#define UART0_LSR      (*((volatile unsigned char *) 0xE000C014))
#define UART0_MSR      (*((volatile unsigned char *) 0xE000C018))
#define UART0_SCR      (*((volatile unsigned char *) 0xE000C01C))
#define UART0_DLL      (*((volatile unsigned char *) 0xE000C000))
#define UART0_DLM      (*((volatile unsigned char *) 0xE000C004))

/* ---- UART 1 --------------------------------------------- */
#define UART1_RBR       (*((volatile unsigned char *)(0xE0010000)))
#define UART1_THR       (*((volatile unsigned char *)(0xE0010000)))
#define UART1_IER       (*((volatile unsigned char *)(0xE0010004)))
#define UART1_IIR       (*((volatile unsigned char *)(0xE0010008)))
#define UART1_FCR       (*((volatile unsigned char *)(0xE0010008)))
#define UART1_LCR       (*((volatile unsigned char *)(0xE001000C)))
#define UART1_LSR       (*((volatile unsigned char *)(0xE0010014)))
#define UART1_SCR       (*((volatile unsigned char *)(0xE001001C)))
#define UART1_DLL       (*((volatile unsigned char *)(0xE0010000)))
#define UART1_DLM       (*((volatile unsigned char *)(0xE0010004)))
#define UART1_MCR       (*((volatile unsigned char *)(0xE0010010)))
#define UART1_MSR       (*((volatile unsigned char *)(0xE0010018)))

/* I2C Interface 0 */
#define I2C0_I2CONSET   (*((volatile unsigned char *) 0xE001C000))
#define I2C0_I2STAT     (*((volatile unsigned char *) 0xE001C004))
#define I2C0_I2DAT      (*((volatile unsigned char *) 0xE001C008))
#define I2C0_I2ADR      (*((volatile unsigned char *) 0xE001C00C))
#define I2C0_I2SCLH     (*((volatile unsigned short*) 0xE001C010))
#define I2C0_I2SCLL     (*((volatile unsigned short*) 0xE001C014))
#define I2C0_I2CONCLR   (*((volatile unsigned char *) 0xE001C018))

/* I2C Interface 1 */
#define I2C1_I2CONSET   (*((volatile unsigned char *) 0xE005C000))
#define I2C1_I2STAT     (*((volatile unsigned char *) 0xE005C004))
#define I2C1_I2DAT      (*((volatile unsigned char *) 0xE005C008))
#define I2C1_I2ADR      (*((volatile unsigned char *) 0xE005C00C))
#define I2C1_I2SCLH     (*((volatile unsigned short*) 0xE005C010))
#define I2C1_I2SCLL     (*((volatile unsigned short*) 0xE005C014))
#define I2C1_I2CONCLR   (*((volatile unsigned char *) 0xE005C018))


/* Timer 0 */
#define TIMER0_IR      (*((volatile unsigned long *) 0xE0004000))
#define TIMER0_TCR     (*((volatile unsigned long *) 0xE0004004))
#define TIMER0_TC      (*((volatile unsigned long *) 0xE0004008))
#define TIMER0_PR      (*((volatile unsigned long *) 0xE000400C))
#define TIMER0_PC      (*((volatile unsigned long *) 0xE0004010))
#define TIMER0_MCR     (*((volatile unsigned long *) 0xE0004014))
#define TIMER0_MR0     (*((volatile unsigned long *) 0xE0004018))
#define TIMER0_MR1     (*((volatile unsigned long *) 0xE000401C))
#define TIMER0_MR2     (*((volatile unsigned long *) 0xE0004020))
#define TIMER0_MR3     (*((volatile unsigned long *) 0xE0004024))
#define TIMER0_CCR     (*((volatile unsigned long *) 0xE0004028))
#define TIMER0_CR0     (*((volatile unsigned long *) 0xE000402C))
#define TIMER0_CR1     (*((volatile unsigned long *) 0xE0004030))
#define TIMER0_CR2     (*((volatile unsigned long *) 0xE0004034))
#define TIMER0_CR3     (*((volatile unsigned long *) 0xE0004038))
#define TIMER0_EMR     (*((volatile unsigned long *) 0xE000403C))
#define TIMER0_CTCR    (*((volatile unsigned long *) 0xE0004070)) //baptiste 2009.08.12
#define TIMER0_PWMCON  (*((volatile unsigned long *) 0xE0004074)) //baptiste 2009.08.12

/* Timer 1 baptiste 2007.05.10*/
#define TIMER1_IR     (*((volatile unsigned long *) 0xE0008000))	/* Interrupt register */
#define TIMER1_TCR    (*((volatile unsigned long *) 0xE0008004))	/* Timer Control register */
#define TIMER1_TC     (*((volatile unsigned long *) 0xE0008008))	/* Timer Counter */
#define TIMER1_PR     (*((volatile unsigned long *) 0xE000800C))	/* Prescale register */
#define TIMER1_PC     (*((volatile unsigned long *) 0xE0008010))	/* Prescale Counter */
#define TIMER1_MCR    (*((volatile unsigned long *) 0xE0008014))	/* Match Control register  */
#define TIMER1_MR0    (*((volatile unsigned long *) 0xE0008018))	/* Match reg0  */
#define TIMER1_MR1    (*((volatile unsigned long *) 0xE000801C))	/* Match reg1  */
#define TIMER1_MR2    (*((volatile unsigned long *) 0xE0008020))	/* Match reg2  */
#define TIMER1_MR3    (*((volatile unsigned long *) 0xE0008024))	/* Match reg3  */
#define TIMER1_CCR    (*((volatile unsigned long *) 0xE0008028))	/* Capture Control register */
#define TIMER1_CR0    (*((volatile unsigned long *) 0xE000802C))	/* Capt reg0  */
#define TIMER1_CR1    (*((volatile unsigned long *) 0xE0008030))	/* Capt reg1  */
#define TIMER1_CR2    (*((volatile unsigned long *) 0xE0008034))	/* Capt reg2  */
#define TIMER1_CR3    (*((volatile unsigned long *) 0xE0008038))	/* Capt reg3  */
#define TIMER1_EMR    (*((volatile unsigned long *) 0xE000803C))	/* External Match register */

/* Timer 2 baptiste 2009.08.11*/
#define TIMER2_IR     (*((volatile unsigned long *) 0xE0070000))	/* Interrupt register */
#define TIMER2_TCR    (*((volatile unsigned long *) 0xE0070004))	/* Timer Control register */
#define TIMER2_TC     (*((volatile unsigned long *) 0xE0070008))	/* Timer Counter */
#define TIMER2_PR     (*((volatile unsigned long *) 0xE007000C))	/* Prescale register */
#define TIMER2_PC     (*((volatile unsigned long *) 0xE0070010))	/* Prescale Counter */
#define TIMER2_MCR    (*((volatile unsigned long *) 0xE0070014))	/* Match Control register  */
#define TIMER2_MR0    (*((volatile unsigned long *) 0xE0070018))	/* Match reg0  */
#define TIMER2_MR1    (*((volatile unsigned long *) 0xE007001C))	/* Match reg1  */
#define TIMER2_MR2    (*((volatile unsigned long *) 0xE0070020))	/* Match reg2  */
#define TIMER2_MR3    (*((volatile unsigned long *) 0xE0070024))	/* Match reg3  */
#define TIMER2_CCR    (*((volatile unsigned long *) 0xE0070028))	/* Capture Control register */
#define TIMER2_CR0    (*((volatile unsigned long *) 0xE007002C))	/* Capt reg0  */
#define TIMER2_CR1    (*((volatile unsigned long *) 0xE0070030))	/* Capt reg1  */
#define TIMER2_CR2    (*((volatile unsigned long *) 0xE0070034))	/* Capt reg2  */
#define TIMER2_EMR    (*((volatile unsigned long *) 0xE007003C))	/* External Match register */
#define TIMER2_CTCR	  (*((volatile unsigned long *) 0xE0070070))	/* Count control register */
#define TIMER2_PWMCON  (*((volatile unsigned long *) 0xE0070074))

/* Timer 3 baptiste 2009.08.12 */
#define TIMER3_IR     (*((volatile unsigned long *) 0xE0074000))	/* Interrupt register */
#define TIMER3_TCR    (*((volatile unsigned long *) 0xE0074004))	/* Timer Control register */
#define TIMER3_TC     (*((volatile unsigned long *) 0xE0074008))	/* Timer Counter */
#define TIMER3_PR     (*((volatile unsigned long *) 0xE007400C))	/* Prescale register */
#define TIMER3_PC     (*((volatile unsigned long *) 0xE0074010))	/* Prescale Counter */
#define TIMER3_MCR    (*((volatile unsigned long *) 0xE0074014))	/* Match Control register  */
#define TIMER3_MR0    (*((volatile unsigned long *) 0xE0074018))	/* Match reg0  */
#define TIMER3_MR1    (*((volatile unsigned long *) 0xE007401C))	/* Match reg1  */
#define TIMER3_MR2    (*((volatile unsigned long *) 0xE0074020))	/* Match reg2  */
#define TIMER3_MR3    (*((volatile unsigned long *) 0xE0074024))	/* Match reg3  */
#define TIMER3_CCR    (*((volatile unsigned long *) 0xE0074028))	/* Capture Control register */
#define TIMER3_CR0    (*((volatile unsigned long *) 0xE007402C))	/* Capt reg0  */
#define TIMER3_CR1    (*((volatile unsigned long *) 0xE0074030))	/* Capt reg1  */
#define TIMER3_CR2    (*((volatile unsigned long *) 0xE0074034))	/* Capt reg2  */
#define TIMER3_EMR    (*((volatile unsigned long *) 0xE007403C))	/* External Match register */
#define TIMER3_CTCR	  (*((volatile unsigned long *) 0xE0074070))	/* Count control register */


/* Watchdog */
#define WDT_WDMOD	  (*((volatile unsigned long *) 0xE0000000))	/* Watchdog Mode register */
#define WDT_WDTC	      (*((volatile unsigned long *) 0xE0000004))	/* Watchdog Timer Constant register */
#define WDT_WDFEED	  (*((volatile unsigned long *) 0xE0000008))	/* Watchdog Feed sequence register */
#define WDT_WDTV	      (*((volatile unsigned long *) 0xE000000C))	/* Watchdog Timer Value register */

/* Analog To Digital Converter (only lpc2103) */
#define AD0CR            (*((volatile unsigned int *) 0xE0034000))	/* Control register */
#define AD0GDR           (*((volatile unsigned int *) 0xE0034004))	/* Global data register */
#define AD0STAT          (*((volatile unsigned int *) 0xE0034030))	/* Status register */
#define AD0INTEN         (*((volatile unsigned int *) 0xE003400C))	/* Interrupt enable register */
#define AD0DR0           (*((volatile unsigned int *) 0xE0034010))	/* Channel 0 */
#define AD0DR1           (*((volatile unsigned int *) 0xE0034014))	/* Channel 1 */
#define AD0DR2           (*((volatile unsigned int *) 0xE0034018))	/* Channel 2 */
#define AD0DR3           (*((volatile unsigned int *) 0xE003401C))	/* Channel 3 */
#define AD0DR4           (*((volatile unsigned int *) 0xE0034020))	/* Channel 4 */
#define AD0DR5           (*((volatile unsigned int *) 0xE0034024))	/* Channel 5 */
#define AD0DR6           (*((volatile unsigned int *) 0xE0034028))	/* Channel 6 */
#define AD0DR7           (*((volatile unsigned int *) 0xE003402C))	/* Channel 7 */


/* Vectored Interrupt Controller (VIC) */
#define VICIRQStatus   (*((volatile unsigned long *) 0xFFFFF000))
#define VICFIQStatus   (*((volatile unsigned long *) 0xFFFFF004))
#define VICRawIntr     (*((volatile unsigned long *) 0xFFFFF008))
#define VICIntSelect   (*((volatile unsigned long *) 0xFFFFF00C))
#define VICIntEnable   (*((volatile unsigned long *) 0xFFFFF010))
#define VICIntEnClr    (*((volatile unsigned long *) 0xFFFFF014))
#define VICSoftInt     (*((volatile unsigned long *) 0xFFFFF018))
#define VICSoftIntClr  (*((volatile unsigned long *) 0xFFFFF01C))
#define VICProtection  (*((volatile unsigned long *) 0xFFFFF020))
#define VICVectAddr    (*((volatile unsigned long *) 0xFFFFF030))
#define VICDefVectAddr (*((volatile unsigned long *) 0xFFFFF034))
#define VICVectAddr0   (*((volatile unsigned long *) 0xFFFFF100))
#define VICVectAddr1   (*((volatile unsigned long *) 0xFFFFF104))
#define VICVectAddr2   (*((volatile unsigned long *) 0xFFFFF108))
#define VICVectAddr3   (*((volatile unsigned long *) 0xFFFFF10C))
#define VICVectAddr4   (*((volatile unsigned long *) 0xFFFFF110))
#define VICVectAddr5   (*((volatile unsigned long *) 0xFFFFF114))
#define VICVectAddr6   (*((volatile unsigned long *) 0xFFFFF118))
#define VICVectAddr7   (*((volatile unsigned long *) 0xFFFFF11C))
#define VICVectAddr8   (*((volatile unsigned long *) 0xFFFFF120))
#define VICVectAddr9   (*((volatile unsigned long *) 0xFFFFF124))
#define VICVectAddr10  (*((volatile unsigned long *) 0xFFFFF128))
#define VICVectAddr11  (*((volatile unsigned long *) 0xFFFFF12C))
#define VICVectAddr12  (*((volatile unsigned long *) 0xFFFFF130))
#define VICVectAddr13  (*((volatile unsigned long *) 0xFFFFF134))
#define VICVectAddr14  (*((volatile unsigned long *) 0xFFFFF138))
#define VICVectAddr15  (*((volatile unsigned long *) 0xFFFFF13C))
#define VICVectCntl0   (*((volatile unsigned long *) 0xFFFFF200))
#define VICVectCntl1   (*((volatile unsigned long *) 0xFFFFF204))
#define VICVectCntl2   (*((volatile unsigned long *) 0xFFFFF208))
#define VICVectCntl3   (*((volatile unsigned long *) 0xFFFFF20C))
#define VICVectCntl4   (*((volatile unsigned long *) 0xFFFFF210))
#define VICVectCntl5   (*((volatile unsigned long *) 0xFFFFF214))
#define VICVectCntl6   (*((volatile unsigned long *) 0xFFFFF218))
#define VICVectCntl7   (*((volatile unsigned long *) 0xFFFFF21C))
#define VICVectCntl8   (*((volatile unsigned long *) 0xFFFFF220))
#define VICVectCntl9   (*((volatile unsigned long *) 0xFFFFF224))
#define VICVectCntl10  (*((volatile unsigned long *) 0xFFFFF228))
#define VICVectCntl11  (*((volatile unsigned long *) 0xFFFFF22C))
#define VICVectCntl12  (*((volatile unsigned long *) 0xFFFFF230))
#define VICVectCntl13  (*((volatile unsigned long *) 0xFFFFF234))
#define VICVectCntl14  (*((volatile unsigned long *) 0xFFFFF238))
#define VICVectCntl15  (*((volatile unsigned long *) 0xFFFFF23C))


#endif  // __LPC210x_H
