/** 
 *
 * @brief PingPongSerial. 
 *
 * @file Describe how to use serial communication with computer
 *
 * @author Sylvain FAY-CHATELARD
 */

#include <pobRoboticSuite.h>

 int main(void)
 {
     //Initialize byte value
	UInt8 byte = 0;
	
	// Initialization of the POB-Robotics-Suite and the Serial
	InitCpu();
	InitUART0(115200);	
	
	while (1)
	{
		//Get the byte from the UART
		byte = GetByteFromUART0();
		
		//Send the byte to the UART
		SendByteToUART0(byte);
	}
	return 0;
 }