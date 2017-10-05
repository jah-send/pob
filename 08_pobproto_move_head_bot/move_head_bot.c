/** \anchor proto3
 *
 * @brief POB-Proto example 2. 
 *
 * @file

 An example to move the head of the bot with the joystick.

 * @author Foucault Alisson
 */ 


#include <string.h>
#include <pob-eye.h>
#include "pad.h"

#define         WIDTH_FRAME   160
#define         HEIGHT_FRAME   120

void reverse(char s[])
{
        int i, j;
        char c;

        for (i = 0, j = strlen(s)-1; i<j; i++, j--) {
                c = s[i];
                s[i] = s[j];
                s[j] = c;
        }
}

void itoa(int n, char s[])
{
        int i, sign;

        if ((sign = n) < 0)
                n = -n;
        i = 0;
        do {
                s[i++] = n % 10 + '0';
        } while ((n /= 10) > 0);
        if (sign < 0)
                s[i++] = '-';
        s[i] = '\0';
        reverse(s);
}

int getSumOfReds(UInt8 * rgbFrame)
{
        int i;
        int sum = 0;
        for (i=0; i<WIDTH_FRAME * HEIGHT_FRAME; i++)
        {
                sum += GetRed(rgbFrame[i]); 
        }

        return sum;
}

int getSumOfBlues(UInt8* rgbFrame)
{
        int i;
        int sum = 0;
        for (i=0; i<WIDTH_FRAME * HEIGHT_FRAME; i++)
        {
                sum += GetBlue(rgbFrame[i]); 
        }

        return sum;
}

int getSumOfGreens(UInt8* rgbFrame)
{
        int i;
        int sum = 0;
        for (i=0; i<WIDTH_FRAME * HEIGHT_FRAME; i++)
        {
                sum += GetGreen(rgbFrame[i]); 
        }

        return sum;
}
// external functions declarations (for PrintTextOnPobLCD)
extern void InitAsciiBuffer();
extern void PrintTextOnPobLCD(int row, int col, char *string, UInt8 *Screen_Buffer);

int     main(void)
{       
        //variable declaration (128 is the center of the LCD screen)
        int top_bottom_axe = 128;
        int right_left_axe = 128;
        char top_bottom[10]; 
        char right_left[10];
        int     position = 130;


        //This buffers will stock the pixels to display, 
        GraphicBuffer           LCD_Buffer_Video;
        UInt8                   LCD_Buffer[LCD_WIDTH*LCD_HEIGHT*BITS];

        //Initialize POB-EYE (lib), POB-LCD (lib) and POB-PROTO(file Functions.c)
        InitPobeye2();
        InitLCD();                      
        InitPobProto();
        InitI2C(I2C_100_KHZ);
        // the pobeye2 camera use the i2c bus for setting, you have to configure i2c bus before!
        InitCameraPobeye2();


        // Initialize the Graphic buffer with 128 per 64, one pixel per bit and LCD_Buffer
        InitGraphicBuffer( &LCD_Buffer_Video, LCD_WIDTH,LCD_HEIGHT,ONE_BIT,LCD_Buffer);

        //Clear and draw the buffer to make clean the screen
        ClearGraphicBuffer(&LCD_Buffer_Video);
        DrawLCD(&LCD_Buffer_Video);

        // Init Ascii buffer, use to write in the LCD screen with PrintTextOnPobLCD function
        InitAsciiBuffer(); 
        UInt32 i;
        UInt8 *rgbFrame;
        UInt8 red[10], green[10], blue[10];

        // Init pobeye2 cpu, i2c bus and camera sensor:


        // Get pointer to the pobeye2 RGB memory:
        rgbFrame = GetRGBFrame();
        InitUART0(115200);

        while (1)
        {               
                // Capture a camera frame and copy it to the pobeye2 memory:
                GrabRGBFrame();

                // Get pixel color:

                i=400;
                int n;
                for (n=0; i< 12400; i+=1200){
                        red[n]   = GetRed(rgbFrame[i]);
                        green[n] = GetGreen(rgbFrame[i]);
                        blue[n]  = GetBlue(rgbFrame[i]);
                        n++;
                }

                int r = 0,g = 0,b = 0;
                int p;
                for (p = 0; p<10; p++){
                        r += red[p];
                        g += green[p];
                        b += blue[p];
                }
                r = r/10;
                g = g/10;
                b = b/10;
                //Send "Hello World" to the UART0


                SendBufferToUART0((unsigned char*) "Hello World", 11);
                //convert it from int to char*
                char redchar[10], greenchar[10], bluechar[10];
                
                int redsum = getSumOfReds(rgbFrame);
                                int greensum = getSumOfGreens(rgbFrame);
                                                int bluesum = getSumOfBlues(rgbFrame);
                char rsum[20], gsum[20], bsum[20];
                                                
                PrintToABuffer(&rsum, "%d", redsum);
                PrintToABuffer(&gsum, "%d", greensum);
                PrintToABuffer(&bsum, "%d", bluesum);
                PrintToABuffer(&redchar, "%d", r); 
                PrintToABuffer(&greenchar, "%d", g);
                PrintToABuffer(&bluechar, "%d", b);
                SendBufferToUART0((unsigned char*) "\nRedsum\n", 6);
                SendBufferToUART0(rsum, 20);
                SendBufferToUART0((unsigned char*) "\ngreensum\n", 8);
                SendBufferToUART0(gsum, 20);
                SendBufferToUART0((unsigned char*) "\nbluesum\n", 7);
                SendBufferToUART0(bsum, 20);              
                //display it
                PrintTextOnPobLCD(1, 1, redchar, LCD_Buffer);
                PrintTextOnPobLCD(2, 1, greenchar, LCD_Buffer);
                PrintTextOnPobLCD(4, 1, bluechar, LCD_Buffer);
                PrintTextOnPobLCD(1, 6, rsum, LCD_Buffer);
                PrintTextOnPobLCD(2, 6, gsum, LCD_Buffer);
                PrintTextOnPobLCD(4, 6, bsum, LCD_Buffer);
                PrintTextOnPobLCD(5, 8, "TEST", LCD_Buffer);
                DrawLCD(&LCD_Buffer_Video);
                WaitUs(5000000);
        }
        return 0;       
}
