//
// Copyright 2009 POB-Technology. All rights reserved.
// POB-Technology PROPRIETARY/CONFIDENTIAL.
//

/** \anchor utils
 *
 * @brief Utils functions
 *
 * @file 
 *
 * Set or clear green led, Convert data to hexadecimal or decimal string, wait some times...
 *
 */
#ifndef POB_UTILS_H
#define POB_UTILS_H

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Set green led to on.
 */
extern void SetLed(void);

/** @brief Clear green led.
 */
extern void ClearLed(void);

/** @brief Send a string on UART0
 *
 * @param str				String to send (end of string with NULL character)
 */
extern void SendString(Int8 *str);

/** @brief Convert binary to decimal
 *
 * @param data				Data to convert
 * @param [out] result		Pointer to a char array. You must allocate char array!
 * @return Lenght of char array
 */
extern UInt32 Bin2Dec(Int32 data,char *result);

/** @brief Convert a binary byte to hexadecimal
 *
 * @param data				Data to convert
 * @param [out] result		Pointer to a char array. You must allocate the char array!
 */
extern void Bin2Hex(UInt8 data,char *result);

/** @brief Wait (a multiple of 1ms)...
 *
 * @param delay_ms		Delay in milliseconds.
 */
extern void WaitMs(UInt32 delay_ms);


/** @brief Like printf function...
 *
 */
extern int PrintToUart0(const char *format, ...);

/** 
 * @brief Print text on POB Terminal.
 *
 * @param format		This parameter is like the printf parameter.
 */
void PrintTextOnPobTerminal(const char *format, ...);

/** @brief Like sprintf function...
 */
extern int PrintToABuffer(char *out, const char *format, ...);


#ifdef __cplusplus
 }
#endif

#endif
