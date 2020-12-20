#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "arm_math.h"                   // ARM::CMSIS:DSP

#define 	SIG_LEN		320

extern void SystemClock_Config(void);
extern float32_t inputSignal_f32_1kHz_15kHz[SIG_LEN];

void plot_input_signal(void);
float32_t signal_mean(float32_t *sig_src_arr, uint32_t length);
float32_t signal_variance(float32_t *sig_src_arr, float32_t sig_mean, uint32_t sig_length);

float32_t inputMean;
float32_t inputVar;
float32_t sample;
uint32_t freq;
int main()
{
	HAL_Init();
	SystemClock_Config();
	freq = HAL_RCC_GetHCLKFreq();
	
	//inputMean = signal_mean((float32_t *) &inputSignal_f32_1kHz_15kHz[0], (uint32_t) SIG_LEN);

	//inputVar = signal_variance((float32_t *)&inputSignal_f32_1kHz_15kHz[0], (float32_t) inputMean, (uint32_t) SIG_LEN);
	
	//arm_mean_f32(&inputSignal_f32_1kHz_15kHz[0],SIG_LEN, &inputMean);
	arm_var_f32(&inputSignal_f32_1kHz_15kHz[0], SIG_LEN, &inputVar);
	
	while(1)
	{
	
		
	}
}

void plot_input_signal()
{
	int i, j;
	for(i = 0; i < SIG_LEN; i++)
	{
		sample = inputSignal_f32_1kHz_15kHz[i];
		for(j=0;j<3000;j++);
	}
	//HAL_Delay(1);
	//for(j=0;j<3000;j++);
}

float32_t signal_mean(float32_t *sig_src_arr, uint32_t length)
{
	float32_t _mean = 0.0;
	uint32_t i;
	for(i = 0; i < length; i++)
	{
		_mean = _mean + sig_src_arr[i];
	}
	_mean /= (float32_t)length;
	
	return _mean;
}

float32_t signal_variance(float32_t *sig_src_arr, float32_t sig_mean, uint32_t sig_length)
{
	float32_t _variance = 0.0;
	uint16_t i;
	for(i = 0; i < SIG_LEN; i++)
	{
		_variance = _variance + pow((sig_src_arr[i]-sig_mean), 2);
	}
	_variance = _variance / (sig_length - 1);
	return _variance;
}

void SysTick_Handler()
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}
