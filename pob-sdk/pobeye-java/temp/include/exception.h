//
// Copyright 2006-2010 POB-Technology. All rights reserved.
// POB-Technology PROPRIETARY/CONFIDENTIAL.
//

/*
 * @brief Exception function
 *
 * @file
 *
 * In original code : ptr protection --> remove it because vm has gc to manage memory.
 *
 * @author Laurent.Deniau@cern.ch and Baptiste Burles POB-Technology
 *
 */
#ifndef EXCEPTION_H
#define EXCEPTION_H

/*
 ******************************
 * Object Oriented Programming in C
 *
 * Author: Laurent Deniau, Laurent.Deniau@cern.ch
 *
 * For more information, please see the paper:
 * http://cern.ch/Laurent.Deniau/html/oopc/exception.html
 *
 ******************************
 */

/* exception code for the arm cpu is integrated in the pob library for correct compile in the POB-TOOLS */
#ifdef VM_LPC2106 /* lpc2106 */
#	include "../lpc2106/setjmp_pob.h"
#	define _save_context_buffer_(context)         setjmp_pob(context)
#	define _restore_context_buffer_(context, val) longjmp_pob(context, val)
#else /* else support libc */
#	include <setjmp.h>
#	define _save_context_buffer_(context)         setjmp(context)
#	define _restore_context_buffer_(context, val) longjmp(context, val)
#endif




/*
  some useful macros
*/

#define _makeConcat_(a,b) a ## b
#define _concat_(a,b) _makeConcat_(a,b)

#define _makeString_(a) # a
#define _string_(a) _makeString_(a)




/*
  some hidden types used to handle exceptions
*/

/* type of stack of exception */
struct _exceptionContext_ {
  struct _exceptionContext_ *next;
  jmp_buf context;
};



extern struct _exceptionContext_ *const _returnExceptionContext_;
extern struct _exceptionContext_ *_currentExceptionContext_;

/* exception keywords */
#define try								 \
  do {									 \
    struct _exceptionContext_ *const _returnExceptionContext0_ =	 \
                                              _returnExceptionContext_;	 \
    struct _exceptionContext_ *const volatile _returnExceptionContext_ = \
                 _returnExceptionContext0_ ? _returnExceptionContext0_:	 \
                                             _currentExceptionContext_;	 \
    struct _exceptionContext_ _localExceptionContext_ =			 \
                                         { _currentExceptionContext_ };	 \
    _currentExceptionContext_ = &_localExceptionContext_;		 \
    (void)_returnExceptionContext_;					 \
    do {								 \
      int const exception =						 \
              _save_context_buffer_(_currentExceptionContext_->context); \
      if (!exception) {

#define catch(except)							\
      } else if ((int)(except) == exception) {				\
        _currentExceptionContext_ = _currentExceptionContext_->next;

#define catch_any							\
      } else {								\
        _currentExceptionContext_ = _currentExceptionContext_->next;

#define endtry								\
      }									\
    } while(0);								\
    if (_currentExceptionContext_ == &_localExceptionContext_) {	\
      _currentExceptionContext_ = _currentExceptionContext_->next;	\
    }									\
  } while(0)

/*
  extern declarations
*/

extern void _exceptionThrow_(int except);

/*
#else // VM_SUPPORT_EXCEPTIONS 
#   define try
#   define catch(except)
#   define catch_any
#   define endtry
#   define throw(e)   
#endif
*/

#ifdef VM_DEBUG_THROW
#	define throw(except) _exceptionThrowDebug_(__FILE__, __LINE__, __func__, _string_(except), (int)(except))
extern void _exceptionThrowDebug_(char const*, int, char const*, char const*,int except);
#else
#	define throw(except) _exceptionThrow_((int)(except))
#endif /* VM_DEBUG_THROW */

#endif
