#include "leds.h"
#include "cmsis_os.h"                   // ARM::CMSIS:RTOS:Keil RTX
#include "stm32f4xx.h"                  // Device header

void orange_Pthread(void const *argument);
void red_thread(void const *argument);
void blue_thread(void const *argument);
void green_thread(void const *argument);

osTimerDef(orange_timer, orange_Pthread);
osTimerId orange_id;

osThreadDef(red_thread, osPriorityNormal, 1, 0);
osThreadDef(blue_thread, osPriorityNormal, 1, 0);
osThreadDef(green_thread, osPriorityNormal, 1, 0);

int main()
{
	LEDs_init();
	osThreadCreate(osThread(red_thread), NULL);
	osThreadCreate(osThread(blue_thread), NULL);
	osThreadCreate(osThread(green_thread), NULL);
	
	orange_id = osTimerCreate(osTimer(orange_timer), osTimerPeriodic, NULL);
	osTimerStart(orange_id, 200);
	
	while(1)
	{
		
	}
}

void orange_Pthread(void const *argument)
{
	while(1)
	{
		ORANGE_toggle();
		osDelay(1000);
	}
}

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
