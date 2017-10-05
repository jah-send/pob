/** \anchor example2
 *
 * @brief Move servomotor. 
 *
 * @file
 
 Move servomotor on dual-pob servomotor.

 */
#include <dual-pob.h>


int main(void)
{
	UInt8 servo = 0;
	UInt8 low_speed = 1;
	UInt8 high_speed = 7;
	
	InitUART0(19200);

	SendString("Test servomotor...\r\n");

	// init dualpob servomotor hardware
	InitDualServo();

	SendString("Init dualservo ok\r\n");

	while(1)
	{
		// set servo 0 to 1 at low speed
		SetServo(servo,1,low_speed);

		Wait_Ms(500);

		// set servo 0 to 250 at high speed
		SetServo(servo,250,high_speed);

		Wait_Ms(500);
	}

	return 0;
}