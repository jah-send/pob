/** \anchor example9
 *
 * @brief Eeprom. 
 *
 * @file
 
 An example to read and write eeprom memory.

 */
#include <dual-pob.h>

#include <stdio.h>

int main(void)
{
	UInt8 i;
	Int8 string[3];
	UInt8 data;

	//init uart0 at 19200 bauds
	InitUART0(19200);


	//write bytes to eeprom
	eepromWrite(0x0000, 0xAA );
	eepromWrite(0x0001, 0xBB );
	eepromWrite(0x0002, 0xCC );

	//read bytes from eeprom
	for(i=0;i<3;i++)
	{
		data = eepromRead(0x0000);
		Bin2Hex(data,string);
		string[2]=' ';
		SendBufferToUART0(string,3);
	}

	while(1)
	{
	}

	return 0;
}
