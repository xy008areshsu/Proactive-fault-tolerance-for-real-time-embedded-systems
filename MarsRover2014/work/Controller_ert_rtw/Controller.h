/*
 * File: Controller.h
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

#ifndef RTW_HEADER_Controller_h_
#define RTW_HEADER_Controller_h_
#include <stddef.h>
#include <string.h>
#ifndef Controller_COMMON_INCLUDES_
# define Controller_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* Controller_COMMON_INCLUDES_ */

#include "Controller_types.h"
#include "MW_target_hardware_resources.h"

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* External inputs (root inport signals with auto storage) */
typedef struct {
  real32_T Bearingtotarget;            /* '<Root>/Bearing to target' */
  real32_T DistanceRemainToTarget;     /* '<Root>/Distance to target' */
} ExternalInputs_Controller;

/* External outputs (root outports fed by signals with auto storage) */
typedef struct {
  real32_T LeftMotorDemand;            /* '<Root>/Left Motor Demand' */
  real32_T RightMotorDemand;           /* '<Root>/Right Motor Demand' */
} ExternalOutputs_Controller;

/* Parameters (auto storage) */
struct Parameters_Controller_ {
  real32_T IntervalTest_lowlimit;      /* Mask Parameter: IntervalTest_lowlimit
                                        * Referenced by: '<S2>/Lower Limit'
                                        */
  real32_T IntervalTest_uplimit;       /* Mask Parameter: IntervalTest_uplimit
                                        * Referenced by: '<S2>/Upper Limit'
                                        */
  real32_T Constant_Value;             /* Computed Parameter: Constant_Value
                                        * Referenced by: '<S1>/Constant'
                                        */
  real32_T Speedgain_Gain;             /* Computed Parameter: Speedgain_Gain
                                        * Referenced by: '<S1>/Speed gain'
                                        */
  real32_T Speedlimit_UpperSat;        /* Computed Parameter: Speedlimit_UpperSat
                                        * Referenced by: '<S1>/Speed limit'
                                        */
  real32_T Speedlimit_LowerSat;        /* Computed Parameter: Speedlimit_LowerSat
                                        * Referenced by: '<S1>/Speed limit'
                                        */
  real32_T Steeringgain_Gain;          /* Computed Parameter: Steeringgain_Gain
                                        * Referenced by: '<S1>/Steering gain'
                                        */
  real32_T Turnlimit_UpperSat;         /* Computed Parameter: Turnlimit_UpperSat
                                        * Referenced by: '<S1>/Turn limit'
                                        */
  real32_T Turnlimit_LowerSat;         /* Computed Parameter: Turnlimit_LowerSat
                                        * Referenced by: '<S1>/Turn limit'
                                        */
};

/* Real-time Model Data Structure */
struct tag_RTM_Controller {
  const char_T *errorStatus;
};

/* Block parameters (auto storage) */
extern Parameters_Controller Controller_P;

/* External inputs (root inport signals with auto storage) */
extern ExternalInputs_Controller Controller_U;

/* External outputs (root outports fed by signals with auto storage) */
extern ExternalOutputs_Controller Controller_Y;

/* Model entry point functions */
extern void Controller_initialize(void);
extern void Controller_step(void);
extern void Controller_terminate(void);

/* Real-time Model object */
extern RT_MODEL_Controller *const Controller_M;

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
 * hilite_system('SimulationModel/Controller')    - opens subsystem SimulationModel/Controller
 * hilite_system('SimulationModel/Controller/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'SimulationModel'
 * '<S1>'   : 'SimulationModel/Controller'
 * '<S2>'   : 'SimulationModel/Controller/Interval Test'
 */
#endif                                 /* RTW_HEADER_Controller_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */
