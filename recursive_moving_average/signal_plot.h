#ifndef SIGNAL_PLOT_H
  #define SIGNAL_PLOT_H
 #include "arm_math.h"
 
void plot_generic_signal(float32_t *signal, float32_t *sample, uint32_t sig_len);
void plot_two_generic_signals(float32_t *signal1, float32_t *signal2, float32_t *sample1, float32_t *sample2, uint32_t sig_len);


#endif
