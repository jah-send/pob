//
// Copyright 2009 POB-Technology. All rights reserved.
// POB-Technology PROPRIETARY/CONFIDENTIAL.
//

/** \anchor iobus
 *
 * @brief I/O Functions
 *
 * @file
 *
 * Function to manage the Input/Output and the bus of POB-EYE2:
 * The POBEYE2 as 12 input/output digital pins free for use, named G0 to G11.
 *
 * @par Example code: configure input/output pins
 *
 * @code

 #include <pob-eye.h>

 int main(void)
 {
	InitPobeye2();

	// configure G0 as output pins 
	SetIOWay(0x1);

	while(1)
	{
		// set to 0 the G0 pin
		ClrOutput(0x1);
		WaitMs(1);
		// set to 1 the G0 pin 
		SetOutput(0x1);
		WaitMs(1);
	}

	return 0;
 }

 * @endcode
 *
 */
#ifndef IO_BUS_H
#define IO_BUS_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name POB-EYE2 input/output digital functions
 * 
 */
/*@{*/

/** 
 * @brief Set the way (input or output) of the I/O.
 *
 * @param config	Value of the I/O. Put 1 to set as an output, 0 for an input
 */
extern void SetIOWay(UInt32 config);


/** 
 * @brief Get the value of the Input pins.
 * 
 * @return UInt16	Value of the Input
 */
extern UInt16 GetInput(void);


/** 
 * @brief Set the value of output pins.
 *
 * @param  Value	Value to set. use 1 to set an output, 0 no effect on the output.
 */
extern void SetOutput(UInt32 Value);


/** 
 * @brief Clear the output pins.
 *
 * @param  Value use 1 to clear an output, 0 no effect on the output.
 */
extern void ClrOutput(UInt32 Value);


/**
 * @brief set and clear output.
 *
 * @param Value : a 1 set the output and 0 clear an output.
 */
extern void ClrAndSetOuput( UInt32 Value);

/*@}*/

/**
 * @name POB-BUS functions
 *
 * 
 */
/*@{*/

/** @brief Send a Byte to a device on the POB-BUS.
 *
 * @param  Addr : address of the device
 * @param  Data : data send to the device
 */
extern void WriteByte(UInt16 Addr,UInt8 Data);


/** @brief Read a byte from a device on the POB-BUS.
 *
 * @param  Addr : address of the device
 * @return unsigned char : the read byte
 */
extern UInt8 ReadByte(UInt16 Addr);
/*@}*/

#ifdef __cplusplus
 }
#endif

#endif

