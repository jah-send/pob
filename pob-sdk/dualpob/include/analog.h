//
// Copyright 2008 POB-Technology. All rights reserved.
// POB-Technology PROPRIETARY/CONFIDENTIAL.
//

/** \anchor analog
 *
 * @brief Analog to digital functions
 *
 * @file
 *
 * The DUAL-POB have 8 analog channel. Analog channels are on the PORTF pins.
 *
 *
 */
#ifndef DUAL_POB_ANALOG_H
#define DUAL_POB_ANALOG_H

/**
 * @brief Init dual-pob analog function.
 */ 
extern void InitAnalog(void);

/**
 * @brief Get a analog value from a channel.
 *
 * @param	channel		Analog channel between 0 and 7.
 * @return	Analog value
 */
extern UInt16 GetAnalog(UInt8 channel);




#endif
