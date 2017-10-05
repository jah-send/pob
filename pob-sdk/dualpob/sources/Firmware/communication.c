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

#include <dual-pob.h>

#include "communication.h"


#define SendByteToUART		SendByteToUART0
#define GetByteFromUART		GetByteFromUART0


//send string and LF+CR
void send(char *buffer)
{
	UInt32 i=0;

	for(i=0;buffer[i]!=0;i++)
	{
		SendByteToUART(buffer[i]);
	}

	SendByteToUART(LF);
	SendByteToUART(CR);
}

//receive string with CR, return size of string
UInt8 receive(unsigned char *buffer,UInt8 len,UInt8 offset)
{
	UInt8 size=offset;
	UInt8 byte;

	do
	{
		byte=GetByteFromUART();

		if(byte==CR)
			break;

		buffer[size]=byte;
		size++;

		if(size>len)
		{
			size=len;
			break;
		}

	}while(1);

	buffer[size]=0;

	return size;
}


Int8 extractString(String *str,int strNb, UInt8 *buffer,UInt8 size)
{
	UInt8 i=0,j=0;
	UInt8 str_index=0;

	for( ; i<size;i++)
	{
		if(buffer[i]!= ' ')
		{
			str[str_index].buffer[j]=buffer[i];
			j++;
		}
		else
		{
			if(j==0)
				continue;

			str[str_index].buffer[j]='\0';
			str[str_index].len=j;
			
//			SendString("\r\n- ");
//			SendString(str[str_index].buffer);

			str_index++;

			if(str_index>strNb)
				return -1;

			j=0;
		}

	}

	str[str_index].buffer[j]='\0';
	str[str_index].len=j;

//	SendString("\r\n- ");
//	SendString(str[str_index].buffer);


	return str_index+1;
}


//compate 2 strings, return 1 if egual.
UInt8 strCmp(Int8 *str,UInt8 *cmp,UInt8 len)
{
	UInt8 i=0;

	for(i=0;i<len||str[i]!=0;i++){
		if(str[i]!=cmp[i])
			return 0;
	}

	if(i==len)
		return 1;

	return 0;
}
