/** \anchor example7
 *
 * @brief Analog example. 
 *
 * @file

	Read the 8 analog channel of the DUAL-POB.

 */
#include <dual-pob.h>

int main(void)
{
	UInt8 i;
	UInt8 string[6];
	UInt8 analog_value,len;

	//init uart0 at 19200 bauds
	InitUART0(19200);

	//init analog input
	InitAnalog();

	//main loop of program:
	while(1)
	{
		//read analog value
		for(i=0;i<8;i++)
		{
			analog_value=GetAnalog(i);
				
			len=Bin2Dec(analog_value,string);

			SendBufferToUART0(string,len);
			SendByteToUART0(' ');
		}
		SendString("\n\r");

		//sleep for 3 seconds before next acquisition
		Wait_Ms(3000);
	}

	return 0;
}
