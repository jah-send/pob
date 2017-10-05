/** 
 * @brief I2C Communication. 
 *
 * @file
 *
 * Communication with the I2C bus as Master mode.
 *
 * @author Pierre SEGUIN. POB-Technology
 *
 */
#ifndef I2C_H
#define I2C_H

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @brief Initalize I2C bus.
 *
 * The bus speed is at speed 128 Kbits/s
 */
void InitI2C(void);

/**
 * @brief Set the speed of the i2c bus.
 *
 * @param speed : the bus speed in KHz (maximum is 375 KHz)
 */
void SetI2cSpeed(UInt32 speed);

/**
 * @brief Send slave adress through the bus.
 * 
 * @param  Addr_S : address of the slave device on the bus.
 */
void SendSlaveAdress(UInt8 Addr_S);


/** 
 * @brief Read a byte from a slave device.
 *
 * @return byte from the slave device.
 */
UInt8 ReadOnI2C(void);


/**
 * @brief Read a byte from a slave device.
 * 
 * @param ack : set to 0 to acknowledge the data (master will send others data), set to to 'not acknowledge' (end of transmission).
 */
UInt8 ReadOnI2CWithAck(UInt8 ack);


/** 
 * @brief Write a byte on the I2C bus to the slave device.
 *
 * @param Byte : Byte that will be sent through the I2C bus to the slave device
 */
void WriteOnI2C(UInt8 Byte);


/**
 * @brief Stop I2C communication
 */
void STOPI2C(void);


/**
 * @brief Initialize POB-EYE I2C bus as Slave device.
 * 
 * @param  addr : address of the slave device on the bus.
 */
void InitI2CSlave(UInt8 addr);

/**
 * @brief Set the speed of the I2C bus.
 * 
 * @param  speed : the bus speed in KHz.
 */
void SetI2CSlaveSpeed(UInt32 speed);

/**
 * @brief Read data on I2C bus from a master device.
 * 
 * @param [out] Data : pointer to store the byte read.
 * @param endOfRead
 * @return 1 if a data is read, else 0 (I2C bus is not in slave receiver mode).
 */
UInt8 ReadOnI2CSlave(UInt8 *Data,UInt8 endOfRead);

/**
 * @brief Write a byte on I2C bus to the master device.
 * 
 * @param  Data : byte send to the master device.
 * @param endOfWrite
 * @return 1 if a byte is send, else 0 (I2C bus is not in slave transmitter mode).
 */
UInt8 WriteOnI2CSlave(UInt8 Data, UInt8 endOfWrite);

#ifdef __cplusplus
 }
#endif

#endif
