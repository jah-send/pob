//
//  Created by Name on Date.
//

#include <string.h>
#include <pob-eye.h>
#include "pad.h"


// external functions declarations (for PrintTextOnPobLCD)
extern void InitAsciiBuffer();
extern void PrintTextOnPobLCD(int row, int col, char *string, UInt8 *Screen_Buffer);
extern void HLightText(int row, int col, int size, UInt8 *Screen_Buffer);

int main(void)
{
    //This buffers will stock the pixels to display,
    GraphicBuffer LCD_Buffer_Video;
    UInt8         LCD_Buffer[LCD_WIDTH*LCD_HEIGHT*BITS];
    // Buffer to stock the ascii table in bitmap format
    UInt8         ASCII_Buffer[LCD_WIDTH*LCD_HEIGHT*BITS];

    //Initialize POB-EYE (lib), POB-LCD (lib), POB-PROTO(file Functions.c) and Servomotors
    InitPobeye2();
    InitLCD();
    InitPobProto();
    SwitchOnAllServo();

    // Initialize the Graphic buffer with 128 per 64, one pixel per bit and LCD_Buffer
    InitGraphicBuffer( &LCD_Buffer_Video, LCD_WIDTH,LCD_HEIGHT,ONE_BIT,LCD_Buffer);

    //Clear and draw the buffer to make clean the screen
    ClearGraphicBuffer(&LCD_Buffer_Video);
    DrawLCD(&LCD_Buffer_Video);

    // Init Ascii buffer, use to write in the LCD screen with PrintTextOnPobLCD function
    InitAsciiBuffer();

    int turn_time;
    char tts[10];
    SetDCSpeed(35);
    for (turn_time = 500000; turn_time < 3000000; turn_time += 50000) {
        // Print current time spent turning
        PrintTextOnPobLCD(1, 2, "TurnTest", LCD_Buffer);
        PrintToABuffer(tts, "%d", turn_time);
        PrintTextOnPobLCD(5, 3, tts, LCD_Buffer);
        PrintTextOnPobLCD(6, 3, "microseconds", LCD_Buffer);
        DrawLCD(&LCD_Buffer_Video);

        // Turn right
        MoveBot(RIGHT);
        WaitUs(turn_time);
        MoveBot(STOP);

        // Wait half a second
        WaitUs(500000);

        // Turn left for same amount of time;
        MoveBot(LEFT);
        WaitUs(turn_time);
        MoveBot(STOP);

        // Wait 2 seconds between turn tests
        WaitUs(2000000);
    }
return 0;
}
