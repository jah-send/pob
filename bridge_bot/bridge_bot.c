/* Embedded Systems CS4397
	Group 1: Joshua Honeycutt, Dani Raznikov, Alwin Mathew, Steve Coopman
	

Reference: Defined in pattern.h
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
void run();
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
	// Init Ascii buffer, use to write in the LCD screen with PrintTextOnPobLCD function
	InitAsciiBuffer();
	// Init the Graphic buffer with 128 per 64, one pixel per bit and LCD_Buffer
	InitGraphicBuffer( &ScreenBuffer, LCD_WIDTH,LCD_HEIGHT,ONE_BIT,LCD_Buffer);
	// clear the graphic buffer
	ClearGraphicBuffer(&ScreenBuffer);
	DrawLCD(&ScreenBuffer);

	// Set Camera Tilt for initial position
	SwitchOnAllServo(); 
	SetServoMotor(0, 30);
	
	// Initialize UART0 (For debugging purposed)
	// InitUART0(115200);


	// Get the pointer of the red,green and blue video buffer
	FrameFromCam = GetRGBFrame();



	// Set the robot to go North initiallly
	PrintTextOnPobLCD(1,2, "North", LCD_Buffer);
	DrawLCD(&ScreenBuffer);
	// Initialize LED (blink)
	SetLed();
	WaitUs(500000);
	ClearLed();
	// Run the program
	run();
	return 0;
}

/* The robot driver function*/
void run(){
	
	/* Flags */
	int stream = 0; // set to 1 after the stream was initially detected
	int bridge = 0; // set to 1 after the bridge was dettected
	int cross = 0; // set to 1 during stream crossing

	
	UInt8 Nb_Identify=0;
	while(1)
	{		
		// grab the RGB components
		GrabRGBFrame();				
		// Binary the three RGB Buffer
		BinaryRGBFrame(FrameFromCam); 
		// Identify the form seen by the 
		Nb_Identify=IdentifyForm(FrameFromCam,ListOfForm,pattern);
		// If no form was identified, try again.
		if (Nb_Identify == 0)
			continue;		
			
		// Detect the first form noticed.
		switch (ListOfForm[0].id)
			{
				// Cross is equivalent to a bridge in our map.
				case IDP_0_CROSS:
					// if the stream wasn't found yet, ignore any cross detection.
					if (!stream)
						continue;
						
					// if the robot crossing the bridge
					else if (cross)
					{
						SetLed(); // notify others that the robot is crossing the bridge with the LED.
						PrintTextOnPobLCD(5,2, "Freedom!!!\n", LCD_Buffer);	
						DrawLCD(&ScreenBuffer);						
						MoveBot(RUN);
					}
					
					// if just detected the bridge, set bridge flag
					else
						bridge=1;

					break;
					
				// Cross is equivalent to a road in our map.
				case IDP_3_TOWER:
				
					/* If a bridge was detected and now the road is detected again,
						it means the robot is perfectly placed on the bridge. 
						In that case, turn right to prepare for crossing.
					*/
					if (bridge)
					{
						turn_right_angle(RIGHT);
						// Update direction
						curr_direction = get_new_direction(curr_direction, RIGHT);
						PrintTextOnPobLCD(1,2, curr_direction, LCD_Buffer);	
						DrawLCD(&ScreenBuffer);
						// unset bridge flag after the turn was completed
						bridge--;
						// set the cross flag to start crossing mechanism
						cross++;
						continue;
					}
					
					/*
					If the road is detected while the cross flag is set, it means that the bridge
						is successfully crossed. Print a success message, clear LED and continue forward.
					
					@@ Can add a different behavior -- for example, make the robot turn right after the bridge.
					*/			
					if (cross)
					{
						ClearLed();
						PrintTextOnPobLCD(5,2, "Nailed it.\n", LCD_Buffer);
						DrawLCD(&ScreenBuffer);
						MoveBot(RUN);
						continue;
					}
					
					/* If previous conditions haven't been met -- it is just a regular road.*/
					MoveBot(RUN);
					break;

				// Triangle is equivalent to a stream in our map.
				case IDP_5_TRIANGLE:  
					/* If stream was not detected yet, stop the bot, turn left,
						update the directions and set the stream flag.*/ 
					if (!stream)
					{
						MoveBot(STOP);
						turn_right_angle(LEFT);
						stream = 1;
						curr_direction = get_new_direction(curr_direction, LEFT);
						PrintTextOnPobLCD(1,2, curr_direction, LCD_Buffer);	
						DrawLCD(&ScreenBuffer);
					}
					/* We observed that the robot tends to the left border of the bridge while crossing.
					If that is the case, correct to the right.*/
	
					else if (stream & cross)
					{		
						MoveBot(RIGHT);
						WaitUs(200000);
						MoveBot(RUN);
					}
					break;
				default:
					break;
			}			
			// print the current direction after each iteration
			PrintTextOnPobLCD(1,2, curr_direction, LCD_Buffer);	
			DrawLCD(&ScreenBuffer);
	}
}

/* Helper function to perform a 90 degrees turn to the passed direction.
Args: 
	UInt8 turn - LEFT or RIGHT (single byte direction integer)
*/
void turn_right_angle(UInt8 turn)
{
	int time = 2200000;
	MoveBot(turn);
	WaitUs(time);
	MoveBot(STOP);
	return;
}

/* Helper function to update the direction string for the Robot.
Args:
	char * curr_direction - pointer to the char array(string) that holds the current direction.
	UInt8 turn - LEFT or RIGHT (single byte direction integer)
Returns:
	char * curr_direction - pointer to the new direction the robot is going to face.
*/
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


Takes a length of ListOfForm
Returns a the ID of the shape that happens the most in the array
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


*/

