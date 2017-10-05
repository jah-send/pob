/** 
 *
 * @brief Servo. 
 *
 * @file Describe how to use servo
 *
 * @author Sylvain FAY-CHATELARD
 */

#include <pobRoboticSuite.h>

UInt16 motion0[SERVO_NUMBER] = {
 	0,  0, 0, 0, 0, 0, 0, 0
};
 
UInt16 motion1[SERVO_NUMBER] = {
	50, 0, 0, 0, 0, 0, 0, 0
};

UInt16 motion2[SERVO_NUMBER] = {
	100, 50, 0, 0, 0, 0, 0, 0
};

UInt16 motion3[SERVO_NUMBER] = {
	150, 100, 50, 0, 0, 0, 0, 0
};

UInt16 motion4[SERVO_NUMBER] = {
	200, 150, 100, 50, 0, 0, 0, 0
};

UInt16 motion5[SERVO_NUMBER] = {
	250, 200, 150, 100, 50, 0, 0, 0
};

UInt16 motion6[SERVO_NUMBER] = {
	200, 250, 200, 150, 100, 50, 0, 0
};

UInt16 motion7[SERVO_NUMBER] = {
	150, 200, 250, 200, 150, 100, 50, 0
};

UInt16 motion8[SERVO_NUMBER] = {
	100, 150, 200, 250, 200, 150, 100, 50
};

UInt16 motion9[SERVO_NUMBER] = {
	50, 100, 150, 200, 250, 200, 150, 100
};

UInt16 motion10[SERVO_NUMBER] = {
	0, 50, 100, 150, 200, 250, 200, 150
};

UInt16 motion11[SERVO_NUMBER] = {
	0, 0, 50, 100, 150, 200, 250, 200
};

UInt16 motion12[SERVO_NUMBER] = {
	0, 0, 0, 50, 100, 150, 200, 250
};

UInt16 motion13[SERVO_NUMBER] = {
	0, 0, 0, 0, 50, 100, 150, 200
};

UInt16 motion14[SERVO_NUMBER] = {
	0, 0, 0, 0, 0, 50, 100, 150
};

UInt16 motion15[SERVO_NUMBER] = {
	0, 0, 0, 0, 0, 0, 50, 100
};

 int main(void)
 {
    	// Init pob-robotics-suite:
    	InitCpu();
    	InitRobot();

	//Simple use, just set servo position
	SetServo(/*port*/ 1,/*position*/ 255,/*speed*/ 16);
	WaitMs(1000);
	SetServo(/*port*/ 1,/*position*/ 0,/*speed*/ 16);

	//Motion use
	//Init 16 movements of servo motion
	InitServoMotion(16,8);
	//Add a servo motion
	AddServoMotion(0,motion0);
	AddServoMotion(1,motion1);
	AddServoMotion(2,motion2);
	AddServoMotion(3,motion3);
	AddServoMotion(4,motion4);
	AddServoMotion(5,motion5);
	AddServoMotion(6,motion6);
	AddServoMotion(7,motion7);
	AddServoMotion(8,motion8);
	AddServoMotion(9,motion9);
	AddServoMotion(10,motion10);
	AddServoMotion(11,motion11);
	AddServoMotion(12,motion12);
	AddServoMotion(13,motion13);
	AddServoMotion(14,motion14);
	AddServoMotion(15,motion15);

	//Play all servos motion
	PlayServoMotion(0);

    	return 0;
 }