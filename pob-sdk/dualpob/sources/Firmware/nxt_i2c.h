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
#ifndef NXT_I2C_H
#define NXT_I2C_H



/** dual-pob bricks order
 *
 * documentation reference: POB_bridge_US.pdf
 */


#define SET_ANALOG			0xA2	/**< set analog channel */
#define GET_ANALOG			0xA5	/**< get analog value */

#define SELECT_POBEYE_FORM	0xB1	/**< select form in pobeye memory */
#define REFRESH_POBEYE_FRAME 0xA1	/**< refresh frame on pobeye */
#define GET_FRAME_X			0xA3	/**< get x form */
#define GET_FRAME_Y			0xA4	/**< get y form */
#define GET_FRAME_WIDTH		0xAA	/**< get width form */
#define GET_FRAME_HEIGHT	0xAB	/**< get height form */


#define SEND_POBEYE_ID		0xA7	/**< send pobeye identifier */
#define READ_FROM_POBEYE	0xA8	/**< read data from pobeye */
#define WRITE_TO_POBEYE		0xA6	/**< write data to pobeye */

#define SET_BAUDRATE		0xB3	/**< set uart0 baudrate */
#define SEND_TO_UART		0xB4	/**< send data to uart0 */

#define PREPARE_UART		0xB5	/**< prepare uart0 reception */
#define GET_FROM_UART		0xB6	/**< get data from uart0 */

#define SET_DUALPOB_SERVO   0xB7
#define SET_BIOLOID_SERVO	0xB8
#define MOVE_BIOLOID		0xB9

#define SET_IO				0xBA	/**< configure/set input output */
#define GET_IO				0xBB	/**< get input value */

#define SET_DC_MOTOR		0xBC	/**< set dc motor */


#endif
