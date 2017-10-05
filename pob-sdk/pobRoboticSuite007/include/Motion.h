//
// Copyright 2010 POB-Technology. All rights reserved.
//
#ifdef English_dox
/** \anchor uccomm
 *
 * @brief Manage the servomotors, motors and low level motion.
 *
 * @file
 *
 * The POB-Robotics-Suite has 2 microcontrollers (or MCU: Micro Controller Unit):
 * - a main microcontroller, named UC1, where you develop and manage all the robot resources.
 * - a second microcontroller, named UC2, manage the low level hardware: direct current motor, servomotors, wheel's encoder...
 *
 * UC1 and UC2 are linked by a I2C bus (named i2c1). You have access to UC2's functions from this file likes:
 * - Direct current motors.
 * - Servomotor movement.
 * - [X.Y] Position.
 * - Motion functions.
 *
 * @par Example Go to [x,y] point.
 *
 * @code

#include <pobRoboticSuite.h>

int main(void)
{
    Status status;

    InitCpu();

    // Init the communication between microcontrollers of the robot:
    InitRobot();

    // Go to [0,200] at speed of 100 mm/s:
    GoToXY(0,200,100);

    // Wait end of 'go to' function:
    GetStatus(&status);
    while( status.eventGoToXY != 0)
    {
        GetStatus(&status);
    }

    return 0;
}

 * @endcode
 */
#endif
#ifdef French_dox
/** \anchor uccomm
 *
 * @brief Gestion moteurs, servomoteurs, mouvement du POB-Robotics-Suite.
 *
 * @file
 *
 * Le POB-Robotics-Suite dispose de 2 microcontrôleurs (en anglais: MCU, Micro Controller Unit) :
 * - le microcontrôleur principal, nommé UC1, sur lequel votre programme tourne et depuis lequel vous gérez tout le robot.
 * - le second microcontrôleur, nommé UC2, gére le bas niveau : moteur courant continu, déplacement, servomoteurs...
 *
 * Les deux microcontrôleurs UC1 et UC2 sont reliés par le bus I2C (i2c1). Vous avez accès aux fonctionnalités d'UC2 par ce fichier :
 * - Contrôle des 2 moteurs à courant continu.
 * - Mouvement des servomoteurs.
 * - Position [X.Y].
 * - Etat du robot.
 *
 * @par Exemple pour aller à un point [x,y].
 *
 * @code

 #include <pobRoboticSuite.h>

 int main(void)
 {
	Status status;

	InitCpu();

	// Initialise le robot (dont la communication entre les deux microcontrôleurs):
	InitRobot();

	// Aller à [0,200] avec une vitesse de 100 mm/s:
	GoToXY(0,200,100);

	// On attend la fin de la fonction 'GoToXY' en demandant le status :
	GetStatus(&status);
	while( status.eventGoToXY != 0)
	{
		GetStatus(&status);
	}

	return 0;
 }

 * @endcode
 */
#endif
#ifndef RS007_UC_COMM_H
#define RS007_UC_COMM_H

#ifdef __cplusplus
extern "C" {
#endif

#define SLAVE_ADDR			0xB0	/**< I2C Address of UC2 microcontroller */

#define SERVO_NUMBER	        8       /**< Servomotor numbers. */

#ifdef English_dox
/** @brief Status structure.
 */
#endif
#ifdef French_dox
/** @brief Structure de status.
 */
#endif
typedef struct _status_
{
    Int32       x;                  /**< X Position of robot */
    Int32       y;                  /**< Y Position of robot */
    UInt32      wheelRightDistance; /**< Distance covered by the right wheel */
    UInt32      wheelLeftDistance;  /**< Distance covered by the left wheel */
    UInt8       firmwVersion;       /**< Firmware version */
    UInt8       eventGoToXY;        /**< event of "Go to XY" function (0 if "go to" function is over) */
    UInt8       eventDoRotation;    /**< event of "Do Rotation" function (0 if "rotation" function is over) */
    UInt8       eventMove;          /**< event of "Movement" function (0 if end of movement function) */
    UInt8       isDcMotorStop;      /**< Egual to 0 if dc motor stopped. */
} Status;

#ifdef English_dox
/** @brief Get UInt32 from a UC2 buffer.
 */
#endif
#ifdef French_dox
/** @brief Get UInt32 from a UC2 buffer.
 */
#endif
#define getUInt32FromUC2(integer,buffer)	integer = ((buffer)[3]<<24)| ((buffer)[2]<<16)|((buffer)[1]<<8)|((buffer)[0])

#ifdef English_dox
/** @brief Get UInt16 from a UC2 buffer.
 */
#endif
#ifdef French_dox
/** @brief Get UInt16 from a UC2 buffer.
 */
#endif
#define getUInt16FromUC2(integer,buffer)	integer = ((buffer)[1]<<8)|((buffer)[0])

#ifdef English_dox
/** @brief Set a UInt32 into a buffer for UC2.
 */
#endif
#ifdef French_dox
/** @brief Set a UInt32 into a buffer for UC2.
 */
#endif
#define setUInt32ForUC2(integer,buffer)		buffer[3] = (integer>>24); buffer[2] = (integer>>16);\
	buffer[1] = (integer>>8); buffer[0] = (integer)

#ifdef English_dox
/** @brief Set UInt16 into a buffer for UC2.
 */
#endif
#ifdef French_dox
/** @brief Set UInt16 into a buffer for UC2.
 */
#endif
#define	setUInt16ForUC2(integer,buffer)	buffer[1] = (integer>>8);	buffer[0] = (UInt8)(integer)

#ifdef English_dox
/** \anchor move_base
 *
 * @name Manage motor and basic movement of the robot.
 *
 * @brief
 */
#endif
#ifdef French_dox
/** \anchor move_base
 *
 * @name Effectuer des mouvements de base au robot et lire l'état du robot.
 *
 * @brief
 */
#endif
/*@{*/

#ifdef English_dox
/** @brief Go to [X,Y] at a specified speed from the origin of the robot.
 *
 *
 * @param x     X position in mm.
 * @param y     Y position in mm.
 * @param speed Speed in mm/s (130 mm/s maximum).
 */
#endif
#ifdef French_dox
/** @brief Aller à [X,Y] à une certaine vitesse depuis l'origine du robot.
 *
 *
 * @param x     position X en mm.
 * @param y     position Y en mm.
 * @param speed Vitesse en mm/s (vitesse max 130 mm/s).
 */
#endif
extern void GoToXY(Int32 x, Int32 y, UInt32 speed);

#ifdef English_dox
/** @brief Go to [X,Y] at a specified speed from the current position of robot.
 *
 *
 * @param x     X position in mm.
 * @param y     Y position in mm.
 * @param speed Speed in mm/s (130 mm/s maximum).
 */
#endif
#ifdef French_dox
/** @brief Aller à [X,Y] à une certaine vitesse depuis la position actuelle du robot.
 *
 *
 * @param x     position X en mm.
 * @param y     position Y en mm.
 * @param speed Vitesse en mm/s (vitesse max 130 mm/s).
 */
#endif
extern void GoToXYRelative(Int32 x, Int32 y, UInt32 speed);

#ifdef English_dox
/** @brief Make a rotation.
 *
 * @param alpha     Rotation angle (in degree).
 * @param speed     Speed (in mm/s, 130 mm/s maximum).
 */
#endif
#ifdef French_dox
/** @brief Effectuer une rotation.
 *
 * @param alpha     Angle de rotation (en degrés).
 * @param speed     Vitesse (en mm/s, maximum 130 mm/s).
 */
#endif
extern void DoRotation(Int32 alpha, UInt32 speed);

#ifdef English_dox
/** @brief Set coefficient on movement (translation and rotation)
 * This coefficient are set for the function GoToXY and DoRotation and can help the robot on ground.
 * By default, coefficient are all egual to 1.
 *
 * @param leftRot       Rotation coefficient on left wheel.
 * @param leftTrans     Translation coefficient on left wheel.
 * @param rightRot      Rotation coefficient on right wheel.
 * @param rightTrans    Translation coefficient on right wheel.
 */
 #endif
#ifdef French_dox
/** @brief Configure les coefficients sur les mouvements du robot.
 * Les coefficients s'appliquent sur les translations et les rotations du robot (les fonctions DoRotation et GoToXY).
 * Cela peut vous aider suivant le type de sol sur lequel se déplace le robot. Par défaut les coefficients sont à 1.
 *
 * @param leftRot       Coefficient sur les rotations de la roue gauche.
 * @param leftTrans     Coefficient sur translations de la roue gauche.
 * @param rightRot      Coefficient sur les rotations de la roue droite.
 * @param rightTrans    Coefficient sur les translations de la roue droite.
 */
#endif
extern void SetCoeffMove( Int8 leftRot, Int8 leftTrans, Int8 rightRot, Int8 rightTrans);

#ifdef English_dox
/** @brief Get status of UC2.
 *
 * You can have access of UC2 status by this function:
 * - Wheel distance made by robot.
 * - End of movement.
 * - End of rotation.
 * - Is dc motor stopped?
 *
 * @param status        Pointer to a valid status structure.
 */
#endif
#ifdef French_dox
/** @brief Récupérer le status du microcontrôleur UC2.
 *
 * Par cette fonction, vous avez accès :
 * - Distance parcourue par le robot.
 * - Evénement fin de mouvement.
 * - Evénement fin de rotation.
 * - Moteur arrêté ou non ?
 *
 * @param status        Pointeur sur une structure Status valide.
 */
#endif
extern void GetStatus(Status *status);


#ifdef English_dox
/** @brief Get position [X.Y] and orientation of robot.
 *
 * Position are in millimeters and orientation in degree.
 *
 * @param [out] x           Pointer to a integer for store X's position.
 * @param [out] y           Pointer to a integer for store Y's position.
 * @param [out] orientation Pointer to a integer for store orientation.
 */
#endif
#ifdef French_dox
/** @brief Récupérer la position [X.Y] et l'orientation du robot.
 *
 * La position [X.Y] est en millimétre et l'orientation est en degrés.
 *
 *
 * @param [out] x           Pointeur sur un entier pour stocker la position X.
 * @param [out] y           Pointeur sur un entier pour stocker la position Y.
 * @param [out] orientation Pointeur sur un entier pour stocker l'orientation.
 */
#endif
extern void GetPosition(Int32 *x, Int32 *y, Int32 *orientation);

#ifdef English_dox
/** @brief Reset current position of robot.
 *
 */
#endif
#ifdef French_dox
/** @brief Remet à zéro la position actuelle du robot.
 *
 */
#endif
extern void ResetPosition(void);


#ifdef English_dox
/** @brief Set the direct current motor movement.
 *
 * A negative value will turn wheel backward, a positive value will turn wheel forward.
 * A zero value will stop the wheel.
 *
 * @param wheelLeft		Speed of Wheel Left in mm/s (between -150 and 150).
 * @param wheelRight	    Speed of Wheel Right in mm/s (between -150 and 150).
 */
#endif
#ifdef French_dox
/** @brief Configurer les moteurs à courant continu.
 *
 * Une valeur négative fait tourner la roue en arriére, une valeur positive entraine la roue en avant.
 * Une valeur à zéro arrête le moteur.
 *
 * @param wheelLeft		Vitesse roue gauche en mm/s (entre -150 et 150).
 * @param wheelRight	    Vitesse roue droite en mm/s (entre -150 et 150).
 */
#endif
extern void SetMotor(Int16 wheelLeft, Int16 wheelRight);

#ifdef English_dox
/** @brief Stop direct current motor.
 */
#endif
#ifdef French_dox
/** @brief Arrêter les moteurs à courant continu.
 */
#endif
extern void StopMotor(void);

/*@}*/

#ifdef English_dox
/** @brief Set the direct current motor movement with PWM values.
 *
 * You control the direct current motor by his PWM values.
 *
 * A negative value will turn wheel backward, a positive value will turn wheel forward.
 * A zero value will stop the wheel.
 *
 * @param wheelLeft			PWM Wheel Left: between -255 and 255.
 * @param wheelRight	    PWM Wheel Right: between -255 and 255.
 */
#endif
#ifdef French_dox
/** @brief Configurer les moteurs à courant continu avec les valeurs PWM.
 *
 * Vous pilotez directement le PWM des deux moteurs.
 *
 * Une valeur négative fait tourner la roue en arriére, une valeur positive entraine la roue en avant.
 * Une valeur à zéro arrête le moteur.
 *
 * @param wheelLeft		Valeur du PWM roue gauche : entre -255 et 255.
 * @param wheelRight	    Valeur du PWM roue droite : entre -255 et 255.
 */
#endif
extern void SetPwmMotor( Int16 wheelLeft,Int16 wheelRight);

#ifdef English_dox
/** \anchor servo
 *
 * @name Servomotor management.
 *
 * @brief
 */
/*@{*/

/** @brief Set a servomotor at a specified position and speed.
 *
 * If the servomotor is switch off, the servomotor start!
 *
 * If you have configured the servomotor in degrees with SetServoUnit, then the position parameter is between 0 and 360 degrees.
 *
 * @param servo     Servomotor identifier, between 1 and 8.
 * @param position  Position (between 0 and 255).
 * @param speed     Speed (between 0 and 31).
 */
#endif
#ifdef French_dox
/** \anchor servo
 *
 * @name Gestion des servomoteurs.
 *
 * @brief
 */
/*@{*/

/** @brief Configurer un servomoteur à une certaine position et une certaine vitesse.
 *
 * Si le servomoteur est arrêté, le servomoteur démarre.
 *
 * Si vous avez configurer le servomoteur en degrés (avec SetServoUnit) alors la position en degrés entre 0 et 360.
 *
 * @param servo     Numéro du servomoteur à configurer, entre 1 et 8.
 * @param position  Position (entre 0 et 255).
 * @param speed     Vitesse (entre 0 et 31).
 */
#endif
extern void SetServo(UInt8 servo, UInt16 position, UInt8 speed);

#ifdef English_dox
/** @brief Servomotor unit enumeration.
 */
#endif
#ifdef French_dox
/** @brief Enumeration unité servomoteur.
 */
#endif
typedef enum _servo_unit
{
    SERVO_UNIT_DEFAULT = 0,     /**< Default's unit. */
    SERVO_UNIT_DEGREES = 1      /**< Servomotor position in degrees. */
} ServoUnit;

#ifdef English_dox
/** @brief Set unit of the servomotor's position.
 *
 * If you set unit in SERVO_UNIT_DEGREES, then all the servomotor management is in degrees from 0 to 360.
 *
 * @param unit      SERVO_UNIT_DEFAULT or SERVO_UNIT_DEGREES
 */
#endif
#ifdef French_dox
/** @brief Configurer l'unité de position du servomoteur.
 *
 * Si vous configurez l'unité en SERVO_UNIT_DEGREES, alors toutes les positions des servomoteurs sont en degrés de 0 à 360.
 *
 * @param unit      SERVO_UNIT_DEFAULT ou SERVO_UNIT_DEGREES
 */
#endif
extern void SetServoUnit( ServoUnit unit);


#ifdef English_dox
/** @brief Swith on a servomotor.
 *
 * @param servo     Servomotor identifier.
 */
#endif
#ifdef French_dox
/** @brief Allumer un servomoteur.
 *
 * @param servo     Numéro du servomoteur.
 */
#endif
extern void SwitchOnServo(UInt8 servo);

#ifdef English_dox
/** @brief Swith off a servomotor.
 *
 * Servomotor power is switch off.
 *
 * @param servo     Servomotor identifier.
 */
#endif
#ifdef French_dox
/** @brief Eteindre un servomoteur.
 *
 * L'alimentation du servomoteur est coupée.
 *
 * @param servo     Numéro du servomoteur.
 */
#endif
extern void SwitchOffServo(UInt8 servo);

#ifdef English_dox
/** @brief Switch on all the servomotors.
 */
#endif
#ifdef French_dox
/** @brief Allumer tous les servomoteurs.
 */
#endif
extern void SwitchOnAllServo(void);

#ifdef English_dox
/** @brief Switch off all the servomotors.
 */
#endif
#ifdef French_dox
/** @brief Eteindre tous les servomoteurs.
 */
#endif
extern void SwitchOffAllServo(void);

#ifdef English_dox
/*@}*/

/** @brief Get analog values from UC2.
 *
 * The analog values from UC2 are used to detect POB's hardware.
 *
 * But you can use it to expand the analog input of your robot by using the reserved analog pins:
 * Use this function only if you know exactly the low level hardware!
 *
 * @par Get analogs.
 *
 * @code

#include <pobRoboticSuite.h>

int main(void)
{
    // Declare an array of 8 values.
    UInt16 arrayAnalog[8];

    // Init CPU:
    InitCpu();

    // Init the communication between microcontrollers of the robot:
    InitRobot();


    // Get the analog values from UC2:
     GetAnalogsFromUc2(arrayAnalog);

    return 0;
}

 * @endcode
 *
 * @param [out] analog		Pointer to an array of 8 analog values.
 */
#endif
#ifdef French_dox
/*@}*/

/** @brief Récupérer les valeurs analogiques du microcontrôleur UC2.
 *
 * Les valeurs analogiques de UC2 sont utilisées pour détecter les capteurs POB.
 *
 * Si vous connaissez exactement votre matériel, vous pouvez utiliser les valeurs analogiques de UC2 pour augmenter le nombre de ports analogiques !
 *
 * @par Lire les valeurs analogiques.
 *
 * @code

 #include <pobRoboticSuite.h>

 int main(void)
 {
    // Création d'un tableau de 8 valeurs.
    UInt16 arrayAnalog[8];

    // Initialisation du CPU :
    InitCpu();

    // Initialisation de tout les élements du robot :
    InitRobot();


    // Récupérer les valeurs analogiques de UC2 :
    GetAnalogsFromUc2(arrayAnalog);

    return 0;
 }

 * @endcode
 *
 * @param [out] analog		Pointeur sur un tableau de 8 valeurs.
 */
#endif
extern void GetAnalogsFromUc2(UInt16 *analog);

#ifdef English_dox
/**
 * @name Movement management.
 *
 * @brief Play a movement with the robot's wheel.
 */
/*@{*/

/** @brief Init a new wheel movement.
 *
 * @param number        Number of wheel movement you want to do.
 * @param speed         Speed of all the movement (in mm/s, maximum 130 mm/s).
 */
#endif
#ifdef French_dox
/**
 * @name Gestion des mouvements.
 *
 * @brief Faire des déplacement au robot.
 */
/*@{*/

/** @brief Initialiser une nouvelles séquence de déplacement.
 *
 * @param number        Nombre de mouvement dans cette nouvelle séquence.
 * @param speed         Vitesse des mouvements (en mm/s, 130 mm/s maximum).
 */
#endif
extern void InitNewMovement(UInt32 number, UInt32 speed);

#ifdef English_dox
/** @brief Add a wheel movement.
 *
 * @param index         Movement index.
 * @param x             X Position (in mm).
 * @param y             Y Position (in mm).
 */
#endif
#ifdef French_dox
/** @brief Ajouter un mouvement dans la séquence.
 *
 * @param index         Numéro du mouvement.
 * @param x             Position X (en mm).
 * @param y             Position Y (en mm).
 */
#endif
extern void AddXYMovement(UInt32 index,Int32 x,Int32 y);

#ifdef English_dox
/** @brief Play the wheel movement.
 *
 * All the movement added by AddXYMovement will be played.
 */
#endif
#ifdef French_dox
/** @brief Jouer la séquence de mouvement.
 *
 * Tout les mouvements ajoutés par la fonction AddXYMovement vont être joué.
 */
#endif
extern void PlayMovement(void);

#ifdef English_dox
/*@}*/

/**
 * @name Servomotor motion.
 *
 * @brief Play a motion with the servomotors.
 *
 */
/*@{*/

/** @brief Init a servomotor motion.
 *
 * @param number    Number of motion (maximum number 16).
 * @param speed     Speed of motion (between 1 and 31).
 *
 * @par Servomotor motion example.
 *
 * @code

#include <pobRoboticSuite.h>

UInt16 motion0[SERVO_NUMBER] = {
    0,    0,      0,      0,   0,  0,  0,  0
};

UInt16 motion1[SERVO_NUMBER] = {
    0,    100,    100,    100, 0,   0,  0,  0
};

UInt16 motion2[SERVO_NUMBER] = {
    0,    250,    250,    250, 0,  0,  0,  0
};

int main(void)
{

    // Init CPU:
    InitCpu();

    // Init the communication between microcontrollers of the robot:
    InitRobot();

    // Init a motion with 3 motion with speed of 8:
    InitServoMotion(3,8);

    // Add motion:
    AddMotion(0,motion0);
    AddMotion(1,motion1);
    AddMotion(2,motion2);

    // Play!
    PlayMotion(0);

    while(1)
    {
    }
}

 * @endcode
 */
#endif
#ifdef French_dox
/*@}*/

/**
 * @name Gestion des mouvements servomoteurs.
 *
 * @brief Effectuer plusieurs mouvements avec les servomoteurs.
 *
 */
/*@{*/

/** @brief Initialiser une nouvelle séquence de mouvement servomoteur.
 *
 * Vous pouvez avoir au maximum 16 séquences de mouvement.
 *
 * @param number    Nombre de mouvement (au maximum 16).
 * @param speed     Vitesse des mouvements (de 1 à 31).
 *
 * @par Exemple de mouvement servomoteur.
 *
 * @code

 #include <pobRoboticSuite.h>

 // Création des tableaux des mouvements :

 UInt16 motion0[SERVO_NUMBER] = {
 0,    0,      0,      0,   0,  0,  0,  0
 };

 UInt16 motion1[SERVO_NUMBER] = {
 0,    100,    100,    100, 0,   0,  0,  0
 };

 UInt16 motion2[SERVO_NUMBER] = {
 0,    250,    250,    250, 0,  0,  0,  0
 };

 int main(void)
 {

    // Initialisatio du CPU et du robot :
    InitCpu();
    InitRobot();

    // Initialisation d'une séquence servomoteur avec 3 mouvements à la vitesse de 8 :
    InitServoMotion(3,8);

    // Ajout des mouvements :
    AddMotion(0,motion0);
    AddMotion(1,motion1);
    AddMotion(2,motion2);

    // On joue la séquence !
    PlayMotion(0);

    while(1)
    {
    }
 }

 * @endcode
 */
#endif
extern void InitServoMotion(UInt8 number, UInt8 speed);

#ifdef English_dox
/** @brief Add a motion.
 *
 * @param index     Motion's index.
 * @param position  Pointer to a array of position.
 */
#endif
#ifdef French_dox
/** @brief Ajouter un mouvement à la séquence.
 *
 * @param index     Index du mouvement servomoteur.
 * @param position  Pointeur sur un tableau de 8 positions servomoteur.
 */
#endif
extern void AddServoMotion(UInt8 index, UInt16 *position);

#ifdef English_dox
/** @brief Play the servomotor motion.
 *
 * @param inLoop     0 stop at the end of motion, 1 to play in loop the motion.
 */
#endif
#ifdef French_dox
/** @brief Jouer la séquence de mouvement servomoteur.
 *
 * @param inLoop     0 pour stopper la séquence à la fin, 1 pour jouer en boucle la séquence.
 */
#endif
extern void PlayServoMotion(UInt8 inLoop);

#ifdef English_dox
/** @brief Stop motion.
 */
#endif
#ifdef French_dox
/** @brief Arrêter la séquence en cours.
 */
#endif
extern void StopServoMotion(void);

#ifdef English_dox
/*@}*/

/**
 * @name Trigonometry.
 *
 * @brief
 *
 */
/*@{*/

/** @brief Get cosinus from an angle in degrees.
 *
 * @param angle     Angle (in degrees).
 * @return Cosinus value.
 */
#endif
#ifdef French_dox
/*@}*/

/**
 * @name Trigonométrie.
 *
 * @brief
 *
 */
/*@{*/

/** @brief Récupérer le cosinus à partir d'un angle.
 *
 * @param angle     Angle (en degrés).
 * @return La valeur Cosinus.
 */
#endif
extern Int16 GetCos(UInt16 angle);

#ifdef English_dox
/** @brief Get sinus from an angle in degrees.
 *
 * @param angle     Angle (in degrees).
 * @return Sinus value.
 */
#endif
#ifdef French_dox
/** @brief Récupérer le sinus à partir un angle.
 *
 * @param angle     Angle (en degrés).
 * @return La valeur Sinus.
 */
#endif
extern Int16 GetSin(UInt16 angle);

//extern Int16 GetArcCos(Int32 value);
//extern Int16 GetArcSin(Int32 value);
/*@}*/

#ifdef __cplusplus
 }
#endif

#endif
