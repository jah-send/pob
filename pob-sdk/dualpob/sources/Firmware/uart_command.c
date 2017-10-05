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

#include <stdio.h>

#include "communication.h"

//all uart protocol comes from rgbandservo source code



/* uart protocol format:
 *
 * command format: <command string><space char><parameters0 string><space char><parameters1...><cr><lf>
 *
 * answer format: <answer string><cr><lf>
 *
 */

#define CMD_POB		"POB"		/* simple test */
#define CMD_M_SPEED "MOTORSPEED" /* set motor speed */
#define CMD_RUN		"RUN"		/* pob-bot run */
#define CMD_BACK	"BACK"		/* pob-bot back */
#define CMD_LEFT	"LEFT"		/* pob-bot left */
#define CMD_RIGHT	"RIGHT"		/* pob-bot right */
#define CMD_STOP	"STOP"		/* pob-bot stop */
#define CMD_SERVO	"SERVO"		/* set servomotor position, parameters: servo_value position_value speed_value */
#define CMD_TYPE	"TYPE"		/* set type of servomotor for the 'SERVO' command: BIOLOID or DUALPOB */
#define CMD_GO		"GO"		/* move 18 bioloid servomotor (position must be set with SAVE command */
#define CMD_SAVE	"SAVE"		/* get movement of 18 bioloid servomotor and save it to ram */
#define CMD_SPEED	"SPEED"		/* set speed of 18 servomotor */
#define CMD_TEST	"TEST"		/* run dualpob test program */
#define CMD_SETAX	"SETAX12"	/* set ax-12 id */
#define CMD_ANA		"ANA"		/* read analog input */
#define CMD_EXIT	"EXIT"		/* exit uart protocol */

/* uart command parameters:
 *
 */

#define ON			"ON"		/* activate a command */
#define OFF			"OFF"		/* deactivate a command */

#define BIOLOID_S	"BIOLOID"	/* select bioloid servomotor */
#define DUALPOB_S	"DUALPOB"	/* select dualpob servomotor */

/* uart answer
 *
 */

#define OK				"OK"	/* last operation successfull */
#define FAILED			"NOK"	/* last operation failed */
#define UNKNOWN			"?"		/* unknown command */


/* program parameters
 *
 */

#define UART_BUFFER_SIZE 255	/* uart buffer size */
#define STR_NUMBER		 24		/* string number */
#define SERVO_NUMBER	 18		/* servomotor number */

/**< pob servo type */
typedef enum _pob_servo
{
	UNKNOWN_SERVO=1,	/**< unknown servomotor */
	DUALPOB_SERVO=2,	/**< dualpob servomotor */
	BIOLOID_SERVO=3		/**< bioloid servomotor */
} SERVO_TYPE;



/** move servomtor
 *
 * @param t 			Type of servomotor 
 * @param identifier	Servomotor identifier
 * @param position		position
 * @param speed			speed
 */
static void SetAndMoveServo(SERVO_TYPE t,UInt8 identifier,UInt16 position,UInt16 speed);


//public functions:

/**< run test program on the dual-pob */
extern void RunTestProgram(void);

/**< uart command process */
void ProcessUARTCommand(UInt8 data)
{
	UInt8 	i,k;
	UInt8 	exit = 0;

	UInt8 	uartBuffer[UART_BUFFER_SIZE];	//uart buffer
	UInt8 	uartSize;						//number of byte receive from uart

	Int8 	stringNumber=0;					//number of string in buffer
	String 	string[STR_NUMBER];				//string buffer
	
	SERVO_TYPE tServo = UNKNOWN_SERVO;		//servomotor type

	UInt8   anaChannel;
	UInt16  anaValue;

	UInt8 	servo;
	UInt16 	position=0,speed=0;

	UInt16 	frame_current=0;
	UInt16 	frames[SERVO_NUMBER];

	UInt8 	first=1;
	UInt8 	offset=1;

	int 	result=0;

	

	//uart main loop
	while(exit==0)
	{
		offset=0;

		if(first==1)
		{
			//first uart command
			offset=1;
			uartBuffer[0]=data;
			first=0;
		}

		//receive user command
		uartSize=receive(uartBuffer,UART_BUFFER_SIZE,offset);

		//extract the user command and parameters from the uart buffer
		stringNumber=extractString(string,STR_NUMBER,uartBuffer,uartSize);


		//POB
		if(strCmp(CMD_POB,string[0].buffer,string[0].len)==1)
		{
			//simple test
			send(OK);
		}
		//EXIT
		else if(strCmp(CMD_EXIT,string[0].buffer,string[0].len)==1)
		{
			exit=1;
			send(OK);
		}
		//TEST
		else if(strCmp(CMD_TEST,string[0].buffer,string[0].len)==1)
		{
			RunTestProgram();
		}
		//SPEED
		else if(strCmp(CMD_M_SPEED,string[0].buffer,string[0].len)==1)
		{
			if(stringNumber==2)
			{
				sscanf((char *)string[1].buffer,"%d",&servo);

				SetDCSpeed(servo);

				send(OK);
			}
			else
			{
				send(FAILED);
			}
		}
		//RUN
		else if(strCmp(CMD_RUN,string[0].buffer,string[0].len)==1)
		{
			
			SetDCMotor(DC_MOTOR_RUN);

			send(OK);
		}
		//LEFT
		else if(strCmp(CMD_LEFT,string[0].buffer,string[0].len)==1)
		{
			
			SetDCMotor(DC_MOTOR_LEFT);

			send(OK);
		}
		//RIGHT
		else if(strCmp(CMD_RIGHT,string[0].buffer,string[0].len)==1)
		{
			
			SetDCMotor(DC_MOTOR_RIGHT);

			send(OK);
		}
		//BACK
		else if(strCmp(CMD_BACK,string[0].buffer,string[0].len)==1)
		{
			
			SetDCMotor(DC_MOTOR_BACK);

			send(OK);
		}
		//STOP
		else if(strCmp(CMD_STOP,string[0].buffer,string[0].len)==1)
		{
			
			SetDCMotor(DC_MOTOR_STOP);

			send(OK);
		}
		//ANA analog_channel
		else if(strCmp(CMD_ANA,string[0].buffer,string[0].len)==1)
		{
			if(stringNumber==2)
			{
				sscanf((char *)string[1].buffer,"%d",&anaChannel);

				anaValue = GetAnalog(anaChannel);

				sprintf(uartBuffer,"%d",anaValue);

				send(uartBuffer);
			}
			else
			{
				send(FAILED);
			}
		}
		//TYPE type_of_servo
		else if(strCmp(CMD_TYPE,string[0].buffer,string[0].len)==1)
		{
			if(stringNumber==2)
			{
				if(strCmp(BIOLOID_S,string[1].buffer,string[1].len)==1)
				{
					tServo=BIOLOID_SERVO;

					send(OK);
				}
				else if(strCmp(DUALPOB_S,string[1].buffer,string[1].len)==1)
				{
					tServo=DUALPOB_SERVO;

					send(OK);
				}
				else
				{
					send(FAILED);
				}
				
			}
			else
			{
				send(FAILED);
			}
		}
		//SERVO servo_id position 
		//SERVO servo_id position speed
		else if(strCmp(CMD_SERVO,string[0].buffer,string[0].len)==1)
		{	

			if(tServo==UNKNOWN_SERVO)
			{
				send(FAILED);
			}

			if(stringNumber==3)
			{
				//get servo and position
				sscanf((char *)string[1].buffer,"%d",&servo);
				sscanf((char *)string[2].buffer,"%d",&position);

				if(tServo==BIOLOID_SERVO)
					speed=100;
				else
					speed=1;

				SetAndMoveServo(tServo,servo,position,speed);

				send(OK);
			}
			else if(stringNumber==4)
			{
				//get servo, position and speed
				sscanf((char *)string[1].buffer,"%d",&servo);
				sscanf((char *)string[2].buffer,"%d",&position);
				sscanf((char *)string[3].buffer,"%d",&speed);

				SetAndMoveServo(tServo,servo,position,speed);
				
			}
			else
			{
				send(FAILED);
			}
		}
		//SETAX12 servo_id
		else if(strCmp(CMD_SETAX,string[0].buffer,string[0].len)==1)
		{
			if(stringNumber==2)
			{
				sscanf((char *)string[1].buffer,"%d",&servo);

				result=0;
				for(i=0;i<253;i++)
				{
					if(PingAx12(i)==1)
					{
						result++;
					}
				}
							
				if(result<2)
				{
					SetAx12Id(servo);

					send(OK);
				}
				else
				{
					send(FAILED);
				}
			}
			else
			{
				send(FAILED);
			}
		}
		//SAVE frame_number position1 ... positionX
		else if(strCmp(CMD_SAVE,string[0].buffer,string[0].len)==1)
		{
			if(stringNumber>=2)
			{
				//get current frame
				if(string[1].len==1&&string[1].buffer[0]=='0')
					frame_current=0;
				else
					sscanf((char *)string[1].buffer,"%d",&frame_current);

				//get servomotor position from strin buffer
				for(i=2,k=0;i<stringNumber;i++,k++)
				{
					if(k==SERVO_NUMBER)
						break;

					if(string[i].len==1&&string[i].buffer[0]=='0')
						frames[k]=0;
					else
					 	result=sscanf((char *)string[i].buffer,"%d", &frames[k] );

					if(result==0)
						frames[k]=0;
				}

				//TODO save current frame to eeprom with current frame index?


				send(OK);
			}
			else
			{
				send(FAILED);
			}
		}
		//GO
		else if(strCmp(CMD_GO,string[0].buffer,string[0].len)==1)
		{

			for(k=0;k<18;k++)
			{						
				if(frames[k]==0xFFFF)
				{
					GetAx12Position(k+1,&frames[k]);
					
				}
			}

			SetAx12Movement(frames,18,100);

			send(OK);
		}
		//unknown command
		else
		{
			send(UNKNOWN);
		}


		//reset string buffer
		string[0].len=0;
		string[0].buffer[0]=0;
		string[1].len=0;
		string[1].buffer[0]=0;



	}
}

static void SetAndMoveServo(SERVO_TYPE t,UInt8 identifier,UInt16 position,UInt16 speed)
{
	
	switch(t)
	{
		case UNKNOWN_SERVO:

		break;

		case BIOLOID_SERVO:

			//first, send position and speed
			SetAx12Position(identifier,position,speed);
			//then, move servomotor
			MoveAx12();

		break;

		case DUALPOB_SERVO:

		//	SwitchOnServo(identifier);

			SetServo(identifier,position,speed);

		break;
	}

}
