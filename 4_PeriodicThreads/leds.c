#include "leds.h"

#define		RED		(1U<<1)
#define		BLUE	(1U<<15)
#define		ORANGE	(1U<<14)
#define		GREEN	(1U<<13)

#define		RED_BIT		(1U<<2)
#define		BLUE_BIT	(1U<<30)
#define		ORANGE_BIT	(1U<<28)
#define		GREEN_BIT	(1U<<26)

#define		GPIOB_CLOCK	(1U<<1)

void LEDs_init(void)
{
	RCC->AHB1ENR |= GPIOB_CLOCK;
	GPIOB->MODER |= RED_BIT | BLUE_BIT | ORANGE_BIT | GREEN_BIT;
}

void RED_toggle()
{
	GPIOB->ODR ^= RED;
}
void BLUE_toggle()
{
	GPIOB->ODR ^= BLUE;
}
void ORANGE_toggle()
{
	GPIOB->ODR ^= ORANGE;
}
void GREEN_toggle()
{
	GPIOB->ODR ^= GREEN;
}
