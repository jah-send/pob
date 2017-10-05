/** \anchor example1
 *
 * @brief Ping pong. 
 *
 * @file

 Serial ping pong between your computer and the dual-pob

 */

#include <dual-pob.h>


int main(void)
{
	UInt8 data;
	
	InitUART0(19200);

	SendString("Ping-Pong!\n");

	while(1)
	{
		// get data from your computer
		data = GetByteFromUART0();
		
		// send data to computer
		SendByteToUART0(data);
	}

	return 0;
}