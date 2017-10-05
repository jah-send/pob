//
// Copyright 2010 POB-Technology. All rights reserved.
//
#ifdef English_dox
/** \anchor utils
 *
 * @brief Utils functions
 *
 * @file
 *
 * When you develop on the robot, you could need various utility functions:
 * - Convert data to hexadecimal or decimal string,
 * - Wait some times...
 *
 */
#endif
#ifdef French_dox
/** \anchor utils
 *
 * @brief Fonctions utilitaires
 *
 * @file
 *
 *  Vous pouvez avoir besoin de fonctions diverses pour programmer le robot :
 * - Convertir un nombre vers une chaine de caractères,
 * - Attendre...
 *
 */
#endif
#ifndef RS007_UTILS_H
#define RS007_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Get UInt32 from buffer.
 */
#define getUInt32(integer,buffer)	integer = ((buffer)[0]<<24)| ((buffer)[1]<<16)|((buffer)[2]<<8)|((buffer)[3])

/** @brief Get UInt16 from buffer.
 */
#define getUInt16(integer,buffer)	integer = ((buffer)[0]<<8)|((buffer)[1])

/** @brief Set UInt32 into a buffer.
 */
#define setUInt32(integer,buffer)	buffer[0] = (integer>>24); buffer[1] = (integer>>16);\
	buffer[2] = (integer>>8); buffer[3] = (integer)

/** @brief Set UInt16 into a buffer.
 */
#define	setUInt16(integer,buffer)	buffer[0] = (integer>>8);	buffer[1] = (UInt8)(integer)

#ifdef English_dox
/** @brief Send a string on UART0
 *
 * @param str				String to send (end of string with NULL character)
 */
#endif
#ifdef French_dox
/** @brief Envoyer une chaîne de caractères sur l'UART0.
 *
 * @param str			Pointeur sur la chaîne de caractères (Doit être finie par le caractère NULL)
 */
#endif
extern void SendString(Int8 *str);

#ifdef English_dox
/** @brief Convert an integer to a base-10 ASCII string.
 *
 * @param data				Data to convert
 * @param [out] result		Pointer to a char array. You must allocate char array!
 * @return Lenght of char array
 */
#endif
#ifdef French_dox
/** @brief Convertir un entier vers de l'ASCII base 10.
 *
 * @param data				Donnée à convertir
 * @param [out] result		Pointeur sur un tableau de caractères. Vous devez allouer ce tableau.
 * @return Longueur de la chaîne de caractère.
 */
#endif
extern UInt32 Bin2Dec(Int32 data,char *result);

#ifdef English_dox
/** @brief Convert a byte to a base-16 ASCII string.
 *
 * @param data				Data to convert
 * @param [out] result		Pointer to a char array. You must allocate the char array!
 */
#endif
#ifdef French_dox
/** @brief Convertir un octet vers de l'ASCII hexadécimal.
 *
 * @param data				Donnée à convertir.
 * @param [out] result		Pointeur vers un tableau de caractères. Vous devez allouer ce tableau.
 */
#endif
extern void Bin2Hex(UInt8 data,char *result);

#ifdef English_dox
/** @brief Convert a base-16 ASCII string to a byte.
 *
 * @param hex				Pointer to the ASCII string (2 bytes lenght).
 * @param [out] bin			Pointer to the binary byte.
 * @return 1 if success and bin has the byte.
 */
#endif
#ifdef French_dox
/** @brief Convertir un tableau ASCII base 16 vers un octet.
 *
 * @param hex				Pointeur sur la chaîne ASCII (2 octets de longueur).
 * @param [out] bin			Pointeur sur un octet.
 * @return 1 si la convertion est ok, sinon 0.
 */
#endif
extern UInt8 Hex2Bin(UInt8 *hex,UInt8 *bin);

#ifdef English_dox
/** @brief Wait (a multiple of 1ms)...
 *
 * This functions is not accurate as WaitUs or WaitMs (see \ref timer "Timer functions").
 *
 * @param delay_ms		Delay in milliseconds.
 */
#endif
#ifdef French_dox
/** @brief Attendre (un multiple de 1ms)...
 *
 * La fonction n'est pas aussi précise que WaitUs ou WaitMs (voir \ref timer "Gestion du temps").
 *
 * @param delay_ms		Delai à attendre (en unité 1 milliseconde).
 */
#endif
extern void DelayMs(UInt32 delay_ms);


#ifdef English_dox
/** @brief Init the random function with a seed.
 *
 * @param seed  Seed.
 */
#endif
#ifdef French_dox
/** @brief Initialise la graine de départ aléatoire.
 *
 * @param seed  La graine de départ.
 */
#endif
extern void InitRand(Int32 seed);

#ifdef English_dox
/** @brief Get a random number.
 * @return a random number.
 */
#endif
#ifdef French_dox
/** @brief Récupére un nombre aléatoire.
 * @return Un nombre aléatoire.
 */
#endif
extern Int32 GetRand(void);



#ifdef English_dox
/** @brief Like the printf function on UART0.
 */
#endif
#ifdef French_dox
/** @brief Comme la fonction printf du langage C sur l'UART0.
 */
#endif
extern int DebugPrintf(const char *format, ...);

#ifdef English_dox
/** @brief Like the sprintf function.
 */
#endif
#ifdef French_dox
/** @brief Comme la fonction sprintf.
 */
#endif
extern int DebugSprintf(char *out, const char *format, ...);

#ifdef __cplusplus
 }
#endif

#endif
