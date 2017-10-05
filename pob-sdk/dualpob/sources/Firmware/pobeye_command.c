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


//global menbers:

UInt8 position[SERVOS_NUMBER];
UInt8 speed[SERVOS_NUMBER];



//public functions:


/**< pob-eye process command */
void ProcessPobeyeCommand(UInt8 command)
{
//	UInt8 len;
//	UInt8 string[2];

	UInt8 tmpA,tmpB,tmpC,tmpD,tmpE;
	UInt8 i;
	
	UInt16 bioloid_pos,bioloid_speed;

	UInt16 analog;	
	
	//--------------------------- command switch:
	switch(command)
	{
		//--------------------------- simple echo command
		case ECHO:
			tmpA=GetByteFromPOBEYE();

		//	Bin2Hex(tmpA,string);
		//	SendBufferToUART0(string,2);
		//	SendString("\n\r");

			SetByteToPOBEYE(tmpA+1);
		break;
		//--------------------------- set one servo
		case SETONESERVO:
			tmpA=GetByteFromPOBEYE();
			tmpB=GetByteFromPOBEYE();
			tmpC=GetByteFromPOBEYE();

			SetServo(tmpA,tmpB,tmpC);

		break;
		//--------------------------- power on 
		case SWITCHONONESERVO:
			tmpA=GetByteFromPOBEYE();

			SwitchOnServo(tmpA);
		break;
		//--------------------------- power off
		case SWITCHOFFONESERVO:
			tmpA=GetByteFromPOBEYE();

			SwitchOffServo(tmpA);
		break;
		//--------------------------- set servomotors (position+speed) array
		case SETARRAYSERVO:
			tmpA=GetByteFromPOBEYE();
			tmpB=GetByteFromPOBEYE();

			for(i=0;i<tmpB;i++)
			{
				position[i]=GetByteFromPOBEYE();
				speed[i]=GetByteFromPOBEYE();
			}
			SetServoArray(position,speed,tmpA,tmpB);
			
		break;
		// get position 
		case GETCURRENTPOS:
			//TODO

		break;
		//--------------------------- set servomotors (only position) array 
		case SETARRAYPOSITION:
			tmpA=GetByteFromPOBEYE();
			tmpB=GetByteFromPOBEYE();

			for(i=0;i<tmpB;i++)
			{
				position[i]=GetByteFromPOBEYE();
			}
			SetServoPosition(position,tmpA,tmpB);

		break;
		//--------------------------- set servomotors (only speed) array 
		case SETARRAYSPEED:
			tmpA=GetByteFromPOBEYE();
			tmpB=GetByteFromPOBEYE();

			for(i=0;i<tmpB;i++)
			{
				speed[i]=GetByteFromPOBEYE();
			}
			SetServoSpeed(position,tmpA,tmpB);

		break;
		//--------------------------- set speed for all servomotors
		case SETGLOBALSPEED:
			tmpA=GetByteFromPOBEYE();

			SetGlobalSpeed(tmpA);
		break;
		//--------------------------- init/reset dualservo
		case RESETPOBSERVO:
			
			InitDualServo();

		break;
		//--------------------------- set ax12 identifier
		case SET_AX12_ID:
			tmpA = GetByteFromPOBEYE();

			if(tmpA>0&&tmpA<253)
			{
				SetAx12Id(tmpA);
			}
		break;
		//--------------------------- set ax12 servomotor
		case SET_AX12_SERVO:
			
			tmpA = GetByteFromPOBEYE();

			tmpB = GetByteFromPOBEYE();
			bioloid_pos = GetByteFromPOBEYE() | (tmpB<<8);

			tmpC = GetByteFromPOBEYE();
			bioloid_speed = GetByteFromPOBEYE() | (tmpC<<8);

			SetAx12Position(tmpA,bioloid_pos,bioloid_speed);
			MoveAx12();

		break;
		//--------------------------- ping ax12 servomotor
		case PING_AX12:
			tmpA = GetByteFromPOBEYE();

			tmpB = PingAx12(tmpA);

			SetByteToPOBEYE(tmpB);

		break;
		//--------------------------- get analog value
		case GET_ANALOG:

			tmpA = GetByteFromPOBEYE();

			analog = GetAnalog(tmpA);

			SetByteToPOBEYE(analog>>2);
		break;
		//--------------------------- configure pwm
		case SET_PWM:
			
			tmpA = GetByteFromPOBEYE();
			tmpB = GetByteFromPOBEYE();
			tmpC = GetByteFromPOBEYE();

			SetPwm(tmpA,tmpB,tmpC);
		break;
		//--------------------------- set movement for dc motor
		case SET_MOTOR:

			tmpA = GetByteFromPOBEYE();

			SetDCMotor(tmpA);
		break;
		//--------------------------- set motor speed
		case SET_MOTOR_SPEED:
			
			tmpA = GetByteFromPOBEYE();

			SetDCSpeed(tmpA);
		break;
		//--------------------------- configure i/o
		case SET_IO_WAY:
			tmpA= GetByteFromPOBEYE();
			tmpB= GetByteFromPOBEYE();
			tmpC= GetByteFromPOBEYE();
			tmpD= GetByteFromPOBEYE();

			SetIOWay(tmpA, tmpB, tmpC, tmpD);

		break;
		//--------------------------- set output pin
		case SET_OUTPUT:
			
			tmpA = GetByteFromPOBEYE();
			tmpB = GetByteFromPOBEYE();

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
		//--------------------------- clear output pin
		case CLR_OUTPUT:

			tmpA = GetByteFromPOBEYE();
			tmpB = GetByteFromPOBEYE();

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
		//--------------------------- get input pin
		case GET_INPUT:
			tmpA = GetByteFromPOBEYE();
			tmpB = GetByteFromPOBEYE();

			tmpC = GetInput(tmpA,tmpB);

			SetByteToPOBEYE(tmpC);
		break;
		default:

		break;
	}
}
