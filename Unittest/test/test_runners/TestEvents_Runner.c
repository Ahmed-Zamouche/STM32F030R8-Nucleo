/*
 * TestEvents_runner.c
 *
 *  Created on: 25 Nov 2017
 *      Author: Ahmed.Z
 */
#include "unity.h"
#include "unity_fixture.h"

TEST_GROUP_RUNNER(Events)
{
  RUN_TEST_CASE(Events, Pwm_Callback);
  RUN_TEST_CASE(Events, Button_Callback);
  RUN_TEST_CASE(Events, Console_CallbackRead);
  RUN_TEST_CASE(Events, Console_CallbackWrite);
}
