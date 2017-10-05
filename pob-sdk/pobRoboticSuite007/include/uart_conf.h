//
// Copyright 2010 POB-Technology. All rights reserved.
//
#ifdef English_dox
/** \anchor uart_conf
 *
 * @brief UART Configuration Flag.
 *
 * @file
 *
 */
#endif
#ifdef French_dox
/** \anchor uart_conf
 *
 * @brief Configuration bas niveau UART.
 *
 * @file
 *
 */
#endif
#ifndef RS007_UART_CONF_H
#define RS007_UART_CONF_H

#ifdef __cplusplus
extern "C" {
#endif

#define EVENT_INTR_UART0    0x01
#define EVENT_INTR_UART1    0x02

#ifdef English_dox
/**
 * @name Low level UART configuration.
 *
 * @brief Use only the next parameters if you want configure the UART.
 */
/*@{*/
#endif
#ifdef French_dox
/**
 * @name Configuration bas niveau du port série.
 *
 * @brief Utiliser les fonctions de ce fichier uniquement si vous souhaitez configurer les différents paramètres du port série : parité, bit de stop...
 */
/*@{*/
#endif

#define BR_230400    0x4000	/**< use a 230400 baudrate */
#define BR_115200	0x1		/**< use a 115200 baudrate */
#define BR_57600		0x2		/**< use a 57600 baudrate */
#define BR_38400		0x4		/**< use a 38400 baudrate */
#define BR_19200	    0x8		/**< use a 19200 baudrate */
#define BR_9600     0x10	    /**< use a 9600 baudrate */
#define BR_4800     0x8000	/**< use a 4800 baudrate */
#define BR_1200     0x10000	/**< use a 1200 baudrate */

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
