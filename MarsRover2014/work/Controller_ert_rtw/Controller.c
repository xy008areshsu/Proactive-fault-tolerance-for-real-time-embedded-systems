/*
 * File: Controller.c
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

/* External inputs (root inport signals with auto storage) */
ExternalInputs_Controller Controller_U;

/* External outputs (root outports fed by signals with auto storage) */
ExternalOutputs_Controller Controller_Y;

/* Real-time model */
RT_MODEL_Controller Controller_M_;
RT_MODEL_Controller *const Controller_M = &Controller_M_;

/* Model step function */
void Controller_step(void)
{
  real32_T rtb_Turnlimit;
  real32_T rtb_Switch;

  /* Outputs for Atomic SubSystem: '<Root>/Controller' */
  /* Gain: '<S1>/Steering gain' incorporates:
   *  Inport: '<Root>/Bearing to target'
   */
  rtb_Turnlimit = Controller_P.Steeringgain_Gain * Controller_U.Bearingtotarget;

  /* Saturate: '<S1>/Turn limit' */
  if (rtb_Turnlimit > Controller_P.Turnlimit_UpperSat) {
    rtb_Turnlimit = Controller_P.Turnlimit_UpperSat;
  } else {
    if (rtb_Turnlimit < Controller_P.Turnlimit_LowerSat) {
      rtb_Turnlimit = Controller_P.Turnlimit_LowerSat;
    }
  }

  /* End of Saturate: '<S1>/Turn limit' */

  /* Switch: '<S1>/Switch' incorporates:
   *  Constant: '<S1>/Constant'
   *  Constant: '<S2>/Lower Limit'
   *  Constant: '<S2>/Upper Limit'
   *  Inport: '<Root>/Bearing to target'
   *  Logic: '<S2>/AND'
   *  RelationalOperator: '<S2>/Lower Test'
   *  RelationalOperator: '<S2>/Upper Test'
   */
  if ((Controller_P.IntervalTest_lowlimit <= Controller_U.Bearingtotarget) &&
      (Controller_U.Bearingtotarget <= Controller_P.IntervalTest_uplimit)) {
    /* Gain: '<S1>/Speed gain' incorporates:
     *  Inport: '<Root>/Distance to target'
     */
    rtb_Switch = Controller_P.Speedgain_Gain *
      Controller_U.DistanceRemainToTarget;

    /* Saturate: '<S1>/Speed limit' */
    if (rtb_Switch > Controller_P.Speedlimit_UpperSat) {
      rtb_Switch = Controller_P.Speedlimit_UpperSat;
    } else {
      if (rtb_Switch < Controller_P.Speedlimit_LowerSat) {
        rtb_Switch = Controller_P.Speedlimit_LowerSat;
      }
    }

    /* End of Saturate: '<S1>/Speed limit' */
  } else {
    rtb_Switch = Controller_P.Constant_Value;
  }

  /* End of Switch: '<S1>/Switch' */

  /* Outport: '<Root>/Left Motor Demand' incorporates:
   *  Sum: '<S1>/Sum'
   */
  Controller_Y.LeftMotorDemand = rtb_Switch - rtb_Turnlimit;

  /* Outport: '<Root>/Right Motor Demand' incorporates:
   *  Sum: '<S1>/Sum1'
   */
  Controller_Y.RightMotorDemand = rtb_Turnlimit + rtb_Switch;

  /* End of Outputs for SubSystem: '<Root>/Controller' */
}

/* Model initialize function */
void Controller_initialize(void)
{
  /* Registration code */

  /* initialize error status */
  rtmSetErrorStatus(Controller_M, (NULL));

  /* external inputs */
  (void) memset((void *)&Controller_U, 0,
                sizeof(ExternalInputs_Controller));

  /* external outputs */
  (void) memset((void *)&Controller_Y, 0,
                sizeof(ExternalOutputs_Controller));
}

/* Model terminate function */
void Controller_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
