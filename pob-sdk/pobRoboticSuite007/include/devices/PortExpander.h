//
// Copyright 2010 POB-Technology. All rights reserved.
//
/** \anchor portexpander
 *
 * @brief Port expander.
 *
 * @file
 *
 * Low level port expander hardware management.
 *
 *
 */
#ifndef RS007_DEVICE_PORTEXPANDER_H
#define RS007_DEVICE_PORTEXPANDER_H

#ifdef __cplusplus
extern "C" {
#endif

// public functions are in Sensor.h
// next functions are for private use in the pob-robotics-suite sdk.

// get i2c address and slot number from a port number:
extern void GetPortExpanderAddress(UInt8 port, UInt8 * i2c, UInt8 * slot);

// get i2c base address from a base slot:
extern UInt8 getBaseAddressOfPortExpander(UInt8 baseSlot);

extern UInt16 GetAnalogFromPortExpander(UInt8 addr, UInt8 slot);

extern UInt16 GetCfgFromPortExpander(UInt8 addr, UInt8 slot);

extern UInt8 GetDigitalIOFromPortExpander(UInt8 addr, UInt8 slot);

extern void SetDigitalIOFromPortExpander(UInt8 addr, UInt8 slot);

extern void ClearDigitalIOFromPortExpander(UInt8 addr, UInt8 slot);

extern void InitDigitalIOFromPortExpander(UInt8 addr, UInt8 slot, DIGITAL_WAY way);


#ifdef __cplusplus
 }
#endif

#endif
