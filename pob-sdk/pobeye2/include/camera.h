//
// Copyright 2009 POB-Technology. All rights reserved.
// POB-Technology PROPRIETARY/CONFIDENTIAL.
//

/** \anchor camera
 *
 * @brief Camera sensor.
 *
 * @file
 *
 * Use the pobeye2 cmos sensor:
 * - The camera sensor is configured by i2c bus and use the i2c address 0x42 at a speed of 100 KHz.
 * - The camera frame is copied in pobey2 memory after a call to grab frame function.
 * - The camera frame has a size of 160 pixels width by 120 pixels height.
 *
 * The RGB frame from camera is compressed and 1 color pixel takes 1 byte:
 * - bit0 and 1   : blue color.
 * - bit2, 3 and 4: green color.
 * - bit5, 6 and 7: red color.
 *
 *
 * @par Get a rgb frame from camera
 *
 * @code

 #include <pob-eye.h>

 int main(void)
 {
	UInt32 i;
	UInt8 *rgbFrame;
	UInt8 red, green, blue;

	// Init pobeye2 cpu, i2c bus and camera sensor:
	InitPobeye2();
	InitI2C(I2C_100_KHZ);
	// the pobeye2 camera use the i2c bus for setting, you have to configure i2c bus before!
	InitCameraPobeye2();

	// Get pointer to the pobeye2 RGB memory:
	rgbFrame = GetRGBFrame();

	// Main loop:
	while(1)
	{
		// Capture a camera frame and copy it to the pobeye2 memory:
		GrabRGBFrame();

		// Get pixel color:
		for(i = 0 ; i < WIDTH_FRAME * HEIGHT_FRAME ; i++)
		{
			// For each byte of rgbFrame, get the color:
			red   = GetRed(rgbFrame[i]);
			green = GetGreen(rgbFrame[i]);
			blue  = GetBlue(rgbFrame[i]);

			// ... then play with the pixel!

		}

	}

	return 0;
 }

 * @endcode
 *
 */
#ifndef POB_CAMERA_H
#define POB_CAMERA_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name Size of frame
 *
 */
 /*@{*/
#define WIDTH_FRAME		160		/**< Width of the pob-eye camera frame */
#define HEIGHT_FRAME	120		/**< Height of the pob-eye camera frame */
/*@}*/

//#define RGBFrame UInt8

/** @brief Init the pobeye2 camera sensor.
 */
extern void InitCameraPobeye2(void);

/** @brief Set camera parameters.
 *
 * @warning this is low level function.
 *
 * @param Addr		Parameter's address in camera's memory.
 * @param Data		Parameter's data.
 */
extern void SetCameraParameter(UInt8 Addr, UInt8 Data);

/** @brief Grab a RGB frame from camera (Pixel are compressed).
 *
 * This function capture a frame and copy it to the pobeye2 memory.
 * The frame is compressed.
 */
extern void GrabRGBFrame(void);

/** @brief Grab a RGB frame from camera (Pixel are not compressed).
 *
 * Warning, this function uses 57600 bytes of pobeye2 memory! You have to provide 2 buffers of a size 19200.
 * The red buffer is provided by pobeye2 firmware.
 *
 * @param greenBuffer		Green's buffer where store the green pixel.
 * @param blueBuffer		Blue's buffer where store the blue pixel.
 *
 * @par Grab a rgb frame not compressed example
 *
 * @code

 #include <pob-eye.h>

 int main(void)
 {
	UInt32 i;

	// Declare a pointer:
	UInt8 *redFrame;

	// Create 2 buffers to store green and blue pixels:
	UInt8 greenFrame[WIDTH_FRAME*HEIGHT_FRAME];
	UInt8 blueFrame[WIDTH_FRAME*HEIGHT_FRAME];

	UInt8 red, green, blue;

	// Init pobeye2 cpu, i2c bus and camera:
	InitPobeye2();
	InitI2C(I2C_100_KHZ);
	InitCameraPobeye2();

	// Get pointer to the red memory:
	redFrame = GetRGBFrame();

	// Main loop:
	while(1)
	{
		// Capture a frame: red pixels are copied to redFrame, green pixels to greenFrame and blue pixels to blueFrame.
		GrabFullRGBFrame(greenFrame,blueFrame);

		for(i=0; i < WIDTH_FRAME*HEIGHT_FRAME ; i++ )
		{
			// Get red, green and blue pixels:
			red		= redFrame[i];
			green	= greenFrame[i];
			blue	= blueFrame[i];
		}

	}
 }

 * @endcode
 */
extern void GrabFullRGBFrame(UInt8 * greenBuffer, UInt8 * blueBuffer );

/** @brief Get RGB frame pointer.
 *
 * The pobeye2 firmware store the RGB frame in a buffer: This function provide a pointer to this buffer.
 *
 * @return Pointer to the RGB frame.
 */
extern UInt8 *GetRGBFrame(void);

/**
 * @name Macro to get color from a pixel byte. Use this macro only with RGB compressed frame!
 *
 */
 /*@{*/

/**
 * @brief Get red pixel from a byte
 */
#define GetRed(byte)	(byte & 0xE0)	/**< Get red pixel from a byte. */

/**
 * @brief Get green pixel from a byte
 */
#define GetGreen(byte)  ((byte << 3) & 0xE0) /**< Get green pixel from a byte. */

/**
 * @brief Get blue pixel from a byte
 */
#define GetBlue(byte)	((byte << 6) & 0xC0) /**< Get blue pixel from a byte. */
/*@}*/

extern void InitCameraPobeye2ForCubot(void);

#ifdef __cplusplus
 }
#endif


#endif
