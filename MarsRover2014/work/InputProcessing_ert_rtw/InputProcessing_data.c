/*
 * File: InputProcessing_data.c
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
#include "InputProcessing_private.h"

/* Block parameters (auto storage) */
Parameters_InputProcessing InputProcessing_P = {
  /*  Variable: lcam
   * Referenced by: '<S1>/Estimator'
   */
  { 21.0, 90.0 },

  /*  Variable: pcam
   * Referenced by: '<S1>/Estimator'
   */
  { 24.0, 100.0 },

  /*  Variable: startPos
   * Referenced by: '<S1>/Estimator'
   */
  { 50.0, 50.0 },
  16.2F,                               /* Variable: AxleLength
                                        * Referenced by: '<S1>/Estimator'
                                        */
  636.0F,                              /* Variable: EncRes
                                        * Referenced by: '<S1>/Estimator'
                                        */
  3.325F,                              /* Variable: WheelRadius
                                        * Referenced by: '<S1>/Estimator'
                                        */
  0,                                   /* Variable: do_one_run
                                        * Referenced by: '<S1>/Estimator'
                                        */
  180.0F,                              /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S2>/Constant'
                                        */
  360.0F                               /* Computed Parameter: Constant1_Value
                                        * Referenced by: '<S2>/Constant1'
                                        */
};

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
