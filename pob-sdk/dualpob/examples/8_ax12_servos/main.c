/** \anchor example8
 *
 * @brief AX-12 servomotors. 
 *
 * @file
 
 An example to use the AX-12 servomotors on the DUAL-POB.

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
	for(i=0;i<255;i++)
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

	//set position of ax12 servo 1 and servo 2:
	SetAx12Position(1,500,130);
	SetAx12Position(2,500,130);
	
	// then, move servo 1 and 2 to the new position
	MoveAx12();

	Wait_Ms(1000);

	//get position
	result=GetAx12Position(1,&pos);
	sprintf(string,"%d %d\n\r",pos,result);
	SendString(string);

	result=GetAx12Position(2,&pos);
	sprintf(string,"%d %d\n\r",pos,result);
	SendString(string);

	while(1)
	{
	}

	return 0;
}
