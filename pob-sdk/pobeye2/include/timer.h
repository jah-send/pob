//
// Copyright 2009 POB-Technology. All rights reserved.
// POB-Technology PROPRIETARY/CONFIDENTIAL.
//

/** \anchor timer
 *
 * @brief Timer functions
 *
 * @file 
 *
 * Manage clock and timer interrupt.
 *
 * @par Timer0 example
 *
 * @code

 #include <pob-eye.h>

 UInt8 flag=0;

 // This function is called every 500ms by the Timer0 interrupt:
 void Process(void)
 {
	// Blink led:
	if(flag==0)
	{
		SetLed();
		flag=1;
	}
	else
	{
		ClearLed();
		flag=0;
	}
 }

 int main(void)
 {

	// Init pobeye2 cpu:
	InitPobeye2();

	// Init timer0 with 500ms delay and attach a function:
	InitTimer0(500000);
	Timer0AttachFunction(&Process);

	while(1)
	{
	}
 }

 * @endcode
 *
 * @par Timer0 second example
 *
 * @code

 #include <pob-eye.h>

 UInt8 flag=0;

 // This function is called every 500ms by the main function:
 void Process(void)
 {
	// Blink led:
	if(flag==0)
	{
		SetLed();
		flag=1;
	}
	else
	{
		ClearLed();
		flag=0;
	}
 }

 int main(void)
 {

	// Init pobeye2 cpu:
	InitPobeye2();

	// Init timer0 with 500ms delay:
	InitTimer0(500000);

	// Main loop:
	while(1)
	{
		if(IsTimer0Overflow()==1)
		{
			// If Timer0 triggers an interrupt, then call Process:
			Process();
		}
	}
 }

 * @endcode
 *
 */
#ifndef POB_TIMER_H
#define POB_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name Clock functions
 *
 * @brief Get clock tick (in 1ms unit).
 */
/*@{*/

/** @brief Start a 1 ms clock on Timer1 hardware.
 */
extern void		StartClock(void);

/** @brief Get current clock.
 *
 * @return Current clock in 1 ms unit.
 */
extern UInt32	GetClock(void);

/** @brief Wait a delay by using the Clock.
 *
 * @param	delayMs		Delay in milliseconds.
 */
//extern void		WaitMsClock(UInt32 delayMs);

/** @brief Stop the clock.
 */
extern void		StopClock(void);

/*@}*/

/** @brief Wait a delay in us.
 * This function use the Timer1 hardware.
 *
 * @param delayInUs		Delay in microseconds to wait.
 */
extern void		WaitUs( UInt32 delayInUs );

/**
 * @name Timer0 functions
 *
 * @brief Use the timer0 interrupt.
 */
/*@{*/

/** @brief Init Timer0 interrupt.
 *
 * The interrupt will be triggered at the end of delay.
 *
 * @param delay		Delay in microseconds.
 */
extern void		InitTimer0(UInt32 delay);

/** @brief Stop the timer0 interrupt.
 */
extern void		StopTimer0(void);

/** @brief Is Timer0 triggered an interrupt?
 *
 * @return 1 if the timer0 overflow, else 0.
 */
extern UInt8 	IsTimer0Overflow (void);

/** @brief Attach a function to timer0 interrupt.
 *
 * The function will be called at Timer0 interrupt.
 * @param Process		Pointer to a function.
 */
extern void 	Timer0AttachFunction (void(*Process)(void));

/** @brief Remove the function attached to Timer0.
 */
extern void 	Timer0DetachFunction (void);

/*@}*/

//rtc
//extern void InitRtc(void);
//extern UInt32 GetRtc(void);

/**
 * @name Watchdog functions
 *
 * @brief Use the hardware watchdog.
 */
/*@{*/

/** @brief Init watchdog timer.
 */
extern void InitWatchdog(UInt32 delay);

/** @brief Reset watchdog timer.
 */
extern void ResetWatchdog(void);
/*@}*/

#ifdef __cplusplus
 }
#endif

#endif
