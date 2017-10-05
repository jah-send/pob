//
// Copyright 2008 POB-Technology. All rights reserved.
// POB-Technology PROPRIETARY/CONFIDENTIAL.
//

/** \anchor pobbus
 * 
 * @brief POB-BUS function
 *
 * @file
 *
 * The dual-pob board has the default POB-Technology bus: the pob-bus.
 *
 * With this bus, you can send/receive data to/from pob-eye camera.
 *
 * @par Code example: init the pob-bus, receive and send data.
 *
 * @code

  UInt8 data;

  // Init pob-bus hardware
  InitPobBus();


  // Main loop program: simple ping-pong between pob-eye and dual-pob
  while(1)
  {
		// Get a data from pob-eye:
		data = GetByteFromPOBEYE();

		// ...and send data to pob-eye
		SendByteToPOBEYE(data);
  }


 * @endcode
 */
#ifndef DUAL_POB_BUS_H
#define DUAL_POB_BUS_H

/** @brief Init pob-bus hardware
 *
 */
extern void InitPobBus(void);

/** @brief Is a byte ready to get from POB-EYE?
 *
 * @return 1 if a byte is ready to get.
 */
extern UInt8 IsByteReadyFromPOBEYE(void);

/** @brief Get a byte from pob-eye
 *
 * @return a byte from pob-eye
 */
extern UInt8 GetByteFromPOBEYE(void);

/** @brief Send a byte to pob-eye
 *
 * @param data		Data to send
 */
extern void SetByteToPOBEYE(UInt8 data);


#endif


