/** \anchor example4
 *
 * @brief DC Motor example. 
 *
 * @file
 
 Init and manage the Direct Current Motor connected on the DUAL-POB.

 */

#include <dual-pob.h>

int main(void)
{
	UInt8 data;
	UInt8 low_speed = 1;
	UInt8 high_speed = 30;

	// init dual-pob servomotor hardware
	InitUART0(19200);
	InitDualServo();
	
	SendString("Init ok\r\n");

	while(1)
	{
		data = GetByteFromUART0();

		if(data=='a')
		{
			SetDCMotor(DC_MOTOR_RUN);
			SetPwm(249,244, PWM_4);
		}
/*
		// set speed of dc motor
		SetDCSpeed(high_speed);
	
		// active dc motor for 1 second
		SetDCMotor(DC_MOTOR_RUN);
		Wait_Ms(3000);


		SetPwm(0x0F,700, PWM_4);
	
		// active dc motor for 1 second
		SetDCMotor(DC_MOTOR_RUN);
		Wait_Ms(3000);

		// move back for 1 second
		SetDCMotor(DC_MOTOR_BACK);
		Wait_Ms(1000);

		// set low speed of dc motor
		SetDCSpeed(low_speed);

		// and turn left for 1 second
		SetDCMotor(DC_MOTOR_LEFT);
		Wait_Ms(1000);

		// turn right for 1 second
		SetDCMotor(DC_MOTOR_RIGHT);
		Wait_Ms(1000);
*/
	}

	return 0;
}