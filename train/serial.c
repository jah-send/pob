#include <windows.h>
#include <stdio.h>

void setCommand(char* p, char s) {
	
	// clear the memory
	p[0] = 0;
	p[1] = 0;
	p[2] = 0;
	// three-byte format: 11111110 - 00AAAAAA - ACCDDDDD
	// if the engine is addressed with 23 (in binary: 10111), then AAAAAAA will be 0010111

	// the first byte is OFE
	*p = 0xfe;

	// the second byte: 00AAAAAA
	//engine addressing code:   0000 1011 (and 1 in the third byte)
	*(p+1) = 0x0b;
	
	switch (s) {
		// remain part for the third byte
	case 's': // s - stop - set abs. speed to 0: 1110 0000
		*(p + 2) = 0xe0;
		break;
	case 'g': // g - start (go) - set abs. speed to 15 : 1110 1111
		*(p+2) = 0xef;
		break;
	case 'h': // h - horn : 1001 1100   
		*(p + 2) = 0x9c;
		break;
	case 'b': // b - bell : 1001 1101
		*(p + 2) = 0x9d;
		break;
	case 'f' : // f - forward direction : 1000 0000
		*(p+2) = 0x80;
		break;
	case 'r': // r - reverse direction: 1000 0011
		*(p + 2) = 0x83;
		break;
	case 't': // r - toggle direction: 1000 0001
		*(p + 2) = 0x81;
		break;
	case 'u' : // u - speed up by one: 1100 0110
		*(p + 2) = 0xc6;
		break;
	case 'd' : // d - speed down by one : 1100 0100
		*(p + 2) = 0xc4;
		break;
	case 'w' : // w - boost WOW! : 1000 0100
		*(p + 2) = 0x84;
		break;
	case 'q': // q - brake : 1000 0111
		*(p + 2) = 0x87;
		break;
	case 'l': // l - let-off sound : 1001 1110
		*(p + 2) = 0x9e; 
		break;
	case 'z': // z - aux1 off : 1000 1000
		*(p + 2) = 0x88;
		break;
	case 'x': // x - aux1 on : 1000 1011
		*(p + 2) = 0x8b;
		break;
	case 'c': // c - aux2 off 1000 1100
		*(p + 2) = 0x8c;
		break;
	case 'v': // v - aux 2 on 1000 1111
		*(p + 2) = 0x8f;
		break;
	default: break;

	}

}

void print_usage() {
	
	char * msg = "Use the following commands to control the train: \n "
		  "* START - to start the train.\n "
		  "* STOP - to stop the train.\n "
		  "* HORN - to use the horn.\n "
		  "* BELL - to ring the bell.\n "
		  "* TOGGLE - toggle direction.\n "
		  "* FORWARD - to go forward.\n "
		  "* REVERSE - to go to the reverse direction.\n "
		  "* FASTER - to go a bit faster.\n "
		  "* SLOWER - to go a bit slower.\n "
		  "* BRAKE - to use the brakes.\n "
		  "* BOOST - to use a speed boost.\n "
		  "* LETOFF - to make let-off sound.\n "
		  "\tEnter EXIT to quit.\n";
	fprintf(stdout, msg);
	
}
int main()
{
	fprintf(stdout,  "Welcome to Train Control System!\n ");
	print_usage();
	char bytes_to_send[3];

	// Declare variables and structures
	HANDLE hSerial;
	DCB dcbSerialParams = { 0 };
	COMMTIMEOUTS timeouts = { 0 };

	// Open the COM1 serial port

	hSerial = CreateFile(
		"\\\\.\\COM1", GENERIC_READ | GENERIC_WRITE, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hSerial == INVALID_HANDLE_VALUE)
	{
		fprintf(stderr, "Error\n");
		return 1;
	}

	// Set device parameters (9600 baud, 1 start bit, 1 stop bit, no parity)
	dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	if (GetCommState(hSerial, &dcbSerialParams) == 0)
	{
		fprintf(stderr, "Error getting device state\n");
		CloseHandle(hSerial);
		return 1;
	}
	
	dcbSerialParams.BaudRate = CBR_9600;
	dcbSerialParams.ByteSize = 8;
	dcbSerialParams.StopBits = ONESTOPBIT;
	dcbSerialParams.Parity = NOPARITY;
	if (SetCommState(hSerial, &dcbSerialParams) == 0)
	{
		fprintf(stderr, "Error setting device parameters\n");
		CloseHandle(hSerial);
		return 1;
	}

	// Set COM port timeout settings
	timeouts.ReadIntervalTimeout = 50;
	timeouts.ReadTotalTimeoutConstant = 50;
	timeouts.ReadTotalTimeoutMultiplier = 10;
	timeouts.WriteTotalTimeoutConstant = 50;
	timeouts.WriteTotalTimeoutMultiplier = 10;
	if (SetCommTimeouts(hSerial, &timeouts) == 0)
	{
		fprintf(stderr, "Error setting timeouts\n");
		CloseHandle(hSerial);
		return 1;
	}
	
	char line[10] = ""; // the line to be read from stdin
	char cmd; // character to hold the command
	
	// keep reading from stdin until "EXIT" was the input
	while (fgets(line, sizeof(line), stdin)  && strncmp(line, "EXIT", 4))
	{
		// set cmd to hold the command to be set
		if (!strncmp (line, "HORN", 4))
			cmd='h';
		else if (!strncmp (line, "STOP", 4))
			cmd='s';
		else if (!strncmp (line, "START", 5))
			cmd='g';
		else if (!strncmp (line, "BELL", 4))
			cmd='b';
		else if (!strncmp (line, "FORWARD", 7))
			cmd='f';
		else if (!strncmp (line, "REVERSE", 6))
			cmd='r';
		else if (!strncmp (line, "FASTER", 6))
			cmd='u';
		else if (!strncmp (line, "SLOWER", 6))
			cmd='d';
		else if (!strncmp (line, "BRAKE", 5))
			cmd='q';
		else if (!strncmp (line, "BOOST", 5))
			cmd='w';
		else if (!strncmp(line, "LETOFF", 6))
			cmd='l';
		else if (!strncmp(line, "TOGGLE", 6))
			cmd='t';
		else if (!strncmp(line, "AUX1OFF", 7))
			cmd='z';
		else if (!strncmp(line, "AUX1ON", 6))
			cmd='x';
		else if (!strncmp(line, "AUX2OFF", 7))
			cmd='c';
		else if (!strncmp(line, "AUX2ON", 6))
			cmd='v';
		else
		{
			fprintf(stdout, "Unsupported Command!\n");
			print_usage();
			continue;
		}
		// send command over serial port
		setCommand(bytes_to_send, cmd);
		DWORD bytes_written, total_bytes_written = 0;
		fprintf(stdout, "Sending command...");
		if (!WriteFile(hSerial, bytes_to_send, 3, &bytes_written, NULL))
		{
			fprintf(stderr, "Error\n");
			CloseHandle(hSerial);
			return 1;
		}
		fprintf(stdout, "Done!\n");
	}

    // Close serial port
	if (CloseHandle(hSerial) == 0)
	{
		fprintf(stderr, "Error\n");
		return 1;
	}
	
	return 0;
}
