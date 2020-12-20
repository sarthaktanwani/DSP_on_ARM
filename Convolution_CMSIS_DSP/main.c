#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "arm_math.h"                   // ARM::CMSIS:DSP

#define 	SIG_LEN		320
#define		IMP_RSP_LEN	29

extern void SystemClock_Config(void);
extern float32_t inputSignal_f32_1kHz_15kHz[SIG_LEN];
extern float32_t impulse_response[IMP_RSP_LEN];
float32_t result[SIG_LEN + IMP_RSP_LEN - 1];

void plot_input_signal(void);
void plot_imp_response(void);
void plot_result(void);
void plot_all(void);


float32_t inputSample;
float32_t imp_resSample;
float32_t resultSample;
uint32_t freq;
int main()
{
	HAL_Init();
	SystemClock_Config();
	freq = HAL_RCC_GetHCLKFreq();
		
	arm_conv_f32(	&inputSignal_f32_1kHz_15kHz[0],
					SIG_LEN, 
					&impulse_response[0], 
					IMP_RSP_LEN, 
					&result[0]
				);
	plot_all();
	
	while(1)
	{
	
		
	}
}

void plot_all()
{
	int16_t i, j, g, k;
	for(i = 0, g = 0, k = 0; i < (SIG_LEN + IMP_RSP_LEN - 1); i++, g++, k++)
	{
		
		if(g == (IMP_RSP_LEN - 1)) g = 0; 
		if(k == (SIG_LEN - 1)) k = 0;
		if(i == (SIG_LEN + IMP_RSP_LEN - 2)) i = 0;
		resultSample = result[i];
		imp_resSample = impulse_response[g];
		inputSample = inputSignal_f32_1kHz_15kHz[k];
		for(j=0;j<3000;j++);
	}
	
}

void plot_input_signal()
{
	int i, j;
	for(i = 0; i < SIG_LEN; i++)
	{
		inputSample = inputSignal_f32_1kHz_15kHz[i];
		for(j=0;j<3000;j++);
	}
}

void plot_imp_response()
{
	int16_t i, j;
	for(i = 0; i < IMP_RSP_LEN; i++)
	{
		imp_resSample = impulse_response[i];
		for(j=0;j<3000;j++);
	}
}

void plot_result()
{
	int16_t i, j;
	for(i = 0; i < (SIG_LEN + IMP_RSP_LEN - 1); i++)
	{
		resultSample = result[i];
		for(j=0;j<3000;j++);
	}
}

void SysTick_Handler()
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}
