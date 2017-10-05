//
// Copyright 2010 POB-Technology. All rights reserved.
//
#ifdef English_dox
/** \anchor minivex
 *
 * @brief MiniVEX sensor.
 *
 * @file
 *
 * The MiniVEX is a device compatible with the VEX sensor:
 * This device has:
 * - 1 VEX servomotor output.
 * - 1 analog input pin.
 * - 2 digital input/output pins.
 *
 * The 2 free digital input/output pins can be connected to:
 * - 1 VEX encoder.
 * - 1 VEX ultrasonic.
 * - or free for use.
 *
 */
#endif
#ifdef French_dox
/** \anchor minivex
 *
 * @brief Actionneur et Capteur MiniVEX.
 *
 * @file
 *
 * La carte MiniVEX est un matériel compatible avec les capteurs et actionneurs VEX :
 * Cette carte dispose de :
 * - 1 sortie servomoteur/moteur VEX.
 * - 1 entrée analogique.
 * - 2 broches d'entrée/sortie numériques.

 * Les deux broches numériques peuvent être connecté à :
 * - 1 encodeur VEX.
 * - 1 capteur ultrason VEX.
 * - ou être utilisé librement avec vos actionneurs/capteurs numériques.
 *
 */
#endif

#ifndef RS007_DEVICE_MINIVEX_H
#define RS007_DEVICE_MINIVEX_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef English_dox
/**
 * @name Input/Output pins.
 *
 * @brief Manage the MiniVex input/output pins as analog input or as digital input/output.
 */
 #endif
 #ifdef French_dox
/**
 * @name Broche d'entrées/sorties du MiniVex.
 *
 * @brief Gestion des entrées/sorties du MiniVex : Entrée analogique et Entrée/Sortie numérique.
 */
 #endif
/*@{*/

#ifdef English_dox
/** @brief Get analog value from the analog input of the MiniVEX.
 *
 * @param port      Port where the MiniVEX is connected (between 1 to 8).
 * @return The analog value.
 */
#endif
#ifdef French_dox
/** @brief Récupérer la valeur analogique de l'entrée analogique du MiniVEX.
 *
 * @param port      Port sur lequel le MiniVEX est connecté (entre 1 et 8).
 * @return La valeur analogique.
 */
#endif
extern UInt16 GetAnalogFromMiniVEX(UInt8 port);

#ifdef English_dox
/** @brief Init the pin way of the digital pin.
 *
 * @param port      Port where the MiniVEX is connected (between 1 to 8).
 * @param pin       Pin number (0 or 1).
 * @param way       Way: DIG_IN for input or DIG_OUT for output pin.
 */
#endif
#ifdef French_dox
/** @brief Initialiser le sens (entrée ou sortie) d'une broche numérique.
 *
 * @param port      Port sur lequel le MiniVEX est connecté (entre 1 et 8).
 * @param pin       Numéro de la broche (0 ou 1).
 * @param way       Sens : DIG_IN pour une broche d'entrée ou DIG_OUT pour une broche de sortie.
 */
#endif
extern void InitDigitalIOFromMiniVEX(UInt8 port, UInt8 pin, DIGITAL_WAY way);

#ifdef English_dox
/** @brief Get the state of a digital input pin.
 *
 * @param port      Port where the MiniVEX is connected (between 1 to 8).
 * @param pin       The Pin number (0 or 1).
 * @return 0 or 1.
 */
#endif
#ifdef French_dox
/** @brief Récupérer l'état d'une broche d'entrée numérique.
 *
 * @param port      Port sur lequel le MiniVEX est connecté (entre 1 et 8).
 * @param pin       Numéro de la broche (0 ou 1).
 * @return 0 ou 1.
 */
#endif
extern UInt8 GetDigitalIOFromMiniVEX(UInt8 port, UInt8 pin);

#ifdef English_dox
/** @brief Set a digital input pin to 1.
 *
 * @param port      Port where the MiniVEX is connected (between 1 to 8).
 * @param pin       The pin number (0 or 1).
 */
#endif
#ifdef French_dox
/** @brief Met à 1 une broche de sortie.
 *
 * @param port      Port sur lequel le MiniVEX est connecté (entre 1 et 8).
 * @param pin       Numéro de la broche (0 ou 1).
 */
#endif
extern void SetDigitalIOFromMiniVEX(UInt8 port, UInt8 pin);

#ifdef English_dox
/** @brief Clear a digital output pin.
 *
 * @param port      Port where the MiniVEX is connected (between 1 to 8).
 * @param pin       Pin number (0 or 1).
 */
#endif
#ifdef French_dox
/** @brief Met à 0 une broche de sortie.
 *
 * @param port      Port sur lequel le MiniVEX est connecté (entre 1 et 8).
 * @param pin       Numéro de la broche (0 ou 1).
 */
#endif
extern void ClearDigitalIOFromMiniVEX(UInt8 port, UInt8 pin);

/*@}*/

#ifdef English_dox
/**
 * @name VEX servomotors.
 *
 * @brief Manage VEX motors and servomotors.
 */
 #endif
 #ifdef French_dox
/**
 * @name Servomoteurs VEX.
 *
 * @brief Gestion des moteurs et des servomoteurs VEX.
 */
 #endif
/*@{*/

#ifdef English_dox
/** @brief Set the servomotor on the MiniVEX device.
 *
 * @param port      Port where the MiniVEX is connected (between 1 to 8).
 * @param Position  Servomotor's position.
 * @param Speed     Speed (between 1 and 31).
 */
#endif
#ifdef French_dox
/** @brief Positionner le servomoteur MiniVEX.
 *
 * @param port      Port sur lequel le MiniVEX est connecté (entre 1 et 8).
 * @param Position  Position du servomoteur.
 * @param Speed     Vitesse (de 1 à 31).
 */
#endif
void SetServoFromMiniVEX(UInt8 port, UInt16 Position, UInt8 Speed);

#ifdef English_dox
/** @brief Stop the servomotor on the MiniVEX.
 *
 * @param port      Port where the MiniVEX is connected (between 1 to 8).
 */
#endif
#ifdef French_dox
/** @brief Arrêter le servomoteur sur la carte MiniVEX.
 *
 * @param port     Port sur lequel le MiniVEX est connecté (entre 1 et 8).
 */
#endif
void StopServoFromMiniVEX(UInt8 port);

/*@}*/

#ifdef English_dox
/**
 * @name VEX Encoder.
 *
 * @brief Use the VEX Encoder sensor with the MiniVEX.
 */
#endif
#ifdef French_dox
/**
 * @name Encodeur VEX.
 *
 * @brief Utiliser l'encodeur VEX avec la carte MiniVEX.
 */
#endif
/*@{*/

#ifdef English_dox
/** @brief Init the Encoder sensor on the MiniVEX device.
 *
 * @param port      Port where the MiniVEX is connected (between 1 to 8).
 */
#endif
#ifdef French_dox
/** @brief Initialiser l'encodeur numérique sur la carte MiniVEX.
 *
 * @param port     Port sur lequel le MiniVEX est connecté (entre 1 et 8).
 */
#endif
extern void InitEncoderFromMiniVEX(UInt8 port);

#ifdef English_dox
/* @brief Get pulse time from the encoder on the MiniVEX device.
 *
 * @param port      Port where the MiniVEX is connected (between 1 to 8).
 * @return Pulse time in us.
 */
#endif
#ifdef French_dox
/* @brief Récupérer le créneaux temporel mesuré sur l'encodeur MiniVEX.
 *
 * @param port      Port sur lequel le MiniVEX est connecté (entre 1 et 8).
 * @return Le temps (en us).
 */
#endif
//extern UInt16 GetEncoderTimeFromMiniVEX(UInt8 port);

#ifdef English_dox
/** @brief Get RPM values from the encoder on the MiniVEX.
 *
 * @param port      Port where the MiniVEX is connected (between 1 to 8).
 * @return RPM values (in turn per minute).
 */
#endif
#ifdef French_dox
/** @brief Récupérer la valeur de tours par minute de l'encodeur sur la carte MiniVEX.
 *
 * @param port      Port sur lequel le MiniVEX est connecté (entre 1 et 8).
 * @return Valeur RPM (en tours/minute).
 */
#endif
extern UInt16 GetEncoderSpeedFromMiniVEX(UInt8 port);

/*@}*/

#ifdef English_dox
/**
 * @name VEX Ultrasonic.
 *
 * @brief Use the VEX Ultrasonic sensor with the MiniVEX.
 */
#endif
#ifdef French_dox
/**
 * @name Capteur ultrason VEX.
 *
 * @brief Utiliser le capteur ultrason VEX avec la carte MiniVEX.
 */
#endif
/*@{*/

#ifdef English_dox
/** @brief Init the ultrasonic sensor on the MiniVEX device.
 *
 * @param port      Port where the MiniVEX is connected (between 1 to 8).
 */
#endif
#ifdef French_dox
/** @brief Initialiser le capteur ultrason sur la carte MiniVEX.
 *
 * @param port      Port sur lequel le MiniVEX est connecté (entre 1 et 8).
 */
#endif
extern void InitUltrasonicFromMiniVEX(UInt8 port);

#ifdef English_dox
/* @brief Get the time computed by the ultrasonic sensor.
 *
 * @param port      Port where the MiniVEX is connected (between 1 to 8).
 * @return Time value.
 */
#endif
#ifdef French_dox
/* @brief Récupérer le temps mesuré par le capteur ultrason.
 *
 * @param port      Port sur lequel le MiniVEX est connecté (entre 1 et 8).
 * @return Temps mesuré.
 */
#endif
//extern UInt16 GetUltrasonicTimeFromMiniVEX(UInt8 port);

#ifdef English_dox
/** @brief Get the object distance front of the ultrasonic sensor.
 *
 * @param port      Port where the MiniVEX is connected (between 1 to 8).
 * @return Distance (in mm)
 */
#endif
#ifdef French_dox
/** @brief Récupérer la distance de l'objet devant le capteur ultrason.
 *
 * @param port      Port sur lequel le MiniVEX est connecté (entre 1 et 8).
 * @return Distance (en mm).
 */
#endif
extern UInt16 GetUltrasonicDistanceFromMiniVEX(UInt8 port);

#ifdef English_dox
/** @brief Set motor direction on the MiniVEX device.
 *
 * @param port      Port where the MiniVEX motor is connected (between 1 to 8).
 */
#endif
#ifdef French_dox
/** @brief Démarrer le moteur MiniVEX.
 *
 * @param port      Port sur lequel le moteur MiniVEX est connecté (entre 1 et 8).
 */
#endif
extern void SetMotorFromMiniVEX(UInt8 port, UInt8 direction);

#ifdef English_dox
/** @brief Stop motor on the MiniVEX device.
 *
 * @param port      Port where the MiniVEX motor is connected (between 1 to 8).
 */
#endif
#ifdef French_dox
/** @brief Stopper le moteur MiniVEX.
 *
 * @param port      Port sur lequel le moteur MiniVEX est connecté (entre 1 et 8).
 */
#endif
extern void StopMotorFromMiniVEX(UInt8 port);


#ifdef __cplusplus
 }
#endif

#endif
