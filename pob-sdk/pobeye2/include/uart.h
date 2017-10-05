//
// Copyright 2010 POB-Technology. All rights reserved.
//

/** \anchor uart
 *
 * @brief UART Communication.
 *
 * @file
 *
 * The UART bus interface is a slow serial bus.
 *
 * The POB-EYE2 comes with 2 UARTs interface, named UART0 and UART1:
 * - UART0 is connected on the USB.
 * - UART1 is free for use (used by default for the ZigBee/Wifi option).
 *
 * @par Use the UART0 Interrupt
 *
 * @code

#include <pob-eye.h>

int main(void)
{
    UInt8 value;

    InitPobeye2();

    // Init the uart 0 and use the hardware interrupt routine:
    InitUART0Intr(115200);

    while(1)
    {
        if( GetByteFromUART0Intr(&value) == 1 )
        {
            // If a data is receveid from uart 0, then...

            // Send the received byte...
            SendByteToUART0(value);

        }
    }

    return 0;
}

 * @endcode
 */
#ifndef POBEYE2_UART_H
#define POBEYE2_UART_H

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @name UART0 functions
 *
 * @brief Communicate on UART0.
 */
/*@{*/

/**
 * @brief Init UART0 (USB).
 *
 * @param baudrate		UART0 baudrate.
 */
extern void InitUART0(UInt32 baudrate);

/** @brief Init UART0 (USB) with an interrupt on reception.
 *
 * The UART0 reception use an hardware interrupt:
 * No byte is lost during reception and you don't have to poll the UART.
 *
 * @param baudrate      UART0 baudrate.
 */
extern void InitUART0Intr(UInt32 baudrate);

/**
 * @brief Send a byte to the UART0.
 *
 * @param  byte			the byte that will be sent
 */
extern void SendByteToUART0(UInt8 byte);

/**
 * @brief Send a byte's array through the UART0.
 *
 * @param  Buffer		Pointer on byte's array.
 * @param  Count		Number of bytes to send.
 */
extern void SendBufferToUART0(UInt8 * Buffer,UInt32 Count);


/**
 * @brief Get a byte from the UART0.
 *
 * Don't use this function if you are using the UART Interrupt!
 *
 * @return The byte from the UART.
 */
extern UInt8 GetByteFromUART0(void);

/** @brief Get a byte from the UART0 Interrupt Buffer.
 *
 * @param[out] Data  Pointer to a byte where store the byte received.
 * @return 1 if one byte is received, 0 if nothing is received.
 */
extern UInt8 GetByteFromUART0Intr(UInt8 *Data);

/**
 * @brief Get a byte from the UART0, and do not wait for any data.
 *
 * Don't use this function if you are using the UART0 Interrupt!
 *
 * @param[out] Data		Pointer to a byte where store the byte received.
 * @return     1 if one byte is received, 0 if nothing is received.
 */
extern UInt8 GetByteFromUART0NoWait(UInt8 *Data);


/**
 * @brief Get an array of bytes from the UART0.
 *
 * @param[out] Buffer		Pointer on array where the bytes are stored.
 * @param      Count		Number of bytes expected.
 */
extern void GetBufferFromUART0(UInt8 *Buffer,UInt32 Count);


/*@}*/


/**
 * @name UART1 functions
 *
 * @brief Communicates on UART1.
 */
/*@{*/

/**
 * @brief Init UART1.
 *
 * @param baudrate		UART1 baudrate.
 */
extern void InitUART1(UInt32 baudrate);

/** @brief Init UART1 with an interrupt on reception.
 *
 * The UART1 reception use an hardware interrupt:
 * No byte is lost during reception and you don't have to poll the UART.
 *
 * @param baudrate      UART1 baudrate.
 */
extern void InitUART1Intr(UInt32 baudrate);

/**
 * @brief Send a byte to the UART1.
 *
 * @param  byte			the byte that will be sent
 */
extern void SendByteToUART1(UInt8 byte);

/**
 * @brief Send a byte's array through the UART1.
 *
 * @param  Buffer		Pointer on byte's array.
 * @param  Count		Number of bytes to send.
 */
extern void SendBufferToUART1(UInt8 * Buffer,UInt32 Count);

/**
 * @brief Get a byte from the UART1.
 *
 * Don't use this function if you are using the UART Interrupt!
 *
 * @return The byte from the UART.
 */
extern UInt8 GetByteFromUART1(void);

/** @brief Get a byte from the UART1 Interrupt Buffer.
 *
 * @param[out] Data  Pointer to a byte where store the byte received.
 * @return 1 if one byte is received, 0 if nothing is received.
 */
extern UInt8 GetByteFromUART1Intr(UInt8 *Data);

/**
 * @brief Get a byte from the UART1, and do not wait for any data.
 *
 * Don't use this function if you are using the UART1 Interrupt!
 *
 * @param[out] Data		Pointer to a byte where store the byte received.
 * @return     1 if one byte is received, 0 if nothing is received.
 */
extern UInt8 GetByteFromUART1NoWait(UInt8 *Data);

/**
 * @brief Get an array of bytes from the UART1.
 *
 * @param[out] Buffer		Pointer on array where the bytes are stored.
 * @param      Count		Number of bytes expected.
 */
extern void GetBufferFromUART1(UInt8 *Buffer,UInt32 Count);
/*@}*/


/**
 * @name Low level UART configuration.
 *
 * @brief Use only the next parameters if you want configure the UART.
 */
/*@{*/

#define BR_230400       0x4000	/**< use a 230400 baudrate */
#define BR_115200		0x1		/**< use a 115200 baudrate */
#define BR_57600		0x2		/**< use a 57600 baudrate */
#define BR_38400		0x4		/**< use a 38400 baudrate */
#define BR_19200		0x8		/**< use a 19200 baudrate */
#define BR_9600			0x10	/**< use a 9600 baudrate */
#define BR_4800			0x8000	/**< use a 4800 baudrate */
#define BR_1200         0x10000	/**< use a 1200 baudrate */

#define LENGTH_5_BIT	0x20
#define LENGTH_6_BIT	0x40
#define LENGTH_7_BIT	0x80
#define LENGTH_8_BIT	0x100

#define ONE_STOP_BIT	0x200
#define TWO_STOP_BIT	0x400

#define NO_PARITY		0x800
#define ODD_PARITY		0x1000
#define EVEN_PARITY		0x2000

extern void SetUART0Configuration(UInt32 Conf);

extern void SetUART1Configuration(UInt32 Conf);
/*@}*/


#ifdef __cplusplus
 }
#endif

#endif
