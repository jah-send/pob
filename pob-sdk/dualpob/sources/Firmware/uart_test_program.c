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

// you need the dual-servomotor and the dual-io to test hardware.
//
// the next function test:
// - analog input
// - joystick pushbutton (as digital input)
// - servomotor 0
// - dc motors
// - bioloid servomotor
//
// how to run the test:
// - open hyperterminal.
// - write TEST + enter on your keyboard.



//public functions:

void RunTestProgram(void)
{
	UInt8 exit=0;
	UInt8 data;
	UInt8 i;
	UInt16 analog_value;
	Int8 string[16];
	UInt8 servo;
		

	//init joystick as digital input
	data =  IO_AS_INPUT << PIN_7 ;

	SetIOWay(data,IO_AS_DEFAULT,IO_AS_DEFAULT,IO_AS_DEFAULT);

	InitAnalog();

	//test loop
	while(exit==0)
	{
		
		//menu display:
		SendString("Test menu:\n\r");
		SendString("1 - test analog input\n\r");
		SendString("2 - test joystick push button\n\r");
		SendString("3 - test servomotor 0\n\r");
		SendString("4 - test dc motor\n\r");
		SendString("5 - test bioloid servomotor\n\r");
		SendString("6 - test eeprom\n\r");
		SendString("7 - exit\r\n");
		SendString("Select a choices: ");

		//get user choice
		data = GetByteFromUART0();
		SendByteToUART0(data);
		SendString("\n\r");
		
		//command execution:
		switch(data)
		{
			//test all analog input
			case '1':

				SendString("PF0 PF1 PF2 PF3 PF4 PF5 PF6 PF7\n\r");
				for(i=0;i<8;i++)
				{
					analog_value=GetAnalog(i);
				
					data=Bin2Dec(analog_value,string);

					SendBufferToUART0(string,data);
					SendByteToUART0(' ');

				}
				SendString("\n\r");

			break;
			//test digital input of push button
			case '2':

				data = GetInput(INPUT_PORTB,INPUT_7);

				if(data==1)
					SendString("\n\rPushbutton press\n\r\n\r");
				else
					SendString("\n\rPushbutton NOT press\n\r\n\r");

			break;
			//test servomotor 0
			case '3':
			
				servo=0;

				SetServo(servo,1,1);

				Wait_Ms(1000);

				SetServo(servo,255,1);

				Wait_Ms(1000);

				SetServo(servo,1,7);

			break;
			//test dc motors
			case '4':

				//SetPwm(249,650,PWM_16);
				//SetPwm(0xFF,850,0x2);
				SetPwmToDefault();

				SetDCMotor(DC_MOTOR_RUN);
				Wait_Ms(1000);

				SetDCMotor(DC_MOTOR_BACK);
				Wait_Ms(1000);

				SetDCMotor(DC_MOTOR_LEFT);
				Wait_Ms(1000);

				SetDCMotor(DC_MOTOR_RIGHT);
				Wait_Ms(1000);

				SetDCMotor(DC_MOTOR_STOP);

			break;
			//test bioloid servomotor: scan all bioloid bus
			case '5':
				SendString("\n\rsearch for ax12 servo...please wait...\r\n");

				data=0;
				for(i=0;i<254;i++)
				{
					if( PingAx12(i)==1)
					{
						data++;
						SendString("servo identifier: ");
						sprintf(string,"%d\r\n",i);	
						SendString(string);
					}
				}
				SendString("Number of ax12 servomotor: ");
				sprintf(string,"%d\r\n",data);	
				SendString(string);


			break;
			//test eeprom write/read
			case '6':
				SendString("\n\rWrite eeprom: ");
				for(i=0 ; i< 255 ;i++)
				{
					eepromWrite( 1000+i,i);
				}

				SendString("OK\n\rRead eeprom: ");
				servo=0;
				for(i=0 ; i<255;i++)
				{
					data = eepromRead(1000+i);
					if(data!=i)
					{
						servo=1;
						SendString("FAILED\n\n\r");
						break;
					}
				}
				if(servo==0)
				{
					SendString("OK\n\n\r");
				}

			break;
			

			//exit test
			case '7':

				exit=1;

				//at the end, set default io configuration
				SetIOWay(IO_AS_DEFAULT, IO_AS_DEFAULT,IO_AS_DEFAULT,IO_AS_DEFAULT);


			break;

		}
		
	}

	
}
