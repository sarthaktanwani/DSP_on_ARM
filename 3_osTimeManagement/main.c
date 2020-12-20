#include "leds.h"
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "stm32f4xx.h"                  // Device header

int32_t count1, count2, count3;
void red_thread(void const *argument)
{
	while(1)
	{
		RED_toggle();
		osDelay(100);
	}
}

void blue_thread(void const *argument)
{
	while(1)
	{
		BLUE_toggle();
		osDelay(100);
	}
}

void green_thread(void const *argument)
{
	while(1)
	{
		GREEN_toggle();
		osDelay(100);
	} 
}

osThreadDef(red_thread, osPriorityNormal, 1, 0);
osThreadDef(blue_thread, osPriorityNormal, 1, 0);
osThreadDef(green_thread, osPriorityNormal, 1, 0);

int main()
{
	LEDs_init();
	osThreadCreate(osThread(red_thread), NULL);
	osThreadCreate(osThread(blue_thread), NULL);
	osThreadCreate(osThread(green_thread), NULL);
	
	while(1)
	{
		
	}
}
