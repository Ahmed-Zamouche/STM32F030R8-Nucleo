#include "unity_fixture.h"
#include <stdbool.h>

#include "led.h"


static void RunAllTests(void)
{
  RUN_TEST_GROUP(Sys);
  RUN_TEST_GROUP(Events);
  RUN_TEST_GROUP(FFT);
}

int main(int argc, const char * argv[]) {

	int result =  UnityMain(argc, argv, RunAllTests);

	Led_Set(LED_1, result ? false: true);

}

