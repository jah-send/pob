//
// Copyright 2008 POB-Technology. All rights reserved.
// POB-Technology PROPRIETARY/CONFIDENTIAL.
//

/** \anchor bluetooth
 * 
 * @brief Bluetooth include
 *
 * @file
 *
 * Initialization of the bluetooth module on the dual-pob board. 
 *
 * The bluetooth communication use the UART0: 
 * to send and receive data from other bluetooth device, you must use the uart functions
 *
 * @see uart.h
 *
 * @warning
 *
 * 2009.02.11: Currently the bluetooth module must be set by a 4-step procedure:
 *  - (1) call InitBluetooth(...) function, compile and upload.
 *  - (2) execute the program with bluetooth link selected.
 *  - (3) remove InitBluetooth and replace it by InitUART0(...), compile and upload.
 *  - (4) execute the program with bluetooth link selected: the bluetooth module is working!
 *
 */
#ifndef DUAL_POB_BLUETOOTH_H
#define DUAL_POB_BLUETOOTH_H

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
 * @param bluetooth_baudrate	Serial baudrate
 * @param bluetooth_name		Name of the device on the bluetooth network
 * @return 0 if success, else error code
 */
extern UInt8 InitBluetooth(UInt32 bluetooth_baudrate,UInt8 *bluetooth_name);


#endif


