//
// Copyright 2010 POB-Technology. All rights reserved.
//

#ifdef English_dox
/** \anchor analog
 *
 * @brief Analog functions
 *
 * @file
 *
 * The POB-Robotics-Suite comes with 8 analog input ports.
 * Each analog input measures a voltage between 0 Volts to 3.3 Volts and convert it to a 10-bits value.
 *
 * If you want use instead the digital input/output pins, see the \ref io "input/output functions".
 *
 * @par Input analog example
 *
 * @code

 #include <pobRoboticSuite.h>

 int main(void)
 {
	UInt16 result;

	// Init CPU:
	InitCpu();

	// Search and Init Devices connected on the POB-Robotics-Suite ports:
	InitRobot();


	// Read the analog value of port 2:
	result = GetAnalog(2);

	return 0;
 }

 * @endcode
 */
#endif
#ifdef French_dox
/** \anchor analog
 *
 * @brief Fonctions analogiques
 *
 * @file
 *
 * Le POB-Robotics-Suite a 8 ports analogiques.
 * Ses ports analogiques mesurent une tension compris entre 0 et 3.3 Volts et la convertit en une valeur sur 10 bits.
 *
 * Si vous souhaitez utiliser une entrée/sortie numérique, allez voir \ref io "fonctions d'entrées/sorties".
 *
 * @par Example d'entrée analogique
 *
 * @code

 #include <pobRoboticSuite.h>

 int main(void)
 {
	UInt16 result;

	// Initialise le CPU:
	InitCpu();

	// Recherche et initialise les périphériques connectés sur les ports du POB-Robotics-Suite :
	InitRobot();

	// Lit la valeur analogique du port 2 du robot :
	result = GetAnalog(2);

	return 0;
 }

 * @endcode
 */
#endif

#ifndef RS007_ANALOG_H
#define RS007_ANALOG_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef English_dox
/** @brief Get a analog value from an analog input.
 *
 * @param port      An analog port (between 1 to 8).
 * @return Analog value between 0 and 1024.
 */
#endif
#ifdef French_dox
/** @brief Récupère la valeur analogique depuis un port du robot.
 *
 * @param port      Le port sélectionné (entre 1 et 8).
 * @return La valeur analogique entre 0 et 1024.
 */
#endif
extern UInt16 GetAnalog(UInt8 port);

#ifdef __cplusplus
 }
#endif

#endif
