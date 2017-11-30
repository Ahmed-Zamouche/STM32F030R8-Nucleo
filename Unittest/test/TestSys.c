#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP(Sys);



TEST_SETUP(Sys)
{

}

TEST_TEAR_DOWN(Sys)
{
}

#if 0
static void Exception_Rise(int n)
{
	HAL_NVIC_EnableIRQ(-15);
	HAL_NVIC_SetPendingIRQ(-15);
}
#endif

TEST(Sys, Clock)
{
	TEST_ASSERT(1);
}

