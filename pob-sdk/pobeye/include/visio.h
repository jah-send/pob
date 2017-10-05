/** 
 * @brief Video recognition
 *
 * @file
 *
 * After getting frame from the \ref cam.h "camera", you can recognize forms in this frame.
 *  - convert the frame to binary format ( BinaryRGBFrame() )
 *  - next, you identify the form with IdentifyForm()
 *
 * @see cam.h
 *
 * @author Pierre SEGUIN. POB-Technology 
 *
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
 * @brief Transform the current frame to a HSL Frame. 
 * 
 * All components RGB are HSL.
 *
 * @param Frame : Pointer to the current frame of the camera.
 */
void GetHSLFrame(const HSLFrame *Frame );

#define GetHslFrame(ptr) GetHSLFrame(ptr)


/** 
 * @brief Binary the RGB Frame. 
 * 
 * All components are binary.
 *
 * @param Frame : Pointer to the current frame of the camera.
 */
void BinaryRGBFrame(const RGBFrame *Frame);


/** 
 * @brief Gray the RGB Frame. 
 * 
 * All components are Gray.
 *
 * @param Frame : Pointer to the current frame of the camera. 
 */
void GrayRGBFrame(const RGBFrame *Frame);


/** 
 * @brief Return a Gray pixel
 *
 * @param Frame : Pointer to the current frame of the camera.
 * @param Id_Pixel : ID of the RGB pixel that return the gray value
 */
UInt16 GrayAPixel(const RGBFrame *Frame,UInt16 Id_Pixel);


/** 
 * @brief Make a list of forms known in a binary picture.
 *
 * The last parameter of the function is build by POB-TOOLS, POB Pattern. 
 * This tools produce a '.h' that contains an array of pattern.
 *
 * @param[in] Frame       : Pointer on a RGB Frame. This frame must be binary.
 * @param[out] ListOfForm : Pointer on an array of known forms.
 * @param[in] Pattern     : Pointer on the pattern.
 * 
 * @return Number of known forms and ListOfForm containing the form.
 */
UInt8 IdentifyForm(const RGBFrame *Frame,Form *ListOfForm,const UInt8 *Pattern);

#ifdef __cplusplus
 }
#endif

#endif
