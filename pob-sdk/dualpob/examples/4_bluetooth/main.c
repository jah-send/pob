/** \anchor example3
 *
 * @brief Bluetooth example. 
 *
 * @file

	Init the bluetooth module on the DUAL-POB (Bluetooth module is an option).

 */
 include <dual-pob.h>


int main(void)
{
	UInt8 data;

	// init bluetooth at 19200 bauds with name "TEST"
	// if you scan bluetooth network on your computer, a device named "TEST" will appear.
	// if the bluetooth device named "TEST" don't appear, set correct dip switch and reboot the dualpob
	if(InitBluetooth(19200,"TEST")!=BLUETOOTH_OK)
	{
		//an error occurs during initialization of bluetooth module
		//... init uart0 instead of bluetooth
		InitUART0(19200);

		SendString("Bluetooth failed! Please set correct dip switch!\r\n");
	}

	//simple ping pong between your computer and the dual-pob
	while(1)
	{
		data = GetByteFromUART0();

		SendByteToUART0(data);
	}

	return 0;
}