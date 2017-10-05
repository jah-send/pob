/** 
 *
 * @brief Motor. 
 *
 * @file Describe how to use wheel
 *
 * @author Sylvain FAY-CHATELARD
 */

#include <pobRoboticSuite.h>

 int main(void)
 {
    	// Init pob-robotics-suite:
    	InitCpu();
    	InitRobot();

	while(1)
	{
		//If distance receive from distance sensor is lower than 300 mm
		if(GetDistanceSensor(1)>300)
		{
			//Move forward
			SetMotor(100,100);
		}
		else
		{
			//Stop
			SetMotor(0,0);
		}		
	}

    	return 0;
 }