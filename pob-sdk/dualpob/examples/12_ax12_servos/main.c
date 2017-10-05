/** \anchor example12
 *
 * @brief AX-12 example 2. 
 *
 * @file
 
 Set id of ax12 servomotor.
 What do you need:
  - 1 DUAL-POB
  - 1 AX-12 servomotor
  - Power supply to 9.6 volts.

  */
#include <dual-pob.h>

#include <stdio.h>

int main(void)
{
	UInt8 i;
	Int8 string[6];
	UInt8 data;

	UInt16 pos;
	Int8 result;

	//init uart0 at 19200 bauds
	InitUART0(19200);
	
	//init ax12 servomotor communication:
	InitAx12Bus();

	// search all ax12 servomotor:
	SendString("\n\rSearch for ax12 servo...please wait...\r\n");

	data=0;
	for(i=0;i<=253;i++)
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

	//set id
	result = GetByteFromUART0();
	if(result =='s')
	{
		SetAx12Id(17);
	}
	

	while(1)
	{
	}

	return 0;
}
