/** 
 * @brief I/O Functions
 *
 * @file
 *
 * Function to manage the Input/Output and the bus of POB-EYE.
 *
 * @author Pierre SEGUIN. POB-Technology
 *
 */
#ifndef IO_BUS_H
#define IO_BUS_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @name pob-eye input/output management functions
 *
 * 
 */
/*@{*/

/** 
 * @brief Set the way of the general purpose I/O.
 *
 * @param  Value : Value of the I/O. Put 1 to set as an output, 0 for an input
 */
extern void SetIOWay(UInt32 Value);


/** 
 * @brief Get the value of the Input
 * 
 * @return UInt16 Value of the Input
 */
extern UInt16 GetInput(void);


/** 
 * @brief Set the value of an Output.
 *
 * @param  Value : Value to set. use 1 to set an output, 0 no effect on the output.
 */
extern void SetOutput(UInt32 Value);


/** 
 * @brief Clear the output.
 *
 * @param  Value : use 1 to clear an output, 0 no effect on the output.
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

