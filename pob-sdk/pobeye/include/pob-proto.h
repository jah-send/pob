/** 
 * @brief Function for communication with the pob-proto board.
 *
 * @file 
 *
 * <br>The pob-proto board has PORTA, PORTC and PORTD.<br>
 * -# PORTA can be set as input/ouput or as analogic port.
 * -# PORTC can be drive servomotor.
 *
 * <br><br> Before use function of this file you must init the pob-proto port with this function :
 *  -# SetPobProto() if you use the POB-PROTO.
 *  -# SetTinyPobProto()  if you have the <b>tiny POB-PROTO</b>.
 *
 * @author Pierre SEGUIN & Baptiste BURLES. POB-Technology
 *
 */
#ifndef pob_proto_h
#define pob_proto_h

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @name Defines for the PORTA
 *
 *  xxx_AS_DI --> digital input
 *  <br>xxx_AS_DO --> digital output
 */
/*@{*/
#define RA0_AS_DI	0x01  /**< set pin 0 PORTA as digital input */
#define RA1_AS_DI	0x02  /**< set pin 1 PORTA as digital input */
#define RA2_AS_DI	0x04  /**< set pin 2 PORTA as digital input */
#define RA3_AS_DI	0x08  /**< set pin 3 PORTA as digital input */
#define RA4_AS_DI	0x10  /**< set pin 4 PORTA as digital input */
#define RA5_AS_DI	0x20  /**< set pin 5 PORTA as digital input */

#define RA0_AS_DO	0     /**< set pin 0 PORTA as digital output */
#define RA1_AS_DO	0     /**< set pin 1 PORTA as digital output */
#define RA2_AS_DO	0     /**< set pin 2 PORTA as digital output */
#define RA3_AS_DO	0     /**< set pin 3 PORTA as digital output */
#define RA4_AS_DO	0     /**< set pin 4 PORTA as digital output */
#define RA5_AS_DO	0     /**< set pin 5 PORTA as digital output */

#define ALL_PORTA_AS_ANA	0x0100 /**< set PORTA as analogic */
/*@}*/


/**
 * @name defines for the PORTD
 *
 *  xxx_AS_DI --> digital input
 *  <br>xxx_AS_DO --> digital output
 */
/*@{*/
#define RD0_AS_DI	0x01  /**< set pin 0 PORTD as digital input */
#define RD1_AS_DI	0x02  /**< set pin 1 PORTD as digital input */
#define RD2_AS_DI	0x04  /**< set pin 2 PORTD as digital input */
#define RD3_AS_DI	0x08  /**< set pin 3 PORTD as digital input */
#define RD4_AS_DI	0x10  /**< set pin 4 PORTD as digital input */
#define RD5_AS_DI	0x20  /**< set pin 5 PORTD as digital input */
#define RD6_AS_DI	0x40  /**< set pin 6 PORTD as digital input */
#define RD7_AS_DI	0x80  /**< set pin 7 PORTD as digital input */


#define RD0_AS_DO	0     /**< set pin 0 PORTD as digital output */
#define RD1_AS_DO	0     /**< set pin 1 PORTD as digital output */
#define RD2_AS_DO	0     /**< set pin 2 PORTD as digital output */
#define RD3_AS_DO	0     /**< set pin 3 PORTD as digital output */
#define RD4_AS_DO	0     /**< set pin 4 PORTD as digital output */
#define RD5_AS_DO	0     /**< set pin 5 PORTD as digital output */
#define RD6_AS_DO	0     /**< set pin 6 PORTD as digital output */
#define RD7_AS_DO	0     /**< set pin 7 PORTD as digital output */
/*@}*/


/**
 * @name Defines for the PORTC
 *
 *  xxx_AS_DI --> digital input
 *  <br>xxx_AS_DO --> digital output
 *  <br>xxx_AS_SERVO --> servomotor on that pin
 */
/*@{*/
#define RC0_AS_DI	0x01  /**< set pin 0 PORTC as digital input */
#define RC1_AS_DI	0x02  /**< set pin 1 PORTC as digital input */
#define RC2_AS_DI	0x04  /**< set pin 2 PORTC as digital input */
#define RC3_AS_DI	0x08  /**< set pin 3 PORTC as digital input */
#define RC6_AS_DI	0x40  /**< set pin 6 PORTC as digital input */
#define RC7_AS_DI	0x80  /**< set pin 7 PORTC as digital input */

#define RC0_AS_DO	0x00  /**< set pin 0 PORTC as digital output */
#define RC1_AS_DO	0x00  /**< set pin 1 PORTC as digital output */
#define RC2_AS_DO	0x00  /**< set pin 2 PORTC as digital output */
#define RC3_AS_DO	0x00  /**< set pin 3 PORTC as digital output */
#define RC6_AS_DO	0x00  /**< set pin 6 PORTC as digital output */
#define RC7_AS_DO	0x00  /**< set pin 7 PORTC as digital output */

#define RC0_AS_SERVO 0x0100 /**< set pin 0 PORTC as a servomotor */
#define RC1_AS_SERVO 0x0200 /**< set pin 1 PORTC as a servomotor */
#define RC2_AS_SERVO 0x0400 /**< set pin 2 PORTC as a servomotor */
#define RC3_AS_SERVO 0x0800 /**< set pin 3 PORTC as a servomotor */
#define RC6_AS_SERVO 0x1000 /**< set pin 6 PORTC as a servomotor */
#define RC7_AS_SERVO 0x2000 /**< set pin 7 PORTC as a servomotor */
/*@}*/


/** 
 * @brief Pob-proto port board structure configuration.
 */
typedef struct _pobproto
{
	UInt16	porta; /**< PORTA configuration */
	UInt16	portc; /**< PORTC configuration */
	UInt8	portd; /**< PORTD configuration */
}PobProto;


/**
 * @brief Write the current configuration of the port on the pob-proto board.
 * 
 * PORTA pin 0 to 5. PORTC pin 0 to 3 and 6 to 7 and PORTD pin 0 to 7.
 *
 * @warning PORTA can be set as input/output or as analogic but not as analogic/input/ouput. pin 4 and 5 of PORTC are reserved.
 *
 * @warning if you set PORTA as analogic, pin 4 can't be used as analogic ! On the POB-PROTO board, you have only pin 0,1,2,3,5 as analogic.
 * 
 *
 * @param Proto : Configuration port.
 */
extern void SetPobProto(PobProto *Proto);

/**
 * @brief Write the current configuration on the Tiny pob-proto board.
 *
 * @see SetPobProto()
 *
 * @warning This function init the <b>TINY POB-PROTO BOARD</b> ! <i>do not use if you don't have the tiny board</i>.
 *
 * @param Proto : Configuration port.
 */
extern void SetTinyPobProto(PobProto *Proto);

/**
 * @brief Get value of PORTA
 *
 * @return the byte value of PORTA
 */
extern UInt8 GetPortA (void);

/**
 * @brief Get value of PORTA's pin
 *
 * @param pin : the pin to get value.
 * @return the value of the pin.
 */
extern UInt8 GetPinPortA(UInt8 pin);

/**
 * @brief Set value of PORTA
 *
 * @param data : the data to set
 */
extern void  SetPortA (UInt8 data);

/**
 * @brief Set PORTA's pin to 1
 *
 * @param pin : the PORTA's pin 
 */
extern void SetPinPortA(UInt8 pin);

/**
 * @brief Clear value of PORTA's pin
 *
 * @param pin : the PORTA's pin 
 */
extern void ClearPinPortA(UInt8 pin);

/**
 * @brief Get analogic value of PortA 's pin 
 *
 * @param RAx : pin to get value
 * @return the analogic value of the pin
 */
extern UInt8 GetPortAnalog (UInt8 RAx);

/**
 * @brief Get value of PortD
 *
 * @return the byte value of PortD
 */
extern UInt8 GetPortD (void);

/**
 * @brief Get value of PORTD's pin
 *
 * @param pin : the pin to get value.
 * @return the value of the pin.
 */
extern UInt8 GetPinPortD(UInt8 pin);

/**
 * @brief Set value of PortD
 *
 * @param data : the data to set
 */
extern void  SetPortD (UInt8 data);

/**
 * @brief Set PORTD's pin to 1
 *
 * @param pin : the PORTD's pin 
 */
extern void SetPinPortD(UInt8 pin);

/**
 * @brief Clear value of PORTD's pin
 *
 * @param pin : the PORTD's pin 
 */
extern void ClearPinPortD(UInt8 pin);


/**
 * @brief Get value of PortC
 *
 * @return the byte value of PortC
 */
extern UInt8 GetPortC (void);

/**
 * @brief Get value of PORTC's pin
 *
 * @param pin : the pin to get value.
 * @return the value of the pin.
 */
extern UInt8 GetPinPortC(UInt8 pin);

/**
 * @brief Set value of PortC
 *
 * @param data : the data to set
 */
extern void  SetPortC (UInt8 data);

/**
 * @brief Set PORTC's pin to 1
 *
 * @param pin : the PORTC's pin 
 */
extern void SetPinPortC(UInt8 pin);

/**
 * @brief Clear value of PORTC's pin
 *
 * @param pin : the PORTC's pin 
 */
extern void ClearPinPortC(UInt8 pin);


/**
 * @brief Set the position of the servomotor.
 *
 * Warning, you can't use the servomotor pin 4 and 5 on the PORTC.
 *
 * @param RCx : on what pin the servomotor is connected
 * @param Pos : the new position of the servomotor.
 */
extern void SetServoMotor(UInt8 RCx,UInt8 Pos);

/**
 * @brief switch off all servomotor connected on PortC
 */
extern void SwitchOffAllServo(void);

/**
 * @brief switch on all servomotor connected on PortC
 */
extern void SwitchOnAllServo(void);

/**
 * @brief Switch off a servomotor
 *
 * @param RCx : on what pin the servomotor is connected
 */
extern void SwitchOffOneServo(UInt8 RCx);

/**
 * @brief Switch on a servomotor
 *
 * @param RCx : on what pin the servomotor is connected
 */
extern void SwitchOnOneServo(UInt8 RCx);


/**
 * @brief Test the pob-proto board with a simple echo command
 *
 * @param test : byte to send on the pob-proto.
 *
 * @return a byte egual to the parameter
 */ 
extern UInt8 SendEcho(UInt8 test);


/**
 * @brief Send an order to the robot sapien. This function work only if you have connected a RoboSapien with pob-eye/pob-proto board.
 *
 * @param data : the order. 
 *
 * @see the file 'robotsapien-order.h' for all sapien orders
 */
void SendToSapien (UInt8 data);


/**
 * @name Tiny POB-PROTO function boards.
 *
 * If you have POB-PROTO board and Tiny POB-PROTO, you can use at the same time the 2 boards with this functions.
 * All this function access the Tiny POB-PROTO board.
 *
 */
/*@{*/

/**
 *
 * @see GetPortA()
 *
 * @warning This function is for <b>TINY POB-PROTO BOARD</b> ! <i>do not use if you don't have the tiny board</i>.
 */
extern UInt8 GetTinyPortA(void);

/**
 *
 * @see GetPinPortA()
 *
 * @warning This function is for <b>TINY POB-PROTO BOARD</b> ! <i>do not use if you don't have the tiny board</i>.
 */
extern UInt8 GetTinyPinPortA( UInt8 pin );

/**
 *
 * @see SetPortA()
 *
 * @warning This function is for <b>TINY POB-PROTO BOARD</b> ! <i>do not use if you don't have the tiny board</i>.
 */
extern void SetTinyPortA(UInt8 data);

/**
 *
 * @see SetPinPortA()
 *
 * @warning This function is for <b>TINY POB-PROTO BOARD</b> ! <i>do not use if you don't have the tiny board</i>.
 */
extern void SetTinyPinPortA(UInt8 pin);

/**
 *
 * @see ClearPinPortA()
 *
 * @warning This function is for <b>TINY POB-PROTO BOARD</b> ! <i>do not use if you don't have the tiny board</i>.
 */
extern void ClearTinyPinPortA(UInt8 pin);

/**
 *
 * @see GetPortAnalog()
 *
 * @warning This function is for <b>TINY POB-PROTO BOARD</b> ! <i>do not use if you don't have the tiny board</i>.
 */
extern UInt8 GetTinyPortAnalog (UInt8 RAx);


/**
 *
 * @see GetPortD()
 *
 * @warning This function is for <b>TINY POB-PROTO BOARD</b> ! <i>do not use if you don't have the tiny board</i>.
 */
extern UInt8 GetTinyPortD (void);

/**
 *
 * @see GetPinPortD()
 *
 * @warning This function is for <b>TINY POB-PROTO BOARD</b> ! <i>do not use if you don't have the tiny board</i>.
 */
extern UInt8 GetTinyPinPortD( UInt8 pin );

/**
 *
 * @see SetPortD()
 *
 * @warning This function is for <b>TINY POB-PROTO BOARD</b> ! <i>do not use if you don't have the tiny board</i>.
 */
extern void  SetTinyPortD (UInt8 data);

/**
 *
 * @see SetPinPortD()
 *
 * @warning This function is for <b>TINY POB-PROTO BOARD</b> ! <i>do not use if you don't have the tiny board</i>.
 */
extern void SetTinyPinPortD(UInt8 pin);

/**
 *
 * @see ClearPinPortD()
 *
 * @warning This function is for <b>TINY POB-PROTO BOARD</b> ! <i>do not use if you don't have the tiny board</i>.
 */
extern void ClearTinyPinPortD(UInt8 pin);


/**
 *
 * @see GetPortC()
 *
 * @warning This function is for <b>TINY POB-PROTO BOARD</b> ! <i>do not use if you don't have the tiny board</i>.
 */
extern UInt8 GetTinyPortC (void);

/**
 *
 * @see GetPinPortC()
 *
 * @warning This function is for <b>TINY POB-PROTO BOARD</b> ! <i>do not use if you don't have the tiny board</i>.
 */
extern UInt8 GetTinyPinPortC( UInt8 pin );

/**
 *
 * @see SetPortC()
 *
 * @warning This function is for <b>TINY POB-PROTO BOARD</b> ! <i>do not use if you don't have the tiny board</i>.
 */
extern void SetTinyPortC (UInt8 data);

/**
 *
 * @see SetPinPortC()
 *
 * @warning This function is for <b>TINY POB-PROTO BOARD</b> ! <i>do not use if you don't have the tiny board</i>.
 */
extern void SetTinyPinPortC(UInt8 pin);

/**
 *
 * @see ClearPinPortC()
 *
 * @warning This function is for <b>TINY POB-PROTO BOARD</b> ! <i>do not use if you don't have the tiny board</i>.
 */
extern void ClearTinyPinPortC(UInt8 pin);


/**
 *
 * @see SetServoMotor()
 *
 * @warning This function is for <b>TINY POB-PROTO BOARD</b> ! <i>do not use if you don't have the tiny board</i>.
 */
extern void SetTinyServoMotor(UInt8 RCx,UInt8 Pos);

/**
 *
 * @see SetServoMotorFull()
 *
 * @warning This function is for <b>TINY POB-PROTO BOARD</b> ! <i>do not use if you don't have the tiny board</i>.
 */
extern void SetTinyServoMotorFull(UInt8 RCx,UInt8 Pos);

/**
 *
 * @see SwitchOffAllServo()
 *
 * @warning This function is for <b>TINY POB-PROTO BOARD</b> ! <i>do not use if you don't have the tiny board</i>.
 */
extern void SwitchTinyOffAllServo(void);

/**
 *
 * @see SwitchOnAllServo()
 *
 * @warning This function is for <b>TINY POB-PROTO BOARD</b> ! <i>do not use if you don't have the tiny board</i>.
 */
extern void SwitchTinyOnAllServo(void);

/**
 *
 * @see SwitchOffOneServo()
 *
 * @warning This function is for <b>TINY POB-PROTO BOARD</b> ! <i>do not use if you don't have the tiny board</i>.
 */
extern void SwitchTinyOffOneServo(UInt8 Servo);

/**
 *
 * @see SwitchOnOneServo()
 *
 * @warning This function is for <b>TINY POB-PROTO BOARD</b> ! <i>do not use if you don't have the tiny board</i>.
 */
extern void SwitchTinyOnOneServo(UInt8 Servo);

/**
 *
 * @see SwitchOffOneServoFull()
 *
 * @warning This function is for <b>TINY POB-PROTO BOARD</b> ! <i>do not use if you don't have the tiny board</i>.
 */
extern void SwitchTinyOffOneServoFull(UInt8 Servo);

/**
 *
 * @see SwitchOnOneServoFull()
 *
 * @warning This function is for <b>TINY POB-PROTO BOARD</b> ! <i>do not use if you don't have the tiny board</i>.
 */
extern void SwitchTinyOnOneServoFull(UInt8 Servo);

/**
 *
 * @see SendEcho()
 *
 * @warning This function is for <b>TINY POB-PROTO BOARD</b> ! <i>do not use if you don't have the tiny board</i>.
 */
extern UInt8 SendTinyEcho(UInt8 test);
/*@}*/

#ifdef __cplusplus
 }
#endif

#endif
