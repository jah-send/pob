/** 
 *
 * @brief ButtonAndLed. 
 *
 * @file Describe how to use robot button and led
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
		//If button is press
		if(GetButton()==1)
		{
			//Start led
			SetLed();
		}
		else
		{
			//Stop led
			ClearLed();
		}
	}

    	return 0;
 }