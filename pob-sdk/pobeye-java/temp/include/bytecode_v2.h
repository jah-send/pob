//
// Copyright 2006-2010 POB-Technology. All rights reserved.
// POB-Technology PROPRIETARY/CONFIDENTIAL.
//

/*
 * @brief Bytecode macro.
 *
 * @file
 *
 * All of this macro represent a java bytecode in the pob vm.
 * This is the version 2 of the file. All opcode definition has moved to Bytecode.cpp.
 *
 * @author Baptiste Burles. POB-Technology
 *
 */
#ifndef BYTECODE_H
#define BYTECODE_H

#include "memory.h"


/* interpreter debug */
#define TRACE_INT(str) TRACE(str)



/*
 * push/pop for 64 bits
 */
static void FUNC_INLINE COPY64(RuntimeVar *src, RuntimeVar *dest)
{
   *dest = *src;
   *(dest+1) = *(src+1);
}


#ifdef VM_SUPPORT_64_BITS
	#define PUSHOPD( value )	COPY64(value,opstack); opstack +=2;
	#define PUSHOPL( value )	COPY64(value,opstack); opstack +=2;

	#define POPOPD( value )     opstack -= 2; COPY64(opstack,value);
	#define POPOPL( value )     opstack -= 2; COPY64(opstack,value);
#else
	#define PUSHOPD( value )	 
	#define PUSHOPL( value )	 

	#define POPOPD( value )       
	#define POPOPL( value )      
#endif


/*  the save frame store the state of the JavaThreadRuntime when jump to method.
 *
 *   save frame format :
 *
 *    +----------------+ 
 *    ! old save frame ! 
 *    .                .
 *    .                .
 *    !                !
 *    +----------------+ 
 *    ! operand stack  ! <- save frame
 *    +----------------+
 *    !                ! <- next free save frame
 *    .                .
 *    .                .
 *    !                !
 *    +----------------+
 *
 * 2 macros manipulated the save frame : 
 *    PUSH_FRAME to store JavaThreadRuntime states.
 *    POP_FRAME to restore JavaThreadRuntime state.
 *
 */

#define FRAME_SAVE_SIZE 1  /* size of save frame */

/* 
 * pop previous frame.
 *
 */

#define POP_FRAME   frame_save-- ; \
                    lvar     = (RuntimeVar *)((frame_save)->ref) ;\
                    rt->lvar = lvar ; rt->save = frame_save ;


/*
 * save current frame
 *
 */
#define PUSH_FRAME   frame_save = rt->save ; \
                     frame_save->ref = (RuntimeVar *)lvar ; frame_save++ ;\
					 rt->save = frame_save ;


/* 
 * restore execution (after a method invocation)
 *
 */
#define RESTORE    DEC_ROOT;


/* 
 * before call a method, set correct lvar stack and gc root
 *
 */
#define INVOKE(lsize)  INC_ROOT rt->lvar = lvar ; 


/* 
 * global variable. WARNING : all java thread share this variable !
 *
 */
#define GLOBAL_VAR     Object *obj ; u4 dup_value ;

/*
 * global 64 bits variable.
 *
 */
#ifdef VM_SUPPORT_64_BITS
#	define GLOBAL_VAR_64  s8 la,lb ; float64 da,db ; s8 lresult ;
#else
#	define GLOBAL_VAR_64
#endif

/*  
// Get integer 64 bits : v is a 64 bits
#define GET64(v, op)      v = *(s8 *)(op)
// Get float 64 bits
#define GETFLOAT64(v, op) v = *(float64 *)(op)
*/


/*
 * Opcode definition. 29/11/2005 : currently pob-vm not support 64 bits operations
 *
 */


// No operation
#define code_nop          

#define code_aconst_null  PUSHOPI(0); 

// Push constant to operand stack :

#define code_lconst_0     la = 0 ; PUSHOPL((RuntimeVar *)&la ); 
#define code_lconst_1     la = 1 ; PUSHOPL((RuntimeVar *)&la ); 
#define code_dconst_0     da = 0.0 ; PUSHOPD((RuntimeVar *)&da ); 
#define code_dconst_1     da = 1.0 ; PUSHOPD((RuntimeVar *)&da );
                         

/* 
 * push constant pool 
 */

#define code_ldc_string(cl,str,len,ia) obj = allocString(&cl,str,len); ia.ref = obj ;

#define code_ldc_w_string(cl,str,len,ia)   code_ldc_string(cl,str,len,ia)

// todo : code_lcd_w_class : Class support

#define code_ldc2_w_long(value)   la = value ; PUSHOPL((RuntimeVar *)&la );

#define code_ldc2_w_double(value) da = value ; PUSHOPD( (RuntimeVar *)&da );



#define code_lload(value)  PUSHOPL((RuntimeVar *)&lvar[value]); 
#define code_dload(value)  PUSHOPD((RuntimeVar *)&lvar[value]); 

#define code_lload_0       PUSHOPL((RuntimeVar *)&lvar[0]);
#define code_lload_1       PUSHOPL((RuntimeVar *)&lvar[1]);
#define code_lload_2       PUSHOPL((RuntimeVar *)&lvar[2]);
#define code_lload_3       PUSHOPL((RuntimeVar *)&lvar[3]);

#define code_dload_0       PUSHOPD((RuntimeVar *)&lvar[0]);
#define code_dload_1       PUSHOPD((RuntimeVar *)&lvar[1]);
#define code_dload_2       PUSHOPD((RuntimeVar *)&lvar[2]);
#define code_dload_3       PUSHOPD((RuntimeVar *)&lvar[3]);


/* Push value from long/double array : not yet implemented
*
*/

#define code_laload       { POPOPI(ia) ; POPOPA(uia) ;\
                            if( ia < 0 || (u4)ia > ObjStack[uia].lenght ){ errorCode = ERR_OUT_OF_BOUNDS; goto exit;}\
                            PUSHOPL((RuntimeVar *)&ObjStack[uia].data[ia]) ; }

#define code_daload       { POPOPI(ia) ; POPOPA(uia) ;\
                            if( ia < 0 || (u4)ia > ObjStack[uia].lenght ){ errorCode = ERR_OUT_OF_BOUNDS; goto exit;}\
                            PUSHOPD((RuntimeVar *)&ObjStack[uia].data[ia]) ; }

// macro to set root_index in astore opcode
#define FREE_OBJ_ASTORE(ops,indice) obj = ops.ref ;\
                                   if( obj != objectStack ){\
                                    if( obj->root_index >= root_index){\
                                      TRACE_INT(("set 0x%p root %d to %d lvar at 0x%p\n", obj,obj->root_index, root_index,lvar ));\
                                      obj->root_index = root_index; }\
                                     gc1(obj, lvar[indice].ref );}


#define code_lstore_0       POPOPL( (RuntimeVar *)&lvar[0] );
#define code_lstore_1       POPOPL( (RuntimeVar *)&lvar[1] );
#define code_lstore_2       POPOPL( (RuntimeVar *)&lvar[2] );
#define code_lstore_3       POPOPL( (RuntimeVar *)&lvar[3] );

#define code_dstore_0       POPOPD( (RuntimeVar *)&lvar[0] );
#define code_dstore_1       POPOPD( (RuntimeVar *)&lvar[1] );
#define code_dstore_2       POPOPD( (RuntimeVar *)&lvar[2] );
#define code_dstore_3       POPOPD( (RuntimeVar *)&lvar[3] );

#define code_dastore        { POPOPD((RuntimeVar *)&da) ;  POPOPA(ib); POPOPA(uia);\
                            if( ia < 0 || (u4)ia > ObjStack[uia].lenght ){ errorCode = ERR_OUT_OF_BOUNDS; goto exit;}\
                            COPY64( (RuntimeVar *)&da, &ObjStack[uia].data[ib] ) ; }

#define code_lastore        { POPOPL((RuntimeVar *)&la) ;  POPOPA(ib); POPOPA(uia);\
                            if( ia < 0 || (u4)ia > ObjStack[uia].lenght ){ errorCode = ERR_OUT_OF_BOUNDS; goto exit;}\
                            COPY64( (RuntimeVar *)&la, &ObjStack[uia].data[ib] ) ; }


// Operand stack operation/manipulation

/*
#define code_dup_x1         value = (opstack-1)->data; \
                            (opstack-1)->data = (opstack-2)->data;\
                            (opstack-2)->data = value ; PUSHOPA(value);

#define code_dup_x2         value = (opstack-1)->data; (opstack-1)->data = (opstack-2)->data;\
                            (opstack-2)->data = (opstack-3)->data; (opstack-3)->data = value;\
                            PUSHOPA(value); 

#define code_dup2           PUSHOPA((opstack-2)->data); PUSHOPA((opstack-2)->data);

#define code_dup2_x1        PUSHOPA( (opstack-2)->data); PUSHOPA( (opstack-2)->data);\
                              (opstack-3)->data = (opstack-5)->data; (opstack-5)->data = (opstack-2)->data;\
                              (opstack-4)->data = (opstack-1)->data; 

#define code_dup2_x2        PUSHOPA((opstack-2)->data); PUSHOPA((opstack-2)->data);\
                              (opstack-4)->data = (opstack-6)->data; (opstack-3)->data = (opstack-5)->data;\
                              (opstack-6)->data = (opstack-2)->data; (opstack-5)->data = (opstack-1)->data; 

#define code_swap           value = (opstack-2)->data; (opstack-2)->data = (opstack-1)->data; (opstack-1)->data = value ;
*/


#define code_ladd         POPOPL((RuntimeVar *)&la);POPOPL((RuntimeVar *)&lb);\
                            la += lb ; PUSHOPL((RuntimeVar *)&la);

#define code_dadd         POPOPD((RuntimeVar *)&da);POPOPD((RuntimeVar *)&db);\
                            da += db ; PUSHOPL((RuntimeVar *)&da);

#define code_lsub         POPOPL((RuntimeVar *)&la);POPOPL((RuntimeVar *)&lb);\
	                        lb -= la ; PUSHOPL((RuntimeVar *)&lb);

#define code_dsub         POPOPD((RuntimeVar *)&da);POPOPD((RuntimeVar *)&db);\
	                        db -= da ; PUSHOPD((RuntimeVar *)&db);

#define code_lmul         POPOPL((RuntimeVar *)&la);POPOPL((RuntimeVar *)&lb);\
	                        lb *= la ; PUSHOPL((RuntimeVar *)&lb);

#define code_dmul         POPOPD((RuntimeVar *)&da);POPOPD((RuntimeVar *)&db);\
	                        db *= da ; PUSHOPD((RuntimeVar *)&db);

#define code_ldiv         POPOPL((RuntimeVar *)&la);\
							if( la == 0 ) { errorCode = ERR_DIV_BY_0 ; goto exit ;}\
	                        POPOPL((RuntimeVar *)&lb);\
	                        lb *= la ; PUSHOPL((RuntimeVar *)&lb); 

#define code_ddiv         POPOPD((RuntimeVar *)&da);\
							if( da == 0 ) { errorCode = ERR_DIV_BY_0 ; goto exit ;}\
	                        POPOPD((RuntimeVar *)&db);\
	                        db *= da ; PUSHOPD((RuntimeVar *)&db);



#define code_lrem         POPOPL((RuntimeVar *)&lb);\
                            if( lb == 0 ){ errorCode = ERR_DIV_BY_0 ; goto exit; }\
                            POPOPL((RuntimeVar *)&la);\
							lresult = la - (la/lb)*lb ;\
							PUSHOPL((RuntimeVar *)&lresult);

#define code_drem          POPOPD((RuntimeVar *)&db);\
                            if( db == 0.0f ){ errorCode = ERR_DIV_BY_0 ; goto exit;}\
							POPOPD((RuntimeVar *)&da);\
							dresult = da - ((float64)((s8)(da / db))) * db;\
                            PUSHOPD((RuntimeVar *)&dresult);
  
#define code_lneg         POPOPL((RuntimeVar *)&lb); lb -= lb ; PUSHOPL((RuntimeVar *)&lb);  
#define code_dneg         POPOPD((RuntimeVar *)&db); db -= db ; PUSHOPD((RuntimeVar *)&db);  


#define code_lshl         POPOPI(ia); POPOPL((RuntimeVar *)&la);\
                            la = la << ia ;\
                            PUSHOPL((RuntimeVar *)&la );

#define code_lshr         POPOPI(ia); POPOPL((RuntimeVar *)&la);\
	                        lresult = la >> ia ;\
                            PUSHOPL((RuntimeVar *)&lresult );

#define code_lushr        POPOPI(ia); POPOPL((RuntimeVar *)&la);\
                            if( la > 0 ) { lresult = la >> (ia&0x3F) ;}\
                            else { lresult = (la >> (ia&0x3F)) + (2<<~(ia&0x3F));}\
                            PUSHOPL((RuntimeVar *)&lresult ); 

#define code_land         POPOPL((RuntimeVar *)&la);POPOPL((RuntimeVar *)&lb); lb &= la ; PUSHOPL((RuntimeVar *)&lb);
#define code_lor          POPOPL((RuntimeVar *)&la);POPOPL((RuntimeVar *)&lb);\
                          lb |= la ; PUSHOPL((RuntimeVar *)&lb);
#define code_lxor         POPOPL((RuntimeVar *)&la);POPOPL((RuntimeVar *)&lb);\
	                      lb ^= la ; PUSHOPL((RuntimeVar *)&lb);


#define code_iinc(v1,v2)    lvar[v1].integer += (s4)v2 ;


// Comparisons :
#define code_lcmp      { POPOPL((RuntimeVar *)&lb);\
                         POPOPL((RuntimeVar *)&la);\
                         if( la > lb ){ PUSHOPI( 1 ); }\
                         else if( la == lb ){ PUSHOPI(0);}\
                         else { PUSHOPI(-1);}\
                         \
                       }


// NaN not implemented : if NaN push -1
#define code_dcmpl      { POPOPD((RuntimeVar *)&db);\
                          POPOPD((RuntimeVar *)&da);\
                          if( da > db ){ PUSHOPI( 1 ); }\
                          else if( da == db ){ PUSHOPI(0);}\
                          else { PUSHOPI(-1);}\
                          \
                        }

// NaN not implemented : if NaN push 1
#define code_dcmpg      code_dcmpl


/* 
 * Branch comparisons
 *
 */
#define code_ifeq(bytecode, ia )  if( ia == 0 ){ goto bytecode;} 

#define code_ifne(bytecode, ia )  if( ia != 0 ){ goto bytecode;} 

#define code_iflt(bytecode, ia )  if( ia < 0 ) { goto bytecode;} 

#define code_ifle(bytecode, ia )  if( ia <= 0 ){ goto bytecode;} 

#define code_ifge(bytecode, ia )  if( ia >= 0 ){ goto bytecode;} 

#define code_ifgt(bytecode, ia )  if( ia > 0 ) { goto bytecode;} 


/*
 * Branch comparisons between 2 values
 *
 */
#define code_if_icmpeq(bytecode,ia,ib) if( ia == ib ){ goto bytecode;}
                            
#define code_if_icmpne(bytecode,ia,ib) if( ia != ib ){ goto bytecode;} 

#define code_if_icmple(bytecode,ia,ib) if( ia <= ib ){ goto bytecode;}
                            
#define code_if_icmplt(bytecode,ia,ib) if( ia < ib ) { goto bytecode;}
                            
#define code_if_icmpge(bytecode,ia,ib) if( ia >= ib ){ goto bytecode;}

#define code_if_icmpgt(bytecode,ia,ib) if( ia > ib ) { goto bytecode;}
                            
#define code_if_acmpeq(bytecode,ia,ib) if( ia == ib ){ goto bytecode;}
                           
#define code_if_acmpne(bytecode,ia,ib) if( ia != ib ){ goto bytecode;}

#define code_ifnull(bytecode,ia)    if( (Object *)ia == objectStack ){ goto bytecode;} 

#define code_ifnonnull(bytecode,ia) if( (Object *)ia != objectStack ){ goto bytecode;}
                            
/* 
 * jump
 *
 */
#define code_goto(bytecode)    goto bytecode ;
#define code_goto_w(bytecode)  goto bytecode ;

#define code_jsr(bytecode)     goto bytecode ;
#define code_jsr_w(bytecode)   goto bytecode ;


/* 
 * return from method (return int,long,float,double, reference or void) 
 *
 */
#define code_ireturn(ia)    rt->return_value.integer = ia.integer ; rt->return_ok=1 ; return ;

#define code_freturn(fa)    rt->return_value.real = fa.real ; rt->return_ok=1 ; return ;

#define code_areturn(aa)    rt->return_value.data = aa.data ; rt->return_ok=1 ; return ;


#define code_lreturn    CALL_GC POPOPL((RuntimeVar *)&la);\
                        POP_FRAME PUSHOPL((RuntimeVar *)&la); rt->opstack = opstack;

#define code_dreturn    CALL_GC POPOPD((RuntimeVar *)&da);POP_FRAME \
						PUSHOPD((RuntimeVar *)&da); rt->opstack = opstack;


#define code_return         run_gc(); return ;   
#define code_return_special  return ;


#define code_getstatic_64bits(field)
#define code_getfield64()       
#define code_putfield64(offset,type)
#define code_putstatic_64(field) POPOPL((RuntimeVar *)&la); COPY64((RuntimeVar *)&la,field);


/* invoke a method :
 *  all the parameter are build by Bytecode.cpp
 *
 */
#define code_invokestatic(me,cl,i,pnumber,lsize,op ) INVOKE(lsize) me(rt); POP_FRAME RESTORE
                                    
// if( rt->return_ok == 1 ) {rt->return_ok = 0 ; op.data = rt->return_value.data ;}
#define code_invokestatic_return(me,cl,i,pnumber,lsize,op )  code_invokestatic(me,cl,i,pnumber,lsize,op ) rt->return_ok = 0 ; op.data = rt->return_value.data ;

/*
 * invoke a natif method
 *
 */
#define code_invokestatic_natif(me,cl,i,pnumber,lsize,op)         code_invokestatic(me,cl,i,pnumber,lsize,op )
#define code_invokestatic_natif_return(me,cl,i,pnumber,lsize,op)  code_invokestatic_return(me,cl,i,pnumber,lsize,op)

/*
 * invoke a constructor method
 *
 */
#define code_invokespecial(me,cl,i,pnumber,lsize,opsize)  TRACE_INT(("Call to a contructor param number %d\n", pnumber )); code_invokestatic(me,cl,i,pnumber,lsize,opsize) 

/*
 * invoke an object method
 *
 */
#define code_invokevirtual(me,cl,i,pnumber,lsize,op)               code_invokestatic(me,cl,i,pnumber,lsize,op)
#define code_invokevirtual_return(me,cl,i,pnumber,lsize,op)        code_invokestatic_return(me,cl,i,pnumber,lsize,op)
#define code_invokevirtual_natif(me,cl,i,pnumber,lsize,op)         code_invokestatic_natif(me,cl,i,pnumber,lsize,op)
#define code_invokevirtual_natif_return(me,cl,i,pnumber,lsize,op)  code_invokestatic_natif_return(me,cl,i,pnumber,lsize,op)


// todo invoke an interface
#define code_invokeinterface 

/*
 * create a new object
 *
 */
#define code_new(c,size,ia)  allocObject(&c,size ); ia.ref = lastObject ; 

/* 
 * create a new primitive array
 *
 */
#define code_newarray(size,ia) allocArray( ia.integer * size ); lastObject->size_of_array = ia.integer ; ia.ref = lastObject; 


/*
 * create a new array of object
 *
 */
#define code_anewarray(c, size,ia )  obj = allocObjectArray(&c, ia.integer,size); ia.ref = obj ; 

  

/* Create a mutildimensionnal array
*
*/
#define code_multianewarray { usa = (*(bytecode+1)<<8) | *(bytecode+2);\
                              ba = *(bytecode+3); INCI(4);\
							  uia = GETCLASSINDEX(current_c->constant_pool[usa]) ;\
							  TRACE_INT((" code_multianewarray Multi Array index %d dimension %d\n", usa, ba));\
							  opstack -= ba ;\
							  ib = AllocObjectMultiArray(uia,ba,(u4 *)opstack,ObjPtr,&ObjNb);\
							  ObjPtr[ObjNb] = ib; ObjNb++;\
							  PUSHOPA(ib);\
							}


/* 
 * throw exception
 * Note : 29/11/2005 : pob-vm support only one catch, no exception filter
 */
#define code_athrow(aa)        rt->return_value.data = aa.data ; rt->return_ok=1 ; throw(0);


#define code_checkcast     { usa = (*(bytecode+1)<<8) | *(bytecode+2);\
							 TRACE_INT(("************** WARNING code_checkcast NOT IMPLEMENTED !\n"));\
						   }


/* 
 * Synchronized access 
 *
 */
#define code_monitorenter  

#define code_monitorexit   

//todo wide
#define code_wide          uba = *(bytecode+1); switch(uba)\
							 {\
                                 case opcode_iinc :\
                                     usa = (*(bytecode+2)<<8) | *(bytecode+3);\
                                     usb = (*(bytecode+4)<<8) | *(bytecode+5);\
									\
									 lvar[usa].integer += (s4)usb ; break;\
								case opcode_iload :\
								    usa = (*(bytecode+2)<<8) | *(bytecode+3);\
								    PUSHOPI(lvar[usa].integer );\
									 break;\
								case opcode_fload :\
								    usa = (*(bytecode+2)<<8) | *(bytecode+3);\
								    PUSHOPF(lvar[usa].real );\
									break;\
								case opcode_aload :\
								    usa = (*(bytecode+2)<<8) | *(bytecode+3);\
								    PUSHOPA(lvar[usa].data );\
									break;\
								case opcode_lload :\
                                     usa = (*(bytecode+2)<<8) | *(bytecode+3);\
								     PUSHOPL((RuntimeVar *)&lvar[usa]); \
									 break;\
								case opcode_dload :\
                                     usa = (*(bytecode+2)<<8) | *(bytecode+3);\
								     PUSHOPD((RuntimeVar *)&lvar[usa]); \
									 break;\
								case opcode_istore :\
								     usa = (*(bytecode+2)<<8) | *(bytecode+3);\
                                     POPOPI( lvar[usa].integer); break;\
								case opcode_fstore :\
								     usa = (*(bytecode+2)<<8) | *(bytecode+3);\
                                     POPOPF( lvar[usa].real); break;\
								case opcode_astore :\
								     usa = (*(bytecode+2)<<8) | *(bytecode+3);\
                                     POPOPA( lvar[usa].data); break;\
								case opcode_lstore :\
								     usa = (*(bytecode+2)<<8) | *(bytecode+3);\
								     POPOPL( (RuntimeVar *)&lvar[usa]);\
									 break;\
								case opcode_dstore :\
								     usa = (*(bytecode+2)<<8) | *(bytecode+3);\
								     POPOPD( (RuntimeVar *)&lvar[usa]);\
									 break;\
								case opcode_ret :\
                                     usa = (*(bytecode+2)<<8) | *(bytecode+3);\
								     uba = (u1)lvar[usa].vb; INCI(uba);\
							 }
						  


#endif

