/** \anchor form1
 *
 * @brief Form recognition. 
 *
 * @file

 Example of form recognition and print the result on UART and the LCD Screen.

 * @author Foucault Alisson
 */

/*
#define IDP_0_CROSS 1
#define IDP_1_BIGA 2
#define IDP_2_KING 3
#define IDP_3_TOWER 4
#define IDP_4_TREFLE 5
#define IDP_5_TRIANGLE 6
#define IDP_6_CIRCLE 7

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
UInt8 find_likely_pattern(UInt8 length);
char * get_new_direction(char * curr_direction, UInt8 turn);
void turn_right_angle(UInt8 turn);
void find_stream();
void find_bridge();
void cross_bridge();
void find_stream_majority();
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
	SetServoMotor(0, 30);
	InitUART0(115200);



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
	run();
	return 0;
}

/*
Takes a length of ListOfForm
Returns a the ID of the shape that happens the most in the array*/
UInt8 find_likely_pattern(UInt8 length)
{
	// Initialize an array to count the occurrences of each pattern 
	UInt8 occur[8];
	UInt8 j=0;
	for (j=0; j<8; j++)
		occur[j]=0;
	// Fill the array with the information from ListOfForm		
	UInt8 i=0;
	for (i=0; i<length; i++)
		{
			occur[ListOfForm[i].id] += 1;
		}
	// Find the max
	UInt8 max = -1;
	UInt8 max_index=-1;
	for (j=0; j<8; j++)
		{
			if (occur[j]>max){
				max = occur[j];
				max_index = j;		
			}
		}
	
	return j;
}

void run(){

	// set as 1 after stream, bridge detected
	int stream = 0;
	int bridge = 0;
	// set as 1 during stream crossing
	int cross = 0;
	
	UInt8 i=0,Nb_Identify=0, shape;
	while(1)
	{		
		// grab the RGB components
		GrabRGBFrame();				
		// Binary the three RGB Buffer
		BinaryRGBFrame(FrameFromCam); 
		// Try to identify the forms and make a list of it
		Nb_Identify=IdentifyForm(FrameFromCam,ListOfForm,pattern);	
		/*if (Nb_Identify<2){
			shape = ListOfForm[0].id;
			PrintToUart0("Identified a single shape in the frame.\n");
			PrintToUart0("%d\n", shape);
		}
		else {
			shape = find_likely_pattern(Nb_Identify);
			PrintToUart0("Identified a multiple shapes\n");
			PrintToUart0("%d\n", shape);
		}*/
		
		switch (ListOfForm[0].id)
			{
				// Cross = Bridge
				case IDP_0_CROSS:
					// if stream wasn't found yet, ignore
					if (!stream)
						continue;
					if (cross)
					{
						SetLed();
						PrintTextOnPobLCD(5,2, "Freedom!!!\n", LCD_Buffer);	
						DrawLCD(&ScreenBuffer);						
						MoveBot(RUN);
						continue;			
					}
					//PrintToUart0("CROSS\n");
					//PrintTextOnPobLCD(3,2, "CROSS\n", LCD_Buffer);	
					DrawLCD(&ScreenBuffer);
					bridge=1;
					break;
				// Tower = Road
				case IDP_3_TOWER:
				// if the continuation of the road is recognized, turn right
					if (bridge)
					{
						turn_right_angle(RIGHT);
						curr_direction = get_new_direction(curr_direction, RIGHT);
						PrintTextOnPobLCD(1,2, curr_direction, LCD_Buffer);	
						DrawLCD(&ScreenBuffer);
						bridge--;
						cross++;
						continue;
					}
				// if the other side of the bridge is reached, turn  and turn off LED					
					if (cross)
					{
						ClearLed();
						PrintTextOnPobLCD(5,2, "Nailed it.\n", LCD_Buffer);
						DrawLCD(&ScreenBuffer);
						MoveBot(RUN);
						continue;
					}
					//PrintToUart0("TOWER\n");
					//PrintTextOnPobLCD(3,2, "TOWER\n", LCD_Buffer);
					//DrawLCD(&ScreenBuffer);
					MoveBot(RUN);
					break;
				case IDP_4_TREFLE:
					//PrintToUart0("TREFLE\n");
					//PrintTextOnPobLCD(3,2, "TREFLE\n", LCD_Buffer);
					//DrawLCD(&ScreenBuffer);
					break;
				// Triangle = Stream
				case IDP_5_TRIANGLE:  
					if (stream)
					{	// if there's a risk to fall into the water, correct to the right
						if (cross)
						{	
							MoveBot(RIGHT);
							WaitUs(200000);
							MoveBot(RUN);
						}	
						continue;
					}
					 
					//PrintToUart0("TRIANGLE\n");
					//PrintTextOnPobLCD(3,2, "TRIANGLE\n", LCD_Buffer);
					//DrawLCD(&ScreenBuffer);
					MoveBot(STOP);
					turn_right_angle(LEFT);
					stream = 1;
					curr_direction = get_new_direction(curr_direction, LEFT);
					PrintTextOnPobLCD(1,2, curr_direction, LCD_Buffer);	
					DrawLCD(&ScreenBuffer);
					//return;
				case IDP_6_CIRCLE:
					//PrintToUart0("CIRCLE\n");
					//PrintTextOnPobLCD(3,2, "CIRCLE\n", LCD_Buffer);
					//DrawLCD(&ScreenBuffer);
					break;
				default:
					break;
			}			
			PrintTextOnPobLCD(1,2, curr_direction, LCD_Buffer);	
			DrawLCD(&ScreenBuffer);
			

		
	}
}


void turn_right_angle(UInt8 turn)
{
	/* Left turn should take a bit longer for some reason */
	int time = 2200000;
	//if (turn==LEFT)
	//	time+=200000;
	MoveBot(turn);
	WaitUs(time);
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

/*void find_stream(){
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
			PrintToUart0("%d\n", i);
			switch (ListOfForm[i].id)
			{
				case IDP_0_CROSS:
					PrintToUart0("CROSS\n");
					PrintTextOnPobLCD(3,2, "CROSS\n", LCD_Buffer);
					DrawLCD(&ScreenBuffer);	
					break;
				case IDP_3_TOWER:
					PrintToUart0("TOWER\n");
					PrintTextOnPobLCD(3,2, "TOWER\n", LCD_Buffer);
					DrawLCD(&ScreenBuffer);
					MoveBot(RUN);
					break;
				case IDP_4_TREFLE:
					PrintToUart0("TREFLE\n");
					PrintTextOnPobLCD(3,2, "TREFLE\n", LCD_Buffer);
					DrawLCD(&ScreenBuffer);
					break;
				case IDP_5_TRIANGLE:
					PrintToUart0("TRIANGLE\n");
					PrintTextOnPobLCD(3,2, "TRIANGLE\n", LCD_Buffer);
					
					break;
				case IDP_6_CIRCLE:
									PrintToUart0("CIRCLE\n");

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
					DrawLCD(&ScreenBuffer);
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
*/