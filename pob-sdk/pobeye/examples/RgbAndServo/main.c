/*
 * Copyright 2007 POB-Technology. All rights reserved.
 * POB-Technology PROPRIETARY/CONFIDENTIAL.
 * 
 * RGB AND SERVO program
 */

#include <stdlib.h>

#include <pob-eye.h>

#include "communication.h"

/*
#if 1
extern "C" int isatty(int fd)
{
	return 1;
}
#endif*/

/* uart command:
 *
 * command format: <command string><space char><parameters0 string><space char><parameters1...><cr><lf>
 *
 * answer format: <answer string><cr><lf>
 *
 */

#define CMD_POB		"POB"		/* simple test */
#define CMD_RGB		"RGB"		/* grab a rgb frame */
#define CMD_HSL		"HSL"		/* grab a hsl frame */
#define CMD_COMPRESS "COMPRESS" /* compress frame component, parameters: ON/OFF */
#define CMD_RUN		"RUN"		/* pob-bot run */
#define CMD_BACK	"BACK"		/* pob-bot back */
#define CMD_LEFT	"LEFT"		/* pob-bot left */
#define CMD_RIGHT	"RIGHT"		/* pob-bot right */
#define CMD_STOP	"STOP"		/* pob-bot stop */
#define CMD_SEND	"SEND"		/* send frame, parameters: RED/GREEN/BLUE/HUE/SATURATION/LIGHT */
#define CMD_CAM		"CAMERA"	/* set camera parameters, parameters: CONTRAST/BRIGHTNESS value */
#define CMD_SERVO	"SERVO"		/* set servomotor position, parameters: servo_value position_value */
#define CMD_LCD		"LCD"		/* draw camera frame, parameters: ON */

/* uart command parameters:
 *
 */

#define RED			"RED"		/* red frame */
#define GREEN		"GREEN"		/* green frame */
#define BLUE		"BLUE"		/* blue frame */

#define HUE			"HUE"		/* hue frame */
#define SATURATION	"SATURATION"/* saturation frame */
#define LIGHT		"LIGHT"		/* light frame */

#define CONTRAST	"CONTRAST"	/* camera contrast */
#define	BRIGTHNESS	"BRIGHTNESS"/* camera brigthness */

#define ON			"ON"		/* activate a command */
#define OFF			"OFF"		/* deactivate a command */


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
#define STR_NUMBER		 4		/* string number */


/* utils functions
 *
 */

//pob-proto init
static UInt8 pobProtoOk=0;
static void InitPobProto (void);

//pob-bot movement
#define MOVE_RUN		0x05
#define MOVE_BACK		0x0A
#define MOVE_LEFT		0x09
#define MOVE_RIGHT		0x06
#define STOP_BOT		0

//pob-bot move 
static void MoveBot(UInt8 Way);

//set servomotor
static void SetServoRgb(UInt8 servo, UInt8 position);

//lcd fast buffer video
static UInt8 LCD_Fast_Buffer[64*64*BYTES];
static GraphicBuffer LCD_Fast_Buffer_Video;

//draw camera frame
static void DrawVision (RGBFrame *FrameFromCam);

//debug to convert int->char
static void IntToChar(UInt32 value);


/* main program
 *
 */
int main(void)
{
	int i=0,j=0;

	UInt8 uartBufferSize=UART_BUFFER_SIZE;	//uart buffer size
	UInt8 uartBuffer[UART_BUFFER_SIZE];		//uart buffer
	UInt8 uartSize;							//number of byte receive from uart

	UInt8 stringMax=STR_NUMBER;	//string buffer size
	Int8 stringNumber=0;		//number of string in buffer
	String string[STR_NUMBER];	//string buffer

	RGBFrame FrameFromCam;		//RGB frame pointer
	HSLFrame FrameFromCam2 ;	//HSL frame pointer


	UInt8 CompressedComponentOk = 0;//flag to active frame compression
	UInt8 PrintFrameOnLcd = 0;		//flag to draw camera frame
	UInt8 ComponentOk = 0 ;			//flag to send camera frame


	//identify variable
//	UInt8 Nb_Identify=0;
//	Form  ListOfForm[MAX_OF_FORM];

	
	int offset,div,last;

	UInt8 *ComponentPointer;	//pointer to a camera frame 

	UInt8 compressed_byte=0;	//temporary byte


	int wh = WIDTH_FRAME*HEIGHT_FRAME;

	int servo,position,temp;

	
	div = wh/255;
	last = wh - div*255;


	//init POB-EYE
	InitPOBEYE();

	//init UART
	InitUART((UInt16)(BR_115200|NO_PARITY|ONE_STOP_BIT|LENGTH_8_BIT));

	//get the pointer of the red,green and blue video buffer
	GetPointerOnRGBFrame(&FrameFromCam);

	//get the pointer on the HSL frame buffer
	GetPointerOnHSLFrame(&FrameFromCam2);


	//main loop program
	while(1)
	{
		//receive user command
		uartSize=receive(uartBuffer,uartBufferSize);

		//extract the user command and parameters from the uart buffer
		stringNumber=extractString(string,stringMax,uartBuffer,uartSize);

		//command switch:

		if(strCmp(CMD_POB,string[0].buffer,string[0].len)==1)
		{
			//simple test
			send(OK);
		}
		else if(strCmp(CMD_RGB,string[0].buffer,string[0].len)==1)
		{
			//grab a frame from camera sensor
			GrabRGBFrame();

			send(OK);
		}
		else if(strCmp(CMD_HSL,string[0].buffer,string[0].len)==1)
		{
			//grab hsl frame
			GrabRGBFrame();
			GetHSLFrame(&FrameFromCam2);

			send(OK);
		}
		else if(strCmp(CMD_COMPRESS,string[0].buffer,string[0].len)==1)
		{
			//compress camera frame
			if(strCmp(ON,string[1].buffer,string[1].len)==1)
			{
				CompressedComponentOk=1;
				send(OK);
			}
			else if(strCmp(OFF,string[1].buffer,string[1].len)==1)
			{
				CompressedComponentOk=0;
				send(OK);
			}
			else
			{
				send(FAILED);
			}
		}
		else if(strCmp(CMD_RUN,string[0].buffer,string[0].len)==1)
		{
			//move bot
			MoveBot( MOVE_RUN );

			send(OK);
		}
		else if(strCmp(CMD_BACK,string[0].buffer,string[0].len)==1)
		{
			//move back the pob-bot
			MoveBot( MOVE_BACK );

			send(OK);
		}
		else if(strCmp(CMD_LEFT,string[0].buffer,string[0].len)==1)
		{
			//move left the pob-bot
			MoveBot( MOVE_LEFT );

			send(OK);
		}
		else if(strCmp(CMD_RIGHT,string[0].buffer,string[0].len)==1)
		{
			//move right the pob-bot
			MoveBot( MOVE_RIGHT );

			send(OK);
		}
		else if(strCmp(CMD_STOP,string[0].buffer,string[0].len)==1)
		{
			//stop pob-bot
			MoveBot( STOP_BOT );

			send(OK);
		}
		else if(strCmp(CMD_SERVO,string[0].buffer,string[0].len)==1)
		{	
			if(stringNumber==3)
			{
				//get servo and position
				servo=(UInt8)strtol((const char*)string[1].buffer,(char **)'\0',10);
				position=(UInt8)strtol((const char*)string[2].buffer,(char **)'\0',10);

				//set servo
				SetServoRgb(servo,position);

				send(OK);
			}
			else
			{
				send(FAILED);
			}
		}
		else if(strCmp(CMD_CAM,string[0].buffer,string[0].len)==1)
		{
			//receive camera orders
			if(stringNumber==3)
			{
				//get camera value
				temp=strtol((const char*)string[2].buffer,(char **)'\0',10);

				//set camera configuration
				if(strCmp(SATURATION,string[1].buffer,string[1].len)==1)
				{
					SendToCam( 0x03,temp);
				}
				else if(strCmp(CONTRAST,string[1].buffer,string[1].len)==1)
				{
					SendToCam( 0x05,temp);
				}
				else if(strCmp(BRIGTHNESS,string[1].buffer,string[1].len)==1)
				{
					SendToCam( 0x06,temp);
				}

				//wait before camera is ok
				for(i=0;i<0xFFFF;i++);	
				for(i=0;i<0xFFFF;i++);

				send(OK);
			}
			else
			{
				send(FAILED);
			}
		}
		else if(strCmp(CMD_SEND,string[0].buffer,string[0].len)==1)
		{
			//receive frame type
			if(stringNumber==2)
			{
				//get frame type
				if(strCmp(RED,string[1].buffer,string[1].len)==1)
				{
					ComponentPointer = FrameFromCam.red;
					ComponentOk = 1 ;
				}
				else if(strCmp(GREEN,string[1].buffer,string[1].len)==1)
				{
					ComponentPointer = FrameFromCam.green;
					ComponentOk = 1 ;
				}
				else if(strCmp(BLUE,string[1].buffer,string[1].len)==1)
				{
					ComponentPointer = FrameFromCam.blue;
					ComponentOk = 1 ;
				}
				else if(strCmp(HUE,string[1].buffer,string[1].len)==1)
				{
					ComponentPointer = FrameFromCam2.hue;
					ComponentOk = 1 ;
				}
				else if(strCmp(SATURATION,string[1].buffer,string[1].len)==1)
				{
					ComponentPointer = FrameFromCam2.saturation;
					ComponentOk = 1 ;
				}
				else if(strCmp(LIGHT,string[1].buffer,string[1].len)==1)
				{
					ComponentPointer = FrameFromCam2.light;
					ComponentOk = 1 ;
				}
				else
				{
					send(FAILED);
					ComponentOk = 0 ;
				}
			}
			else
			{
				send(FAILED);
				ComponentOk = 0 ;
			}
		}
		else if(strCmp(CMD_LCD,string[0].buffer,string[0].len)==1)
		{
			//lcd test
			if(stringNumber==2)
			{
				if(strCmp(ON,string[1].buffer,string[1].len)==1)
				{
					//init the pob-lcd
					InitLCD(); 
					//init the graphic buffer video: 64 x 64 pixels
					InitGraphicBuffer(&LCD_Fast_Buffer_Video,64,64,EIGHT_BITS,LCD_Fast_Buffer);
					//clear graphic buffer
					ClearGraphicBuffer(&LCD_Fast_Buffer_Video);

					//while no byte from uart, draw camera frame on lcd
					while(GetByteFromUARTNoWait(&PrintFrameOnLcd)==0)
					{
						GrabRGBFrame();
						BinaryRGBFrame(&FrameFromCam);

						DrawVision(&FrameFromCam);
					}

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
		else
		{
			send(UNKNOWN);
		}

		//send frame component
		if(ComponentOk==1)
		{
			if( CompressedComponentOk == 0)
			{
				//send buffer

		//		offset=0;
		//		for(i=0;i<div;i++)
		//		{
		//			for(j=0;j<255;j++)
		//			{
		//				SendByteToUART(ComponentPointer[offset+j]);
		//			}

		//			GetByteFromUART();

		//			offset+=255;
		//		}

		//		SendBufferToUART(ComponentPointer+offset,last);

				for (i=0,j=0; i < wh ; i++,j++)
				{
					SendByteToUART( ComponentPointer[i]);
			
					//pob-eye crash if you send to many byte

					if(j==255)
					{
						j=0;
						GetByteFromUART();
					}
				}

				ComponentOk = 0 ;
			}
			else if( CompressedComponentOk == 1)
			{
				//send buffer
				for (i=0,j=0; i < wh ; i=i+2,j++)
				{
					compressed_byte = (ComponentPointer[i]&0xF0) | ( ComponentPointer[i+1]>>4);
			
					SendByteToUART(compressed_byte);
			
					//pob-eye crash if you send to many byte
					if(j==255)
					{
						j=0;
						GetByteFromUART();
					}
				}

				ComponentOk=0;
			}

			send(OK);
		}


		//reset string buffer
		string[0].len=0;
		string[0].buffer[0]=0;
		string[1].len=0;
		string[1].buffer[0]=0;
	}

	return 0;
}


void IntToChar(UInt32 value)
{
	UInt8 bCount, bPrinted;
	UInt32 lTmp,lDigit;

	bPrinted = 0;

	lDigit = 1000000000L;
	for(bCount = 0; bCount < 9; bCount++)
	{
		lTmp = (UInt8)(value/lDigit);
		if(lTmp) 
		{
			SendByteToUART(((UInt8)lTmp)+'0');
			bPrinted = 1;
		}
		else if(bPrinted) SendByteToUART(((UInt8)lTmp)+'0');
	
		value -= ((long)lTmp)*lDigit;
		lDigit = lDigit/10;
	}

	lTmp = (UInt8)(value/lDigit);
  
	/*if(lTmp)*/ SendByteToUART(((UInt8)lTmp)+'0');

}

//Function to initialize the POB-PROTO board
void InitPobProto (void)
{
	PobProto	Proto; // struct to set the pob-proto
	
	Proto.porta=ALL_PORTA_AS_ANA;	//to get the position of the analogic joystick, you have to set the PORTA as analogic input
	Proto.portc=RC7_AS_SERVO	| RC6_AS_SERVO |RC3_AS_SERVO |RC2_AS_SERVO|RC1_AS_SERVO |RC0_AS_SERVO;	//all pin of PORTC are configured to manage servomotors
	Proto.portd=RD7_AS_DI	| RD6_AS_DI	|RD5_AS_DI |RD4_AS_DI|RD3_AS_DO	|RD2_AS_DO	|RD1_AS_DO	|RD0_AS_DO;		//RD0 RD1 RD2 RD3 are configured as digitals output to gear DC motor, RD4 RD5 RD6 RD7 are configured as digitals input
	SetPobProto(&Proto);	//set the pob proto

}


//function to move the bot
void MoveBot (UInt8 Way)
{	
	if(pobProtoOk==0)
	{
		InitPobProto();
		SwitchOnAllServo();
		pobProtoOk=1;
	}

	SetPortD(Way);
}


//set servo
void SetServoRgb(UInt8 servo, UInt8 position)
{
	if(pobProtoOk==0)
	{
		InitPobProto();
		SwitchOnAllServo();
		pobProtoOk=1;
	}


	if(position==4||position==5)
	{
		SetServoMotor(servo,position+2);
	}
	else
	{
		SetServoMotor(servo,position);
	}
}


//Draw the frame binarised 
void DrawVision (RGBFrame *FrameFromCam)
{	
	//draw the red buffer (88*120 pixels) on the Buffer for for the left screen (64*64 pixels)
	DrawComponentInABufferVideo(FrameFromCam->red,&LCD_Fast_Buffer_Video);
	DrawLeftLCD(&LCD_Fast_Buffer_Video); //refresh the left screen
}
