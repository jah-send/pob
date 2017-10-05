/** 
 * @brief General POBEYE include
 *
 * @file
 *
 * This file must be included in your main code.
 *
 * Only put in your code <i>#include <pob-eye.h></i> for use all the POB Library functions.
 *
 * @author Pierre SEGUIN. POB-Technology
 *
 */
#ifndef POBEYE_H
#define POBEYE_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name Definition for C variables.
 *
 * You can use these definition in your own program.
 */
/*@{*/
#define UInt8	unsigned char
#define UInt16	unsigned short
#define UInt32	unsigned long

#define Int8	char
#define Int16	short
#define Int32	long
/*@}*/


/**
 * @name General include for the POBEYE library.
 */
/*@{*/
#include "bluetooth.h"
#include "dual-pob.h"
#include "i2c.h"
#include "io-bus.h"
#include "uart.h"
#include "cam.h"
#include "graph.h"
#include "lcd.h"
#include "visio.h"
#include "pob-proto.h"
#include "robotsapien-order.h"
#include "servos.h"
#include "flash.h"
/*@}*/


#define POBEYE_VERSION_1	0x00
#define POBEYE_VERSION_2	0x01
#define POBEYE_VERSION_3	0x02

/**
 * @brief Init the POBEYE module
 * 
 * Init the I2C bus at 128 Kbits/s, camera and UART communication (38400 bauds, 8 data bit, 1 stop bit, and no parity).
 */
void InitPOBEYE(void);

void InitPOBEYE2(void);


void _InitPOBEYE_(void);

/**
 * Wait...
 *
 * @param time_in_microseconds : Time in microseconds to wait.
 */
void Wait(UInt32 time_in_microseconds);

/**
 * Start timer (set to zero the timer).
 */
void TimerStart(void);

/**
 * Stop timer and get current time.
 *
 * @return get current time in milliseconds.
 */
UInt32 TimerStop(void);


/**
 * Get current timer value. The timer must be start with TimerStart.
 *
 * @return get current time.
 */
UInt32 TimerGet(void);

#ifdef __cplusplus
 }
#endif

#endif




  
