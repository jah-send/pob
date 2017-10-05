//
// Copyright 2008 POB-Technology. All rights reserved.
// POB-Technology PROPRIETARY/CONFIDENTIAL.
//

/** \anchor iobus
 * 
 * @brief input/output management
 *
 * @file
 *
 * The dual-pob board have 22 input/output pin free for use. 
 *
 * This pin are on PORTF, PORTB, PORTG and PORTE of the dual-pob cpu:
 * - the PORTF pin 0 to 7, as digital input, digital output or analog input
 * - the PORTB pin2, pin3 and pin7 as digital input/output
 * - the PORTG pin0 to 4 as digital input/output
 * - the PORTE pin 2 to 7 as digital input/output
 *
 * \note Please note that only the PORTF can be use as analog input!
 * 
 * @par Example code: configure input/output pins
 *
 * @code

  UInt8 portb=0;
  UInt8 porte=0;

  // Set pin7 of PORTB as output (the other pin are set as input by default)
  portb = IO_AS_OUTPUT << PIN_7 ;

  // Set pin2 and pin7 of PORTE as output (the other pin are set as input by default)
  porte = (IO_AS_OUTPUT << PIN_2) | (IO_AS_OUTPUT << PIN_7 ); 

  // Finally, write the i/o configuration:
  SetIOWay(portb, porte,IO_AS_DEFAULT,IO_AS_DEFAULT);

 * @endcode
 *
 * @par Example code: set/clear an output pin
 *
 * @code

  // Set pin7 of PORTE to 1 during 1 second

  SetOutput(PORTE,PIN_7);

  Wait_Ms(1000);

  ClearOutput(PORTE,PIN_7);


 * @endcode
 *
 * @par Example code: Get value of input pin
 *
 * @code

  UInt8 value;

  // Get the pin value of PORTB
  value = GetInput(INPUT_PORTB,INPUT_1);

 * @endcode
 *
 * For advanced users, you can check the AVR-libc documentations at http://www.nongnu.org/avr-libc
 */
#ifndef DUAL_POB_IO_H
#define DUAL_POB_IO_H

#include <avr/io.h>

#define cbi(REG8,BITNUM) REG8 &= ~(_BV(BITNUM))
#define sbi(REG8,BITNUM) REG8 |= _BV(BITNUM)


/** @name Define for set and clear output pin
 *
 */
/*@{*/

/** @brief Set output pin
 * Write a logical one to the output pin of the specified port
 *
 * <b>Parameters:</b>
 * - PORT		port's name: <i>PORTF, PORTB, PORTG, PORTE</i>
 * - BIT		pin's port to set (PIN_0 to PIN_7)
 */
#define SetOutput(PORT,PIN)	sbi(PORT,PIN)	

/** @brief Clear output pin.
 * Write a logical zero to output pin of the specified port.
 *
 * <b>Parameters:</b>
 * - PORT		port's name: <i>PORTF, PORTB, PORTG, PORTE</i>
 * - BIT		pin's port to clear (PIN_0 to PIN_7)
 */
#define ClearOutput(PORT,PIN)	cbi(PORT,PIN)
/*@}*/


/** @brief IO pin settings.
 * 
 */
typedef enum _io_settings
{
	IO_AS_INPUT=0,		/**<	Set io pin as input */
	IO_AS_OUTPUT=1,		/**<	Set io pin as output */
	IO_AS_ANALOG=0,		/**<	Set io pin as analog input */
	IO_AS_DEFAULT=0		/**<	Default io settings: input */
} IO_SETTINGS;

/** @brief Port input enumeration
 *
 * Use this enumeration with the GetInput() function.
 */
typedef enum _input_port
{
	INPUT_PORTB=0,		/**<	PORTB */
	INPUT_PORTE=1,		/**<	PORTE */
	INPUT_PORTF=2,		/**<	PORTF */
	INPUT_PORTG=3,		/**<	PORTF */
	INPUT_NONE=4		/**<	NONE  */
} INPUT_PORT;

/** @brief Pin ouput number
 *
 * Use only for the output functions: ClearOutput(), SetOutput() and the configuration function: SetIOWay().
 */
typedef enum _io_pin
{
	PIN_0=0,
	PIN_1=1,
	PIN_2=2,
	PIN_3=3,
	PIN_4=4,
	PIN_5=5,
	PIN_6=6,
	PIN_7=7
} IO_PIN;

/** @brief Pin input number
 *
 * Use this enumeration with the GetInput() function.
 */
typedef enum _input_pin
{
	INPUT_0=0x01,	/**<	Get pin 0 */
	INPUT_1=0x02,	/**<	Get pin 1 */
	INPUT_2=0x04,	/**<	Get pin 2 */
	INPUT_3=0x08,	/**<	Get pin 3 */
	INPUT_4=0x10,	/**<	Get pin 4 */
	INPUT_5=0x20,	/**<	Get pin 5 */
	INPUT_6=0x40,	/**<	Get pin 6 */
	INPUT_7=0x80	/**<	Get pin 7 */
} INPUT_PIN;

/** @brief Set IO way as input/output of portb, porte, portf or portg.
 *
 * @param portb		PORTB configuration word
 * @param porte		PORTE configuration word
 * @param portf		PORTF configuration word
 * @param portg		PORTG configuration word
 */
extern void SetIOWay(UInt8 portb, UInt8 porte, UInt8 portf, UInt8 portg);


/** @brief Get input pin value
 *
 * @param port		port where read the value
 * @param pin		pin number of port
 * @return the pin value: 0 or 1. if selected port is wrong, the function will return 0xFF.
 */
extern UInt8 GetInput(INPUT_PORT port,INPUT_PIN pin);


#endif
