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

char * get_new_direction(char * curr_direction, UInt8 turn);
void turn_right_angle(UInt8 turn);
void find_stream();
void find_bridge();
void cross_bridge();

char * curr_direction = "North";
// List of form
Form ListOfForm[MAX_OF_FORM];
// Struct of three pointers on the RGB components
UInt8 * FrameFromCam;
//The pixels will be stocked in the LCD buffer
UInt8 LCD_Buffer [LCD_WIDTH*LCD_HEIGHT*BITS] ;
GraphicBuffer ScreenBuffer ;

int main (void)
{	



	// System and LCD screen initialization
	InitPobeye2();
	InitI2C(I2C_100_KHZ);
	InitCameraPobeye2();
	InitLCD();	
	InitPobProto();
	// set camera to look downward (15? degrees)
	SwitchOnAllServo(); 
	SetServoMotor(0, 45);


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
	InitUART0(115200);

	ClearLed();

	find_stream();
	//find_bridge();
	//cross_bridge();

	return 0;
}

void find_stream(){
	UInt8 i=0,Nb_Identify=0;
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
					PrintTextOnPobLCD(3,2, "CROSS\n", LCD_Buffer);	
					break;
				case IDP_3_TOWER:
					PrintTextOnPobLCD(3,2, "TOWER\n", LCD_Buffer);
					MoveBot(RUN);
					break;
				case IDP_4_TREFLE:
					PrintTextOnPobLCD(3,2, "TREFLE\n", LCD_Buffer);
					break;
				case IDP_5_TRIANGLE:
					PrintTextOnPobLCD(3,2, "TRIANGLE\n", LCD_Buffer);
					break;
				case IDP_6_CIRCLE:
					PrintTextOnPobLCD(3,2, "CIRCLE\n", LCD_Buffer);
					MoveBot(STOP);
					turn_right_angle(LEFT);
					curr_direction = get_new_direction(curr_direction, LEFT);
					PrintTextOnPobLCD(1,2, curr_direction, LCD_Buffer);	
					DrawLCD(&ScreenBuffer);
					return;
					break;
				default:
					break;
			}			
			PrintTextOnPobLCD(1,2, curr_direction, LCD_Buffer);	
			DrawLCD(&ScreenBuffer);
		}
	}
}

void find_bridge(){
	UInt8 i=0,Nb_Identify=0;
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
					PrintTextOnPobLCD(3,2, "CROSS", LCD_Buffer);	
					// Draw bitmap on the buffer and the LCD screen
					MoveBot(STOP);
					break;

				case IDP_1_BIGA:
					PrintTextOnPobLCD(3,2, "BIGA", LCD_Buffer);
					break;

				case IDP_2_KING:
					PrintTextOnPobLCD(3,2, "KING", LCD_Buffer);
					break;

				case IDP_3_TOWER:
					PrintTextOnPobLCD(3,2, "TOWER", LCD_Buffer);
					turn_right_angle(RIGHT);
					curr_direction = get_new_direction(curr_direction, RIGHT);
					break;

				case IDP_4_TREFLE:
					PrintTextOnPobLCD(3,2, "TREFLE", LCD_Buffer);
					break;

				case IDP_5_TRIANGLE:
					PrintTextOnPobLCD(3,2, "TRIANGLE", LCD_Buffer);
					MoveBot(RUN);

					break;
				case IDP_6_CIRCLE:
					PrintTextOnPobLCD(3,2, "CIRCLE", LCD_Buffer);
					turn_right_angle(LEFT);
					curr_direction = get_new_direction(curr_direction, LEFT);
					break;
				default:
					break;
			}			
			PrintTextOnPobLCD(1,2, curr_direction, LCD_Buffer);	
			DrawLCD(&ScreenBuffer);
		}		
		if (Nb_Identify == 0)
		{

		}
	}

}

void cross_bridge(){
	UInt8 i=0,Nb_Identify=0;
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
					PrintTextOnPobLCD(3,2, "CROSS", LCD_Buffer);	
					// Draw bitmap on the buffer and the LCD screen
					MoveBot(STOP);
					break;

				case IDP_1_BIGA:
					PrintTextOnPobLCD(3,2, "BIGA", LCD_Buffer);
					break;

				case IDP_2_KING:
					PrintTextOnPobLCD(3,2, "KING", LCD_Buffer);
					break;

				case IDP_3_TOWER:
					PrintTextOnPobLCD(3,2, "TOWER", LCD_Buffer);
					turn_right_angle(RIGHT);
					curr_direction = get_new_direction(curr_direction, RIGHT);
					break;

				case IDP_4_TREFLE:
					PrintTextOnPobLCD(3,2, "TREFLE", LCD_Buffer);
					break;

				case IDP_5_TRIANGLE:
					PrintTextOnPobLCD(3,2, "TRIANGLE", LCD_Buffer);
					MoveBot(RUN);

					break;
				case IDP_6_CIRCLE:
					PrintTextOnPobLCD(3,2, "CIRCLE", LCD_Buffer);
					turn_right_angle(LEFT);
					curr_direction = get_new_direction(curr_direction, LEFT);
					break;
				default:
					break;
			}			
			PrintTextOnPobLCD(1,2, curr_direction, LCD_Buffer);	
			DrawLCD(&ScreenBuffer);
		}		
		if (Nb_Identify == 0)
		{

		}
	}

}

void turn_right_angle(UInt8 turn)
{
	// TODO Figure out a better timinig for turning 90 degrees
	MoveBot(turn);
	WaitUs(1900000);
	MoveBot(STOP);
	return;
}
char * get_new_direction(char * curr_direction, UInt8 turn)
{
	if (turn == LEFT)
	{
		if (strcmp(curr_direction, "North")==0)
			curr_direction = "West\n";
		else if (strcmp(curr_direction, "East\n")==0)
			curr_direction = "North";
		else if (strcmp(curr_direction, "South")==0)
			curr_direction = "East\n";
		else
			curr_direction = "South";
	}
	else if (turn == RIGHT)
	{
		if (strcmp(curr_direction, "North")==0)
			curr_direction = "East\n";
		else if (strcmp(curr_direction, "East\n")==0)
			curr_direction = "South";
		else if (strcmp(curr_direction, "South")==0)
			curr_direction = "West\n";
		else
			curr_direction = "North";
	}

	return curr_direction;

}
