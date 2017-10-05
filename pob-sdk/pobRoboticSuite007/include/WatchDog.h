//
// Copyright 2010 POB-Technology. All rights reserved.
//
#ifdef English_dox
/** \anchor watchdog
 *
 * @brief WatchDog Management.
 *
 * @file
 *
 * The watchdog restart the hardware after a determined time if your program failed to reset the watchdog.
 * The watchdog is used in embedded software to reboot automaticaly hardware when an exception occurs.
 *
 * @par Watchdog example.
 *
 * @code

 #include <pobRoboticSuite.h>

int main(void)
{

    // Initialize the CPU:
    InitCpu();

    // Search and Init sensors connected on the port:
    // InitRobot initialize all the sensors connected on the robot's port.
    InitRobot();

    // Init UART0:
    InitUART0(115200);

    // Initialize the watchdog timer:
    InitWatchdog(700000);

    DebugPrintf("Hello world!\r\n");

    // Main loop:
    while(1)
    {
        // Reset the watchdog...
        ResetWatchdog();

        // wait sometimes... if the pob-robotics-suite reset, then decrease the time wait:
        WaitMs(3000);
    }

    return 0;
}

 * @endcode
 */
#endif
#ifdef French_dox
/** \anchor watchdog
 *
 * @brief Gestion du chien de garde.
 *
 * @file
 *
 * Le "chien de garde" redémarre le matériel au bout d'un certain temps si votre programme a échoué à remettre à zéro le chien de garde.
 * Le chien de garde est utilisé en embarqué pour redémarrer automatiquement le logiciel lorsque un problème survient.
 *
 * @par Exemple "chien de garde".
 *
 * @code

 #include <pobRoboticSuite.h>

 int main(void)
 {

	// Initialisation du CPU :
	InitCpu();

	// Cherche et initialise les capteurs connectés sur les ports du robot :
	InitRobot();

	// Initialisation de l'UART0 :
	InitUART0(115200);

	// Initialisation du chien de garde :
	InitWatchdog(700000);

	DebugPrintf("Hello world!\r\n");

	// Boucle principale :
	while(1)
	{
		// On remet à zéro le chien de garde...
		ResetWatchdog();

		// On attend un peu...
		// Si le robot redémarre, vous pouvez décrementer le temps :
		WaitMs(3000);
	}

	return 0;
 }

 * @endcode
 */
#endif
#ifndef RS007_WATCHDOG_H
#define RS007_WATCHDOG_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef English_dox
/** @brief Init the Watchdog.
 *
 * @param delay        Watchdog timer in us.
 */
#endif
#ifdef French_dox
/** @brief Initialisation du chien de garde.
 *
 * @param delay        Période du chien de garde en us.
 */
#endif
extern void InitWatchdog(UInt32 delay);

#ifdef English_dox
/** @brief Reset the watchdog timer.
 */
#endif
#ifdef French_dox
/** @brief Remet à zéro le chien de garde.
 */
#endif
extern void ResetWatchdog(void);


#ifdef __cplusplus
 }
#endif

#endif
