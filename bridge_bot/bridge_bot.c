/** \anchor form1
 *
 * @brief Form recognition. 
 *
 * @file

 Example of form recognition and print the result on UART and the LCD Screen.

 * @author Foucault Alisson
 */

#include <pob-eye.h>
#include <string.h>

// Include bitmap list and dictionnary of forms
#include "pattern.h"
#include "pad.h"

// external functions declarations (for PrintTextOnPobLCD)
extern void InitAsciiBuffer();
extern void PrintTextOnPobLCD(int row, int col, char *string, UInt8 *Screen_Buffer);
extern void HLightText(int row, int col, int size, UInt8 *Screen_Buffer);

int main (void)
{	
	UInt8 i=0,Nb_Identify=0;

	// List of form
	Form ListOfForm[MAX_OF_FORM];

	// Struct of three pointers on the RGB components
	UInt8 * FrameFromCam;

	//The pixels will be stocked in the LCD buffer
	UInt8 LCD_Buffer [LCD_WIDTH*LCD_HEIGHT*BITS] ;
	GraphicBuffer ScreenBuffer ;

	// System and LCD screen initialization
	InitPobeye2();
	InitI2C(I2C_100_KHZ);
	InitCameraPobeye2();
	InitLCD();	
	InitPobProto();
	SwitchOnAllServo();

	// Get the pointer of the red,green and blue video buffer
	FrameFromCam = GetRGBFrame();

	// Init the Graphic buffer with 128 per 64, one pixel per bit and LCD_Buffer
	InitGraphicBuffer( &ScreenBuffer, LCD_WIDTH,LCD_HEIGHT,ONE_BIT,LCD_Buffer);

	// clear the graphic buffer
	ClearGraphicBuffer(&ScreenBuffer);
	DrawLCD(&ScreenBuffer);

	// Init Ascii buffer, use to write in the LCD screen with PrintTextOnPobLCD function
	InitAsciiBuffer();

	// demo code for reference
	PrintTextOnPobLCD(1,2, "North", LCD_Buffer);
	DrawLCD(&ScreenBuffer);
	WaitMs(500);
	SetLed();
	WaitUs(500000);
	ClearLed();

	while(1)
	{		
		// grab the RGB components
		GrabRGBFrame();				

		// Binary the three RGB Buffer
		BinaryRGBFrame(FrameFromCam); 

		// Try to identify the forms and make a list of it
		Nb_Identify=IdentifyForm(FrameFromCam,ListOfForm,pattern);	

		// Parse the list of the form and print result on the Pob-Terminal and the LCD Screen
		for (i=0;i<Nb_Identify;i++)
		{
			switch (ListOfForm[i].id)
			{
				case IDP_0_CROSS:
					// Draw bitmap on the buffer and the LCD screen
					MoveBot(STOP);
					break;

				case IDP_1_BIGA:
					break;

				case IDP_2_KING:

					break;

				case IDP_3_TOWER:

					break;

				case IDP_4_TREFLE:

					break;

				case IDP_5_TRIANGLE:

					break;
				case IDP_6_CIRCLE:

					MoveBot(RUN);
					break;
				default:
					break;
			}				
		}		
		if (Nb_Identify == 0)
		{

		}
	}
	return 0;
}

char * get_new_direction(char * curr_direction, UInt8 turn)
{
	if (turn == LEFT)
	{
		if (strcmp(curr_direction, 'North')==0)
			return "West";
		else if (strcmp(curr_direction, 'East')==0)
			return "North";
		else if (strcmp(curr_direction, 'South')==0)
			return "East";
		else
			return "South";
	}
	else if (turn == RIGHT)
	{
		if (strcmp(curr_direction, 'North')==0)
			return "East";
		else if (strcmp(curr_direction, 'East')==0)
			return "South";
		else if (strcmp(curr_direction, 'South')==0)
			return "West";
		else
			return "North";
	}
	else
		return curr_direction;

}
