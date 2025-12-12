/* Include files */

#include "vtg_sim_r24b_sfun.h"
#include "c4_vtg_sim_r24b.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(S);
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

/* Forward Declarations */

/* Type Definitions */

/* Named Constants */
#define CALL_EVENT                     (-1)

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;

/* Function Declarations */
static void initialize_c4_vtg_sim_r24b(SFc4_vtg_sim_r24bInstanceStruct
  *chartInstance);
static void initialize_params_c4_vtg_sim_r24b(SFc4_vtg_sim_r24bInstanceStruct
  *chartInstance);
static void mdl_start_c4_vtg_sim_r24b(SFc4_vtg_sim_r24bInstanceStruct
  *chartInstance);
static void mdl_terminate_c4_vtg_sim_r24b(SFc4_vtg_sim_r24bInstanceStruct
  *chartInstance);
static void mdl_setup_runtime_resources_c4_vtg_sim_r24b
  (SFc4_vtg_sim_r24bInstanceStruct *chartInstance);
static void mdl_cleanup_runtime_resources_c4_vtg_sim_r24b
  (SFc4_vtg_sim_r24bInstanceStruct *chartInstance);
static void enable_c4_vtg_sim_r24b(SFc4_vtg_sim_r24bInstanceStruct
  *chartInstance);
static void disable_c4_vtg_sim_r24b(SFc4_vtg_sim_r24bInstanceStruct
  *chartInstance);
static void sf_gateway_c4_vtg_sim_r24b(SFc4_vtg_sim_r24bInstanceStruct
  *chartInstance);
static void ext_mode_exec_c4_vtg_sim_r24b(SFc4_vtg_sim_r24bInstanceStruct
  *chartInstance);
static void c4_update_jit_animation_c4_vtg_sim_r24b
  (SFc4_vtg_sim_r24bInstanceStruct *chartInstance);
static void c4_do_animation_call_c4_vtg_sim_r24b(SFc4_vtg_sim_r24bInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c4_vtg_sim_r24b
  (SFc4_vtg_sim_r24bInstanceStruct *chartInstance);
static void set_sim_state_c4_vtg_sim_r24b(SFc4_vtg_sim_r24bInstanceStruct
  *chartInstance, const mxArray *c4_st);
static void c4_emlrt_marshallIn(SFc4_vtg_sim_r24bInstanceStruct *chartInstance,
  const mxArray *c4_nullptr, const char_T *c4_identifier, real_T c4_y[16]);
static void c4_b_emlrt_marshallIn(SFc4_vtg_sim_r24bInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId, real_T c4_y[16]);
static int32_T c4_c_emlrt_marshallIn(SFc4_vtg_sim_r24bInstanceStruct
  *chartInstance, const mxArray *c4_nullptr, const char_T *c4_identifier);
static int32_T c4_d_emlrt_marshallIn(SFc4_vtg_sim_r24bInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId);
static void init_dsm_address_info(SFc4_vtg_sim_r24bInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc4_vtg_sim_r24bInstanceStruct
  *chartInstance);

/* Function Definitions */
static void initialize_c4_vtg_sim_r24b(SFc4_vtg_sim_r24bInstanceStruct
  *chartInstance)
{
  sim_mode_is_external(chartInstance->S);
  chartInstance->c4_doneDoubleBufferReInit = false;
  chartInstance->c4_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void initialize_params_c4_vtg_sim_r24b(SFc4_vtg_sim_r24bInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void mdl_start_c4_vtg_sim_r24b(SFc4_vtg_sim_r24bInstanceStruct
  *chartInstance)
{
  sim_mode_is_external(chartInstance->S);
}

static void mdl_terminate_c4_vtg_sim_r24b(SFc4_vtg_sim_r24bInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void mdl_setup_runtime_resources_c4_vtg_sim_r24b
  (SFc4_vtg_sim_r24bInstanceStruct *chartInstance)
{
  static const uint32_T c4_decisionTxtEndIdx = 0U;
  static const uint32_T c4_decisionTxtStartIdx = 0U;
  sfSetAnimationVectors(chartInstance->S, &chartInstance->c4_JITStateAnimation[0],
                        &chartInstance->c4_JITTransitionAnimation[0]);
  covrtCreateStateflowInstanceData(chartInstance->c4_covrtInstance, 1U, 0U, 1U,
    47U);
  covrtChartInitFcn(chartInstance->c4_covrtInstance, 0U, false, false, false);
  covrtStateInitFcn(chartInstance->c4_covrtInstance, 0U, 0U, false, false, false,
                    0U, &c4_decisionTxtStartIdx, &c4_decisionTxtEndIdx);
  covrtTransInitFcn(chartInstance->c4_covrtInstance, 0U, 0, NULL, NULL, 0U, NULL);
  covrtEmlInitFcn(chartInstance->c4_covrtInstance, "", 4U, 0U, 1U, 0U, 0U, 0U,
                  0U, 0U, 0U, 0U, 0U, 0U);
  covrtEmlFcnInitFcn(chartInstance->c4_covrtInstance, 4U, 0U, 0U,
                     "c4_vtg_sim_r24b", 0, -1, 581);
}

static void mdl_cleanup_runtime_resources_c4_vtg_sim_r24b
  (SFc4_vtg_sim_r24bInstanceStruct *chartInstance)
{
  covrtDeleteStateflowInstanceData(chartInstance->c4_covrtInstance);
}

static void enable_c4_vtg_sim_r24b(SFc4_vtg_sim_r24bInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c4_vtg_sim_r24b(SFc4_vtg_sim_r24bInstanceStruct
  *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void sf_gateway_c4_vtg_sim_r24b(SFc4_vtg_sim_r24bInstanceStruct
  *chartInstance)
{
  int32_T c4_b_info;
  int32_T c4_i;
  int32_T c4_i1;
  int32_T c4_i2;
  int32_T c4_i3;
  int32_T c4_i4;
  int32_T c4_i5;
  int32_T c4_i6;
  if (covrtIsSigCovEnabledFcn(chartInstance->c4_covrtInstance, 2U) != 0U) {
    for (c4_i = 0; c4_i < 8; c4_i++) {
      covrtSigUpdateFcnAssumingCovEnabled(chartInstance->c4_covrtInstance, 2U,
        (real_T)(*chartInstance->c4_select)[c4_i]);
    }
  }

  if (covrtIsSigCovEnabledFcn(chartInstance->c4_covrtInstance, 1U) != 0U) {
    for (c4_i1 = 0; c4_i1 < 16; c4_i1++) {
      covrtSigUpdateFcnAssumingCovEnabled(chartInstance->c4_covrtInstance, 1U, (*
        chartInstance->c4_U)[c4_i1]);
    }
  }

  if (covrtIsSigCovEnabledFcn(chartInstance->c4_covrtInstance, 0U) != 0U) {
    for (c4_i2 = 0; c4_i2 < 16; c4_i2++) {
      covrtSigUpdateFcnAssumingCovEnabled(chartInstance->c4_covrtInstance, 0U, (*
        chartInstance->c4_T)[c4_i2]);
    }
  }

  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c4_JITTransitionAnimation[0] = 0U;
  chartInstance->c4_sfEvent = CALL_EVENT;
  covrtEmlFcnEval(chartInstance->c4_covrtInstance, 4U, 0, 0);
  for (c4_i3 = 0; c4_i3 < 16; c4_i3++) {
    (*chartInstance->c4_T_out)[c4_i3] = (*chartInstance->c4_T)[c4_i3];
  }

  for (c4_i4 = 0; c4_i4 < 16; c4_i4++) {
    (*chartInstance->c4_U_out)[c4_i4] = (*chartInstance->c4_U)[c4_i4];
  }

  c4_b_info = ordschur_reorder(4, &(*chartInstance->c4_T_out)[0],
    &(*chartInstance->c4_U_out)[0], &(*chartInstance->c4_select)[0]);
  *chartInstance->c4_info = c4_b_info;
  if (covrtIsSigCovEnabledFcn(chartInstance->c4_covrtInstance, 3U) != 0U) {
    for (c4_i5 = 0; c4_i5 < 16; c4_i5++) {
      covrtSigUpdateFcnAssumingCovEnabled(chartInstance->c4_covrtInstance, 3U, (*
        chartInstance->c4_T_out)[c4_i5]);
    }
  }

  if (covrtIsSigCovEnabledFcn(chartInstance->c4_covrtInstance, 4U) != 0U) {
    for (c4_i6 = 0; c4_i6 < 16; c4_i6++) {
      covrtSigUpdateFcnAssumingCovEnabled(chartInstance->c4_covrtInstance, 4U, (*
        chartInstance->c4_U_out)[c4_i6]);
    }
  }

  covrtSigUpdateFcn(chartInstance->c4_covrtInstance, 5U, (real_T)
                    *chartInstance->c4_info);
}

static void ext_mode_exec_c4_vtg_sim_r24b(SFc4_vtg_sim_r24bInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c4_update_jit_animation_c4_vtg_sim_r24b
  (SFc4_vtg_sim_r24bInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c4_do_animation_call_c4_vtg_sim_r24b(SFc4_vtg_sim_r24bInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c4_vtg_sim_r24b
  (SFc4_vtg_sim_r24bInstanceStruct *chartInstance)
{
  const mxArray *c4_b_y = NULL;
  const mxArray *c4_c_y = NULL;
  const mxArray *c4_d_y = NULL;
  const mxArray *c4_st;
  const mxArray *c4_y = NULL;
  c4_st = NULL;
  c4_st = NULL;
  c4_y = NULL;
  sf_mex_assign(&c4_y, sf_mex_createcellmatrix(3, 1), false);
  c4_b_y = NULL;
  sf_mex_assign(&c4_b_y, sf_mex_create("y", *chartInstance->c4_T_out, 0, 0U, 1,
    0U, 2, 4, 4), false);
  sf_mex_setcell(c4_y, 0, c4_b_y);
  c4_c_y = NULL;
  sf_mex_assign(&c4_c_y, sf_mex_create("y", *chartInstance->c4_U_out, 0, 0U, 1,
    0U, 2, 4, 4), false);
  sf_mex_setcell(c4_y, 1, c4_c_y);
  c4_d_y = NULL;
  sf_mex_assign(&c4_d_y, sf_mex_create("y", chartInstance->c4_info, 6, 0U, 0, 0U,
    0), false);
  sf_mex_setcell(c4_y, 2, c4_d_y);
  sf_mex_assign(&c4_st, c4_y, false);
  return c4_st;
}

static void set_sim_state_c4_vtg_sim_r24b(SFc4_vtg_sim_r24bInstanceStruct
  *chartInstance, const mxArray *c4_st)
{
  const mxArray *c4_u;
  real_T c4_dv[16];
  real_T c4_dv1[16];
  int32_T c4_i;
  int32_T c4_i1;
  chartInstance->c4_doneDoubleBufferReInit = true;
  c4_u = sf_mex_dup(c4_st);
  c4_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c4_u, 0)),
                      "T_out", c4_dv);
  for (c4_i = 0; c4_i < 16; c4_i++) {
    (*chartInstance->c4_T_out)[c4_i] = c4_dv[c4_i];
  }

  c4_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c4_u, 1)),
                      "U_out", c4_dv1);
  for (c4_i1 = 0; c4_i1 < 16; c4_i1++) {
    (*chartInstance->c4_U_out)[c4_i1] = c4_dv1[c4_i1];
  }

  *chartInstance->c4_info = c4_c_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c4_u, 2)), "info");
  sf_mex_destroy(&c4_u);
  sf_mex_destroy(&c4_st);
}

const mxArray *sf_c4_vtg_sim_r24b_get_eml_resolved_functions_info(void)
{
  const mxArray *c4_nameCaptureInfo = NULL;
  c4_nameCaptureInfo = NULL;
  sf_mex_assign(&c4_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1, 0U, 2, 0, 1), false);
  return c4_nameCaptureInfo;
}

static void c4_emlrt_marshallIn(SFc4_vtg_sim_r24bInstanceStruct *chartInstance,
  const mxArray *c4_nullptr, const char_T *c4_identifier, real_T c4_y[16])
{
  emlrtMsgIdentifier c4_thisId;
  c4_thisId.fIdentifier = (const char_T *)c4_identifier;
  c4_thisId.fParent = NULL;
  c4_thisId.bParentIsCell = false;
  c4_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_nullptr), &c4_thisId, c4_y);
  sf_mex_destroy(&c4_nullptr);
}

static void c4_b_emlrt_marshallIn(SFc4_vtg_sim_r24bInstanceStruct *chartInstance,
  const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId, real_T c4_y[16])
{
  real_T c4_dv[16];
  int32_T c4_i;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), c4_dv, 1, 0, 0U, 1, 0U, 2, 4, 4);
  for (c4_i = 0; c4_i < 16; c4_i++) {
    c4_y[c4_i] = c4_dv[c4_i];
  }

  sf_mex_destroy(&c4_u);
}

static int32_T c4_c_emlrt_marshallIn(SFc4_vtg_sim_r24bInstanceStruct
  *chartInstance, const mxArray *c4_nullptr, const char_T *c4_identifier)
{
  emlrtMsgIdentifier c4_thisId;
  int32_T c4_y;
  c4_thisId.fIdentifier = (const char_T *)c4_identifier;
  c4_thisId.fParent = NULL;
  c4_thisId.bParentIsCell = false;
  c4_y = c4_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c4_nullptr), &c4_thisId);
  sf_mex_destroy(&c4_nullptr);
  return c4_y;
}

static int32_T c4_d_emlrt_marshallIn(SFc4_vtg_sim_r24bInstanceStruct
  *chartInstance, const mxArray *c4_u, const emlrtMsgIdentifier *c4_parentId)
{
  int32_T c4_i;
  int32_T c4_y;
  (void)chartInstance;
  sf_mex_import(c4_parentId, sf_mex_dup(c4_u), &c4_i, 1, 6, 0U, 0, 0U, 0);
  c4_y = c4_i;
  sf_mex_destroy(&c4_u);
  return c4_y;
}

static void init_dsm_address_info(SFc4_vtg_sim_r24bInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc4_vtg_sim_r24bInstanceStruct
  *chartInstance)
{
  chartInstance->c4_covrtInstance = (CovrtStateflowInstance *)
    sfrtGetCovrtInstance(chartInstance->S);
  chartInstance->c4_fEmlrtCtx = (void *)sfrtGetEmlrtCtx(chartInstance->S);
  chartInstance->c4_T = (real_T (*)[16])ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c4_T_out = (real_T (*)[16])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c4_U = (real_T (*)[16])ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c4_select = (boolean_T (*)[8])ssGetInputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c4_U_out = (real_T (*)[16])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c4_info = (int32_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 3);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* SFunction Glue Code */
void sf_c4_vtg_sim_r24b_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(4010045628U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1654172103U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1550587408U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3720749742U);
}

mxArray *sf_c4_vtg_sim_r24b_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c4_vtg_sim_r24b_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "hiddenFallbackType", "hiddenFallbackReason", "incompatibleSymbol" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 5, infoFields);
  mxArray *fallbackType = mxCreateString("late");
  mxArray *fallbackReason = mxCreateString("ir_function_calls");
  mxArray *hiddenFallbackType = mxCreateString("");
  mxArray *hiddenFallbackReason = mxCreateString("");
  mxArray *incompatibleSymbol = mxCreateString("ordschur_reorder");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], hiddenFallbackType);
  mxSetField(mxInfo, 0, infoFields[3], hiddenFallbackReason);
  mxSetField(mxInfo, 0, infoFields[4], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c4_vtg_sim_r24b_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = sf_mex_decode(
    "eNpjYPT0ZQACPiBuYGZgYAPSHEDMyAABrEh8ZiRxkHoNRvzqmdDUOzAg1LNgUc+PpF4Ayk9MSfH"
    "MS84pTUkNSCzJKAabs4EBv72MaPY2ELDXE81eEN/ZKia0OLWoOCY4IzEzNzHRNccpMTsnszgjxi"
    "U/uTQ3Na+kOMY9s8SjNCmmrCQ9PjE5Ob4oNTEnpjgztzQnMy87JrcyOS0zJ7WYhuHFh+ZuPkh4B"
    "eeXFiVDg2tIh9cHBjqGlxvEcpBYBYnh5UHAXiE0e0H8/KKU4uSM0qL48qLEgoLUIr1kiDwAmVRc"
    "ng=="
    );
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c4_vtg_sim_r24b(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  mxArray *mxVarInfo = sf_mex_decode(
    "eNpjYPT0ZQACPiBewcTAwAakOYCYiQECWKF8RiBmhtIQcRa4uAIQl1QWpILEi4uSPVOAdF5iLpi"
    "fWFrhmZeWDzbfggFhPhsW8xmRzOeEikPAB3vK9Is4oOtnwaKfFUm/AJQfEp9fWgINH1g4DZw/FM"
    "j2R+ig8ocS2B8GBPzBguIPFoZMYEKCuR8A704YwQ=="
    );
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c4_vtg_sim_r24b_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static const char* sf_get_instance_specialization(void)
{
  return "sgbqorP1A57KUrkGABcwWwG";
}

static void sf_opaque_initialize_c4_vtg_sim_r24b(void *chartInstanceVar)
{
  initialize_params_c4_vtg_sim_r24b((SFc4_vtg_sim_r24bInstanceStruct*)
    chartInstanceVar);
  initialize_c4_vtg_sim_r24b((SFc4_vtg_sim_r24bInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c4_vtg_sim_r24b(void *chartInstanceVar)
{
  enable_c4_vtg_sim_r24b((SFc4_vtg_sim_r24bInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c4_vtg_sim_r24b(void *chartInstanceVar)
{
  disable_c4_vtg_sim_r24b((SFc4_vtg_sim_r24bInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c4_vtg_sim_r24b(void *chartInstanceVar)
{
  sf_gateway_c4_vtg_sim_r24b((SFc4_vtg_sim_r24bInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c4_vtg_sim_r24b(SimStruct* S)
{
  return get_sim_state_c4_vtg_sim_r24b((SFc4_vtg_sim_r24bInstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c4_vtg_sim_r24b(SimStruct* S, const mxArray *
  st)
{
  set_sim_state_c4_vtg_sim_r24b((SFc4_vtg_sim_r24bInstanceStruct*)
    sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_cleanup_runtime_resources_c4_vtg_sim_r24b(void
  *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc4_vtg_sim_r24bInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_vtg_sim_r24b_optimization_info();
    }

    mdl_cleanup_runtime_resources_c4_vtg_sim_r24b
      ((SFc4_vtg_sim_r24bInstanceStruct*) chartInstanceVar);
    utFree(chartInstanceVar);
    if (ssGetUserData(S)!= NULL) {
      sf_free_ChartRunTimeInfo(S);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_mdl_start_c4_vtg_sim_r24b(void *chartInstanceVar)
{
  mdl_start_c4_vtg_sim_r24b((SFc4_vtg_sim_r24bInstanceStruct*) chartInstanceVar);
  if (chartInstanceVar) {
    sf_reset_warnings_ChartRunTimeInfo(((SFc4_vtg_sim_r24bInstanceStruct*)
      chartInstanceVar)->S);
  }
}

static void sf_opaque_mdl_terminate_c4_vtg_sim_r24b(void *chartInstanceVar)
{
  mdl_terminate_c4_vtg_sim_r24b((SFc4_vtg_sim_r24bInstanceStruct*)
    chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c4_vtg_sim_r24b(SimStruct *S)
{
  mdlProcessParamsCommon(S);
  if (sf_machine_global_initializer_called()) {
    initialize_params_c4_vtg_sim_r24b((SFc4_vtg_sim_r24bInstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

const char* sf_c4_vtg_sim_r24b_get_post_codegen_info(void)
{
  int i;
  const char* encStrCodegen [21] = {
    "eNrdWE9vG0UUH8du1KI2FAmpPSBRceKCRNNWcEA0jv8Ei4RY2G5RL9F493l35NkZZ/7YMRKfhSu",
    "fgCNfgSP9AJw4cYMjb9Zrx6yNs7uWmpSVNpu3u7957/32/RuTUuuE4LGH5+uHhOzi9TaeO2R23E",
    "rk0tI5u18hXyRy+x1CvJAq0xIDSfIfnvQhANGxgwG7yIkVNmpTRSNdQK+gEXwLWnJrmBT5jGdiA",
    "AqEhwuMpDK59GoWWc7EsGmF5zTrlyHzwk4oLfcPcUHqnwo+/S+9I2vaqLHOFHimCeCbUEkbhE1O",
    "g80sKDOpheANtY1yc6XBdOzIuapPLDdsxKFxAV5LaEORBX2Fvx1DDdTMRe4IYbozR8toxBkV2bk",
    "Oqe7ACKPDQG/k499Ta5C9jHpRX58JaqRilDciXnMRnhHb5mjnCYY1z82ziUwd+jYImAgcu8pGIN",
    "B/jJMMXA1qcgyKBnAqcuag865xEX/gRVxmz8GWC8tCOWij2VfRhbCx3sYYGdIF9TY9UaOc63zYr",
    "hwdwxh4rL9ODS2AnenPAdaa+V35giqXBTkzyQp2biHB1qTwWfYvPE6h4oL7DRbPDHAWuZACH2le",
    "mL5Y6KqYtNrIqIZpVD8+zqhvFdsSBtSAepC59inKNKDBcVzl1OszTfvcoZElE3uZeQUQhaFED6y",
    "oT6QaIsd5i+wlVy4T8qHBD6AOBuKC0cDofkG5zWhzpLHCufDoaaxY+fQi1uVPIbBHvRB8108Yhx",
    "PQbgGduT5jH6mit2NmpnXQnmKjrJlkNfjYSBxL3ekIemIo5EQ0lYw6yUSwIa4AsGpQJbAtHGJbU",
    "tMmGp/NagXnXRdZRcaziBpO+y42jkBgZ3G+uk5IPcyqhsDRDQ3aBtth32NrF5ppg+PUtBHngB/P",
    "ow9L+ebR9xL5ySKXWrqr8EtRbMMCJ6VqPx72oMsiiG90KM4UMzE5nN5PyaXeOzub9e7gf6WCOLI",
    "l7mAJV1nDz7tLuPuJ7D09G5vgDEeyM7X/tL+i/24GntfZncaRFdwlv/Prx0v40hq9ZOl6FU/lFZ",
    "7KpFQqrfB0L6WnksLtJlz9/MsPt//4MTy+99dv019fNX/fJi6+K+eL471E/mA+ly0613iluLt3v",
    "7oiDh6k4sDJOuifS9V+XH322dc9NTyqHnqTl5OjeL2fdjbbW07ZO7//CE+DhS2uk8pr+ckey8nU",
    "zmZ/t/7nS/buXsHHnaV4IuTP59vh3z9I49fxdSvFl5O7ZzLeOSzH7/X58aiwH70b5cdHB+m8Wud",
    "H5V9+VNzeW+69RfX6uvrDddqZpY+U3zCOvGHctv7l7Y9v+/ub6gBJvX//BvuRvhadk26aX69Jvj",
    "nmw0T+cvHbRS1k3F+ze0oe4wZnsO7p/yS+/87J33xuazj+kh9fXz2pCsqnuF2abUeT223lfvdbP",
    "FJA9fo96XX0oaz7lbup/HbyhAlfTvQnj/ef7W/T1/4BFOcKdQ==",
    ""
  };

  static char newstr [1477] = "";
  newstr[0] = '\0';
  for (i = 0; i < 21; i++) {
    strcat(newstr, encStrCodegen[i]);
  }

  return newstr;
}

static void mdlSetWorkWidths_c4_vtg_sim_r24b(SimStruct *S)
{
  const char* newstr = sf_c4_vtg_sim_r24b_get_post_codegen_info();
  sf_set_work_widths(S, newstr);
  ssSetChecksum0(S,(142458550U));
  ssSetChecksum1(S,(1281925098U));
  ssSetChecksum2(S,(2044196621U));
  ssSetChecksum3(S,(3829816015U));
}

static void mdlRTW_c4_vtg_sim_r24b(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlSetupRuntimeResources_c4_vtg_sim_r24b(SimStruct *S)
{
  SFc4_vtg_sim_r24bInstanceStruct *chartInstance;
  chartInstance = (SFc4_vtg_sim_r24bInstanceStruct *)utMalloc(sizeof
    (SFc4_vtg_sim_r24bInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc4_vtg_sim_r24bInstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c4_vtg_sim_r24b;
  chartInstance->chartInfo.initializeChart =
    sf_opaque_initialize_c4_vtg_sim_r24b;
  chartInstance->chartInfo.mdlStart = sf_opaque_mdl_start_c4_vtg_sim_r24b;
  chartInstance->chartInfo.mdlTerminate =
    sf_opaque_mdl_terminate_c4_vtg_sim_r24b;
  chartInstance->chartInfo.mdlCleanupRuntimeResources =
    sf_opaque_cleanup_runtime_resources_c4_vtg_sim_r24b;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c4_vtg_sim_r24b;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c4_vtg_sim_r24b;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c4_vtg_sim_r24b;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c4_vtg_sim_r24b;
  chartInstance->chartInfo.getSimStateInfo =
    sf_get_sim_state_info_c4_vtg_sim_r24b;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c4_vtg_sim_r24b;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c4_vtg_sim_r24b;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartEventFcn = NULL;
  chartInstance->S = S;
  chartInstance->chartInfo.dispatchToExportedFcn = NULL;
  sf_init_ChartRunTimeInfo(S, &(chartInstance->chartInfo), false, 0);
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  mdl_setup_runtime_resources_c4_vtg_sim_r24b(chartInstance);
}

void c4_vtg_sim_r24b_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_SETUP_RUNTIME_RESOURCES:
    mdlSetupRuntimeResources_c4_vtg_sim_r24b(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c4_vtg_sim_r24b(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c4_vtg_sim_r24b(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c4_vtg_sim_r24b_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
