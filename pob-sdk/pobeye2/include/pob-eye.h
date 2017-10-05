//
// Copyright 2009 POB-Technology. All rights reserved.
// POB-Technology PROPRIETARY/CONFIDENTIAL.
//

/** 
 * @brief General POBEYE include
 *
 * @file
 *
 * This file must be included in your main code.
 *
 * Put in your code <i>#include <pob-eye.h></i> for use all the POB-EYE2 Library functions.
 *
 *
 */
#ifndef POBEYE2_H
#define POBEYE2_H

#ifdef __cplusplus
extern "C" {
#endif

#define POBEYE2_HARDWARE 1	/**< Define POBEYE2 Hardware */

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
/*#include "bluetooth.h"*/
#include "dual-pob.h"
#include "i2c.h"
#include "io-bus.h"
#include "uart.h"
#include "utils.h"
#include "camera.h"
#include "visio.h"
#include "interrupt.h"
#include "timer.h"
#include "flash.h"
#include "pob-proto.h"
#include "graph.h"
#include "lcd.h"
#include "servos.h"
	/*
#include "robotsapien-order.h"
*/
/*@}*/

/** @brief Init pobeye2 cpu.
 *
 */
extern void InitPobeye2(void);


#ifdef __cplusplus
 }
#endif

#endif




  
