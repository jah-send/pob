/** 
 * @brief DUAL-POB Function 
 *
 * @file 
 *
 * The dual-pob board have 22 input/output pin free for use. 
 *
 * This pin are on PORTF, PORTB, PORTG and PORTE of the dual-pob cpu:
 * - the PORTF pin 0 to 7, as digital input, digital output or analog input
 * - the PORTB pin2, pin3 and pin7 as digital input/output
 * - the PORTG pin0 to 4 as digital input/output
 * - the PORTE pin 2 to 7 as digital input/output
 *
 * \note Please note that only the PORTF can be use as analog input!
 * 
 * @par Example code: configure dual-pob input/output pins
 *
 * @code

  UInt8 portb=0;
  UInt8 porte=0;

  // Set pin7 of PORTB as output (the other pin are set as input by default)
  portb = IO_AS_OUTPUT << PIN_7 ;

  // Set pin2 and pin7 of PORTE as output (the other pin are set as input by default)
  porte = (IO_AS_OUTPUT << PIN_2) | (IO_AS_OUTPUT << PIN_7 ); 

  // Finally, write the i/o configuration:
  SetDualIOWay(portb, porte,IO_AS_DEFAULT,IO_AS_DEFAULT);

 * @endcode
 *
 * @par Example code: set/clear an output pin on the dual-pob:
 *
 * @code

  // Set pin7 of PORTE to 1 during 1 second

  SetDualOutput(OUTPUT_PORTE,PIN_7);

  Wait(1000);

  ClearDualOutput(OUTPUT_PORTE,PIN_7);


 * @endcode
 *
 * @par Example code: Get value of dual-pob input pin
 *
 * @code

  UInt8 value;

  // Get the pin value of PORTB
  value = GetDualInput(INPUT_PORTB,INPUT_1);

 * @endcode
 *
 * @author Pierre SEGUIN & Baptiste BURLES. POB-Technology
 *
 */
#ifndef DUAL_POB_H
#define DUAL_POB_H

#ifdef __cplusplus
extern "C" {
#endif

/** @brief dual-servo pwm prescaler enumerations
 *
 */
typedef enum _dualpob_prescaler { 
	PWM_1=0x0,	/**< PWM prescaler of 1 */
	PWM_4=0x1,	/**< PWM prescaler of 4 */
	PWM_16=0x2	/**< PWM prescaler of 16 */
} PwmPrescaler;


/** @brief Set pwm parameters of dual-pob DC motors.
 *
 * You can compute the period and dutycycle parameters for this function with this formula:
 *
 * <b>period</b> = ( <i>PWM Period</i> x <i>CPU Frequency</i> ) / <i>prescaler</i> - 1
 *
 * <b>dutyclycle</b> = ( <i>PWM Dutycycle x 4 x <i>CPU Frequency ) / <i>prescaler</i> 
 *
 * With <i>CPU Frequency = 20 MHz</i> and <i>PWM Period</i> and <i>PWM Dutycycle</i> in seconds.
 *
 * @param period		PWM period configuration (see previous formula to compute this byte)
 * @param dutycycle		Duty cycle configuration (see previous formula to compute this byte)
 * @param prescaler		PWM prescaler value: 1, 4 or 16
 */
extern void SetPwm(UInt8 period,UInt16 dutycycle,PwmPrescaler prescaler);


/** @brief dual-servo dc motor movement
 *
 */
typedef enum _dualpob_dc_motor {
	DC_MOTOR_STOP=0,		/**< stop motors */
	DC_MOTOR_RUN=0x28,		/**< run */
	DC_MOTOR_BACK=0x50,		/**< back */
	DC_MOTOR_LEFT=0x48,		/**< left */
	DC_MOTOR_RIGHT=0x30		/**< right */
} MotorMovement;

/** @brief Active dual-pob DC motors.
 *
 * @code

  // Set speed:

  SetDCSpeed(0);

  // Run motor for 1 seconds:

  SetDCMotor( DC_MOTOR_RUN );

  Wait(10000);

  SetDCMotor(DC_MOTOR_STOP);

 * @endcode
 *
 * @param move		DC motor activation
 */
extern void SetDCMotor(MotorMovement move);

/** @brief Set speed of dual-pob DC motors.
 *
 * This function calls SetPwm() to set the speed. If you want control the speed with more parameters, use the SetPwm().
 *
 * @param speed		DC motors speed (between 0 and 35)
 */
extern void SetDCSpeed(UInt8 speed);


/** @brief IO pin settings enumeration.
 * 
 */
typedef enum _io_settings
{
	IO_AS_INPUT=0,		/**<	Set io pin as input */
	IO_AS_OUTPUT=1,		/**<	Set io pin as output */
	IO_AS_ANALOG=0,		/**<	Set io pin as analog input */
	IO_AS_DEFAULT=0		/**<	Default io settings: input */
} IO_SETTINGS;


/** @brief Set dual-pob IO way as input/output of portb, porte, portf and portg pins.
 *
 * @param portb		PORTB configuration word
 * @param porte		PORTE configuration word
 * @param portf		PORTF configuration word
 * @param portg		PORTG configuration word
 */
extern void SetDualIOWay(UInt8 portb, UInt8 porte, UInt8 portf, UInt8 portg);


/**
 * @brief Get analog value from a dual-pob analog input channel.
 *
 * @param	channel		Analog channel between 0 and 7.
 * @return	Analog value
 */
extern UInt8 GetAnalog(UInt8 channel);


/** @brief Output port enumeration
 *
 */
typedef enum _dual_output_port {
	OUTPUT_PORTB=0,		/**<	select PORTB as output port */
	OUTPUT_PORTE=1,		/**<	select PORTE as output port */
	OUTPUT_PORTF=2,		/**<	select PORTF as output port */
	OUTPUT_PORTG=3		/**<	select PORTG as output port */
} OUTPUT_PORT;


/** @brief Output pin number enumerations
 *
 * Use this enumeration in SetDualOutput() and ClearDualOutput() functions.
 */
typedef enum _dual_output_pin
{
	PIN_0=0,	/**<	pin0 of a I/O port */
	PIN_1=1,	/**<	pin1 of a I/O port */
	PIN_2=2,	/**<	pin2 of a I/O port */
	PIN_3=3,	/**<	pin3 of a I/O port */
	PIN_4=4,	/**<	pin4 of a I/O port */
	PIN_5=5,	/**<	pin5 of a I/O port */
	PIN_6=6,	/**<	pin6 of a I/O port */
	PIN_7=7		/**<	pin7 of a I/O port */
} OUTPUT_PIN;


/** @brief Set output pin
 * Write a logical one to the output pin of the specified port
 *
 * @code

  // Set pin7 of PORTE to 1 

  SetDualOutput(OUTPUT_PORTE,PIN_7);

 * @endcode
 *
 * @param port	port's name
 * @param pin	pin's port to set (PIN_0 to PIN_7)
 */
extern void SetDualOutput(OUTPUT_PORT port, OUTPUT_PIN pin);


/** @brief Clear output pin.
 * Write a logical zero to output pin of the specified port.
 *
 * @code

  // Clear pin7 of PORTE 

  ClearDualOutput(OUTPUT_PORTE,PIN_7);

 * @endcode
 *
 * @param port	port's name.
 * @param pin	pin's port to clear (PIN_0 to PIN_7)
 */
extern void ClearDualOutput(OUTPUT_PORT port, OUTPUT_PIN pin);


/** @brief Port input enumeration
 *
 * Use this enumeration with the GetDualInput() function.
 */
typedef enum _input_port
{
	INPUT_PORTB=0,		/**<	PORTB */
	INPUT_PORTE=1,		/**<	PORTE */
	INPUT_PORTF=2,		/**<	PORTF */
	INPUT_PORTG=3,		/**<	PORTF */
	INPUT_NONE=4		/**<	NONE  */
} INPUT_PORT;


/** @brief Pin input number
 *
 * Use this enumeration with the GetDualInput() function.
 */
typedef enum _input_pin
{
	INPUT_0=0x01,	/**<	Get pin 0 */
	INPUT_1=0x02,	/**<	Get pin 1 */
	INPUT_2=0x04,	/**<	Get pin 2 */
	INPUT_3=0x08,	/**<	Get pin 3 */
	INPUT_4=0x10,	/**<	Get pin 4 */
	INPUT_5=0x20,	/**<	Get pin 5 */
	INPUT_6=0x40,	/**<	Get pin 6 */
	INPUT_7=0x80	/**<	Get pin 7 */
} INPUT_PIN;


/** @brief Get input pin value
 *
 * @code

  UInt8 value;

  // Get value of pin 1 of PORTB

  value = GetDualInput(INPUT_PORTB,INPUT_1);

 * @endcode
 *
 * @param port		port where read the value
 * @param pin		pin number of port
 * @return the pin value: 0 or 1. if selected port is wrong, the function will return 0xFF.
 */
extern UInt8 GetDualInput(INPUT_PORT port,INPUT_PIN pin);

/** @brief Test communication between dualpob and pobeye
 *
 * @param Data
 * @return Echo back
 */
extern UInt8 GetEchoFromDual(UInt8 data);

/** @brief Ping a ax12 bioloid servomotor
 *
 * @param servo	Servomotor identifier
 * @return 1 if servomotor is detected, else 0
 */
extern UInt8 PingAX12Servo(UInt8 servo);

/** @brief Set AX12 position
 *
 * @param servo		Servomotor identifier
 * @param position	Servomotor position
 * @param speed		Servomotor speed
 */
extern void SetAX12Servo(UInt8 servo,UInt16 position, UInt16 speed);

/** @brief Set AX12 identifier.
 *
 * @warning if you use this function, connect only ONE AX12 servo on the dual-pob!
 *
 * @param id_servo	Identifier
 */
extern void SetAX12Id(UInt8 id_servo);

#ifdef __cplusplus
 }
#endif

#endif
