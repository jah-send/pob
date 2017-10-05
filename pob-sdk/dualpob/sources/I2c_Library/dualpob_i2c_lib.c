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


/** include section
 *
 * Note for users: set your own include files for your platform!
 *
 * For example , here the dualpob is used with pobeye
 */
#include <pob-eye.h>	

#include "dualpob_i2c_lib.h"

/** i2c functions 
 *
 * Note for users: you have to change this define for your platform!
 */
/**< i2c start condition + send slave address */
#define i2c_start_sendaddr(addr) SendSlaveAdress(addr)		
/**< i2c write */
#define i2c_write(data)		WriteOnI2C(data)
/**< i2c read + ack */
#define i2c_read_ack()		ReadOnI2CWithAck(0)
/**< i2c read + no ack */
#define i2c_read_noack()	ReadOnI2CWithAck(1)
/**< i2c stop condition */
#define i2c_stop()			STOPI2C()
/**< wait in us */
#define wait_us(long_time)	Wait(long_time);

/** dualpob i2c address 
 *
 * Note for users: if you change the i2c address, you have to set the same i2c address in the dualpob main firmware!
 */
#define DUALPOB_I2C_ADDR	0x44	


/** dualpob i2c command */

#define ECHO			  0x00	/**< simple test */
#define SETONESERVO       0x01	/**< set one servo */
#define SWITCHONONESERVO  0x02	/**< switch on one servo */
#define SWITCHOFFONESERVO 0x03	/**< switch off one servo */
#define SETARRAYSERVO     0x04	/**< set many servos with position and speed */
#define GETCURRENTPOS     0x05	/**< !!not implemented!! */
#define SETARRAYPOSITION  0x06	/**< set many servos with position */
#define SETARRAYSPEED     0x07	/**< set many servos with speed */
#define SETGLOBALSPEED    0x08	/**< set speed for all servos */
#define RESETPOBSERVO     0x09	/**< reset dualpob servo */

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

#define POBEYE_TEST		  0x1A	/** test pobeye communication */
#define POBEYE_GRAB		  0x1B	/** grab a frame and identify form */
#define POBEYE_SET_FORM	  0x1C	/** set pattern form */
#define POBEYE_GET_FORM   0x1D	/** get pattern form */


/** dualpob servomotors variables */

#define SERVOS_NUMBER	18				/**< servomotors numbers */


/** public functions */

unsigned char dualpob_echo(unsigned char data)
{
	unsigned char tmp;

	i2c_start_sendaddr(DUALPOB_I2C_ADDR);
	i2c_write(ECHO);
	i2c_write(data);
	i2c_stop();

	i2c_start_sendaddr(DUALPOB_I2C_ADDR|1);
	tmp = i2c_read_noack();
	i2c_stop();

	return tmp;
}

unsigned char dualpob_pingAx12Servo(unsigned char servo)
{
	unsigned char answer;

	i2c_start_sendaddr(DUALPOB_I2C_ADDR);
	i2c_write(PING_AX12);
	i2c_write(servo);
	i2c_stop();
	i2c_start_sendaddr(DUALPOB_I2C_ADDR|1);
	answer=i2c_read_noack();

	return answer;
}

void dualpob_setAx12Servo(unsigned char servo,unsigned short position, unsigned short speed)
{
	i2c_start_sendaddr(DUALPOB_I2C_ADDR);
	i2c_write(SET_AX12_SERVO);
	i2c_write(servo);
	
	i2c_write(position>>8);
	i2c_write(position);

	i2c_write(speed>>8);
	i2c_write(speed);

	i2c_stop();
}

unsigned char dualpob_getAnalog(unsigned char channel)
{
	unsigned char ana;

	i2c_start_sendaddr(DUALPOB_I2C_ADDR);
	i2c_write(GET_ANALOG);
	i2c_write(channel);
	i2c_start_sendaddr(DUALPOB_I2C_ADDR|1);
	ana = i2c_read_noack();
	i2c_stop();

	return ana;
}


void dualpob_setPwm(unsigned char period,unsigned char dutycycle,DP_PWM_PRESCALER prescaler)
{
	i2c_start_sendaddr(DUALPOB_I2C_ADDR);
	i2c_write(SET_PWM);
	i2c_write(period);
	i2c_write(dutycycle);
	i2c_write(prescaler);
	i2c_stop();
}

void dualpob_setDCMotor(DP_DC_MOTOR move)
{
	i2c_start_sendaddr(DUALPOB_I2C_ADDR);
	i2c_write(SET_MOTOR);
	i2c_write(move);
	i2c_stop();
}

void dualpob_setDCSpeed(unsigned char speed)
{
	i2c_start_sendaddr(DUALPOB_I2C_ADDR);
	i2c_write(SET_MOTOR_SPEED);
	i2c_write(speed);
	i2c_stop();
}

void dualpob_setIoWay(unsigned char portb, unsigned char porte, unsigned char portf, unsigned portg)
{
	i2c_start_sendaddr(DUALPOB_I2C_ADDR);
	i2c_write(SET_IO_WAY);
	i2c_write(portb);
	i2c_write(porte);
	i2c_write(portf);
	i2c_write(portg);
	i2c_stop();
}

void dualpob_setOutput(DP_OUTPUT_PORT port, DP_OUTPUT_PIN pin)
{
	i2c_start_sendaddr(DUALPOB_I2C_ADDR);
	i2c_write(SET_OUTPUT);
	i2c_write(port);
	i2c_write(pin);
	i2c_stop();
}

void dualpob_clearOutput(DP_OUTPUT_PORT port, DP_OUTPUT_PIN pin)
{
	i2c_start_sendaddr(DUALPOB_I2C_ADDR);
	i2c_write(CLR_OUTPUT);
	i2c_write(port);
	i2c_write(pin);
	i2c_stop();
}

unsigned char dualpob_getInput(DP_INPUT_PORT port,DP_INPUT_PIN pin)
{
	unsigned char input;

	i2c_start_sendaddr(DUALPOB_I2C_ADDR);
	i2c_write(GET_INPUT);
	i2c_write(port);
	i2c_write(pin);
	i2c_stop();

	i2c_start_sendaddr(DUALPOB_I2C_ADDR|1);
	input = i2c_read_noack();
	i2c_stop();

	return input;
}


void dualpob_initServos(void)
{
	//reset the servo board
	i2c_start_sendaddr(DUALPOB_I2C_ADDR);
	i2c_write(RESETPOBSERVO);
	i2c_stop();
}


void dualpob_setServo(unsigned char servo, unsigned char position, unsigned char speed)
{
	if (servo<SERVOS_NUMBER)
	{
		i2c_start_sendaddr(DUALPOB_I2C_ADDR);
		i2c_write(SETONESERVO);
		i2c_write(servo);
		i2c_write(position);
		i2c_write(speed);
		i2c_stop();
	}
}

void dualpob_switchOnServo(UInt8 servo)
{
	i2c_start_sendaddr(DUALPOB_I2C_ADDR);
	i2c_write(SWITCHONONESERVO);
	i2c_write(servo);
	i2c_stop();
}

void dualpob_switchOffServo(UInt8 servo)
{
	i2c_start_sendaddr(DUALPOB_I2C_ADDR);
	i2c_write(SWITCHOFFONESERVO);
	i2c_write(servo);
	i2c_stop();
}

void dualpob_setServoArray( unsigned char *position, unsigned char *speed, unsigned char offset, unsigned char len)
{
	unsigned char i ;

	i2c_start_sendaddr(DUALPOB_I2C_ADDR);
	i2c_write(SETARRAYSERVO);
	i2c_write(offset);
	i2c_write(len);

	for(i=0; i<len ;i++)
	{
		i2c_write(position[i]);
		i2c_write(speed[i]);
	}
	i2c_stop();
}

void dualpob_setServoPosition(unsigned char *position, unsigned char offset,unsigned char len)
{
	unsigned char i ;

	i2c_start_sendaddr(DUALPOB_I2C_ADDR);
	i2c_write(SETARRAYPOSITION);
	i2c_write(offset);
	i2c_write(len);

	for(i=0; i<len ;i++)
	{
		i2c_write(position[i]);	
	}
	i2c_stop();
}

void dualpob_setServoSpeed(unsigned char *speed,unsigned char offset,unsigned char len)
{
	unsigned char i ;

	i2c_start_sendaddr(DUALPOB_I2C_ADDR);
	i2c_write(SETARRAYSPEED);
	i2c_write(offset);
	i2c_write(len);

	for(i=0; i<len ;i++)
	{
		i2c_write(speed[i]);
	}
	i2c_stop();
}

void dualpob_setGlobalSpeed(UInt8 speed)
{
	i2c_start_sendaddr(DUALPOB_I2C_ADDR);
	i2c_write(SETGLOBALSPEED);
	i2c_write(speed);
	i2c_stop();
}


unsigned char dualpob_pobeyeTest(unsigned char data)
{
	unsigned char tmp,i;

	i2c_start_sendaddr(DUALPOB_I2C_ADDR);
	i2c_write(POBEYE_TEST);
	i2c_write(data);
	i2c_stop();
	
	for(i=0;i<5;i++)
	{
		wait_us(10000);
	}

	i2c_start_sendaddr(DUALPOB_I2C_ADDR|1);
	tmp = i2c_read_noack();
	i2c_stop();

	return tmp;
}

void dualpob_setPobeyeForm(unsigned char form)
{
	i2c_start_sendaddr(DUALPOB_I2C_ADDR);
	i2c_write(POBEYE_SET_FORM);
	i2c_write(form);
	i2c_stop();
}

unsigned char dualpob_grabFrame(void)
{
	unsigned char i;
	unsigned char tmp;

	i2c_start_sendaddr(DUALPOB_I2C_ADDR);
	i2c_write(POBEYE_GRAB);
	i2c_stop();

	for(i=0;i<0x30;i++)
	{
		wait_us(10000);
	}
	
	i2c_start_sendaddr(DUALPOB_I2C_ADDR|1);
	tmp = i2c_read_noack();
	i2c_stop();
	
	return tmp;
}

unsigned char dualpob_getPobeyeForm(unsigned char *x,unsigned char *y,unsigned char *w,unsigned char *h)
{
	unsigned char form,i;

	i2c_start_sendaddr(DUALPOB_I2C_ADDR);
	i2c_write(POBEYE_GET_FORM);
	i2c_stop();

	for(i=0;i<0x10;i++)
	{
		wait_us(10000);
	}

	i2c_start_sendaddr(DUALPOB_I2C_ADDR|1);
	form = i2c_read_ack();
	*x = i2c_read_ack();
	*y = i2c_read_ack();
	*w = i2c_read_ack();
	*h = i2c_read_noack();
	i2c_stop();

	return form;
}