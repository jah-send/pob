/** 
 * @brief UART Communication.
 *
 * @file 
 *
 * UART communication functions.
 *
 * @author Pierre SEGUIN. POB-Technology
 *
 */
#ifndef UART_H
#define UART_H

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @name Define the baud rate
 */
/*@{*/
#define BR_230400       0x4000
#define BR_115200		0x1
#define BR_57600		0x2
#define BR_38400		0x4
#define BR_19200		0x8
#define BR_9600			0x10
#define BR_4800			0x8000
/*@}*/

/**
 * @name Define the bit lenght
 */
/*@{*/
#define LENGTH_5_BIT	0x20	
#define LENGTH_6_BIT	0x40
#define LENGTH_7_BIT	0x80
#define LENGTH_8_BIT	0x100	
/*@}*/


/**
 * @name Define the number of stop bit
 */
/*@{*/
#define ONE_STOP_BIT	0x200
#define TWO_STOP_BIT	0x400
/*@}*/

/**
 * @name Define the parity bits
 */
/*@{*/
#define NO_PARITY		0x800
#define ODD_PARITY		0x1000
#define EVEN_PARITY		0x2000
/*@}*/


/**
 * @brief Init the UART.
 *
 * @param Conf : Configuration word.
 */
extern void InitUART(UInt16 Conf);


/** 
 * @brief Send a byte with the UART.
 *
 * @param  Byte : the byte that will be sent
 */
extern void SendByteToUART(UInt8 Byte);


/** 
 * @brief Send a byte's array through the UART.
 *
 * @param  Buffer : Pointer on byte's array.
 * @param  Count  : Number of bytes to send.
 */
extern void SendBufferToUART(UInt8 * Buffer,UInt32 Count);


/** 
 * @brief Get a byte from the UART.
 *
 * @return The byte from the UART.
 */
extern UInt8 GetByteFromUART(void);


/**
 * @brief Get a byte from the UART, and do not wait for any data.
 *
 * @param[out] Data : Pointer on receiving data.
 * @return     1 if one byte is received, 0 if nothing is received.
 */
extern UInt8 GetByteFromUARTNoWait(UInt8 *Data);


/** 
 * @brief Get an array of bytes from the UART.
 *
 * @param[out] Buffer : pointer on array where the bytes are stored.
 * @param      Count  : Number of bytes expected.
 */
extern void GetBufferFromUART(UInt8 *Buffer,UInt32 Count);


/** 
 * @brief Print text on POB Terminal.
 *
 * @param format : This parameter is like the printf parameter.
 */
void PrintTextOnPobTerminal(const char *format, ...);


/** 
 * @brief Print video component on POB Terminal.
 *
 * @param Buffer : a video buffer that contains red or blue or green component.
 * @param ID     : ID of screen in POB Terminal
 */
void PrintComponentOnPobTerminal(UInt8 *Buffer,UInt8 ID);



/** Write a bitmap on the server
*
*	@param Path : Path of the file
*	@param Buffer : Buffer of the bitmap
*	@param Width : Width of the graphic buffer
*	@param Height :  Height of the graphic buffer
*	
* 
*/
//void WriteBmp(Int8 const *Path,UInt8 *Buffer,UInt8 Width,UInt8 Height);


/** WriteFile on the Server
*
* @param Path :		Path of file
* @param Buffer :	Buffer of the file that will be saved
* @param Size	:	Size of the file on the disk
*/
//void WriteFile(Int8 const *Path,UInt8 *Buffer,UInt16 Size);



/** Read a Bmp on the Server
*
* @param Path :		Path of file
* @param Buffer :	Buffer of the file that will be saved
*/
//UInt8 ReadBmp(Int8 *Path,UInt8 *Buffer);


/** Read a fast BMP on the Server (it only bee a 64 by 64 pixels picture, and a LCD graphic buffer)
*
* @param Path :		Path of file
* @param Buffer :	Buffer of the file that will be saved
*/
//UInt8 ReadFastBmp(Int8 *Path,UInt8 *Buffer);


/** Write a fast Bmp on the Server (it only bee a 64 by 64 pixels picture, and a LCD graphic buffer)
*
* @param Path :		Path of file
* @param Buffer :	Buffer of the file that will be saved
*/
//void WriteFastBmp (Int8 *Path,UInt8 *Buffer);


void InitUART1(UInt16 conf);
void SendByteToUART1(UInt8 byte);
void SendBufferToUART1(UInt8 * Buffer,UInt32 Count);
UInt8 GetByteFromUART1(void);
UInt8 GetByteFromUARTNoWait1(UInt8 *Data);
void GetBufferFromUART1(UInt8 *Buffer,UInt32 Count);

void InitUART0Intr(UInt32 baudrate);
UInt8 GetByteFromUART0Intr(UInt8 *Data);
void InitUART0(UInt32 baudrate);
void SetUART0Configuration(UInt32 Conf);

#ifdef __cplusplus
 }
#endif

#endif
