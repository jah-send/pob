/* Copyright POB-Technology, 2008
 *
 * contact@pob-technology.com
 * 
 * This software is the main firmware of DUAL-POB device.
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
// firmware configuration 

#ifndef FIRMWARE_CONFIG_H
#define FIRMWARE_CONFIG_H


// Debug on uart0: 
// comment the next line to remove debug
//#define DEBUG_DUAL_POB	1

// Default uart baudrate
#define UART_BAUDRATE		19200



// Dualpob i2c slave address
#define I2C_SLAVE_ADDR		0x44


// Execute pob-eye command
extern void ProcessPobeyeCommand(UInt8 command);
// or a i2c command
extern void ProcessI2cCommand(UInt8 command);

// Execute a uart command
extern void ProcessUARTCommand(UInt8 data);


// servomotor number
#define SERVOS_NUMBER	18

// global variable to store position and speed of servomotor
extern UInt8 position[SERVOS_NUMBER];
extern UInt8 speed[SERVOS_NUMBER];


//pobeye and i2c command firmware:

#define ECHO			  0x00	/**< simple test */
#define SETONESERVO       0x01	/**< set one servo */
#define SWITCHONONESERVO  0x02	/**< switch on one servo */
#define SWITCHOFFONESERVO 0x03	/**< switch off one servo */
#define SETARRAYSERVO     0x04	/**< set many servos with position and speed */
#define GETCURRENTPOS     0x05	/**< rfu */
#define SETARRAYPOSITION  0x06	/**< set many servos with position */
#define SETARRAYSPEED     0x07	/**< set many servos with speed */
#define SETGLOBALSPEED    0x08	/**< set speed for all servos */
#define RESETPOBSERVO     0x09	/**< reset dualpob servo */

#define SET_AX12_ID		  0x0A	/**< set ax12 identifier */
#define SET_AX12_SERVO 	  0x0B	/**< set ax12 servomotor */
#define GET_ANALOG		  0x0C	/**< get analog value */
#define SET_PWM			  0x0D	/**< set pwm */
#define SET_MOTOR		  0x0E	/**< set dc motor movement */
#define SET_MOTOR_SPEED	  0x0F	/**< set dc motor speed */

#define SET_IO_WAY		  0x10	/**< configure i/o way */
#define SET_OUTPUT		  0x11	/**< set a pin output to 1 */
#define CLR_OUTPUT		  0x12  /**< clear a pin output */
#define GET_INPUT		  0x13	/**< get pin input value */

#define PING_AX12 		  0x14	/**< ping ax12 servomotor */

// not yet implemented! 
//#define BLUETOOTH_INIT	  0x15	/**< bluetooth init */
//#define UART_INIT		  0x16	/**< uart init */

//#define UART_GET_BYTE	  0x17	/**< get byte from uart */
//#define UART_SET_BYTE	  0x18	/**< set byte to uart */
//#define UART_BYTE_READY	  0x19	/**< is a byte ready from uart? */


#define POBEYE_TEST		  0x1A	/** test pobeye (only for i2c and nxt) */
#define POBEYE_GRAB		  0x1B	/** grab a frame from pobeye (only for i2c and nxt) */
#define POBEYE_SET_FORM	  0x1C	/** set pattern id (only for i2c and nxt) */
#define POBEYE_GET_FORM   0x1D	/** get x/y/widht/height of form recognized (only for i2c and nxt) */
#define POBEYE_GRAB_NO_ACK 0x1E /**< grab a frame no acknowledge (only for nxt) */

#endif
