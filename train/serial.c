#include <windows.h>
#include <stdio.h>

void setCommand(char* p, char s) {
	
	p[0] = 0;
	p[1] = 0;
	p[2] = 0;
	// three-byte format: 11111110 - 00AAAAAA - ACCDDDDD
	// if the engine is addressed with 23 (in binary: 10111), then AAAAAAA will be 0010111

	// the first byte is OFE
	*p |= 1 << 1;
	*p |= 1 << 2;
	*p |= 1 << 3;
	*p |= 1 << 4;
	*p |= 1 << 5;
	*p |= 1 << 6;
	*p |= 1 << 7;

	// the second byte: 00AAAAAA
	//engine addressing code:   000010111
	*(p + 1) |= 1 ;
	*(p + 1) |= 1 << 1;
	*(p + 1) |= 1 << 3;

	// the third byte: 1CCDDDDD
	*(p + 2) |= 1 << 7;
/*
@TODO 
1. Start the engine
2. Stop the engine
*/
	switch (s) {
		// remain part for the third byte
	case 'h': // h - horn : 001 1100   
		*(p + 2) |= 1 << 2;   
		*(p + 2) |= 1 << 3;
		*(p + 2) |= 1 << 4;
		break;
	case 'b': // b - bell : 001 1101
		*(p + 2) |= 1 << 2;
		*(p + 2) |= 1 << 3;
		*(p + 2) |= 1 << 4;
		*(p + 2) |= 1;
		break;
	case 'f' : // f - forward direction : 000 0000
		*(p+2) &= 0;
		break;
	case 'r': // r - reverse direction: 000 0011
		*(p + 2) |= 1 << 1;
		*(p + 2) |= 1;
		break;
	case 't': // r - toggle direction: 000 0001
		*(p + 2) |= 1;
		break;
	case 'u' : // u - speed up by one:  100 0110
		*(p + 2) |= 1 << 6;
		*(p + 2) |= 1 << 2;   
		*(p + 2) |= 1 << 1;   
		break;
	case 'd' : // d - speed down by one : 100 0100
		*(p + 2) |= 1 << 6;
		*(p + 2) |= 1 << 2; 
		break;
	case 'w' : // w - boost WOW! : 000 0100
		*(p + 2) |= 1 << 2;
		break;
	case 'q': // q - brake : 000 0111
		*(p + 2) |= 1 << 2;
		*(p + 2) |= 1 << 1;
		*(p + 2) |= 1;
		break;
	case 'l': // l - let off sounds 001 1110
		*(p + 2) |= 1 << 4;   
		*(p + 2) |= 1 << 3;  
		*(p + 2) |= 1 << 2;   
		*(p + 2) |= 1 << 1;  
		break;
	default: break;
	
	}

}

void print_usage() {
	
	char * msg = "Use the following commands to control the train: \n "
		  "1. HORN - to use the horn.\n "
		  "2. BELL - to ring the bell.\n "
		  "3. FORWARD - to go forward.\n "
		  "4. REVERSE - to go to the reverse direction.\n "
		  "5. FASTER - to go a bit faster.\n "
		  "6. SLOWER - to go a bit slower.\n "
		  "7. BRAKE - to use the brakes.\n "
		  "8. BOOST - to use a speed boost.\n "
		  "9. QUIET - to let off the sound.\n "
		  "10. TOGGLE - toggle direction.\n "
		  "Enter EXIT to quit.";
	fprintf(stdout, msg);
	
}
int main()
{
	fprintf(stdout,  "Welcome to Train Control System!\n ");
	print_usage();
    // Each command is in a three-byte command
	char bytes_to_send[3];



	// Declare variables and structures
	HANDLE hSerial;
	DCB dcbSerialParams = { 0 };
	COMMTIMEOUTS timeouts = { 0 };

	// Open the right serial port number, normally on this computer should be COM1
	fprintf(stderr, "Opening serial port...");

	hSerial = CreateFile(
		"\\\\.\\COM1", GENERIC_READ | GENERIC_WRITE, 0, NULL,
		OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hSerial == INVALID_HANDLE_VALUE)
	{
		fprintf(stderr, "Error\n");
		return 1;
	}
	else fprintf(stderr, "OK\n");


	// Set device parameters (9600 baud, 1 start bit,
	// 1 stop bit, no parity)
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
	
	char line[10] = ""; // contain the line to be read
	char cmd; // character to hold the command
	while (fgets(line, sizeof(line), stdin)  && strncmp(line, "EXIT", 4))
	{
		fprintf(stdout, line);
		if (!strncmp (line, "HORN", 4))
			cmd='h';
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
		else if (!strncmp(line, "QUIET", 5))
			cmd='l';
		else if (!strncmp(line, "TOGGLE", 6))
			cmd='t';
		else
		{
			fprintf(stdout, "Unsupported Command!\n");
			print_usage();
			continue;
		}
		
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
	fprintf(stderr, "Closing serial port...");
	if (CloseHandle(hSerial) == 0)
	{
		fprintf(stderr, "Error\n");
		return 1;
	}
	fprintf(stderr, "OK.\n");
	// exit normally

	return 0;
}
