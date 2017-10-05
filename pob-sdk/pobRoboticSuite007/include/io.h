//
// Copyright 2010 POB-Technology. All rights reserved.
//

#ifdef English_dox
/** \anchor io
*
* @brief Manage digital I/O.
*
* @file
*
* The POB-Robotics-Suite comes with 8 digital input/output pins:
* - Each pin can be configured has input or output pin.
* - On a pin, you can clear or set a digital output channel or get value of an digital input channel.
*
* The digital pins is 5V tolerant.
*
* If you want read an analog input, see the \ref analog "analog functions".
*
* The InitRobot function initialize all the low level hardware of the robot: You don't have to manage all the low level stuff.
*
* @par Input/Output example
*
* @code

#include <pobRoboticSuite.h>

int main(void)
{
	UInt32 result;

	// Init CPU:
	InitCpu();

	// Init robot, search and init devices connected on the POB-Robotics-Suite ports:
	InitRobot();


	// Write 1 to input port 3:
	SetDigitalIO(3);

	// Wait some times...
	WaitUs(10000);

	// Clear port 3:
	ClearDigitalIO(3);

	// Read input of port 4:
	result = GetDigitalIO(4);

	return 0;
}

* @endcode
*/
#endif
#ifdef French_dox
/** \anchor io
*
* @brief Gestion des entrées/sorties numériques.
*
* @file
*
* POB-Robotics-Suite a 8 ports d'entrées/sorties numérique :
* - Chaque port est automatiquement configuré en entrée ou en sortie suivant le type de capteur que vous branchez.
* - Sur un port numérique, vous pouvez mettre à 0 ou à 1 une sortie numérique ou récupérer l'état d'une entrée numérique.
*
* Les broches sont 5V tolérantes.
*
* Si vous voulez lire une entrée analogique, il faut voir  les \ref analog "fonctions analogiques".
*
* La fonction InitRobot initialise tout le bas niveau du robot : Vous n'avez pas à gérer toutes les initialisations bas niveau.
*
* @par Exemple Entrées/Sorties
*
* @code

#include <pobRoboticSuite.h>

int main(void)
{
	UInt32 result;

	// Initialisation du CPU:
	InitCpu();

	// Initialisation du robot, recherche et initialisation des capteurs connectés sur les ports du POB-Robotics-Suite :
	InitRobot();

	// Il vous faut un 'bumper' connecté sur le port 3.

	// Met à 1 le port 3 :
	SetDigitalIO(3);

	WaitUs(10000);

	// Met à 0 le port 3:
	ClearDigitalIO(3);

	// Lecture du port 4 :
	result = GetDigitalIO(4);

	return 0;
}

* @endcode
*/
#endif

#ifndef RS007_IO_H
#define RS007_IO_H


#ifdef __cplusplus
extern "C" {
#endif

#ifdef English_dox
/** @brief Get digital state of a port.
*
* @param port      Port of the digital input (between 1 and 8).
* @return 0 or 1.
*/
#endif
#ifdef French_dox
/** @brief Récupérer l'état du port (0 ou 1).
*
* @param port      Numéro du port de l'entrée numérique (entre 1 et 8).
* @return 0 ou 1.
*/
#endif
extern UInt32 GetDigitalIO(UInt8 port);

#ifdef English_dox
/** @brief Set a digital output to 1.
*
* @param port      Port of the digital output (between 1 and 8).
*/
#endif
#ifdef French_dox
/** @brief Met à 1 une sortie numérique.
 *
 * Ne fonctionne que si un capteur 'sortie numérique' est connecté sur le port.
 *
 * @param port      Numéro du port (entre 1 et 8).
 */
#endif
extern void SetDigitalIO(UInt8 port);

#ifdef English_dox
/** @brief Clear a digital port (Set 0 to an output).
*
* @param port      Port of the digital output.
*/
#endif
#ifdef French_dox
/** @brief Met à 0 une sortie numérique.
 *
 * Ne fonctionne que si un capteur 'sortie numérique' est connecté sur le port.
 *
 * @param port      Numéro du port (entre 1 et 8).
 */
#endif
extern void ClearDigitalIO(UInt8 port);

#ifdef English_dox
/** @brief Power on the robot led.
*/
#endif
#ifdef French_dox
/** @brief Allume la led arriére du robot.
 */
#endif
extern void SetLed(void);

#ifdef English_dox
/** @brief Power off the robot led.
*/
#endif
#ifdef French_dox
/** @brief Eteint la led arriére du robot.
 */
#endif
extern void ClearLed(void);

#ifdef English_dox
/** @brief Get the button state at the back of robot.
*
* @return 1 if button pressed, else 0.
*/
#endif
#ifdef French_dox
/** @brief Récupérer l'état du bouton arriére du robot.
 *
 * @return 1 si le bouton est pressé, sinon 0.
 */
#endif
extern UInt8 GetButton(void);

#ifdef __cplusplus
}
#endif


#endif // POB_IO_H
