/** \anchor example5
 *
 * @brief Joystick example. 
 *
 * @file
 
	An example to use the Joystick connected on the DUAl-IO device.

 */
#include <dual-pob.h>

int main(void)
{
	UInt8 portb;
	UInt8 data;
	UInt8 x,y;

	//init uart0 at 19200 bauds
	InitUART0(19200);

	//init joystick as input
	portb =  IO_AS_INPUT << PIN_7 ;

	//write input/output configuration
	SetIOWay(data,IO_AS_DEFAULT,IO_AS_DEFAULT,IO_AS_DEFAULT);

	//init analog input
	InitAnalog();

	//main loop of program:
	while(1)
	{
		//read joystick button
		data = GetInput(INPUT_PORTB,INPUT_7);

		if(data==1)
			SendString("\n\rPushbutton press\n\r\n\r");
		else
			SendString("\n\rPushbutton NOT press\n\r\n\r");

		//read analog value of joystick
		x = GetAnalog(6);
		y = GetAnalog(7);



	}

	return 0;
}