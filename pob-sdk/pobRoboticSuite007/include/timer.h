//
// Copyright 2010 POB-Technology. All rights reserved.
//

#ifdef English_dox
/** \anchor timer
 *
 * @brief Timer functions
 *
 * @file
 *
 * Manage clock and timer interrupt.
 *
 * @par Timer3 example
 *
 * @code

 #include <pobRoboticSuite.h>

 UInt8 flag=0;

 // This function is called every 500ms by the Timer3 interrupt:
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

	// Init cpu:
	InitCpu();

	// Init timer3 with 500ms delay and attach a function:
	InitTimer3(500000);
	Timer3AttachFunction(&Process);

	while(1)
	{
	}
 }

 * @endcode
 *
 * @par Timer3 second example
 *
 * @code

 #include <pobRoboticSuite.h>

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

	// Init cpu:
	InitCpu();

	// Init timer3 with 500ms delay:
	InitTimer3(500000);

	// Main loop:
	while(1)
	{
		if(IsTimer3Overflow()==1)
		{
			// If Timer3 triggers an interrupt, then call the function Process:
			Process();
		}
	}
 }

 * @endcode
 *
 */
#endif
#ifdef French_dox
/** \anchor timer
 *
 * @brief Gestion du temps
 *
 * @file
 *
 * Gérer l'horloge et le temps sur le robot.
 *
 * @par Exemple Timer3
 *
 * @code

 #include <pobRoboticSuite.h>

 UInt8 flag=0;

 // Cette fonction est appelée toutes les 500ms par l'interruption Timer3 :
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

    // Initialisation du cpu:
    InitCpu();

    // Initialisation du timer3 avec une période de 500ms et attacher une fonction à ce timer :
    InitTimer3(500000);
    Timer3AttachFunction(&Process);

    while(1)
    {
    }
 }

 * @endcode
 *
 * @par Second exemple avec le Timer3
 *
 * @code

 #include <pobRoboticSuite.h>

 UInt8 flag=0;

 // Cette fonction est appelée toutes les 500ms par la fonction main :
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

    // Initialisation du cpu :
    InitCpu();

    // Initialisation du timer3 avec une période 500ms :
    InitTimer3(500000);

    // Main loop:
    while(1)
    {
        if(IsTimer3Overflow()==1)
        {
            // Si l'interruption Timer3 est déclenché, alors la fonction Process est appelée :
            Process();
        }
    }
 }

 * @endcode
 *
 */
#endif
#ifndef RS007_TIMER_H
#define RS007_TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef English_dox
/**
 * @name Clock functions
 *
 * @brief Get clock tick (in 1ms unit).
 */
/*@{*/

/** @brief Start the clock !
 *
 * The function reset the current clock and init a clock on timer0 hardware.
 * Clock unit: 1 ms.
 */
#endif
#ifdef French_dox
/**
 * @name Fonctions d'horloge
 *
 * @brief Récupère le temps du robot (en unité de 1ms ).
 */
/*@{*/

/** @brief Démarre l'horloge !
 *
 * La fonction met à zéro l'horloge courante et initialise une nouvelle horloge sur le timer0.
 * Unité de l'horloge : 1 ms.
 */
#endif
extern void		StartClock(void);

#ifdef English_dox
/** @brief Get current clock.
 *
 * @return Current clock in 1 ms unit.
 */
#endif
#ifdef French_dox
/** @brief Récupère l'horloge courante.
 *
 * @return Valeur de l'horloge en unité de 1 ms.
 */
#endif
extern UInt32	GetClock(void);

#ifdef English_dox
/** @brief Stop the clock.
 */
#endif
#ifdef French_dox
/** @brief Arrête l'horloge.
 */
#endif
extern void		StopClock(void);

#ifdef English_dox
/*@}*/

/** @brief Wait a delay in microseconds.
 *
 * This function use the Timer1 hardware and it's very accurate.
 *
 * @param delayInUs		Delay in microseconds to wait.
 */
#endif
#ifdef French_dox
/*@}*/

/** @brief Attendre un certain délai en microsecondes.
 *
 * Cette fonction utilise le Timer1 et elle est très précise.
 *
 * @param delayInUs		Délai à attendre en microsecondes.
 */
#endif
extern void		WaitUs( UInt32 delayInUs );

#ifdef English_dox
/** @brief Wait a delay in milliseconds.
 *
 * This function use the Timer1 hardware and it's very accurate.
 *
 * @param delayInMs		Delay in milliseconds to wait.
 */
#endif
#ifdef French_dox
/** @brief Attendre un certain délai en millisecondes.
 *
 * Cette fonction utilise le Timer1 et elle est très précise.
 *
 * @param delayInMs		Délai à attendre en millisecondes.
 */
#endif
extern void WaitMs(UInt32 delayInMs);

#ifdef English_dox
/**
 * @name Timer3 functions
 *
 * @brief Use the timer3 interrupt.
 */
/*@{*/

/** @brief Init a timer on Timer3 hardware.
 *
 * An timer interrupt will be triggered at the end of delay.
 *
 * @param delay		Delay in microseconds.
 */
#endif
#ifdef French_dox
/**
 * @name Fonctions Timer3
 *
 * @brief Utilise l'interruption timer3.
 */
/*@{*/

/** @brief Initialiser le minuteur du Timer3.
 *
 * Une interruption sera générée à la fin du délai, puis l'interruption sera re-armée du même délai.
 *
 * @param delay		Délai en microsecondes.
 */
#endif
extern void		InitTimer3(UInt32 delay);

#ifdef English_dox
/** @brief Stop the timer3 interrupt.
 */
#endif
#ifdef French_dox
/** @brief Arrête l'interruption du Timer3.
 */
#endif
extern void		StopTimer3(void);

#ifdef English_dox
/** @brief Is Timer3 triggered an interrupt?
 *
 * @return 1 if the timer3 overflow, else 0.
 */
#endif
#ifdef French_dox
/** @brief Est ce que le Timer3 a déclenché une interruption ?
 *
 * @return 1 si le Timer3 a déclenché, sinon 0.
 */
#endif
extern UInt8 	IsTimer3Overflow (void);

#ifdef English_dox
/** @brief Attach a function to the Timer3.
 *
 * The Timer3 Interrupt will trigger the function in parameter.
 *
 * @param Process	User function
 *
 * @par Attach function example
 *
 * @code

  // This code call the MyProcess function at overflow of timer3.
  void MyProcess(void)
  {
		//all the 7.5 ms, this function is triggered by the Timer3 Interrupt.
  }

  void main(void)
  {
        InitCpu();
        InitRobot();

		// Init timer:
		Timer3Init(7500);

		// Attach a function to timer3
		Timer3AttachFunction(&MyProcess);

		while(1)
		{
			// Main loop
		}

  }

 * @endcode
 */
#endif
#ifdef French_dox
/** @brief Attacher une fonction au Timer3.
 *
 * A chaque interruption Timer3, la fonction attachée sera appelée.
 *
 * @param Process	La fonction
 *
 * @par Exemple pour attacher une fonction
 *
 * @code

 void MyProcess(void)
 {
    // Toutes les 7.5 ms, cette fonction sera appelée par le Timer3.
 }

 void main(void)
 {
	 InitCpu();
	 InitRobot();

	 // Initialiser le timer3 à une période de 7.5 ms :
	 Timer3Init(7500);

	 // On attache la fonction MyProcess au timer3
	 Timer3AttachFunction(&MyProcess);

	 while(1)
	 {
	  // Boucle principale
	 }

 }

 * @endcode
 */
#endif
extern void 	Timer3AttachFunction (void(*Process)(void));

#ifdef English_dox
/** @brief Remove the function attached to the Timer3.
 */
#endif
#ifdef French_dox
/** @brief Enlève la fonction attachée au Timer3.
 */
#endif
extern void 	Timer3DetachFunction (void);

/*@}*/

//real time clock is not connected on prs hardware
//extern void InitRtc(void);
//extern UInt32 GetRtc(void);


#ifdef __cplusplus
 }
#endif

#endif
