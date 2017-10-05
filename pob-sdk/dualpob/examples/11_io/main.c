/** \anchor example11
 *
 * @brief Input/Output example. 
 *
 * @file
 
 An example to use the digital input/output and use the timer.

 This example generate a clock pulse on pin 2 and pin 7 of PORTE. You can verify the clock pulse with an oscilloscope.


 */
#include <dual-pob.h>


static UInt8 tick2;

// Example of how to use timer function
void MyTimerFunction(void)
{
	// Clock output on pin 2 of PORTE: 
    if(tick2==0)
    {
		SetOutput(PORTE,PIN_2);
        tick2=1;
	}
    else
    {
		ClearOutput(PORTE,PIN_2);
        tick2=0;
	}

}

int main(void)
{
	UInt8 tick;
	UInt8 portb;
	UInt8 porte;
	UInt8 portf;
	UInt8 portg;

	// Set io as default
	portb = IO_AS_DEFAULT ;
	portf = IO_AS_DEFAULT ;
	portg = IO_AS_DEFAULT ;

	// Set pin2 and pin7 of PORTE as output (the other pin are set as input by default)
	porte = (IO_AS_OUTPUT << PIN_2) | (IO_AS_OUTPUT << PIN_7 ); 

	// Finally, write the i/o configuration:
	SetIOWay(portb, porte,portf,portg);

	// Init timer overflow to 7.5 ms
	Timer1Init(50536,TIMER1_8);

	tick2=0;

	// Attach a function to timer1
	Timer1AttachFunction(MyTimerFunction);

	tick=0;
	while(1)
	{
		// Wait an overflow of timer:
        if( IsTimer1Overflow() == 1 )
        {
			// Clock output on pin 7 of PORTE: 
            if(tick==0)
            {
				SetOutput(PORTE,PIN_7);
                tick=1;
			}
            else
            {
				ClearOutput(PORTE,PIN_7);
                tick=0;
			}
        }

	}

	return 0;
}
