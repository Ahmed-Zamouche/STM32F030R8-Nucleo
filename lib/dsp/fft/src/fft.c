/*
 * fft.c
 *
 *  Created on: 28 Nov 2017
 *      Author: Ahmed.Z
 */
#include "fft.h"

#if	defined(FFT_IMPL_F32)
#include "fft_f32.h"
#elif defined(FFT_IMPL_Q8_7)
#include "fft_q8_7.h"
#else
#error "FFT_IMPL possible value FFT_IMPL_F32=0 or FFT_IMPL_Q8_7=1"
#endif

__attribute__((always_inline))
static inline void Complex_Add(Complex_t *c, Complex_t *a, Complex_t *b)
{
	c->re = _Add(a->re , b->re);
	c->im = _Add(a->im , b->im);
}

__attribute__((always_inline))
static inline void Complex_Sub(Complex_t *c, Complex_t *a, Complex_t *b)
{
	c->re = _Sub(a->re , b->re);
	c->im = _Sub(a->im , b->im);
}

__attribute__((always_inline))
static inline void Complex_Mul(Complex_t *c, Complex_t *a, Complex_t *b)
{
	c->re = _Sub(_Mul(a->re , b->re) , _Mul(a->im , b->im));
	c->im = _Add(_Mul(a->re , b->im) , _Mul(a->im , b->re));
}

__attribute__((always_inline))
static inline void Complex_Copy(Complex_t *des, Complex_t *src)
{
	des->re = src->re;
	des->im = src->im;
}

__attribute__((always_inline))
static inline void TwiddleFactor(Complex_t *c, size_t k, size_t log_2_n)
{
	size_t i =  k << (LOG_2_FFT_X_N-log_2_n);
	c->re = twiddle_factor_re[i];
	c->im = twiddle_factor_im[i];
}

void fft_recursive(Complex_t *X, size_t log_2_n)
{
	if(log_2_n == 0)
	{
		return;
	}
	size_t log_2_m = (log_2_n - 1);
	size_t m = (1 << log_2_m);
	Complex_t *X_even = X + 0;
	Complex_t *X_odd  = X + m;

	fft_recursive(X_even, log_2_m);
	fft_recursive(X_odd, log_2_m);

	for (int k = 0; k < m; ++k) {

		Complex_t C, X_e, X_o;

		TwiddleFactor(&C, k, log_2_n);

		Complex_Mul(&X_o, &X_odd[k], &C);
		Complex_Copy(&X_e, &X_even[k]);

		Complex_Add(&X[k + 0], &X_e, &X_o);
		Complex_Sub(&X[k + m], &X_e, &X_o);
	}
}

void fft(Complex_t *X)
{
	bit_reversal(X);
	fft_recursive(X, LOG_2_FFT_X_N);
}
