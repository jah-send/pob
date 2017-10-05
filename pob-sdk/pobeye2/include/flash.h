//
// Copyright 2009 POB-Technology. All rights reserved.
// POB-Technology PROPRIETARY/CONFIDENTIAL.
//
/** \anchor flash
 *
 * @brief Flash memory functions
 *
 * @file 
 * 
 * You can write and read 8K bytes of pobeye2 flash. The flash is divided into 15 sectors of 512 bytes.
 * Only the write function must have a sector, the read function can read from anywhere.
 *
 * @par flash example
 *
 * @code

 #include <pob-eye.h>

 #define DATA	"pob-technology"

 int main(void)
 {
	UInt8 buffer[32];
	UInt32 size,i;

	// Init pobeye2 hardware:
	InitPobeye2();
	InitUART0(115200);
	FlashInit();

	// Get size of DATA:
	size = strlen(DATA);
	// Copy DATA to buffer:
	memcpy(buffer, DATA, size);

	// Before write any data, erase flash:
	FlashErase();

	// Write buffer to the flash sector 0:
	FlashWrite(0,buffer,size);
	buffer[0] = 0;

	// Read 10 bytes from offset 4 in flash data.
	FlashRead(4,buffer,10);

	for(i=0;i<10;i++)
	{
	  SendByteToUART0(buffer[i]);
	}

	return 0;
 }

 * @endcode
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

/** @brief Init flash function.
 */
extern void FlashInit(void);

/** @brief Erase flash sector.
 *
 * @return 0 if no error, else error code.
 */
extern UInt32 FlashErase(void);

/** @brief Write a buffer into flash.
 *
 * @param sector		Sector number (between 0 and 15).
 * @param buffer		Pointer to a buffer.
 * @param bufferSize	Number of bytes to write to flash.
 * @return 0 if no error, else error code.
 */
extern UInt32 FlashWrite(UInt32 sector, UInt8 *buffer, UInt32 bufferSize);

/** @brief Read data from flash.
 *
 * @param offset		Offset where read data into flash.
 * @param data			Pointer to an array where store the bytes read.
 * @param len			Number of bytes to read.
 */
extern void FlashRead( UInt32 offset, UInt8 *data, UInt32 len);

#ifdef __cplusplus
 }
#endif

#endif
