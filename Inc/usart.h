/*
 * usart.h
 *
 *  Created on: Sep 12, 2026
 *      Author: furka
 */

#ifndef USART_H_
#define USART_H_

#include <stdint.h>

#include "base.h"
#include "rcc.h"

#define USART2_OFFSET	(0x00004400UL) // APB1
#define USART1_OFFSET	(0x00001000UL) // APB2
#define USART6_OFFSET	(0x00001400UL) // APB2



typedef struct {
	volatile uint32_t SR;
	volatile uint32_t DR;
	volatile uint32_t BRR;
	volatile uint32_t CR1;
	volatile uint32_t CR2;
	volatile uint32_t CR3;
	volatile uint32_t GTPR;
}USART_TypeDef;

#define USART2 ((USART_TypeDef *)(APB1_BASE + USART2_OFFSET))
#define USART1 ((USART_TypeDef *)(APB2_BASE + USART1_OFFSET))
#define USART6 ((USART_TypeDef *)(APB2_BASE + USART6_OFFSET))




#endif /* USART_H_ */
