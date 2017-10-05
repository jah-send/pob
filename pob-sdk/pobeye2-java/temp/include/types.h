//
// Copyright 2006-2010 POB-Technology. All rights reserved.
// POB-Technology PROPRIETARY/CONFIDENTIAL.
//

/*
 * @brief vm runtime type
 *
 * @file
 *
 * structure for method, field, class and object for the pob vm.
 *
 * @author Baptiste Burles. POB-Technology. 2005
 *
 */
#ifndef TYPES_H
#define TYPES_H

/*
 * field
 */
typedef struct _field
{
	u1 isObject ; // is this field an object ?
	u2 offset ;   // offset in field data 
	u1 isStatic ; // is a static field ?
	RuntimeVar *var ; // variable for a static field only ! if object this variable is set to 0

} Field ;


/*
 * java method
 */
typedef struct _method
{
	void (*call)(void *rt) ; // pointer to method code

} Method ;


/*
 * java class
 */
typedef struct _class
{
	struct _class *superclass ;

	u4 size ;
	u4 fieldsNb ;
	struct _field *fields ;

} Class ;

/*
 * object
 */
typedef struct _object 
{
	u1 root_index ; // garbage collector root index 
	u1 mark ;       // garbage collector mark
	u1 constant ;   // object created by a ldc instructions (ldc_string for example)
	u4 hash ;       // id for constant string

	struct _class *classes ; // reference to this class (null if primitive array or int or float...)

	u4 len ;           // len of data or size of array (in bytes)
	u4 size_of_array ; // size of array (in array units)
	u1 *data ;         // field data or array data 

	struct _object *prev ; // previous object
	struct _object *next ; // next object

} Object ;




/*
 * java thread runtime
 */
typedef struct _java_thread
{
	RuntimeVar *frame ;   // main frame (point on the frame begin)
	u4 frame_size ;       // size of main frame (in RuntimeVar units)
	RuntimeVar *save ;    // save frame 
	RuntimeVar *lvar ;    // local variable stack
	//u4 lvar_size ;        // size of local variable stack
	Method *m ;           // current method
	u1 return_ok ;            // set to 1, if method return a value
	RuntimeVar return_value ; // return value, currently only 32 bits return value.

} JavaThreadRuntime ;



#endif
