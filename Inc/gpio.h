/*
 * gpio.h
 *
 *  Created on: Sep 12, 2026
 *      Author: furka
 */

#ifndef GPIO_H_
#define GPIO_H_

#include <stdint.h>
#include "base.h"



typedef struct{
	volatile uint32_t MODER;
	volatile uint32_t OTYPER;
	volatile uint32_t OSPEEDR;
	volatile uint32_t PUPDR;
	volatile uint32_t IDR;
	volatile uint32_t ODR;
	volatile uint32_t BSRR;
	volatile uint32_t LCKR;
	volatile uint32_t AFRL;
	volatile uint32_t AFRH;
}GPIO_TypeDef;

// GPIOx (A,B,C..) pointer'e cevir

#define GPIOA 	((GPIO_TypeDef *)(AHB1_BASE + 0x00UL))
#define GPIOB	((GPIO_TypeDef *)(AHB1_BASE + 0x00000400UL))
#define GPIOC	((GPIO_TypeDef *)(AHB1_BASE + 0x00000800UL))
#define GPIOD	((GPIO_TypeDef *)(AHB1_BASE + 0x00000C00UL))
#define GPIOE	((GPIO_TypeDef *)(AHB1_BASE + 0x00001000UL))
#define GPIOH	((GPIO_TypeDef *)(AHB1_BASE + 0x00001C00UL))

#endif /* GPIO_H_ */
