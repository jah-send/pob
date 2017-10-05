//simple test of i2c api:
// you have to solder i2c bus between dualpob and pobeye to test!
#include <pob-eye.h>

#include "../dualpob_i2c_lib.h"

void SendString(UInt8 *str)
{
	UInt32 i=0;
	for(i=0; str[i]!=0;i++)
	{
		SendByteToUART(str[i]);
	}
}

int main(void)
{
	UInt8 data,i;
	Int8 string[128];

	UInt8 x,y,w,h;

	InitPOBEYE();
	InitI2C();

	Wait(20000);
	Wait(20000);
	Wait(20000);

	data = DP_IO_AS_OUTPUT << DP_PIN_2 ;
	dualpob_setIoWay(DP_IO_AS_DEFAULT,data,DP_IO_AS_DEFAULT,DP_IO_AS_DEFAULT);

	while(1)
	{
		SendString("Test I2C dualpob\n\r");

		data = GetByteFromUART();

		switch(data)
		{
		case 'y':
			break;

		case 'p':

			data = dualpob_pobeyeTest(0xAA);

			SendString("Test pobeye com: ");
			sprintf(string,"0x%X \n\r",data);
			SendString(string);

			break;
		case 'f':
			
			dualpob_setPobeyeForm(2);

			data = dualpob_grabFrame();

			SendString("\n\rGrab result=");
			sprintf(string,"%d\n\r",data);
			SendString(string);

			data = dualpob_getPobeyeForm(&x,&y,&w,&h);
			SendString("Form: ");
			sprintf(string,"%d xy=%d %d wh=%d %d\n\r",data,x,y,w,h);
			SendString(string);
		
			break;
		case 'e':
			for(i=0;i<0xFE;i++)
			{
				data = dualpob_echo(i);
				if(data!= (i+1) )
				{
					SendString("Failed to get echo: ");
					sprintf(string,"%d %d\n\n\r",data,i+1);
					SendString(string);
				}
			}
			
			SendString("Echo test end.\n\r");

		break;
		/*
		case 's':
			dualpob_setServo(1,255,7);
			Wait(20000);
			dualpob_setServo(1,20,2);
			break;
		case 'm':
			dualpob_setDCSpeed(1);
			dualpob_setDCMotor(DC_MOTOR_RUN);
			break;
		case 'h':
			dualpob_setDCMotor(DC_MOTOR_STOP);
			break;
		case 'o':
			for(i=0;i<2;i++)
			{
				//set or clear take 250 us
				dualpob_setOutput(OUTPUT_PORTE,PIN_2);
				Wait(250);
				dualpob_clearOutput(OUTPUT_PORTE,PIN_2);
				Wait(250);
			}
		break;*/
		}
		
	}
}