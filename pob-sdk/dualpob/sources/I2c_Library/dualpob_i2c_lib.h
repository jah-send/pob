/* Copyright POB-Technology, 2008
 *
 * contact@pob-technology.com
 * 
 * This software is a library whose purpose is to manage the DUAL-POB device from I2C bus.
 * 
 * This software is governed by the CeCILL-C license under French law and
 * abiding by the rules of distribution of free software.  You can  use, 
 * modify and/ or redistribute the software under the terms of the CeCILL-C
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info". 
 * 
 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited
 * liability. 
 * 
 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 * therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or 
 * data to be ensured and,  more generally, to use and operate it in the 
 * same conditions as regards security. 
 * 
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL-C license and that you accept its terms.
 * 
 */

/** \anchor dualpob_i2c_lib
 *
 * @brief DUAL-POB I2C LIBRARY
 *
 * @file
 *
 * Manage the Dual-POB device over the I2C bus. 
 * All the function are derived from the DUAL-POB API: If you want more details about functions, read the DUAL-POB API documentation.
 *
 * How to use the library:
 * - Flash dualpob device with the default firmware
 * - Compile the dualpob_i2c_lib.c for your platform
 * 
 * How to configure the library for your platform:
 * - By default, the library is configured for pobeye
 * - Open the dualpob_i2c_lib.c
 * - Change the include section with your own platform include
 * - Change the i2c functions sections with your own i2c platform function
 *
 *
 */
#ifndef DUALPOB_I2C_LIB_H
#define DUALPOB_I2C_LIB_H


/** @brief Test communication between dualpob and your platform.
 *
 * @param Data
 * @return Echo back
 */
extern unsigned char dualpob_echo(unsigned char data);

/** @brief Ping AX-12 servomotor.
 *
 * @param servo	Servomotor identifier
 * @return 1 if servomotor is detected, else 0
 */
extern unsigned char dualpob_pingAx12Servo(unsigned char servo);

/** @brief Set AX-12 position/speed.
 *
 * @param servo		Servomotor identifier
 * @param position	Servomotor position
 * @param speed		Servomotor speed
 */
extern void dualpob_setAx12Servo(unsigned char servo,unsigned short position, unsigned short speed);

/** @brief Get analog value from a dualpob channel.
 *
 * @param	channel		Analog channel between 0 and 7.
 * @return	Analog value
 */
extern unsigned char dualpob_getAnalog(unsigned char channel);

/** @brief dual-servo pwm prescaler enumerations
 *
 */
typedef enum __dp_prescaler { 
	DP_PWM_1=0x0,	/**< PWM prescaler of 1 */
	DP_PWM_4=0x1,	/**< PWM prescaler of 4 */
	DP_PWM_16=0x2	/**< PWM prescaler of 16 */
} DP_PWM_PRESCALER;

/** @brief Set pwm of the dualpob direct current motor
 *
 * see DUAL-POB API for details.
 *
 * @param period
 * @param dutycycle
 * @param prescaler
 */
extern void dualpob_setPwm(unsigned char period,unsigned char dutycycle,DP_PWM_PRESCALER prescaler);

/** @brief dual-servo dc motor movement enumeration.
 *
 */
typedef enum __dp_dc_motor {
	DP_DC_MOTOR_STOP=0,		/**< stop motors */
	DP_DC_MOTOR_RUN=0x28,	/**< run */
	DP_DC_MOTOR_BACK=0x50,	/**< back */
	DP_DC_MOTOR_LEFT=0x48,	/**< left */
	DP_DC_MOTOR_RIGHT=0x30	/**< right */
} DP_DC_MOTOR;

/** @brief Set movement of direct current motor.
 *
 * @param move		DC motor activation
 */
extern void dualpob_setDCMotor(DP_DC_MOTOR move);

/** @brief Set speed of dual-pob DC motors.
 *
 * If you want control the speed with more parameters, use the dualpob_setPwm().
 *
 * @param speed		DC motors speed (between 0 and 35)
 */
extern void dualpob_setDCSpeed(unsigned char speed);


/** @brief IO pin settings enumeration.
 * 
 */
typedef enum __dp_io_settings
{
	DP_IO_AS_INPUT=0,		/**<	Set io pin as input */
	DP_IO_AS_OUTPUT=1,		/**<	Set io pin as output */
	DP_IO_AS_ANALOG=0,		/**<	Set io pin as analog input */
	DP_IO_AS_DEFAULT=0		/**<	Default io settings: input */
} DP_IO_SETTINGS;

/** @brief Set dual-pob input/output configuration of portb, porte, portf and portg pins.
 *
 * see DUAL-POB API for detail and example.
 *
 * @param portb		PORTB configuration word
 * @param porte		PORTE configuration word
 * @param portf		PORTF configuration word
 * @param portg		PORTG configuration word
 */
extern void dualpob_setIoWay(unsigned char portb, unsigned char porte, unsigned char portf, unsigned portg);


/** @brief Output port enumeration.
 *
 */
typedef enum __dp_output_port {
	DP_OUTPUT_PORTB=0,		/**<	select PORTB as output port */
	DP_OUTPUT_PORTE=1,		/**<	select PORTE as output port */
	DP_OUTPUT_PORTF=2,		/**<	select PORTF as output port */
	DP_OUTPUT_PORTG=3		/**<	select PORTG as output port */
} DP_OUTPUT_PORT;


/** @brief Output pin number enumerations.
 *
 * Use this enumeration in dualpob_setOutput() and dualpob_clearOutput() functions.
 */
typedef enum __dp_output_pin
{
	DP_PIN_0=0,	/**<	pin0 of a I/O port */
	DP_PIN_1=1,	/**<	pin1 of a I/O port */
	DP_PIN_2=2,	/**<	pin2 of a I/O port */
	DP_PIN_3=3,	/**<	pin3 of a I/O port */
	DP_PIN_4=4,	/**<	pin4 of a I/O port */
	DP_PIN_5=5,	/**<	pin5 of a I/O port */
	DP_PIN_6=6,	/**<	pin6 of a I/O port */
	DP_PIN_7=7		/**<	pin7 of a I/O port */
} DP_OUTPUT_PIN;

/** @brief Set output pin.
 * Write a logical one to the output pin of the specified port
 *
 * @param port	port's name (DP_OUTPUT_PORTB to DP_OUTPUT_PORTG)
 * @param pin	pin's port to set (DP_PIN_0 to DP_PIN_7)
 */
extern void dualpob_setOutput(DP_OUTPUT_PORT port, DP_OUTPUT_PIN pin);

/** @brief Clear output pin.
 * Write a logical zero to output pin of the specified port.
 *
 * @param port	port's name.
 * @param pin	pin's port to clear (DP_PIN_0 to DP_PIN_7)
 */
extern void dualpob_clearOutput(DP_OUTPUT_PORT port, DP_OUTPUT_PIN pin);


/** @brief Port input enumeration.
 *
 * Use this enumeration with the dualpob_getInput() function.
 */
typedef enum __dp_input_port
{
	DP_INPUT_PORTB=0,		/**<	PORTB */
	DP_INPUT_PORTE=1,		/**<	PORTE */
	DP_INPUT_PORTF=2,		/**<	PORTF */
	DP_INPUT_PORTG=3,		/**<	PORTF */
	DP_INPUT_NONE=4		/**<	NONE  */
} DP_INPUT_PORT;


/** @brief Pin input number enumeration.
 *
 * Use this enumeration with the dualpob_getInput() function.
 */
typedef enum __dp_input_pin
{
	DP_INPUT_0=0x01,	/**<	Get pin 0 */
	DP_INPUT_1=0x02,	/**<	Get pin 1 */
	DP_INPUT_2=0x04,	/**<	Get pin 2 */
	DP_INPUT_3=0x08,	/**<	Get pin 3 */
	DP_INPUT_4=0x10,	/**<	Get pin 4 */
	DP_INPUT_5=0x20,	/**<	Get pin 5 */
	DP_INPUT_6=0x40,	/**<	Get pin 6 */
	DP_INPUT_7=0x80	/**<	Get pin 7 */
} DP_INPUT_PIN;

/** @brief Get input pin value.
 *
 * @param port		port where read the value (DP_INPUT_PORTx)
 * @param pin		pin number of port (DP_INPUT_y)
 * @return the pin value: 0 or 1. if selected port is wrong, the function will return 0xFF.
 */
extern unsigned char dualpob_getInput(DP_INPUT_PORT port,DP_INPUT_PIN pin);

/** @brief Init dualpob servomotor.
 *
 */
extern void dualpob_initServos(void);

/** @brief Set servomotor.
 *
 * @param servo		Servomotor to move (between 0 and 18)
 * @param position  Servomotor Position (0 to 255)
 * @param speed		Servomotor Speed (between 0 and 7)
 */
extern void dualpob_setServo(unsigned char servo, unsigned char position, unsigned char speed);

/** @brief Switch on servomotor.
 *
 * @param servo	Servomotor identifier
 */
extern void dualpob_switchOnServo(UInt8 servo);

/** @brief Switch off servomotor.
 *
 * @param Servomotor identifier
 */
extern void dualpob_switchOffServo(UInt8 servo);

/** @brief Set position/speed of servomotors.
 *
 * @param position Servomotor position array
 * @param speed	   Servomotor speed array
 * @param offset   Servomotor where begin to set position and speed
 * @param len	   Lenght of position and speed array
 */
extern void dualpob_setServoArray( unsigned char *position, unsigned char *speed, unsigned char offset, unsigned char len);

/** @brief Set position of servomotors.
 *
 * @param position Servomotor position array
 * @param offset   Servomotor where begin to set position
 * @param len	   Lenght of position array
 */
extern void dualpob_setServoPosition(unsigned char *position, unsigned char offset,unsigned char len);

/** @brief Set speed of servomotors.
 *
 * @param speed	   Servomotor speed array
 * @param offset   Servomotor where begin to set speed
 * @param len	   Lenght of speed array
 */
extern void dualpob_setServoSpeed(unsigned char *speed,unsigned char offset,unsigned char len);

/** @brief Set speed of all servomotors.
 *
 * @param speed	Speed for all servomotors
 */
extern void dualpob_setGlobalSpeed(UInt8 speed);


extern unsigned char dualpob_pobeyeTest(unsigned char data);

/** @brief Set the form to be recognized in pobeye memory.
 *
 * @param form	Form number: 1=BIgA 2=Circle 3=Cross 4=King 5=Tower 6=Trefle 7=Triangle
 */
extern void dualpob_setPobeyeForm(unsigned char form);

/** @brief Grab a new frame and identify form
 *
 * @return 1 no error
 */
extern unsigned char dualpob_grabFrame(void);

/** @brief Get form recognized
 *
 * @param [out] x	x coordinate of the form
 * @param [out] y	y coordinate of the form
 * @param [out] w   Form's widht
 * @param [out] h	Form's height
 * @return 1 if a form is recognized, else 0.
 */
extern unsigned char dualpob_getPobeyeForm(unsigned char *x,unsigned char *y,unsigned char *w,unsigned char *h);

#endif
