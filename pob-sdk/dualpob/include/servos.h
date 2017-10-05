//
// Copyright 2008 POB-Technology. All rights reserved.
// POB-Technology PROPRIETARY/CONFIDENTIAL.
//

/** \anchor servo
 * 
 * @brief DUAL-POB servomotor function
 *
 * @file
 * 
 * Function to manage servomotor and motors of the dual-pob servo board.
 *
 * <b>dual-pob servo features:</b>
 *	- 18 servomotors.
 *	- 1 internal pwm for the 2 DC motors.
 *	- 1 connector for 2 DC motors.
 *
 * @par Servo example
 *
 * @code
 
	UInt8 position,speed;
	UInt8 array[2];

	InitUART0(19200);
	
	InitDualServo();

	SendString("dual-pob servo test\r\n");


	SetServo(5,1,1);

	Wait_Ms(1000);

	SetServo(5,254,1);

 * @endcode
 *
 */
#ifndef DUAL_POB_SERVO_H
#define DUAL_POB_SERVO_H

/**
 * @name dual-pob servomotor functions
 *
 * 
 */
/*@{*/


/**
 * @brief Init dual-pob servo board.
 */
extern void InitDualServo(void);


/** 
 * @brief Set the position and speed of one servomotor on the dual-pob servo
 * 
 * @param servo			servomotor identifier : between 0 to 17
 * @param position		servomotor position
 * @param speed			servomotor speed : between 0 to 7.
 */
extern void SetServo(UInt8 servo, UInt8 position, UInt8 speed);



/* @brief Get the current position of the servomotor.
 *
 * @param servo		servomotor number to get.
 * @return the current servomotor position.
 */
//extern UInt8 GetDualServoPosition(UInt8 servo);


/**
 * @brief Switch on the servomotor.
 *
 * @param servo		switch on the specified servomotor.
 */
extern void SwitchOnServo(UInt8 servo);


/**
 * @brief Switch off a servomotor.
 * 
 * @param servo		switch off the specified servomotor.
 */
extern void SwitchOffServo(UInt8 servo);


/**
 * @brief Set position and speed of multiple servomotor.
 *
 * @code

	UInt8 position[4];
	UInt8 speed[4];

	// init position and speed array....
	position[0] = 0;
	position[1] = 0;
	position[2] = 0;
	position[3] = 0;

	speed[0]=1;
	speed[1]=1;
	speed[2]=1;
	speed[3]=1;

	// set servos 2,3,4 and 5 with the position and speed array:

	SetServoArray(position, speed, 2, 4 );

 * @endcode
 *
 * @param position		Array of position
 * @param speed			Array of speed
 * @param offset		Identifier of the first servomotor which have to be set.
 * @param len			Lenght of position's array and speed's array.
 */
extern void SetServoArray( UInt8 *position, UInt8 *speed, UInt8 offset, UInt8 len);

/**
 * @brief Set position of multiple servomotor.
 *
 * @code

  	UInt8 position[4];

	// init position array....
	position[0] = 100;
	position[1] = 100;
	position[2] = 100;
	position[3] = 100;

	// set servos 2,3,4 and 5 with the position array:

	SetServoArray(position, 2, 4 );

 * @endcode
 *
 * @param position		Array of position
 * @param offset		Identifier of the first servomotor which have to be set.
 * @param len			Lenght of position's array.
 */
extern void SetServoPosition(UInt8 *position, UInt8 offset,UInt8 len);


/**
 * @brief Set speed of multiple servomotor.
 *
 * @param speed			Array of speed
 * @param offset		Identifier of the first servomotor which have to be set.
 * @param len			Lenght of position's array and speed's array.
 */
extern void SetServoSpeed(UInt8 *speed,UInt8 offset,UInt8 len);

/**
 * @brief Set speed for all servomotor.
 *
 * @param speed			speed for all servomotor
 */
extern void SetGlobalSpeed(UInt8 speed);

/** @brief pwm prescaler
 *
 */
typedef enum _dualpob_prescaler { 
	PWM_1=0x0,	/**< PWM prescaler of 1 */
	PWM_4=0x1,	/**< PWM prescaler of 4 */
	PWM_16=0x2	/**< PWM prescaler of 16 */
} PwmPrescaler;

/** @brief Set pwm of DC motors.
 *
 * The PWM period and PWM duty cycle formula:
 *
 * <b>PWM Period</b> = (<i>PWM period configuration byte</i> +1 ) x 4 x (1 / CPU Frequency) x (<i>PWM prescaler</i>) with CPU Frequency at 20MHz
 *
 * <b>PWM Duty cycle</b> = (<i>Duty cycle configuration byte</i> + 256 ) x (1 / CPU Frequency) x (<i>PWM prescaler</i>) with CPU Frequency at 20MHz
 *
 *
 * You can compute the period and dutycycle parameters for this function with this formula:
 *
 * <b>period byte</b> = ( <i>PWM Period</i> x <i>CPU Frequency</i> ) / ( <i>prescaler</i> x 4 ) - 1
 *
 * <b>dutyclycle word</b> = ( <i>PWM Dutycycle x 4 x <i>CPU Frequency ) / ( <i>prescaler</i> ) - 256 
 *
 * With <i>CPU Frequency = 20 MHz</i> and <i>PWM Period</i> and <i>PWM Dutycycle</i> in seconds.
 *
 *
 * @warning Hardware don't support frequencies higher than 5 KHz.
 *
 * @param period		PWM period configuration (previous formula to compute this byte)
 * @param dutycycle		Duty cycle configuration (previous formula to compute this byte)
 * @param prescaler		PWM prescaler value: 1, 4 or 16
 */
extern void SetPwm(UInt8 period,UInt16 dutycycle,PwmPrescaler prescaler);

/** @brief Set default value for pwm
 *
 * Period = 0xFF, Dutycycle = 650 and Prescaler = 16.
 */
extern void SetPwmToDefault(void);



/** @brief dc motor movement
 *
 */
typedef enum _dualpob_dc_motor {
	DC_MOTOR_STOP	=0,			/**< stop motors */
	DC_MOTOR_LEFT	=0x28,		/**< run */
	DC_MOTOR_RIGHT	=0x50,		/**< back */
	DC_MOTOR_RUN	=0x48,		/**< left */
	DC_MOTOR_BACK	=0x30		/**< right */
} MotorMovement;

/** @brief Active dual-pob dc motors.
 *
 * @param move		DC motor activation
 */
extern void SetDCMotor(MotorMovement move);

/** @brief Set speed of DC motors.
 *
 * This function calls SetPwm() to set the speed. If you want control the speed with more parameters, use the SetPwm().
 *
 * @param speed		DC motors speed (between 0 and 35)
 */
extern void SetDCSpeed(UInt8 speed);

/*@}*/

/**
 * @name low level function between dual-pob and dual-pob servomotor.
 *
 * you don't have to call this function in your user code!
 */
/*@{*/

/** @brief Init dual-pob servo communication.
 *
 * Init the communication with the dual-pob servo boards
 *
 * @warning low level function! 
 */
extern void InitDualServoBus(void);

/** @brief Write a byte to dual-pob servo board
 *
 * @warning low level function! 
 * @param data		Data to be write
 */
extern void WriteByteToDualServo(UInt8 data);

/*@}*/


#endif
