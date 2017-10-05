/** 
 * @brief Access POB-EYE flash memory
 *
 * @file
 * 
 * Read/Write the flash memory of POB-EYE. 
 * <br>The functions works on the last flash sector of POB-EYE. The size of this flash sector is 8192 bytes.
 * You can't write or read more than 8K bytes.
 *
 * This flash sector is divided in 16 sector of 512 bytes.
 *
 * <b>Update:</b>
 * <br>
 * <i>2007.02.21: write on 8K bytes of flash</i>
 * <br>
 * @author Baptiste Burles. POB-Technology
 *
 */
#ifndef POB_FLASH_H
#define POB_FLASH_H

#ifdef __cplusplus
extern "C" {
#endif

	/**
 * @name Flash result codes.
 *
 */
/*@{*/
#define FLASH_SUCCESS									0		/**< Last operation in flash is a success. */
#define FLASH_INVALID_COMMAND							1		/**< Invalid command. */
#define FLASH_SRC_ADDR_ERROR							2		/**< Source address is not on word boundary. */
#define FLASH_DST_ADDR_ERROR							3		/**< Destination address is not on a correct boundary. */
#define FLASH_SRC_ADDR_NOT_MAPPED						4		/**< Source address is not mapped in memory. */
#define FLASH_DST_ADDR_NOT_MAPPED						5		/**< Destination address is not mapped in memory. */
#define FLASH_COUNT_ERROR								6		/**< Byte count is not multiple of 4. */
#define FLASH_INVALID_SECTOR							7		/**< Sector number is invalid. */
#define FLASH_SECTOR_NOT_BLANK							8		/**< Sector is not blank. */
#define FLASH_SECTOR_NOT_PREPARED_FOR_WRITE_OPERATION	9		/**< Sector not prepared for write. */
//#define FLASH_COMPARE_ERROR                          10		
#define FLASH_BUSY										11		/**< Flash hardware interface busy. */
/*@}*/

/**
 * @brief Init flash function
 *
 * To use the flash function, you must call first this function.
 *
 * For example:
 * <i>InitPOBEYE();<br>FlashInit();</i>
 */
extern void FlashInit(void);


/**
 * @brief Erase flash sector
 *
 * @return 0 if no error
 */
extern UInt32 FlashErase(void);

/**
 * @brief Write data on flash. 
 *
 * This function write data on the specified sector of flash.
 *
 * @param sector_number: sector where writing data. Must be between 0 and 15. 
 * @param ptr: pointer to the data 
 * @param len: Length of data.
 * @return 0 if no error
 */
extern UInt32 FlashWrite( UInt32 sector_number, unsigned char *ptr, UInt32 len );


/**
 * @brief Read data on flash.
 *
 * @param sector_number : begin read at the sector number specified (between 0 and 15)
 * @param offset : position in sector (between 0 and 511)
 * @param ptr : array to store data read
 * @param len : number of byte to read
 */
extern void FlashRead( UInt32 offset, unsigned char *data, UInt32 len );

#ifdef __cplusplus
 }
#endif

#endif
