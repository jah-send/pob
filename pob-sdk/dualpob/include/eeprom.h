//
// Copyright 2008 POB-Technology. All rights reserved.
// POB-Technology PROPRIETARY/CONFIDENTIAL.
//

/** \anchor eeprom
 * 
 * @brief eeprom functions
 *
 * @file
 *
 * Read and Write data from DUAL-POB EEPROM memory. The DUAL-POB have 4K bytes of EEPROM.
 *
 *
 */
#ifndef DUAL_POB_EEPROM_H
#define DUAL_POB_EEPROM_H


/** @brief Write a data to eeprom memory
 * 
 * @param address	Data address
 * @param data		Data to write
 */
extern void eepromWrite(UInt16 address,UInt8 data);


/** @brief Read a data from eeprom memory
 * 
 * @param address	Address
 * @return Data read from eeprom
 */
extern UInt8 eepromRead(UInt16 address);


#endif
