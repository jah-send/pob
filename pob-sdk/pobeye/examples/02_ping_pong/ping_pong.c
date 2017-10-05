/** \anchor pingpong
 *
 * @brief Ping Pong. 
 *
 * @file

 An example to use the UART: a simple ping pong between POBEYE and computer.

 * @author Foucault Alisson
 */

#include <pob-eye.h>

int main(void)
{		
	//Initialize byte value
	UInt8 byte = 0;
	
	// Initialization of the POB-Eye and the Serial
	InitPOBEYE();
	InitUART((UInt16)(BR_115200|NO_PARITY|ONE_STOP_BIT|LENGTH_8_BIT));	
	
	while (1)
	{
		//Get the byte from the UART
		byte = GetByteFromUART();
		
		//Send the byte to the UART
		SendByteToUART(byte);
	}
	return 0;
}
