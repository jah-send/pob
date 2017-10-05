/** 
 * @brief Servomotor function
 *
 * @file
 * 
 * This function manages the servomotor of the POB-Servo board and the DUAL-POB servo device.
 *
 * @par Code example:
 *
 * @code

	// init the servomotor device:

	InitServos( DUAL_POB );

	// move servomotor 0 to position 0:

	SetServo(0,0,1);

	Wait(100);

	// move servomotor 0 to position 255 (low speed)

	SetServo(0,255,1);

	Wait(100);

	// move servomotor 0 to position 0 (high speed)
	SetServo(0,0,7);


	// move multiple servomotors at the same time:

  	UInt8 position[4];
	UInt8 speed[4];

	// init position and speed array....
	position[0] = 100;
	position[1] = 100;
	position[2] = 100;
	position[3] = 100;

	speed[0]=2;
	speed[1]=2;
	speed[2]=2;
	speed[3]=2;

	// set servos 2,3,4 and 5 with the position and speed array:

	SetServoArray(position, speed, 2, 4 );


 * @endcode
 *
 * @author Baptiste BURLES & Pierre SEGUIN. POB-Technology 
 *
 */
#ifndef POB_SERVO_DEV_H
#define POB_SERVO_DEV_H

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Servomotor device enumeration
 *
 */
typedef enum _servo_device 
{
	POB_SERVO=0,	/**< select pob-servo board as servo device */
	DUAL_POB=1		/**< select dual-pob servo board as servo device */
} SERVO_DEVICE;


/**
 * @brief Init the servomotor device with the specified board.
 *
 * @param type	Type of servomotor device: POB_SERVO or DUAL_POB.
 */
extern void InitServos(SERVO_DEVICE type);


/** 
 * @brief Set the position and speed of one servomotor.
 * 
 * @param servo : servo number to set
 * @param position : position of the servo
 * @param speed : speed of the servo : between 0 to 7.
 */
extern void SetServo(UInt8 servo, UInt8 position, UInt8 speed);


/**
 * @brief Get the current position of the servomotor.
 *
 * This function works only for the POB-Servo. On Dual-pob, this function return 0.
 *
 * @param servo		servomotor number to get.
 * @return the current position of the servomotor.
 */
extern UInt8 GetServoPosition(UInt8 servo);


/**
 * @brief Switch on a servomotor.
 *
 * @param servo		the servomotor to switch on.
 */
extern void SwitchOnServo(UInt8 servo);


/**
 * @brief Switch off a servomotor.
 * 
 * @param servo		the servomotor to switch off.
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
 * @param position	Array of position
 * @param speed		Array of speed
 * @param offset	Id of the first servomotor to set.
 * @param len		Lenght of position's array and speed's array.
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
 * @param position	Array of position
 * @param offset	Id of the first servomotor to set.
 * @param len		Lenght of position's array and speed's array.
 */
extern void SetServoPosition(UInt8 *position, UInt8 offset,UInt8 len);


/**
 * @brief Set speed of multiple servomotor.
 *
 * @param speed		Array of speed
 * @param offset	Id of the first servomotor which have to be set.
 * @param len		Lenght of position's array and speed's array.
 */
extern void SetServoSpeed(UInt8 *speed,UInt8 offset,UInt8 len);

/**
 * @brief Set speed for all servomotor.
 *
 * @param speed		speed for all servomotor (between 0 and 7).
 */
extern void SetGlobalSpeed(UInt8 speed);

#ifdef __cplusplus
 }
#endif

#endif
