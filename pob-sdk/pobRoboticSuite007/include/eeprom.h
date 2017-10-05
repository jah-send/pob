//
// Copyright 2010 POB-Technology. All rights reserved.
//

#ifdef English_dox
/** \anchor eeprom
 *
 * @brief Eeprom access functions.
 *
 * @file
 *
 * You can read and write to the eeprom memory of the POB-Robotics-Suite to store sensors values, saved values...
 * - Your application has 40 K bytes of eeprom memory.
 * - The eeprom memory is a storage memory: Please note that access for read or write is slow.
 *
 * @par Read and Write into eeprom memory.
 *
 * @code

 #include <pobRoboticSuite.h>

 int main(void)
 {
	UInt32 i;
	UInt8 byte0, byte1;

	// Init Hardware:
	InitCpu();

	// Init all the robot part and init all the sensors connected on the robot's port.
	InitRobot();


	// Write 16 bytes into eeprom, starting from eeprom address 0.
	for(i=0; i < 16 ; i++)
	{
	WriteByteToEeprom(i, i);
	}


	// Read 2 bytes from eeprom memory at address 1 and adress 2.
	ReadByteFromEeprom(1,&byte0);
	ReadByteFromEeprom(2,&byte1);

	return 0;
 }

 * @endcode
 *
 */
#endif
#ifdef French_dox
/** \anchor eeprom
 *
 * @brief Fonction pour accéder à l'Eeprom.
 *
 * @file
 *
 * Vous pouvez lire et écrire dans la mémoire eeprom du robot POB-Robotics-Suite pour stocker vos valeurs et vos paramètres.
 * - Vous disposez de 40 K octets de mémoire eeprom.
 * - La mémoire eeprom est connectée sur le bus i2c : l'accès à cette mémoire peut être lente.
 *
 * @par Exemple pour lire et écrire en eeprom.
 *
 * @code

 #include <pobRoboticSuite.h>

 int main(void)
 {
	UInt32 i;
	UInt8 byte0, byte1;

	// Initialisation du CPU :
	InitCpu();

	// Initialisation du robot et des capteurs du robot :
	InitRobot();


	// On écrit 16 octets dans l'eeprom, en commencant depuis l'adresse 0.
	for(i=0; i < 16 ; i++)
	{
		WriteByteToEeprom(i, i);
	}


	// On lit 2 octets depuis la mémoire eeprom à l'adresse 1 et l'adresse 2.
	ReadByteFromEeprom(1,&byte0);
	ReadByteFromEeprom(2,&byte1);

	return 0;
 }

 * @endcode
 *
 */
#endif

#ifndef RS007_EEPROM_H
#define RS007_EEPROM_H

#ifdef __cplusplus
extern "C" {
#endif

#define EEPROM_SUCCESS				0   /**< Last operation in eeprom is a success. */
#define EEPROM_ERROR_OUT_OF_RANGE	1   /**< Memory Out of range. */

#ifdef English_dox
/** @brief Write a byte to Eeprom.
 *
 * @param addr		Address to write.
 * @param dat		Data to write.
 */
#endif
#ifdef French_dox
/** @brief Ecrire un octet en Eeprom.
 *
 * @param addr		Adresse où écrire l'octet.
 * @param dat		Octet à écrire.
 */
#endif
extern Int32 WriteByteToEeprom(Int32 addr, UInt8 dat);

#ifdef English_dox
/** @brief Write a buffer to Eeprom.
 *
 * @param addr		Address where write the buffer (start address).
 * @param size		Size of buffer.
 * @param buffer	Data to write.
 * @return 0 if no error, else Error code.
 */
#endif
#ifdef French_dox
/** @brief Ecrire un buffer en Eeprom.
 *
 * @param addr		Adresse où écrire le buffer (Adresse de départ).
 * @param size		Taille du buffer.
 * @param buffer	Buffer à écrire.
 * @return 0 si aucune erreur, sinon code d'erreur.
 */
#endif

extern Int32 WriteBufferToEeprom(Int32 addr, Int32 size, UInt8* buffer);

#ifdef English_dox
/** @brief Read a byte from Eeprom.
 *
 * @param addr		Address where read the data.
 * @param dat		Data read (out).
 * @return 0 if no error, else Error code.
 */
#endif
#ifdef French_dox
/** @brief Lire un octet depuis l'eeprom.
 *
 * @param addr		Adresse où lire.
 * @param dat		Octet lu (pointeur sur un octet).
 * @return 0 si aucune erreur, sinon code d'erreur.
 */
#endif

extern Int32 ReadByteFromEeprom(Int32 addr, UInt8* dat);

#ifdef English_dox
/** @brief Read a buffer from Eeprom.
 *
 * @param addr		Address where read the data (start address).
 * @param size		Number of bytes to read.
 * @param buffer	Data read (out).
 * @return 0 if no error,else Error code.
 */
#endif
#ifdef French_dox
/** @brief Lire un tableau depuis l'Eeprom.
 *
 * @param addr		Adresse où lire les données (Adresse de départ).
 * @param size		Nombre d'octets à lire.
 * @param buffer	Pointeur sur un tableau où placer les octets lus.
 * @return 0 si aucune erreur, sinon code d'erreur.
 */
#endif

extern Int32 ReadBufferFromEeprom(Int32 addr, Int32 size, UInt8* buffer);

#ifdef English_dox
/** @brief Erase all the Eeprom memory.
 *
 * @return 0 if no error, else Error code.
 */
#endif
#ifdef French_dox
/** @brief Effacer la mémoire Eeprom.
 *
 * @return 0 si aucune erreur, sinon code d'erreur.
 */
#endif

extern Int32 EraseEeprom();



#ifdef __cplusplus
 }
#endif

#endif
