/*
 * File: Controller_data.c
 *
 * Code generated for Simulink model 'Controller'.
 *
 * Model version                  : 1.848
 * Simulink Coder version         : 8.8 (R2015a) 09-Feb-2015
 * C/C++ source code generated on : Thu Apr 09 10:30:33 2015
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "Controller.h"
#include "Controller_private.h"

/* Block parameters (auto storage) */
Parameters_Controller Controller_P = {
  -25.0F,                              /* Mask Parameter: IntervalTest_lowlimit
                                        * Referenced by: '<S2>/Lower Limit'
                                        */
  25.0F,                               /* Mask Parameter: IntervalTest_uplimit
                                        * Referenced by: '<S2>/Upper Limit'
                                        */
  0.0F,                                /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S1>/Constant'
                                        */
  3.0F,                                /* Computed Parameter: Speedgain_Gain
                                        * Referenced by: '<S1>/Speed gain'
                                        */
  40.0F,                               /* Computed Parameter: Speedlimit_UpperSat
                                        * Referenced by: '<S1>/Speed limit'
                                        */
  0.0F,                                /* Computed Parameter: Speedlimit_LowerSat
                                        * Referenced by: '<S1>/Speed limit'
                                        */
  1.2F,                                /* Computed Parameter: Steeringgain_Gain
                                        * Referenced by: '<S1>/Steering gain'
                                        */
  50.0F,                               /* Computed Parameter: Turnlimit_UpperSat
                                        * Referenced by: '<S1>/Turn limit'
                                        */
  -50.0F                               /* Computed Parameter: Turnlimit_LowerSat
                                        * Referenced by: '<S1>/Turn limit'
                                        */
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
