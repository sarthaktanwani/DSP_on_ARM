#include "stm32f4xx_hal.h"              // Keil::Device:STM32Cube HAL:Common
#include "arm_math.h"                   // ARM::CMSIS:DSP

#define	SIG_LEN		320
#define	NUM_TAPS	29
#define BLOCK_SIZE	32

uint32_t freq;

uint32_t numBlocks = SIG_LEN/BLOCK_SIZE;
extern void SystemClock_Config(void);
extern float32_t inputSignal_f32_1kHz_15kHz[SIG_LEN];
void plot_input_signal(void);
void plot_output_signal(void);
void plot_both_signal(void);

float32_t outputSignal_f32[SIG_LEN];

static float32_t firStateF32[BLOCK_SIZE + NUM_TAPS - 1];

float32_t inputSample, outputSample;

const float32_t firCoeffs32[NUM_TAPS] = {
  -0.0018225230f, -0.0015879294f, +0.0000000000f, +0.0036977508f, +0.0080754303f, +0.0085302217f, -0.0000000000f, -0.0173976984f,
  -0.0341458607f, -0.0333591565f, +0.0000000000f, +0.0676308395f, +0.1522061835f, +0.2229246956f, +0.2504960933f, +0.2229246956f,
  +0.1522061835f, +0.0676308395f, +0.0000000000f, -0.0333591565f, -0.0341458607f, -0.0173976984f, -0.0000000000f, +0.0085302217f,
  +0.0080754303f, +0.0036977508f, +0.0000000000f, -0.0015879294f, -0.0018225230f
};

int main()
{
	int i;
	HAL_Init();
	SystemClock_Config();
	arm_fir_instance_f32 _1KHz_15KHz_sig;
	//freq = HAL_RCC_GetHCLKFreq();
	arm_fir_init_f32(&_1KHz_15KHz_sig, NUM_TAPS, (float32_t *)&firCoeffs32[0], &firStateF32[0], BLOCK_SIZE);
	//the reason why we have to use (float32_t *) typecasting for the firCoeffs32 argument is because it is defined as a constant and constants 
	//are stored in different part of the memory. we can remove the const keyword and the (float32_t *) part of the argument and it 
	//would work perfectly fine
	for(i = 0; i < numBlocks; i++)
	{
		arm_fir_f32(&_1KHz_15KHz_sig, &inputSignal_f32_1kHz_15kHz[0] + (i * BLOCK_SIZE), &outputSignal_f32[0] + (i * BLOCK_SIZE), BLOCK_SIZE);
		
	}
	plot_both_signal();
	
	while(1)
	{
	}
}

void plot_input_signal(void)
{
	int i, j;
	for(i = 0; i < SIG_LEN; i++)
	{
		inputSample = inputSignal_f32_1kHz_15kHz[i];
		for(j = 0; j < 3000; j++);
		if(i == SIG_LEN-1) i=0;
	}
	
}

void plot_output_signal(void)
{
	int i, j;
	for(i = 0; i < SIG_LEN; i++)
	{
		outputSample = outputSignal_f32[i];
		for(j = 0; j < 3000; j++);
		if(i == SIG_LEN-1) i=0;
	}
	
}

void plot_both_signal(void)
{
	int i, j;
	for(i = 0; i < SIG_LEN; i++)
	{
		inputSample = inputSignal_f32_1kHz_15kHz[i];
		outputSample = outputSignal_f32[i];
		for(j = 0; j < 3000; j++);
		if(i == SIG_LEN-1) i=0;
	}
	
}

void SysTick_Handler(void)
{
	HAL_IncTick();
	HAL_SYSTICK_IRQHandler();
}
