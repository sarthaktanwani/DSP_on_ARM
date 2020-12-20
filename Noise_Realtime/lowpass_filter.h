#ifndef __LOWPASS_FILTER_H__
#define __LOWPASS_FILTER_H__
#include "arm_math.h"                   // ARM::CMSIS:DSP

void low_pass_filter_init(void);
q15_t low_pass_filter(q15_t *input);


#endif
