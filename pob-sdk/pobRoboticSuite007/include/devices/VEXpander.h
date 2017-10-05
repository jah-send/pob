//
// Copyright 2010 POB-Technology. All rights reserved.
//
#ifdef English_dox
/** \anchor vexpander
 *
 * @brief VEX port expander.
 *
 * @file
 *
 * The VEXpander is a hardware compatible with all the VEX sensor.
 *
 */
#endif
#ifdef French_dox
/** \anchor vexpander
 *
 * @brief VEX port expander.
 *
 * @file
 *
 * The VEXpander is a hardware compatible with all the VEX sensor.
 *
 */
#endif
#ifndef RS007_DEVICE_PORTEXPANDER_H
#define RS007_DEVICE_PORTEXPANDER_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef English_dox
/** @brief
 *
 * @param port      Port where the VEXpander is connected (between 1 to 8).
 * @param slot
 */
#endif
extern UInt16 GetAnalogFromVEXpander(UInt8 port, UInt8 slot);

#ifdef English_dox
/** @brief
 *
 * @param port      Port where the VEXpander is connected (between 1 to 8).
 * @param slot
 * @param way
 */
#endif
extern void InitDigitalIOFromVEXpander(UInt8 port, UInt8 slot, DIGITAL_WAY way);

#ifdef English_dox
/** @brief
 *
 * @param port      Port where the VEXpander is connected (between 1 to 8).
 * @param slot
 */
#endif
extern UInt8 GetDigitalIOFromVEXpander(UInt8 port, UInt8 slot);

#ifdef English_dox
/** @brief
 *
 * @param port      Port where the VEXpander is connected (between 1 to 8).
 * @param slot
 */
#endif
extern void SetDigitalIOFromVEXpander(UInt8 port, UInt8 slot);


#ifdef English_dox
/** @brief
 *
 * @param port      Port where the VEXpander is connected (between 1 to 8).
 * @param slot
 */
#endif
extern void ClearDigitalIOFromVEXpander(UInt8 port, UInt8 slot);



/**
 * @name VEX Encoder.
 *
 * @brief Use the VEX Encoder sensor with the VEXpander.
 */
/*@{*/

#ifdef English_dox
/** @brief
 *
 * @param port      Port where the VEXpander is connected (between 1 to 8).
 * @param numencoder
 * @param port1
 * @param port2
 */
#endif
extern void InitEncoderFromVEXPander(UInt8 port, UInt8 numencoder, UInt8 port1, UInt8 port2);

#ifdef English_dox
/** @brief
 *
 * @param port      Port where the VEXpander is connected (between 1 to 8).
 * @param numencoder
 */
#endif
extern UInt8 GetEncoderPulseTimeFromVEXpander(UInt8 port, UInt8 numencoder);

/*@}*/

/**
 * @name VEX Ultrasonic.
 *
 * @brief Use the VEX Ultrasonic sensor with the VEXpander.
 */
/*@{*/

#ifdef English_dox
/** @brief
 *
 * @param port      Port where the VEXpander is connected (between 1 to 8).
 * @param numsensor
 * @param port_in
 * @param port_out
 */
#endif
extern void InitUltrasonicFromVEXPander(UInt8 port, UInt8 numsensor, UInt8 port_in, UInt8 port_out);

#ifdef English_dox
/** @brief
 *
 * @param port      Port where the VEXpander is connected (between 1 to 8).
 * @param numsensor
 */
#endif
extern void StartUltrasonicFromVEXpander(UInt8 port, UInt8 numsensor);

#ifdef English_dox
/** @brief
 *
 * @param port      Port where the VEXpander is connected (between 1 to 8).
 * @param numsensor
 */
#endif
extern UInt8 GetUltrasonicTimeFromVEXpander(UInt8 port, UInt8 numsensor);

/*@}*/

#ifdef __cplusplus
 }
#endif

#endif
