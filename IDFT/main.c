#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "arm_math.h"                   // ARM::CMSIS:DSP

#define 	SIG_LEN		200
#define		IMP_RSP_LEN	29
#define		ECG_LEN		640

extern void SystemClock_Config(void);
extern float32_t inputSignal_f32_1kHz_15kHz[SIG_LEN];
extern float32_t _640_points_ecg_[640];

float32_t REX[ SIG_LEN/2 ];
float32_t IMX[ SIG_LEN/2 ];

float32_t ecg_rex[ ECG_LEN/2 ];
float32_t ecg_imx[ ECG_LEN/2 ];
float32_t is_it_ecg[ ECG_LEN ];

void plot_rex_signal(void);
void plot_ecg_signal(void);
void plot_ecg_rex_signal(void);
void plot_check_ecg_signal(void);
void plot_ecg_check_ecg_signal(void);

void calc_sig_dft(float32_t *sig_src_arr, float32_t *sig_dest_rex_arr, float32_t *sig_dest_imx_arr, uint32_t sig_len);
void calc_sig_idft(float32_t *sig_dest_arr, float32_t *sig_src_rex_arr, float32_t *sig_src_imx_arr, uint32_t sig_len);
void get_dft_output_mag(void);
void get_ecg_dft_output_mag(void);

float32_t inputSample;
float32_t rexSample;
float32_t imxSample;
float32_t ecgSample;
float32_t ecg_rexSample;
float32_t isEcgSample;

uint32_t freq;
int main()
{
	HAL_Init();
	SystemClock_Config();
	freq = HAL_RCC_GetHCLKFreq();
	
	calc_sig_dft(&_640_points_ecg_[0],&ecg_rex[0],&ecg_imx[0],ECG_LEN);
	
	//get_ecg_dft_output_mag();	
	
	//plot_ecg_rex_signal();
	
	calc_sig_idft(&is_it_ecg[0],&ecg_rex[0],&ecg_imx[0],ECG_LEN);
	
	//plot_check_ecg_signal();
	//plot_ecg_signal();
	
	plot_ecg_check_ecg_signal();

	
	
	while(1)
	{
		
	}
}

void calc_sig_idft(float32_t *sig_dest_arr, float32_t *sig_src_rex_arr, float32_t *sig_src_imx_arr, uint32_t sig_len)
{
	uint16_t i, k;
	
	for(k = 1; k < sig_len/2; k++)
	{
		sig_src_rex_arr[k] = sig_src_rex_arr[k]/(sig_len/2);
		sig_src_imx_arr[k] = -sig_src_imx_arr[k]/(sig_len/2);
	}
	sig_src_rex_arr[0] = sig_src_rex_arr[0]/sig_len;
	sig_src_imx_arr[0] = sig_src_imx_arr[0]/sig_len;
	for(i = 0; i < sig_len; i++)
		sig_dest_arr[i] = 0.0;
	
	for(i = 0; i < sig_len; i++)
	{
		for(k = 0; k < sig_len/2; k++)
		{
			sig_dest_arr[i] += sig_src_rex_arr[k] * cos(2*PI*k*i/sig_len) + sig_src_imx_arr[k] * sin(2*PI*k*i/sig_len); 
		}
	}
}

void get_dft_output_mag()
{
	for(uint16_t k = 0; k < SIG_LEN/2; k++)
	{
		REX[k] = fabs(REX[k]);
	}
}

void get_ecg_dft_output_mag()
{
	for(uint16_t k = 0; k < ECG_LEN/2; k++)
	{
		ecg_rex[k] = fabs(ecg_rex[k]);
	}
}

void plot_check_ecg_signal()
{
	uint16_t i, j;
	for(i = 0; i < ECG_LEN; i++) 
	{
		isEcgSample = is_it_ecg[i];
		for(j = 0; j < 3000; j++);
		//if(i == (ECG_LEN - 1))i=0;
	}
}

void plot_ecg_signal()
{
	uint16_t i, j;
	for(i = 0; i < ECG_LEN; i++) 
	{
		ecgSample = _640_points_ecg_[i];
		for(j = 0; j < 3000; j++);
		//if(i == (ECG_LEN - 1))i=0;
	}
}

void plot_ecg_check_ecg_signal()
{
	uint16_t i, j;
	for(i = 0; i < ECG_LEN; i++) 
	{
		ecgSample = _640_points_ecg_[i];
		isEcgSample = is_it_ecg[i];
		for(j = 0; j < 3000; j++);
		if(i == (ECG_LEN - 1))i=0; 
	}
}

void plot_ecg_rex_signal()
{
	uint16_t i, j;
	for(i = 0; i < ECG_LEN/2; i++)
	{
		ecg_rexSample = ecg_rex[i];
		for(j = 0; j < 3000; j++);

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
		for(j = 0; j < 3000; j++);

	}
}

void SysTick_Handler()
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}
