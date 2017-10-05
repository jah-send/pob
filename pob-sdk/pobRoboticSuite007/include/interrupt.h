//
// Copyright 2010 POB-Technology. All rights reserved.
// POB-Technology PROPRIETARY/CONFIDENTIAL.
//

#ifdef English_dox
/** \anchor interrupt
 *
 * @brief Manage interrupt.
 *
 * @file
 *
 * Enable or disable the interrupt hardware.
 *
 */
#endif
#ifdef French_dox
/** \anchor interrupt
 *
 * @brief Gestion des interruptions.
 *
 * @file
 *
 * Activer ou désactiber les interruptions matérielles.
 *
 */
#endif

#ifndef RS007_INTR_H
#define RS007_INTR_H

#ifdef __cplusplus
extern "C" {
#endif

#ifdef English_dox
/** @brief Enable interrupt.
 *
 * @return processor register state.
 */
#endif
#ifdef French_dox
/** @brief Activer les interruptions.
 *
 * @return Etat des interruptions au moment de l'activation.
 */
#endif
extern UInt32 enableIRQ(void);

#ifdef English_dox
/** @brief Disable interrupt.
 *
 * @return processor register state.
 */
#endif
#ifdef French_dox
/** @brief Désactiver toutes les interruptions.
 *
 * @return Etat des interruptions au moment de l'arrêt.
 */
#endif

extern UInt32 disableIRQ(void);

#ifdef English_dox
/** @brief Restore interrupt state.
 *
 * @param restore	Old processor state.
 * @return processor register state.
 */
#endif
#ifdef French_dox
/** @brief Restaurer l'état des interruptions.
 *
 * @param restore	Ancien état des interruptions.
 * @return Nouvel état.
 */
#endif
extern UInt32 restoreIRQ(UInt32 restore);

#ifdef __cplusplus
 }
#endif

#endif
