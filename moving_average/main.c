#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "arm_math.h"                   // ARM::CMSIS:DSP
#include "signal_plot.h"

#define 	SIG_LEN		320
#define 	FILT_PTS	11

extern void SystemClock_Config(void);
extern float32_t inputSignal_f32_1kHz_15kHz[SIG_LEN];
void moving_average(float32_t *sig_src_arr, float32_t *sig_dest_arr, uint32_t sig_len, uint32_t filter_pts);
float32_t moving_avg_output[SIG_LEN];

void plot_generic_signal(float32_t *signal, float32_t *sample, uint32_t sig_len);
void plot_two_generic_signals(float32_t *signal1,  float32_t *sample1, float32_t *signal2, float32_t *sample2, uint32_t sig_len);

float32_t inputSample;
float32_t outputSample;
uint32_t freq;
int main()
{
	HAL_Init();
	SystemClock_Config();
	freq = HAL_RCC_GetHCLKFreq();
	
	moving_average(&inputSignal_f32_1kHz_15kHz[0], &moving_avg_output[0], SIG_LEN, FILT_PTS);
	
	//plot_generic_signal(&moving_avg_output[0], &outputSample, SIG_LEN);
	//plot_generic_signal(&inputSignal_f32_1kHz_15kHz[0], &inputSample, SIG_LEN);
	
	plot_two_generic_signals(&inputSignal_f32_1kHz_15kHz[0],&inputSample, &moving_avg_output[0], &outputSample, SIG_LEN);
	
	while(1)
	{
		
	}
}

void moving_average(float32_t *sig_src_arr, float32_t *sig_dest_arr, uint32_t sig_len, uint32_t filter_pts)
{
	uint32_t i, j;
	for(i = floor(filter_pts/2); i < ((sig_len - floor(filter_pts/2)) - 1); i++)
	{
		sig_dest_arr[i] = 0.0;
		for(j = -(floor(filter_pts/2)); j < floor(filter_pts/2); j++)
		{
			sig_dest_arr[i] = sig_dest_arr[i] + sig_src_arr[i + j];
		}
		sig_dest_arr[i] = sig_dest_arr[i]/filter_pts;
	}
}

void SysTick_Handler()
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}
