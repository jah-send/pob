/* Copyright POB-Technology, 2008
 *
 * contact@pob-technology.com
 * 
 * This software is the main firmware of DUAL-POB device.
 * 
 * This software is governed by the CeCILL-C license under French law and
 * abiding by the rules of distribution of free software.  You can  use, 
 * modify and/ or redistribute the software under the terms of the CeCILL-C
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info". 
 * 
 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited
 * liability. 
 * 
 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 * therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or 
 * data to be ensured and,  more generally, to use and operate it in the 
 * same conditions as regards security. 
 * 
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL-C license and that you accept its terms.
 * 
 */

// dual-pob library include
#include <dual-pob.h>


// firmware configuration
#include "config.h"


// main program:
int main(void)
{
	UInt8 data;

#ifdef DEBUG_DUAL_POB
	UInt8 string[16];
	UInt8 len;
#endif

	// Init communication link: 

	// 0 - uart 
	if(InitBluetooth(UART_BAUDRATE,"DUALPOB")!=BLUETOOTH_OK)
	{
		// If bluetooth failed, init the default uart
		InitUART0(UART_BAUDRATE);
	}

	// 1 - i2c slave
	InitI2CSlave(I2C_SLAVE_ADDR);

	// Init dual-pob hardware:

	// 2 - pobeye camera bus
	InitPobBus();
	
	// 3 - dual-servo device bus
	// warning, if you don't have dualpob servo board, next function go to infinite loop!
	InitDualServo();
	
	// 4 - ax12 bus
	InitAx12Bus();
	
	// 5 - input/output pins
	SetIOWay(IO_AS_DEFAULT, IO_AS_DEFAULT,IO_AS_DEFAULT,IO_AS_DEFAULT);

	// 6 - analog pin
	InitAnalog();

#ifdef DEBUG_DUAL_POB
	SendString("main dual-pob firmware\r\n");
#endif

	// Main loop program
	while(1)
	{
		// Byte ready from pob-eye on pob-bus?
		if(IsByteReadyFromPOBEYE()==1)
		{
			//...yes, get pob-eye byte
			data = GetByteFromPOBEYE();
		
#ifdef DEBUG_DUAL_POB
			len=Bin2Dec(data,string);
			SendString("\r\ncommand= ");
			SendBufferToUART0(string,len);
#endif

			//... and process pob-eye command
			ProcessPobeyeCommand(data);
		}
		
		// NXT send a data?
		if(ReadOnI2CSlave(&data)==1)
		{
#ifdef DEBUG_DUAL_POB
			Bin2Hex(data,string);
			string[2]='-';
			SendBufferToUART0(string,3);
#endif
			
			//...yes, then process i2c command

			ProcessI2cCommand(data);
		}

		//	Receive a byte from UART?
		if( GetByteFromUART0NoWait(&data) ==1)
		{
			//...yes, then process uart command
			ProcessUARTCommand(data);
		}		
	
	}

	return 0;
}

