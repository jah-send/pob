
//
// Copyright 2010 POB-Technology. All rights reserved.
//

#ifdef English_dox
/** \anchor io_uc1
 *
 * @brief Low level input/output of microcontroller.
 *
 * @file
 *
 * This file provides access to the low level input/output of the microcontroller.
 *
 * Don't use this functions if you don't know exactly the microcontroller hardware, please use instead:
 * - Analog input channels: \ref analog "analog functions",
 * - Digital input/output pins: \ref io "input/output functions"
 *
 * @warning Don't use this functions if you don't know exactly the hardware!
 *
 *
 * @par Initialize input/output.
 *
 * @code

#include <pobRoboticSuite.h>

int main(void)
{
    UInt8 flag = 0;

    // Initialize the microcontroller of the robot:
    InitCpu();

    // Warning, if you have connected a sensor on port 1, you can destroy it with this code!

    // Set digital 0 has output:
    InitMcuDigitalIO(DIG0, DIG_OUT);

    // Main loop:
    while(1)
    {
        // Create an output signal on DIG0 with a pulse 100 us:

        if(flag==0)
        {
            SetMcuDigitalIO(DIG0);
            flag = 1;
        }
        else
        {
            ClearMcuDigitalIO(DIG0);
            flag = 0;
        }

        WaitUs(100);
    }

    return 0;
}

 * @endcode
 */
#endif
#ifdef French_dox
/** \anchor io_uc1
 *
 * @brief Entrées/Sorties bas niveau du microcontrôleur.
 *
 * @file
 *
 * Les fonctions de ce fichier vous donnent accès aux entrées/sorties numérique bas niveau du microcontrôleur du robot.
 *
 * Attention, utilisez avec précaution ces fonctions ! Vous pouvez à la place utiliser les fonctions suivantes :
 * - Entrées analogiques : \ref analog "fonctions analogiques",
 * - Entrées/Sorties numériques : \ref io "fonctions e/s numériques"
 *
 * @warning N'utilisez pas les fonctions de ce fichier si vous ne connaissez pas exactement le matériel !
 *
 *
 * @par Initialiser une broche d'entrée/sortie.
 *
 * @code

 #include <pobRoboticSuite.h>

 int main(void)
 {
	UInt8 flag = 0;

	// Initialisation du microcontrôleur du robot :
	InitCpu();

	// Attention de ne pas connecter directement un capteur sur le port 1 du robot !

	// Configuration de la broche 0 en sortie :
	InitMcuDigitalIO(DIG0, DIG_OUT);

	// Boucle principale :
	while(1)
	{
		// On crée un signal carré de 100 us sur la broche 0 :

		if(flag==0)
		{
			SetMcuDigitalIO(DIG0);
			flag = 1;
		}
		else
		{
			ClearMcuDigitalIO(DIG0);
			flag = 0;
		}

		WaitUs(100);
	}

	return 0;
 }

 * @endcode
 */
#endif

#ifndef RS007_MCU_IO_H
#define RS007_MCU_IO_H


#ifdef __cplusplus
extern "C" {
#endif

#ifdef English_dox
/**
 * @name Input/Output functions
 *
 * @brief Manage Input/Output channels.
 */
/*@{*/

/** @brief Digital channel enumeration */
#endif
#ifdef French_dox
/**
 * @name Fonctions d'Entrées/Sorties
 *
 * @brief Gérer les broches d'entrées/sorties.
 */
/*@{*/

/** @brief Enumeration des broches */
#endif
typedef enum DIGITAL_CHANNEL_
{
    DIG0=0x00080000,    /**< Digital Channel 0 */
    DIG1=0x00100000,    /**< Digital Channel 1 */
    DIG2=0x00200000,    /**< Digital Channel 2 */
    DIG3=0x08000000,    /**< Digital Channel 3 */
    DIG4=0x10000000,    /**< Digital Channel 4 */
    DIG5=0x20000000,    /**< Digital Channel 5 */
    DIG6=0x40000000,    /**< Digital Channel 6 */
    DIG7=0x80000000,    /**< Digital Channel 7 */
    BUTTON=0x4000,      /**< Digital Input Button */
    LED=0x10000         /**< Digital Output Led */
} DIGITAL_CHANNEL ;

#ifdef English_dox
/** @brief Digital channel way enumeration */
#endif
#ifdef French_dox
/** @brief Enumeration du sens des entrées/sorties */
#endif
typedef enum DIGITAL_WAY_
{
    DIG_IN  = 0,        /**< Digital channel is an Input */
    DIG_OUT = 1         /**< Digital channel is an Output */
} DIGITAL_WAY ;

#ifdef English_dox
/**
 * @brief Init Digital pin as Input or Output channel.
 *
 * @param channel       Digital Channel to configure.
 * @param way           Way of digital channel (DIG_IN or DIG_OUT).
 */
#endif
#ifdef French_dox
/**
 * @brief Initialiser une broche numérique en entrée ou en sortie.
 *
 * @param channel       Broche à configurer.
 * @param way           Sens de la broche (DIG_IN ou DIG_OUT).
 */
#endif
extern void InitMcuDigitalIO(DIGITAL_CHANNEL channel, DIGITAL_WAY way);

#ifdef English_dox
/**
 * @brief Set a digital output to 1.
 *
 * @param	channel		Digital channel between DIG0 and DIG7.
 */
#endif
#ifdef French_dox
/**
 * @brief Met à 1 une broche de sortie.
 *
 * @param	channel		La broche numérique : une valeur de DIG0 à DIG7.
 */
#endif
extern void SetMcuDigitalIO(DIGITAL_CHANNEL channel);

#ifdef English_dox
/**
 * @brief Clear a digital channel (Set 0 to an output).
 *
 * @param	channel		Digital channel between DIG0 and DIG7.
 */
#endif
#ifdef French_dox
/**
 * @brief Met à 0 une broche de sortie.
 *
 * @param	channel		La broche numérique : une valeur de DIG0 à DIG7.
 */
#endif
extern void ClearMcuDigitalIO(DIGITAL_CHANNEL channel);

#ifdef English_dox
/**
 * @brief Get the state of a digital channel.
 *
 * @param	channel		Digital channel between DIG0 and DIG7.
 * @return  state of the channel ( 0 or 1 ).
 */
#endif
#ifdef French_dox
/**
 * @brief Donne l'état d'une broche d'entrée.
 *
 * @param	channel		La broche d'entrée : une valeur de DIG0 à DIG7.
 * @return  Etat de la broche ( 0 ou 1 ).
 */
#endif
extern UInt32 GetMcuDigitalIO(DIGITAL_CHANNEL channel);

#ifdef English_dox
/** @brief Get a Digital Channel from a channel number.
 *
 * This functions is useful if you want manage the Digital pins from a number instead of a DIGITAL_CHANNEL enumeration.
 *
 * @param channel       Channel number between 0 and 7.
 * @return A correct DIGITAL_CHANNEL.
 */
#endif
#ifdef French_dox
/** @brief Converti un numéro de broche vers la valeur correcte de broche.
 *
 * Cette fonction est utile si vous souhaitez gérer les broches à partir d'un numéro entre 0 et 7 au lieu d'utiliser l'énumération DIGITAL_CHANNEL.
 *
 * @param channel       Un numéro de broche entre 0 et 7.
 * @return La valeur correcte de broche de type DIGITAL_CHANNEL.
 */
#endif
extern DIGITAL_CHANNEL GetDigitalChannel(UInt8 channel);

#ifdef English_dox
/*@}*/

/**
 * @name Analog functions
 *
 * @brief Manage the analog channel of UC1.
 */
/*@{*/

/** @brief Analog channel enumeration */
#endif
#ifdef French_dox
/*@}*/

/**
 * @name Fonctions analogique
 *
 * @brief Gérer les broches analogiques du microcontrôleur UC1.
 */
/*@{*/

/** @brief Enumeration des entrées analogiques */
#endif
typedef enum ANALOG_CHANNEL_
{
	ANA0=0x01,      /**< Channel 0 */
	ANA1=0x02,      /**< Channel 1 */
	ANA2=0x04,      /**< Channel 2 */
	ANA3=0x08,      /**< Channel 3 */
	ANA4=0x10,      /**< Channel 4 */
	ANA5=0x20,      /**< Channel 5 */
	ANA6=0x40,      /**< Channel 6 */
	ANA7=0x80,      /**< Channel 7 */
} ANALOG_CHANNEL ;

#ifdef English_dox
/**
 * @brief Init analog hardware.
 */
#endif
#ifdef French_dox
/**
 * @brief Initialiser la partie analogique du robot.
 */
#endif
extern void InitMcuAnalog(void);

#ifdef English_dox
/**
 * @brief Get a analog value from a channel.
 *
 * @param	channel		Analog channel between ANA0 and ANA7.
 * @return	Analog value between 0 and 1024.
 */
#endif
#ifdef French_dox
/**
 * @brief Donne la valeur analogique d'une broche.
 *
 * @param	channel		Une broche analogique entre ANA0 et ANA7.
 * @return	Valeur analogique de la broche sélectionnée entre 0 et 1024.
 */
#endif
extern UInt16 GetMcuAnalog(ANALOG_CHANNEL channel);

#ifdef English_dox
/** @brief Get ANALOG_CHANNEL from a channel number.
 *
 * This functions helps you to convert a number to a correct ANALOG_CHANNEL enumeration.
 *
 * @param channel       0 to 7.
 * @return return the ANALOG_CHANNEL value.
 */
#endif
#ifdef English_dox
/** @brief Converti un numéro de broche vers une valeur ANALOG_CHANNEL.
 *
 * Cette fonction vous permet de convertir un numéro entre 0 et 7 vers la valeur correspondante de l'énumération ANALOG_CHANNEL.
 *
 * @param channel       Un nombre comprit entre 0 et 7.
 * @return Donne la valeur ANALOG_CHANNEL.
 */
#endif
extern ANALOG_CHANNEL GetAnalogChannel(UInt8 channel);

/*@}*/

#ifdef __cplusplus
 }
#endif


#endif
