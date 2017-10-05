//POB-Technology - 2008
//
// How to use:
// - compile project with pobtools
// - download to pobeye
// - connect pobeye + dualpob + nxt
// - use the pobeye with the nxt!

#include <pob-eye.h>

#include "pattern.h"

//dualpob address on pob-bus:
#define DUALPOB_ADDR	0x06

//pobeye command firmware:

#define POBEYE_COMMAND_ECHO			0x00
#define POBEYE_COMMAND_GRAB			0x01
#define POBEYE_COMMAND_SETFORM 		0x02
#define POBEYE_COMMAND_GETFORM		0x03
#define POBEYE_COMMAND_GRAB_NO_ACK	0x04

//graphic buffer variable
static GraphicBuffer LCD_Fast_Buffer_Video;	
static UInt8 LCD_Fast_Buffer	[64*64*BYTES];


void DrawVision (RGBFrame *FrameFromCam)
{	
	//draw the red buffer (88*120 pixels) on the Buffer for for the left screen (64*64 pixels)
	DrawComponentInABufferVideo(FrameFromCam->red,&LCD_Fast_Buffer_Video);
	DrawLeftLCD(&LCD_Fast_Buffer_Video); //refresh the left screen
}

int main(void)
{
	UInt8 x_form=0;		//x form
	UInt8 y_form=0;		//y form
	UInt8 w_form=0;		//width form
	UInt8 h_form=0;		//height form
	UInt8 found_form=0; //form found == 1
	UInt8 id_form=IDP_CROSS; //form id: default cross 

	UInt8 command,i;
	UInt8 tmpA;
	UInt8 wait=0;

	UInt8 Nb_Identify;
	Form ListOfForm[MAX_OF_FORM];
	RGBFrame FrameFromCam;

	//init hardware
	InitPOBEYE();
	InitLCD();	
		
	//init graphic buffer
	InitGraphicBuffer(&LCD_Fast_Buffer_Video,64,64,EIGHT_BITS,LCD_Fast_Buffer);

	//get the pointer of the RGB camera buffer
	GetPointerOnRGBFrame(&FrameFromCam);


	while(1)
	{
		command = ReadByte(DUALPOB_ADDR);

		switch(command)
		{
		// Simple echo test
		case POBEYE_COMMAND_ECHO:
			tmpA = ReadByte(DUALPOB_ADDR);
			WriteByte(DUALPOB_ADDR,tmpA+1);
			break;
		// Grab a frame from pobeye camera (and don't aknowledge)
		case POBEYE_COMMAND_GRAB_NO_ACK:
			//no ack
			wait = 1;
		// Grab a frame from pobeye camera 
		case POBEYE_COMMAND_GRAB:

			//grab the RGB components
			GrabRGBFrame();				
		
			//binary the RGB Buffer
			BinaryRGBFrame(&FrameFromCam); 

			DrawVision(&FrameFromCam);
			
			Nb_Identify=IdentifyForm(&FrameFromCam,ListOfForm,pattern);	
			
			found_form=0;
			x_form=0;
			y_form=0;
			w_form=0;
			h_form=0;
			for(i=0;i<Nb_Identify;i++)
			{
				if(id_form==ListOfForm[i].id)
				{
					x_form = ListOfForm[i].x;
					y_form = 120 - ListOfForm[i].y;
					w_form = ListOfForm[i].width;
					h_form = ListOfForm[i].height;

//					PrintTextOnPobTerminal("ListOfForm[i].y %d y %d", ListOfForm[i].y, y_form);
//					PrintTextOnPobTerminal("x %d y %d w %d h %d",x_form,y_form,w_form,h_form);

					found_form=1;
				}
			}

			if(wait==0)
			{
				WriteByte(DUALPOB_ADDR,0x01);
			}
//			else
//			{
//				PrintTextOnPobTerminal("grab\n");
//			}
			wait=0;

			break;
		case POBEYE_COMMAND_SETFORM:

			id_form = ReadByte(DUALPOB_ADDR);

			if(id_form<1)
				id_form=IDP_CROSS;
			else if(id_form>7)
				id_form=IDP_CROSS;

			break;
		case POBEYE_COMMAND_GETFORM:

			WriteByte(DUALPOB_ADDR,found_form);
			WriteByte(DUALPOB_ADDR,x_form);
			WriteByte(DUALPOB_ADDR,y_form);
			WriteByte(DUALPOB_ADDR,w_form);
			WriteByte(DUALPOB_ADDR,h_form);

//			PrintTextOnPobTerminal("getform\n");

			found_form=0;
			x_form=0;
			y_form=0;
			w_form=0;
			h_form=0;

			break;
		}
	}

}
