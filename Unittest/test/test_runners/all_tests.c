#include "unity_fixture.h"


#include <console.h>
#include <stdio.h>      /* printf, scanf */
#include <stdlib.h>     /* exit */
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>

#define Q8_7_shift	(7)
#define N			(256)


#define COS_Q8_7_LUT_SIZE_LOG2	(6)
#define COS_Q8_7_LUT_SIZE	(1<<COS_Q8_7_LUT_SIZE_LOG2)

const uint8_t cos_Q8_7_lut[]={
0x80, 0x80, 0x80, 0x80, 0x7f, 0x7f, 0x7f, 0x7e,
0x7e, 0x7d, 0x7c, 0x7b, 0x7a, 0x7a, 0x79, 0x77,
0x76, 0x75, 0x74, 0x72, 0x71, 0x6f, 0x6e, 0x6c,
0x6a, 0x69, 0x67, 0x65, 0x63, 0x61, 0x5f, 0x5d,
0x5b, 0x58, 0x56, 0x54, 0x51, 0x4f, 0x4c, 0x4a,
0x47, 0x44, 0x42, 0x3f, 0x3c, 0x3a, 0x37, 0x34,
0x31, 0x2e, 0x2b, 0x28, 0x25, 0x22, 0x1f, 0x1c,
0x19, 0x16, 0x13, 0x10, 0x0d, 0x09, 0x06, 0x03,
};

const int16_t Q8_7_PI = 0x0192;
const int16_t Q8_7_HALF_PI = 0x00c9;
const int16_t Q8_7_ONE = 0x0080;


static inline int16_t cos_Q8_7(int16_t x)
{
	x = abs(x);
	size_t seg_num = (x / Q8_7_HALF_PI) & 0x3;
	x = (x % Q8_7_HALF_PI);

	size_t idx = ((x << COS_Q8_7_LUT_SIZE_LOG2) / Q8_7_HALF_PI);

	int16_t cosVal;
	switch (seg_num) {
	case 0:
		cosVal = cos_Q8_7_lut[idx];
		break;
	case 1:
		cosVal = -cos_Q8_7_lut[(COS_Q8_7_LUT_SIZE - 1) - idx];
		break;
	case 2:
		cosVal = -cos_Q8_7_lut[idx];
		break;
	case 3:
		cosVal = cos_Q8_7_lut[(COS_Q8_7_LUT_SIZE - 1) - idx];
		break;
	default:
		assert(0);
	}
	return cosVal;
}

static inline int16_t sin_Q8_7(int16_t x)
{
	return cos_Q8_7(x - (Q8_7_PI >> 1) );
}


static void RunAllTests(void)
{
  RUN_TEST_GROUP(Sys);
}

int main(int argc, const char * argv[]) {

	(*(int*) 0 = -1);

	char str[32];
	extern uint32_t HAL_GetTick(void);
	uint32_t start = HAL_GetTick();
#if 0
	for (int16_t x = -(Q8_7_PI); x <(Q8_7_PI); x += 1)
	{
		sprintf(str, "%d, %d, %d;\n", x, cos_Q8_7(x), sin_Q8_7(x));
		Console_Puts(CONSOLE_1, str);
	}
#else
	uint16_t x = 0;
	volatile int16_t r;
	do {
		r =  cos_Q8_7(x++);
	} while (x);
	(void) r;
#endif
	uint32_t end = HAL_GetTick();
	sprintf(str, "%ldms\n", (end - start));
	Console_Puts(CONSOLE_1, str);


	return UnityMain(argc, argv, RunAllTests);

}

