#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "arm_math.h"                   // ARM::CMSIS:DSP

#define 	SIG_LEN		320
#define		IMP_RSP_LEN	29

extern void SystemClock_Config(void);					//but i'll just add the keyword for safety
extern float32_t inputSignal_f32_1kHz_15kHz[SIG_LEN];	//extern keyword not needed for functions i suppose, only needed for arrays and variables

float32_t REX[ SIG_LEN/2 ];
float32_t IMX[ SIG_LEN/2 ];

float32_t mag[ SIG_LEN/2 ];
float32_t phase[ SIG_LEN/2 ];

void plot_rex_signal(void);

void plot_input_signal(void);
void plot_imp_response(void);
void plot_result(void);
void plot_both_signal(void);
void calc_running_sum(float32_t *sig_src_arr, float32_t *sig_dest_arr, uint32_t sig_len);
void calc_first_difference(float32_t *sig_src_arr, float32_t *sig_dest_arr, uint32_t sig_length);
void calc_sig_dft(float32_t *sig_src_arr, float32_t *sig_dest_rex_arr, float32_t *sig_dest_imx_arr, uint32_t sig_len);
void get_dft_output_mag(void);
void Rect_to_Polar(float32_t *src_rex_arr, float32_t *src_imx_arr, float32_t *dest_mag_arr, float32_t *dest_phase_arr, uint32_t sig_len);

extern void plot_generic_signal(float32_t *signal, float32_t *sample, uint32_t sig_len);
extern void plot_two_generic_signals(float32_t *signal1, float32_t *signal2, float32_t *sample1, float32_t *sample2, uint32_t sig_len);

float32_t inputSample;
float32_t rexSample;
float32_t imxSample;
float32_t oneSample;
float32_t magSample;
float32_t phaseSample;

uint32_t freq;
int main()
{
	HAL_Init();
	SystemClock_Config();
	freq = HAL_RCC_GetHCLKFreq();

	calc_sig_dft((float32_t *)&inputSignal_f32_1kHz_15kHz[0], (float32_t *)&REX[0], (float32_t *)&IMX[0], (uint32_t) SIG_LEN);
	
	//get_dft_output_mag();
	
	//plot_rex_signal();
	//plot_generic_signal(&REX[0], &rexSample, SIG_LEN/2);
	
	Rect_to_Polar(&REX[0], &IMX[0], &mag[0], &phase[0], SIG_LEN);
	
	plot_two_generic_signals(&mag[0],&phase[0],&magSample,&phaseSample,SIG_LEN/2);
	
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

void Rect_to_Polar(float32_t *src_rex_arr, float32_t *src_imx_arr, float32_t *dest_mag_arr, float32_t *dest_phase_arr, uint32_t sig_len)
{
	uint32_t k;
	for(k = 0; k < sig_len; k++)
	{
		dest_mag_arr[k] 	= sqrt(powf(src_rex_arr[k],2) + powf(src_imx_arr[k],2));
		if(src_rex_arr[k] == 0)src_rex_arr[k] = pow(10, -20);		//just to separate out anomalies as stated by video guy
		dest_phase_arr[k] 	= atan(src_imx_arr[k]/src_rex_arr[k]);
			if((src_rex_arr[k] < 0) && (src_imx_arr[k] < 0)) dest_phase_arr[k] -= PI;
				if((src_rex_arr[k] < 0) && (src_imx_arr[k] >= 0)) dest_phase_arr[k] += PI;
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
