//
// Copyright 2010 POB-Technology. All rights reserved.
//
#ifdef English_dox
/**
 * @brief General POB-Robotics-Suite include
 *
 * @file
 *
 * This file must be included in your main code.
 *
 * Only put in your code <i>#include <pobRoboticSuite.h></i> for use all the functionnality of the Robot.
 *
 *
 */
#endif
#ifdef French_dox
/**
 * @brief Fichier En tête principale du POB-Robotics-Suite
 *
 * @file
 *
 * Ce fichier doit être inclut dans votre code pour utilier toutes les fonctions du robot.
 *
 * Placer simplement dans votre code : <i>#include <pobRoboticSuite.h></i> pour utiliser le robot.
 *
 *
 */
#endif
#ifndef RS007_MAIN_H
#define RS007_MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

#define RS_HARDWARE_0		1

#ifdef English_dox
/**
 * @name Definition for C variables.
 *
 * You can use these definition in your own program.
 */
/*@{*/
#endif
#ifdef French_dox
/**
 * @name Définitions pour les variables du langage C.
 *
 * Vous pouvez utiliser celle-ci dans votre programme.
 */
/*@{*/
#endif
#define UInt8	unsigned char
#define UInt16	unsigned short
#define UInt32	unsigned int

#define Int8	char
#define Int16	short
#define Int32	int
/*@}*/

#ifdef English_dox
/**
 * @name General include for the POB-Robotics-Suite library.
 */
/*@{*/
#endif
#ifdef French_dox
/**
 * @name Fichier en tête de la librairie POB-Robotics-Suite.
 */
/*@{*/
#endif
#include "lpc210x-config.h"
#include "lpc210x.h"
#include "McuIO.h"
#include "io.h"
#include "devices/Sensor.h"
#include "devices/Devices.h"
#include "analog.h"
#include "i2c.h"
#include "interrupt.h"
#include "timer.h"
#include "uart_conf.h"
#include "uart.h"
#include "Motion.h"
#include "utils.h"
#include "eeprom.h"
#include "WatchDog.h"
#include "lcd.h"
#include "zigbee.h"
#include "wifi.h"
/*@}*/

#ifdef English_dox
/** @brief Initialize the microcontroller of the POB-Robotics-Suite.
 *
 */
#endif
#ifdef French_dox
/** @brief Initialiser le microcontrôleur du POB-Robotics-Suite.
 *
 */
#endif
extern void InitCpu(void);



#ifdef __cplusplus
 }
#endif

#endif





