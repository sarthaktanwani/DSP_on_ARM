#include "arm_math.h"

void plot_generic_signal(float32_t *signal, float32_t *sample, uint32_t sig_len);
void plot_two_generic_signals(float32_t *signal1, float32_t *signal2, float32_t *sample1, float32_t *sample2, uint32_t sig_len);

void plot_generic_signal(float32_t *signal, float32_t *sample, uint32_t sig_len)
{
	uint32_t i, j;
	for(i = 0; i < sig_len; i++)
	{
		*sample = signal[i];
		for(j = 0; j < 3000; j++);
	}
}

void plot_two_generic_signals(float32_t *signal1, float32_t *signal2, float32_t *sample1, float32_t *sample2, uint32_t sig_len)
{
	uint32_t i, j;
	for(i = 0; i < sig_len; i++)
	{
		*sample1 = signal1[i];
		*sample2 = signal2[i];
		for(j = 0; j < 3000; j++);
	}
}
