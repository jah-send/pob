//
// Copyright 2008 POB-Technology. All rights reserved.
// POB-Technology PROPRIETARY/CONFIDENTIAL.
//

/** \anchor bioloid
 * 
 * @brief Robotis AX-12 functions
 *
 * @file
 *
 * You can connect on the DUAL-POB board robotis AX-12 servomotor. 
 * The robotis AX-12 servomotor is working with a serial bus and support easy daisy chain connection.
 *
 * @par Example code: use AX-12 servomotor.
 *
 * @code

	UInt16 positions[2];

	// Init the ax-12 serial bus.
	InitAx12Bus();

	// Send position to servo 1 and servo 2.
	SetAx12Position(1,500,130);
	SetAx12Position(2,500,130);

	// Move servomotors.
	MoveAx12();

	// Wait...
	Wait_Ms(1000);

	// Set position with an array of positions
	positions[0] = 0;
	positions[1] = 1;
	SetAx12Movement(positions,2,130);
	// or equivalent function: SetAx12MovementWithOffset(positions,0,2,130);

	// Move servomotors.
	MoveAx12();

 * @endcode
 *
 */
#ifndef POB_AX12_H
#define POB_AX12_H


/**
 * @name ax-12 protocol error code
 */
/*@{*/
#define AX12_ERR_TIMEOUT		-1	/**< timeout error */
#define AX12_ERR_WRONG_HEADER	-2	/**< wrong header error */
#define AX12_ERR_BAD_ID			-3	/**< bad id error */
#define AX12_ERR_WRONG_LEN		-4	/**< wrong len error */
#define AX12_ERR_CHECKSUM		-5	/**< checksum error */
/*@}*/


/** @brief Init AX-12 communication bus on uart1. 
 * 
 */
extern void InitAx12Bus(void);


/** @brief Ping a ax-12 servomotor.
 *
 * @param identifier	AX-12 servomotor
 * @return 1 if servomotor is find, else 0.
 */
extern Int8 PingAx12(UInt8 identifier);

/** @brief Set idenfitifer of an ax-12 servomotor.
 *
 * @warning BEFORE CALL THIS FUNCTION, MAKE SURE THERE IS ONLY ONE AX-12 SERVOMOTOR CONNECTED ON THE DUAL-POB!
 *
 * @param identifier	New AX-12 identifier
 */
extern void SetAx12Id(UInt8 identifier);

//extern void PingAll(void);


/** @brief Set movement of AX-12 servomotors
 *
 * The servomotor 1 to servonumber+1 will move at the specified position.
 *
 * @param position		Position array
 * @param servonumber   Length of position array
 * @param speed		    Speed of servomotor
 */
extern void SetAx12Movement(UInt16 *position,UInt8 servonumber,UInt16 speed);

/** @brief Set movement of AX-12 servomotors
 *
 * The servomotor servoOffset+1 to servonumber+1 will move at the specified position.
 *
 * @param position		Position array
 * @param servoOffset	First servomotor identifier
 * @param servonumber   Length of position array
 * @param speed		    Speed of servomotor
 */
extern void SetAx12MovementWithOffset(UInt16 *position,UInt8 servoOffset,UInt8 servonumber,UInt16 speed);

/** @brief Get position of current servomotor
 *
 * @param [in] identifier 	Servomotor id
 * @param [out] position 	Servomotor position
 * @return 0 if no error. else protocol error code
 */
extern Int8 GetAx12Position(UInt8 identifier, UInt16 *position);

/** @brief Prepare position and speed of a servomotor
 *
 * Position and speed are send to the servomotor but the servo don't move.
 *
 * @see Action to move your servomotor!
 *
 * @param identifier 	Servomotor id
 * @param position 		Servomotor position
 * @param speed			Servomotor speed
 * @return	0 if no error. else protocol error code
 */
extern Int8 SetAx12Position(UInt8 identifier, UInt16 position, UInt16 speed);

/** @brief Move all servomotor at the same time!
 *
 * Before move servomotor, you must set position and speed of the servomotor with the SetAx12Position() function.
 *
 * @see SetAx12Position
 */
extern void MoveAx12(void);


/** @brief Read a byte from AX-12 memory
 *
 * @param identifier 	AX-12 identifier
 * @param address		AX-12 memory address
 * @param [out] data	Data read. You must allocate the array!
 * @return 0 if no error.
 */
extern Int32 ReadByteFromAX12(UInt8 identifier, UInt8 address, UInt8 *data);



/**
 * @name low level bioloid communication functions. 
 *
 * @brief All this function come from bioloid cm-5 example (author: BS KIM from robotis)
 */
/*@{*/


/** @brief Set paramaters of packet.
 *
 * Set the packet parameters before call the TxPacket function
 *
 * @param index	 Parameter index in packet parameter buffer
 * @param data	 Data
 */
extern void SetTxParam(UInt8 index,UInt8 data);


//get parameters of packet
//extern UInt8 GetTxParam(int index);


/** @brief Get packet data
 *
 * Get last data receive from RxPacket function.
 *
 * @param index Index in receive buffer
 * @return Data
 */
extern UInt8 GetRxData(UInt8 index);


/** @brief send a packet to AX-12
 *
 * Send a packet to a AX-12 servomotor, with instruction and parameter's lenght.
 *
 * @param bId			 AX-12 identifier
 * @param bInstruction	 Instruction
 * @param bParameterLength Lenght of parameters
 *
 * @return Size of packet.
 */
extern UInt8 TxPacket(UInt8 bID, UInt8 bInstruction, UInt8 bParameterLength);


/** @brief receive a packet from AX-12
 *
 * @param bRxPacketLength Total lenght of return packet
 * @return Lenght of return packet or error code.
 */
extern Int32 RxPacket(UInt8 bRxPacketLength);
/*@}*/


#endif
