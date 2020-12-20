#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "arm_math.h"                   // ARM::CMSIS:DSP

#define 	SIG_LEN		250
#define		IMP_RSP_LEN	29

extern void SystemClock_Config(void);
extern float32_t inputSignal_f32_1kHz_15kHz[SIG_LEN];
float32_t result[SIG_LEN];

void plot_input_signal(void);
void plot_imp_response(void);
void plot_result(void);
void plot_both_signal(void);
void calc_running_sum(float32_t *sig_src_arr, float32_t *sig_dest_arr, uint32_t sig_len);

float32_t inputSample;
float32_t imp_resSample;
float32_t resultSample;
float32_t oneSample;
uint32_t freq;
int main()
{
	HAL_Init();
	SystemClock_Config();
	freq = HAL_RCC_GetHCLKFreq();

	calc_running_sum(&inputSignal_f32_1kHz_15kHz[0], &result[0], SIG_LEN);

	plot_both_signal(); 	

	while(1)
	{
	
		
	}
}


void calc_running_sum(float32_t *sig_src_arr, float32_t *sig_dest_arr, uint32_t sig_length)
{
	int16_t i;
	sig_dest_arr[0] = sig_src_arr[0];
	for(i = 1; i < sig_length; i++)
	{
		sig_dest_arr[i] = sig_src_arr[i] + sig_dest_arr[i - 1];
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

void plot_result()
{
	int16_t i, j;
	for(i = 0; i < SIG_LEN; i++)
	{
		resultSample = result[i];
		for(j=0;j<3000;j++);
	}
}

void plot_both_signal()
{
	int16_t i, j;
	for(i = 0; i < SIG_LEN; i++)
	{
		inputSample = inputSignal_f32_1kHz_15kHz[i];
		resultSample = result[i];
		for(j=0;j<3000;j++);
	}
}

void SysTick_Handler()
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}
