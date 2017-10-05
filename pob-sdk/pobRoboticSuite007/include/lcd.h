//
// Copyright 2010 POB-Technology. All rights reserved.
//
#ifdef English_dox
/** \anchor lcd
 *
 * @brief LCD Screen functions
 *
 * @file
 *
 * The POB-Robotics-Suite comes with a lcd screen with a size of 60 pixels by 8 pixels (width / height).
 *
 * You can print text to the lcd screen or send directly the pixel values to draw a picture.
 *
 * @par Print Text to the LCD.
 *
 * @code

 #include <pobRoboticSuite.h>

 int main(void)
 {

		// Init the Pob-Robotics-Suite hardware:
		InitCpu();
		InitRobot();

		// Print the text to the LCD Screen:
		SetLCDText("Hello !",7);

		while(1)
		{
		}

		return 0;
 }

 * @endcode
 */
#endif
#ifdef French_dox
/** \anchor lcd
 *
 * @brief Fonctions de l'écran LCD
 *
 * @file
 *
 * Le POB-Robotics-Suite a un écran lcd avec une taille de 60 pixels par 8 pixels (largeur / hauteur).
 *
 * Vous pouvez afficher du texte ou envoyer directement les pixels à l'écran pour afficher une petite image.
 *
 * @par Afficher du texte sur l'écran LCD.
 *
 * @code

 #include <pobRoboticSuite.h>

 int main(void)
 {

	  // Initialisation du matériel Pob-Robotics-Suite :
	  InitCpu();
	  InitRobot();

	  // Afficher le texte à l'écran :
	  SetLCDText("Hello !",7);

	  while(1)
	  {
	  }

	  return 0;
 }

 * @endcode
 */
#endif

#ifndef RS007_LCD_H
#define RS007_LCD_H


#ifdef __cplusplus
extern "C" {
#endif

#ifdef English_dox
/** @brief Video mode. */
#endif
#ifdef French_dox
/** @brief Type de vidéo. */
#endif
typedef enum _videomode_
{
    VIDEOMODE_NORMAL    = 0,    /**< Normal mode (Black on white) */
    VIDEOMODE_REVERSE   = 1,    /**< Reverse mode (White on black) */
} VIDEOMODE;

#ifdef English_dox
/** @brief Scroll's mode. */
#endif
#ifdef French_dox
/** @brief Type de défilement. */
#endif
typedef enum _scroll_mode_
{
    SCROLL_MODE_STOP    = 0,    /**< Stop after scrolling */
    SCROLL_MODE_LOOP    = 1,    /**< Play in loop the text */
    SCROLL_MODE_REBOUND = 2     /**< Rebound the text when reach end of text. */
} SCROLL_MODE;

#ifdef English_dox
/** @brief Scroll's sens. */
#endif
#ifdef French_dox
/** @brief Sens du défilement. */
#endif
typedef enum _scroll_sens_
{
    SCROLL_LEFT_RIGHT   = 1,    /**< Text go left to right */
    SCROLL_RIGHT_LEFT   = 2     /**< Text go to right to left */
} SCROLL_SENS;

#ifdef English_dox
/** @brief Scroll option structure */
#endif
#ifdef French_dox
/** @brief Structure de défilement */
#endif
typedef struct _scroll_option_
{
    SCROLL_MODE     mode;       /**< Scroll's mode: No scroll, Loop, Rebound */
    SCROLL_SENS     sens;       /**< Scroll's sens. */
    UInt8           speed;      /**< Speed of the text. */
} ScrollOption;

#ifdef English_dox
/** @brief Set video mode of the LCD Screen.
 *
 * @param  videomode    VIDEOMODE_NORMAL or VIDEOMODE_REVERSE.
 */
#endif
#ifdef French_dox
/** @brief Configure le type de vidéo pour l'écran LCD.
 *
 * @param  videomode    VIDEOMODE_NORMAL ou VIDEOMODE_REVERSE.
 */
#endif
extern void SetLCDVideoMode(VIDEOMODE videomode);

#ifdef English_dox
/** @brief Clear the LCD Screen.
 */
#endif
#ifdef French_dox
/** @brief Effacer l'écran LCD.
 */
#endif
extern void ClearLCDScreen(void);

#ifdef English_dox
/** @brief Print a text on LCD Screen.
 *
 * @param text      Text to print.
 * @param textLen   Lenght of text.
 */
#endif
#ifdef French_dox
/** @brief Afficher un texte sur l'écran LCD.
 *
 * @param text      Texte à afficher.
 * @param textLen   Longueur du texte.
 */
#endif
extern void SetLCDText(UInt8* text, UInt8 textLen);

#ifdef English_dox
/** @brief Draw a pixel buffer to the LCD Screen.
 *
 * @param buffer        Pixel buffer.
 * @param len           Size of buffer.
 */
#endif
#ifdef French_dox
/** @brief Afficher un tableau de pixel à l'écran.
 *
 * @param buffer        Pointeur sur un tableau de pixel.
 * @param len           Taille du tableau.
 */
#endif
extern void SetLCDGraphic(UInt8* buffer, UInt8 len);

#ifdef English_dox
/** @brief Set the option of the LCD scroll.
 *
 * @param option        A pointer to a valid ScrollOption structure. You have to set parameters of this structure!
 *
 *
 * @par Scrolling option example.
 *
 * @code

 #include <pobRoboticSuite.h>

 int main(void)
 {
    // declare a ScrollOption structure:
    ScrollOption option;

    // init pob-robotics-suite:
    InitCpu();
    InitRobot();

    // set option in the scructure: loop, text go from left to right at speed 2:
    option.mode     = SCROLL_MODE_LOOP;
    option.sens     = SCROLL_LEFT_RIGHT;
    option.speed    = 2;

    // write parameters:
    SetLCDScrollParam(&option);

    // write text to the lcd:
    SetLCDScrollText("Hello from Pob-Robotics-Suite",29);

    // ... and start the scrolling!
    StartLCDScroll();

    while(1)
    {
    }

    return 0;
 }

 * @endcode
 */
#endif
#ifdef French_dox
/** @brief Configurer le défilement de l'écran LCD.
 *
 * @param option    Un pointeur sur une structure valide ScrollOption. Vous avez à remplir cette structure !
 *
 *
 * @par Exemple de configuration.
 *
 * @code

 #include <pobRoboticSuite.h>

 int main(void)
 {
	  // Création d'une structure ScrollOption :
	  ScrollOption option;

	  // Initialisation du pob-robotics-suite:
	  InitCpu();
	  InitRobot();

	  // Configuration des options de défilement : en boucle, texte de gauche à droite à une vitesse 2 :
	  option.mode     = SCROLL_MODE_LOOP;
	  option.sens     = SCROLL_LEFT_RIGHT;
	  option.speed    = 2;

	  // Ecriture des paramétres de défilement :
	  SetLCDScrollParam(&option);

	  // On écrit du texte à l'écran :
	  SetLCDScrollText("Hello from Pob-Robotics-Suite",29);

	  // ... et on lance le défilement !
	  StartLCDScroll();

	  while(1)
	  {
	  }

	  return 0;
 }

 * @endcode
 */
#endif
extern void SetLCDScrollParam(ScrollOption *option);

#ifdef English_dox
/** @brief Print a text on the LCD Screen and scroll the text.
 *
 * @param text      Text to print on the LCD.
 * @param textLen   Lenght of text.
 */
#endif
#ifdef French_dox
/** @brief Affiche du texte à l'écran et prépare le défilement de ce texte.
 *
 * @param text      Texte à afficher à l'écran.
 * @param textLen   Longueur du texte.
 */
#endif
extern void SetLCDScrollText(UInt8* text, UInt8 textLen);

#ifdef English_dox
/** @brief Start the scrolling mode.
 */
#endif
#ifdef French_dox
/** @brief Démarre le défilement.
 */
#endif
extern void StartLCDScroll(void);

#ifdef English_dox
/** @brief Stop the scrolling mode.
 */
#endif
#ifdef French_dox
/** @brief Arrête le défilement.
 */
#endif
extern void StopLCDScroll(void);


//extern void TestLCD(UInt8 test);
	
//* @brief Draw a pixel buffer to the LCD Screen and scroll the pixel.
// *
// * @param buffer    Pixel buffer.
// * @param size      Size of buffer.
// */
//extern void SetLCDScrollGraphic(UInt8* buffer, UInt8 size);


#ifdef __cplusplus
 }
#endif


#endif // RS007_LCD_H
