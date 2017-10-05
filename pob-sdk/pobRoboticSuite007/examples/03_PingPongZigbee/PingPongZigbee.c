/** 
 *
 * @brief PingPongZigbee. 
 *
 * @file Describe how to use zigbee communication with computer
 *
 * @author Sylvain FAY-CHATELARD
 */

#include <pobRoboticSuite.h>

 int main(void)
 {
	// Initialization of frame table
	UInt8 frame[100];
	// Initialization of address of sender
	UInt16 address=0;
	// Initialization of length of frame
	UInt32 length=0;
	
	// Initialization of the POB-Robotics-Suite
	InitCpu();
	InitRobot();
	InitUART0(115200);
	// Initialization of the zigbee chip with speed, mode, and address
	if(InitZigbee(9600,ZIGBEE_MODE_API,1)==ZIGBEE_OK)
	{
		SetLCDText((UInt8*)"CONFIG OK",9);
	}
	else
	{
		SetLCDText((UInt8*)"ERROR",5);
	}
	
	while (1)
	{
		//Get the frame from zigbee
		if(GetBufferFromZigbee(frame,&length,&address)==ZIGBEE_OK)
		{	
			//Send the frame to zigbee
			DebugPrintf("Receive value : %d\r\n",frame[0]);
			SendBufferToZigbee(frame,length,address,ZIGBEE_SHORT_ADDRESS);
		}
	}
	return 0;
 }