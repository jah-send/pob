//
// Copyright 2006-2010 POB-Technology. All rights reserved.
// POB-Technology PROPRIETARY/CONFIDENTIAL.
//

/**
 * @brief Object management.
 *
 * @file
 *
 * Alloc, free and manage object pool
 *
 * @author Baptiste Burles. POB-Technology 
 *
 */
#ifndef OBJECT_H
#define OBJECT_H


/**
 * Macro to set the garbage collector root index
 */
extern u1 root_index ;
#define INC_ROOT root_index++;
#define DEC_ROOT root_index--;


/**
 * alloc a new object
 */
extern s1 allocObject( Class *c, int size );

/**
 * alloc a new array
 */
extern s1 allocArray( int len );

/**
 * alloc a new object array
 */
extern Object *allocObjectArray(Class *c,int len, int size_of_field);

/**
 * alloc a new string (constant string)
 */
extern Object *allocString( Class *c,  s1 *str, u4 len );

/**
 * verify if object is in object stack
 */
extern s1 isObjectInStack( Object *ptr );


/**
 * free an object
 */
extern void freeObject( Object *ptr );

/**
 * run the garbage collector
 */
extern void run_gc(void);
extern void gc(void);
extern void gc1(Object *op, Object *lvar );

/**
 * debug object stack
 */
extern void dumpObject( void );


#endif
