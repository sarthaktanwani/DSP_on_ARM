#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core
#include "timers.h"                     // ARM.FreeRTOS::RTOS:Timers


#define		RED		(1U<<1)
#define		BLUE	(1U<<15)
#define		ORANGE	(1U<<14)
#define		GREEN	(1U<<13)

void GPIO_Init(void);

void vBlueLedControllerTask(void *pvParameters);
void vRedLedControllerTask(void *pvParameters);
void vOrangeLedControllerTask(void *pvParameters);
void vGreenLedControllerTask(void *pvParameters);


int main()
{
	GPIO_Init();
	
	xTaskCreate(
				vBlueLedControllerTask,
				"Blue LED Controller",
				100,
				NULL,
				1,
				NULL
				);
	
	xTaskCreate(
				vRedLedControllerTask,
				"Red LED Controller",
				100,
				NULL,
				1,
				NULL
				);
	
	xTaskCreate(
				vOrangeLedControllerTask,
				"Orange LED Controller",
				100,
				NULL,
				1,
				NULL
				);
				
	xTaskCreate(
				vGreenLedControllerTask,
				"Green LED Controller",
				100,
				NULL,
				1,
				NULL
				);
				
	vTaskStartScheduler();
	
	while(1)
	{
	}
	
}

void vBlueLedControllerTask(void *pvParameters)
{
	while(1)
	{
		//HAL_GPIO_TogglePin(GPIOB, BLUE);
		GPIOB->ODR ^= (1<<15);
		
		for(int i = 0; i < 700000; i++);
	}
}

void vRedLedControllerTask(void *pvParameters)
{
	while(1)
	{
		//HAL_GPIO_TogglePin(GPIOB, RED);
		GPIOB->ODR ^= (1<<1);
		for(int i = 0; i < 700000; i++);
	}
}

void vOrangeLedControllerTask(void *pvParameters)
{
	while(1)
	{
		//HAL_GPIO_TogglePin(GPIOB, ORANGE);
		GPIOB->ODR ^= (1<<14);
		for(int i = 0; i < 700000; i++);
	}
}

void vGreenLedControllerTask(void *pvParameters)
{
	while(1)
	{
		//HAL_GPIO_TogglePin(GPIOB, GREEN);
		GPIOB->ODR ^= (1<<13);
		for(int i = 0; i < 700000; i++);
	}
}

void GPIO_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStruct;
	
	/* GPIO Ports Clock Enable */
	__HAL_RCC_GPIOB_CLK_ENABLE();
	
	/* Configure GPIO pin Output Level */
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_1|GPIO_PIN_15|GPIO_PIN_14|GPIO_PIN_13, GPIO_PIN_RESET);
	
	/* Configure GPIO pins : PB1 PB15 PB14 PB13 */
	GPIO_InitStruct.Pin = GPIO_PIN_1|GPIO_PIN_15|GPIO_PIN_14|GPIO_PIN_13;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_NOPULL;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
}
