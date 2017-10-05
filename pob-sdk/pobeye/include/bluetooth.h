//
// Copyright 2008 POB-Technology. All rights reserved.
// POB-Technology PROPRIETARY/CONFIDENTIAL.
//

/** 
 * @brief Bluetooth include
 *
 * @file
 *
 * Initialization of the POB-TOOTH module on the pob-eye. 
 *
 * The bluetooth communication use the UART: 
 * to send and receive data from other bluetooth device, you must use the uart functions
 *
 * @see uart.h
 *
 *
 */
#ifndef POB_BLUETOOTH_H
#define POB_BLUETOOTH_H

#ifdef __cplusplus
extern "C" {
#endif

/** @name bluetooth error code
 *
 */
/*@{*/
#define BLUETOOTH_OK				0	/**< no error */
#define BLUETOOTH_WRONG_BAUDRATE	1	/**< wrong baudrate selected */
#define BLUETOOTH_FAILED			2	/**< initialization of bluetooth failed */
/*@}*/

/** @brief Init bluetooth module at the specified baudrate.
 *
 * @param bluetooth_baudrate	Baudrate
 * @param bluetooth_name		Name of the device on the bluetooth network. If NULL, default name is use (POBTOOTH)
 * @return 0 if success, else error code
 */
extern UInt8 InitBluetooth(UInt32 bluetooth_baudrate,UInt8 *bluetooth_name);

#ifdef __cplusplus
 }
#endif

#endif


