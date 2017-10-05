/* Copyright POB-Technology, 2008
 *
 * contact@pob-technology.com
 * 
 * This software is the main firmware of DUAL-POB device.
 * 
 * This software is governed by the CeCILL-C license under French law and
 * abiding by the rules of distribution of free software.  You can  use, 
 * modify and/ or redistribute the software under the terms of the CeCILL-C
 * license as circulated by CEA, CNRS and INRIA at the following URL
 * "http://www.cecill.info". 
 * 
 * As a counterpart to the access to the source code and  rights to copy,
 * modify and redistribute granted by the license, users are provided only
 * with a limited warranty  and the software's author,  the holder of the
 * economic rights,  and the successive licensors  have only  limited
 * liability. 
 * 
 * In this respect, the user's attention is drawn to the risks associated
 * with loading,  using,  modifying and/or developing or reproducing the
 * software by the user in light of its specific status of free software,
 * that may mean  that it is complicated to manipulate,  and  that  also
 * therefore means  that it is reserved for developers  and  experienced
 * professionals having in-depth computer knowledge. Users are therefore
 * encouraged to load and test the software's suitability as regards their
 * requirements in conditions enabling the security of their systems and/or 
 * data to be ensured and,  more generally, to use and operate it in the 
 * same conditions as regards security. 
 * 
 * The fact that you are presently reading this means that you have had
 * knowledge of the CeCILL-C license and that you accept its terms.
 * 
 */
#ifndef COMMUNICATION_H
#define COMMUNICATION_H

/**< end of string character */
#define LF				0x0A
#define CR				0x0D


/**< string structure */
typedef struct _string
{
	UInt8 len;			/**< string's lenght */
	UInt8 buffer[16];	/**< string character */
} String;


/** @brief Extract string from an uart buffer
 *
 * @param [out]str		String array
 * @param strNb			Lenght of string array
 * @param [in]buffer	Uart buffer
 * @param [in]size		Uart buffer size
 * @return Number of string in the uart buffer
 */
extern Int8 extractString(String *str,int strNb, UInt8 *buffer,UInt8 size);


/** @brief Send string on uart with CR LF at the end
 *
 * @param buffer	String to send
 */
extern void send(char *buffer);

/** @brief Receive a uart character that contains CR LF
 *
 * @param buffer 	Buffer 
 * @param len		Size of buffer
 * @param offset	Buffer offset
 * return Lenght of string.
 */
extern UInt8 receive(unsigned char *buffer,UInt8 len, UInt8 offset);

/** @brief Compare 2 strings
 *
 * @param str 		Source string
 * @param cmp		Compare string
 * @param len		Lenght of compare string
 * @return 1 if str and cmp are egual else return 0.
 */
extern UInt8 strCmp(Int8 *str,UInt8 *cmp,UInt8 len);


#endif
