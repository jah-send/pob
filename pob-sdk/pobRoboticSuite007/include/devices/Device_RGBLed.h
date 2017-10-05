//
// Copyright 2010 POB-Technology. All rights reserved.
//
#ifdef English_dox
/** \anchor rgbled
 *
 * @brief RGB Led device
 *
 * @file
 *
 * The RGB Led device allows you to display various light with a red/green/blue code.
 *
 */
 #endif

#ifdef French_dox
/** \anchor rgbled
 *
 * @brief Piloter la carte Led RGB
 *
 * @file
 *
 * La led RGB vous permet d'allumer une led de différentes couleurs.
 */
 #endif

#ifndef RS007_DEVICE_RGBLED_H
#define RS007_DEVICE_RGBLED_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef English_dox
/** @brief Set red-green-blue color on the RGB Led actuator.
 *
 * @param port      Port where the RGB Led is connected (between 1 to 8).
 * @param r         Red value.
 * @param g         Green value.
 * @param b         Blue value.
 */
 #endif
 #ifdef French_dox
/** @brief Configurer la couleur à allumer sur la led RGB.
 *
 * @param port      Port sur lequel la led RGB est connectée (entre 1 à 8).
 * @param r         Valeur de rouge.
 * @param g         Valeur de vert.
 * @param b         Valeur de bleu.
 */
 #endif
extern void SetColorOnRGBLed(UInt8 port, UInt8 r, UInt8 g, UInt8 b);

#ifdef English_dox
/** @brief RGB Led color enumeration.
 */
#endif
#ifdef French_dox
 /** @brief Enumeration des couleurs de la led RGB.
  */
#endif
typedef enum _rgb_led_color_
{
    RGB_LED_BLACK       = 0,    /**< Black */
    RGB_LED_WHITE       = 1,    /**< White */
    RGB_LED_COLDWHITE   = 2,    /**< ColdWhite */
    RGB_LED_RED         = 3,    /**< Red */
    RGB_LED_GREEN       = 4,    /**< Green */
    RGB_LED_BLUE        = 5,    /**< Blue */
    RGB_LED_YELLOW      = 6,    /**< Yellow */
    RGB_LED_FUCHSIA     = 7,    /**< Fuchsia */
    RGB_LED_CYAN        = 8,    /**< Cyan */
    RGB_LED_ORANGE      = 9,    /**< Orange */
    RGB_LED_LIME        = 10,   /**< Lime */
    RGB_LED_PINK        = 11,   /**< Pink */
    RGB_LED_PURPLE      = 12,   /**< Purple */
    RGB_LED_TURQUOISE   = 13,   /**< Turquoise */
    RGB_LED_AQUA        = 14,   /**< Aqua */
    RGB_LED_GOLD        = 15    /**< Gold */
} RgbLedColor ;

#ifdef English_dox
/** @brief Set a predefined color on the RGB Led device.
 *
 * @param port          Port where the RGB Led is connected (between 1 to 8).
 * @param predefcolor   Predefined value of a color.
 */
 #endif
 #ifdef French_dox
/** @brief Allumer la led RGB suivant une couleur prédéfinie.
 *
 * @param port          Port sur lequel la led RGB est connectée (entre 1 à 8).
 * @param predefcolor   Valeur prédéfinie d'une couleur.
 */
 #endif
extern void SetPredefinedColorOnRGBLed(UInt8 port, RgbLedColor predefcolor);

#ifdef English_dox
/** @brief Blink color.
 *
 * @param port      Port where the RGB Led is connected (between 1 to 8).
 * @param color1    Color 1 value.
 * @param time1     Time's value for displayed the color 1.
 * @param color2    Color 2 value.
 * @param time2     Time's value for displayed the color 2.
 */
 #endif
 #ifdef French_dox
/** @brief Faire clignoter la led RGB.
 *
 * @param port      Port sur lequel la led RGB est connectée (entre 1 à 8).
 * @param color1    Première couleur.
 * @param time1     Temps durant laquel on affiche la couleur 1.
 * @param color2    Seconde couleur.
 * @param time2     Temps durant laquel on affiche la couleur 2.
 */
 #endif
extern void SetBlinkOnRGBLed(UInt8 port, RgbLedColor color1, UInt8 time1, RgbLedColor color2, UInt8 time2);

#ifdef English_dox
/** @brief Set a colored sequence in the RGB Led memory.
 *
 * @param port      Port where the RGB Led is connected (between 1 to 8).
 * @param seq       Sequence identifier.
 * @param buffer    Pointer to a color buffer.
 * @param size      Color's number.
 */
 #endif
 #ifdef French_dox
/** @brief Configurer une séquence de couleur dans la mémoire de la led RGB.
 *
 * @param port      Port sur lequel la led RGB est connectée (entre 1 à 8).
 * @param seq       Numéro de la séquence.
 * @param buffer    Pointeur sur un tableau de couleur à envoyer dans la led RGB.
 * @param size      Nombre de couleur dans le tableau.
 */
 #endif
extern void SetSequenceOnRGBLed(UInt8 port, UInt8 seq, UInt8 * buffer, UInt8 size);

#ifdef English_dox
/** @brief Start a color sequence on the RGB Led.
 *
 * @param port      Port where the RGB Led is connected (between 1 to 8).
 * @param seq       Sequence idenfifier to be played.
 * @param repeat    0 no repeat, 1 repeat.
 */
 #endif
 #ifdef French_dox
/** @brief Jouer une séquence de couleur sur la led RGB.
 *
 * @param port      Port sur lequel la led RGB est connectée (entre 1 à 8).
 * @param seq       Numéro de la séquence à jouer.
 * @param repeat    0 pas de répetition, 1 pour jouer en boucle la séquence.
 */
 #endif
extern void StartSequenceOnRGBLed(UInt8 port, UInt8 seq, UInt8 repeat);



#ifdef __cplusplus
 }
#endif

#endif
