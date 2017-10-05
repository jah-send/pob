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

	//Simple use, just set motor speed
	//Forward
	SetMotor(100,100);
	//Wait a second
	WaitMs(1000);
	//Stops
	SetMotor(0,0);

	//Motion use
	//Init 3 movements
	InitNewMovement(3,100);
	//Add a movement
	AddXYMovement(0,0,200);
	AddXYMovement(1,-200,0);
	AddXYMovement(2,0,200);
	//Play all movements
	PlayMovement();

    	return 0;
 }