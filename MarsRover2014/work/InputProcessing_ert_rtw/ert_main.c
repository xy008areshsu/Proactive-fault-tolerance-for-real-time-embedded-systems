/*
 * File: ert_main.c
 *
 * Code generated for Simulink model 'InputProcessing'.
 *
 * Model version                  : 1.851
 * Simulink Coder version         : 8.8 (R2015a) 09-Feb-2015
 * C/C++ source code generated on : Thu Apr 09 10:32:54 2015
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "InputProcessing.h"
#include "rtwtypes.h"

volatile int IsrOverrun = 0;
static boolean_T OverrunFlag = 0;
void rt_OneStep(void)
{
  /* Check for overrun. Protect OverrunFlag against preemption */
  if (OverrunFlag++) {
    IsrOverrun = 1;
    OverrunFlag--;
    return;
  }

  InputProcessing_step();

  /* Get model outputs here */
  OverrunFlag--;
}

#define UNUSED(x)                      x = x

int main(void)
{
  volatile boolean_T runModel = 1;
  float modelBaseRate = 0.1;
  float systemClock = 100;
  SystemCoreClockUpdate();
  UNUSED(modelBaseRate);
  UNUSED(systemClock);
  rtmSetErrorStatus(InputProcessing_M, 0);
  InputProcessing_initialize();
  runModel =
    rtmGetErrorStatus(InputProcessing_M) == (NULL);
  while (runModel) {
    rt_OneStep();
    runModel =
      rtmGetErrorStatus(InputProcessing_M) == (NULL);
  }

  /* Disable rt_OneStep() here */

  /* Terminate model */
  InputProcessing_terminate();
  return 0;
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
