/** \anchor example0
 *
 * @brief Hello world on UART. 
 *
 * @file

 Simple hello world on DUAL-POB.

 */
#include <dual-pob.h>

//main program
int main(void)
{

	//init uart0 to 19200
	InitUART0(19200);

	//send text on your computer
	SendString("Hello world from DUAL-POB!");


	return 0;
}