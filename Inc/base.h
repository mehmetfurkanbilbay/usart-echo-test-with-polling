/*
 * base.h
 *
 *  Created on: Sep 12, 2026
 *      Author: furka
 */

#ifndef BASE_H_
#define BASE_H_

#define BASE_ADDRESS	(0x40000000UL)
#define APB1_OFFSET		(0x00UL)
#define APB1_BASE 		(BASE_ADDRESS + APB1_OFFSET)
#define APB2_OFFSET		(0x00010000UL)
#define APB2_BASE		(BASE_ADDRESS + APB2_OFFSET)
#define AHB1_OFFSET		(0x00020000UL)
#define AHB1_BASE		(BASE_ADDRESS + AHB1_OFFSET)
#define AHB2_OFFSET		(0x10000000UL)
#define AHB2_BASE		(BASE_ADDRESS + AHB2_OFFSET)
#define NVIC_BASE		(0xE000E100)

#endif /* BASE_H_ */
