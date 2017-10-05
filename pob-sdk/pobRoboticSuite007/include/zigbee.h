//
// Copyright 2010 POB-Technology. All rights reserved.
//
#ifdef English_dox
/** \anchor zigbee
 *
 * @brief ZigBee functions
 *
 * @file
 *
 * The ZigBee module is a wireless network for embedded system.
 *
 * On the robot, The ZigBee module is connected to the UART 1 (this is an optional module !)
 * It can works in 2 modes:
 * - Transparent mode, you use the ZigBee has a serial link with the \ref uart1 "UART 1 functions".
 * - API mode, you use the ZigBee GetBufferFromZigbee and SendBufferToZigbee functions.
 *
 *
 */
#endif
#ifdef French_dox
/** \anchor zigbee
 *
 * @brief Fonction module ZigBee
 *
 * @file
 *
 * Le module ZigBee permet d'avoir un réseau sans fil radio pour le robot.
 *
 * Sur le robot, le module ZigBee est connecté sur le port série UART 1 (Ce module est optionnel !).
 * Le module ZigBee peut fonctionner en 2 modes :
 * - mode Transparent, vous utilisez le ZigBee comme un lien série avec les \ref uart1 "fonctions UART 1".
 * - mode API, vous utilisez le ZigBee en mode paquet : vous pouvez utilisez les fonctions GetBufferFromZigbee et SendBufferToZigbee.
 *
 *
 */
#endif
#ifndef RS007_ZIGBEE_H
#define RS007_ZIGBEE_H

#ifdef __cplusplus
extern "C" {
#endif

#define ZIGBEE_OK               0       /**< Zigbee module ok */
#define ZIGBEE_ERROR            1       /**< Last operation failed */
#define ZIGBEE_TIMEOUT          2       /**< Timeout occurs during operation on Zigbee module */


#define ZIGBEE_BROADCAST_ADDR   0xFFFF   /**< Zigbee Broadcast address */

typedef enum _ZigbeeMode_
{
	ZIGBEE_MODE_API         = '1',      /**< Select API mode for ZigBee module */
	ZIGBEE_MODE_TRANSPARENT = '0'       /**< Select Transparent mode for ZigBee module */
} ZigbeeMode;

typedef enum _ZigbeeAddressMode_
{
	ZIGBEE_LARGE_ADDRESS = 1,           /**< Use a large address (32 bits address) */
	ZIGBEE_SHORT_ADDRESS = 0            /**< Use a short address (16 bits address) */
} ZigbeeAddress;

#ifdef English_dox
/** @brief Init the ZigBee module.
 *
 * @param baudrate      ZigBee baudrate (supported baudrate: 9600, 19200, 38400, 57600 and 115200).
 * @param mode          Select the ZigBee mode: API or Transparent.
 * @param address       Address of your ZigBee module.
 * @return ZIGBEE_OK if no error, else error code.
 */
#endif
#ifdef French_dox
/** @brief Initialiser le module ZigBee.
 *
 * @param baudrate      Débit (débit supporté : 9600, 19200, 38400, 57600 and 115200).
 * @param mode          Sélection du mode ZigBee : API ou Transparent.
 * @param address       Adresse de votre module ZigBee.
 * @return ZIGBEE_OK si aucune erreur, sinon code d'erreur.
 */
#endif
extern UInt8 InitZigbee(UInt32 baudrate, ZigbeeMode mode, UInt16 address);

#ifdef English_dox
/** @brief Get a buffer from a ZigBee module.
 *
 * Use this function only if you have set the ZigBee in API mode.
 * If you have init the module with Transparent mode, please use the \ref uart1 "UART 1 functions".
 *
 * @param buffer        Buffer where store the received data (you must declare a buffer of size + bytes minimum).
 * @param [out] length  Data's length.
 * @param [out] address Address of the sender.
 * @return ZIGBEE_OK if no error, else error code.
 *
 * @par Get a zigbee buffer example.
 *
 * @code

#include <pobRoboticSuite.h>

int main(void)
{
    UInt8 result;
    UInt32 size;
    UInt16 addr;
    UInt8 data[2+16];

    // init cpu and robot:
    InitCpu();
    InitRobot();

    // initialize the uart to usb at 115200 baudrate:
    InitUART0(115200);

    // initialize the zigbee module in API mode with address 1:
    InitZigbee(115200,ZIGBEE_MODE_API,1);

    while(1)
    {
        result = GetBufferFromZigbee(data,&size,&addr);

        if(result==ZIGBEE_OK)
        {
            DebugPrintf("Receiver Address: 0x%x Length: %d\r\n", addr, size);
        }

    }

    return 0;
}

 * @endcode
 */
#endif
#ifdef French_dox
/** @brief Récupérer un tableau d'octet depuis le module ZigBee.
 *
 * Utiliser cette fonction uniquement si vous êtes en mode API !
 * Si vous avez configurer le module en mode Transparent, il faut utiliser les \ref uart1 "fonctions UART 1".
 *
 * @param buffer        Pointeur sur un tableau où stocker les octets reçus (la taille minimale du tableau doit être votre taille + 16 octets).
 * @param [out] length  Nombre d'octets reçus.
 * @param [out] address Adresse de l'émetteur.
 * @return ZIGBEE_OK si aucune erreur, sinon code d'erreur.
 *
 * @par Exemple pour récupérer un tableau du module ZigBee.
 *
 * @code

 #include <pobRoboticSuite.h>

 int main(void)
 {
    UInt8 result;
    UInt32 size;
    UInt16 addr;
    UInt8 data[2+16];

    // initialisation du cpu et du robot :
    InitCpu();
    InitRobot();

    // initialisation du port série uart 0 :
    InitUART0(115200);

    // initialisation du module zigbee en mode API avec l'adresse 1 :
    InitZigbee(115200,ZIGBEE_MODE_API,1);

    while(1)
    {
        result = GetBufferFromZigbee(data,&size,&addr);

        if(result==ZIGBEE_OK)
        {
            DebugPrintf("Receiver Address: 0x%x Length: %d\r\n", addr, size);
        }

    }

    return 0;
 }

 * @endcode
 */
#endif
extern UInt8 GetBufferFromZigbee(UInt8 * buffer,UInt32 * length, UInt16 * address);

#ifdef English_dox
/** @brief Send a buffer to a ZigBee module.
 *
 * @param buffer    Buffer to send.
 * @param length    Buffer's length.
 * @param address   Address of the ZigBee receiver.
 * @param addressType   Type of address: ZIGBEE_LARGE_ADDRESS or ZIGBEE_SHORT_ADDRESS.
 * @return ZIGBEE_OK if no error, else error code.
 */
#endif
#ifdef French_dox
/** @brief Envoyer un tableau d'octet vers un module ZigBee.
 *
 * @param buffer    Tableau à envoyer.
 * @param length    Longueur des données à envoyer.
 * @param address   Adresse du module récepteur ZigBee.
 * @param addressType   Type de l'adresse : ZIGBEE_LARGE_ADDRESS ou ZIGBEE_SHORT_ADDRESS.
 * @return ZIGBEE_OK si aucune erreur, sinon code d'erreur.
 */
#endif
extern UInt8 SendBufferToZigbee(UInt8 * buffer, UInt32 length, UInt32 address, ZigbeeAddress addressType);

#ifdef English_dox
/** @brief Set the ZigBee address.
 *
 * @param address   The new address of your module.
 * @return ZIGBEE_OK if no error, else error code.
 */
#endif
#ifdef French_dox
/** @brief Configurer l'adresse du module ZigBee.
 *
 * @param address   La nouvelle adresse de votre module.
 * @return ZIGBEE_OK si aucune erreur, sinon code d'erreur.
 */
#endif
extern UInt8 SetZigbeeAddress(UInt16 address);


#ifdef __cplusplus
 }
#endif

#endif
