//
// Copyright 2006-2010 POB-Technology. All rights reserved.
// POB-Technology PROPRIETARY/CONFIDENTIAL.
//

/*
 * @brief define and type
 *
 * @file
 *
 * Various type and macro for pob vm. This file is platform dependant
 *
 * @author Baptiste Burles. POB-Technology. 2005
 *
 */
#ifndef RUNTIME_H
#define RUNTIME_H

/* VM define flag :
 *
 *    VM_DEBUG_ON to include trace for debug
 *    VM_ARM if compile to ARM cpu             
 *    VM_GCC if compile with GNU GCC
 *    VM_SUPPORT_64_BITS if cpu/compiler support 64 bits
 *    VM_SUPPORT_EXCEPTIONS if vm support try { } catch 
 *    VM_WIN32 if compile to WIN32 system
 *    VM_GBA if compile for the GameBoy Advance
 *    VM_LPC2106 if compile for the POB-EYE
 *
 */



//#define VM_LPC2106
#ifdef VM_LPC2106
#	define VM_ARM 
#	define VM_GCC 
//#	define VM_SUPPORT_EXCEPTIONS
#endif


/* If VM support 64 bits */
#ifdef VM_SUPPORT_64_BITS 
#	ifdef VM_GCC  /* if pob vm compiled with gcc */
#		define int64  long long
#	else  /* else compiled with ms visual c++ */
#		define int64  _int64 
#	endif
#endif

#ifdef VM_GCC /* GCC inline */
#	define FUNC_INLINE inline
#else /* MS VISUAL inline */
#	define FUNC_INLINE __inline 
#endif

/*  VM TYPES */

/* signed value */
#define s4 long
#define s2 short
#define s1 char 

/* unsigned value */
#define u4  unsigned long
#define u2  unsigned short
#define u1  unsigned char 

/* real type */
#define float32 float


#ifdef VM_SUPPORT_64_BITS
#	define s8 int64
#	define u8  unsigned int64
#	define float64 double // double : 64 bits for gcc and ms compiler
#endif


/**  runtime variable */
typedef union _var {
	s1 byte ;      /**< byte value              */
	s2 character ; /**< short value             */
	s4 integer ;   /**< integer value           */

	float32 real ; /**< float value             */

	void *ref ;    /**< memory reference        */

	u2 unicode;    /**< unicode character       */
	u4 data ;      /**< data                    */

} RuntimeVar ;


#define KB 1024
#define MB (KB*KB)

/** Debug macro */

#ifdef VM_DEBUG_ON
#	ifdef VM_LINUX
#		define DEBUG( string ) printf(" %s : %s : %d : %s\n",(char *)__FILE__ ,(char *)__FUNCTION__,  __LINE__, string );
#		define TRACE( string ) printf str ;
#	endif
#	ifdef VM_WIN32
#		define DEBUG( string ) printf("In file %s at %d : %s\n",(char *)__FILE__ ,  __LINE__, string );
#		define TRACE( string ) printf string
#	endif
#	ifdef VM_GBA
/* this code work only in the VisualBoyAdvance emulator */
	   static void print(char *s)
	   {
		 asm volatile("mov r0, %0;"
					  "swi 0xff0000;"
					  : // no ouput
					  : "r" (s)
					  : "r0");
	   }
#		define TRACE( str ) 
#		define DEBUG( str ) //print(str);
#	endif
#	ifdef VM_LPC2106
#		define TRACE( str ) PrintTextOnPobTerminal str ;
#	endif
#endif


#ifndef VM_DEBUG_ON
#	define TRACE(str)
#	define EDBUG(str)
#endif


#endif
