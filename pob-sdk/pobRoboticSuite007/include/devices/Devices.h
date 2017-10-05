//
// Copyright 2010 POB-Technology. All rights reserved.
//
/** \anchor sensor_private
 *

 */
#ifndef RS007_DEVICE_H
#define RS007_DEVICE_H

#ifdef __cplusplus
extern "C" {
#endif

#include "device_Camera.h"
#include "Device_GP2D12.h"
#include "Device_LinesensorSharp.h"
#include "Device_RGBLed.h"
#include "PortExpander.h"
#include "Devices_MiniVEX.h"
#include "Device_IRFollower.h"

// public functions are in Sensor.h
// next functions are for private use in the pob-robotics-suite sdk.

extern SensorType GetDeviceTypeFromCfgValue(UInt16 analogvalue);

extern UInt8 GetI2cAddressOfPort(UInt8 port);

extern void SendToPobDevice(UInt32 port, UInt32 deviceAddr, UInt8 * buffer, UInt32 size);

extern void SendAndRcvToPobDevice(UInt32 port, UInt32 deviceAddr, UInt8 * buffer, UInt32 size, UInt32 request);

#ifdef __cplusplus
 }
#endif

#endif
