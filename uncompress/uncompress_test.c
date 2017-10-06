 #include <pob-eye.h>

 int main(void)
 {
        UInt32 i;

        // Declare a pointer:
        UInt8 *redFrame;

        // Create 2 buffers to store green and blue pixels:
        UInt8 greenFrame[WIDTH_FRAME*HEIGHT_FRAME];
        UInt8 blueFrame[WIDTH_FRAME*HEIGHT_FRAME];

        UInt8 red, green, blue;

        // Init pobeye2 cpu, i2c bus and camera:
        InitPobeye2();
        InitI2C(I2C_100_KHZ);
        InitCameraPobeye2();

        // Get pointer to the red memory:
        redFrame = GetRGBFrame();

        InitUART0(115200);
        // Main loop:
        while(1)
        {
                // Capture a frame: red pixels are copied to redFrame, green pixels to greenFrame and blue pixels to blueFrame.
                GrabFullRGBFrame(greenFrame,blueFrame);
				
                for(i=0; i < WIDTH_FRAME*HEIGHT_FRAME ; i++ )
                {
                        // Get red, green and blue pixels:
                        red     = redFrame[i];
                        green   = greenFrame[i];
                        blue    = blueFrame[i];
                        PrintToUart0("%d", red);
                        PrintToUart0("%d", green);
                        PrintToUart0("%d\n", blue);
                        WaitMs(500000);
                }

        }
 }