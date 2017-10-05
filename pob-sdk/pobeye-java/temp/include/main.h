//
// Copyright 2006-2010 POB-Technology. All rights reserved.
// POB-Technology PROPRIETARY/CONFIDENTIAL.
//

#ifndef MAIN_H
#define MAIN_H


/*
 * global structure and function 
 *
 * @author Baptiste Burles. POB-Technology 
 */

extern const Class *objectClass;
extern Method *mainMethod ;

extern Object *objectStack ;
extern u4 objectNumber ;
extern Object *lastObject ;

extern void runClinitFunction(JavaThreadRuntime *rt);

// file system
extern const unsigned char *POB_FILE_FS ;

#endif
