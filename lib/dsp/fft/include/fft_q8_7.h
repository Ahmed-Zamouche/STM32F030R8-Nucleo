/*
 * fft_q8_7.h
 *
 *  Created on: 27 Nov 2017
 *      Author: Ahmed.Z
 */

#ifndef INC_FFT_Q8_7_H_
#define INC_FFT_Q8_7_H_

#include <stdint.h>

/**
 * @see http://www.artist-embedded.org/docs/Events/2009/EmbeddedControl/SLIDES/FixPoint.pdf
 */

typedef int16_t Q8_7_t;
typedef int32_t Q16_14_t;

#define Q8_7_MAX INT16_MAX
#define Q8_7_MIN INT16_MIN

#define Q8_7_SHIFT	(7)

typedef struct Complex_s{
	Q8_7_t re;
	Q8_7_t im;
}Complex_t;

typedef struct Polar_s{
	Q8_7_t amp;
	Q8_7_t phase;
}Polar_t;

__attribute__((always_inline))
static inline Q8_7_t _Add(Q8_7_t a, Q8_7_t b) {
	Q8_7_t c;
	Q16_14_t temp;

	temp = (Q16_14_t) a + b;

	if (temp > Q8_7_MAX)		/*saturate the result before assignment*/
		c = Q8_7_MAX;
	else if (temp < Q8_7_MIN)
		c = Q8_7_MIN;
	else
		c = temp;
	return c;
}

__attribute__((always_inline))
static inline Q8_7_t _Sub(Q8_7_t a, Q8_7_t b) {
	Q8_7_t c;
	Q16_14_t temp;

	temp = (Q16_14_t) a - b;

	if (temp > Q8_7_MAX)		/*saturate the result before assignment*/
		c = Q8_7_MAX;
	else if (temp < Q8_7_MIN)
		c = Q8_7_MIN;
	else
		c = temp;
	return c;
}

__attribute__((always_inline))
static inline Q8_7_t _Mul(Q8_7_t a, Q8_7_t b) {
	Q8_7_t c;
	Q16_14_t temp;

	temp = (Q16_14_t) a * b; 	/*Cast operands to 16 bits and multiply*/
	temp +=  (1 << (Q8_7_SHIFT-1));	 	/*add 1/2 to give correct rounding*/
	temp >>= Q8_7_SHIFT;				 	/*divide by 2^7*/
	if (temp > Q8_7_MAX)		/*saturate the result before assignment*/
		c = Q8_7_MAX;
	else if (temp < Q8_7_MIN)
		c = Q8_7_MIN;
	else
		c = temp;
	return c;
}

__attribute__((always_inline))
static inline Q8_7_t _Div(Q8_7_t a, Q8_7_t b) {
	Q8_7_t c;
	Q16_14_t temp;
	temp = (Q16_14_t) a << Q8_7_SHIFT; 	/* cast operand to 32 bits and shift*/
	temp += b >> 1; 			/*Add b/2 to give correct rounding*/
	temp /= b;					/*Perform the division (expensive!)*/
	c = temp;					/*Truncate and assign result*/
	return c;
}
/* GENERATED CODE BEGIN */
static const Q8_7_t PI_Q8_7 = 0x0192;
static const int8_t twiddle_factor_re[256]={
0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7e, 0x7e,
0x7d, 0x7c, 0x7c, 0x7b, 0x7a, 0x79, 0x78, 0x77,
0x76, 0x75, 0x73, 0x72, 0x70, 0x6f, 0x6d, 0x6c,
0x6a, 0x68, 0x66, 0x64, 0x62, 0x60, 0x5e, 0x5c,
0x5a, 0x58, 0x55, 0x53, 0x51, 0x4e, 0x4c, 0x49,
0x47, 0x44, 0x41, 0x3f, 0x3c, 0x39, 0x36, 0x33,
0x30, 0x2e, 0x2b, 0x28, 0x25, 0x22, 0x1f, 0x1c,
0x18, 0x15, 0x12, 0x0f, 0x0c, 0x09, 0x06, 0x03,
0x00, 0xfd, 0xfa, 0xf7, 0xf4, 0xf1, 0xee, 0xeb,
0xe8, 0xe4, 0xe1, 0xde, 0xdb, 0xd8, 0xd5, 0xd2,
0xd0, 0xcd, 0xca, 0xc7, 0xc4, 0xc1, 0xbf, 0xbc,
0xb9, 0xb7, 0xb4, 0xb2, 0xaf, 0xad, 0xab, 0xa8,
0xa6, 0xa4, 0xa2, 0xa0, 0x9e, 0x9c, 0x9a, 0x98,
0x96, 0x94, 0x93, 0x91, 0x90, 0x8e, 0x8d, 0x8b,
0x8a, 0x89, 0x88, 0x87, 0x86, 0x85, 0x84, 0x84,
0x83, 0x82, 0x82, 0x81, 0x81, 0x81, 0x81, 0x81,
};
static const int8_t twiddle_factor_im[256]={
0x00, 0xfd, 0xfa, 0xf7, 0xf4, 0xf1, 0xee, 0xeb,
0xe8, 0xe4, 0xe1, 0xde, 0xdb, 0xd8, 0xd5, 0xd2,
0xd0, 0xcd, 0xca, 0xc7, 0xc4, 0xc1, 0xbf, 0xbc,
0xb9, 0xb7, 0xb4, 0xb2, 0xaf, 0xad, 0xab, 0xa8,
0xa6, 0xa4, 0xa2, 0xa0, 0x9e, 0x9c, 0x9a, 0x98,
0x96, 0x94, 0x93, 0x91, 0x90, 0x8e, 0x8d, 0x8b,
0x8a, 0x89, 0x88, 0x87, 0x86, 0x85, 0x84, 0x84,
0x83, 0x82, 0x82, 0x81, 0x81, 0x81, 0x81, 0x81,
0x80, 0x81, 0x81, 0x81, 0x81, 0x81, 0x82, 0x82,
0x83, 0x84, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89,
0x8a, 0x8b, 0x8d, 0x8e, 0x90, 0x91, 0x93, 0x94,
0x96, 0x98, 0x9a, 0x9c, 0x9e, 0xa0, 0xa2, 0xa4,
0xa6, 0xa8, 0xab, 0xad, 0xaf, 0xb2, 0xb4, 0xb7,
0xb9, 0xbc, 0xbf, 0xc1, 0xc4, 0xc7, 0xca, 0xcd,
0xd0, 0xd2, 0xd5, 0xd8, 0xdb, 0xde, 0xe1, 0xe4,
0xe8, 0xeb, 0xee, 0xf1, 0xf4, 0xf7, 0xfa, 0xfd,
};
__attribute__((always_inline))
static inline void bit_reversal(Complex_t *X){
    Q8_7_t tmp;
    tmp = X[  1].re; X[  1].re = X[128].re; X[128].re = tmp;
    tmp = X[  2].re; X[  2].re = X[ 64].re; X[ 64].re = tmp;
    tmp = X[  3].re; X[  3].re = X[192].re; X[192].re = tmp;
    tmp = X[  4].re; X[  4].re = X[ 32].re; X[ 32].re = tmp;
    tmp = X[  5].re; X[  5].re = X[160].re; X[160].re = tmp;
    tmp = X[  6].re; X[  6].re = X[ 96].re; X[ 96].re = tmp;
    tmp = X[  7].re; X[  7].re = X[224].re; X[224].re = tmp;
    tmp = X[  8].re; X[  8].re = X[ 16].re; X[ 16].re = tmp;
    tmp = X[  9].re; X[  9].re = X[144].re; X[144].re = tmp;
    tmp = X[ 10].re; X[ 10].re = X[ 80].re; X[ 80].re = tmp;
    tmp = X[ 11].re; X[ 11].re = X[208].re; X[208].re = tmp;
    tmp = X[ 12].re; X[ 12].re = X[ 48].re; X[ 48].re = tmp;
    tmp = X[ 13].re; X[ 13].re = X[176].re; X[176].re = tmp;
    tmp = X[ 14].re; X[ 14].re = X[112].re; X[112].re = tmp;
    tmp = X[ 15].re; X[ 15].re = X[240].re; X[240].re = tmp;
    tmp = X[ 17].re; X[ 17].re = X[136].re; X[136].re = tmp;
    tmp = X[ 18].re; X[ 18].re = X[ 72].re; X[ 72].re = tmp;
    tmp = X[ 19].re; X[ 19].re = X[200].re; X[200].re = tmp;
    tmp = X[ 20].re; X[ 20].re = X[ 40].re; X[ 40].re = tmp;
    tmp = X[ 21].re; X[ 21].re = X[168].re; X[168].re = tmp;
    tmp = X[ 22].re; X[ 22].re = X[104].re; X[104].re = tmp;
    tmp = X[ 23].re; X[ 23].re = X[232].re; X[232].re = tmp;
    tmp = X[ 25].re; X[ 25].re = X[152].re; X[152].re = tmp;
    tmp = X[ 26].re; X[ 26].re = X[ 88].re; X[ 88].re = tmp;
    tmp = X[ 27].re; X[ 27].re = X[216].re; X[216].re = tmp;
    tmp = X[ 28].re; X[ 28].re = X[ 56].re; X[ 56].re = tmp;
    tmp = X[ 29].re; X[ 29].re = X[184].re; X[184].re = tmp;
    tmp = X[ 30].re; X[ 30].re = X[120].re; X[120].re = tmp;
    tmp = X[ 31].re; X[ 31].re = X[248].re; X[248].re = tmp;
    tmp = X[ 33].re; X[ 33].re = X[132].re; X[132].re = tmp;
    tmp = X[ 34].re; X[ 34].re = X[ 68].re; X[ 68].re = tmp;
    tmp = X[ 35].re; X[ 35].re = X[196].re; X[196].re = tmp;
    tmp = X[ 37].re; X[ 37].re = X[164].re; X[164].re = tmp;
    tmp = X[ 38].re; X[ 38].re = X[100].re; X[100].re = tmp;
    tmp = X[ 39].re; X[ 39].re = X[228].re; X[228].re = tmp;
    tmp = X[ 41].re; X[ 41].re = X[148].re; X[148].re = tmp;
    tmp = X[ 42].re; X[ 42].re = X[ 84].re; X[ 84].re = tmp;
    tmp = X[ 43].re; X[ 43].re = X[212].re; X[212].re = tmp;
    tmp = X[ 44].re; X[ 44].re = X[ 52].re; X[ 52].re = tmp;
    tmp = X[ 45].re; X[ 45].re = X[180].re; X[180].re = tmp;
    tmp = X[ 46].re; X[ 46].re = X[116].re; X[116].re = tmp;
    tmp = X[ 47].re; X[ 47].re = X[244].re; X[244].re = tmp;
    tmp = X[ 49].re; X[ 49].re = X[140].re; X[140].re = tmp;
    tmp = X[ 50].re; X[ 50].re = X[ 76].re; X[ 76].re = tmp;
    tmp = X[ 51].re; X[ 51].re = X[204].re; X[204].re = tmp;
    tmp = X[ 53].re; X[ 53].re = X[172].re; X[172].re = tmp;
    tmp = X[ 54].re; X[ 54].re = X[108].re; X[108].re = tmp;
    tmp = X[ 55].re; X[ 55].re = X[236].re; X[236].re = tmp;
    tmp = X[ 57].re; X[ 57].re = X[156].re; X[156].re = tmp;
    tmp = X[ 58].re; X[ 58].re = X[ 92].re; X[ 92].re = tmp;
    tmp = X[ 59].re; X[ 59].re = X[220].re; X[220].re = tmp;
    tmp = X[ 61].re; X[ 61].re = X[188].re; X[188].re = tmp;
    tmp = X[ 62].re; X[ 62].re = X[124].re; X[124].re = tmp;
    tmp = X[ 63].re; X[ 63].re = X[252].re; X[252].re = tmp;
    tmp = X[ 65].re; X[ 65].re = X[130].re; X[130].re = tmp;
    tmp = X[ 67].re; X[ 67].re = X[194].re; X[194].re = tmp;
    tmp = X[ 69].re; X[ 69].re = X[162].re; X[162].re = tmp;
    tmp = X[ 70].re; X[ 70].re = X[ 98].re; X[ 98].re = tmp;
    tmp = X[ 71].re; X[ 71].re = X[226].re; X[226].re = tmp;
    tmp = X[ 73].re; X[ 73].re = X[146].re; X[146].re = tmp;
    tmp = X[ 74].re; X[ 74].re = X[ 82].re; X[ 82].re = tmp;
    tmp = X[ 75].re; X[ 75].re = X[210].re; X[210].re = tmp;
    tmp = X[ 77].re; X[ 77].re = X[178].re; X[178].re = tmp;
    tmp = X[ 78].re; X[ 78].re = X[114].re; X[114].re = tmp;
    tmp = X[ 79].re; X[ 79].re = X[242].re; X[242].re = tmp;
    tmp = X[ 81].re; X[ 81].re = X[138].re; X[138].re = tmp;
    tmp = X[ 83].re; X[ 83].re = X[202].re; X[202].re = tmp;
    tmp = X[ 85].re; X[ 85].re = X[170].re; X[170].re = tmp;
    tmp = X[ 86].re; X[ 86].re = X[106].re; X[106].re = tmp;
    tmp = X[ 87].re; X[ 87].re = X[234].re; X[234].re = tmp;
    tmp = X[ 89].re; X[ 89].re = X[154].re; X[154].re = tmp;
    tmp = X[ 91].re; X[ 91].re = X[218].re; X[218].re = tmp;
    tmp = X[ 93].re; X[ 93].re = X[186].re; X[186].re = tmp;
    tmp = X[ 94].re; X[ 94].re = X[122].re; X[122].re = tmp;
    tmp = X[ 95].re; X[ 95].re = X[250].re; X[250].re = tmp;
    tmp = X[ 97].re; X[ 97].re = X[134].re; X[134].re = tmp;
    tmp = X[ 99].re; X[ 99].re = X[198].re; X[198].re = tmp;
    tmp = X[101].re; X[101].re = X[166].re; X[166].re = tmp;
    tmp = X[103].re; X[103].re = X[230].re; X[230].re = tmp;
    tmp = X[105].re; X[105].re = X[150].re; X[150].re = tmp;
    tmp = X[107].re; X[107].re = X[214].re; X[214].re = tmp;
    tmp = X[109].re; X[109].re = X[182].re; X[182].re = tmp;
    tmp = X[110].re; X[110].re = X[118].re; X[118].re = tmp;
    tmp = X[111].re; X[111].re = X[246].re; X[246].re = tmp;
    tmp = X[113].re; X[113].re = X[142].re; X[142].re = tmp;
    tmp = X[115].re; X[115].re = X[206].re; X[206].re = tmp;
    tmp = X[117].re; X[117].re = X[174].re; X[174].re = tmp;
    tmp = X[119].re; X[119].re = X[238].re; X[238].re = tmp;
    tmp = X[121].re; X[121].re = X[158].re; X[158].re = tmp;
    tmp = X[123].re; X[123].re = X[222].re; X[222].re = tmp;
    tmp = X[125].re; X[125].re = X[190].re; X[190].re = tmp;
    tmp = X[127].re; X[127].re = X[254].re; X[254].re = tmp;
    tmp = X[131].re; X[131].re = X[193].re; X[193].re = tmp;
    tmp = X[133].re; X[133].re = X[161].re; X[161].re = tmp;
    tmp = X[135].re; X[135].re = X[225].re; X[225].re = tmp;
    tmp = X[137].re; X[137].re = X[145].re; X[145].re = tmp;
    tmp = X[139].re; X[139].re = X[209].re; X[209].re = tmp;
    tmp = X[141].re; X[141].re = X[177].re; X[177].re = tmp;
    tmp = X[143].re; X[143].re = X[241].re; X[241].re = tmp;
    tmp = X[147].re; X[147].re = X[201].re; X[201].re = tmp;
    tmp = X[149].re; X[149].re = X[169].re; X[169].re = tmp;
    tmp = X[151].re; X[151].re = X[233].re; X[233].re = tmp;
    tmp = X[155].re; X[155].re = X[217].re; X[217].re = tmp;
    tmp = X[157].re; X[157].re = X[185].re; X[185].re = tmp;
    tmp = X[159].re; X[159].re = X[249].re; X[249].re = tmp;
    tmp = X[163].re; X[163].re = X[197].re; X[197].re = tmp;
    tmp = X[167].re; X[167].re = X[229].re; X[229].re = tmp;
    tmp = X[171].re; X[171].re = X[213].re; X[213].re = tmp;
    tmp = X[173].re; X[173].re = X[181].re; X[181].re = tmp;
    tmp = X[175].re; X[175].re = X[245].re; X[245].re = tmp;
    tmp = X[179].re; X[179].re = X[205].re; X[205].re = tmp;
    tmp = X[183].re; X[183].re = X[237].re; X[237].re = tmp;
    tmp = X[187].re; X[187].re = X[221].re; X[221].re = tmp;
    tmp = X[191].re; X[191].re = X[253].re; X[253].re = tmp;
    tmp = X[199].re; X[199].re = X[227].re; X[227].re = tmp;
    tmp = X[203].re; X[203].re = X[211].re; X[211].re = tmp;
    tmp = X[207].re; X[207].re = X[243].re; X[243].re = tmp;
    tmp = X[215].re; X[215].re = X[235].re; X[235].re = tmp;
    tmp = X[223].re; X[223].re = X[251].re; X[251].re = tmp;
    tmp = X[239].re; X[239].re = X[247].re; X[247].re = tmp;
}
/* GENERATED CODE END */

#endif /* INC_FFT_Q8_7_H_ */
