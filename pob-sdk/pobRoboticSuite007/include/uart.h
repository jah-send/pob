//
// Copyright 2010 POB-Technology. All rights reserved.
//
#ifdef English_dox
/** \anchor uart
*
* @brief UART Communication.
*
* @file
*
* The UART bus interface is a slow serial bus.
*
* The POB-Robotics-Suite comes with 2 UARTs interface, named UART0 and UART1:
* - UART0 is connected on the USB.
* - UART1 is free for use (used by default for the wireless ZigBee option).
*
* @par Use the UART0 Interrupt
*
* @code

#include <pobRoboticSuite.h>

int main(void)
{
UInt8 value;

// Init CPU:
InitCpu();

// Init the uart 0 and use the hardware interrupt routine:
InitUART0Intr(115200);

while(1)
{
	if( GetByteFromUART0Intr(&value) == 1 )
	{
		// If a data is receveid from uart 0, then...

		// Send the received byte...
		SendByteToUART0(value);

	}
}

return 0;
}

* @endcode
*/
#endif
#ifdef French_dox
/** \anchor uart
*
* @brief Communication UART.
*
* @file
*
* Le bus UART est un bus série lent.
*
* Le POB-Robotics-Suite a deux interface série, nommées UART0 et UART1:
* - UART0 est connecté sur l'USB.
* - UART1 est libre d'utilisation (par défaut utilisé pour l'option sans fil ZigBee).
*
* @par Exemple pour utiliser l'UART0
*
* @code

#include <pobRoboticSuite.h>

int main(void)
{
    UInt8 value;

    // Initialisation du CPU:
    InitCpu();

    // Initialisation de l'uart 0 en utilisant l'interruption :
    InitUART0Intr(115200);

    while(1)
    {
        if( GetByteFromUART0Intr(&value) == 1 )
        {
            // Si une donnée est reçue sur l'uart0, alors...

            // ... renvoyé la donnée sur l'UART0...
            SendByteToUART0(value);

        }
    }

    return 0;
}

* @endcode
*/
#endif
#ifndef RS007_UART_H
#define RS007_UART_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef English_dox
/**
* @name UART0 functions
*
* @brief Communicate on UART0.
*/
/*@{*/

/**
* @brief Init UART0 (USB).
*
* @param baudrate		UART0 baudrate.
*/
#endif
#ifdef French_dox
/**
* @name Fonctions UART0
*
* @brief Communiquer sur le bus série UART0.
*/
/*@{*/

/**
* @brief Initialiser l'UART0 (USB).
*
* @param baudrate		Le débit du bus : 115200, 57600, 38400, 19200 ou 9600.
*/
#endif
extern void InitUART0(UInt32 baudrate);

#ifdef English_dox
/** @brief Init UART0 (USB) with an interrupt on reception.
*
* The UART0 reception use a hardware interrupt:
* No byte is lost during reception and you don't have to poll the UART.
*
* @param baudrate      UART0 baudrate.
*/
#endif
#ifdef French_dox
/** @brief Initialiser l'UART0 (USB) en activant l'interruption en réception.
 *
 * La réception UART0 utilise une interruption :
 * Aucun octet n'est perdu durant la réception et vous n'avez pas besoin de scruter l'UART0.
 *
 * @param baudrate      Le débit du bus : 115200, 57600, 38400, 19200 ou 9600.
 */
#endif
extern void InitUART0Intr(UInt32 baudrate);

#ifdef English_dox
/**
* @brief Send a byte to the UART0.
*
* @param  byte			the byte that will be sent
*/
#endif
#ifdef French_dox
/**
 * @brief Envoyer un octet sur l'UART0.
 *
 * @param  byte			L'octet à envoyer.
 */
#endif
extern void SendByteToUART0(UInt8 byte);

#ifdef English_dox
/**
* @brief Send a byte's array through the UART0.
*
* @param  Buffer		Pointer on byte's array.
* @param  Count		Number of bytes to send.
*/
#endif
#ifdef French_dox
/**
 * @brief Envoyer un tableau d'octets sur l'UART0.
 *
 * @param  Buffer		Pointeur sur le tableau d'octets à envoyer.
 * @param  Count		Nombre d'octets à envoyer.
 */
#endif
extern void SendBufferToUART0(UInt8 * Buffer,UInt32 Count);

#ifdef English_dox
/**
* @brief Get a byte from the UART0.
*
* Don't use this function if you are using the UART Interrupt!
*
* @return The byte from the UART.
*/
#endif
#ifdef French_dox
/**
 * @brief Récupérer un octet sur l'UART0.
 *
 * La fonction est bloquante.
 * N'utilisez pas cette fonction si vous utilisze l'interruption UART0 !
 *
 * @return L'octet reçu.
 */
#endif
extern UInt8 GetByteFromUART0(void);

#ifdef English_dox
/** @brief Get a byte from the UART0 Interrupt Buffer.
*
* @param[out] Data  Pointer to a byte where store the byte received.
* @return 1 if one byte is received, 0 if nothing is received.
*/
#endif
#ifdef French_dox
/** @brief Récupérer un octet du tampon de l'interruption de l'UART0.
 *
 * La fonction n'est pas bloquante.
 *
 * @param[out] Data     Pointeur vers un octet où stocker l'octet reçu.
 * @return 1 si un octet est reçu, 0 si aucune donnée n'est présente.
 */
#endif
extern UInt8 GetByteFromUART0Intr(UInt8 *Data);

#ifdef English_dox
/**
* @brief Get a byte from the UART0, and do not wait for any data.
*
* Don't use this function if you are using the UART0 Interrupt!
*
* @param[out] Data		Pointer to a byte where store the byte received.
* @return     1 if one byte is received, 0 if nothing is received.
*/
#endif
#ifdef French_dox
/**
 * @brief Récupérer un octet depuis l'UART0.
 *
 * La fonction n'est pas bloquante.
 * N'utilisez pas cette fonction si vous utilisez l'interruption UART0 !
 *
 * @param[out] Data		Pointeur sur un octet où stocker l'octet reçu.
 * @return     1 si un octet est reçu, 0 si aucune donnée n'est présente.
 */
#endif
extern UInt8 GetByteFromUART0NoWait(UInt8 *Data);

#ifdef English_dox
/**
* @brief Get an array of bytes from the UART0.
*
* @param[out] Buffer		Pointer on array where the bytes are stored.
* @param      Count		Number of bytes expected.
*/
#endif
#ifdef French_dox
/**
 * @brief Récupérer un tableau d'octets depuis l'UART0.
 *
 * La fonction est bloquante.
 *
 * @param[out] Buffer		Pointeur sur un tableau où écrire les octets reçus.
 * @param      Count		    Nombre d'octet à lire sur l'UART0.
 */
#endif
extern void GetBufferFromUART0(UInt8 *Buffer,UInt32 Count);

#ifdef English_dox
/*@}*/


/** \anchor uart1
*
* @name UART1 functions
*
* @brief Communicates on UART1.
*/
/*@{*/

/**
* @brief Init UART1.
*
* @param baudrate		UART1 baudrate.
*/
#endif
#ifdef French_dox
/*@}*/


/** \anchor uart1
 *
 * @name Fonctions UART1
 *
 * @brief Communiquer sur le bus UART1.
 */
/*@{*/

/**
 * @brief Initialiser le bus UART1.
 *
 * @param baudrate		Le débit du bus : 115200, 57600, 38400, 19200 ou 9600.
 */
#endif
extern void InitUART1(UInt32 baudrate);

#ifdef English_dox
/** @brief Init UART1 with an interrupt on reception.
*
* The UART1 reception use an hardware interrupt:
* No byte is lost during reception and you don't have to poll the UART.
*
* @param baudrate      UART1 baudrate.
*/
#endif
#ifdef French_dox
/** @brief Initialiser l'UART1 avec l'interruption activée en réception.
 *
 * L'UART1 utilise une interruption en réception :
 * Aucune donnée n'est perdu et vous n'avez pas à scruter l'UART en réception.
 *
 * @param baudrate      UART1 baudrate.
 */
#endif
extern void InitUART1Intr(UInt32 baudrate);

#ifdef English_dox
/**
* @brief Send a byte to the UART1.
*
* @param  byte			the byte that will be sent
*/
#endif
#ifdef French_dox
/**
 * @brief Envoyer un octet sur l'UART1.
 *
 * @param  byte			l'octet à envoyer.
 */
#endif
extern void SendByteToUART1(UInt8 byte);

#ifdef English_dox
/**
* @brief Send a byte's array through the UART1.
*
* @param  Buffer		Pointer on byte's array.
* @param  Count		Number of bytes to send.
*/
#endif
#ifdef French_dox
/**
 * @brief Envoyer un tableau d'octets sur l'UART1.
 *
 * @param  Buffer		Pointeur sur le tableau à envoyer.
 * @param  Count		Nombre d'octets à envoyer.
 */
#endif
extern void SendBufferToUART1(UInt8 * Buffer,UInt32 Count);

#ifdef English_dox
/**
* @brief Get a byte from the UART1.
*
* Don't use this function if you are using the UART Interrupt!
*
* @return The byte from the UART.
*/
#endif
#ifdef French_dox
/**
 * @brief Récupérer un octet sur l'UART1.
 *
 * La fonction est bloquante.
 * N'utilisez pas cette fonction si vous avez activé l'interruption en réception !
 *
 * @return L'octet reçu de l'UART.
 */
#endif
extern UInt8 GetByteFromUART1(void);

#ifdef English_dox
/** @brief Get a byte from the UART1 Interrupt Buffer.
*
* @param[out] Data  Pointer to a byte where store the byte received.
* @return 1 if one byte is received, 0 if nothing is received.
*/
#endif
#ifdef French_dox
/** @brief Récupérer un octet depuis le tampon d'interruption de l'uart.
 *
 * La fonction n'est pas bloquante.
 *
 * @param[out] Data  Pointeur sur un octet où stocker la donnée reçue.
 * @return 1 si un octet est reçu, 0 sinon.
 */
#endif
extern UInt8 GetByteFromUART1Intr(UInt8 *Data);

#ifdef English_dox
/**
* @brief Get a byte from the UART1, and do not wait for any data.
*
* Don't use this function if you are using the UART1 Interrupt!
*
* @param[out] Data		Pointer to a byte where store the byte received.
* @return     1 if one byte is received, 0 if nothing is received.
*/
#endif
#ifdef French_dox
/**
* @brief Récupérer un octet sur l'UART1.
*
* La fonction n'est pas bloquante.
* N'utilisez pas cette fonction si vous avez activé l'interruption en réception !
*
* @param[out] Data		Pointeur sur un octet où stocker l'octet reçu.
* @return     1 si un octet est reçu, 0 sinon.
*/
#endif
extern UInt8 GetByteFromUART1NoWait(UInt8 *Data);

#ifdef English_dox
/**
* @brief Get an array of bytes from the UART1.
*
* @param[out] Buffer		Pointer on array where the bytes are stored.
* @param      Count		Number of bytes expected.
*/
#endif
#ifdef French_dox
/**
* @brief Récupérer un tableau d'octet sur l'UART1.
*
* @param[out] Buffer		Pointeur sur le tableau où stocker les données reçues.
* @param      Count		Nombre d'octets à récupérer sur l'UART1.
*/
#endif
extern void GetBufferFromUART1(UInt8 *Buffer,UInt32 Count);
/*@}*/


#ifdef __cplusplus
}
#endif

#endif
