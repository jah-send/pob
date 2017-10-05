//
// Copyright 2008 POB-Technology. All rights reserved.
// POB-Technology PROPRIETARY/CONFIDENTIAL.
//

/** \anchor uart
 * 
 * @brief UART communication function
 *
 * @file
 *
 * The DUAL-POB have 2 UART: UART0 and UART1. UART0 is on usb connector and bluetooth connector. 
 * You can't use at the same time bluetooth and usb connector!
 *
 * UART1 is currently used for robotis servomotor communications.
 * 
 *
 *
 */
#ifndef DUAL_POB_UART_H
#define DUAL_POB_UART_H


/**
 * @name uart0 functions
 *
 * @brief communication functions on UART0
 */
/*@{*/

/** @brief Init UART0
 *
 * Baudrate for DUAL-POB between 9600 and 230400.
 *
 * @param baudrate	 UART Baudrate
 */

extern void InitUART0(UInt32 baudrate);

/** @brief Send a byte to UART0
 *
 * @param Byte	 Byte to send
 */
extern void SendByteToUART0(UInt8 Byte);

/** @brief Send a buffer to UART0
 *
 * @param Buffer	 Buffer to send
 * @param Count		 Number of byte to send
 */
extern void SendBufferToUART0 (UInt8 *Buffer, UInt32 Count);

/** @brief Read a byte from UART0
 * 
 * @return Byte read
 */
extern UInt8 GetByteFromUART0 (void);

/** @brief Read a byte from UART0, do not wait a data.
 *
 * @param [out] Data	 Pointer to a byte
 * @return 0 if no data read, else 1 (and Data contains the byte read).
 */
extern UInt8 GetByteFromUART0NoWait (UInt8 *Data);

/** @brief Read a buffer from UART0
 * 
 * @param [out] Buffer	 Pointer to a buffer. You must allocate the buffer!
 * @param Count				 Number of byte to read from UART0
 */
extern void GetBufferFromUART0 (UInt8 *Buffer, UInt32 Count);

/*@}*/

/**
 * @name uart1 functions
 *
 * @brief communication functions on UART1
 */
/*@{*/
extern void InitUART1(UInt32 baudrate);
extern void SendByteToUART1 (UInt8 Byte);
extern void SendBufferToUART1 (UInt8 *Buffer, UInt32 Count);
extern UInt8 GetByteFromUART1 (void);
extern UInt8 GetByteFromUART1NoWait (UInt8 *Data);
extern void GetBufferFromUART1 (UInt8 *Buffer, UInt32 Count);
/*@}*/

#endif
