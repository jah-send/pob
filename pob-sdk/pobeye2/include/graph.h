/** 
 * @brief Manipulate the graphic buffer
 *
 * @file
 *
 * You can draw line,point, or bitmap with the graphic buffer functions.
 * After drawing in the graphic buffer, you can draw it in \ref lcd_screen "LCD Screen"
 *
 * \note For bitmap function, parameters are built by POB-TOOLS : POB Bitmap. 
 *  this tools produce a '.h' that contains bitmap array and bitmap ID.
 *
 * @see lcd.h
 * 
 * @author Pierre SEGUIN. POB-Technology
 *
 */
#ifndef GRAPH_H
#define GRAPH_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name  Bits per pixel
 * 
 * Define the number of bits per pixel used in your graphics buffer.
 *
 */
/*@{*/
#define ONE_BIT 0     /**< The graphic buffer use 1 bit per pixel */
#define EIGHT_BITS 8 /**< The graphic buffer use 8 bits per pixel */
/*@}*/


/** 
 * @name Size of pixel
 *
 * define the size of the video buffer used in your graphics buffer.
 *
 */
/*@{*/
#define BYTES  1
#define BITS   1/8 	
/*@}*/


/**
 * \anchor graphic_buffer
 *
 * @brief Graphic buffer structure.
 *
 */
typedef struct _GraphicBuffer
{
	UInt8 bitsPerPixel; /**< bits per pixel */
	UInt8 height;       /**< height of the buffer */
	UInt8 width;        /**< width of the buffer */
	UInt8 *buffer;      /**< video buffer */
}GraphicBuffer;


/**
 * @brief Init a graphic buffer.
 *
 * @param Target : graphic buffer to init
 * @param w      : Width of buffer.
 * @param h      : Heigth of buffer.
 * @param bits   : Number of bits per pixel : ::ONE_BIT or ::EIGHT_BITS
 * @param Buffer : Video buffer (used for display). You must create an array of a size : width * heigth * size of pixel (::BYTES or ::BITS)
 */
extern void InitGraphicBuffer( GraphicBuffer *Target, UInt8 w, UInt8 h,UInt8 bits, UInt8 *Buffer);

/** 
 * @brief Clear a graphic buffer.
 *
 * @param Target : pointer on the buffer to be cleared.
 */
extern void ClearGraphicBuffer (const GraphicBuffer *Target);


/** 
 * @brief Draw a Bitmap in a graphic buffer.
 *
 * @param x,y    : Where the bitmap will be drawn in the graphic buffer.
 * @param id	 : Id of the Bitmap in the Bitmap list.
 * @param bitmap : the bitmap list. (this bitmap list is build by POB Bitmap)
 * @param target : Pointer on a GraphicBuffer, on which the bitmap will be drawn. 
 */
extern void DrawBitmap(UInt8 x,UInt8 y,UInt8 id ,const UInt8* bitmap,const GraphicBuffer *target);



/** 
 * @brief Get the width of a bitmap.
 *
 * Parameter's are set by POB Tools : POB Bitmap.
 *
 * @param id     : ID of the Bitmap in the bitmap list.
 * @param Bitmap : the bitmap list. (this bitmap list is build by POB Bitmap)
 * @return The width of bitmap.
 */
extern UInt8 GetBitmapWidth(UInt8 id,const UInt8* Bitmap);



/** 
 * @brief Get the height of a Bitmap.
 *
 * Parameter's are set by POB Tools : POB Bitmap.
 *
 * @param id     : Id of the Bitmap in the bitmap list.
 * @param Bitmap : the bitmap list. (this bitmap list is build by POB Bitmap)
 * @return the height of bitmap.
 */
extern UInt8 GetBitmapHeight(UInt8 id,const UInt8* Bitmap);


/**
 * @brief Plot a point on a graphic Buffer.
 *
 * @param X,Y    : Where the point will be drawn
 * @param Target : Pointer on a GraphicBuffer where the point will be drawn
 */
extern void PlotAPoint(UInt16 X,UInt16 Y,const GraphicBuffer *Target);

/**
 * @brief Draw component in a buffer video
 *
 * @param Componant : pointer on a component.
 * @param LCD_Buff  : Pointer on a graphic buffer, has to 64*64 pixels and each pixel has EIGHT_BITS per pixel
 */
extern UInt8 DrawComponentInABufferVideo(UInt8 *Componant,const GraphicBuffer *LCD_Buff );


/**
 * @brief Draw a line on a graphic Buffer.
 *
 * @param X1,Y1  : Where the first point is.
 * @param X2,Y2  : Where the second point is.
 * @param Target : Pointer on a GraphicBuffer where the line wil be drawn.
 */
extern void DrawLine(UInt16 X1, UInt16 Y1, UInt16 X2, UInt16 Y2,const GraphicBuffer *Target);

#ifdef __cplusplus
 }
#endif

#endif
