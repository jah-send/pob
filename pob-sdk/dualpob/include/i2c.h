//
// Copyright 2008 POB-Technology. All rights reserved.
// POB-Technology PROPRIETARY/CONFIDENTIAL.
//

/** \anchor i2c
 * 
 * @brief I2C Communication. 
 *
 * @file
 *
 * Communication with the I2C bus as Master/Slave mode. The i2c bus on dual-pob comes with 4.7k pull-up resistances.
 *
 * @par Master write example
 *
 * @code
 *
 	UInt8 buffer;
	UInt8 i2c_slave_addr = 0x40;
 
  	InitI2C();
 
 	data=0;
 	while(1)
 	{
 		SendSlaveAddress( i2c_slave_addr );
 		if(data==0)
 		{
 			buffer='A';
 			WriteOnI2C(buffer);
 			data=1;
  		}
 		else
 		{
 			buffer='B';
  			WriteOnI2C(buffer);
 			data=0;
 		}
 
 		STOPI2C();
 	}
 
  @endcode
 
  @par Master read example
 
  @code
 
 	InitUART0(19200);
 	InitI2C();
 
 	while(1)
 	{
 		SendSlaveAddress( i2c_slave_addr | 1 );
 		data=ReadOnI2CAck();
 		data1=ReadOnI2CNoAck();
 
 		SendByteToUART0(data);
		SendByteToUART0(data1);
 
 		STOPI2C();
 	}
 
 * @endcode
 *
 * @par Slave code example
 *
 * @code
 *
	UInt8 i2c_slave_addr = 0x40;

 	InitUART0(19200);
 
 	InitI2CSlave(i2c_slave_addr);
 
 	while(1)
 	{
 		if(ReadOnI2CSlave(&data)==1)
 		{
 			SendByteToUART0(data);
 		}
 
 		if(flag==0)
 		{
 			data='0';
 			flag=1;
 		}
 		else
 		{
 			data='R';
 			flag=0;
 		}
 		
 		PrepareWriteOnI2CSlave(data);
 
 		if(IsWriteOnI2COk(data)==1)
 		{
 			SendByteToUART0('w');
 		}
 	}
 *
 * @endcode
 *
 *
 */
#ifndef DUAL_POB_I2C_H
#define DUAL_POB_I2C_H


/**
 * @name I2C master functions
 */
/*@{*/

/**
 * @brief Initialize I2C bus.
 *
 * The bus speed is at 100 Kbits/s
 */
extern void InitI2C(void);


/** @brief Set I2C bus speed
 *
 *
 * @param scl_clock		I2C SCL clock, between 100000 and 400000.
 */
extern void SetI2CSpeed(UInt32 scl_clock);

/**
 * @brief Send slave address through the bus.
 * 
 * This function issues a start condition, sends slave address and transfer direction.
 *
 * @par To write on i2c bus:
 * @code
 *		SendSlaveAddress(your_i2c_slave_adress).
 * @endcode
 *
 * @par To read on i2c bus:
 * @code 
 *		SendSlaveAddress(your_i2c_slave_adress | 1);
 * @endcode
 *
 * @param  Addr_S		address (and transfer direction!) of the slave device on the i2c bus.
 */
extern void SendSlaveAddress(UInt8 Addr_S);

/** 
 * @brief Read a byte from a slave device and acknowledge.
 *
 * @return byte from the slave device.
 */
extern UInt8 ReadOnI2CAck(void);

/** @brief Read a byte from a slave device and don't acknowledge.
 *
 * This call must be follow by a STOPI2C() call.
 *
 * @return byte from the slave device.
 */
extern UInt8 ReadOnI2CNoAck(void);


/** 
 * @brief Write a byte on the I2C bus to the slave device.
 *
 * @param data		Byte that will be sent through the I2C bus to the slave device
 * @return 1 if write failed, 0 else.
 */
extern UInt8 WriteOnI2C( UInt8 data );

/** @brief Write a buffer on the I2C bus to the slave device
 *
 *
 * @param Data		Buffer to send.
 * @param Len		Lenght of buffer
 */
extern void WriteBufferOnI2C(UInt8 *Data, UInt32 Len);

/**
 * @brief Stop I2C communication.
 */
extern void STOPI2C(void);
/*@}*/


/**
 * @name I2C slave functions
 */
/*@{*/

/**
 * @brief Initialize I2C bus in slave mode.
 *
 * <b>I2C slave functions.</b>
 * the dual-pob use the i2c interrupt in slave mode.
 *
 * @param slaveAddress	I2C slave address.
 */
extern void InitI2CSlave(UInt8 slaveAddress);

/** 
 * @brief Read a byte from a i2c master device.
 *
 * <b>I2C slave functions.</b>
 *
 * @param [out] data	the data read
 * @return 1 if a data have been read, else 0.
 */
extern UInt8 ReadOnI2CSlave( UInt8 *data );


/** @brief Prepare a byte to be write on I2C bus.
 *
 * <b>I2C slave functions.</b>
 * Call the IsWriteOnI2COk() function to verify if your byte has been sent to the master device.
 * 
 * @param data		Data send to i2c master
 */
extern void PrepareWriteOnI2CSlave(UInt8 data);


/** @brief Is the byte has been sent to the i2c master?
 *
 * <b>I2C slave functions.</b>
 * Use this function to verify if the master has been read the slave device. @see PrepareWriteOnI2CSlave
 *
 * @par Example: Wait a write transfer from a master device:
 *
 * @code

	PrepareWriteOnI2CSlave( your_data );

	while( IsWriteOnI2COk() == 0 ) ;

 * @endcode
 *
 * @return 1 if the data has been sent. 0 else.
 */
extern UInt8 IsWriteOnI2COk(void);


/** @brief Detect a stop condition or a restart condition on i2c bus
 *
 * <b>I2C slave functions.</b>
 * You can use this function to test end of transmition for example.
 *
 * @return 1 if a stop or restart condition occurs on i2c bus. else 0
 */
extern UInt8 StopDetectedOnI2CSlave(void);

/*@}*/


/**
 * @name low level master i2c functions: start and repeated start condition
 */
/*@{*/
/** @brief Send start condition + slave address
 *
 * @warning low level functions!
 *
 * @param address	I2c slave address
 * @return 1 on success, else 0 (device not accessible).
 */
extern unsigned char i2c_start(unsigned char address);

/** @brief Send a repeated start condition
 *
 * @warning low level functions!
 *
 * @param address
 * @return 1 on success, else 0 (device not accessible).
 */
extern unsigned char i2c_rep_start(unsigned char address);
/*@}*/

#endif
