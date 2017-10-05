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

//dual-pob block code
#include "nxt_i2c.h"

//#include "config.h"


/**< POB-EYE command: */

#define REFRESH_IMG			0xA1 //refresh camera frame and send X
#define REFRESH_IMG_Y		0xA2 //send Y

#define POBEYE_WRITE_BRICK  0xA6 //send a value to POB-EYE
#define POBEYE_READ_BRICK   0xA7 //get a value from POB-EYE

#define REFRESH_IMG_W 		0xAA //Get Width image
#define REFRESH_IMG_H		0xAB //Get Height image


#define SELECT_PATTERN		0xB1 //select POB-EYE pattern 


/**< private menbers: */


static UInt8 analog_channel;	//analog channel

static UInt8 pobeye_init=0;

static UInt8 io_pin_conf;		//input/output configuration word
static INPUT_PORT input_port;	//input port
static INPUT_PIN input_pin;		//input pin

static MotorMovement move;		//dc motor movement
static MotorMovement moveOld = DC_MOTOR_STOP;

static UInt8 pobeye_id;

static UInt8 uart_data;			//uart data

static UInt8 dualservo_init=0;  //flag dualservo init
static UInt8 servo;				//dualservo id
static UInt8 _position;			//dualservo position
static UInt8 _speed;				//dualservo speed

static UInt8 test;				//test value

static UInt16 pos_ax12;
static UInt16 speed_ax12;


void ConfIoPort(UInt8 config)
{
	// config bits:
	// bit7 		pin type (input=0, output=1)
	// bit6 		output value
	// bits5 4 		port number
	// bits3 2 1 0 	pin number

	UInt8 pinType = (0x80 & config) >> 7;

	//PORTB=0 PORTE=1 PORTG=2 PORTF=3
	UInt8 portType = (config & 0x30) >> 4;

	IO_PIN pinNumber = (IO_PIN)(config & 0x0F);

	UInt8 outputValue = config & 0x40;

	UInt8 port;

	// by default, all port in input
	UInt8 portb = IO_AS_DEFAULT;
	UInt8 porte = IO_AS_DEFAULT;
	UInt8 portf = IO_AS_DEFAULT;
	UInt8 portg = IO_AS_DEFAULT;

#ifdef DEBUG_DUAL_POB
	SendByteToUART0('0'+pinNumber);
	
	SendByteToUART0('0'+portType);

	SendByteToUART0('0'+pinType);
	SendByteToUART0(' ');
#endif


	if(pinType==1)
	{
		//output pin
		
		port = IO_AS_OUTPUT << pinNumber;

		input_port = INPUT_NONE;

		switch(portType)
		{
		case 0:
			portb=port;
		break;
		case 1:
			porte=port;
		break;
		case 2:
			portf=port;
		break;
		case 3:
			portg=port;
		break;
		}
	}
	else
	{
		//input pin

		input_port = (INPUT_PORT)portType;
		switch(pinNumber)
		{
			case 0:
				input_pin = INPUT_0;
			break;
			case 1:
				input_pin = INPUT_1;
			break;
			case 2:
				input_pin = INPUT_2;
			break;
			case 3:
				input_pin = INPUT_3;
			break;
			case 4:
				input_pin = INPUT_4;
			break;
			case 5:
				input_pin = INPUT_5;
			break;
			case 6:
				input_pin = INPUT_6;
			break;
			case 7:
				input_pin = INPUT_7;
			break;
		}

	}

	// set input/output way
	SetIOWay(portb,porte,portf,portg);

	// if pin is an output, then...
	if(pinType==1)
	{
		// clear or set output pin
		if(outputValue==0)
		{
			switch(portType)
			{
			case 0:
				ClearOutput(PORTB,pinNumber);
			break;
			case 1:
				ClearOutput(PORTE,pinNumber);
			break;
			case 2:
				ClearOutput(PORTF,pinNumber);
			break;
			case 3:
				ClearOutput(PORTG,pinNumber);
			break;
			}
		}
		else
		{
			switch(portType)
			{
			case 0:
				SetOutput(PORTB,pinNumber);
			break;
			case 1:
				SetOutput(PORTE,pinNumber);
			break;
			case 2:
				SetOutput(PORTF,pinNumber);
			break;
			case 3:
				SetOutput(PORTG,pinNumber);
			break;
			}
		}
		
	}

}

void ProcessBlockCommand(UInt8 data)
{	
	UInt8 temp_value;
	UInt16 ana_value;

#ifdef DEBUG_DUAL_POB	
	char debugUart[16];
#endif

	//nxt protocol switch
	switch(data)
	{

	// Set analog channel
	case SET_ANALOG:
		while( ReadOnI2CSlave(&analog_channel)==0) ;

		SendByteToUART0('0'+analog_channel);
	break;

	// Get analog value
	case GET_ANALOG:
		ana_value=GetAnalog( analog_channel );
		
		SendByteToUART0('0'+analog_channel);
		SendString("\r\n");

		ana_value = ana_value >> 2;

		temp_value = (UInt8)ana_value;
		PrepareWriteOnI2CSlave(temp_value);

		while(IsWriteOnI2COk()==0) ;

	break;


	// Select a pob-eye form
	case SELECT_POBEYE_FORM:

		while( ReadOnI2CSlave(&temp_value)==0) ;
		
		
		if( pobeye_init==0)
		{
			InitPobBus();
			pobeye_init=1;
		}

		//send order
		SetByteToPOBEYE(SELECT_PATTERN);
		GetByteFromPOBEYE();

		//send form identifier
		SetByteToPOBEYE(temp_value);


//		SendByteToUART0('0'+temp_value);		

	break;

	// Refresh pob-eye camera frame
	case REFRESH_POBEYE_FRAME:
		
		//Send a refresh order to pobeye: 
		
		//command works only in the pob-bridge firmware
		
	break;

	// Get frame x from pobeye
	case GET_FRAME_X:

		//send order
		SetByteToPOBEYE(REFRESH_IMG);
		//get x value
		temp_value=GetByteFromPOBEYE();

//		SendByteToUART0('x');
			
		PrepareWriteOnI2CSlave(temp_value);

		while(IsWriteOnI2COk()==0) ;
		
	break;

	//Get frame y from pobeye
	case GET_FRAME_Y:
		//send order
		SetByteToPOBEYE(REFRESH_IMG_Y);
		//get x value
		temp_value=GetByteFromPOBEYE();

//		SendByteToUART0('y');

		PrepareWriteOnI2CSlave(temp_value);

		while(IsWriteOnI2COk()==0) ;	//wait a i2c master read 
		
	break;

	//Get frame width from pobeye
	case GET_FRAME_WIDTH:
		//send order
		SetByteToPOBEYE(REFRESH_IMG_W);
		//get witdth value
		temp_value=GetByteFromPOBEYE();

//		SendByteToUART0('w');

		PrepareWriteOnI2CSlave(temp_value);

		while(IsWriteOnI2COk()==0) ;	//wait a i2c master read 
		
	break;

	//Get frame height from pobeye
	case GET_FRAME_HEIGHT:
		//send order
		SetByteToPOBEYE(REFRESH_IMG_H);
		//get height value
		temp_value=GetByteFromPOBEYE();

//		SendByteToUART0('h');

		PrepareWriteOnI2CSlave(temp_value);
		while(IsWriteOnI2COk()==0) ;	//wait a i2c master read
		
	break;

	case SET_IO:
		while( ReadOnI2CSlave(&io_pin_conf)==0) 	;

		ConfIoPort(io_pin_conf);

	//	Bin2Hex(io_pin_conf,buffer);
	//	buffer[2]=' ';
	//	SendBufferToUART0(buffer,3);
		
	break;

	case GET_IO:
	
		if(input_port!= INPUT_NONE)
		{
			temp_value=GetInput(input_port,input_pin);
			input_port=INPUT_NONE;
		}
		else
		{
			temp_value=0;
		}

		PrepareWriteOnI2CSlave(temp_value);
			
		
		while(IsWriteOnI2COk()==0) ;	//wait a i2c master read 

	break;

	// Send pob-eye identifier
	case SEND_POBEYE_ID:
	
		//wait data from i2c master
		while( ReadOnI2CSlave(&pobeye_id)==0) ;

//		SendByteToUART0('0'+pobeye_id);

	break;

	// Read data from pob-eye
	case READ_FROM_POBEYE:
		
		SetByteToPOBEYE(POBEYE_READ_BRICK);
		SetByteToPOBEYE(pobeye_id);

		temp_value=GetByteFromPOBEYE();
		
		PrepareWriteOnI2CSlave(temp_value);

		while(IsWriteOnI2COk()==0) ;	//wait a i2c master read
		
	break;

	// Write a data to pob-eye
	case WRITE_TO_POBEYE:
		
		while( ReadOnI2CSlave(&temp_value)==0) ;

		//send identifier to pobeye
		SetByteToPOBEYE(POBEYE_WRITE_BRICK);
		SetByteToPOBEYE(temp_value);

//		SendByteToUART0('0'+temp_value);

		while( ReadOnI2CSlave(&temp_value)==0) ;

		//send data to pobeye
		SetByteToPOBEYE(temp_value);

//		SendByteToUART0('0'+temp_value);

	break;
	
	// Set baudrate of dual-pob uart0
	case SET_BAUDRATE:

		//get baudrate
		while( ReadOnI2CSlave(&temp_value)==0) ;

//		SendByteToUART0('0'+ temp_value);

		//configure uart
		//InitUART0(...)

	break;

	// Send a byte to dual-pob uart0
	case SEND_TO_UART:

		while( ReadOnI2CSlave(&temp_value)==0) ;

		SendByteToUART0(temp_value);

	break;

	// Prepare uart to receive data
	case PREPARE_UART:


	break;

	// Get a byte from dual-pob uart0
	case GET_FROM_UART:
		temp_value=GetByteFromUART0();

		PrepareWriteOnI2CSlave(temp_value);

		while(IsWriteOnI2COk()==0) ;

	break;

	case SET_DUALPOB_SERVO:
		
		while( ReadOnI2CSlave(&servo)==0) ;

		while( ReadOnI2CSlave(&_position)==0) ;

		while( ReadOnI2CSlave(&_speed)==0) ;

		//init dualservo
		if(dualservo_init==0)
		{
			InitDualServo();

			dualservo_init=1;
		}

		//send servo
		SetServo(servo,_position,_speed);


	break;
	
	case SET_DC_MOTOR:
		while( ReadOnI2CSlave(&_speed)==0) ;

		while( ReadOnI2CSlave(&_position)==0) ;

//		SendByteToUART0('0'+position);
	

		//init dualservo
/*		if(dualservo_init==0)
		{
			InitDualServo();

			dualservo_init=1;
		}

*/				
		switch(_position)
		{
			case 0:
				move = DC_MOTOR_STOP;
			break;
			case 1:
				move = DC_MOTOR_RUN;
			break;
			case 2:
				move = DC_MOTOR_BACK;
			break;
			case 3:
				move = DC_MOTOR_LEFT;
			break;
			case 4:
				move = DC_MOTOR_RIGHT;
			break;
			default:
				move = DC_MOTOR_STOP;
			break;
		}

		if(moveOld!=move)
		{
			//set dc motor
			SetDCSpeed(_speed);

			SetDCMotor(move);

			moveOld=move;
		}
		
	break;

	case SET_BIOLOID_SERVO:
		while( ReadOnI2CSlave(&servo)==0) ;

		while( ReadOnI2CSlave(&pos_ax12)==0) ;
		while( ReadOnI2CSlave(&_position)==0) ;

#ifdef DEBUG_DUAL_POB
//		sprintf(debugUart,"%d %d %d\r\n",servo,pos_ax12,position);
//		SendString(debugUart);
#endif

		pos_ax12 = 	_position | (pos_ax12<<8);

		while( ReadOnI2CSlave(&speed_ax12)==0) ;
		while( ReadOnI2CSlave(&_speed)==0) ;

#ifdef DEBUG_DUAL_POB
//		sprintf(debugUart,"%d\r\n",speed);
//		SendString(debugUart);
#endif

		speed_ax12 = 	_speed | (speed_ax12<<8);

#ifdef DEBUG_DUAL_POB
		sprintf(debugUart,"%d %d\r\n",pos_ax12,speed_ax12);
		SendString(debugUart);
#endif

		SetAx12Position(servo,pos_ax12,speed_ax12);
		MoveAx12();
		Wait_Ms(500);


	break;

	case MOVE_BIOLOID:

	break;

	default:
		//by default:
	
	break;

	}

	test++;
}

