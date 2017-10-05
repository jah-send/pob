//
// Copyright 2008 POB-Technology. All rights reserved.
// POB-Technology PROPRIETARY/CONFIDENTIAL.
//

/** 
 * @brief dual-pob library include
 *
 * @file
 *
 * This file must be included in your main code.
 *
 *
 *
 */
#ifndef POB_DUALPOB_H
#define POB_DUALPOB_H


#define DUALPOB_VERSION	1	/**< dualpob library version */


/**
 * @name Definition for C variables.
 *
 * You can use these definition in your own program.
 */
/*@{*/
#define UInt8	unsigned char	/**< An unsigned 8-bits */
#define UInt16	unsigned short	/**< An unsigned 16-bits */
#define UInt32	unsigned long	/**< An unsigned 32-bits */

#define Int8	char			/**< A signed 8-bits */
#define Int16	short			/**< A signed 16-bits */
#define Int32	long			/**< A signed 32-bits */
/*@}*/


/**
 * @name include section for the dual-pob library
 */
/*@{*/
#include "analog.h"		/**< analog functions */
#include "ax12.h"		/**< ax-12 servomotor functions */
#include "bluetooth.h"	/**< bluetooth communications */
#include "eeprom.h"		/**< eeprom memory functions */
#include "i2c.h"		/**< i2c bus management */
#include "io.h"			/**< input / output management */
#include "pob-bus.h"	/**< pob-bus management */
#include "servos.h"		/**< dual-pob servomotors functions */
#include "timer.h"		/**< wait and timer event */
#include "uart.h"		/**< uart communications */
#include "utils.h"		/**< utils functions */
/*@}*/



#endif




  
