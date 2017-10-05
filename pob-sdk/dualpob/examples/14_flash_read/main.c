/** \anchor example14
 *
 * @brief Flash example. 
 *
 * @file
 
  An example to read data from the internal flash of DUAL-POB.

 */

// Include flash definition & functions:
#include <avr/pgmspace.h>

#include <dual-pob.h>

// Create a new array and place it in flash:
prog_uint16_t array_in_flash[4] = { 123,1234,12345,65000};



int main(void)
{
	Int8 string[16];
	UInt32 len;
	Int32 data;
	UInt8 i;

	InitUART0(19200);


	SendString("Init ok.\r\n");


	for(i=0;i<4;i++)
	{
		// Get data from array and print it on uart:
		data = GetUInt16Flash(array_in_flash,i);
		len = Bin2Dec(data,string);
		
		string[len]=0;

		SendString(string);
		SendString("\r\n");
	}
	

	return 0;
}
