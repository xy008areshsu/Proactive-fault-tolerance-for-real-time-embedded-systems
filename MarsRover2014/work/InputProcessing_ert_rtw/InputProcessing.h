/*
 * File: InputProcessing.h
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

#ifndef RTW_HEADER_InputProcessing_h_
#define RTW_HEADER_InputProcessing_h_
#include <float.h>
#include <math.h>
#include <stddef.h>
#include <string.h>
#ifndef InputProcessing_COMMON_INCLUDES_
# define InputProcessing_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* InputProcessing_COMMON_INCLUDES_ */

#include "InputProcessing_types.h"
#include "MW_target_hardware_resources.h"
#include "mw_cmsis.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
#include "rtGetInf.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Block signals (auto storage) */
typedef struct {
  real32_T x[2];
  real32_T BearingRemainToTarget;      /* '<S1>/Estimator' */
} BlockIO_InputProcessing;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  real32_T CurrentDistance;            /* '<S1>/Estimator' */
  real32_T prev_target[2];             /* '<S1>/Estimator' */
  real32_T prev_bearing;               /* '<S1>/Estimator' */
  real32_T BearingToTarget;            /* '<S1>/Estimator' */
  real32_T DistanceToTarget;           /* '<S1>/Estimator' */
  int32_T encoder_right_prev_target;   /* '<S1>/Estimator' */
  int32_T encoder_left_prev_target;    /* '<S1>/Estimator' */
  uint8_T is_active_c2_InputProcessing;/* '<S1>/Estimator' */
  uint8_T is_c2_InputProcessing;       /* '<S1>/Estimator' */
  uint8_T is_Running;                  /* '<S1>/Estimator' */
  uint8_T TargetIndex;                 /* '<S1>/Estimator' */
  uint8_T temporalCounter_i1;          /* '<S1>/Estimator' */
} D_Work_InputProcessing;

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real32_T Targets[16];                /* '<Root>/Targets' */
  int32_T EncoderLeft;                 /* '<Root>/Encoder Left' */
  int32_T EncoderRight;                /* '<Root>/Encoder Right' */
  int16_T distance[6];                 /* '<Root>/distance' */
  int8_T bearing[6];                   /* '<Root>/bearing' */
  boolean_T Go;                        /* '<Root>/Go' */
} ExternalInputs_InputProcessing;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real32_T BearingtoTarget;            /* '<Root>/Bearing to Target' */
  real32_T DistancetoTarget;           /* '<Root>/Distance to Target' */
  boolean_T doBeep;                    /* '<Root>/doBeep' */
  boolean_T doScan;                    /* '<Root>/doScan' */
  boolean_T allTargetsDone;            /* '<Root>/allTargetsDone' */
} ExternalOutputs_InputProcessing;

/* Parameters (auto storage) */
struct Parameters_InputProcessing_ {
  real_T lcam[2];                      /* Variable: lcam
                                        * Referenced by: '<S1>/Estimator'
                                        */
  real_T pcam[2];                      /* Variable: pcam
                                        * Referenced by: '<S1>/Estimator'
                                        */
  real_T startPos[2];                  /* Variable: startPos
                                        * Referenced by: '<S1>/Estimator'
                                        */
  real32_T AxleLength;                 /* Variable: AxleLength
                                        * Referenced by: '<S1>/Estimator'
                                        */
  real32_T EncRes;                     /* Variable: EncRes
                                        * Referenced by: '<S1>/Estimator'
                                        */
  real32_T WheelRadius;                /* Variable: WheelRadius
                                        * Referenced by: '<S1>/Estimator'
                                        */
  boolean_T do_one_run;                /* Variable: do_one_run
                                        * Referenced by: '<S1>/Estimator'
                                        */
  real32_T Constant_Value;             /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S2>/Constant'
                                        */
  real32_T Constant1_Value;            /* Computed Parameter: Constant1_Value
                                        * Referenced by: '<S2>/Constant1'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_InputProcessing {
  const char_T *errorStatus;
};

/* Block parameters (auto storage) */
extern Parameters_InputProcessing InputProcessing_P;

/* Block signals (auto storage) */
extern BlockIO_InputProcessing InputProcessing_B;

/* Block states (auto storage) */
extern D_Work_InputProcessing InputProcessing_DWork;

/* External inputs (root inport signals with auto storage) */
extern ExternalInputs_InputProcessing InputProcessing_U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExternalOutputs_InputProcessing InputProcessing_Y;

/* Model entry point functions */
extern void InputProcessing_initialize(void);
extern void InputProcessing_step(void);
extern void InputProcessing_terminate(void);

/* Real-time Model object */
extern RT_MODEL_InputProcessing *const InputProcessing_M;

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('SimulationModel/InputProcessing')    - opens subsystem SimulationModel/InputProcessing
 * hilite_system('SimulationModel/InputProcessing/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'SimulationModel'
 * '<S1>'   : 'SimulationModel/InputProcessing'
 * '<S2>'   : 'SimulationModel/InputProcessing/Compute BearingToTarget'
 * '<S3>'   : 'SimulationModel/InputProcessing/Estimator'
 */
#endif                                 /* RTW_HEADER_InputProcessing_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
