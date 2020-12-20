#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "arm_math.h"                   // ARM::CMSIS:DSP

#define 	SIG_LEN		320
#define 	IMP_RSP_LEN	29

extern void SystemClock_Config(void);
extern float32_t inputSignal_f32_1kHz_15kHz[SIG_LEN];

float32_t output_signal[IMP_RSP_LEN + SIG_LEN - 1];

void convolution(	float32_t *	sig_src_arr,
					float32_t *	sig_dest_arr,
					float32_t *	imp_response_arr,
					uint32_t	sig_src_length,
					uint32_t	imp_res_length
					);

const float32_t impulse_response[IMP_RSP_LEN] = {
  -0.0018225230f, -0.0015879294f, +0.0000000000f, +0.0036977508f, +0.0080754303f, +0.0085302217f, -0.0000000000f, -0.0173976984f,
  -0.0341458607f, -0.0333591565f, +0.0000000000f, +0.0676308395f, +0.1522061835f, +0.2229246956f, +0.2504960933f, +0.2229246956f,
  +0.1522061835f, +0.0676308395f, +0.0000000000f, -0.0333591565f, -0.0341458607f, -0.0173976984f, -0.0000000000f, +0.0085302217f,
  +0.0080754303f, +0.0036977508f, +0.0000000000f, -0.0015879294f, -0.0018225230f
};

void plot_input_signal(void);
void plot_impulse_response(void);
void plot_output_signal(void);


uint32_t freq;
float32_t inputSample = 0.0, imp_resSample = 0.0, outputSample = 0.0;
int main()
{
	HAL_Init();
	SystemClock_Config();
	freq = HAL_RCC_GetHCLKFreq();
	
	convolution(	(float32_t *)	&inputSignal_f32_1kHz_15kHz[0],
					(float32_t *)	&output_signal[0],
					(float32_t *)	&impulse_response[0],
					(uint32_t)		SIG_LEN,
					(uint32_t)		IMP_RSP_LEN
					);
	
	//plot_input_signal();
	//plot_impulse_response();
	plot_output_signal();
	
	while(1)
	{
	
	}
}

void plot_input_signal()
{
	uint32_t i, j;
	for(i = 0; i < SIG_LEN; i++)
	{
		inputSample = inputSignal_f32_1kHz_15kHz[i];
		for(j=0;j<3000;j++);
	}
}

void plot_impulse_response()
{
	uint32_t i, j;
	for(i = 0; i < IMP_RSP_LEN; i++)
	{
		imp_resSample = impulse_response[i];
		for(j=0;j<3000;j++);
	}
}

void plot_output_signal()
{
	uint32_t i, j;
	for(i = 0; i < (SIG_LEN + IMP_RSP_LEN); i++)
	{
		outputSample = output_signal[i];
		for(j=0;j<3000;j++);
	}
}

void convolution(	
					float32_t *	sig_src_arr,
					float32_t *	sig_dest_arr,
					float32_t *	imp_response_arr,
					uint32_t	sig_src_length,
					uint32_t	imp_res_length
					)
{
	uint32_t i, j;
	for(i = 0; i < (sig_src_length + imp_res_length - 1); i++)
		sig_dest_arr[i] = 0.0;
	for(i = 0; i < (sig_src_length + imp_res_length - 1); i++)
	{
		for(j = 0; j < imp_res_length; j++)
		{
			if((int32_t)(i - j) >= 0)
			sig_dest_arr[i] = sig_dest_arr[i] + imp_response_arr[j] * sig_src_arr[i - j];
		}
	}
}

void SysTick_Handler()
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}
