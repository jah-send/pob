//
// Copyright 2009 POB-Technology. All rights reserved.
// POB-Technology PROPRIETARY/CONFIDENTIAL.
//

/** \anchor i2c
 *
 * @brief I2C Communication. 
 *
 * @file
 *
 * Communication on I2C bus as Master mode or as Slave mode.
 *
 * @par Master write example
 *
 * @code

 #include <pob-eye.h>

 int main(void)
 {
 	UInt8 buffer;
	UInt8 i2c_slave_addr = 0x40; // The slave address.
 
	// Init pobeye hardware:
	InitPobeye2();
  	InitI2C(I2C_400_KHZ);
 
 	data=0;

	// Main loop:
 	while(1)
 	{
		// 1 - send slave address in write mode
		// 2 - Write data
		// 3 - Stop i2c

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
 
 		StopI2C();
 	}
 }
  @endcode
 
  @par Master read example
 
  @code
 
 #include <pob-eye.h>

 int main(void)
 {
	UInt8 data,data1;
 	UInt8 i2c_slave_addr = 0x40; // The slave address.
 
	// Init pobeye hardware:
	InitPobeye2();
  	InitI2C(I2C_400_KHZ);
	InitUART0(19200);
 
	// Main loop:
 	while(1)
 	{
		// 1 - Send slave address in read mode.
		// 2 - Read data from i2c slave device, don't acknoledge the last data.
		// 3 - Stop i2c.

 		SendSlaveAddress( i2c_slave_addr | 1 );
 		data=ReadOnI2CWithAck(0);  //ack byte
 		data1=ReadOnI2CWithAck(1); //don't ack the last byte. 
 		StopI2C();

		SendByteToUART0(data);
		SendByteToUART0(data1);

 	}
 }

 * @endcode
 *
 *
 */
#ifndef I2C_H
#define I2C_H

#ifdef __cplusplus
extern "C" {
#endif

/** @brief I2C Bus Speed.
 */
typedef enum _i2c_speed
{
	I2C_100_KHZ=0,		/**< I2C frequency 100 KHz */
	I2C_400_KHZ=1		/**< I2C frequency 400 KHz */
} I2C_SPEED;

/**
 * @name i2c master
 *
 * @brief Use pobeye2 in I2C Master mode.
 */
/*@{*/

/**
 * @brief Initalize I2C bus as Master.
 *
 * @param speed		Frequency speed of I2C bus.
 */
extern void InitI2C(I2C_SPEED speed);


/**
 * @brief Send slave adress through the bus.
 * 
 * @param  Addr_S		address of the slave device on the bus.
 */
extern void SendSlaveAddress(UInt8 Addr_S);


/** 
 * @brief Read a byte from a slave device.
 *
 * @return byte from the slave device.
 */
extern UInt8 ReadOnI2C(void);


/**
 * @brief Read a byte from a slave device.
 * 
 * @param ack		Set to 0 to acknowledge the data (master will send others data), set to 1 to 'not acknowledge' (end of transmission).
 */
extern UInt8 ReadOnI2CWithAck(UInt8 ack);


/** 
 * @brief Write a byte on the I2C bus to the slave device.
 *
 * @param Byte		Byte that will be sent through the I2C bus to the slave device
 */
extern void WriteOnI2C(UInt8 Byte);

/**
 * @brief Wrtie a buffer on the I2C bus to the slave device.
 * @param Data		Pointer to data.
 * @param Len		Lenght fo data.
 */
extern void WriteBufferOnI2C (UInt8 *Data, UInt32 Len);

/**
 * @brief Stop I2C communication
 */
extern void StopI2C(void);

/*@}*/



/**
 * @name i2c slave
 *
 * @brief Use pobeye2 in I2C Slave mode.
 */
/*@{*/

/** @brief Init I2C Bus as slave.
 *
 * @param address		Device address.
 * @param speed			Frequency speed of I2C bus.
 */
extern void InitSlaveI2C(UInt8 address,I2C_SPEED speed);

/** @brief Get buffer from I2C bus (as slave).
 *
 * @param Buffer		Pointer to a buffer.
 * @return Size of received buffer.
 *
 * @par Example
 *
 * @code

 int main(void)
 {
	UInt8 *buffer;
	UIn8 size;

	// init pobeye2 and i2c as slave:
	InitPobeye2();
	InitSlaveI2C(0xB0,I2C_100_KHZ);

	// main loop:
	while(1)
	{
		// get the i2c buffer:
		size = GetBufferFromSlaveI2C(&buffer);
		if(size!=0)
		{
			//then buffer contains the data (master send something)...
		}
	}
 }

  @endcode

 */
extern UInt8 GetBufferFromSlaveI2C(UInt8 **buffer);

/** @brief Set buffer to I2C bus (as slave).
 */
extern void SetBufferToSlaveI2C(UInt8 *buffer, UInt8 size);

/*@}*/

#ifdef __cplusplus
 }
#endif

#endif
