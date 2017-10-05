/**
 * \anchor lcd_screen
 *
 * @brief Draw on LCD.
 * 
 *
 * @file
 *
 * LCD drawing function. All of this function take a \ref graphic_buffer "GraphicBuffer" parameter.
 *
 * @author Pierre SEGUIN. POB-Technology
 *
 */
#ifndef LCD_H
#define LCD_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * Dimensions of the LCD screen.
 */
/*@{*/
#define LCD_WIDTH 128 /**< LCD screen width */
#define LCD_HEIGHT 64 /**< LCD screen height */
/*@}*/


/**
 * @brief Initialize the LCD screen.
 */
extern void InitLCD (void);


/** 
 * @brief Draw graphic buffer to the LCD screen (128 x 64 pixels)
 *
 * @param Buffer : Pointer on a GraphicBuffer.
 */
extern void DrawLCD(const GraphicBuffer *Buffer);


/** 
 * @brief Draw the left side of the LCD screen (64 x 64 pixels). 
 * 
 * The GraphicBuffer must have a 64 by 64 pixels video buffer size.
 *
 * @param Buffer : Pointer on a GraphicBuffer. 
 */
extern void DrawLeftLCD(const GraphicBuffer *Buffer);


/** 
 * @brief Draw the right side of the LCD screen (64 x 64 pixels). 
 * 
 * The GraphicBuffer must have a 64 by 64 pixels video buffer size .
 *
 * @param Buffer : Pointer on a GraphicBuffer.
 */
extern void DrawRightLCD(const GraphicBuffer *Buffer);

#ifdef __cplusplus
 }
#endif


#endif
