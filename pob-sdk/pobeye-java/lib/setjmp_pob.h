
#ifndef SETJMP_POB_H
#define SETJMP_POB_H


/*
 * All callee preserved registers:
 * v1 - v7, fp, ip, sp, lr, f4, f5, f6, f7
 */
#define _JBLEN 23



typedef	int jmp_buf[_JBLEN];



#define _SAVEMASK	_JBLEN
#define _SIGMASK	(_JBLEN+1)


void longjmp_pob(jmp_buf __jmpb, int __retval);
int	setjmp_pob(jmp_buf __jmpb);

#endif
