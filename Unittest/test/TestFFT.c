#include "unity.h"
#include "unity_fixture.h"

#include <stdio.h>

#define FFT_IMPL_Q8_7

#include "fft.h"
#include "timer.h"
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



	Complex_t X[FFT_X_N] ={0};

	for (size_t i = 0; i < FFT_X_N; ++i) {
		X[i].re = (i % 8);//sawtooth
		X[i].im = 0;
	}

	timer_start(TIMER_1);
	uint32_t start = timer_counterValue(TIMER_1);
	fft(X);
	uint32_t end = timer_counterValue(TIMER_1);
	timer_stop(TIMER_1);

	char str[128];
	sprintf(str, "X=[\n");
	Console_Puts(CONSOLE_1, str);
	for (int i = 0; i < (FFT_X_N/2); ++i) {
		sprintf(str, "%d, %d;\n", X[i].re, X[i].im);
		Console_Puts(CONSOLE_1, str);
	}
	sprintf(str, "];\n(X=X/128);\nplot(sqrt(X(:,1).^2+X(:,2).^2));\n");
	sprintf(str, "\n%ldus\n", (end - start));
	Console_Puts(CONSOLE_1, str);
	TEST_ASSERT(1);


}

