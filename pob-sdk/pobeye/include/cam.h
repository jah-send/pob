
/** 
 * @brief Function to get frame from POBEYE.
 *
 * @file
 * 
 *  
 *  - To get a frame from the camera, call one of these functions : 
 *    -# GrabRGBFrame(), 
 *    -# GrabRedFrame(), 
 *    -# GrabGreenFrame() or 
 *    -# GrabBlueFrame().
 *  - Next, get the frame with the function :
 *   -# GetPointerOnRGBFrame(), 
 *   -# GetPointerOnRedBuffer(), 
 *   -# GetPointerOnGreenBuffer() or 
 *   -# GetPointerOnBlueBuffer().
 *
 *  - To get Hue-Saturation-Light Frame, call the functions :
 *   -# GetPointerOnHSLFrame(),
 *   -# GrabRGBFrame(),
 *   -# GetHslFrame()
 *
 *
 * \note  The frame is in POB-EYE memory. The memory contains the 3 components red,green and blue.
 * This memory has a size of ~ 32 Kbytes ( 120 pixels per 88 per component ).
 * 
 * \note The HSL Frame share the same memory array that the RGB frame.
 *
 * \warning The POB-EYE module have 64 Kbytes of RAM and uses 32 Kbytes for own usage. 
 * <b><i>You have for your program only 32 Kbytes </i></b>.
 *
 * @see visio.h
 *
 * @author Pierre SEGUIN. POB-Technology
 *
 */

#ifndef CAM_H
#define CAM_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name Size of frame
 *
 * Define for the frame camera size
 */
 /*@{*/
#define WIDTH_FRAME 88    /**< Width of the pob-eye camera frame */
#define HEIGHT_FRAME 120  /**< Height of the pob-eye camera frame */
/*@}*/


/** 
 * @brief RGB Frame structure.
 */
typedef struct _RGBFrame
{
	UInt8 *red ;   /**< red component of the frame */
	UInt8 *green ; /**< green component of the frame */
	UInt8 *blue ;  /**< blue component of the frame */
} RGBFrame ;


/**
 * @brief HSL Frame structure
 */
typedef struct _HSLFrame
{
	UInt8 *hue ;        /**< hue component */
	UInt8 *saturation ; /**< saturation component */
	UInt8 *light ;      /**< light component */
} HSLFrame ;


/** 
 * @brief Initialize the camera.
 */
extern void InitCam(UInt8 version);


/**
 * @brief Send parameter to camera module
 *
 * @param Addr : adress register.
 * @param Data : Data to set.
 */
extern void SendToCam(UInt8 Addr, UInt8 Data);


/** 
 * @brief Grab a RGB frame from the camera.
 */
extern void GrabRGBFrame(void);

extern void GrabRGBFrameXY(UInt32 X, UInt32 Y);

/**
 * @brief Grab only the red component.
 */
extern void GrabRedFrame(void);


/**
 * @brief Grab only the green component.
 */
extern void GrabGreenFrame(void);


/**
 * @brief Grab only the blue component.
 */
extern void GrabBlueFrame(void);


/** 
 * @brief Get pointer on the RGB frame of the camera.
 *
 * @param[out] Frame : pointer on the RGB component.
 * @return Frame contains the pointer to the RGB component of the current frame.
 */
extern void GetPointerOnRGBFrame(RGBFrame *Frame);

/**
 * @brief Get pointer on the HSL frame of the camera.
 *
 * @param[out] Frame : pointer on the HSL component.
 * @return Frame contains the pointer to the HSL component of the current frame.
 */
extern void GetPointerOnHSLFrame(HSLFrame *Frame);

/**
 * @brief Get the array's pointer of red component.
 * 
 * @return a pointer on the red component. The array at this pointer has a size of 120*88 bytes.
 */
extern UInt8* GetPointerOnRedBuffer(void);


/**
 * @brief Get the array's pointer of green component.
 * 
 * @return a pointer on the green component. The array at this pointer has a size of 120*88 bytes.
 */
extern UInt8* GetPointerOnGreenBuffer(void);

/**
 * @brief Get the array's pointer of blue component.
 * 
 * @return a pointer on the blue component. The array at this pointer has a size of 120*88 bytes.
 */
extern UInt8* GetPointerOnBlueBuffer(void);

/**
 * @brief Get pointer on Hue buffer, return a UInt8* pointer. <i> You must declare a HSL frame to work with this pointer</i>
 */
#define GetPointerOnHueBuffer()  GetPointerOnRedBuffer()

/**
 * @brief Get pointer on Saturation buffer, return a UInt8* pointer. <i> You must declare a HSL frame to work with this pointer</i>
 */
#define GetPointerOnSaturationBuffer()  GetPointerOnGreenBuffer()

/**
 * @brief Get pointer on Light buffer, return a UInt8* pointer. <i> You must declare a HSL frame to work with this pointer</i>
 */
#define GetPointerOnLightBuffer()  GetPointerOnBlueBuffer()


#ifdef __cplusplus
 }
#endif

#endif

