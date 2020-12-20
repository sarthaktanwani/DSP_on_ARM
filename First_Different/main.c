#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "arm_math.h"                   // ARM::CMSIS:DSP

#define 	SIG_LEN		200
#define		IMP_RSP_LEN	29

extern void SystemClock_Config(void);
extern float32_t inputSignal_f32_1kHz_15kHz[SIG_LEN];

float32_t REX[ SIG_LEN/2 ];
float32_t IMX[ SIG_LEN/2 ];

void plot_rex_signal(void);

void plot_input_signal(void);
void plot_imp_response(void);
void plot_result(void);
void plot_both_signal(void);
void calc_running_sum(float32_t *sig_src_arr, float32_t *sig_dest_arr, uint32_t sig_len);
void calc_first_difference(float32_t *sig_src_arr, float32_t *sig_dest_arr, uint32_t sig_length);
void calc_sig_dft(float32_t *sig_src_arr, float32_t *sig_dest_rex_arr, float32_t *sig_dest_imx_arr, uint32_t sig_len);
void get_dft_output_mag(void);

float32_t inputSample;
float32_t rexSample;
float32_t imxSample;
float32_t oneSample;

uint32_t freq;
int main()
{
	HAL_Init();
	SystemClock_Config();
	freq = HAL_RCC_GetHCLKFreq();

	calc_sig_dft((float32_t *)&inputSignal_f32_1kHz_15kHz[0], (float32_t *)&REX[0], (float32_t *)&IMX[0], (uint32_t) SIG_LEN);
	
	get_dft_output_mag();
	
	plot_rex_signal();
	
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

void calc_first_difference(float32_t *sig_src_arr, float32_t *sig_dest_arr, uint32_t sig_length)
{
	int16_t i;
	for(i = 1; i < sig_length; i++)
	{
		sig_dest_arr[i] = sig_src_arr[i] - sig_src_arr[i - 1];
	}
}

void get_dft_output_mag()
{
	for(uint16_t k = 0; k < SIG_LEN/2; k++)
	{
		REX[k] = fabs(REX[k]);
	}
}

void calc_sig_dft(float32_t *sig_src_arr, float32_t *sig_dest_rex_arr, float32_t *sig_dest_imx_arr, uint32_t sig_len)
{
	uint16_t i, k, j;
	for(j = 0; j < sig_len/2; j++)
	{
		sig_dest_rex_arr[j] = 0.0;
		sig_dest_imx_arr[j] = 0.0;
	}
	for(k = 0; k < sig_len/2; k++)
	{
		for(i = 0; i < sig_len; i++)
		{
			sig_dest_rex_arr[k] += sig_src_arr[i]*cos(2*PI*k*i/sig_len);
			sig_dest_imx_arr[k] -= sig_src_arr[i]*sin(2*PI*k*i/sig_len);
		}
	}
}

void plot_rex_signal()
{
	uint16_t i, j;
	for(i = 0; i < SIG_LEN/2; i++)
	{
		rexSample = REX[i];
		//imxSample = IMX[i];
		for(j = 0; j < 3000; j++);

	}
}

void SysTick_Handler()
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}
