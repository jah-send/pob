/** \anchor hello0
 *
 * @brief Hello world. 
 *
 * @file

 An example to print Hello World in the UART.

 * @author Foucault Alisson
 */

#include <pob-eye.h>

int main (void)
{	
	//Initialize POB-Eye and Serial
	InitPOBEYE();
	InitUART((UInt16)(BR_115200|NO_PARITY|ONE_STOP_BIT|LENGTH_8_BIT));

	//Send "Hello World" to the UART
	SendBufferToUART("Hello World", 11);
	return 0;
}
