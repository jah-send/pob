/** \anchor example13
 *
 * @brief Move servomotors. 
 *
 * @file
 
 Move multiple servomotors on the dual-pob.

 */
#include <dual-pob.h>


int main(void)
{
	UInt8 servo = 0;
	UInt8 low_speed = 1;
	UInt8 high_speed = 7;
	UInt8 position[4];
	
	InitUART0(19200);

	// init dualpob servomotor hardware
	InitDualServo();

	SendString("Init dualservo ok\r\n");

	while(1)
	{

		// init position array....
		position[0] = 10;
		position[1] = 10;
		position[2] = 10;
		position[3] = 10;

		// set servos 2,3,4 and 5 with the position array:

		SetGlobalSpeed(1);
		SetServoPosition(position, 2, 4 );

		Wait_Ms(800);

		position[0] = 255;
		position[1] = 255;
		position[2] = 255;
		position[3] = 255;

		SetGlobalSpeed(6);
		SetServoPosition(position, 2, 4 );

		Wait_Ms(800);
	}

	return 0;
}
