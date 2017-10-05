//
// Copyright 2006-2010 POB-Technology. All rights reserved.
// POB-Technology PROPRIETARY/CONFIDENTIAL.
//

/*
 * @brief Memory management.
 *
 * @file
 *
 * Alloc block of memory.
 *
 * @author Baptiste Burles. POB-Technology 
 *
 */
#ifndef MEMORY_H
#define MEMORY_H


extern u4 memory_size ;


extern u4 getFreeMemory(void);

extern u4 getSizeOfMemory(void);


extern void *allocMemory( u4 numbytes);

extern void freeMemory(void *firstbyte );


#ifdef VM_LPC2106
extern void *memset(void *m, int c,int n);
#endif

#endif

