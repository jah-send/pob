//
// Copyright 2009 POB-Technology. All rights reserved.
// POB-Technology PROPRIETARY/CONFIDENTIAL.
//

/** \anchor interrupt
 *
 * @brief Manage interrupt.
 *
 * @file 
 *
 *
 */
#ifndef POB_INTR_H
#define POB_INTR_H

#ifdef __cplusplus
extern "C" {
#endif

/** @brief Enable interrupt.
 *
 * @return processor register state.
 */
extern UInt32 enableIRQ(void);

/** @brief Disable interrupt.
 *
 * @return processor register state.
 */
extern UInt32 disableIRQ(void);

/** @brief Restore interrupt state.
 *
 * @param restore	Old processor state.
 * @return processor register state.
 */
extern UInt32 restoreIRQ(UInt32 restore);

#ifdef __cplusplus
 }
#endif

#endif
