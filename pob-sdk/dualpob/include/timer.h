//
// Copyright 2008 POB-Technology. All rights reserved.
// POB-Technology PROPRIETARY/CONFIDENTIAL.
//


/** \anchor timer
 * 
 * @brief Timer functions
 *
 * @file
 *
 * Time event functions
 *
 * - To wait in your program, you can use the Wait_Us() or Wait_Ms() functions.
 * - If you want a periodic event, you can use the Timer1 function. This function use the interrupt timer1.
 *
 * @par timer1 event interrupt example code
 *
 * @code

	// This code example will generate a pulse signal on pin 2 of PORTE.

	UInt8 tick=0;

	DDRE=0x02; // pin PORTE pin2 is set as output 
	tick=0;

	// Init timer overflow to 7.5 ms
	Timer1Init(50536,TIMER1_8);
	
	// Main loop program
	while(1)
	{
		// Wait an overflow of timer:
		if( IsTimer1Overflow() == 1 )
		{
			// Clock output on PORTE2: 
			if(tick==0)
			{
				sbi(PORTE,2);
				tick=1;
			}
			else
			{
				cbi(PORTE,2);
				tick=0;
			}
		}
	}

 * @endcode
 */
#ifndef DUAL_POB_TIMER_H
#define DUAL_POB_TIMER_H


/** @brief Timer1 prescaler enumeration
 *
 */
typedef enum _timer1_prescaler
{
	TIMER1_STOP=0,	/**< no prescaler, timer1 off */
	TIMER1_1=1,		/**< timer prescaler 1 */
	TIMER1_8=2,		/**< timer prescaler 8 */
	TIMER1_64=3,	/**< timer prescaler 64 */
	TIMER1_256=4,	/**< timer prescaler 256 */
	TIMER1_1024=5,	/**< timer prescaler 1024 */
} TIMER1_PRESCALER;


/**
 * @name Timer1 event functions
 */
/*@{*/

/** @brief Init timer1 interrupt
 *
 * The timer1 will overflow when your delay is off.
 *
 * How to compute the delay parameter:
 *
 * <b>Delay parameter</b> = 65536 - <i>Your Timer</i> x ( <i>CPU Frequency</i> / <i>Prescaler</i> )
 *
 * With: 
 *  - <i>CPU Frequency</i> = 16 MHz
 *  - <i>Your timer</i> in seconds
 *  - <i>Prescaler</i> egual to 1, 8, 64, 256 or 1024.
 *
 * For example, to have a 7.5 ms period timer, the delay parameter is egual to 65536 - 0.0075 x ( 16000000 / 8 ) = 50536
 * 
 * @param delay			Delay (see formula to compute this value)
 * @param prescaler		Prescaler value
 */
void Timer1Init(UInt16 delay, TIMER1_PRESCALER prescaler);

/** @brief Stop timer1 interrupt
 *
 */
void Timer1Stop(void);

/** @brief Is the timer1 overflow?
 *
 * @return 1 if the timer1 overflow, else 0.
 */
UInt8 IsTimer1Overflow(void);


/** @brief Attach a function to timer overflow
 *
 * The function will be called at overflow of timer1.
 *
 * @param Process	User function
 *
 * @par Attach function example
 *
 * @code

  // This code example call the MyProcess function at overflow of timer1.

  void MyProcess(void)
  {
		//all the 7.5 ms, this function is runing at timer1 overflow
  }

  void main(void)
  {
		// Init timer:
		Timer1Init(50536,TIMER1_8);

		// Attach a function to timer1
		Timer1AttachFunction(MyProcess);

		while(1)
		{
			// Main loop
		}

  }

 * @endcode
 *
 */
void Timer1AttachFunction( void (*Process)(void) );

/** @brief Detach a function.
 *
 */
void Timer1DetachFunction(void);



/** @brief Generate pwm signal on a input pin.
 *
 * Period formula: delay = <i> CPU Frequency</i> / ( <b> your period in second </b> x <i> prescaler </i> ) -1
 *
 * With: 
 *  - <i>CPU Frequency</i> = 16 000 000.
 *  - <i>Your timer</i> in seconds.
 *  - <i>Prescaler</i> egual to 1, 8, 64, 256 or 1024.
 *
 * The pwm signal is generated on PIN3 of PORTE: You have to set PIN3 of PORTE as an output pin with the SetIOWay function.
 *
 * @param delayPinE3		Pwm period (see previous formula for compute this parameter).
 * @param prescaler			Timer prescaler.
 */
void PwmTimer3Init(UInt16 delayPinE3/*, UInt16 delayPinE4, UInt16 delayPinE5*/, TIMER1_PRESCALER prescaler );

/** @brief Set pwm period.
 *
 * @warning The pwm must be init with PwmTimer3Init function!
 * @param delay		New pwm period.
 */
void PwmTimer3SetPinE3(UInt16 delay);

/** @brief Stop pwm timer3.
 */
void PwmTimer3Stop(void);

//void PwmTimer3SetPinE4(UInt16 delay);
//void PwmTimer3SetPinE5(UInt16 delay);

/*@}*/

/**
 * @name Waiting...
 */
/*@{*/

/** @brief Wait...
 *
 * @param time_us	Delay in microseconds.
 */
void Wait_Us(UInt32 time_us);

/** @brief Wait in milliseconds.
 *
 * @param time_ms	Time to wait in milliseconds.
 */
void Wait_Ms(UInt32 time_ms);



/*@}*/

#endif
