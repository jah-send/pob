//
// Copyright 2010 POB-Technology. All rights reserved.
//

#ifdef English_dox
/** \anchor sensor
 *
 * @brief Manage sensor.
 *
 * @file
 *
 * The POB-Robotics-Suite has 8 ports, identify has 1 to 8.
 * You can plug different sensor on channel, likes:
 * - Light sensor
 * - GP2D12 infrared distance sensor
 * - RGB Led
 * - Contact sensor (or Bump sensor)
 * - Line follower
 * - Camera
 * - IR Beacon
 *
 * If you want read an analog input, see the \ref analog "analog functions".
 * If you want use instead the digital input/output pins, see the \ref io "input/output functions".
 *
 * The InitRobot function initialize all the low level hardware of the robot: You don't have to manage all the low level stuff.
 *
 *
 * @par Example: Init the POB-Robotics-Suite Hardware and Read a distance sensor
 *
 * @code

#include <pobRoboticSuite.h>

int main(void)
{
    UInt32 i;
    UInt32 value;
    SensorType * sensors;

    // Init hardware:
    InitCpu();
    InitUART0Intr(115200);
    sensors = InitRobot();

    for(i=0;i<CHANNEL_NUMBER;i++)
    {
        DebugPrintf("Sensor[%d] is: %d\r\n", i, sensors[i] );
    }


    while(1)
    {
        // Get distance from a GP2D12 Infrared sensor:

        // You have to connect this sensor on port 1 for this example:

        value = GetDistanceSensor(1);

        DebugPrintf("Distance from channel 0 is: %d\r\n", value);
    }

    return 0;
}

 * @endcode
 */
#endif

#ifdef French_dox
/** \anchor sensor
 *
 * @brief Gestion des capteurs sur le POB-Robotics-Suite.
 *
 * @file
 *
 * Le POB-Robotics-Suite a 8 ports, identifier par un numéro de 1 à 8.
 * Vous pouvez connecter différent capteurs sur les ports, comme:
 * - Capteur de lumière
 * - Capteur de distance infrarouge GP2D12
 * - Actionneur led RGB
 * - Capteur de contact
 * - Suiveur de ligne
 * - Caméra
 * - Balise infrarouge
 *
 * Si vous voulez lire directement une entrée analogique, il faut utiliser les \ref analog "fonctions analogiques".
 * Si vous voulez utiliser les entrées/sorties numériques des ports, il faut utiliser les \ref io "fonctions d'entrées/sorties".
 *
 * La fonction InitRobot initialise le bas niveau et tous les élements du robot: Vous n'avez pas à vous occuper de tout le bas niveau.
 *
 *
 * @par Exemple: Initialiser le POB-Robotics-Suite et lire un capteur de distance
 *
 * @code

#include <pobRoboticSuite.h>

int main(void)
{
    UInt32 i;
    UInt32 value;
    SensorType * sensors;

    // Initialisation du matériel :
    InitCpu();
    InitUART0Intr(115200);
    sensors = InitRobot();

    for(i=0;i<CHANNEL_NUMBER;i++)
    {
        DebugPrintf("Sensor[%d] is: %d\r\n", i, sensors[i] );
    }


    while(1)
    {
        // Lire la distance d'un capteur de distance infrarouge GP2D12 :

        // Vous avez à connecter ce capteur sur le port 1 pour cette exemple :

        value = GetDistanceSensor(1);

        DebugPrintf("Distance from port 1 is: %d\r\n", value);
    }

    return 0;
}

 * @endcode
 */
#endif
#ifndef RS007_SENSOR_DEVICE_H
#define RS007_SENSOR_DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Sensor type enumeration.
 */
typedef enum _sensor_type_
{
    SENSOR_UNKNOWN              = 0,    /**< [0] Unknown or no device found */
    SENSOR_ANA_IN               = 1,    /**< [1] An analog input */
    SENSOR_ANA_DIG_IN           = 2,    /**< [2] An analog input and a digital input */
    SENSOR_DIG_IN               = 3,    /**< [3] A digital input */
    SENSOR_DIG_OUT              = 4,    /**< [4] A digital output */

    SENSOR_I2C                  = 10,   /**< [10] An Unknown I2C device */

    SENSOR_I2C_LINESENSOR_SHARP = 11,   /**< [11] Line Follower */
    SENSOR_I2C_RGBLED           = 12,   /**< [12] Red Green Blue Led device */
    SENSOR_I2C_24LED            = 13,   /**< [13] 24 LED Display */
    SENSOR_I2C_MOTORDRIVER      = 14,   /**< [14] Direct Current Motor */
    SENSOR_I2C_ULTRASONIC       = 15,   /**< [15] Ultrasonic sensor */
    SENSOR_I2C_TEMPSENSOR       = 16,   /**< [16] Temperature sensor */
    SENSOR_I2C_EEPROM           = 17,   /**< [17] Eeprom memory */
    SENSOR_I2C_ACCELEROMETER    = 18,   /**< [18] Accelerometer sensor */
    SENSOR_I2C_COMPASS          = 19,   /**< [19] Compass */
    SENSOR_I2C_IRBEACON         = 20,   /**< [20] IR Beacon */
    SENSOR_I2C_IRDA             = 21,   /**< [21] IRDA transceiver */
    SENSOR_I2C_PORTEXPANDER     = 22,   /**< [22] Port expander */
    SENSOR_I2C_CAMERA           = 23,   /**< [23] Camera */
    SENSOR_I2C_VEXPANDER        = 24,   /**< [24] VEX port expander */
    SENSOR_I2C_MINIVEX          = 25,   /**< [25] MiniVEX port expander */
    SENSOR_I2C_IRFOLLOWER       = 26    /**< [26] IR Follower */
} SensorType;


#define CHANNEL_NUMBER      8   /**< Number of input/output channel */

#ifdef English_dox
/** @brief Initialize the hardware of the POB-Robotics-Suite.
 *
 * This functions initialize the i2c0 bus as master, the digital input/output, analog input and initialize various hardware on the robot.
 * The function search sensors connected on the port and initialize one by one the connected sensor.
 *
 * @return A pointer to an array of SensorType discovered on the port.
 */
#endif
#ifdef French_dox
/** @brief Initialiser le matériel du POB-Robotics-Suite.
 *
 * Cette fonction initialise le bus i2c0 comme maître, les entrées/sorties, les entrées analogiques et le bas niveau du robot.
 * La fonction cherche aussi les capteurs branchés sur les ports et les initialisent un par un.
 *
 * @return Un pointeur sur un tableau de SensorType.
 */
#endif
extern SensorType * InitRobot(void);


#ifdef English_dox
/** @brief Get distance from a GP2D12 Sharp sensor or a Line Sensor.
 *
 * @param port      Port where distance sensor is connected (from 1 to 8).
 * @return A distance in millimeter.
 */
#endif
#ifdef French_dox
/** @brief Récupérer la distance d'un capteur de distance GP2D12 ou d'un suiveur de ligne.
 *
 * @param port      Port sur lequel le capteur est connecté (entre 1 et 8).
 * @return La distance en millimétre.
 */
#endif
extern UInt32 GetDistanceSensor(UInt8 port);

#ifdef English_dox
/** @brief Get beacon status from the infrared sensor.
 *
 * @param port      Port where IR sensor is connected (from 1 to 8).
 * @param beacon    Beacon number (from 0to 15).
 * @return Beacon status.
 */
#endif
#ifdef French_dox
/** @brief Récupérer le satus de la balise infrarouge.
 *
 * @param port      Port sur lequel le capteur est connecté (entre 1 et 8).
 * @param beacon    Numéro de la balise à repérer (entre 0 et 15).
 * @return Status de la balise.
 */
#endif
extern UInt8 GetIRBeacon(UInt8 port, UInt8 beacon);

#ifdef English_dox
/** @brief Get light intensity from the light sensor.
 *
 * @param port      Port where light sensor is connected (from 1 to 8).
 * @return A percentage of ligth received (0% = dark, 100% = sun light).
 */
#endif
#ifdef French_dox
/** @brief Récupérer l'intensité lumineuse du capteur de lumière.
 *
 * @param port      Port sur lequel le capteur est connecté (entre 1 et 8).
 * @return Un pourcentage de l'intensité lumineuse (0% = obscurité, 100% = en plein lumière).
 */
#endif
extern UInt32 GetLightSensor(UInt8 port);

/** @brief Line sensor structure.
 */
typedef struct _LineSensor
{
    UInt16 left;     /**< Left value */
    UInt16 right;    /**< Right value */
    UInt16 sharp;    /**< Analog value of sharp sensor */
} LineSensor;

#ifdef English_dox
/** @brief Get sensor values of the Line Sensor.
 *
 * @param port
 * @param result
 */
#endif
#ifdef French_dox
/** @brief Récupérer les valeurs des capteurs du capteur de ligne.
 *
 * @param port
 * @param result
 */
#endif
extern void GetValuesFromLineSensor(UInt8 port,LineSensor *result);


#ifdef English_dox
/** @brief Initialize the camera of the Pob-Robotics-Suite.
 *
 * @warning You need to connect the camera sensor!
 */
#endif
#ifdef French_dox
/** @brief Initialiser la caméra.
 *
 * @warning Vous devez connecter la caméra sur le robot !
 */
#endif
extern void InitCamera(void);


#ifdef __cplusplus
 }
#endif

#endif

