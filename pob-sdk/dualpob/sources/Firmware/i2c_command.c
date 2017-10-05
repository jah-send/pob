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
#include <dual-pob.h>


#include "config.h"


//get/set macro
#define i2c_get(data)	while( ReadOnI2CSlave(&data)==0)

#define i2c_set(data)	PrepareWriteOnI2CSlave(data);while(IsWriteOnI2COk()==0) 

//pobeye command firmware:

#define POBEYE_COMMAND_ECHO		0x00 //test communication
#define POBEYE_COMMAND_GRAB		0x01 //grab a new frame
#define POBEYE_COMMAND_SETFORM 	0x02 //set form
#define POBEYE_COMMAND_GETFORM	0x03 //get form
#define POBEYE_COMMAND_GRAB_NO_ACK 0x04 //grab new frame, no ack

//private variable

static UInt8 portb_conf = IO_AS_DEFAULT ;
static UInt8 porte_conf = IO_AS_DEFAULT ;
static UInt8 portf_conf = IO_AS_DEFAULT ;
static UInt8 portg_conf = IO_AS_DEFAULT ;

//private functions:

void SetIOAsOutput(UInt8 port,UInt8 pin)
{
	UInt8 tmp = IO_AS_OUTPUT << pin;

	switch(port)
	{
		case 0:
			//PORTB
			portb_conf |= tmp;
			break;
		case 1:
			//PORTE
			porte_conf |= tmp;
			break;
		case 2:
			//PORTF
			portf_conf |= tmp;
			break;
		case 3:
			//PORTG
			portg_conf |= tmp;
			break;
	}

	SetIOWay(portb_conf,porte_conf,portf_conf,portg_conf);
}


//public functions:

void ProcessI2cCommand(UInt8 command)
{
	UInt8 tmpA,tmpB,tmpC,tmpD,tmpE;
	UInt8 i;
	
	UInt16 bioloid_pos,bioloid_speed;

	UInt16 analog;	

//	UInt8 buff[2];


	//--------------------------- command switch:
	switch(command)
	{
		//--------------------------- simple echo command
		case ECHO:
			i2c_get(tmpA);

			i2c_set(tmpA+1);
		break;
		//--------------------------- set one servo
		case SETONESERVO:
			i2c_get(tmpA);
			i2c_get(tmpB);
			i2c_get(tmpC);

			SetServo(tmpA,tmpB,tmpC);

		break;
		//--------------------------- power on 
		case SWITCHONONESERVO:
			i2c_get(tmpA);

			SwitchOnServo(tmpA);
		break;
		//--------------------------- power off
		case SWITCHOFFONESERVO:
			i2c_get(tmpA);

			SwitchOffServo(tmpA);
		break;
		//---------------------------  set servomotors (position+speed) array
		case SETARRAYSERVO:
			i2c_get(tmpA);
			i2c_get(tmpB);

			for(i=0;i<tmpB;i++)
			{
				i2c_get(position[i]);
				i2c_get(speed[i]);
			}
			SetServoArray(position,speed,tmpA,tmpB);
			
		break;
		//---------------------------  get position 
		case GETCURRENTPOS:
			//TODO

		break;
		//---------------------------  set servomotors (only position) array 
		case SETARRAYPOSITION:
			i2c_get(tmpA);
			i2c_get(tmpB);

			for(i=0;i<tmpB;i++)
			{
				i2c_get(position[i]);
			}
			SetServoPosition(position,tmpA,tmpB);

		break;
		//---------------------------  set servomotors (only speed) array 
		case SETARRAYSPEED:
			i2c_get(tmpA);
			i2c_get(tmpB);

			for(i=0;i<tmpB;i++)
			{
				i2c_get(speed[i]);
			}
			SetServoSpeed(speed,tmpA,tmpB);

		break;
		//---------------------------  set speed for all servomotors
		case SETGLOBALSPEED:
			i2c_get(tmpA);

			SetGlobalSpeed(tmpA);
		break;
		//---------------------------  init/reset dualservo
		case RESETPOBSERVO:
			
			InitDualServo();

		break;
		//---------------------------  set ax12 servomotor
		case SET_AX12_SERVO:
			
			i2c_get(tmpA);

			i2c_get(tmpB);
			i2c_get(tmpC); 
			bioloid_pos = tmpC | (tmpB<<8);

			i2c_get(tmpC);
			i2c_get(tmpB);
			bioloid_speed = tmpB | (tmpC<<8);


			SetAx12Position(tmpA,bioloid_pos,bioloid_speed);
			MoveAx12();

		break;
		//--------------------------- ping ax12 servomotor
		case PING_AX12:
			i2c_get(tmpA);

			tmpB = PingAx12(tmpA);

			i2c_set(tmpB);

		break;
		//--------------------------- get analog value
		case GET_ANALOG:

			i2c_get(tmpA);

			analog = GetAnalog(tmpA);

			i2c_set(analog>>2);
		break;
		//--------------------------- configure pwm
		case SET_PWM:
			
			i2c_get(tmpA);
			i2c_get(tmpB);
			i2c_get(tmpC);

			SetPwm(tmpA,tmpB,tmpC);
		break;
		//---------------------------  set movement for dc motor
		case SET_MOTOR:

			i2c_get(tmpA);

			SetDCMotor(tmpA);
		break;
		//---------------------------  set motor speed
		case SET_MOTOR_SPEED:
			
			i2c_get(tmpA);

			SetDCSpeed(tmpA);
		break;
		//---------------------------  configure i/o
		case SET_IO_WAY:
			i2c_get(tmpA);
			i2c_get(tmpB);
			i2c_get(tmpC);
			i2c_get(tmpD);

			//reset io configuration
			portb_conf = tmpA;
			porte_conf = tmpB;
			portf_conf = tmpC;
			portg_conf = tmpD;
			SetIOWay(tmpA, tmpB, tmpC, tmpD);

		break;
		//---------------------------  set output pin
		case SET_OUTPUT:
			
			i2c_get(tmpA);
			i2c_get(tmpB);

			SetIOAsOutput(tmpA,tmpB);

			switch(tmpA)
			{
				case 0:
					SetOutput(PORTB,tmpB);
					break;
				case 1:
					SetOutput(PORTE,tmpB);
					break;
				case 2:
					SetOutput(PORTF,tmpB);
					break;
				case 3:
					SetOutput(PORTG,tmpB);
					break;
			}
			
		break;
		//---------------------------  clear output pin
		case CLR_OUTPUT:

			i2c_get(tmpA);
			i2c_get(tmpB);

			SetIOAsOutput(tmpA,tmpB);

			switch(tmpA)
			{
				case 0:
					ClearOutput(PORTB,tmpB);
					break;
				case 1:
					ClearOutput(PORTE,tmpB);
					break;
				case 2:
					ClearOutput(PORTF,tmpB);
					break;
				case 3:
					ClearOutput(PORTG,tmpB);
					break;
			}

		break;
		//---------------------------  get input pin
		case GET_INPUT:
			i2c_get(tmpA);
			i2c_get(tmpB);

			tmpC = GetInput(tmpA,tmpB);

			i2c_set(tmpC);
		break;
		//--------------------------- test pobeye
		case POBEYE_TEST:

			i2c_get(tmpA);


			tmpB=0;
			SetByteToPOBEYE(POBEYE_COMMAND_ECHO);
			SetByteToPOBEYE(tmpA);

//			SendString(" \n\rtmpA=");
//			Bin2Hex(tmpA,buff);
//			SendBufferToUART0(buff,2);

			tmpB = GetByteFromPOBEYE();
			
//			SendString(" tmpB=");
//			Bin2Hex(tmpB,buff);
//			SendBufferToUART0(buff,2);

			i2c_set(tmpB);

		break;
		//--------------------------- grab a frame (no ack)
		case POBEYE_GRAB_NO_ACK:
			
			SetByteToPOBEYE(POBEYE_COMMAND_GRAB_NO_ACK);

			break;
		//--------------------------- grab a frame 
		case POBEYE_GRAB:

			SetByteToPOBEYE(POBEYE_COMMAND_GRAB);

			tmpA = GetByteFromPOBEYE();
			i2c_set(tmpA);
			
		break;
		//--------------------------- define pattern form
		case POBEYE_SET_FORM:

			i2c_get(tmpA);

			SetByteToPOBEYE(POBEYE_COMMAND_SETFORM);
			SetByteToPOBEYE(tmpA);

		break;
		//--------------------------- get form
		case POBEYE_GET_FORM:

			SetByteToPOBEYE(POBEYE_COMMAND_GETFORM);
			tmpA = GetByteFromPOBEYE(); //form yes no ?
			tmpB = GetByteFromPOBEYE(); //x
			tmpC = GetByteFromPOBEYE(); //y
			tmpD = GetByteFromPOBEYE(); //w
			tmpE = GetByteFromPOBEYE(); //h

//			Bin2Hex(tmpA,buff);
//			SendBufferToUART0(buff,2);
//			SendByteToUART0(' ');


//			Bin2Hex(tmpE,buff);
//			SendBufferToUART0(buff,2);
//			SendByteToUART0(' ');

			i2c_set(tmpA);
			i2c_set(tmpB);
			i2c_set(tmpC);
			i2c_set(tmpD);
			i2c_set(tmpE);

		break;

		default:

		break;
	}

}
