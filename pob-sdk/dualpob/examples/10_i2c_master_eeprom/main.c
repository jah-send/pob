/** \anchor example10
 *
 * @brief I2C Master example. 
 *
 * @file
 
 An example to read the 24c64 i2c eeprom.
 
 */

#include <dual-pob.h>

#define EEPROM_ADDR	0xA0

UInt8 GetByteFromI2cEeprom(UInt16 address)
{
	UInt8 tmp;

	SendSlaveAddress(EEPROM_ADDR);			//Send the Eeprom Adress
	WriteOnI2C((UInt8)((address&0xff00)>>8));	//Send Addr H
	WriteOnI2C((UInt8)address&0x00ff);			//Send Addr L	
	STOPI2C();

	SendSlaveAddress(EEPROM_ADDR|1);		
	tmp=ReadOnI2CNoAck();
	STOPI2C();

	return tmp;
}

void SetByteToI2cEeprom(UInt16 address,UInt8 data)
{	
	SendSlaveAddress(EEPROM_ADDR);			//Send the Eeprom Adress	
	WriteOnI2C((UInt8)((address&0xff00)>>8));	//Send Addr H
	WriteOnI2C((UInt8)address&0x00ff);			//Send Addr L
	WriteOnI2C(data);						//Send Data 
	STOPI2C();
}

int main(void)
{
	Int8 string[2];
	UInt8 data;

	//init uart0 at 19200 bauds
	InitUART0(19200);

	//init i2c
	InitI2C();

	SetByteToI2cEeprom(0x0000,0xAA);
	data = GetByteFromI2cEeprom(0x0000);

	Bin2Hex(data,string);
	SendBufferToUART0(string,2);

	while(1)
	{
	}

	return 0;
}
