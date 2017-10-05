//
// Copyright 2010 POB-Technology. All rights reserved.
//
#ifndef SLAVE_UC_MODULES_H
#define SLAVE_UC_MODULES_H

#ifdef English_dox
/** @brief Slave communication.

 @file

 This module manages the slave communication on the port 1 to 8 of the POB-Robotics-Suite.

 @warning If you don't develop a new slave device for the Pob-Robotics-Suite, forget all this code.

*/

/** @brief Memory module structure.
 */
#endif
#ifdef French_dox
/** @brief Slave communication.

 @file

 This module manages the slave communication on the port 1 to 8 of the POB-Robotics-Suite.

 @warning If you don't develop a new slave device for the Pob-Robotics-Suite, forget all this code.

 */

/** @brief Memory module structure.
 */
#endif
typedef struct _mem_modules_
{
	UInt16		id;		    /**< Module identifier. */
	UInt16      size;	    /**< Size of memory. */
	UInt8 *		ptr;	    /**< Pointer to memory. */
	void (*update)(void);   /**< Code for update memory. */
} MemoryModule;

#ifdef English_dox
/** @brief Get memory module pointer from an address.
 *
 * @param address   Address.
 * @return A pointer to the memory module or 0 if no memory found.
 */
#endif
#ifdef French_dox
/** @brief Get memory module pointer from an address.
 *
 * @param address   Address.
 * @return A pointer to the memory module or 0 if no memory found.
 */
#endif
extern MemoryModule * GetSlaveModulesMemory(UInt16 address);

#ifdef English_dox
/** @brief Get memory module address.
 */
#endif
#ifdef French_dox
/** @brief Get memory module address.
 */
#endif
extern UInt16 GetSlaveModAddr(void);

#ifdef English_dox
/** @brief Get the memory modules from an address.
 */
#endif
#ifdef French_dox
/** @brief Get the memory modules from an address.
 */
#endif
extern MemoryModule * GetSlaveModulesMemory(UInt16 address);

#ifdef English_dox
/** @brief Init the slave.
 */
#endif
#ifdef French_dox
/** @brief Init the slave.
 */
#endif
extern UInt8 I2CSlaveInit(SensorType mtype);

#ifdef English_dox
/** @brief Run slave communication.
 */
#ifdef French_dox
#endif
/** @brief Run slave communication.
 */
#endif
extern void RunSlaveComm(UInt8 *buffer, UInt8 size);

#endif
