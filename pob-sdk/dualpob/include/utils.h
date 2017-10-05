//
// Copyright 2008 POB-Technology. All rights reserved.
// POB-Technology PROPRIETARY/CONFIDENTIAL.
//

/** \anchor utils
 * 
 * @brief Utils functions
 *
 * @file
 *
 * Various utils functions.
 *
 * @par Convertion example
 *
 * @code
 *
	UInt8 buffer[2];
	UInt8 string[16];
	UInt32 string_len;
	
	UInt8 data8 = 123;

	Bin2Hex(data8,buffer);

	SendBufferToUART0(buffer,2);

	UInt32 data32 = 123456;

	string_len = Bin2Dec(data32,string);

	SendBufferToUART0(string,string_len);

 * @endcode
 *
 *
 */
#ifndef DUAL_POB_UTILS_H
#define DUAL_POB_UTILS_H


/** @brief Convert binary to decimal
 *
 * @param data				Data to convert
 * @param [out] result		Pointer to a char array. You must allocate char array!
 * @return Lenght of char array
 */
UInt32 Bin2Dec(Int32 data,char *result);

/** @brief Convert binary to hexadecimal
 *
 * @param data				Data to convert
 * @param [out] result		Pointer to a char array. You must allocate the char array!
 */
void Bin2Hex(UInt8 data,char *result);


/** @brief Send a string on UART0
 *
 * @param str				String to send (end of string with NULL character)
 */
void SendString(Int8 *str);


/** @name Get byte or 2-byte from a flash array
 *
 * You have to declare your array with prog_uint16_t or prog_uint8_t
 */
/*@{*/
/** @brief Get byte from flash
 *
 * @param arrray	Array address
 * @param i			Array index
 */
#define GetUInt8Flash(array,i)			pgm_read_byte(&array[i])

/** @brief Get 2-byte from flash
 *
 * @param arrray	Array address
 * @param i			Array index
 */
#define GetUInt16Flash(array,i)			pgm_read_word(&array[i])
/*@}*/


#endif
