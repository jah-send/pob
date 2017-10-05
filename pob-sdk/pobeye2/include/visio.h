//
// Copyright 2009 POB-Technology. All rights reserved.
// POB-Technology PROPRIETARY/CONFIDENTIAL.
//

/** \anchor visio
 *
 * @brief Recognition functions.
 *
 * @file
 *
 * Identify patterns, transform rgb frame to various format (Hue/Saturation/Light, Gray level, Binary level...)
 *
 * Identify function works with a dictionnary of forms. This dictionnary of forms is build by the PobTools software.
 * After getting frame from the \ref camera.h "camera", you can recognize forms in this frame.
 *  - convert the frame to binary format ( BinaryRGBFrame() )
 *  - next, you identify the form with IdentifyForm()
 *
 * @par Transform RGB pixels to HSL pixels example
 *
 * @code

 #include <pob-eye.h>

 int main(void)
 {
	UInt32 i;
	UInt8 *rgbFrame;
	UInt8 hue, saturation, light;

	// Init pobeye2 hardware: i2c and camera.
	InitPobeye2();
	InitI2C();
	InitCameraPobeye2();

	// Get a pointer on the pobeye2 RGB memory (currently this memory is empty).
	rgbFrame = GetRGBFrame();

	// Main loop:
	while(1)
	{
		// Store the RGB camera frame into the pobeye2 RGB memory:
		GrabRGBFrame();

		// Transform the RGB pixels to HSL pixels:
		GetHSLFrame(rgbFrame);

		// Get the HSL component:
		for(i = 0 ; i < WIDTH_FRAME * HEIGHT_FRAME ; i++)
		{
			// For each byte of rgbFrame, get the pixel:
			hue        = GetHue(rgbFrame[i]);
			saturation = GetSaturation(rgbFrame[i]);
			light      = GetLight(rgbFrame[i]);

		}
	}
 }

 * @endcode
 */
#ifndef VISIO_H
#define VISIO_H

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @brief Rectangular structure
 */
typedef struct _Rect
{
	UInt8 x;
	UInt8 y;
	UInt8 width;
	UInt8 height;
} Rect;


/**
 * @brief Point structure
 */
typedef struct _Point
{
	UInt8 x; 
	UInt8 y;	
} Point;


/** 
 * @brief Form on a picture 
 */
typedef struct _Form
{
	UInt8 id ;	    /**< ID in the list of form */
	UInt8 x ;		/**< Center X of the form */
	UInt8 y ;		/**< Center Y of the form */
	UInt8 width ;	/**< Form's width */
	UInt8 height ;	/**< Form's height */
} Form;


/**
 * Form max
 */
#define MAX_OF_FORM 10

/**
 * @name Macro to get hue/saturation/light from a pixel byte. Use this macro with HSL frame!
 *
 */
 /*@{*/
#define GetHue(byte)		GetRed(byte)	/**< Get hue pixel from a byte. */
#define GetSaturation(byte)	GetGreen(byte)	/**< Get saturation pixel from a byte. */
#define GetLight(byte)		GetBlue(byte)	/**< Get light pixel from a byte. */
/*@}*/

/** 
 * @brief Transform the current RGB frame to a HSL Frame. 
 * 
 * @warning this function works only with compressed rgb frame!
 *
 * @param Frame			Pointer to the pobeye2 rgb memory.
 */
extern void GetHSLFrame(UInt8 *Frame );

/** @brief Transform the current RGB Frame to a HSV Frame.
 *
 * @param Frame			Pointer to the pobeye2 rgb memory.
 */
extern void GetHSVFrame(UInt8 *Frame );

/** 
 * @brief Binary the RGB Frame. 
 * 
 * @warning this function works only with compressed rgb frame!
 *
 * @param Frame			Pointer to the pobeye2 rgb memory.
 */
extern void BinaryRGBFrame(UInt8 *Frame);


/** 
 * @brief Gray the RGB Frame.
 * 
 * @warning this function works only with compressed rgb frame!
 *
 * @param Frame			Pointer to the pobeye2 rgb memory. 
 */
extern void GrayRGBFrame(UInt8 *Frame);


/* 
 * @brief Return a Gray pixel
 *
 * @param Frame			Pointer to the current frame of the camera.
 * @param Id_Pixel		ID of the RGB pixel that return the gray value
 */
extern UInt8 GrayAPixel(const UInt8 *Frame,UInt32 Id_Pixel);

/** 
 * @brief Make a list of forms known in a binary picture.
 *
 * The last parameter of the function is build by POB-TOOLS, POB Pattern. 
 * This tools produce a '.h' that contains an array of pattern.
 *
 * @param[in] Frame			Pointer on a RGB Frame. This frame must be binary.
 * @param[out] ListOfForm	Pointer on an array of known forms.
 * @param[in] Pattern		Pointer on the pattern.
 * 
 * @return Number of known forms and ListOfForm containing the form.
 */
extern UInt8 IdentifyForm(UInt8 *Frame,Form *ListOfForm,const UInt8 *Pattern);

#ifdef __cplusplus
 }
#endif

#endif
