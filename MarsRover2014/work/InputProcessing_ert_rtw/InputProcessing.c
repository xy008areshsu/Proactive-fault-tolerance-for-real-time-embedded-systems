/*
 * File: InputProcessing.c
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

/* Named constants for Chart: '<S1>/Estimator' */
#define Inpu_IN_Apply_camera_correction ((uint8_T)1U)
#define InputPr_IN_Calc_next_robot_move ((uint8_T)2U)
#define InputProces_IN_All_targets_done ((uint8_T)1U)
#define InputProces_IN_Wait_for_scoring ((uint8_T)4U)
#define InputProcess_IN_NO_ACTIVE_CHILD ((uint8_T)0U)
#define InputProcessing_IN_Finished    ((uint8_T)2U)
#define InputProcessing_IN_Next_Target ((uint8_T)3U)
#define InputProcessing_IN_Running     ((uint8_T)3U)
#define InputProcessing_IN_Standby     ((uint8_T)4U)

/* Block signals (auto storage) */
BlockIO_InputProcessing InputProcessing_B;

/* Block states (auto storage) */
D_Work_InputProcessing InputProcessing_DWork;

/* External inputs (root inport signals with auto storage) */
ExternalInputs_InputProcessing InputProcessing_U;

/* External outputs (root outports fed by signals with auto storage) */
ExternalOutputs_InputProcessing InputProcessing_Y;

/* Real-time model */
RT_MODEL_InputProcessing InputProcessing_M_;
RT_MODEL_InputProcessing *const InputProcessing_M = &InputProcessing_M_;

/* Forward declaration for local functions */
static void InputP_enter_atomic_Next_Target(void);
static void enter_atomic_Calc_next_robot_mo(void);
real32_T rt_atan2f_snf(real32_T u0, real32_T u1)
{
  real32_T y;
  int32_T u0_0;
  int32_T u1_0;
  if (rtIsNaNF(u0) || rtIsNaNF(u1)) {
    y = (rtNaNF);
  } else if (rtIsInfF(u0) && rtIsInfF(u1)) {
    if (u0 > 0.0F) {
      u0_0 = 1;
    } else {
      u0_0 = -1;
    }

    if (u1 > 0.0F) {
      u1_0 = 1;
    } else {
      u1_0 = -1;
    }

    y = (real32_T)atan2((real32_T)u0_0, (real32_T)u1_0);
  } else if (u1 == 0.0F) {
    if (u0 > 0.0F) {
      y = RT_PIF / 2.0F;
    } else if (u0 < 0.0F) {
      y = -(RT_PIF / 2.0F);
    } else {
      y = 0.0F;
    }
  } else {
    y = (real32_T)atan2(u0, u1);
  }

  return y;
}

/* Function for Chart: '<S1>/Estimator' */
static void InputP_enter_atomic_Next_Target(void)
{
  real32_T scale;
  real32_T absxk;
  real32_T t;
  real32_T tmp[2];
  int32_T tmp_0;

  /* Entry 'Next_Target': '<S3>:1' */
  InputProcessing_Y.doScan = false;
  tmp_0 = (int32_T)(InputProcessing_DWork.TargetIndex + 1U);
  if ((uint32_T)tmp_0 > 255U) {
    tmp_0 = 255;
  }

  InputProcessing_DWork.TargetIndex = (uint8_T)tmp_0;

  /* Inport: '<Root>/Targets' */
  /* Calc relative distance to next target */
  tmp[0] = InputProcessing_U.Targets[InputProcessing_DWork.TargetIndex - 1];
  tmp[1] = InputProcessing_U.Targets[InputProcessing_DWork.TargetIndex + 7];
  mw_arm_sub_f32(tmp, InputProcessing_DWork.prev_target, &InputProcessing_B.x[0],
                 2U);
  InputProcessing_DWork.DistanceToTarget = 0.0F;
  scale = 1.17549435E-38F;
  absxk = (real32_T)fabs(InputProcessing_B.x[0]);
  if (absxk > 1.17549435E-38F) {
    t = 1.17549435E-38F / absxk;
    InputProcessing_DWork.DistanceToTarget =
      InputProcessing_DWork.DistanceToTarget * t * t + 1.0F;
    scale = absxk;
  } else {
    t = absxk / 1.17549435E-38F;
    InputProcessing_DWork.DistanceToTarget += t * t;
  }

  absxk = (real32_T)fabs(InputProcessing_B.x[1]);
  if (absxk > scale) {
    t = scale / absxk;
    InputProcessing_DWork.DistanceToTarget =
      InputProcessing_DWork.DistanceToTarget * t * t + 1.0F;
    scale = absxk;
  } else {
    t = absxk / scale;
    InputProcessing_DWork.DistanceToTarget += t * t;
  }

  mw_arm_sqrt_f32(InputProcessing_DWork.DistanceToTarget, &absxk);
  InputProcessing_DWork.DistanceToTarget = scale * absxk;

  /* Inport: '<Root>/Targets' */
  /* Calc relative bearing to next target */
  InputProcessing_DWork.BearingToTarget = rt_atan2f_snf
    (InputProcessing_U.Targets[InputProcessing_DWork.TargetIndex + 7] -
     InputProcessing_DWork.prev_target[1],
     InputProcessing_U.Targets[InputProcessing_DWork.TargetIndex - 1] -
     InputProcessing_DWork.prev_target[0]) * 57.2957802F -
    InputProcessing_DWork.prev_bearing;

  /* Save values for relative moves */
  InputProcessing_DWork.prev_target[0] =
    InputProcessing_U.Targets[InputProcessing_DWork.TargetIndex - 1];
  InputProcessing_DWork.prev_target[1] =
    InputProcessing_U.Targets[InputProcessing_DWork.TargetIndex + 7];
  InputProcessing_DWork.prev_bearing += InputProcessing_DWork.BearingToTarget;

  /* Inport: '<Root>/Encoder Left' */
  InputProcessing_DWork.encoder_left_prev_target = InputProcessing_U.EncoderLeft;

  /* Inport: '<Root>/Encoder Right' */
  InputProcessing_DWork.encoder_right_prev_target =
    InputProcessing_U.EncoderRight;
  InputProcessing_Y.DistancetoTarget = InputProcessing_DWork.DistanceToTarget;
  InputProcessing_B.BearingRemainToTarget =
    InputProcessing_DWork.BearingToTarget;
}

/* Function for Chart: '<S1>/Estimator' */
static void enter_atomic_Calc_next_robot_mo(void)
{
  real32_T dR;
  real32_T dL;
  int32_T qY;

  /* Entry 'Calc_next_robot_move': '<S3>:146' */
  InputProcessing_Y.doBeep = false;

  /* Inport: '<Root>/Encoder Left' */
  /* Calc the new trajectory based on what has already been done */
  qY = InputProcessing_U.EncoderLeft -
    InputProcessing_DWork.encoder_left_prev_target;
  if ((InputProcessing_U.EncoderLeft < 0) &&
      ((InputProcessing_DWork.encoder_left_prev_target >= 0) && (qY >= 0))) {
    qY = MIN_int32_T;
  } else {
    if ((InputProcessing_U.EncoderLeft >= 0) &&
        ((InputProcessing_DWork.encoder_left_prev_target < 0) && (qY < 0))) {
      qY = MAX_int32_T;
    }
  }

  /* End of Inport: '<Root>/Encoder Left' */
  dL = (real32_T)qY * 2.0F * InputProcessing_P.WheelRadius * 3.14159274F /
    InputProcessing_P.EncRes;

  /* Inport: '<Root>/Encoder Right' */
  qY = InputProcessing_U.EncoderRight -
    InputProcessing_DWork.encoder_right_prev_target;
  if ((InputProcessing_U.EncoderRight < 0) &&
      ((InputProcessing_DWork.encoder_right_prev_target >= 0) && (qY >= 0))) {
    qY = MIN_int32_T;
  } else {
    if ((InputProcessing_U.EncoderRight >= 0) &&
        ((InputProcessing_DWork.encoder_right_prev_target < 0) && (qY < 0))) {
      qY = MAX_int32_T;
    }
  }

  /* End of Inport: '<Root>/Encoder Right' */
  dR = (real32_T)qY * 2.0F * InputProcessing_P.WheelRadius * 3.14159274F /
    InputProcessing_P.EncRes;
  InputProcessing_DWork.CurrentDistance = (dL + dR) / 2.0F;
  InputProcessing_Y.DistancetoTarget = InputProcessing_DWork.DistanceToTarget -
    InputProcessing_DWork.CurrentDistance;
  InputProcessing_B.BearingRemainToTarget =
    InputProcessing_DWork.BearingToTarget - (dR - dL) * 180.0F /
    (InputProcessing_P.AxleLength * 1.01F * 3.14159274F);
}

real32_T rt_roundf_snf(real32_T u)
{
  real32_T y;
  if ((real32_T)fabs(u) < 8.388608E+6F) {
    if (u >= 0.5F) {
      y = (real32_T)floor(u + 0.5F);
    } else if (u > -0.5F) {
      y = u * 0.0F;
    } else {
      y = (real32_T)ceil(u - 0.5F);
    }
  } else {
    y = u;
  }

  return y;
}

real32_T rt_modf_snf(real32_T u0, real32_T u1)
{
  real32_T y;
  real32_T tmp;
  if (u1 == 0.0F) {
    y = u0;
  } else if (!((!rtIsNaNF(u0)) && (!rtIsInfF(u0)) && ((!rtIsNaNF(u1)) &&
               (!rtIsInfF(u1))))) {
    y = (rtNaNF);
  } else {
    tmp = u0 / u1;
    if (u1 <= (real32_T)floor(u1)) {
      y = u0 - (real32_T)floor(tmp) * u1;
    } else if ((real32_T)fabs(tmp - rt_roundf_snf(tmp)) <= FLT_EPSILON *
               (real32_T)fabs(tmp)) {
      y = 0.0F;
    } else {
      y = (tmp - (real32_T)floor(tmp)) * u1;
    }
  }

  return y;
}

/* Model step function */
void InputProcessing_step(void)
{
  uint8_T ind;
  uint8_T TargetFound;
  real32_T dR;
  real32_T dL;
  boolean_T guard1;
  int16_T x;
  int16_T c_x;
  int16_T dist_remaining;
  int32_T tmp;
  int32_T qY;

  /* Chart: '<S1>/Estimator' incorporates:
   *  Inport: '<Root>/Encoder Left'
   *  Inport: '<Root>/Encoder Right'
   *  Inport: '<Root>/Go'
   *  Inport: '<Root>/bearing'
   *  Inport: '<Root>/distance'
   */
  if (InputProcessing_DWork.temporalCounter_i1 < 31U) {
    InputProcessing_DWork.temporalCounter_i1++;
  }

  /* Gateway: InputProcessing/Estimator */
  /* During: InputProcessing/Estimator */
  if (InputProcessing_DWork.is_active_c2_InputProcessing == 0U) {
    /* Entry: InputProcessing/Estimator */
    InputProcessing_DWork.is_active_c2_InputProcessing = 1U;

    /* Entry Internal: InputProcessing/Estimator */
    /* Transition: '<S3>:15' */
    InputProcessing_DWork.is_c2_InputProcessing = InputProcessing_IN_Standby;

    /* Outport: '<Root>/doBeep' */
    /* Entry 'Standby': '<S3>:4' */
    /* Init */
    InputProcessing_Y.doBeep = false;

    /* Outport: '<Root>/doScan' */
    InputProcessing_Y.doScan = false;
    InputProcessing_DWork.encoder_left_prev_target = 0;
    InputProcessing_DWork.encoder_right_prev_target = 0;
    InputProcessing_DWork.CurrentDistance = 0.0F;
    InputProcessing_DWork.prev_target[0] = (real32_T)InputProcessing_P.startPos
      [0];
    InputProcessing_DWork.prev_target[1] = (real32_T)InputProcessing_P.startPos
      [1];
    InputProcessing_DWork.prev_bearing = 0.0F;
    InputProcessing_DWork.TargetIndex = 0U;

    /* Outport: '<Root>/allTargetsDone' */
    InputProcessing_Y.allTargetsDone = false;
  } else {
    switch (InputProcessing_DWork.is_c2_InputProcessing) {
     case InputProces_IN_All_targets_done:
      /* During 'All_targets_done': '<S3>:187' */
      if (InputProcessing_DWork.temporalCounter_i1 >= 30U) {
        /* Transition: '<S3>:193' */
        InputProcessing_DWork.is_c2_InputProcessing =
          InputProcessing_IN_Finished;

        /* Outport: '<Root>/allTargetsDone' */
        /* Entry 'Finished': '<S3>:192' */
        InputProcessing_Y.allTargetsDone = true;

        /* Outport: '<Root>/doScan' */
        InputProcessing_Y.doScan = false;
      }
      break;

     case InputProcessing_IN_Finished:
      /* During 'Finished': '<S3>:192' */
      if (!InputProcessing_P.do_one_run) {
        /* Outport: '<Root>/allTargetsDone' */
        /* Transition: '<S3>:245' */
        InputProcessing_Y.allTargetsDone = false;
        InputProcessing_DWork.TargetIndex = 0U;
        InputProcessing_DWork.is_c2_InputProcessing = InputProcessing_IN_Running;

        /* Entry Internal 'Running': '<S3>:3' */
        /* Transition: '<S3>:134' */
        InputProcessing_DWork.is_Running = InputProcessing_IN_Next_Target;
        InputP_enter_atomic_Next_Target();
      }
      break;

     case InputProcessing_IN_Running:
      /* During 'Running': '<S3>:3' */
      if ((InputProcessing_Y.DistancetoTarget < 7.0F) &&
          (InputProcessing_DWork.TargetIndex >= 8)) {
        /* Transition: '<S3>:188' */
        /* Exit Internal 'Running': '<S3>:3' */
        InputProcessing_DWork.is_Running = InputProcess_IN_NO_ACTIVE_CHILD;
        InputProcessing_DWork.is_c2_InputProcessing =
          InputProces_IN_All_targets_done;
        InputProcessing_DWork.temporalCounter_i1 = 0U;

        /* Outport: '<Root>/Distance to Target' */
        /* Entry 'All_targets_done': '<S3>:187' */
        InputProcessing_Y.DistancetoTarget = 0.0F;

        /* Outport: '<Root>/doScan' */
        InputProcessing_Y.doScan = true;
      } else {
        switch (InputProcessing_DWork.is_Running) {
         case Inpu_IN_Apply_camera_correction:
          /* During 'Apply_camera_correction': '<S3>:145' */
          /* Transition: '<S3>:186' */
          InputProcessing_DWork.is_Running = InputPr_IN_Calc_next_robot_move;
          enter_atomic_Calc_next_robot_mo();
          break;

         case InputPr_IN_Calc_next_robot_move:
          /* During 'Calc_next_robot_move': '<S3>:146' */
          if (InputProcessing_Y.DistancetoTarget < 7.0F) {
            /* Transition: '<S3>:175' */
            InputProcessing_DWork.is_Running = InputProces_IN_Wait_for_scoring;
            InputProcessing_DWork.temporalCounter_i1 = 0U;

            /* Outport: '<Root>/Distance to Target' */
            /* Entry 'Wait_for_scoring': '<S3>:174' */
            InputProcessing_Y.DistancetoTarget = 0.0F;

            /* Outport: '<Root>/doScan' */
            InputProcessing_Y.doScan = true;
          } else if ((InputProcessing_DWork.CurrentDistance > 5.0F) &&
                     (InputProcessing_Y.DistancetoTarget >
                      InputProcessing_P.pcam[0] - 5.0)) {
            /* Transition: '<S3>:185' */
            InputProcessing_DWork.is_Running = Inpu_IN_Apply_camera_correction;

            /* Entry 'Apply_camera_correction': '<S3>:145' */
            /* Find the closest match between seen targets and current destination */
            TargetFound = 0U;
            dL = rt_roundf_snf(InputProcessing_Y.DistancetoTarget);
            if (dL < 32768.0F) {
              if (dL >= -32768.0F) {
                dist_remaining = (int16_T)dL;
              } else {
                dist_remaining = MIN_int16_T;
              }
            } else {
              dist_remaining = MAX_int16_T;
            }

            for (ind = 0U; ind < 6U; ind++) {
              if (InputProcessing_U.distance[ind] != 0) {
                qY = InputProcessing_U.distance[ind] - dist_remaining;
                if (qY > 32767) {
                  qY = 32767;
                } else {
                  if (qY < -32768) {
                    qY = -32768;
                  }
                }

                if ((int16_T)qY < 0) {
                  qY = -(int16_T)qY;
                  if (qY > 32767) {
                    qY = 32767;
                  }

                  x = (int16_T)qY;
                } else {
                  x = (int16_T)qY;
                }

                if (x < 15) {
                  guard1 = false;
                  if (TargetFound == 0) {
                    guard1 = true;
                  } else {
                    qY = InputProcessing_U.distance[TargetFound - 1] -
                      dist_remaining;
                    if (qY > 32767) {
                      qY = 32767;
                    } else {
                      if (qY < -32768) {
                        qY = -32768;
                      }
                    }

                    tmp = InputProcessing_U.distance[ind] - dist_remaining;
                    if (tmp > 32767) {
                      tmp = 32767;
                    } else {
                      if (tmp < -32768) {
                        tmp = -32768;
                      }
                    }

                    if ((int16_T)qY < 0) {
                      qY = -(int16_T)qY;
                      if (qY > 32767) {
                        qY = 32767;
                      }

                      x = (int16_T)qY;
                    } else {
                      x = (int16_T)qY;
                    }

                    if ((int16_T)tmp < 0) {
                      qY = -(int16_T)tmp;
                      if (qY > 32767) {
                        qY = 32767;
                      }

                      c_x = (int16_T)qY;
                    } else {
                      c_x = (int16_T)tmp;
                    }

                    if (x > c_x) {
                      guard1 = true;
                    }
                  }

                  if (guard1) {
                    TargetFound = (uint8_T)(ind + 1U);
                  }
                }
              }
            }

            /* If a target is found update the distance and bearing from the camera */
            if (TargetFound != 0) {
              /* Outport: '<Root>/doBeep' */
              InputProcessing_Y.doBeep = true;
              InputProcessing_DWork.DistanceToTarget =
                InputProcessing_U.distance[TargetFound - 1];
              InputProcessing_DWork.BearingToTarget = (real32_T)
                InputProcessing_U.bearing[TargetFound - 1] / 2.0F;
              InputProcessing_DWork.encoder_left_prev_target =
                InputProcessing_U.EncoderLeft;
              InputProcessing_DWork.encoder_right_prev_target =
                InputProcessing_U.EncoderRight;
            }
          } else {
            /* Outport: '<Root>/doBeep' */
            InputProcessing_Y.doBeep = false;

            /* Calc the new trajectory based on what has already been done */
            qY = InputProcessing_U.EncoderLeft -
              InputProcessing_DWork.encoder_left_prev_target;
            if ((InputProcessing_U.EncoderLeft < 0) &&
                ((InputProcessing_DWork.encoder_left_prev_target >= 0) && (qY >=
                  0))) {
              qY = MIN_int32_T;
            } else {
              if ((InputProcessing_U.EncoderLeft >= 0) &&
                  ((InputProcessing_DWork.encoder_left_prev_target < 0) && (qY <
                    0))) {
                qY = MAX_int32_T;
              }
            }

            dL = (real32_T)qY * 2.0F * InputProcessing_P.WheelRadius *
              3.14159274F / InputProcessing_P.EncRes;
            qY = InputProcessing_U.EncoderRight -
              InputProcessing_DWork.encoder_right_prev_target;
            if ((InputProcessing_U.EncoderRight < 0) &&
                ((InputProcessing_DWork.encoder_right_prev_target >= 0) && (qY >=
                  0))) {
              qY = MIN_int32_T;
            } else {
              if ((InputProcessing_U.EncoderRight >= 0) &&
                  ((InputProcessing_DWork.encoder_right_prev_target < 0) && (qY <
                    0))) {
                qY = MAX_int32_T;
              }
            }

            dR = (real32_T)qY * 2.0F * InputProcessing_P.WheelRadius *
              3.14159274F / InputProcessing_P.EncRes;
            InputProcessing_DWork.CurrentDistance = (dL + dR) / 2.0F;

            /* Outport: '<Root>/Distance to Target' incorporates:
             *  Inport: '<Root>/Encoder Left'
             *  Inport: '<Root>/Encoder Right'
             */
            InputProcessing_Y.DistancetoTarget =
              InputProcessing_DWork.DistanceToTarget -
              InputProcessing_DWork.CurrentDistance;
            InputProcessing_B.BearingRemainToTarget =
              InputProcessing_DWork.BearingToTarget - (dR - dL) * 180.0F /
              (InputProcessing_P.AxleLength * 1.01F * 3.14159274F);
          }
          break;

         case InputProcessing_IN_Next_Target:
          /* During 'Next_Target': '<S3>:1' */
          /* Transition: '<S3>:177' */
          InputProcessing_DWork.is_Running = InputPr_IN_Calc_next_robot_move;
          enter_atomic_Calc_next_robot_mo();
          break;

         default:
          /* During 'Wait_for_scoring': '<S3>:174' */
          if (InputProcessing_DWork.temporalCounter_i1 >= 30U) {
            /* Transition: '<S3>:176' */
            InputProcessing_DWork.is_Running = InputProcessing_IN_Next_Target;
            InputP_enter_atomic_Next_Target();
          }
          break;
        }
      }
      break;

     default:
      /* During 'Standby': '<S3>:4' */
      if (InputProcessing_U.Go) {
        /* Transition: '<S3>:5' */
        InputProcessing_DWork.is_c2_InputProcessing = InputProcessing_IN_Running;

        /* Entry Internal 'Running': '<S3>:3' */
        /* Transition: '<S3>:134' */
        InputProcessing_DWork.is_Running = InputProcessing_IN_Next_Target;
        InputP_enter_atomic_Next_Target();
      }
      break;
    }
  }

  /* End of Chart: '<S1>/Estimator' */

  /* Outport: '<Root>/Bearing to Target' incorporates:
   *  Constant: '<S2>/Constant'
   *  Constant: '<S2>/Constant1'
   *  Math: '<S2>/Math Function1'
   *  Sum: '<S2>/Sum10'
   *  Sum: '<S2>/Sum7'
   */
  InputProcessing_Y.BearingtoTarget = rt_modf_snf
    (InputProcessing_P.Constant_Value + InputProcessing_B.BearingRemainToTarget,
     InputProcessing_P.Constant1_Value) - InputProcessing_P.Constant_Value;
}

/* Model initialize function */
void InputProcessing_initialize(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize error status */
  rtmSetErrorStatus(InputProcessing_M, (NULL));

  /* block I/O */
  (void) memset(((void *) &InputProcessing_B), 0,
                sizeof(BlockIO_InputProcessing));

  /* states (dwork) */
  (void) memset((void *)&InputProcessing_DWork, 0,
                sizeof(D_Work_InputProcessing));

  /* external inputs */
  (void) memset((void *)&InputProcessing_U, 0,
                sizeof(ExternalInputs_InputProcessing));

  /* external outputs */
  (void) memset((void *)&InputProcessing_Y, 0,
                sizeof(ExternalOutputs_InputProcessing));

  /* InitializeConditions for Chart: '<S1>/Estimator' */
  InputProcessing_DWork.is_Running = InputProcess_IN_NO_ACTIVE_CHILD;
  InputProcessing_DWork.temporalCounter_i1 = 0U;
  InputProcessing_DWork.is_active_c2_InputProcessing = 0U;
  InputProcessing_DWork.is_c2_InputProcessing = InputProcess_IN_NO_ACTIVE_CHILD;
}

/* Model terminate function */
void InputProcessing_terminate(void)
{
  /* (no terminate code required) */
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
