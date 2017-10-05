//
// Copyright 2010 POB-Technology. All rights reserved.
//

#ifndef RS007_DEVICE_LINESENSORSHARP_H
#define RS007_DEVICE_LINESENSORSHARP_H

#ifdef __cplusplus
extern "C" {
#endif

// public functions are in Sensor.h
// next functions are for private use in the pob-robotics-suite sdk.


/** @brief Get distance from the Line follower module.
 *
 * @param port      Port where line follower is connected (from 1 to 8).
 * @return A distance in millimeter.
 */
extern UInt32 GetDistanceFromLineFollower(UInt8 port);


#ifdef __cplusplus
 }
#endif

#endif
