//
// Copyright 2009 POB-Technology. All rights reserved.
//

#ifndef LPC210x_CONFIG_H
#define LPC210x_CONFIG_H

/* Fosc and PLL multiplier */
#define FOSC		10000000		/**< CPU Oscillator in MHz */
#define PLL_M		6				/**< CPU PLL on lcp2103 =6 and on pobeye2=5 */

/** @brief Compute timer value.
 */
#define TIMER_VALUE(delayInUs)		(delayInUs) * ((FOSC * PLL_M)/ (1000000))

/** @brief Enable interrupt.
 */
#define Intr_Enable					(1<<5)

#endif
