/** \anchor camera
 *
 * @brief Grab frame from camera. 
 *
 * @file

An example to grab a frame from the pobeye camera and draw this frame on the LCD screen.

 * @author Foucault Alisson
 */
																		
//POB-Eye include
#include <pob-eye.h> 


int main (void)
{
	// Value declaration and initialization
	Int16 i=0,j=0,k=0,i_Cam=0,i_LCD=0;

	//LCD buffer, 128*64 pixels, 1 byte per pixel
	UInt8 LCD_Buffer [LCD_WIDTH*LCD_HEIGHT*BYTES];
	
	// Graphic buffer
	GraphicBuffer LCD_Screen; 
	
	// Frame of camera
	RGBFrame FrameFromCam;

	//Initialize POB-Eye and LCD screen
	InitPOBEYE();
	InitLCD();


	// Init the graphic buffer : 128 per 64, 1 bytes per pixel and LCD_Buffer
	InitGraphicBuffer(&LCD_Screen,LCD_WIDTH,LCD_HEIGHT,EIGHT_BITS,LCD_Buffer);

	// Clear the graphic buffer
	ClearGraphicBuffer(&LCD_Screen);
	
	// Get the pointer of the red,green and blue video buffer
	GetPointerOnRGBFrame(&FrameFromCam);

	while (1)
	{
		// Grab the RGB components
		GrabRGBFrame();
		
		// Binary the RGB buffer
		BinaryRGBFrame(&FrameFromCam);

		// Put the pixel from the red component witch is binary, to the lcd buffer
		for (k=0,i=63 ; i ; i--)
		{
			for (j=0;j<120;j++,k++)
					LCD_Screen.buffer[k] = FrameFromCam.red[i+(j*88)];
			k+=8;
		}

		// draw the buffer on the screen
		DrawLCD(&LCD_Screen);
	}
	return 0;
}
