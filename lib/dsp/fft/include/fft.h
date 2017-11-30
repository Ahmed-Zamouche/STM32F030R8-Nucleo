/*
 * fft.h
 *
 *  Created on: 28 Nov 2017
 *      Author: Ahmed.Z
 */

#ifndef INC_FFT_H_
#define INC_FFT_H_

#include <stddef.h>

#if	defined(FFT_IMPL_F32)
#include "fft_f32.h"
#elif defined(FFT_IMPL_Q8_7)
#include "fft_q8_7.h"
#else
#error "FFT_IMPL possible value FFT_IMPL_F32=0 or FFT_IMPL_Q8_7=1"
#endif


/* GENERATED CODE BEGIN */
#define LOG_2_FFT_X_N (8)
/* GENERATED CODE END*/

#define FFT_X_N	(1<<LOG_2_FFT_X_N)

void fft(Complex_t *X);

#endif /* INC_FFT_H_ */
