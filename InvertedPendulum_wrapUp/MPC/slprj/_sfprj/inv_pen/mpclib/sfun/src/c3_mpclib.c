/* Include files */

#include <stddef.h>
#include "blas.h"
#include "mpclib_sfun.h"
#include "c3_mpclib.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "mpclib_sfun_debug_macros.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(sfGlobalDebugInstanceStruct,S);

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)
#define c3_b_p                         (10.0)
#define c3_b_nu                        (1.0)
#define c3_b_isQP                      (true)
#define c3_b_ny                        (2.0)
#define c3_b_degrees                   (4.0)
#define c3_b_uoff                      (0.0)
#define c3_b_maxiter                   (200.0)
#define c3_b_nxQP                      (5.0)
#define c3_b_openloopflag              (false)
#define c3_b_lims_inport               (0.0)
#define c3_b_no_umin                   (1.0)
#define c3_b_no_umax                   (1.0)
#define c3_b_no_ymin                   (1.0)
#define c3_b_no_ymax                   (1.0)
#define c3_b_switch_inport             (0.0)
#define c3_b_no_switch                 (1.0)
#define c3_b_enable_value              (0.0)
#define c3_b_return_cost               (0.0)
#define c3_b_return_sequence           (0.0)
#define c3_b_no_ywt                    (1.0)
#define c3_b_no_duwt                   (1.0)
#define c3_b_no_rhoeps                 (1.0)
#define c3_b_Wy                        (0.0)
#define c3_b_Wdu                       (0.0)
#define c3_b_Jm                        (0.0)
#define c3_b_SuJm                      (0.0)
#define c3_b_I2JmWuI2Jm                (0.0)
#define c3_b_Su1                       (0.0)
#define c3_b_I1WuI2Jm                  (0.0)
#define c3_b_Sx                        (0.0)
#define c3_b_Hv                        (0.0)
#define c3_b_Wu                        (0.0)
#define c3_b_I1                        (0.0)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;
static const char * c3_debug_family_names[70] = { "isQP", "nu", "ny", "degrees",
  "Hinv", "Kx", "Ku1", "Kut", "Kr", "Kv", "Mlim", "Mx", "Mu1", "Mv", "z_degrees",
  "utarget", "p", "uoff", "yoff", "maxiter", "nxQP", "openloopflag",
  "lims_inport", "no_umin", "no_umax", "no_ymin", "no_ymax", "switch_inport",
  "no_switch", "enable_value", "return_cost", "H", "return_sequence",
  "blocking_moves", "Linv", "Ac", "no_ywt", "no_duwt", "no_rhoeps", "Wy", "Wdu",
  "Jm", "SuJm", "I2JmWuI2Jm", "Su1", "I1WuI2Jm", "Sx", "Hv", "Wu", "I1",
  "nargin", "nargout", "rseq", "vseq", "x", "old_u", "iA", "umin", "umax",
  "ymin", "ymax", "switch_in", "ywt", "duwt", "rhoeps", "u", "cost", "useq",
  "status", "iAout" };

/* Function Declarations */
static void initialize_c3_mpclib(SFc3_mpclibInstanceStruct *chartInstance);
static void initialize_params_c3_mpclib(SFc3_mpclibInstanceStruct *chartInstance);
static void enable_c3_mpclib(SFc3_mpclibInstanceStruct *chartInstance);
static void disable_c3_mpclib(SFc3_mpclibInstanceStruct *chartInstance);
static void c3_update_debugger_state_c3_mpclib(SFc3_mpclibInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c3_mpclib(SFc3_mpclibInstanceStruct
  *chartInstance);
static void set_sim_state_c3_mpclib(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_st);
static void finalize_c3_mpclib(SFc3_mpclibInstanceStruct *chartInstance);
static void sf_gateway_c3_mpclib(SFc3_mpclibInstanceStruct *chartInstance);
static void c3_chartstep_c3_mpclib(SFc3_mpclibInstanceStruct *chartInstance);
static void initSimStructsc3_mpclib(SFc3_mpclibInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber, uint32_T c3_instanceNumber);
static const mxArray *c3_sf_marshallOut(void *chartInstanceVoid, void *c3_inData);
static void c3_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_b_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_c_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static void c3_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static const mxArray *c3_d_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_e_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_f_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_g_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_h_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_i_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_j_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_k_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_l_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_m_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_n_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_o_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_p_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_q_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_r_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_s_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static const mxArray *c3_t_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static real_T c3_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_u, const char_T *c3_identifier);
static real_T c3_b_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_c_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_useq, const char_T *c3_identifier, real_T c3_y[10]);
static void c3_d_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[10]);
static void c3_e_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_iAout, const char_T *c3_identifier, boolean_T c3_y[50]);
static void c3_f_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, boolean_T c3_y[50]);
static const mxArray *c3_u_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData);
static int32_T c3_g_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static boolean_T c3_h_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void c3_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_i_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[16]);
static void c3_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_j_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[15]);
static void c3_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_k_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[3]);
static void c3_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_l_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[30]);
static void c3_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_m_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[60]);
static void c3_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_n_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[33]);
static void c3_k_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_o_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[46]);
static void c3_l_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_p_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[230]);
static void c3_m_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_q_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[506]);
static void c3_n_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_r_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[4]);
static void c3_o_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_s_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[2]);
static void c3_p_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_t_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[10]);
static void c3_q_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static void c3_u_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[184]);
static void c3_r_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData);
static uint8_T c3_v_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_b_is_active_c3_mpclib, const char_T *c3_identifier);
static uint8_T c3_w_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId);
static void init_dsm_address_info(SFc3_mpclibInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c3_mpclib(SFc3_mpclibInstanceStruct *chartInstance)
{
  chartInstance->c3_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c3_is_active_c3_mpclib = 0U;
}

static void initialize_params_c3_mpclib(SFc3_mpclibInstanceStruct *chartInstance)
{
  real_T c3_d0;
  real_T c3_d1;
  real_T c3_d2;
  real_T c3_d3;
  real_T c3_dv0[16];
  int32_T c3_i0;
  real_T c3_dv1[15];
  int32_T c3_i1;
  real_T c3_dv2[3];
  int32_T c3_i2;
  real_T c3_dv3[30];
  int32_T c3_i3;
  real_T c3_dv4[60];
  int32_T c3_i4;
  real_T c3_dv5[33];
  int32_T c3_i5;
  real_T c3_dv6[46];
  int32_T c3_i6;
  real_T c3_dv7[230];
  int32_T c3_i7;
  real_T c3_dv8[46];
  int32_T c3_i8;
  real_T c3_dv9[506];
  int32_T c3_i9;
  real_T c3_dv10[4];
  int32_T c3_i10;
  real_T c3_dv11[10];
  int32_T c3_i11;
  real_T c3_d4;
  real_T c3_d5;
  real_T c3_dv12[2];
  int32_T c3_i12;
  real_T c3_d6;
  real_T c3_d7;
  real_T c3_d8;
  real_T c3_d9;
  real_T c3_d10;
  real_T c3_d11;
  real_T c3_d12;
  real_T c3_d13;
  real_T c3_d14;
  real_T c3_d15;
  real_T c3_d16;
  real_T c3_d17;
  real_T c3_dv13[16];
  int32_T c3_i13;
  real_T c3_d18;
  real_T c3_dv14[10];
  int32_T c3_i14;
  real_T c3_dv15[16];
  int32_T c3_i15;
  real_T c3_dv16[184];
  int32_T c3_i16;
  real_T c3_d19;
  real_T c3_d20;
  real_T c3_d21;
  real_T c3_d22;
  real_T c3_d23;
  real_T c3_d24;
  real_T c3_d25;
  real_T c3_d26;
  real_T c3_d27;
  real_T c3_d28;
  real_T c3_d29;
  real_T c3_d30;
  real_T c3_d31;
  real_T c3_d32;
  sf_mex_import_named("isQP", sf_mex_get_sfun_param(chartInstance->S, 27, 0),
                      &c3_d0, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_isQP = (c3_d0 != 0.0);
  sf_mex_import_named("nu", sf_mex_get_sfun_param(chartInstance->S, 38, 0),
                      &c3_d1, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_nu = c3_d1;
  sf_mex_import_named("ny", sf_mex_get_sfun_param(chartInstance->S, 40, 0),
                      &c3_d2, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_ny = c3_d2;
  sf_mex_import_named("degrees", sf_mex_get_sfun_param(chartInstance->S, 25, 0),
                      &c3_d3, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_degrees = c3_d3;
  sf_mex_import_named("Hinv", sf_mex_get_sfun_param(chartInstance->S, 2, 0),
                      c3_dv0, 0, 0, 0U, 1, 0U, 2, 4, 4);
  for (c3_i0 = 0; c3_i0 < 16; c3_i0++) {
    chartInstance->c3_Hinv[c3_i0] = c3_dv0[c3_i0];
  }

  sf_mex_import_named("Kx", sf_mex_get_sfun_param(chartInstance->S, 12, 0),
                      c3_dv1, 0, 0, 0U, 1, 0U, 2, 5, 3);
  for (c3_i1 = 0; c3_i1 < 15; c3_i1++) {
    chartInstance->c3_Kx[c3_i1] = c3_dv1[c3_i1];
  }

  sf_mex_import_named("Ku1", sf_mex_get_sfun_param(chartInstance->S, 9, 0),
                      c3_dv2, 0, 0, 0U, 1, 0U, 2, 1, 3);
  for (c3_i2 = 0; c3_i2 < 3; c3_i2++) {
    chartInstance->c3_Ku1[c3_i2] = c3_dv2[c3_i2];
  }

  sf_mex_import_named("Kut", sf_mex_get_sfun_param(chartInstance->S, 10, 0),
                      c3_dv3, 0, 0, 0U, 1, 0U, 2, 10, 3);
  for (c3_i3 = 0; c3_i3 < 30; c3_i3++) {
    chartInstance->c3_Kut[c3_i3] = c3_dv3[c3_i3];
  }

  sf_mex_import_named("Kr", sf_mex_get_sfun_param(chartInstance->S, 8, 0),
                      c3_dv4, 0, 0, 0U, 1, 0U, 2, 20, 3);
  for (c3_i4 = 0; c3_i4 < 60; c3_i4++) {
    chartInstance->c3_Kr[c3_i4] = c3_dv4[c3_i4];
  }

  sf_mex_import_named("Kv", sf_mex_get_sfun_param(chartInstance->S, 11, 0),
                      c3_dv5, 0, 0, 0U, 1, 0U, 2, 11, 3);
  for (c3_i5 = 0; c3_i5 < 33; c3_i5++) {
    chartInstance->c3_Kv[c3_i5] = c3_dv5[c3_i5];
  }

  sf_mex_import_named("Mlim", sf_mex_get_sfun_param(chartInstance->S, 14, 0),
                      c3_dv6, 0, 0, 0U, 1, 0U, 1, 46);
  for (c3_i6 = 0; c3_i6 < 46; c3_i6++) {
    chartInstance->c3_Mlim[c3_i6] = c3_dv6[c3_i6];
  }

  sf_mex_import_named("Mx", sf_mex_get_sfun_param(chartInstance->S, 17, 0),
                      c3_dv7, 0, 0, 0U, 1, 0U, 2, 46, 5);
  for (c3_i7 = 0; c3_i7 < 230; c3_i7++) {
    chartInstance->c3_Mx[c3_i7] = c3_dv7[c3_i7];
  }

  sf_mex_import_named("Mu1", sf_mex_get_sfun_param(chartInstance->S, 15, 0),
                      c3_dv8, 0, 0, 0U, 1, 0U, 1, 46);
  for (c3_i8 = 0; c3_i8 < 46; c3_i8++) {
    chartInstance->c3_Mu1[c3_i8] = c3_dv8[c3_i8];
  }

  sf_mex_import_named("Mv", sf_mex_get_sfun_param(chartInstance->S, 16, 0),
                      c3_dv9, 0, 0, 0U, 1, 0U, 2, 46, 11);
  for (c3_i9 = 0; c3_i9 < 506; c3_i9++) {
    chartInstance->c3_Mv[c3_i9] = c3_dv9[c3_i9];
  }

  sf_mex_import_named("z_degrees", sf_mex_get_sfun_param(chartInstance->S, 49, 0),
                      c3_dv10, 0, 0, 0U, 1, 0U, 1, 4);
  for (c3_i10 = 0; c3_i10 < 4; c3_i10++) {
    chartInstance->c3_z_degrees[c3_i10] = c3_dv10[c3_i10];
  }

  sf_mex_import_named("utarget", sf_mex_get_sfun_param(chartInstance->S, 47, 0),
                      c3_dv11, 0, 0, 0U, 1, 0U, 1, 10);
  for (c3_i11 = 0; c3_i11 < 10; c3_i11++) {
    chartInstance->c3_utarget[c3_i11] = c3_dv11[c3_i11];
  }

  sf_mex_import_named("p", sf_mex_get_sfun_param(chartInstance->S, 42, 0),
                      &c3_d4, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_p = c3_d4;
  sf_mex_import_named("uoff", sf_mex_get_sfun_param(chartInstance->S, 46, 0),
                      &c3_d5, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_uoff = c3_d5;
  sf_mex_import_named("yoff", sf_mex_get_sfun_param(chartInstance->S, 48, 0),
                      c3_dv12, 0, 0, 0U, 1, 0U, 1, 2);
  for (c3_i12 = 0; c3_i12 < 2; c3_i12++) {
    chartInstance->c3_yoff[c3_i12] = c3_dv12[c3_i12];
  }

  sf_mex_import_named("maxiter", sf_mex_get_sfun_param(chartInstance->S, 29, 0),
                      &c3_d6, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_maxiter = c3_d6;
  sf_mex_import_named("nxQP", sf_mex_get_sfun_param(chartInstance->S, 39, 0),
                      &c3_d7, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_nxQP = c3_d7;
  sf_mex_import_named("openloopflag", sf_mex_get_sfun_param(chartInstance->S, 41,
    0), &c3_d8, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_openloopflag = (c3_d8 != 0.0);
  sf_mex_import_named("lims_inport", sf_mex_get_sfun_param(chartInstance->S, 28,
    0), &c3_d9, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_lims_inport = c3_d9;
  sf_mex_import_named("no_umin", sf_mex_get_sfun_param(chartInstance->S, 34, 0),
                      &c3_d10, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_no_umin = c3_d10;
  sf_mex_import_named("no_umax", sf_mex_get_sfun_param(chartInstance->S, 33, 0),
                      &c3_d11, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_no_umax = c3_d11;
  sf_mex_import_named("no_ymin", sf_mex_get_sfun_param(chartInstance->S, 36, 0),
                      &c3_d12, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_no_ymin = c3_d12;
  sf_mex_import_named("no_ymax", sf_mex_get_sfun_param(chartInstance->S, 35, 0),
                      &c3_d13, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_no_ymax = c3_d13;
  sf_mex_import_named("switch_inport", sf_mex_get_sfun_param(chartInstance->S,
    45, 0), &c3_d14, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_switch_inport = c3_d14;
  sf_mex_import_named("no_switch", sf_mex_get_sfun_param(chartInstance->S, 32, 0),
                      &c3_d15, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_no_switch = c3_d15;
  sf_mex_import_named("enable_value", sf_mex_get_sfun_param(chartInstance->S, 26,
    0), &c3_d16, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_enable_value = c3_d16;
  sf_mex_import_named("return_cost", sf_mex_get_sfun_param(chartInstance->S, 43,
    0), &c3_d17, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_return_cost = c3_d17;
  sf_mex_import_named("H", sf_mex_get_sfun_param(chartInstance->S, 1, 0),
                      c3_dv13, 0, 0, 0U, 1, 0U, 2, 4, 4);
  for (c3_i13 = 0; c3_i13 < 16; c3_i13++) {
    chartInstance->c3_H[c3_i13] = c3_dv13[c3_i13];
  }

  sf_mex_import_named("return_sequence", sf_mex_get_sfun_param(chartInstance->S,
    44, 0), &c3_d18, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_return_sequence = c3_d18;
  sf_mex_import_named("blocking_moves", sf_mex_get_sfun_param(chartInstance->S,
    24, 0), c3_dv14, 0, 0, 0U, 1, 0U, 2, 1, 10);
  for (c3_i14 = 0; c3_i14 < 10; c3_i14++) {
    chartInstance->c3_blocking_moves[c3_i14] = c3_dv14[c3_i14];
  }

  sf_mex_import_named("Linv", sf_mex_get_sfun_param(chartInstance->S, 13, 0),
                      c3_dv15, 0, 0, 0U, 1, 0U, 2, 4, 4);
  for (c3_i15 = 0; c3_i15 < 16; c3_i15++) {
    chartInstance->c3_Linv[c3_i15] = c3_dv15[c3_i15];
  }

  sf_mex_import_named("Ac", sf_mex_get_sfun_param(chartInstance->S, 0, 0),
                      c3_dv16, 0, 0, 0U, 1, 0U, 2, 46, 4);
  for (c3_i16 = 0; c3_i16 < 184; c3_i16++) {
    chartInstance->c3_Ac[c3_i16] = c3_dv16[c3_i16];
  }

  sf_mex_import_named("no_ywt", sf_mex_get_sfun_param(chartInstance->S, 37, 0),
                      &c3_d19, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_no_ywt = c3_d19;
  sf_mex_import_named("no_duwt", sf_mex_get_sfun_param(chartInstance->S, 30, 0),
                      &c3_d20, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_no_duwt = c3_d20;
  sf_mex_import_named("no_rhoeps", sf_mex_get_sfun_param(chartInstance->S, 31, 0),
                      &c3_d21, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_no_rhoeps = c3_d21;
  sf_mex_import_named("Wy", sf_mex_get_sfun_param(chartInstance->S, 23, 0),
                      &c3_d22, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_Wy = c3_d22;
  sf_mex_import_named("Wdu", sf_mex_get_sfun_param(chartInstance->S, 21, 0),
                      &c3_d23, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_Wdu = c3_d23;
  sf_mex_import_named("Jm", sf_mex_get_sfun_param(chartInstance->S, 7, 0),
                      &c3_d24, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_Jm = c3_d24;
  sf_mex_import_named("SuJm", sf_mex_get_sfun_param(chartInstance->S, 19, 0),
                      &c3_d25, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_SuJm = c3_d25;
  sf_mex_import_named("I2JmWuI2Jm", sf_mex_get_sfun_param(chartInstance->S, 6, 0),
                      &c3_d26, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_I2JmWuI2Jm = c3_d26;
  sf_mex_import_named("Su1", sf_mex_get_sfun_param(chartInstance->S, 18, 0),
                      &c3_d27, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_Su1 = c3_d27;
  sf_mex_import_named("I1WuI2Jm", sf_mex_get_sfun_param(chartInstance->S, 5, 0),
                      &c3_d28, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_I1WuI2Jm = c3_d28;
  sf_mex_import_named("Sx", sf_mex_get_sfun_param(chartInstance->S, 20, 0),
                      &c3_d29, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_Sx = c3_d29;
  sf_mex_import_named("Hv", sf_mex_get_sfun_param(chartInstance->S, 3, 0),
                      &c3_d30, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_Hv = c3_d30;
  sf_mex_import_named("Wu", sf_mex_get_sfun_param(chartInstance->S, 22, 0),
                      &c3_d31, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_Wu = c3_d31;
  sf_mex_import_named("I1", sf_mex_get_sfun_param(chartInstance->S, 4, 0),
                      &c3_d32, 0, 0, 0U, 0, 0U, 0);
  chartInstance->c3_I1 = c3_d32;
}

static void enable_c3_mpclib(SFc3_mpclibInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c3_mpclib(SFc3_mpclibInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void c3_update_debugger_state_c3_mpclib(SFc3_mpclibInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c3_mpclib(SFc3_mpclibInstanceStruct
  *chartInstance)
{
  const mxArray *c3_st;
  const mxArray *c3_y = NULL;
  real_T c3_hoistedGlobal;
  real_T c3_u;
  const mxArray *c3_b_y = NULL;
  int32_T c3_i17;
  boolean_T c3_b_u[50];
  const mxArray *c3_c_y = NULL;
  real_T c3_b_hoistedGlobal;
  real_T c3_c_u;
  const mxArray *c3_d_y = NULL;
  real_T c3_c_hoistedGlobal;
  real_T c3_d_u;
  const mxArray *c3_e_y = NULL;
  int32_T c3_i18;
  real_T c3_e_u[10];
  const mxArray *c3_f_y = NULL;
  uint8_T c3_d_hoistedGlobal;
  uint8_T c3_f_u;
  const mxArray *c3_g_y = NULL;
  real_T *c3_cost;
  real_T *c3_status;
  real_T *c3_g_u;
  real_T (*c3_useq)[10];
  boolean_T (*c3_iAout)[50];
  c3_iAout = (boolean_T (*)[50])ssGetOutputPortSignal(chartInstance->S, 5);
  c3_status = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c3_useq = (real_T (*)[10])ssGetOutputPortSignal(chartInstance->S, 3);
  c3_cost = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c3_g_u = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c3_st = NULL;
  c3_st = NULL;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_createcellmatrix(6, 1), false);
  c3_hoistedGlobal = *c3_cost;
  c3_u = c3_hoistedGlobal;
  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", &c3_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c3_y, 0, c3_b_y);
  for (c3_i17 = 0; c3_i17 < 50; c3_i17++) {
    c3_b_u[c3_i17] = (*c3_iAout)[c3_i17];
  }

  c3_c_y = NULL;
  sf_mex_assign(&c3_c_y, sf_mex_create("y", c3_b_u, 11, 0U, 1U, 0U, 1, 50),
                false);
  sf_mex_setcell(c3_y, 1, c3_c_y);
  c3_b_hoistedGlobal = *c3_status;
  c3_c_u = c3_b_hoistedGlobal;
  c3_d_y = NULL;
  sf_mex_assign(&c3_d_y, sf_mex_create("y", &c3_c_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c3_y, 2, c3_d_y);
  c3_c_hoistedGlobal = *c3_g_u;
  c3_d_u = c3_c_hoistedGlobal;
  c3_e_y = NULL;
  sf_mex_assign(&c3_e_y, sf_mex_create("y", &c3_d_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c3_y, 3, c3_e_y);
  for (c3_i18 = 0; c3_i18 < 10; c3_i18++) {
    c3_e_u[c3_i18] = (*c3_useq)[c3_i18];
  }

  c3_f_y = NULL;
  sf_mex_assign(&c3_f_y, sf_mex_create("y", c3_e_u, 0, 0U, 1U, 0U, 1, 10), false);
  sf_mex_setcell(c3_y, 4, c3_f_y);
  c3_d_hoistedGlobal = chartInstance->c3_is_active_c3_mpclib;
  c3_f_u = c3_d_hoistedGlobal;
  c3_g_y = NULL;
  sf_mex_assign(&c3_g_y, sf_mex_create("y", &c3_f_u, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c3_y, 5, c3_g_y);
  sf_mex_assign(&c3_st, c3_y, false);
  return c3_st;
}

static void set_sim_state_c3_mpclib(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_st)
{
  const mxArray *c3_u;
  boolean_T c3_bv0[50];
  int32_T c3_i19;
  real_T c3_dv17[10];
  int32_T c3_i20;
  real_T *c3_cost;
  real_T *c3_status;
  real_T *c3_b_u;
  boolean_T (*c3_iAout)[50];
  real_T (*c3_useq)[10];
  c3_iAout = (boolean_T (*)[50])ssGetOutputPortSignal(chartInstance->S, 5);
  c3_status = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c3_useq = (real_T (*)[10])ssGetOutputPortSignal(chartInstance->S, 3);
  c3_cost = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c3_b_u = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c3_doneDoubleBufferReInit = true;
  c3_u = sf_mex_dup(c3_st);
  *c3_cost = c3_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u,
    0)), "cost");
  c3_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 1)),
                        "iAout", c3_bv0);
  for (c3_i19 = 0; c3_i19 < 50; c3_i19++) {
    (*c3_iAout)[c3_i19] = c3_bv0[c3_i19];
  }

  *c3_status = c3_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u,
    2)), "status");
  *c3_b_u = c3_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 3)),
    "u");
  c3_c_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c3_u, 4)),
                        "useq", c3_dv17);
  for (c3_i20 = 0; c3_i20 < 10; c3_i20++) {
    (*c3_useq)[c3_i20] = c3_dv17[c3_i20];
  }

  chartInstance->c3_is_active_c3_mpclib = c3_v_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c3_u, 5)), "is_active_c3_mpclib");
  sf_mex_destroy(&c3_u);
  c3_update_debugger_state_c3_mpclib(chartInstance);
  sf_mex_destroy(&c3_st);
}

static void finalize_c3_mpclib(SFc3_mpclibInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void sf_gateway_c3_mpclib(SFc3_mpclibInstanceStruct *chartInstance)
{
  int32_T c3_i21;
  int32_T c3_i22;
  int32_T c3_i23;
  int32_T c3_i24;
  int32_T c3_i25;
  int32_T c3_i26;
  int32_T c3_i27;
  int32_T c3_i28;
  int32_T c3_i29;
  int32_T c3_i30;
  int32_T c3_i31;
  int32_T c3_i32;
  int32_T c3_i33;
  int32_T c3_i34;
  int32_T c3_i35;
  int32_T c3_i36;
  int32_T c3_i37;
  int32_T c3_i38;
  int32_T c3_i39;
  int32_T c3_i40;
  int32_T c3_i41;
  int32_T c3_i42;
  int32_T c3_i43;
  int32_T c3_i44;
  int32_T c3_i45;
  int32_T c3_i46;
  real_T *c3_old_u;
  real_T *c3_umin;
  real_T *c3_umax;
  real_T *c3_switch_in;
  real_T *c3_duwt;
  real_T *c3_rhoeps;
  real_T *c3_u;
  real_T *c3_cost;
  real_T *c3_status;
  boolean_T (*c3_iAout)[50];
  real_T (*c3_useq)[10];
  real_T (*c3_ywt)[2];
  real_T (*c3_ymax)[2];
  real_T (*c3_ymin)[2];
  boolean_T (*c3_iA)[50];
  real_T (*c3_x)[5];
  real_T (*c3_vseq)[11];
  real_T (*c3_rseq)[20];
  c3_iAout = (boolean_T (*)[50])ssGetOutputPortSignal(chartInstance->S, 5);
  c3_status = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c3_useq = (real_T (*)[10])ssGetOutputPortSignal(chartInstance->S, 3);
  c3_cost = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c3_u = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c3_rhoeps = (real_T *)ssGetInputPortSignal(chartInstance->S, 12);
  c3_duwt = (real_T *)ssGetInputPortSignal(chartInstance->S, 11);
  c3_ywt = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 10);
  c3_switch_in = (real_T *)ssGetInputPortSignal(chartInstance->S, 9);
  c3_ymax = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 8);
  c3_ymin = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 7);
  c3_umax = (real_T *)ssGetInputPortSignal(chartInstance->S, 6);
  c3_umin = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
  c3_iA = (boolean_T (*)[50])ssGetInputPortSignal(chartInstance->S, 4);
  c3_old_u = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c3_x = (real_T (*)[5])ssGetInputPortSignal(chartInstance->S, 2);
  c3_vseq = (real_T (*)[11])ssGetInputPortSignal(chartInstance->S, 1);
  c3_rseq = (real_T (*)[20])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_SYMBOL_SCOPE_PUSH(0U, 0U);
  _sfTime_ = sf_get_time(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG, 0U, chartInstance->c3_sfEvent);
  for (c3_i21 = 0; c3_i21 < 20; c3_i21++) {
    _SFD_DATA_RANGE_CHECK((*c3_rseq)[c3_i21], 0U);
  }

  for (c3_i22 = 0; c3_i22 < 11; c3_i22++) {
    _SFD_DATA_RANGE_CHECK((*c3_vseq)[c3_i22], 1U);
  }

  for (c3_i23 = 0; c3_i23 < 5; c3_i23++) {
    _SFD_DATA_RANGE_CHECK((*c3_x)[c3_i23], 2U);
  }

  _SFD_DATA_RANGE_CHECK(*c3_old_u, 3U);
  for (c3_i24 = 0; c3_i24 < 50; c3_i24++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*c3_iA)[c3_i24], 4U);
  }

  _SFD_DATA_RANGE_CHECK(*c3_umin, 5U);
  _SFD_DATA_RANGE_CHECK(*c3_umax, 6U);
  for (c3_i25 = 0; c3_i25 < 2; c3_i25++) {
    _SFD_DATA_RANGE_CHECK((*c3_ymin)[c3_i25], 7U);
  }

  for (c3_i26 = 0; c3_i26 < 2; c3_i26++) {
    _SFD_DATA_RANGE_CHECK((*c3_ymax)[c3_i26], 8U);
  }

  _SFD_DATA_RANGE_CHECK(*c3_switch_in, 9U);
  for (c3_i27 = 0; c3_i27 < 2; c3_i27++) {
    _SFD_DATA_RANGE_CHECK((*c3_ywt)[c3_i27], 10U);
  }

  _SFD_DATA_RANGE_CHECK(*c3_duwt, 11U);
  _SFD_DATA_RANGE_CHECK(*c3_rhoeps, 12U);
  chartInstance->c3_sfEvent = CALL_EVENT;
  c3_chartstep_c3_mpclib(chartInstance);
  _SFD_SYMBOL_SCOPE_POP();
  _SFD_CHECK_FOR_STATE_INCONSISTENCY(_mpclibMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
  _SFD_DATA_RANGE_CHECK(*c3_u, 13U);
  _SFD_DATA_RANGE_CHECK(*c3_cost, 14U);
  for (c3_i28 = 0; c3_i28 < 10; c3_i28++) {
    _SFD_DATA_RANGE_CHECK((*c3_useq)[c3_i28], 15U);
  }

  _SFD_DATA_RANGE_CHECK(*c3_status, 16U);
  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c3_isQP, 17U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_nu, 18U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_ny, 19U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_degrees, 20U);
  for (c3_i29 = 0; c3_i29 < 16; c3_i29++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_Hinv[c3_i29], 21U);
  }

  for (c3_i30 = 0; c3_i30 < 15; c3_i30++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_Kx[c3_i30], 22U);
  }

  for (c3_i31 = 0; c3_i31 < 3; c3_i31++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_Ku1[c3_i31], 23U);
  }

  for (c3_i32 = 0; c3_i32 < 30; c3_i32++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_Kut[c3_i32], 24U);
  }

  for (c3_i33 = 0; c3_i33 < 60; c3_i33++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_Kr[c3_i33], 25U);
  }

  for (c3_i34 = 0; c3_i34 < 33; c3_i34++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_Kv[c3_i34], 26U);
  }

  for (c3_i35 = 0; c3_i35 < 46; c3_i35++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_Mlim[c3_i35], 27U);
  }

  for (c3_i36 = 0; c3_i36 < 230; c3_i36++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_Mx[c3_i36], 28U);
  }

  for (c3_i37 = 0; c3_i37 < 46; c3_i37++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_Mu1[c3_i37], 29U);
  }

  for (c3_i38 = 0; c3_i38 < 506; c3_i38++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_Mv[c3_i38], 30U);
  }

  for (c3_i39 = 0; c3_i39 < 4; c3_i39++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_z_degrees[c3_i39], 31U);
  }

  for (c3_i40 = 0; c3_i40 < 10; c3_i40++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_utarget[c3_i40], 32U);
  }

  _SFD_DATA_RANGE_CHECK(chartInstance->c3_p, 33U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_uoff, 34U);
  for (c3_i41 = 0; c3_i41 < 2; c3_i41++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_yoff[c3_i41], 35U);
  }

  _SFD_DATA_RANGE_CHECK(chartInstance->c3_maxiter, 36U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_nxQP, 37U);
  _SFD_DATA_RANGE_CHECK((real_T)chartInstance->c3_openloopflag, 38U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_lims_inport, 39U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_no_umin, 40U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_no_umax, 41U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_no_ymin, 42U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_no_ymax, 43U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_switch_inport, 44U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_no_switch, 45U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_enable_value, 46U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_return_cost, 47U);
  for (c3_i42 = 0; c3_i42 < 16; c3_i42++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_H[c3_i42], 48U);
  }

  _SFD_DATA_RANGE_CHECK(chartInstance->c3_return_sequence, 49U);
  for (c3_i43 = 0; c3_i43 < 10; c3_i43++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_blocking_moves[c3_i43], 50U);
  }

  for (c3_i44 = 0; c3_i44 < 16; c3_i44++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_Linv[c3_i44], 51U);
  }

  for (c3_i45 = 0; c3_i45 < 184; c3_i45++) {
    _SFD_DATA_RANGE_CHECK(chartInstance->c3_Ac[c3_i45], 52U);
  }

  _SFD_DATA_RANGE_CHECK(chartInstance->c3_no_ywt, 53U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_no_duwt, 54U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_no_rhoeps, 55U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_Wy, 56U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_Wdu, 57U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_Jm, 58U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_SuJm, 59U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_I2JmWuI2Jm, 60U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_Su1, 61U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_I1WuI2Jm, 62U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_Sx, 63U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_Hv, 64U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_Wu, 65U);
  _SFD_DATA_RANGE_CHECK(chartInstance->c3_I1, 66U);
  for (c3_i46 = 0; c3_i46 < 50; c3_i46++) {
    _SFD_DATA_RANGE_CHECK((real_T)(*c3_iAout)[c3_i46], 67U);
  }
}

static void c3_chartstep_c3_mpclib(SFc3_mpclibInstanceStruct *chartInstance)
{
  real_T c3_hoistedGlobal;
  real_T c3_b_hoistedGlobal;
  real_T c3_c_hoistedGlobal;
  real_T c3_d_hoistedGlobal;
  real_T c3_e_hoistedGlobal;
  real_T c3_f_hoistedGlobal;
  int32_T c3_i47;
  real_T c3_rseq[20];
  int32_T c3_i48;
  real_T c3_vseq[11];
  int32_T c3_i49;
  real_T c3_x[5];
  real_T c3_old_u;
  int32_T c3_i50;
  boolean_T c3_iA[50];
  real_T c3_umin;
  real_T c3_umax;
  int32_T c3_i51;
  real_T c3_ymin[2];
  int32_T c3_i52;
  real_T c3_ymax[2];
  real_T c3_switch_in;
  int32_T c3_i53;
  real_T c3_ywt[2];
  real_T c3_duwt;
  real_T c3_rhoeps;
  uint32_T c3_debug_family_var_map[70];
  boolean_T c3_c_isQP;
  real_T c3_c_nu;
  real_T c3_c_ny;
  real_T c3_c_degrees;
  real_T c3_c_Hinv[16];
  real_T c3_c_Kx[15];
  real_T c3_c_Ku1[3];
  real_T c3_c_Kut[30];
  real_T c3_c_Kr[60];
  real_T c3_c_Kv[33];
  real_T c3_c_Mlim[46];
  real_T c3_c_Mx[230];
  real_T c3_c_Mu1[46];
  real_T c3_c_Mv[506];
  real_T c3_c_z_degrees[4];
  real_T c3_c_utarget[10];
  real_T c3_c_p;
  real_T c3_c_uoff;
  real_T c3_c_yoff[2];
  real_T c3_c_maxiter;
  real_T c3_c_nxQP;
  boolean_T c3_c_openloopflag;
  real_T c3_c_lims_inport;
  real_T c3_c_no_umin;
  real_T c3_c_no_umax;
  real_T c3_c_no_ymin;
  real_T c3_c_no_ymax;
  real_T c3_c_switch_inport;
  real_T c3_c_no_switch;
  real_T c3_c_enable_value;
  real_T c3_c_return_cost;
  real_T c3_c_H[16];
  real_T c3_c_return_sequence;
  real_T c3_c_blocking_moves[10];
  real_T c3_c_Linv[16];
  real_T c3_c_Ac[184];
  real_T c3_c_no_ywt;
  real_T c3_c_no_duwt;
  real_T c3_c_no_rhoeps;
  real_T c3_c_Wy;
  real_T c3_c_Wdu;
  real_T c3_c_Jm;
  real_T c3_c_SuJm;
  real_T c3_c_I2JmWuI2Jm;
  real_T c3_c_Su1;
  real_T c3_c_I1WuI2Jm;
  real_T c3_c_Sx;
  real_T c3_c_Hv;
  real_T c3_c_Wu;
  real_T c3_c_I1;
  real_T c3_nargin = 63.0;
  real_T c3_nargout = 5.0;
  real_T c3_u;
  real_T c3_cost;
  real_T c3_useq[10];
  real_T c3_status;
  boolean_T c3_iAout[50];
  int32_T c3_i54;
  static real_T c3_d_Ac[184] = { -0.00036328052791727641,
    -0.00090894352795221174, -0.0014523344173358365, -0.0036427175613747281,
    -0.0032674476148997047, -0.0082288506944112987, -0.0058108838201925191,
    -0.014717988074923466, -0.0090869314144345729, -0.023184505555004661,
    -0.013101975569318329, -0.033727419596500482, -0.017864596416665234,
    -0.046471604059489635, -0.023385694484220412, -0.061569328823867758,
    -0.029678644942328882, -0.079202139200009847, -0.036759482564682408,
    -0.099583099323828125, 0.00036328052791727641, 0.00090894352795221174,
    0.0014523344173358365, 0.0036427175613747281, 0.0032674476148997047,
    0.0082288506944112987, 0.0058108838201925191, 0.014717988074923466,
    0.0090869314144345729, 0.023184505555004661, 0.013101975569318329,
    0.033727419596500482, 0.017864596416665234, 0.046471604059489635,
    0.023385694484220412, 0.061569328823867758, 0.029678644942328882,
    0.079202139200009847, 0.036759482564682408, 0.099583099323828125, -1.0, -1.0,
    -1.0, 1.0, 1.0, 1.0, -0.0, -0.0, -0.00036328052791727641,
    -0.00090894352795221174, -0.0014523344173358365, -0.0036427175613747281,
    -0.0032674476148997047, -0.0082288506944112987, -0.0058108838201925191,
    -0.014717988074923466, -0.0090869314144345729, -0.023184505555004661,
    -0.013101975569318329, -0.033727419596500482, -0.017864596416665234,
    -0.046471604059489635, -0.023385694484220412, -0.061569328823867758,
    -0.029678644942328882, -0.079202139200009847, -0.0, -0.0,
    0.00036328052791727641, 0.00090894352795221174, 0.0014523344173358365,
    0.0036427175613747281, 0.0032674476148997047, 0.0082288506944112987,
    0.0058108838201925191, 0.014717988074923466, 0.0090869314144345729,
    0.023184505555004661, 0.013101975569318329, 0.033727419596500482,
    0.017864596416665234, 0.046471604059489635, 0.023385694484220412,
    0.061569328823867758, 0.029678644942328882, 0.079202139200009847, -0.0, -1.0,
    -1.0, -0.0, 1.0, 1.0, -0.0, -0.0, -0.0, -0.0, -0.00036328052791727641,
    -0.00090894352795221174, -0.0014523344173358365, -0.0036427175613747281,
    -0.0032674476148997047, -0.0082288506944112987, -0.0058108838201925191,
    -0.014717988074923466, -0.0090869314144345729, -0.023184505555004661,
    -0.013101975569318329, -0.033727419596500482, -0.017864596416665234,
    -0.046471604059489635, -0.023385694484220412, -0.061569328823867758, -0.0,
    -0.0, -0.0, -0.0, 0.00036328052791727641, 0.00090894352795221174,
    0.0014523344173358365, 0.0036427175613747281, 0.0032674476148997047,
    0.0082288506944112987, 0.0058108838201925191, 0.014717988074923466,
    0.0090869314144345729, 0.023184505555004661, 0.013101975569318329,
    0.033727419596500482, 0.017864596416665234, 0.046471604059489635,
    0.023385694484220412, 0.061569328823867758, -0.0, -0.0, -1.0, -0.0, -0.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0 };

  int32_T c3_i55;
  static real_T c3_d_Linv[16] = { 0.012879481041163827, -0.21670594465305731,
    0.97923454554007938, 0.0, 0.0, 0.28292534589975354, -2.4313075825807404, 0.0,
    0.0, 0.0, 1.5526128630882652, 0.0, 0.0, 0.0, 0.0, 0.00014142135623730951 };

  int32_T c3_i56;
  static real_T c3_d_blocking_moves[10] = { 1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 0.0,
    0.0, 0.0, 0.0 };

  int32_T c3_i57;
  static real_T c3_d_H[16] = { 6028.4168033446, 4617.45042310221,
    3428.5483288741116, 0.0, 4617.45042310221, 3549.217034350188,
    2645.6507084770183, 0.0, 3428.5483288741116, 2645.6507084770183,
    1980.9714400637881, 0.0, 0.0, 0.0, 0.0, 5.0E+7 };

  int32_T c3_i58;
  int32_T c3_i59;
  int32_T c3_i60;
  int32_T c3_i61;
  int32_T c3_i62;
  static real_T c3_d_Mu1[46] = { -0.00036328052791727641,
    -0.00090894352795221174, -0.0014523344173358365, -0.0036427175613747281,
    -0.0032674476148997047, -0.0082288506944112987, -0.0058108838201925191,
    -0.014717988074923466, -0.0090869314144345729, -0.023184505555004661,
    -0.013101975569318329, -0.033727419596500482, -0.017864596416665234,
    -0.046471604059489635, -0.023385694484220412, -0.061569328823867758,
    -0.029678644942328882, -0.079202139200009847, -0.036759482564682408,
    -0.099583099323828125, 0.00036328052791727641, 0.00090894352795221174,
    0.0014523344173358365, 0.0036427175613747281, 0.0032674476148997047,
    0.0082288506944112987, 0.0058108838201925191, 0.014717988074923466,
    0.0090869314144345729, 0.023184505555004661, 0.013101975569318329,
    0.033727419596500482, 0.017864596416665234, 0.046471604059489635,
    0.023385694484220412, 0.061569328823867758, 0.029678644942328882,
    0.079202139200009847, 0.036759482564682408, 0.099583099323828125, -1.0, -1.0,
    -1.0, 1.0, 1.0, 1.0 };

  int32_T c3_i63;
  static real_T c3_d_Mx[230] = { -1.0, -0.0, -1.0, -0.0, -1.0, -0.0, -1.0, -0.0,
    -1.0, -0.0, -1.0, -0.0, -1.0, -0.0, -1.0, -0.0, -1.0, -0.0, -1.0, -0.0, 1.0,
    0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0,
    1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.019963671947208269,
    9.0894352795221192E-5, -0.039854766558266412, 0.00036427175613747294,
    -0.059673255238510026, 0.00082288506944113013, -0.079418911617980745,
    0.0014717988074923471, -0.099091306858556535, 0.0023184505555004665,
    -0.11868980244306816, 0.0033727419596500494, -0.13821354035833347,
    0.0046471604059489646, -0.15766143055157794, 0.0061569328823867769,
    -0.17703213550576707, 0.0079202139200009875, -0.19632405174353174,
    0.0099583099323828153, 0.019963671947208269, -9.0894352795221192E-5,
    0.039854766558266412, -0.00036427175613747294, 0.059673255238510026,
    -0.00082288506944113013, 0.079418911617980745, -0.0014717988074923471,
    0.099091306858556535, -0.0023184505555004665, 0.11868980244306816,
    -0.0033727419596500494, 0.13821354035833347, -0.0046471604059489646,
    0.15766143055157794, -0.0061569328823867769, 0.17703213550576707,
    -0.0079202139200009875, 0.19632405174353174, -0.0099583099323828153, 0.0,
    0.0, 0.0, 0.0, 0.0, 0.0, -0.00053444799629476973, -1.0062412644269734,
    -0.0021418746510364611, -1.0250364866318467, -0.00483846645054517,
    -1.0566105114032032, -0.0086540021401051454, -1.1013475277715139,
    -0.013632213837171036, -1.1597957406960058, -0.019831322045004252,
    -1.232674086543184, -0.027324751109844447, -1.3208810745942514,
    -0.036202033912122178, -1.4255058632940765, -0.046569916937601222,
    -1.5478417077662052, -0.058553679367021334, -1.6894019446128352,
    0.00053444799629476973, 1.0062412644269734, 0.0021418746510364611,
    1.0250364866318467, 0.00483846645054517, 1.0566105114032032,
    0.0086540021401051454, 1.1013475277715139, 0.013632213837171036,
    1.1597957406960058, 0.019831322045004252, 1.232674086543184,
    0.027324751109844447, 1.3208810745942514, 0.036202033912122178,
    1.4255058632940765, 0.046569916937601222, 1.5478417077662052,
    0.058553679367021334, 1.6894019446128352, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
    -3.5625841145916218E-6, -0.020041593836139883, -2.8528137397835878E-5,
    -0.04033330886731374, -9.6495655095394316E-5, -0.061128209961158558,
    -0.00022952332519571408, -0.0826854462067362, -0.00045040369920622421,
    -0.10527348116488458, -0.00078294781511922243, -0.12917343687464308,
    -0.0012522818123364764, -0.15468259327076955, -0.001885159731501382,
    -0.18211808657491696, -0.0027102963913475287, -0.21182085267289896,
    -0.0037587244822630088, -0.24415986451280514, 3.5625841145916218E-6,
    0.020041593836139883, 2.8528137397835878E-5, 0.04033330886731374,
    9.6495655095394316E-5, 0.061128209961158558, 0.00022952332519571408,
    0.0826854462067362, 0.00045040369920622421, 0.10527348116488458,
    0.00078294781511922243, 0.12917343687464308, 0.0012522818123364764,
    0.15468259327076955, 0.001885159731501382, 0.18211808657491696,
    0.0027102963913475287, 0.21182085267289896, 0.0037587244822630088,
    0.24415986451280514, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, -0.0, -1.0, -0.0, -1.0,
    -0.0, -1.0, -0.0, -1.0, -0.0, -1.0, -0.0, -1.0, -0.0, -1.0, -0.0, -1.0, -0.0,
    -1.0, -0.0, -1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0,
    0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 };

  int32_T c3_i64;
  static real_T c3_d_Mlim[46] = { 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0, 1.0,
    1.0, 25.0, 25.0, 25.0, 25.0, 25.0, 25.0 };

  int32_T c3_i65;
  int32_T c3_i66;
  static real_T c3_d_Kr[60] = { -0.00036328052791727641, -227.23588198805294,
    -0.0014523344173358365, -910.679390343682, -0.0032674476148997047,
    -2057.2126736028245, -0.0058108838201925191, -3679.4970187308668,
    -0.0090869314144345729, -5796.126388751165, -0.013101975569318329,
    -8431.8548991251209, -0.017864596416665234, -11617.901014872408,
    -0.023385694484220412, -15392.332205966939, -0.029678644942328882,
    -19800.534800002461, -0.036759482564682408, -24895.774830957031, -0.0, -0.0,
    -0.00036328052791727641, -227.23588198805294, -0.0014523344173358365,
    -910.679390343682, -0.0032674476148997047, -2057.2126736028245,
    -0.0058108838201925191, -3679.4970187308668, -0.0090869314144345729,
    -5796.126388751165, -0.013101975569318329, -8431.8548991251209,
    -0.017864596416665234, -11617.901014872408, -0.023385694484220412,
    -15392.332205966939, -0.029678644942328882, -19800.534800002461, -0.0, -0.0,
    -0.0, -0.0, -0.00036328052791727641, -227.23588198805294,
    -0.0014523344173358365, -910.679390343682, -0.0032674476148997047,
    -2057.2126736028245, -0.0058108838201925191, -3679.4970187308668,
    -0.0090869314144345729, -5796.126388751165, -0.013101975569318329,
    -8431.8548991251209, -0.017864596416665234, -11617.901014872408,
    -0.023385694484220412, -15392.332205966939 };

  int32_T c3_i67;
  int32_T c3_i68;
  static real_T c3_d_Ku1[3] = { 6028.4168033446, 4617.45042310221,
    3428.5483288741111 };

  int32_T c3_i69;
  static real_T c3_d_Kx[15] = { 0.14077127177199517, -602.81953632048237,
    134499.05765834541, 17043.654164312389, 92809.149104340555,
    0.10401178920731277, -461.728169956972, 99847.887817254537,
    12885.998097065893, 67913.374273383524, 0.074333144264983886,
    -342.84240960026534, 71826.804496082332, 9432.310435187781,
    48112.839473381056 };

  int32_T c3_i70;
  static real_T c3_d_Hinv[16] = { 1.0060276426589494, -2.4421319800460997,
    1.5203721513859187, 0.0, -2.4421319800460997, 5.9913033124670987,
    -3.7748794268388921, 0.0, 1.5203721513859187, -3.7748794268388921,
    2.41060670262714, 0.0, 0.0, 0.0, 0.0, 2.0E-8 };

  int32_T c3_i71;
  int32_T c3_i72;
  int32_T c3_i73;
  real_T c3_b_u[20];
  const mxArray *c3_y = NULL;
  int32_T c3_i74;
  real_T c3_c_u[11];
  const mxArray *c3_b_y = NULL;
  real_T c3_d_u;
  const mxArray *c3_c_y = NULL;
  real_T c3_e_u;
  const mxArray *c3_d_y = NULL;
  int32_T c3_i75;
  real_T c3_f_u[2];
  const mxArray *c3_e_y = NULL;
  int32_T c3_i76;
  real_T c3_g_u[2];
  const mxArray *c3_f_y = NULL;
  real_T c3_h_u;
  const mxArray *c3_g_y = NULL;
  int32_T c3_i77;
  real_T c3_i_u[5];
  const mxArray *c3_h_y = NULL;
  real_T c3_j_u;
  const mxArray *c3_i_y = NULL;
  int32_T c3_i78;
  boolean_T c3_k_u[50];
  const mxArray *c3_j_y = NULL;
  boolean_T c3_l_u;
  const mxArray *c3_k_y = NULL;
  real_T c3_m_u;
  const mxArray *c3_l_y = NULL;
  real_T c3_n_u;
  const mxArray *c3_m_y = NULL;
  real_T c3_o_u;
  const mxArray *c3_n_y = NULL;
  int32_T c3_i79;
  real_T c3_p_u[16];
  const mxArray *c3_o_y = NULL;
  int32_T c3_i80;
  real_T c3_q_u[15];
  const mxArray *c3_p_y = NULL;
  int32_T c3_i81;
  real_T c3_r_u[3];
  const mxArray *c3_q_y = NULL;
  int32_T c3_i82;
  real_T c3_s_u[30];
  const mxArray *c3_r_y = NULL;
  int32_T c3_i83;
  real_T c3_t_u[60];
  const mxArray *c3_s_y = NULL;
  int32_T c3_i84;
  real_T c3_u_u[33];
  const mxArray *c3_t_y = NULL;
  int32_T c3_i85;
  real_T c3_v_u[46];
  const mxArray *c3_u_y = NULL;
  int32_T c3_i86;
  real_T c3_w_u[230];
  const mxArray *c3_v_y = NULL;
  int32_T c3_i87;
  real_T c3_x_u[46];
  const mxArray *c3_w_y = NULL;
  int32_T c3_i88;
  real_T c3_y_u[506];
  const mxArray *c3_x_y = NULL;
  int32_T c3_i89;
  real_T c3_ab_u[4];
  const mxArray *c3_y_y = NULL;
  int32_T c3_i90;
  real_T c3_bb_u[10];
  const mxArray *c3_ab_y = NULL;
  real_T c3_cb_u;
  const mxArray *c3_bb_y = NULL;
  real_T c3_db_u;
  const mxArray *c3_cb_y = NULL;
  int32_T c3_i91;
  real_T c3_eb_u[2];
  const mxArray *c3_db_y = NULL;
  real_T c3_fb_u;
  const mxArray *c3_eb_y = NULL;
  real_T c3_gb_u;
  const mxArray *c3_fb_y = NULL;
  boolean_T c3_hb_u;
  const mxArray *c3_gb_y = NULL;
  real_T c3_ib_u;
  const mxArray *c3_hb_y = NULL;
  real_T c3_jb_u;
  const mxArray *c3_ib_y = NULL;
  real_T c3_kb_u;
  const mxArray *c3_jb_y = NULL;
  real_T c3_lb_u;
  const mxArray *c3_kb_y = NULL;
  real_T c3_mb_u;
  const mxArray *c3_lb_y = NULL;
  real_T c3_nb_u;
  const mxArray *c3_mb_y = NULL;
  real_T c3_ob_u;
  const mxArray *c3_nb_y = NULL;
  real_T c3_pb_u;
  const mxArray *c3_ob_y = NULL;
  real_T c3_qb_u;
  const mxArray *c3_pb_y = NULL;
  int32_T c3_i92;
  real_T c3_rb_u[16];
  const mxArray *c3_qb_y = NULL;
  real_T c3_sb_u;
  const mxArray *c3_rb_y = NULL;
  int32_T c3_i93;
  real_T c3_tb_u[10];
  const mxArray *c3_sb_y = NULL;
  int32_T c3_i94;
  real_T c3_ub_u[16];
  const mxArray *c3_tb_y = NULL;
  int32_T c3_i95;
  real_T c3_vb_u[184];
  const mxArray *c3_ub_y = NULL;
  int32_T c3_i96;
  real_T c3_wb_u[2];
  const mxArray *c3_vb_y = NULL;
  real_T c3_xb_u;
  const mxArray *c3_wb_y = NULL;
  real_T c3_yb_u;
  const mxArray *c3_xb_y = NULL;
  real_T c3_ac_u;
  const mxArray *c3_yb_y = NULL;
  real_T c3_bc_u;
  const mxArray *c3_ac_y = NULL;
  real_T c3_cc_u;
  const mxArray *c3_bc_y = NULL;
  real_T c3_dc_u;
  const mxArray *c3_cc_y = NULL;
  real_T c3_ec_u;
  const mxArray *c3_dc_y = NULL;
  real_T c3_fc_u;
  const mxArray *c3_ec_y = NULL;
  real_T c3_gc_u;
  const mxArray *c3_fc_y = NULL;
  real_T c3_hc_u;
  const mxArray *c3_gc_y = NULL;
  real_T c3_ic_u;
  const mxArray *c3_hc_y = NULL;
  real_T c3_jc_u;
  const mxArray *c3_ic_y = NULL;
  real_T c3_kc_u;
  const mxArray *c3_jc_y = NULL;
  real_T c3_lc_u;
  const mxArray *c3_kc_y = NULL;
  real_T c3_mc_u;
  const mxArray *c3_lc_y = NULL;
  real_T c3_nc_u;
  const mxArray *c3_mc_y = NULL;
  const mxArray *c3_b_iAout = NULL;
  const mxArray *c3_b_status = NULL;
  const mxArray *c3_b_useq = NULL;
  const mxArray *c3_b_cost = NULL;
  const mxArray *c3_oc_u = NULL;
  real_T c3_dv18[10];
  int32_T c3_i97;
  boolean_T c3_bv1[50];
  int32_T c3_i98;
  int32_T c3_i99;
  int32_T c3_i100;
  real_T *c3_b_old_u;
  real_T *c3_b_umin;
  real_T *c3_b_umax;
  real_T *c3_b_switch_in;
  real_T *c3_b_duwt;
  real_T *c3_b_rhoeps;
  real_T *c3_pc_u;
  real_T *c3_c_cost;
  real_T *c3_c_status;
  real_T (*c3_c_useq)[10];
  boolean_T (*c3_c_iAout)[50];
  real_T (*c3_b_ywt)[2];
  real_T (*c3_b_ymax)[2];
  real_T (*c3_b_ymin)[2];
  boolean_T (*c3_b_iA)[50];
  real_T (*c3_b_x)[5];
  real_T (*c3_b_vseq)[11];
  real_T (*c3_b_rseq)[20];
  c3_c_iAout = (boolean_T (*)[50])ssGetOutputPortSignal(chartInstance->S, 5);
  c3_c_status = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
  c3_c_useq = (real_T (*)[10])ssGetOutputPortSignal(chartInstance->S, 3);
  c3_c_cost = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c3_pc_u = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c3_b_rhoeps = (real_T *)ssGetInputPortSignal(chartInstance->S, 12);
  c3_b_duwt = (real_T *)ssGetInputPortSignal(chartInstance->S, 11);
  c3_b_ywt = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 10);
  c3_b_switch_in = (real_T *)ssGetInputPortSignal(chartInstance->S, 9);
  c3_b_ymax = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 8);
  c3_b_ymin = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 7);
  c3_b_umax = (real_T *)ssGetInputPortSignal(chartInstance->S, 6);
  c3_b_umin = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
  c3_b_iA = (boolean_T (*)[50])ssGetInputPortSignal(chartInstance->S, 4);
  c3_b_old_u = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
  c3_b_x = (real_T (*)[5])ssGetInputPortSignal(chartInstance->S, 2);
  c3_b_vseq = (real_T (*)[11])ssGetInputPortSignal(chartInstance->S, 1);
  c3_b_rseq = (real_T (*)[20])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG, 0U, chartInstance->c3_sfEvent);
  c3_hoistedGlobal = *c3_b_old_u;
  c3_b_hoistedGlobal = *c3_b_umin;
  c3_c_hoistedGlobal = *c3_b_umax;
  c3_d_hoistedGlobal = *c3_b_switch_in;
  c3_e_hoistedGlobal = *c3_b_duwt;
  c3_f_hoistedGlobal = *c3_b_rhoeps;
  for (c3_i47 = 0; c3_i47 < 20; c3_i47++) {
    c3_rseq[c3_i47] = (*c3_b_rseq)[c3_i47];
  }

  for (c3_i48 = 0; c3_i48 < 11; c3_i48++) {
    c3_vseq[c3_i48] = (*c3_b_vseq)[c3_i48];
  }

  for (c3_i49 = 0; c3_i49 < 5; c3_i49++) {
    c3_x[c3_i49] = (*c3_b_x)[c3_i49];
  }

  c3_old_u = c3_hoistedGlobal;
  for (c3_i50 = 0; c3_i50 < 50; c3_i50++) {
    c3_iA[c3_i50] = (*c3_b_iA)[c3_i50];
  }

  c3_umin = c3_b_hoistedGlobal;
  c3_umax = c3_c_hoistedGlobal;
  for (c3_i51 = 0; c3_i51 < 2; c3_i51++) {
    c3_ymin[c3_i51] = (*c3_b_ymin)[c3_i51];
  }

  for (c3_i52 = 0; c3_i52 < 2; c3_i52++) {
    c3_ymax[c3_i52] = (*c3_b_ymax)[c3_i52];
  }

  c3_switch_in = c3_d_hoistedGlobal;
  for (c3_i53 = 0; c3_i53 < 2; c3_i53++) {
    c3_ywt[c3_i53] = (*c3_b_ywt)[c3_i53];
  }

  c3_duwt = c3_e_hoistedGlobal;
  c3_rhoeps = c3_f_hoistedGlobal;
  _SFD_SYMBOL_SCOPE_PUSH_EML(0U, 70U, 70U, c3_debug_family_names,
    c3_debug_family_var_map);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_isQP, 0U, c3_k_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_nu, 1U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_ny, 2U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_degrees, 3U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_Hinv, 4U, c3_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_Kx, 5U, c3_t_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_Ku1, 6U, c3_s_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_Kut, 7U, c3_r_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_Kr, 8U, c3_q_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_Kv, 9U, c3_p_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_Mlim, 10U, c3_n_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_Mx, 11U, c3_o_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_Mu1, 12U, c3_n_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_Mv, 13U, c3_m_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_z_degrees, 14U, c3_l_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_utarget, 15U, c3_c_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_p, 16U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_uoff, 17U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_yoff, 18U, c3_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_maxiter, 19U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_nxQP, 20U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_openloopflag, 21U, c3_k_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_lims_inport, 22U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_no_umin, 23U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_no_umax, 24U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_no_ymin, 25U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_no_ymax, 26U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_switch_inport, 27U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_no_switch, 28U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_enable_value, 29U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_return_cost, 30U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_H, 31U, c3_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_return_sequence, 32U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_blocking_moves, 33U, c3_j_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_Linv, 34U, c3_i_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_c_Ac, 35U, c3_h_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_no_ywt, 36U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_no_duwt, 37U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_no_rhoeps, 38U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_Wy, 39U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_Wdu, 40U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_Jm, 41U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_SuJm, 42U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_I2JmWuI2Jm, 43U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_Su1, 44U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_I1WuI2Jm, 45U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_Sx, 46U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_Hv, 47U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_Wu, 48U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_c_I1, 49U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargin, 50U, c3_b_sf_marshallOut,
    c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_nargout, 51U, c3_b_sf_marshallOut,
    c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_rseq, 52U, c3_g_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_vseq, 53U, c3_f_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_x, 54U, c3_e_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_old_u, 55U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_iA, 56U, c3_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_umin, 57U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_umax, 58U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_ymin, 59U, c3_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_ymax, 60U, c3_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_switch_in, 61U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(c3_ywt, 62U, c3_d_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_duwt, 63U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML(&c3_rhoeps, 64U, c3_b_sf_marshallOut);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_u, 65U, c3_b_sf_marshallOut,
    c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_cost, 66U, c3_b_sf_marshallOut,
    c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_useq, 67U, c3_c_sf_marshallOut,
    c3_c_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(&c3_status, 68U, c3_b_sf_marshallOut,
    c3_b_sf_marshallIn);
  _SFD_SYMBOL_SCOPE_ADD_EML_IMPORTABLE(c3_iAout, 69U, c3_sf_marshallOut,
    c3_sf_marshallIn);
  c3_c_I1 = c3_b_I1;
  c3_c_Wu = c3_b_Wu;
  c3_c_Hv = c3_b_Hv;
  c3_c_Sx = c3_b_Sx;
  c3_c_I1WuI2Jm = c3_b_I1WuI2Jm;
  c3_c_Su1 = c3_b_Su1;
  c3_c_I2JmWuI2Jm = c3_b_I2JmWuI2Jm;
  c3_c_SuJm = c3_b_SuJm;
  c3_c_Jm = c3_b_Jm;
  c3_c_Wdu = c3_b_Wdu;
  c3_c_Wy = c3_b_Wy;
  c3_c_no_rhoeps = c3_b_no_rhoeps;
  c3_c_no_duwt = c3_b_no_duwt;
  c3_c_no_ywt = c3_b_no_ywt;
  for (c3_i54 = 0; c3_i54 < 184; c3_i54++) {
    c3_c_Ac[c3_i54] = c3_d_Ac[c3_i54];
  }

  for (c3_i55 = 0; c3_i55 < 16; c3_i55++) {
    c3_c_Linv[c3_i55] = c3_d_Linv[c3_i55];
  }

  for (c3_i56 = 0; c3_i56 < 10; c3_i56++) {
    c3_c_blocking_moves[c3_i56] = c3_d_blocking_moves[c3_i56];
  }

  c3_c_return_sequence = c3_b_return_sequence;
  for (c3_i57 = 0; c3_i57 < 16; c3_i57++) {
    c3_c_H[c3_i57] = c3_d_H[c3_i57];
  }

  c3_c_return_cost = c3_b_return_cost;
  c3_c_enable_value = c3_b_enable_value;
  c3_c_no_switch = c3_b_no_switch;
  c3_c_switch_inport = c3_b_switch_inport;
  c3_c_no_ymax = c3_b_no_ymax;
  c3_c_no_ymin = c3_b_no_ymin;
  c3_c_no_umax = c3_b_no_umax;
  c3_c_no_umin = c3_b_no_umin;
  c3_c_lims_inport = c3_b_lims_inport;
  c3_c_openloopflag = c3_b_openloopflag;
  c3_c_nxQP = c3_b_nxQP;
  c3_c_maxiter = c3_b_maxiter;
  for (c3_i58 = 0; c3_i58 < 2; c3_i58++) {
    c3_c_yoff[c3_i58] = 0.0;
  }

  c3_c_uoff = c3_b_uoff;
  c3_c_p = c3_b_p;
  for (c3_i59 = 0; c3_i59 < 10; c3_i59++) {
    c3_c_utarget[c3_i59] = 0.0;
  }

  for (c3_i60 = 0; c3_i60 < 4; c3_i60++) {
    c3_c_z_degrees[c3_i60] = 0.0;
  }

  for (c3_i61 = 0; c3_i61 < 506; c3_i61++) {
    c3_c_Mv[c3_i61] = -0.0;
  }

  for (c3_i62 = 0; c3_i62 < 46; c3_i62++) {
    c3_c_Mu1[c3_i62] = c3_d_Mu1[c3_i62];
  }

  for (c3_i63 = 0; c3_i63 < 230; c3_i63++) {
    c3_c_Mx[c3_i63] = c3_d_Mx[c3_i63];
  }

  for (c3_i64 = 0; c3_i64 < 46; c3_i64++) {
    c3_c_Mlim[c3_i64] = c3_d_Mlim[c3_i64];
  }

  for (c3_i65 = 0; c3_i65 < 33; c3_i65++) {
    c3_c_Kv[c3_i65] = 0.0;
  }

  for (c3_i66 = 0; c3_i66 < 60; c3_i66++) {
    c3_c_Kr[c3_i66] = c3_d_Kr[c3_i66];
  }

  for (c3_i67 = 0; c3_i67 < 30; c3_i67++) {
    c3_c_Kut[c3_i67] = 0.0;
  }

  for (c3_i68 = 0; c3_i68 < 3; c3_i68++) {
    c3_c_Ku1[c3_i68] = c3_d_Ku1[c3_i68];
  }

  for (c3_i69 = 0; c3_i69 < 15; c3_i69++) {
    c3_c_Kx[c3_i69] = c3_d_Kx[c3_i69];
  }

  for (c3_i70 = 0; c3_i70 < 16; c3_i70++) {
    c3_c_Hinv[c3_i70] = c3_d_Hinv[c3_i70];
  }

  c3_c_degrees = c3_b_degrees;
  c3_c_ny = c3_b_ny;
  c3_c_nu = c3_b_nu;
  c3_c_isQP = c3_b_isQP;
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 8);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 9);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 10);
  CV_EML_COND(0, 1, 0, true);
  CV_EML_COND(0, 1, 1, false);
  CV_EML_COND(0, 1, 2, false);
  CV_EML_MCDC(0, 1, 0, true);
  CV_EML_IF(0, 1, 0, true);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 12);
  c3_u = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 13);
  c3_cost = 0.0;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 14);
  for (c3_i71 = 0; c3_i71 < 10; c3_i71++) {
    c3_useq[c3_i71] = 0.0;
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 15);
  c3_status = 1.0;
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 16);
  for (c3_i72 = 0; c3_i72 < 50; c3_i72++) {
    c3_iAout[c3_i72] = false;
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 17);
  CV_EML_IF(0, 1, 1, true);
  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, 18);
  for (c3_i73 = 0; c3_i73 < 20; c3_i73++) {
    c3_b_u[c3_i73] = c3_rseq[c3_i73];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_b_u, 0, 0U, 1U, 0U, 1, 20), false);
  for (c3_i74 = 0; c3_i74 < 11; c3_i74++) {
    c3_c_u[c3_i74] = c3_vseq[c3_i74];
  }

  c3_b_y = NULL;
  sf_mex_assign(&c3_b_y, sf_mex_create("y", c3_c_u, 0, 0U, 1U, 0U, 1, 11), false);
  c3_d_u = c3_umin;
  c3_c_y = NULL;
  sf_mex_assign(&c3_c_y, sf_mex_create("y", &c3_d_u, 0, 0U, 0U, 0U, 0), false);
  c3_e_u = c3_umax;
  c3_d_y = NULL;
  sf_mex_assign(&c3_d_y, sf_mex_create("y", &c3_e_u, 0, 0U, 0U, 0U, 0), false);
  for (c3_i75 = 0; c3_i75 < 2; c3_i75++) {
    c3_f_u[c3_i75] = c3_ymin[c3_i75];
  }

  c3_e_y = NULL;
  sf_mex_assign(&c3_e_y, sf_mex_create("y", c3_f_u, 0, 0U, 1U, 0U, 1, 2), false);
  for (c3_i76 = 0; c3_i76 < 2; c3_i76++) {
    c3_g_u[c3_i76] = c3_ymax[c3_i76];
  }

  c3_f_y = NULL;
  sf_mex_assign(&c3_f_y, sf_mex_create("y", c3_g_u, 0, 0U, 1U, 0U, 1, 2), false);
  c3_h_u = c3_switch_in;
  c3_g_y = NULL;
  sf_mex_assign(&c3_g_y, sf_mex_create("y", &c3_h_u, 0, 0U, 0U, 0U, 0), false);
  for (c3_i77 = 0; c3_i77 < 5; c3_i77++) {
    c3_i_u[c3_i77] = c3_x[c3_i77];
  }

  c3_h_y = NULL;
  sf_mex_assign(&c3_h_y, sf_mex_create("y", c3_i_u, 0, 0U, 1U, 0U, 1, 5), false);
  c3_j_u = c3_old_u;
  c3_i_y = NULL;
  sf_mex_assign(&c3_i_y, sf_mex_create("y", &c3_j_u, 0, 0U, 0U, 0U, 0), false);
  for (c3_i78 = 0; c3_i78 < 50; c3_i78++) {
    c3_k_u[c3_i78] = c3_iA[c3_i78];
  }

  c3_j_y = NULL;
  sf_mex_assign(&c3_j_y, sf_mex_create("y", c3_k_u, 11, 0U, 1U, 0U, 1, 50),
                false);
  c3_l_u = c3_b_isQP;
  c3_k_y = NULL;
  sf_mex_assign(&c3_k_y, sf_mex_create("y", &c3_l_u, 11, 0U, 0U, 0U, 0), false);
  c3_m_u = c3_b_nu;
  c3_l_y = NULL;
  sf_mex_assign(&c3_l_y, sf_mex_create("y", &c3_m_u, 0, 0U, 0U, 0U, 0), false);
  c3_n_u = c3_b_ny;
  c3_m_y = NULL;
  sf_mex_assign(&c3_m_y, sf_mex_create("y", &c3_n_u, 0, 0U, 0U, 0U, 0), false);
  c3_o_u = c3_b_degrees;
  c3_n_y = NULL;
  sf_mex_assign(&c3_n_y, sf_mex_create("y", &c3_o_u, 0, 0U, 0U, 0U, 0), false);
  for (c3_i79 = 0; c3_i79 < 16; c3_i79++) {
    c3_p_u[c3_i79] = c3_d_Hinv[c3_i79];
  }

  c3_o_y = NULL;
  sf_mex_assign(&c3_o_y, sf_mex_create("y", c3_p_u, 0, 0U, 1U, 0U, 2, 4, 4),
                false);
  for (c3_i80 = 0; c3_i80 < 15; c3_i80++) {
    c3_q_u[c3_i80] = c3_d_Kx[c3_i80];
  }

  c3_p_y = NULL;
  sf_mex_assign(&c3_p_y, sf_mex_create("y", c3_q_u, 0, 0U, 1U, 0U, 2, 5, 3),
                false);
  for (c3_i81 = 0; c3_i81 < 3; c3_i81++) {
    c3_r_u[c3_i81] = c3_d_Ku1[c3_i81];
  }

  c3_q_y = NULL;
  sf_mex_assign(&c3_q_y, sf_mex_create("y", c3_r_u, 0, 0U, 1U, 0U, 2, 1, 3),
                false);
  for (c3_i82 = 0; c3_i82 < 30; c3_i82++) {
    c3_s_u[c3_i82] = 0.0;
  }

  c3_r_y = NULL;
  sf_mex_assign(&c3_r_y, sf_mex_create("y", c3_s_u, 0, 0U, 1U, 0U, 2, 10, 3),
                false);
  for (c3_i83 = 0; c3_i83 < 60; c3_i83++) {
    c3_t_u[c3_i83] = c3_d_Kr[c3_i83];
  }

  c3_s_y = NULL;
  sf_mex_assign(&c3_s_y, sf_mex_create("y", c3_t_u, 0, 0U, 1U, 0U, 2, 20, 3),
                false);
  for (c3_i84 = 0; c3_i84 < 33; c3_i84++) {
    c3_u_u[c3_i84] = 0.0;
  }

  c3_t_y = NULL;
  sf_mex_assign(&c3_t_y, sf_mex_create("y", c3_u_u, 0, 0U, 1U, 0U, 2, 11, 3),
                false);
  for (c3_i85 = 0; c3_i85 < 46; c3_i85++) {
    c3_v_u[c3_i85] = c3_d_Mlim[c3_i85];
  }

  c3_u_y = NULL;
  sf_mex_assign(&c3_u_y, sf_mex_create("y", c3_v_u, 0, 0U, 1U, 0U, 1, 46), false);
  for (c3_i86 = 0; c3_i86 < 230; c3_i86++) {
    c3_w_u[c3_i86] = c3_d_Mx[c3_i86];
  }

  c3_v_y = NULL;
  sf_mex_assign(&c3_v_y, sf_mex_create("y", c3_w_u, 0, 0U, 1U, 0U, 2, 46, 5),
                false);
  for (c3_i87 = 0; c3_i87 < 46; c3_i87++) {
    c3_x_u[c3_i87] = c3_d_Mu1[c3_i87];
  }

  c3_w_y = NULL;
  sf_mex_assign(&c3_w_y, sf_mex_create("y", c3_x_u, 0, 0U, 1U, 0U, 1, 46), false);
  for (c3_i88 = 0; c3_i88 < 506; c3_i88++) {
    c3_y_u[c3_i88] = -0.0;
  }

  c3_x_y = NULL;
  sf_mex_assign(&c3_x_y, sf_mex_create("y", c3_y_u, 0, 0U, 1U, 0U, 2, 46, 11),
                false);
  for (c3_i89 = 0; c3_i89 < 4; c3_i89++) {
    c3_ab_u[c3_i89] = 0.0;
  }

  c3_y_y = NULL;
  sf_mex_assign(&c3_y_y, sf_mex_create("y", c3_ab_u, 0, 0U, 1U, 0U, 1, 4), false);
  for (c3_i90 = 0; c3_i90 < 10; c3_i90++) {
    c3_bb_u[c3_i90] = 0.0;
  }

  c3_ab_y = NULL;
  sf_mex_assign(&c3_ab_y, sf_mex_create("y", c3_bb_u, 0, 0U, 1U, 0U, 1, 10),
                false);
  c3_cb_u = c3_b_p;
  c3_bb_y = NULL;
  sf_mex_assign(&c3_bb_y, sf_mex_create("y", &c3_cb_u, 0, 0U, 0U, 0U, 0), false);
  c3_db_u = c3_b_uoff;
  c3_cb_y = NULL;
  sf_mex_assign(&c3_cb_y, sf_mex_create("y", &c3_db_u, 0, 0U, 0U, 0U, 0), false);
  for (c3_i91 = 0; c3_i91 < 2; c3_i91++) {
    c3_eb_u[c3_i91] = 0.0;
  }

  c3_db_y = NULL;
  sf_mex_assign(&c3_db_y, sf_mex_create("y", c3_eb_u, 0, 0U, 1U, 0U, 1, 2),
                false);
  c3_fb_u = c3_b_maxiter;
  c3_eb_y = NULL;
  sf_mex_assign(&c3_eb_y, sf_mex_create("y", &c3_fb_u, 0, 0U, 0U, 0U, 0), false);
  c3_gb_u = c3_b_nxQP;
  c3_fb_y = NULL;
  sf_mex_assign(&c3_fb_y, sf_mex_create("y", &c3_gb_u, 0, 0U, 0U, 0U, 0), false);
  c3_hb_u = c3_b_openloopflag;
  c3_gb_y = NULL;
  sf_mex_assign(&c3_gb_y, sf_mex_create("y", &c3_hb_u, 11, 0U, 0U, 0U, 0), false);
  c3_ib_u = c3_b_lims_inport;
  c3_hb_y = NULL;
  sf_mex_assign(&c3_hb_y, sf_mex_create("y", &c3_ib_u, 0, 0U, 0U, 0U, 0), false);
  c3_jb_u = c3_b_no_umin;
  c3_ib_y = NULL;
  sf_mex_assign(&c3_ib_y, sf_mex_create("y", &c3_jb_u, 0, 0U, 0U, 0U, 0), false);
  c3_kb_u = c3_b_no_umax;
  c3_jb_y = NULL;
  sf_mex_assign(&c3_jb_y, sf_mex_create("y", &c3_kb_u, 0, 0U, 0U, 0U, 0), false);
  c3_lb_u = c3_b_no_ymin;
  c3_kb_y = NULL;
  sf_mex_assign(&c3_kb_y, sf_mex_create("y", &c3_lb_u, 0, 0U, 0U, 0U, 0), false);
  c3_mb_u = c3_b_no_ymax;
  c3_lb_y = NULL;
  sf_mex_assign(&c3_lb_y, sf_mex_create("y", &c3_mb_u, 0, 0U, 0U, 0U, 0), false);
  c3_nb_u = c3_b_switch_inport;
  c3_mb_y = NULL;
  sf_mex_assign(&c3_mb_y, sf_mex_create("y", &c3_nb_u, 0, 0U, 0U, 0U, 0), false);
  c3_ob_u = c3_b_no_switch;
  c3_nb_y = NULL;
  sf_mex_assign(&c3_nb_y, sf_mex_create("y", &c3_ob_u, 0, 0U, 0U, 0U, 0), false);
  c3_pb_u = c3_b_enable_value;
  c3_ob_y = NULL;
  sf_mex_assign(&c3_ob_y, sf_mex_create("y", &c3_pb_u, 0, 0U, 0U, 0U, 0), false);
  c3_qb_u = c3_b_return_cost;
  c3_pb_y = NULL;
  sf_mex_assign(&c3_pb_y, sf_mex_create("y", &c3_qb_u, 0, 0U, 0U, 0U, 0), false);
  for (c3_i92 = 0; c3_i92 < 16; c3_i92++) {
    c3_rb_u[c3_i92] = c3_d_H[c3_i92];
  }

  c3_qb_y = NULL;
  sf_mex_assign(&c3_qb_y, sf_mex_create("y", c3_rb_u, 0, 0U, 1U, 0U, 2, 4, 4),
                false);
  c3_sb_u = c3_b_return_sequence;
  c3_rb_y = NULL;
  sf_mex_assign(&c3_rb_y, sf_mex_create("y", &c3_sb_u, 0, 0U, 0U, 0U, 0), false);
  for (c3_i93 = 0; c3_i93 < 10; c3_i93++) {
    c3_tb_u[c3_i93] = c3_d_blocking_moves[c3_i93];
  }

  c3_sb_y = NULL;
  sf_mex_assign(&c3_sb_y, sf_mex_create("y", c3_tb_u, 0, 0U, 1U, 0U, 2, 1, 10),
                false);
  for (c3_i94 = 0; c3_i94 < 16; c3_i94++) {
    c3_ub_u[c3_i94] = c3_d_Linv[c3_i94];
  }

  c3_tb_y = NULL;
  sf_mex_assign(&c3_tb_y, sf_mex_create("y", c3_ub_u, 0, 0U, 1U, 0U, 2, 4, 4),
                false);
  for (c3_i95 = 0; c3_i95 < 184; c3_i95++) {
    c3_vb_u[c3_i95] = c3_d_Ac[c3_i95];
  }

  c3_ub_y = NULL;
  sf_mex_assign(&c3_ub_y, sf_mex_create("y", c3_vb_u, 0, 0U, 1U, 0U, 2, 46, 4),
                false);
  for (c3_i96 = 0; c3_i96 < 2; c3_i96++) {
    c3_wb_u[c3_i96] = c3_ywt[c3_i96];
  }

  c3_vb_y = NULL;
  sf_mex_assign(&c3_vb_y, sf_mex_create("y", c3_wb_u, 0, 0U, 1U, 0U, 1, 2),
                false);
  c3_xb_u = c3_duwt;
  c3_wb_y = NULL;
  sf_mex_assign(&c3_wb_y, sf_mex_create("y", &c3_xb_u, 0, 0U, 0U, 0U, 0), false);
  c3_yb_u = c3_rhoeps;
  c3_xb_y = NULL;
  sf_mex_assign(&c3_xb_y, sf_mex_create("y", &c3_yb_u, 0, 0U, 0U, 0U, 0), false);
  c3_ac_u = c3_b_no_ywt;
  c3_yb_y = NULL;
  sf_mex_assign(&c3_yb_y, sf_mex_create("y", &c3_ac_u, 0, 0U, 0U, 0U, 0), false);
  c3_bc_u = c3_b_no_duwt;
  c3_ac_y = NULL;
  sf_mex_assign(&c3_ac_y, sf_mex_create("y", &c3_bc_u, 0, 0U, 0U, 0U, 0), false);
  c3_cc_u = c3_b_no_rhoeps;
  c3_bc_y = NULL;
  sf_mex_assign(&c3_bc_y, sf_mex_create("y", &c3_cc_u, 0, 0U, 0U, 0U, 0), false);
  c3_dc_u = c3_b_Wy;
  c3_cc_y = NULL;
  sf_mex_assign(&c3_cc_y, sf_mex_create("y", &c3_dc_u, 0, 0U, 0U, 0U, 0), false);
  c3_ec_u = c3_b_Wdu;
  c3_dc_y = NULL;
  sf_mex_assign(&c3_dc_y, sf_mex_create("y", &c3_ec_u, 0, 0U, 0U, 0U, 0), false);
  c3_fc_u = c3_b_Jm;
  c3_ec_y = NULL;
  sf_mex_assign(&c3_ec_y, sf_mex_create("y", &c3_fc_u, 0, 0U, 0U, 0U, 0), false);
  c3_gc_u = c3_b_SuJm;
  c3_fc_y = NULL;
  sf_mex_assign(&c3_fc_y, sf_mex_create("y", &c3_gc_u, 0, 0U, 0U, 0U, 0), false);
  c3_hc_u = c3_b_I2JmWuI2Jm;
  c3_gc_y = NULL;
  sf_mex_assign(&c3_gc_y, sf_mex_create("y", &c3_hc_u, 0, 0U, 0U, 0U, 0), false);
  c3_ic_u = c3_b_Su1;
  c3_hc_y = NULL;
  sf_mex_assign(&c3_hc_y, sf_mex_create("y", &c3_ic_u, 0, 0U, 0U, 0U, 0), false);
  c3_jc_u = c3_b_I1WuI2Jm;
  c3_ic_y = NULL;
  sf_mex_assign(&c3_ic_y, sf_mex_create("y", &c3_jc_u, 0, 0U, 0U, 0U, 0), false);
  c3_kc_u = c3_b_Sx;
  c3_jc_y = NULL;
  sf_mex_assign(&c3_jc_y, sf_mex_create("y", &c3_kc_u, 0, 0U, 0U, 0U, 0), false);
  c3_lc_u = c3_b_Hv;
  c3_kc_y = NULL;
  sf_mex_assign(&c3_kc_y, sf_mex_create("y", &c3_lc_u, 0, 0U, 0U, 0U, 0), false);
  c3_mc_u = c3_b_Wu;
  c3_lc_y = NULL;
  sf_mex_assign(&c3_lc_y, sf_mex_create("y", &c3_mc_u, 0, 0U, 0U, 0U, 0), false);
  c3_nc_u = c3_b_I1;
  c3_mc_y = NULL;
  sf_mex_assign(&c3_mc_y, sf_mex_create("y", &c3_nc_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_call_debug(sfGlobalDebugInstanceStruct, "mpcblock_optimizer_double_mex",
                    5U, 63U, 14, c3_y, 14, c3_b_y, 14, c3_c_y, 14, c3_d_y, 14,
                    c3_e_y, 14, c3_f_y, 14, c3_g_y, 14, c3_h_y, 14, c3_i_y, 14,
                    c3_j_y, 14, c3_k_y, 14, c3_l_y, 14, c3_m_y, 14, c3_n_y, 14,
                    c3_o_y, 14, c3_p_y, 14, c3_q_y, 14, c3_r_y, 14, c3_s_y, 14,
                    c3_t_y, 14, c3_u_y, 14, c3_v_y, 14, c3_w_y, 14, c3_x_y, 14,
                    c3_y_y, 14, c3_ab_y, 14, c3_bb_y, 14, c3_cb_y, 14, c3_db_y,
                    14, c3_eb_y, 14, c3_fb_y, 14, c3_gb_y, 14, c3_hb_y, 14,
                    c3_ib_y, 14, c3_jb_y, 14, c3_kb_y, 14, c3_lb_y, 14, c3_mb_y,
                    14, c3_nb_y, 14, c3_ob_y, 14, c3_pb_y, 14, c3_qb_y, 14,
                    c3_rb_y, 14, c3_sb_y, 14, c3_tb_y, 14, c3_ub_y, 14, c3_vb_y,
                    14, c3_wb_y, 14, c3_xb_y, 14, c3_yb_y, 14, c3_ac_y, 14,
                    c3_bc_y, 14, c3_cc_y, 14, c3_dc_y, 14, c3_ec_y, 14, c3_fc_y,
                    14, c3_gc_y, 14, c3_hc_y, 14, c3_ic_y, 14, c3_jc_y, 14,
                    c3_kc_y, 14, c3_lc_y, 14, c3_mc_y, &c3_oc_u, &c3_b_cost,
                    &c3_b_useq, &c3_b_status, &c3_b_iAout);
  c3_u = c3_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_oc_u), "u");
  c3_cost = c3_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_cost), "cost");
  c3_c_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_useq), "useq", c3_dv18);
  for (c3_i97 = 0; c3_i97 < 10; c3_i97++) {
    c3_useq[c3_i97] = c3_dv18[c3_i97];
  }

  c3_status = c3_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_status),
    "status");
  c3_e_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_iAout), "iAout", c3_bv1);
  for (c3_i98 = 0; c3_i98 < 50; c3_i98++) {
    c3_iAout[c3_i98] = c3_bv1[c3_i98];
  }

  _SFD_EML_CALL(0U, chartInstance->c3_sfEvent, -30);
  _SFD_SYMBOL_SCOPE_POP();
  sf_mex_destroy(&c3_oc_u);
  sf_mex_destroy(&c3_b_cost);
  sf_mex_destroy(&c3_b_useq);
  sf_mex_destroy(&c3_b_status);
  sf_mex_destroy(&c3_b_iAout);
  *c3_pc_u = c3_u;
  *c3_c_cost = c3_cost;
  for (c3_i99 = 0; c3_i99 < 10; c3_i99++) {
    (*c3_c_useq)[c3_i99] = c3_useq[c3_i99];
  }

  *c3_c_status = c3_status;
  for (c3_i100 = 0; c3_i100 < 50; c3_i100++) {
    (*c3_c_iAout)[c3_i100] = c3_iAout[c3_i100];
  }

  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG, 0U, chartInstance->c3_sfEvent);
}

static void initSimStructsc3_mpclib(SFc3_mpclibInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_script_number_translation(uint32_T c3_machineNumber, uint32_T
  c3_chartNumber, uint32_T c3_instanceNumber)
{
  (void)c3_machineNumber;
  (void)c3_chartNumber;
  (void)c3_instanceNumber;
}

static const mxArray *c3_sf_marshallOut(void *chartInstanceVoid, void *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i101;
  boolean_T c3_b_inData[50];
  int32_T c3_i102;
  boolean_T c3_u[50];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i101 = 0; c3_i101 < 50; c3_i101++) {
    c3_b_inData[c3_i101] = (*(boolean_T (*)[50])c3_inData)[c3_i101];
  }

  for (c3_i102 = 0; c3_i102 < 50; c3_i102++) {
    c3_u[c3_i102] = c3_b_inData[c3_i102];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 11, 0U, 1U, 0U, 1, 50), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static void c3_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_iAout;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  boolean_T c3_y[50];
  int32_T c3_i103;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_iAout = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_iAout), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_iAout);
  for (c3_i103 = 0; c3_i103 < 50; c3_i103++) {
    (*(boolean_T (*)[50])c3_outData)[c3_i103] = c3_y[c3_i103];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_b_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  real_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(real_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 0, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static void c3_b_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_u;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_u = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_u), &c3_thisId);
  sf_mex_destroy(&c3_u);
  *(real_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_c_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i104;
  real_T c3_b_inData[10];
  int32_T c3_i105;
  real_T c3_u[10];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i104 = 0; c3_i104 < 10; c3_i104++) {
    c3_b_inData[c3_i104] = (*(real_T (*)[10])c3_inData)[c3_i104];
  }

  for (c3_i105 = 0; c3_i105 < 10; c3_i105++) {
    c3_u[c3_i105] = c3_b_inData[c3_i105];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 1, 10), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static void c3_c_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_useq;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[10];
  int32_T c3_i106;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_useq = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_useq), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_useq);
  for (c3_i106 = 0; c3_i106 < 10; c3_i106++) {
    (*(real_T (*)[10])c3_outData)[c3_i106] = c3_y[c3_i106];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static const mxArray *c3_d_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i107;
  real_T c3_b_inData[2];
  int32_T c3_i108;
  real_T c3_u[2];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i107 = 0; c3_i107 < 2; c3_i107++) {
    c3_b_inData[c3_i107] = (*(real_T (*)[2])c3_inData)[c3_i107];
  }

  for (c3_i108 = 0; c3_i108 < 2; c3_i108++) {
    c3_u[c3_i108] = c3_b_inData[c3_i108];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 1, 2), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_e_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i109;
  real_T c3_b_inData[5];
  int32_T c3_i110;
  real_T c3_u[5];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i109 = 0; c3_i109 < 5; c3_i109++) {
    c3_b_inData[c3_i109] = (*(real_T (*)[5])c3_inData)[c3_i109];
  }

  for (c3_i110 = 0; c3_i110 < 5; c3_i110++) {
    c3_u[c3_i110] = c3_b_inData[c3_i110];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 1, 5), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_f_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i111;
  real_T c3_b_inData[11];
  int32_T c3_i112;
  real_T c3_u[11];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i111 = 0; c3_i111 < 11; c3_i111++) {
    c3_b_inData[c3_i111] = (*(real_T (*)[11])c3_inData)[c3_i111];
  }

  for (c3_i112 = 0; c3_i112 < 11; c3_i112++) {
    c3_u[c3_i112] = c3_b_inData[c3_i112];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 1, 11), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_g_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i113;
  real_T c3_b_inData[20];
  int32_T c3_i114;
  real_T c3_u[20];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i113 = 0; c3_i113 < 20; c3_i113++) {
    c3_b_inData[c3_i113] = (*(real_T (*)[20])c3_inData)[c3_i113];
  }

  for (c3_i114 = 0; c3_i114 < 20; c3_i114++) {
    c3_u[c3_i114] = c3_b_inData[c3_i114];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 1, 20), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_h_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i115;
  int32_T c3_i116;
  int32_T c3_i117;
  real_T c3_b_inData[184];
  int32_T c3_i118;
  int32_T c3_i119;
  int32_T c3_i120;
  real_T c3_u[184];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_i115 = 0;
  for (c3_i116 = 0; c3_i116 < 4; c3_i116++) {
    for (c3_i117 = 0; c3_i117 < 46; c3_i117++) {
      c3_b_inData[c3_i117 + c3_i115] = (*(real_T (*)[184])c3_inData)[c3_i117 +
        c3_i115];
    }

    c3_i115 += 46;
  }

  c3_i118 = 0;
  for (c3_i119 = 0; c3_i119 < 4; c3_i119++) {
    for (c3_i120 = 0; c3_i120 < 46; c3_i120++) {
      c3_u[c3_i120 + c3_i118] = c3_b_inData[c3_i120 + c3_i118];
    }

    c3_i118 += 46;
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 2, 46, 4), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_i_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i121;
  int32_T c3_i122;
  int32_T c3_i123;
  real_T c3_b_inData[16];
  int32_T c3_i124;
  int32_T c3_i125;
  int32_T c3_i126;
  real_T c3_u[16];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_i121 = 0;
  for (c3_i122 = 0; c3_i122 < 4; c3_i122++) {
    for (c3_i123 = 0; c3_i123 < 4; c3_i123++) {
      c3_b_inData[c3_i123 + c3_i121] = (*(real_T (*)[16])c3_inData)[c3_i123 +
        c3_i121];
    }

    c3_i121 += 4;
  }

  c3_i124 = 0;
  for (c3_i125 = 0; c3_i125 < 4; c3_i125++) {
    for (c3_i126 = 0; c3_i126 < 4; c3_i126++) {
      c3_u[c3_i126 + c3_i124] = c3_b_inData[c3_i126 + c3_i124];
    }

    c3_i124 += 4;
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 2, 4, 4), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_j_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i127;
  real_T c3_b_inData[10];
  int32_T c3_i128;
  real_T c3_u[10];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i127 = 0; c3_i127 < 10; c3_i127++) {
    c3_b_inData[c3_i127] = (*(real_T (*)[10])c3_inData)[c3_i127];
  }

  for (c3_i128 = 0; c3_i128 < 10; c3_i128++) {
    c3_u[c3_i128] = c3_b_inData[c3_i128];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 2, 1, 10), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_k_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  boolean_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(boolean_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 11, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_l_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i129;
  real_T c3_b_inData[4];
  int32_T c3_i130;
  real_T c3_u[4];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i129 = 0; c3_i129 < 4; c3_i129++) {
    c3_b_inData[c3_i129] = (*(real_T (*)[4])c3_inData)[c3_i129];
  }

  for (c3_i130 = 0; c3_i130 < 4; c3_i130++) {
    c3_u[c3_i130] = c3_b_inData[c3_i130];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 1, 4), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_m_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i131;
  int32_T c3_i132;
  int32_T c3_i133;
  real_T c3_b_inData[506];
  int32_T c3_i134;
  int32_T c3_i135;
  int32_T c3_i136;
  real_T c3_u[506];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_i131 = 0;
  for (c3_i132 = 0; c3_i132 < 11; c3_i132++) {
    for (c3_i133 = 0; c3_i133 < 46; c3_i133++) {
      c3_b_inData[c3_i133 + c3_i131] = (*(real_T (*)[506])c3_inData)[c3_i133 +
        c3_i131];
    }

    c3_i131 += 46;
  }

  c3_i134 = 0;
  for (c3_i135 = 0; c3_i135 < 11; c3_i135++) {
    for (c3_i136 = 0; c3_i136 < 46; c3_i136++) {
      c3_u[c3_i136 + c3_i134] = c3_b_inData[c3_i136 + c3_i134];
    }

    c3_i134 += 46;
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 2, 46, 11), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_n_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i137;
  real_T c3_b_inData[46];
  int32_T c3_i138;
  real_T c3_u[46];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i137 = 0; c3_i137 < 46; c3_i137++) {
    c3_b_inData[c3_i137] = (*(real_T (*)[46])c3_inData)[c3_i137];
  }

  for (c3_i138 = 0; c3_i138 < 46; c3_i138++) {
    c3_u[c3_i138] = c3_b_inData[c3_i138];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 1, 46), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_o_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i139;
  int32_T c3_i140;
  int32_T c3_i141;
  real_T c3_b_inData[230];
  int32_T c3_i142;
  int32_T c3_i143;
  int32_T c3_i144;
  real_T c3_u[230];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_i139 = 0;
  for (c3_i140 = 0; c3_i140 < 5; c3_i140++) {
    for (c3_i141 = 0; c3_i141 < 46; c3_i141++) {
      c3_b_inData[c3_i141 + c3_i139] = (*(real_T (*)[230])c3_inData)[c3_i141 +
        c3_i139];
    }

    c3_i139 += 46;
  }

  c3_i142 = 0;
  for (c3_i143 = 0; c3_i143 < 5; c3_i143++) {
    for (c3_i144 = 0; c3_i144 < 46; c3_i144++) {
      c3_u[c3_i144 + c3_i142] = c3_b_inData[c3_i144 + c3_i142];
    }

    c3_i142 += 46;
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 2, 46, 5), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_p_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i145;
  int32_T c3_i146;
  int32_T c3_i147;
  real_T c3_b_inData[33];
  int32_T c3_i148;
  int32_T c3_i149;
  int32_T c3_i150;
  real_T c3_u[33];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_i145 = 0;
  for (c3_i146 = 0; c3_i146 < 3; c3_i146++) {
    for (c3_i147 = 0; c3_i147 < 11; c3_i147++) {
      c3_b_inData[c3_i147 + c3_i145] = (*(real_T (*)[33])c3_inData)[c3_i147 +
        c3_i145];
    }

    c3_i145 += 11;
  }

  c3_i148 = 0;
  for (c3_i149 = 0; c3_i149 < 3; c3_i149++) {
    for (c3_i150 = 0; c3_i150 < 11; c3_i150++) {
      c3_u[c3_i150 + c3_i148] = c3_b_inData[c3_i150 + c3_i148];
    }

    c3_i148 += 11;
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 2, 11, 3), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_q_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i151;
  int32_T c3_i152;
  int32_T c3_i153;
  real_T c3_b_inData[60];
  int32_T c3_i154;
  int32_T c3_i155;
  int32_T c3_i156;
  real_T c3_u[60];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_i151 = 0;
  for (c3_i152 = 0; c3_i152 < 3; c3_i152++) {
    for (c3_i153 = 0; c3_i153 < 20; c3_i153++) {
      c3_b_inData[c3_i153 + c3_i151] = (*(real_T (*)[60])c3_inData)[c3_i153 +
        c3_i151];
    }

    c3_i151 += 20;
  }

  c3_i154 = 0;
  for (c3_i155 = 0; c3_i155 < 3; c3_i155++) {
    for (c3_i156 = 0; c3_i156 < 20; c3_i156++) {
      c3_u[c3_i156 + c3_i154] = c3_b_inData[c3_i156 + c3_i154];
    }

    c3_i154 += 20;
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 2, 20, 3), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_r_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i157;
  int32_T c3_i158;
  int32_T c3_i159;
  real_T c3_b_inData[30];
  int32_T c3_i160;
  int32_T c3_i161;
  int32_T c3_i162;
  real_T c3_u[30];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_i157 = 0;
  for (c3_i158 = 0; c3_i158 < 3; c3_i158++) {
    for (c3_i159 = 0; c3_i159 < 10; c3_i159++) {
      c3_b_inData[c3_i159 + c3_i157] = (*(real_T (*)[30])c3_inData)[c3_i159 +
        c3_i157];
    }

    c3_i157 += 10;
  }

  c3_i160 = 0;
  for (c3_i161 = 0; c3_i161 < 3; c3_i161++) {
    for (c3_i162 = 0; c3_i162 < 10; c3_i162++) {
      c3_u[c3_i162 + c3_i160] = c3_b_inData[c3_i162 + c3_i160];
    }

    c3_i160 += 10;
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 2, 10, 3), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_s_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i163;
  real_T c3_b_inData[3];
  int32_T c3_i164;
  real_T c3_u[3];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  for (c3_i163 = 0; c3_i163 < 3; c3_i163++) {
    c3_b_inData[c3_i163] = (*(real_T (*)[3])c3_inData)[c3_i163];
  }

  for (c3_i164 = 0; c3_i164 < 3; c3_i164++) {
    c3_u[c3_i164] = c3_b_inData[c3_i164];
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 2, 1, 3), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static const mxArray *c3_t_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_i165;
  int32_T c3_i166;
  int32_T c3_i167;
  real_T c3_b_inData[15];
  int32_T c3_i168;
  int32_T c3_i169;
  int32_T c3_i170;
  real_T c3_u[15];
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_i165 = 0;
  for (c3_i166 = 0; c3_i166 < 3; c3_i166++) {
    for (c3_i167 = 0; c3_i167 < 5; c3_i167++) {
      c3_b_inData[c3_i167 + c3_i165] = (*(real_T (*)[15])c3_inData)[c3_i167 +
        c3_i165];
    }

    c3_i165 += 5;
  }

  c3_i168 = 0;
  for (c3_i169 = 0; c3_i169 < 3; c3_i169++) {
    for (c3_i170 = 0; c3_i170 < 5; c3_i170++) {
      c3_u[c3_i170 + c3_i168] = c3_b_inData[c3_i170 + c3_i168];
    }

    c3_i168 += 5;
  }

  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", c3_u, 0, 0U, 1U, 0U, 2, 5, 3), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

const mxArray *sf_c3_mpclib_get_eml_resolved_functions_info(void)
{
  const mxArray *c3_nameCaptureInfo = NULL;
  c3_nameCaptureInfo = NULL;
  sf_mex_assign(&c3_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c3_nameCaptureInfo;
}

static real_T c3_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_u, const char_T *c3_identifier)
{
  real_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_u), &c3_thisId);
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static real_T c3_b_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  real_T c3_y;
  real_T c3_d33;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_d33, 1, 0, 0U, 0, 0U, 0);
  c3_y = c3_d33;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_c_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_useq, const char_T *c3_identifier, real_T c3_y[10])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_useq), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_useq);
}

static void c3_d_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[10])
{
  real_T c3_dv19[10];
  int32_T c3_i171;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv19, 1, 0, 0U, 1, 0U, 1, 10);
  for (c3_i171 = 0; c3_i171 < 10; c3_i171++) {
    c3_y[c3_i171] = c3_dv19[c3_i171];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_e_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_iAout, const char_T *c3_identifier, boolean_T c3_y[50])
{
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_f_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_iAout), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_iAout);
}

static void c3_f_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, boolean_T c3_y[50])
{
  boolean_T c3_bv2[50];
  int32_T c3_i172;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_bv2, 1, 11, 0U, 1, 0U, 1, 50);
  for (c3_i172 = 0; c3_i172 < 50; c3_i172++) {
    c3_y[c3_i172] = c3_bv2[c3_i172];
  }

  sf_mex_destroy(&c3_u);
}

static const mxArray *c3_u_sf_marshallOut(void *chartInstanceVoid, void
  *c3_inData)
{
  const mxArray *c3_mxArrayOutData = NULL;
  int32_T c3_u;
  const mxArray *c3_y = NULL;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_mxArrayOutData = NULL;
  c3_u = *(int32_T *)c3_inData;
  c3_y = NULL;
  sf_mex_assign(&c3_y, sf_mex_create("y", &c3_u, 6, 0U, 0U, 0U, 0), false);
  sf_mex_assign(&c3_mxArrayOutData, c3_y, false);
  return c3_mxArrayOutData;
}

static int32_T c3_g_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  int32_T c3_y;
  int32_T c3_i173;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_i173, 1, 6, 0U, 0, 0U, 0);
  c3_y = c3_i173;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_d_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_b_sfEvent;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  int32_T c3_y;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_b_sfEvent = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_g_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_b_sfEvent),
    &c3_thisId);
  sf_mex_destroy(&c3_b_sfEvent);
  *(int32_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static boolean_T c3_h_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  boolean_T c3_y;
  boolean_T c3_b0;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_b0, 1, 11, 0U, 0, 0U, 0);
  c3_y = c3_b0;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void c3_e_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_c_isQP;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  boolean_T c3_y;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_c_isQP = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_h_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_c_isQP), &c3_thisId);
  sf_mex_destroy(&c3_c_isQP);
  *(boolean_T *)c3_outData = c3_y;
  sf_mex_destroy(&c3_mxArrayInData);
}

static void c3_i_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[16])
{
  real_T c3_dv20[16];
  int32_T c3_i174;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv20, 1, 0, 0U, 1, 0U, 2, 4, 4);
  for (c3_i174 = 0; c3_i174 < 16; c3_i174++) {
    c3_y[c3_i174] = c3_dv20[c3_i174];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_f_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_c_Hinv;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[16];
  int32_T c3_i175;
  int32_T c3_i176;
  int32_T c3_i177;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_c_Hinv = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_i_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_c_Hinv), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_c_Hinv);
  c3_i175 = 0;
  for (c3_i176 = 0; c3_i176 < 4; c3_i176++) {
    for (c3_i177 = 0; c3_i177 < 4; c3_i177++) {
      (*(real_T (*)[16])c3_outData)[c3_i177 + c3_i175] = c3_y[c3_i177 + c3_i175];
    }

    c3_i175 += 4;
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static void c3_j_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[15])
{
  real_T c3_dv21[15];
  int32_T c3_i178;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv21, 1, 0, 0U, 1, 0U, 2, 5, 3);
  for (c3_i178 = 0; c3_i178 < 15; c3_i178++) {
    c3_y[c3_i178] = c3_dv21[c3_i178];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_g_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_c_Kx;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[15];
  int32_T c3_i179;
  int32_T c3_i180;
  int32_T c3_i181;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_c_Kx = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_j_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_c_Kx), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_c_Kx);
  c3_i179 = 0;
  for (c3_i180 = 0; c3_i180 < 3; c3_i180++) {
    for (c3_i181 = 0; c3_i181 < 5; c3_i181++) {
      (*(real_T (*)[15])c3_outData)[c3_i181 + c3_i179] = c3_y[c3_i181 + c3_i179];
    }

    c3_i179 += 5;
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static void c3_k_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[3])
{
  real_T c3_dv22[3];
  int32_T c3_i182;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv22, 1, 0, 0U, 1, 0U, 2, 1, 3);
  for (c3_i182 = 0; c3_i182 < 3; c3_i182++) {
    c3_y[c3_i182] = c3_dv22[c3_i182];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_h_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_c_Ku1;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[3];
  int32_T c3_i183;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_c_Ku1 = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_k_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_c_Ku1), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_c_Ku1);
  for (c3_i183 = 0; c3_i183 < 3; c3_i183++) {
    (*(real_T (*)[3])c3_outData)[c3_i183] = c3_y[c3_i183];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static void c3_l_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[30])
{
  real_T c3_dv23[30];
  int32_T c3_i184;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv23, 1, 0, 0U, 1, 0U, 2, 10,
                3);
  for (c3_i184 = 0; c3_i184 < 30; c3_i184++) {
    c3_y[c3_i184] = c3_dv23[c3_i184];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_i_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_c_Kut;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[30];
  int32_T c3_i185;
  int32_T c3_i186;
  int32_T c3_i187;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_c_Kut = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_l_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_c_Kut), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_c_Kut);
  c3_i185 = 0;
  for (c3_i186 = 0; c3_i186 < 3; c3_i186++) {
    for (c3_i187 = 0; c3_i187 < 10; c3_i187++) {
      (*(real_T (*)[30])c3_outData)[c3_i187 + c3_i185] = c3_y[c3_i187 + c3_i185];
    }

    c3_i185 += 10;
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static void c3_m_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[60])
{
  real_T c3_dv24[60];
  int32_T c3_i188;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv24, 1, 0, 0U, 1, 0U, 2, 20,
                3);
  for (c3_i188 = 0; c3_i188 < 60; c3_i188++) {
    c3_y[c3_i188] = c3_dv24[c3_i188];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_j_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_c_Kr;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[60];
  int32_T c3_i189;
  int32_T c3_i190;
  int32_T c3_i191;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_c_Kr = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_m_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_c_Kr), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_c_Kr);
  c3_i189 = 0;
  for (c3_i190 = 0; c3_i190 < 3; c3_i190++) {
    for (c3_i191 = 0; c3_i191 < 20; c3_i191++) {
      (*(real_T (*)[60])c3_outData)[c3_i191 + c3_i189] = c3_y[c3_i191 + c3_i189];
    }

    c3_i189 += 20;
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static void c3_n_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[33])
{
  real_T c3_dv25[33];
  int32_T c3_i192;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv25, 1, 0, 0U, 1, 0U, 2, 11,
                3);
  for (c3_i192 = 0; c3_i192 < 33; c3_i192++) {
    c3_y[c3_i192] = c3_dv25[c3_i192];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_k_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_c_Kv;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[33];
  int32_T c3_i193;
  int32_T c3_i194;
  int32_T c3_i195;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_c_Kv = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_n_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_c_Kv), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_c_Kv);
  c3_i193 = 0;
  for (c3_i194 = 0; c3_i194 < 3; c3_i194++) {
    for (c3_i195 = 0; c3_i195 < 11; c3_i195++) {
      (*(real_T (*)[33])c3_outData)[c3_i195 + c3_i193] = c3_y[c3_i195 + c3_i193];
    }

    c3_i193 += 11;
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static void c3_o_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[46])
{
  real_T c3_dv26[46];
  int32_T c3_i196;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv26, 1, 0, 0U, 1, 0U, 1, 46);
  for (c3_i196 = 0; c3_i196 < 46; c3_i196++) {
    c3_y[c3_i196] = c3_dv26[c3_i196];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_l_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_c_Mlim;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[46];
  int32_T c3_i197;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_c_Mlim = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_o_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_c_Mlim), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_c_Mlim);
  for (c3_i197 = 0; c3_i197 < 46; c3_i197++) {
    (*(real_T (*)[46])c3_outData)[c3_i197] = c3_y[c3_i197];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static void c3_p_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[230])
{
  real_T c3_dv27[230];
  int32_T c3_i198;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv27, 1, 0, 0U, 1, 0U, 2, 46,
                5);
  for (c3_i198 = 0; c3_i198 < 230; c3_i198++) {
    c3_y[c3_i198] = c3_dv27[c3_i198];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_m_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_c_Mx;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[230];
  int32_T c3_i199;
  int32_T c3_i200;
  int32_T c3_i201;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_c_Mx = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_p_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_c_Mx), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_c_Mx);
  c3_i199 = 0;
  for (c3_i200 = 0; c3_i200 < 5; c3_i200++) {
    for (c3_i201 = 0; c3_i201 < 46; c3_i201++) {
      (*(real_T (*)[230])c3_outData)[c3_i201 + c3_i199] = c3_y[c3_i201 + c3_i199];
    }

    c3_i199 += 46;
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static void c3_q_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[506])
{
  real_T c3_dv28[506];
  int32_T c3_i202;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv28, 1, 0, 0U, 1, 0U, 2, 46,
                11);
  for (c3_i202 = 0; c3_i202 < 506; c3_i202++) {
    c3_y[c3_i202] = c3_dv28[c3_i202];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_n_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_c_Mv;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[506];
  int32_T c3_i203;
  int32_T c3_i204;
  int32_T c3_i205;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_c_Mv = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_q_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_c_Mv), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_c_Mv);
  c3_i203 = 0;
  for (c3_i204 = 0; c3_i204 < 11; c3_i204++) {
    for (c3_i205 = 0; c3_i205 < 46; c3_i205++) {
      (*(real_T (*)[506])c3_outData)[c3_i205 + c3_i203] = c3_y[c3_i205 + c3_i203];
    }

    c3_i203 += 46;
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static void c3_r_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[4])
{
  real_T c3_dv29[4];
  int32_T c3_i206;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv29, 1, 0, 0U, 1, 0U, 1, 4);
  for (c3_i206 = 0; c3_i206 < 4; c3_i206++) {
    c3_y[c3_i206] = c3_dv29[c3_i206];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_o_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_c_z_degrees;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[4];
  int32_T c3_i207;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_c_z_degrees = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_r_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_c_z_degrees), &c3_thisId,
                        c3_y);
  sf_mex_destroy(&c3_c_z_degrees);
  for (c3_i207 = 0; c3_i207 < 4; c3_i207++) {
    (*(real_T (*)[4])c3_outData)[c3_i207] = c3_y[c3_i207];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static void c3_s_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[2])
{
  real_T c3_dv30[2];
  int32_T c3_i208;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv30, 1, 0, 0U, 1, 0U, 1, 2);
  for (c3_i208 = 0; c3_i208 < 2; c3_i208++) {
    c3_y[c3_i208] = c3_dv30[c3_i208];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_p_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_c_yoff;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[2];
  int32_T c3_i209;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_c_yoff = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_s_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_c_yoff), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_c_yoff);
  for (c3_i209 = 0; c3_i209 < 2; c3_i209++) {
    (*(real_T (*)[2])c3_outData)[c3_i209] = c3_y[c3_i209];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static void c3_t_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[10])
{
  real_T c3_dv31[10];
  int32_T c3_i210;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv31, 1, 0, 0U, 1, 0U, 2, 1,
                10);
  for (c3_i210 = 0; c3_i210 < 10; c3_i210++) {
    c3_y[c3_i210] = c3_dv31[c3_i210];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_q_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_c_blocking_moves;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[10];
  int32_T c3_i211;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_c_blocking_moves = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_t_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_c_blocking_moves),
                        &c3_thisId, c3_y);
  sf_mex_destroy(&c3_c_blocking_moves);
  for (c3_i211 = 0; c3_i211 < 10; c3_i211++) {
    (*(real_T (*)[10])c3_outData)[c3_i211] = c3_y[c3_i211];
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static void c3_u_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId, real_T c3_y[184])
{
  real_T c3_dv32[184];
  int32_T c3_i212;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), c3_dv32, 1, 0, 0U, 1, 0U, 2, 46,
                4);
  for (c3_i212 = 0; c3_i212 < 184; c3_i212++) {
    c3_y[c3_i212] = c3_dv32[c3_i212];
  }

  sf_mex_destroy(&c3_u);
}

static void c3_r_sf_marshallIn(void *chartInstanceVoid, const mxArray
  *c3_mxArrayInData, const char_T *c3_varName, void *c3_outData)
{
  const mxArray *c3_c_Ac;
  const char_T *c3_identifier;
  emlrtMsgIdentifier c3_thisId;
  real_T c3_y[184];
  int32_T c3_i213;
  int32_T c3_i214;
  int32_T c3_i215;
  SFc3_mpclibInstanceStruct *chartInstance;
  chartInstance = (SFc3_mpclibInstanceStruct *)chartInstanceVoid;
  c3_c_Ac = sf_mex_dup(c3_mxArrayInData);
  c3_identifier = c3_varName;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_u_emlrt_marshallIn(chartInstance, sf_mex_dup(c3_c_Ac), &c3_thisId, c3_y);
  sf_mex_destroy(&c3_c_Ac);
  c3_i213 = 0;
  for (c3_i214 = 0; c3_i214 < 4; c3_i214++) {
    for (c3_i215 = 0; c3_i215 < 46; c3_i215++) {
      (*(real_T (*)[184])c3_outData)[c3_i215 + c3_i213] = c3_y[c3_i215 + c3_i213];
    }

    c3_i213 += 46;
  }

  sf_mex_destroy(&c3_mxArrayInData);
}

static uint8_T c3_v_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_b_is_active_c3_mpclib, const char_T *c3_identifier)
{
  uint8_T c3_y;
  emlrtMsgIdentifier c3_thisId;
  c3_thisId.fIdentifier = c3_identifier;
  c3_thisId.fParent = NULL;
  c3_y = c3_w_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c3_b_is_active_c3_mpclib), &c3_thisId);
  sf_mex_destroy(&c3_b_is_active_c3_mpclib);
  return c3_y;
}

static uint8_T c3_w_emlrt_marshallIn(SFc3_mpclibInstanceStruct *chartInstance,
  const mxArray *c3_u, const emlrtMsgIdentifier *c3_parentId)
{
  uint8_T c3_y;
  uint8_T c3_u0;
  (void)chartInstance;
  sf_mex_import(c3_parentId, sf_mex_dup(c3_u), &c3_u0, 1, 3, 0U, 0, 0U, 0);
  c3_y = c3_u0;
  sf_mex_destroy(&c3_u);
  return c3_y;
}

static void init_dsm_address_info(SFc3_mpclibInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

/* SFunction Glue Code */
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

void sf_c3_mpclib_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(4116592134U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(943105118U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2184209396U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2593534341U);
}

mxArray *sf_c3_mpclib_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs", "locals" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,5,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateString("MGA6AC6ylZUP3LtQ0XSLEC");
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,13,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(20);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(11);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(5);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(50);
      pr[1] = (double)(1);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(1);
      mxSetField(mxData,7,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,7,"type",mxType);
    }

    mxSetField(mxData,7,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(1);
      mxSetField(mxData,8,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,8,"type",mxType);
    }

    mxSetField(mxData,8,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,9,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,9,"type",mxType);
    }

    mxSetField(mxData,9,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(1);
      mxSetField(mxData,10,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,10,"type",mxType);
    }

    mxSetField(mxData,10,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,11,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,11,"type",mxType);
    }

    mxSetField(mxData,11,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,12,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,12,"type",mxType);
    }

    mxSetField(mxData,12,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,50,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(46);
      pr[1] = (double)(4);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(4);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(4);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,5,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,5,"type",mxType);
    }

    mxSetField(mxData,5,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,6,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,6,"type",mxType);
    }

    mxSetField(mxData,6,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,7,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,7,"type",mxType);
    }

    mxSetField(mxData,7,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(20);
      pr[1] = (double)(3);
      mxSetField(mxData,8,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,8,"type",mxType);
    }

    mxSetField(mxData,8,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(3);
      mxSetField(mxData,9,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,9,"type",mxType);
    }

    mxSetField(mxData,9,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(10);
      pr[1] = (double)(3);
      mxSetField(mxData,10,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,10,"type",mxType);
    }

    mxSetField(mxData,10,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(11);
      pr[1] = (double)(3);
      mxSetField(mxData,11,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,11,"type",mxType);
    }

    mxSetField(mxData,11,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(5);
      pr[1] = (double)(3);
      mxSetField(mxData,12,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,12,"type",mxType);
    }

    mxSetField(mxData,12,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(4);
      mxSetField(mxData,13,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,13,"type",mxType);
    }

    mxSetField(mxData,13,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(46);
      pr[1] = (double)(1);
      mxSetField(mxData,14,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,14,"type",mxType);
    }

    mxSetField(mxData,14,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(46);
      pr[1] = (double)(1);
      mxSetField(mxData,15,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,15,"type",mxType);
    }

    mxSetField(mxData,15,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(46);
      pr[1] = (double)(11);
      mxSetField(mxData,16,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,16,"type",mxType);
    }

    mxSetField(mxData,16,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(46);
      pr[1] = (double)(5);
      mxSetField(mxData,17,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,17,"type",mxType);
    }

    mxSetField(mxData,17,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,18,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,18,"type",mxType);
    }

    mxSetField(mxData,18,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,19,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,19,"type",mxType);
    }

    mxSetField(mxData,19,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,20,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,20,"type",mxType);
    }

    mxSetField(mxData,20,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,21,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,21,"type",mxType);
    }

    mxSetField(mxData,21,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,22,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,22,"type",mxType);
    }

    mxSetField(mxData,22,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,23,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,23,"type",mxType);
    }

    mxSetField(mxData,23,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(10);
      mxSetField(mxData,24,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,24,"type",mxType);
    }

    mxSetField(mxData,24,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,25,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,25,"type",mxType);
    }

    mxSetField(mxData,25,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,26,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,26,"type",mxType);
    }

    mxSetField(mxData,26,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,27,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,27,"type",mxType);
    }

    mxSetField(mxData,27,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,28,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,28,"type",mxType);
    }

    mxSetField(mxData,28,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,29,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,29,"type",mxType);
    }

    mxSetField(mxData,29,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,30,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,30,"type",mxType);
    }

    mxSetField(mxData,30,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,31,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,31,"type",mxType);
    }

    mxSetField(mxData,31,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,32,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,32,"type",mxType);
    }

    mxSetField(mxData,32,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,33,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,33,"type",mxType);
    }

    mxSetField(mxData,33,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,34,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,34,"type",mxType);
    }

    mxSetField(mxData,34,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,35,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,35,"type",mxType);
    }

    mxSetField(mxData,35,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,36,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,36,"type",mxType);
    }

    mxSetField(mxData,36,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,37,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,37,"type",mxType);
    }

    mxSetField(mxData,37,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,38,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,38,"type",mxType);
    }

    mxSetField(mxData,38,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,39,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,39,"type",mxType);
    }

    mxSetField(mxData,39,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,40,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,40,"type",mxType);
    }

    mxSetField(mxData,40,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,41,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,41,"type",mxType);
    }

    mxSetField(mxData,41,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,42,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,42,"type",mxType);
    }

    mxSetField(mxData,42,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,43,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,43,"type",mxType);
    }

    mxSetField(mxData,43,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,44,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,44,"type",mxType);
    }

    mxSetField(mxData,44,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,45,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,45,"type",mxType);
    }

    mxSetField(mxData,45,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,46,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,46,"type",mxType);
    }

    mxSetField(mxData,46,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(10);
      pr[1] = (double)(1);
      mxSetField(mxData,47,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,47,"type",mxType);
    }

    mxSetField(mxData,47,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(2);
      pr[1] = (double)(1);
      mxSetField(mxData,48,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,48,"type",mxType);
    }

    mxSetField(mxData,48,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(4);
      pr[1] = (double)(1);
      mxSetField(mxData,49,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,49,"type",mxType);
    }

    mxSetField(mxData,49,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxData);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,5,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(10);
      pr[1] = (double)(1);
      mxSetField(mxData,2,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,2,"type",mxType);
    }

    mxSetField(mxData,2,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,3,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,3,"type",mxType);
    }

    mxSetField(mxData,3,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(50);
      pr[1] = (double)(1);
      mxSetField(mxData,4,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(1));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,4,"type",mxType);
    }

    mxSetField(mxData,4,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"locals",mxCreateDoubleMatrix(0,0,mxREAL));
  }

  return(mxAutoinheritanceInfo);
}

mxArray *sf_c3_mpclib_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c3_mpclib_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c3_mpclib(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x6'type','srcId','name','auxInfo'{{M[1],M[20],T\"cost\",},{M[1],M[145],T\"iAout\",},{M[1],M[126],T\"status\",},{M[1],M[19],T\"u\",},{M[1],M[21],T\"useq\",},{M[8],M[0],T\"is_active_c3_mpclib\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 6, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c3_mpclib_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc3_mpclibInstanceStruct *chartInstance;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    chartInstance = (SFc3_mpclibInstanceStruct *) chartInfo->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart
          (sfGlobalDebugInstanceStruct,
           _mpclibMachineNumber_,
           3,
           1,
           1,
           0,
           68,
           0,
           0,
           0,
           0,
           0,
           &(chartInstance->chartNumber),
           &(chartInstance->instanceNumber),
           (void *)S);

        /* Each instance must initialize ist own list of scripts */
        init_script_number_translation(_mpclibMachineNumber_,
          chartInstance->chartNumber,chartInstance->instanceNumber);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          sf_debug_set_chart_disable_implicit_casting
            (sfGlobalDebugInstanceStruct,_mpclibMachineNumber_,
             chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(sfGlobalDebugInstanceStruct,
            _mpclibMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);
          _SFD_SET_DATA_PROPS(0,1,1,0,"rseq");
          _SFD_SET_DATA_PROPS(1,1,1,0,"vseq");
          _SFD_SET_DATA_PROPS(2,1,1,0,"x");
          _SFD_SET_DATA_PROPS(3,1,1,0,"old_u");
          _SFD_SET_DATA_PROPS(4,1,1,0,"iA");
          _SFD_SET_DATA_PROPS(5,1,1,0,"umin");
          _SFD_SET_DATA_PROPS(6,1,1,0,"umax");
          _SFD_SET_DATA_PROPS(7,1,1,0,"ymin");
          _SFD_SET_DATA_PROPS(8,1,1,0,"ymax");
          _SFD_SET_DATA_PROPS(9,1,1,0,"switch_in");
          _SFD_SET_DATA_PROPS(10,1,1,0,"ywt");
          _SFD_SET_DATA_PROPS(11,1,1,0,"duwt");
          _SFD_SET_DATA_PROPS(12,1,1,0,"rhoeps");
          _SFD_SET_DATA_PROPS(13,2,0,1,"u");
          _SFD_SET_DATA_PROPS(14,2,0,1,"cost");
          _SFD_SET_DATA_PROPS(15,2,0,1,"useq");
          _SFD_SET_DATA_PROPS(16,2,0,1,"status");
          _SFD_SET_DATA_PROPS(17,10,0,0,"isQP");
          _SFD_SET_DATA_PROPS(18,10,0,0,"nu");
          _SFD_SET_DATA_PROPS(19,10,0,0,"ny");
          _SFD_SET_DATA_PROPS(20,10,0,0,"degrees");
          _SFD_SET_DATA_PROPS(21,10,0,0,"Hinv");
          _SFD_SET_DATA_PROPS(22,10,0,0,"Kx");
          _SFD_SET_DATA_PROPS(23,10,0,0,"Ku1");
          _SFD_SET_DATA_PROPS(24,10,0,0,"Kut");
          _SFD_SET_DATA_PROPS(25,10,0,0,"Kr");
          _SFD_SET_DATA_PROPS(26,10,0,0,"Kv");
          _SFD_SET_DATA_PROPS(27,10,0,0,"Mlim");
          _SFD_SET_DATA_PROPS(28,10,0,0,"Mx");
          _SFD_SET_DATA_PROPS(29,10,0,0,"Mu1");
          _SFD_SET_DATA_PROPS(30,10,0,0,"Mv");
          _SFD_SET_DATA_PROPS(31,10,0,0,"z_degrees");
          _SFD_SET_DATA_PROPS(32,10,0,0,"utarget");
          _SFD_SET_DATA_PROPS(33,10,0,0,"p");
          _SFD_SET_DATA_PROPS(34,10,0,0,"uoff");
          _SFD_SET_DATA_PROPS(35,10,0,0,"yoff");
          _SFD_SET_DATA_PROPS(36,10,0,0,"maxiter");
          _SFD_SET_DATA_PROPS(37,10,0,0,"nxQP");
          _SFD_SET_DATA_PROPS(38,10,0,0,"openloopflag");
          _SFD_SET_DATA_PROPS(39,10,0,0,"lims_inport");
          _SFD_SET_DATA_PROPS(40,10,0,0,"no_umin");
          _SFD_SET_DATA_PROPS(41,10,0,0,"no_umax");
          _SFD_SET_DATA_PROPS(42,10,0,0,"no_ymin");
          _SFD_SET_DATA_PROPS(43,10,0,0,"no_ymax");
          _SFD_SET_DATA_PROPS(44,10,0,0,"switch_inport");
          _SFD_SET_DATA_PROPS(45,10,0,0,"no_switch");
          _SFD_SET_DATA_PROPS(46,10,0,0,"enable_value");
          _SFD_SET_DATA_PROPS(47,10,0,0,"return_cost");
          _SFD_SET_DATA_PROPS(48,10,0,0,"H");
          _SFD_SET_DATA_PROPS(49,10,0,0,"return_sequence");
          _SFD_SET_DATA_PROPS(50,10,0,0,"blocking_moves");
          _SFD_SET_DATA_PROPS(51,10,0,0,"Linv");
          _SFD_SET_DATA_PROPS(52,10,0,0,"Ac");
          _SFD_SET_DATA_PROPS(53,10,0,0,"no_ywt");
          _SFD_SET_DATA_PROPS(54,10,0,0,"no_duwt");
          _SFD_SET_DATA_PROPS(55,10,0,0,"no_rhoeps");
          _SFD_SET_DATA_PROPS(56,10,0,0,"Wy");
          _SFD_SET_DATA_PROPS(57,10,0,0,"Wdu");
          _SFD_SET_DATA_PROPS(58,10,0,0,"Jm");
          _SFD_SET_DATA_PROPS(59,10,0,0,"SuJm");
          _SFD_SET_DATA_PROPS(60,10,0,0,"I2JmWuI2Jm");
          _SFD_SET_DATA_PROPS(61,10,0,0,"Su1");
          _SFD_SET_DATA_PROPS(62,10,0,0,"I1WuI2Jm");
          _SFD_SET_DATA_PROPS(63,10,0,0,"Sx");
          _SFD_SET_DATA_PROPS(64,10,0,0,"Hv");
          _SFD_SET_DATA_PROPS(65,10,0,0,"Wu");
          _SFD_SET_DATA_PROPS(66,10,0,0,"I1");
          _SFD_SET_DATA_PROPS(67,2,0,1,"iAout");
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of MATLAB Function Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,2,0,0,0,0,0,3,1);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,2587);
        _SFD_CV_INIT_EML_IF(0,1,0,648,733,2048,2586);
        _SFD_CV_INIT_EML_IF(0,1,1,1003,1024,1532,2047);

        {
          static int condStart[] = { 651, 676, 708 };

          static int condEnd[] = { 671, 703, 733 };

          static int pfixExpr[] = { 0, 1, -1, -3, 2, -1, -3 };

          _SFD_CV_INIT_EML_MCDC(0,1,0,651,733,3,0,&(condStart[0]),&(condEnd[0]),
                                7,&(pfixExpr[0]));
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 20;
          _SFD_SET_DATA_COMPILED_PROPS(0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_g_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 11;
          _SFD_SET_DATA_COMPILED_PROPS(1,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_f_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 5;
          _SFD_SET_DATA_COMPILED_PROPS(2,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_e_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(3,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 50;
          _SFD_SET_DATA_COMPILED_PROPS(4,SF_UINT8,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(5,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(6,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(7,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(8,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(9,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)NULL);

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(10,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_d_sf_marshallOut,(MexInFcnForType)NULL);
        }

        _SFD_SET_DATA_COMPILED_PROPS(11,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(12,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)NULL);
        _SFD_SET_DATA_COMPILED_PROPS(13,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)c3_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(14,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)c3_b_sf_marshallIn);

        {
          unsigned int dimVector[1];
          dimVector[0]= 10;
          _SFD_SET_DATA_COMPILED_PROPS(15,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)
            c3_c_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(16,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)c3_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(17,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_k_sf_marshallOut,(MexInFcnForType)c3_e_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(18,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)c3_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(19,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)c3_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(20,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)c3_b_sf_marshallIn);

        {
          unsigned int dimVector[2];
          dimVector[0]= 4;
          dimVector[1]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(21,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_i_sf_marshallOut,(MexInFcnForType)
            c3_f_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 5;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(22,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_t_sf_marshallOut,(MexInFcnForType)
            c3_g_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 1;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(23,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_s_sf_marshallOut,(MexInFcnForType)
            c3_h_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 10;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(24,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_r_sf_marshallOut,(MexInFcnForType)
            c3_i_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 20;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(25,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_q_sf_marshallOut,(MexInFcnForType)
            c3_j_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 11;
          dimVector[1]= 3;
          _SFD_SET_DATA_COMPILED_PROPS(26,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_p_sf_marshallOut,(MexInFcnForType)
            c3_k_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 46;
          _SFD_SET_DATA_COMPILED_PROPS(27,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_n_sf_marshallOut,(MexInFcnForType)
            c3_l_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 46;
          dimVector[1]= 5;
          _SFD_SET_DATA_COMPILED_PROPS(28,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_o_sf_marshallOut,(MexInFcnForType)
            c3_m_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 46;
          _SFD_SET_DATA_COMPILED_PROPS(29,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_n_sf_marshallOut,(MexInFcnForType)
            c3_l_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 46;
          dimVector[1]= 11;
          _SFD_SET_DATA_COMPILED_PROPS(30,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_m_sf_marshallOut,(MexInFcnForType)
            c3_n_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(31,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_l_sf_marshallOut,(MexInFcnForType)
            c3_o_sf_marshallIn);
        }

        {
          unsigned int dimVector[1];
          dimVector[0]= 10;
          _SFD_SET_DATA_COMPILED_PROPS(32,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_c_sf_marshallOut,(MexInFcnForType)
            c3_c_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(33,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)c3_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(34,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)c3_b_sf_marshallIn);

        {
          unsigned int dimVector[1];
          dimVector[0]= 2;
          _SFD_SET_DATA_COMPILED_PROPS(35,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_d_sf_marshallOut,(MexInFcnForType)
            c3_p_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(36,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)c3_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(37,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)c3_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(38,SF_UINT8,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_k_sf_marshallOut,(MexInFcnForType)c3_e_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(39,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)c3_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(40,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)c3_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(41,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)c3_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(42,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)c3_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(43,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)c3_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(44,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)c3_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(45,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)c3_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(46,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)c3_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(47,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)c3_b_sf_marshallIn);

        {
          unsigned int dimVector[2];
          dimVector[0]= 4;
          dimVector[1]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(48,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_i_sf_marshallOut,(MexInFcnForType)
            c3_f_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(49,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)c3_b_sf_marshallIn);

        {
          unsigned int dimVector[2];
          dimVector[0]= 1;
          dimVector[1]= 10;
          _SFD_SET_DATA_COMPILED_PROPS(50,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_j_sf_marshallOut,(MexInFcnForType)
            c3_q_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 4;
          dimVector[1]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(51,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_i_sf_marshallOut,(MexInFcnForType)
            c3_f_sf_marshallIn);
        }

        {
          unsigned int dimVector[2];
          dimVector[0]= 46;
          dimVector[1]= 4;
          _SFD_SET_DATA_COMPILED_PROPS(52,SF_DOUBLE,2,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_h_sf_marshallOut,(MexInFcnForType)
            c3_r_sf_marshallIn);
        }

        _SFD_SET_DATA_COMPILED_PROPS(53,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)c3_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(54,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)c3_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(55,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)c3_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(56,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)c3_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(57,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)c3_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(58,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)c3_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(59,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)c3_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(60,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)c3_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(61,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)c3_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(62,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)c3_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(63,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)c3_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(64,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)c3_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(65,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)c3_b_sf_marshallIn);
        _SFD_SET_DATA_COMPILED_PROPS(66,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,0,
          (MexFcnForType)c3_b_sf_marshallOut,(MexInFcnForType)c3_b_sf_marshallIn);

        {
          unsigned int dimVector[1];
          dimVector[0]= 50;
          _SFD_SET_DATA_COMPILED_PROPS(67,SF_UINT8,1,&(dimVector[0]),0,0,0,0.0,
            1.0,0,0,(MexFcnForType)c3_sf_marshallOut,(MexInFcnForType)
            c3_sf_marshallIn);
        }

        {
          real_T *c3_old_u;
          real_T *c3_umin;
          real_T *c3_umax;
          real_T *c3_switch_in;
          real_T *c3_duwt;
          real_T *c3_rhoeps;
          real_T *c3_u;
          real_T *c3_cost;
          real_T *c3_status;
          real_T (*c3_rseq)[20];
          real_T (*c3_vseq)[11];
          real_T (*c3_x)[5];
          boolean_T (*c3_iA)[50];
          real_T (*c3_ymin)[2];
          real_T (*c3_ymax)[2];
          real_T (*c3_ywt)[2];
          real_T (*c3_useq)[10];
          boolean_T (*c3_iAout)[50];
          c3_iAout = (boolean_T (*)[50])ssGetOutputPortSignal(chartInstance->S,
            5);
          c3_status = (real_T *)ssGetOutputPortSignal(chartInstance->S, 4);
          c3_useq = (real_T (*)[10])ssGetOutputPortSignal(chartInstance->S, 3);
          c3_cost = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
          c3_u = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          c3_rhoeps = (real_T *)ssGetInputPortSignal(chartInstance->S, 12);
          c3_duwt = (real_T *)ssGetInputPortSignal(chartInstance->S, 11);
          c3_ywt = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 10);
          c3_switch_in = (real_T *)ssGetInputPortSignal(chartInstance->S, 9);
          c3_ymax = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 8);
          c3_ymin = (real_T (*)[2])ssGetInputPortSignal(chartInstance->S, 7);
          c3_umax = (real_T *)ssGetInputPortSignal(chartInstance->S, 6);
          c3_umin = (real_T *)ssGetInputPortSignal(chartInstance->S, 5);
          c3_iA = (boolean_T (*)[50])ssGetInputPortSignal(chartInstance->S, 4);
          c3_old_u = (real_T *)ssGetInputPortSignal(chartInstance->S, 3);
          c3_x = (real_T (*)[5])ssGetInputPortSignal(chartInstance->S, 2);
          c3_vseq = (real_T (*)[11])ssGetInputPortSignal(chartInstance->S, 1);
          c3_rseq = (real_T (*)[20])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, *c3_rseq);
          _SFD_SET_DATA_VALUE_PTR(1U, *c3_vseq);
          _SFD_SET_DATA_VALUE_PTR(2U, *c3_x);
          _SFD_SET_DATA_VALUE_PTR(3U, c3_old_u);
          _SFD_SET_DATA_VALUE_PTR(4U, *c3_iA);
          _SFD_SET_DATA_VALUE_PTR(5U, c3_umin);
          _SFD_SET_DATA_VALUE_PTR(6U, c3_umax);
          _SFD_SET_DATA_VALUE_PTR(7U, *c3_ymin);
          _SFD_SET_DATA_VALUE_PTR(8U, *c3_ymax);
          _SFD_SET_DATA_VALUE_PTR(9U, c3_switch_in);
          _SFD_SET_DATA_VALUE_PTR(10U, *c3_ywt);
          _SFD_SET_DATA_VALUE_PTR(11U, c3_duwt);
          _SFD_SET_DATA_VALUE_PTR(12U, c3_rhoeps);
          _SFD_SET_DATA_VALUE_PTR(13U, c3_u);
          _SFD_SET_DATA_VALUE_PTR(14U, c3_cost);
          _SFD_SET_DATA_VALUE_PTR(15U, *c3_useq);
          _SFD_SET_DATA_VALUE_PTR(16U, c3_status);
          _SFD_SET_DATA_VALUE_PTR(17U, &chartInstance->c3_isQP);
          _SFD_SET_DATA_VALUE_PTR(18U, &chartInstance->c3_nu);
          _SFD_SET_DATA_VALUE_PTR(19U, &chartInstance->c3_ny);
          _SFD_SET_DATA_VALUE_PTR(20U, &chartInstance->c3_degrees);
          _SFD_SET_DATA_VALUE_PTR(21U, chartInstance->c3_Hinv);
          _SFD_SET_DATA_VALUE_PTR(22U, chartInstance->c3_Kx);
          _SFD_SET_DATA_VALUE_PTR(23U, chartInstance->c3_Ku1);
          _SFD_SET_DATA_VALUE_PTR(24U, chartInstance->c3_Kut);
          _SFD_SET_DATA_VALUE_PTR(25U, chartInstance->c3_Kr);
          _SFD_SET_DATA_VALUE_PTR(26U, chartInstance->c3_Kv);
          _SFD_SET_DATA_VALUE_PTR(27U, chartInstance->c3_Mlim);
          _SFD_SET_DATA_VALUE_PTR(28U, chartInstance->c3_Mx);
          _SFD_SET_DATA_VALUE_PTR(29U, chartInstance->c3_Mu1);
          _SFD_SET_DATA_VALUE_PTR(30U, chartInstance->c3_Mv);
          _SFD_SET_DATA_VALUE_PTR(31U, chartInstance->c3_z_degrees);
          _SFD_SET_DATA_VALUE_PTR(32U, chartInstance->c3_utarget);
          _SFD_SET_DATA_VALUE_PTR(33U, &chartInstance->c3_p);
          _SFD_SET_DATA_VALUE_PTR(34U, &chartInstance->c3_uoff);
          _SFD_SET_DATA_VALUE_PTR(35U, chartInstance->c3_yoff);
          _SFD_SET_DATA_VALUE_PTR(36U, &chartInstance->c3_maxiter);
          _SFD_SET_DATA_VALUE_PTR(37U, &chartInstance->c3_nxQP);
          _SFD_SET_DATA_VALUE_PTR(38U, &chartInstance->c3_openloopflag);
          _SFD_SET_DATA_VALUE_PTR(39U, &chartInstance->c3_lims_inport);
          _SFD_SET_DATA_VALUE_PTR(40U, &chartInstance->c3_no_umin);
          _SFD_SET_DATA_VALUE_PTR(41U, &chartInstance->c3_no_umax);
          _SFD_SET_DATA_VALUE_PTR(42U, &chartInstance->c3_no_ymin);
          _SFD_SET_DATA_VALUE_PTR(43U, &chartInstance->c3_no_ymax);
          _SFD_SET_DATA_VALUE_PTR(44U, &chartInstance->c3_switch_inport);
          _SFD_SET_DATA_VALUE_PTR(45U, &chartInstance->c3_no_switch);
          _SFD_SET_DATA_VALUE_PTR(46U, &chartInstance->c3_enable_value);
          _SFD_SET_DATA_VALUE_PTR(47U, &chartInstance->c3_return_cost);
          _SFD_SET_DATA_VALUE_PTR(48U, chartInstance->c3_H);
          _SFD_SET_DATA_VALUE_PTR(49U, &chartInstance->c3_return_sequence);
          _SFD_SET_DATA_VALUE_PTR(50U, chartInstance->c3_blocking_moves);
          _SFD_SET_DATA_VALUE_PTR(51U, chartInstance->c3_Linv);
          _SFD_SET_DATA_VALUE_PTR(52U, chartInstance->c3_Ac);
          _SFD_SET_DATA_VALUE_PTR(53U, &chartInstance->c3_no_ywt);
          _SFD_SET_DATA_VALUE_PTR(54U, &chartInstance->c3_no_duwt);
          _SFD_SET_DATA_VALUE_PTR(55U, &chartInstance->c3_no_rhoeps);
          _SFD_SET_DATA_VALUE_PTR(56U, &chartInstance->c3_Wy);
          _SFD_SET_DATA_VALUE_PTR(57U, &chartInstance->c3_Wdu);
          _SFD_SET_DATA_VALUE_PTR(58U, &chartInstance->c3_Jm);
          _SFD_SET_DATA_VALUE_PTR(59U, &chartInstance->c3_SuJm);
          _SFD_SET_DATA_VALUE_PTR(60U, &chartInstance->c3_I2JmWuI2Jm);
          _SFD_SET_DATA_VALUE_PTR(61U, &chartInstance->c3_Su1);
          _SFD_SET_DATA_VALUE_PTR(62U, &chartInstance->c3_I1WuI2Jm);
          _SFD_SET_DATA_VALUE_PTR(63U, &chartInstance->c3_Sx);
          _SFD_SET_DATA_VALUE_PTR(64U, &chartInstance->c3_Hv);
          _SFD_SET_DATA_VALUE_PTR(65U, &chartInstance->c3_Wu);
          _SFD_SET_DATA_VALUE_PTR(66U, &chartInstance->c3_I1);
          _SFD_SET_DATA_VALUE_PTR(67U, *c3_iAout);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(sfGlobalDebugInstanceStruct,
        _mpclibMachineNumber_,chartInstance->chartNumber,
        chartInstance->instanceNumber);
    }
  }
}

static const char* sf_get_instance_specialization(void)
{
  return "bFKCrsVmn3lP2SIh82GF7D";
}

static void sf_opaque_initialize_c3_mpclib(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc3_mpclibInstanceStruct*) chartInstanceVar)->S,
    0);
  initialize_params_c3_mpclib((SFc3_mpclibInstanceStruct*) chartInstanceVar);
  initialize_c3_mpclib((SFc3_mpclibInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c3_mpclib(void *chartInstanceVar)
{
  enable_c3_mpclib((SFc3_mpclibInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c3_mpclib(void *chartInstanceVar)
{
  disable_c3_mpclib((SFc3_mpclibInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c3_mpclib(void *chartInstanceVar)
{
  sf_gateway_c3_mpclib((SFc3_mpclibInstanceStruct*) chartInstanceVar);
}

extern const mxArray* sf_internal_get_sim_state_c3_mpclib(SimStruct* S)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c3_mpclib((SFc3_mpclibInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c3_mpclib();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

extern void sf_internal_set_sim_state_c3_mpclib(SimStruct* S, const mxArray *st)
{
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
  ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[3];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxDuplicateArray(st);      /* high level simctx */
  prhs[2] = (mxArray*) sf_get_sim_state_info_c3_mpclib();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 3, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c3_mpclib((SFc3_mpclibInstanceStruct*)chartInfo->chartInstance,
    mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static const mxArray* sf_opaque_get_sim_state_c3_mpclib(SimStruct* S)
{
  return sf_internal_get_sim_state_c3_mpclib(S);
}

static void sf_opaque_set_sim_state_c3_mpclib(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c3_mpclib(S, st);
}

static void sf_opaque_terminate_c3_mpclib(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc3_mpclibInstanceStruct*) chartInstanceVar)->S;
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_mpclib_optimization_info();
    }

    finalize_c3_mpclib((SFc3_mpclibInstanceStruct*) chartInstanceVar);
    utFree((void *)chartInstanceVar);
    if (crtInfo != NULL) {
      utFree((void *)crtInfo);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc3_mpclib((SFc3_mpclibInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c3_mpclib(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)(ssGetUserData(S));
    ChartInfoStruct * chartInfo = (ChartInfoStruct *)(crtInfo->instanceInfo);
    initialize_params_c3_mpclib((SFc3_mpclibInstanceStruct*)
      (chartInfo->chartInstance));
  }
}

static void mdlSetWorkWidths_c3_mpclib(SimStruct *S)
{
  /* Actual parameters from chart:
     Ac H Hinv Hv I1 I1WuI2Jm I2JmWuI2Jm Jm Kr Ku1 Kut Kv Kx Linv Mlim Mu1 Mv Mx Su1 SuJm Sx Wdu Wu Wy blocking_moves degrees enable_value isQP lims_inport maxiter no_duwt no_rhoeps no_switch no_umax no_umin no_ymax no_ymin no_ywt nu nxQP ny openloopflag p return_cost return_sequence switch_inport uoff utarget yoff z_degrees
   */
  const char_T *rtParamNames[] = { "Ac", "H", "Hinv", "Hv", "I1", "I1WuI2Jm",
    "I2JmWuI2Jm", "Jm", "Kr", "Ku1", "Kut", "Kv", "Kx", "Linv", "Mlim", "Mu1",
    "Mv", "Mx", "Su1", "SuJm", "Sx", "Wdu", "Wu", "Wy", "blocking_moves",
    "degrees", "enable_value", "isQP", "lims_inport", "maxiter", "no_duwt",
    "no_rhoeps", "no_switch", "no_umax", "no_umin", "no_ymax", "no_ymin",
    "no_ywt", "nu", "nxQP", "ny", "openloopflag", "p", "return_cost",
    "return_sequence", "switch_inport", "uoff", "utarget", "yoff", "z_degrees" };

  ssSetNumRunTimeParams(S,ssGetSFcnParamsCount(S));

  /* registration for Ac*/
  ssRegDlgParamAsRunTimeParam(S, 0, 0, rtParamNames[0], SS_DOUBLE);

  /* registration for H*/
  ssRegDlgParamAsRunTimeParam(S, 1, 1, rtParamNames[1], SS_DOUBLE);

  /* registration for Hinv*/
  ssRegDlgParamAsRunTimeParam(S, 2, 2, rtParamNames[2], SS_DOUBLE);

  /* registration for Hv*/
  ssRegDlgParamAsRunTimeParam(S, 3, 3, rtParamNames[3], SS_DOUBLE);

  /* registration for I1*/
  ssRegDlgParamAsRunTimeParam(S, 4, 4, rtParamNames[4], SS_DOUBLE);

  /* registration for I1WuI2Jm*/
  ssRegDlgParamAsRunTimeParam(S, 5, 5, rtParamNames[5], SS_DOUBLE);

  /* registration for I2JmWuI2Jm*/
  ssRegDlgParamAsRunTimeParam(S, 6, 6, rtParamNames[6], SS_DOUBLE);

  /* registration for Jm*/
  ssRegDlgParamAsRunTimeParam(S, 7, 7, rtParamNames[7], SS_DOUBLE);

  /* registration for Kr*/
  ssRegDlgParamAsRunTimeParam(S, 8, 8, rtParamNames[8], SS_DOUBLE);

  /* registration for Ku1*/
  ssRegDlgParamAsRunTimeParam(S, 9, 9, rtParamNames[9], SS_DOUBLE);

  /* registration for Kut*/
  ssRegDlgParamAsRunTimeParam(S, 10, 10, rtParamNames[10], SS_DOUBLE);

  /* registration for Kv*/
  ssRegDlgParamAsRunTimeParam(S, 11, 11, rtParamNames[11], SS_DOUBLE);

  /* registration for Kx*/
  ssRegDlgParamAsRunTimeParam(S, 12, 12, rtParamNames[12], SS_DOUBLE);

  /* registration for Linv*/
  ssRegDlgParamAsRunTimeParam(S, 13, 13, rtParamNames[13], SS_DOUBLE);

  /* registration for Mlim*/
  ssRegDlgParamAsRunTimeParam(S, 14, 14, rtParamNames[14], SS_DOUBLE);

  /* registration for Mu1*/
  ssRegDlgParamAsRunTimeParam(S, 15, 15, rtParamNames[15], SS_DOUBLE);

  /* registration for Mv*/
  ssRegDlgParamAsRunTimeParam(S, 16, 16, rtParamNames[16], SS_DOUBLE);

  /* registration for Mx*/
  ssRegDlgParamAsRunTimeParam(S, 17, 17, rtParamNames[17], SS_DOUBLE);

  /* registration for Su1*/
  ssRegDlgParamAsRunTimeParam(S, 18, 18, rtParamNames[18], SS_DOUBLE);

  /* registration for SuJm*/
  ssRegDlgParamAsRunTimeParam(S, 19, 19, rtParamNames[19], SS_DOUBLE);

  /* registration for Sx*/
  ssRegDlgParamAsRunTimeParam(S, 20, 20, rtParamNames[20], SS_DOUBLE);

  /* registration for Wdu*/
  ssRegDlgParamAsRunTimeParam(S, 21, 21, rtParamNames[21], SS_DOUBLE);

  /* registration for Wu*/
  ssRegDlgParamAsRunTimeParam(S, 22, 22, rtParamNames[22], SS_DOUBLE);

  /* registration for Wy*/
  ssRegDlgParamAsRunTimeParam(S, 23, 23, rtParamNames[23], SS_DOUBLE);

  /* registration for blocking_moves*/
  ssRegDlgParamAsRunTimeParam(S, 24, 24, rtParamNames[24], SS_DOUBLE);

  /* registration for degrees*/
  ssRegDlgParamAsRunTimeParam(S, 25, 25, rtParamNames[25], SS_DOUBLE);

  /* registration for enable_value*/
  ssRegDlgParamAsRunTimeParam(S, 26, 26, rtParamNames[26], SS_DOUBLE);

  /* registration for isQP*/
  ssRegDlgParamAsRunTimeParam(S, 27, 27, rtParamNames[27], SS_BOOLEAN);

  /* registration for lims_inport*/
  ssRegDlgParamAsRunTimeParam(S, 28, 28, rtParamNames[28], SS_DOUBLE);

  /* registration for maxiter*/
  ssRegDlgParamAsRunTimeParam(S, 29, 29, rtParamNames[29], SS_DOUBLE);

  /* registration for no_duwt*/
  ssRegDlgParamAsRunTimeParam(S, 30, 30, rtParamNames[30], SS_DOUBLE);

  /* registration for no_rhoeps*/
  ssRegDlgParamAsRunTimeParam(S, 31, 31, rtParamNames[31], SS_DOUBLE);

  /* registration for no_switch*/
  ssRegDlgParamAsRunTimeParam(S, 32, 32, rtParamNames[32], SS_DOUBLE);

  /* registration for no_umax*/
  ssRegDlgParamAsRunTimeParam(S, 33, 33, rtParamNames[33], SS_DOUBLE);

  /* registration for no_umin*/
  ssRegDlgParamAsRunTimeParam(S, 34, 34, rtParamNames[34], SS_DOUBLE);

  /* registration for no_ymax*/
  ssRegDlgParamAsRunTimeParam(S, 35, 35, rtParamNames[35], SS_DOUBLE);

  /* registration for no_ymin*/
  ssRegDlgParamAsRunTimeParam(S, 36, 36, rtParamNames[36], SS_DOUBLE);

  /* registration for no_ywt*/
  ssRegDlgParamAsRunTimeParam(S, 37, 37, rtParamNames[37], SS_DOUBLE);

  /* registration for nu*/
  ssRegDlgParamAsRunTimeParam(S, 38, 38, rtParamNames[38], SS_DOUBLE);

  /* registration for nxQP*/
  ssRegDlgParamAsRunTimeParam(S, 39, 39, rtParamNames[39], SS_DOUBLE);

  /* registration for ny*/
  ssRegDlgParamAsRunTimeParam(S, 40, 40, rtParamNames[40], SS_DOUBLE);

  /* registration for openloopflag*/
  ssRegDlgParamAsRunTimeParam(S, 41, 41, rtParamNames[41], SS_BOOLEAN);

  /* registration for p*/
  ssRegDlgParamAsRunTimeParam(S, 42, 42, rtParamNames[42], SS_DOUBLE);

  /* registration for return_cost*/
  ssRegDlgParamAsRunTimeParam(S, 43, 43, rtParamNames[43], SS_DOUBLE);

  /* registration for return_sequence*/
  ssRegDlgParamAsRunTimeParam(S, 44, 44, rtParamNames[44], SS_DOUBLE);

  /* registration for switch_inport*/
  ssRegDlgParamAsRunTimeParam(S, 45, 45, rtParamNames[45], SS_DOUBLE);

  /* registration for uoff*/
  ssRegDlgParamAsRunTimeParam(S, 46, 46, rtParamNames[46], SS_DOUBLE);

  /* registration for utarget*/
  ssRegDlgParamAsRunTimeParam(S, 47, 47, rtParamNames[47], SS_DOUBLE);

  /* registration for yoff*/
  ssRegDlgParamAsRunTimeParam(S, 48, 48, rtParamNames[48], SS_DOUBLE);

  /* registration for z_degrees*/
  ssRegDlgParamAsRunTimeParam(S, 49, 49, rtParamNames[49], SS_DOUBLE);
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    mxArray *infoStruct = load_mpclib_optimization_info();
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable(sf_get_instance_specialization(),infoStruct,3);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop(sf_get_instance_specialization(),
                infoStruct,3,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop
      (sf_get_instance_specialization(),infoStruct,3,
       "gatewayCannotBeInlinedMultipleTimes"));
    sf_update_buildInfo(sf_get_instance_specialization(),infoStruct,3);
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 1, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 2, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 3, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 4, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 5, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 6, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 7, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 8, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 9, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 10, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 11, SS_REUSABLE_AND_LOCAL);
      ssSetInputPortOptimOpts(S, 12, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,sf_get_instance_specialization(),
        infoStruct,3,13);
      sf_mark_chart_reusable_outputs(S,sf_get_instance_specialization(),
        infoStruct,3,5);
    }

    {
      unsigned int outPortIdx;
      for (outPortIdx=1; outPortIdx<=5; ++outPortIdx) {
        ssSetOutputPortOptimizeInIR(S, outPortIdx, 1U);
      }
    }

    {
      unsigned int inPortIdx;
      for (inPortIdx=0; inPortIdx < 13; ++inPortIdx) {
        ssSetInputPortOptimizeInIR(S, inPortIdx, 1U);
      }
    }

    sf_set_rtw_dwork_info(S,sf_get_instance_specialization(),infoStruct,3);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
  } else {
  }

  ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  ssSetChecksum0(S,(635007846U));
  ssSetChecksum1(S,(2604604812U));
  ssSetChecksum2(S,(302458395U));
  ssSetChecksum3(S,(2285852399U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
  ssSupportsMultipleExecInstances(S,1);
}

static void mdlRTW_c3_mpclib(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c3_mpclib(SimStruct *S)
{
  SFc3_mpclibInstanceStruct *chartInstance;
  ChartRunTimeInfo * crtInfo = (ChartRunTimeInfo *)utMalloc(sizeof
    (ChartRunTimeInfo));
  chartInstance = (SFc3_mpclibInstanceStruct *)utMalloc(sizeof
    (SFc3_mpclibInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc3_mpclibInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c3_mpclib;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c3_mpclib;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c3_mpclib;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c3_mpclib;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c3_mpclib;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c3_mpclib;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c3_mpclib;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c3_mpclib;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c3_mpclib;
  chartInstance->chartInfo.mdlStart = mdlStart_c3_mpclib;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c3_mpclib;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.debugInstance = sfGlobalDebugInstanceStruct;
  chartInstance->S = S;
  crtInfo->instanceInfo = (&(chartInstance->chartInfo));
  crtInfo->isJITEnabled = false;
  ssSetUserData(S,(void *)(crtInfo));  /* register the chart instance with simstruct */
  init_dsm_address_info(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  sf_opaque_init_subchart_simstructs(chartInstance->chartInfo.chartInstance);
  chart_debug_initialization(S,1);
}

void c3_mpclib_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c3_mpclib(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c3_mpclib(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c3_mpclib(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c3_mpclib_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
