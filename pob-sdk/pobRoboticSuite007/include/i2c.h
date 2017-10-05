//
// Copyright 2010 POB-Technology. All rights reserved.
//

#ifdef English_dox
/** \anchor i2c
*
* @brief I2C Communication.
*
* @file
*
* The I2C bus interface is a fast serial bus with a master and multiple slave (up to 128).
*
* POB-Robotics-Suite comes with two I2C bus link, named i2c0 and i2c1.
* By default:
* - the i2c0 is used as a master i2c.
* - the i2c1 is connected to the low level motor mpu and the eeprom: don't use if you don't know exactly the low level hardware!
*
* A lot of sensors connected on the POB-Robotics-Suite use the i2c bus, if you want initialize all the sensors connected, see the \ref io "input/output functions".
*
*
* @par Read and Write data to a slave device.
*
* @code

#include <pobRoboticSuite.h>

int main(void)
{
	UInt8 buffer[4];

	InitCpu();

	// Search and Init sensors connected on the port:
	// InitRobot initialize the i2c0 bus at 400KHz speed as master i2c.
	InitRobot();

	// Set buffer with 2 bytes:
	buffer[0] = 0xAA;
	buffer[1] = 0x55;

	// Write 2 bytes to i2c0 slave 0xB0
	SendBufferToI2C0(0xB0,buffer,2);

	// Read 4 bytes from slace 0xB0
	GetBufferFromI2C0(0xB0,buffer,4);

	return 0;
}

* @endcode
*/
#endif
#ifdef French_dox
/** \anchor i2c
*
* @brief Communication I2C.
*
* @file
*
* Le bus I2C est un bus série rapide avec un maître et de multiples esclaves (jusqu'à 128).
*
* Le POB-Robotics-Suite a deux bus I2C, nommé i2c0 et i2c1.
* Par défaut :
* - i2c0 est utilisé pour relier les capteurs en tant que maître par le robot.
* - i2c1 est connecté à l'eeprom et à la partie bas niveau du robot : N'utilisez pas ce bus si vous ne connaissez pas exactement le matériel !
*
* Beaucoup de capteur du POB-Robotics-Suite utilise le bus i2c.
*
* @par Lire et écrire des données.
*
* @code

#include <pobRoboticSuite.h>

int main(void)
{
	 UInt8 buffer[4];

	 InitCpu();

	 // Cherche et initialise les capteur sur les ports du robot :
	 // InitRobot initialise le bus i2c0 à une vitesse de 400KHz en maître.
	 InitRobot();

	 // Ecrit 2 octets dans buffer :
	 buffer[0] = 0xAA;
	 buffer[1] = 0x55;

	 // Envoie le buffer à l'esclave 0xB0 sur le bus i2c0 :
	 SendBufferToI2C0(0xB0,buffer,2);

	 // Lit 4 octets à l'esclave 0xB0
	 GetBufferFromI2C0(0xB0,buffer,4);

	 return 0;
}

* @endcode
*/
#endif

#ifndef RS007_I2C_H
#define RS007_I2C_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef English_dox
/** @brief I2C Bus Speed.
 */
#endif
#ifdef French_dox
/** @brief Enumération des vitesses de bus I2C.
 */
#endif

typedef enum _i2c_speed
{
    I2C_100_KHZ=0,		/**< I2C speed frequency 100 KHz */
    I2C_400_KHZ=1		/**< I2C speed frequency 400 KHz */
} I2C_SPEED;

#ifdef English_dox
/**
 * @name i2c result code.
 *
 */
/*@{*/
#endif
#ifdef French_dox
/**
 * @name Résultat i2c.
 *
 */
/*@{*/
#endif

#define I2C_OK          0   /**< Last operation on i2c bus is OK. */
#define I2C_ERROR       1   /**< Error on i2c bus. */
#define I2C_ERROR_START 2   /**< Error when send START bit on i2c bus. */
#define I2C_ERROR_SEND  3   /**< Error when send data on i2c bus. */
#define I2C_BUSY        4   /**< i2c bus is busy. */
#define I2C_EMPTY       5   /**< i2c buffer is empty. */
#define I2C_TIMEOUT     6   /**< Operation timeout on i2c bus */
/*@}*/

#ifdef English_dox
/**
 * @name I2C0 Master functions
 *
 * @brief Use the I2C0 Bus as Master.
 */
/*@{*/
#endif
#ifdef French_dox
/**
 * @name Fonctions I2C0 maître
 *
 * @brief Utiliser le bus I2C0 en étant maître.
 */
/*@{*/
#endif

#ifdef English_dox
/**
 * @brief Initalize I2C0 bus.
 *
 * @param speed		Frequency speed of I2C bus.
 */
#endif
#ifdef French_dox
/**
 * @brief Initaliser le bus I2C0.
 *
 * @param speed		Vitesse du bus I2C0.
 */
#endif

extern void InitI2C0(I2C_SPEED speed);

#ifdef English_dox
/** @brief Write bytes array to a I2C0 device.
 *
 * @param addr      Address of the slave device on the I2C0 bus.
 * @param buffer    Buffer to send.
 * @param len       Lenght of data to send.
 * @return 0 if no error, else error code.
 */
#endif
#ifdef French_dox
/** @brief Envoyer un tableau d'octets vers un esclave sur le bus I2C0.
 *
 * @param addr      Adresse de l'esclave sur le bus I2C0.
 * @param buffer    Tableau à envoyer.
 * @param len       Longueur des données à envoyer.
 * @return 0 si aucune erreur, sinon code d'erreur.
 */
#endif

extern UInt32 SendBufferToI2C0(UInt8 addr, UInt8 *buffer, UInt32 len);

#ifdef English_dox
/** @brief Read bytes array from a I2C0 device.
 *
 * @param addr      Address of the slave device on the I2C0 bus.
 * @param buffer    Array where store the receveid bytes.
 * @param len       Number of bytes to read on the I2C0 device.
 * @return 0 if no error, else error code.
 */
#endif
#ifdef French_dox
/** @brief Lit un tableau d'octets depuis un esclave sur le bus I2C0.
 *
 * @param addr      Adresse de l'esclave sur le bus I2C0.
 * @param buffer    Pointeur sur un tableau où stocker les données lues.
 * @param len       Nombre d'octets à lire depuis l'esclave I2C0.
 * @return 0 si aucune erreur, sinon code d'erreur.
 */
#endif

extern UInt32 GetBufferFromI2C0(UInt8 addr, UInt8 *buffer, UInt32 len);

#ifdef English_dox
/*@}*/

/**
 * @name I2C1 Master functions
 *
 * @brief Use the I2C1 Bus as Master.
 */
/*@{*/
/**
 * @brief Initalize I2C1 bus.
 *
 * @param speed		Frequency speed of I2C bus.
 */
#endif
#ifdef French_dox
/*@}*/

/**
 * @name Fonctions maître I2C1
 *
 * @brief Utiliser le bus U2C1 en étant maître.
 */
/*@{*/
/**
 * @brief Initaliser le bus I2C1 en mode maître i2c.
 *
 * @param speed		Vitesse du bus i2c.
 */
#endif

extern void InitI2C1(I2C_SPEED speed);

#ifdef English_dox
/** @brief Write bytes array to a I2C1 device.
 *
 * @param addr      Address of the slave device on the I2C1 bus.
 * @param buffer    Buffer to send.
 * @param len       Lenght of data to send.
 * @return 0 if no error, else error code.
 */
#endif
#ifdef French_dox
/** @brief Envoyer un tableau d'octets à un esclave I2C1.
 *
 * @param addr      Adresse de l'esclave vers lequel envoyer.
 * @param buffer    Tableau à envoyer.
 * @param len       Nombre d'octets à envoyer.
 * @return 0 si aucune erreur, sinon code d'erreur.
 */
#endif

extern UInt32 SendBufferToI2C1(UInt8 addr, UInt8 *buffer, UInt32 len);

#ifdef English_dox
/** @brief Read bytes array from a I2C1 device.
 *
 * @param addr      Address of the slave device on the I2C1 bus.
 * @param buffer    Array where store the receveid bytes.
 * @param len       Number of bytes to read on the I2C1 device.
 * @return 0 if no error, else error code.
 */
#endif
#ifdef French_dox
/** @brief Recevoir un tableau d'octets depuis un esclave I2C1.
 *
 * @param addr      Adresse de l'esclave I2C1.
 * @param buffer    Pointeur sur un tableau où écrire les octets reçus.
 * @param len       Nombre d'octets à lire depuis l'esclave.
 * @return 0 si aucune erreur, sinon code d'erreur.
 */
#endif

extern UInt32 GetBufferFromI2C1(UInt8 addr, UInt8 *buffer, UInt32 len);
/*@}*/

#ifdef English_dox
/**
 * @name I2C0 Slave functions
 *
 * @brief Use the I2C0 Bus as Slave.
 */
/*@{*/

/** @brief Init I2C0 as Slave.
 *
 * @param address		I2C address of the device.
 * @param speed			Speed frequency of I2C bus.
 */
#endif
#ifdef French_dox
/**
 * @name Fonctions esclave I2C0
 *
 * @brief Utiliser le bus I2C0 en étant esclave.
 */
/*@{*/

/** @brief Initialiser le bus I2C0 en mode esclave.
 *
 * @param address		Adresse esclave.
 * @param speed			Vitesse du bus i2c.
 */
#endif

extern void InitSlaveI2C0(UInt8 address, I2C_SPEED speed);

#ifdef English_dox
/** @brief Get a buffer from the master i2c.
 *
 * @param data		Pointer to the received data.
 * @return Number of bytes received (0 if nothing).
 */
#endif
#ifdef French_dox
/** @brief Récupérer un buffer envoyé par un maître i2c.
 *
 * @param data		Pointer sur les données reçues.
 * @return Nombre d'octets reçues (0 si aucune donnée n'est présente).
 */
#endif

extern UInt8 GetBufferFromSlaveI2C0(UInt8 **data);

#ifdef English_dox
/** @brief Send a buffer on I2C bus.
 *
 * Warning, the buffer is send when master begins a read operation!
 *
 * @param buffer		Buffer to send.
 * @param size			Size of buffer.
 */
#endif
#ifdef French_dox
/** @brief Envoyer un buffer sur le bus i2c.
 *
 * Attention, le buffer est effectivement envoyé lorsque le maître commence une opération de lecture sur le bus i2c!
 *
 * @param buffer		Pointeur sur les données à envoyer.
 * @param size			Taille des données à envoyer.
 */
#endif

extern void SetBufferToSlaveI2C0(UInt8 *buffer, UInt8 size);

#ifdef English_dox
/** @brief Halt I2C0 Slave Hardware.
 */
#endif
#ifdef French_dox
/** @brief Arrêter l'esclave ic2.
 */
#endif

extern void HaltSlaveI2C0(void);
/*@}*/

#ifdef __cplusplus
}
#endif

#endif
