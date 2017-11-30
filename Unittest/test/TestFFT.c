#include "unity.h"
#include "unity_fixture.h"

#include <stdio.h>

#define FFT_IMPL_Q8_7

#include "fft.h"
#include "console.h"

TEST_GROUP(FFT);



TEST_SETUP(FFT)
{

}

TEST_TEAR_DOWN(FFT)
{
}

TEST(FFT, Algorithm)
{

	char str[128];
	extern uint32_t HAL_GetTick(void);


	Complex_t X[FFT_X_N] ={0};

	for (size_t i = 0; i < FFT_X_N; ++i) {
		X[i].re = (i % 8);//sawtooth
		X[i].im = 0;
	}
	uint32_t start = HAL_GetTick();
	fft(X);
	uint32_t end = HAL_GetTick();
	Console_Puts(CONSOLE_1, str);


	sprintf(str, "X=[\n");
	Console_Puts(CONSOLE_1, str);
	for (int i = 0; i < (FFT_X_N/2); ++i) {
		sprintf(str, "%d, %d;\n", X[i].re, X[i].im);
		Console_Puts(CONSOLE_1, str);
	}
	sprintf(str, "];\n(X=X/128);\nplot(sqrt(X(:,1).^2+X(:,2).^2));\n");
	sprintf(str, "\n%ldms\n", (end - start));
	Console_Puts(CONSOLE_1, str);
	TEST_ASSERT(1);
}

