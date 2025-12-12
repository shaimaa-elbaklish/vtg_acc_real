/* Include files */

#include "vtg_r24b_sfun.h"
#include "c6_vtg_r24b.h"
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
static void initialize_c6_vtg_r24b(SFc6_vtg_r24bInstanceStruct *chartInstance);
static void initialize_params_c6_vtg_r24b(SFc6_vtg_r24bInstanceStruct
  *chartInstance);
static void mdl_start_c6_vtg_r24b(SFc6_vtg_r24bInstanceStruct *chartInstance);
static void mdl_terminate_c6_vtg_r24b(SFc6_vtg_r24bInstanceStruct *chartInstance);
static void mdl_setup_runtime_resources_c6_vtg_r24b(SFc6_vtg_r24bInstanceStruct *
  chartInstance);
static void mdl_cleanup_runtime_resources_c6_vtg_r24b
  (SFc6_vtg_r24bInstanceStruct *chartInstance);
static void enable_c6_vtg_r24b(SFc6_vtg_r24bInstanceStruct *chartInstance);
static void disable_c6_vtg_r24b(SFc6_vtg_r24bInstanceStruct *chartInstance);
static void sf_gateway_c6_vtg_r24b(SFc6_vtg_r24bInstanceStruct *chartInstance);
static void ext_mode_exec_c6_vtg_r24b(SFc6_vtg_r24bInstanceStruct *chartInstance);
static void c6_update_jit_animation_c6_vtg_r24b(SFc6_vtg_r24bInstanceStruct
  *chartInstance);
static void c6_do_animation_call_c6_vtg_r24b(SFc6_vtg_r24bInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c6_vtg_r24b(SFc6_vtg_r24bInstanceStruct
  *chartInstance);
static void set_sim_state_c6_vtg_r24b(SFc6_vtg_r24bInstanceStruct *chartInstance,
  const mxArray *c6_st);
static void c6_emlrt_marshallIn(SFc6_vtg_r24bInstanceStruct *chartInstance,
  const mxArray *c6_nullptr, const char_T *c6_identifier, real_T c6_y[16]);
static void c6_b_emlrt_marshallIn(SFc6_vtg_r24bInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[16]);
static int32_T c6_c_emlrt_marshallIn(SFc6_vtg_r24bInstanceStruct *chartInstance,
  const mxArray *c6_nullptr, const char_T *c6_identifier);
static int32_T c6_d_emlrt_marshallIn(SFc6_vtg_r24bInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId);
static void init_dsm_address_info(SFc6_vtg_r24bInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc6_vtg_r24bInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c6_vtg_r24b(SFc6_vtg_r24bInstanceStruct *chartInstance)
{
  sim_mode_is_external(chartInstance->S);
  chartInstance->c6_doneDoubleBufferReInit = false;
  chartInstance->c6_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void initialize_params_c6_vtg_r24b(SFc6_vtg_r24bInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void mdl_start_c6_vtg_r24b(SFc6_vtg_r24bInstanceStruct *chartInstance)
{
  sim_mode_is_external(chartInstance->S);
}

static void mdl_terminate_c6_vtg_r24b(SFc6_vtg_r24bInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void mdl_setup_runtime_resources_c6_vtg_r24b(SFc6_vtg_r24bInstanceStruct *
  chartInstance)
{
  static const uint32_T c6_decisionTxtEndIdx = 0U;
  static const uint32_T c6_decisionTxtStartIdx = 0U;
  sfSetAnimationVectors(chartInstance->S, &chartInstance->c6_JITStateAnimation[0],
                        &chartInstance->c6_JITTransitionAnimation[0]);
  covrtCreateStateflowInstanceData(chartInstance->c6_covrtInstance, 1U, 0U, 1U,
    35U);
  covrtChartInitFcn(chartInstance->c6_covrtInstance, 0U, false, false, false);
  covrtStateInitFcn(chartInstance->c6_covrtInstance, 0U, 0U, false, false, false,
                    0U, &c6_decisionTxtStartIdx, &c6_decisionTxtEndIdx);
  covrtTransInitFcn(chartInstance->c6_covrtInstance, 0U, 0, NULL, NULL, 0U, NULL);
  covrtEmlInitFcn(chartInstance->c6_covrtInstance, "", 4U, 0U, 1U, 0U, 0U, 0U,
                  0U, 0U, 0U, 0U, 0U, 0U);
  covrtEmlFcnInitFcn(chartInstance->c6_covrtInstance, 4U, 0U, 0U, "c6_vtg_r24b",
                     0, -1, 581);
}

static void mdl_cleanup_runtime_resources_c6_vtg_r24b
  (SFc6_vtg_r24bInstanceStruct *chartInstance)
{
  covrtDeleteStateflowInstanceData(chartInstance->c6_covrtInstance);
}

static void enable_c6_vtg_r24b(SFc6_vtg_r24bInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c6_vtg_r24b(SFc6_vtg_r24bInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void sf_gateway_c6_vtg_r24b(SFc6_vtg_r24bInstanceStruct *chartInstance)
{
  int32_T c6_b_info;
  int32_T c6_i;
  int32_T c6_i1;
  int32_T c6_i2;
  int32_T c6_i3;
  int32_T c6_i4;
  int32_T c6_i5;
  int32_T c6_i6;
  if (covrtIsSigCovEnabledFcn(chartInstance->c6_covrtInstance, 2U) != 0U) {
    for (c6_i = 0; c6_i < 8; c6_i++) {
      covrtSigUpdateFcnAssumingCovEnabled(chartInstance->c6_covrtInstance, 2U,
        (real_T)(*chartInstance->c6_select)[c6_i]);
    }
  }

  if (covrtIsSigCovEnabledFcn(chartInstance->c6_covrtInstance, 1U) != 0U) {
    for (c6_i1 = 0; c6_i1 < 16; c6_i1++) {
      covrtSigUpdateFcnAssumingCovEnabled(chartInstance->c6_covrtInstance, 1U, (*
        chartInstance->c6_U)[c6_i1]);
    }
  }

  if (covrtIsSigCovEnabledFcn(chartInstance->c6_covrtInstance, 0U) != 0U) {
    for (c6_i2 = 0; c6_i2 < 16; c6_i2++) {
      covrtSigUpdateFcnAssumingCovEnabled(chartInstance->c6_covrtInstance, 0U, (*
        chartInstance->c6_T)[c6_i2]);
    }
  }

  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c6_JITTransitionAnimation[0] = 0U;
  chartInstance->c6_sfEvent = CALL_EVENT;
  covrtEmlFcnEval(chartInstance->c6_covrtInstance, 4U, 0, 0);
  for (c6_i3 = 0; c6_i3 < 16; c6_i3++) {
    (*chartInstance->c6_T_out)[c6_i3] = (*chartInstance->c6_T)[c6_i3];
  }

  for (c6_i4 = 0; c6_i4 < 16; c6_i4++) {
    (*chartInstance->c6_U_out)[c6_i4] = (*chartInstance->c6_U)[c6_i4];
  }

  c6_b_info = ordschur_reorder(4, &(*chartInstance->c6_T_out)[0],
    &(*chartInstance->c6_U_out)[0], &(*chartInstance->c6_select)[0]);
  *chartInstance->c6_info = c6_b_info;
  if (covrtIsSigCovEnabledFcn(chartInstance->c6_covrtInstance, 3U) != 0U) {
    for (c6_i5 = 0; c6_i5 < 16; c6_i5++) {
      covrtSigUpdateFcnAssumingCovEnabled(chartInstance->c6_covrtInstance, 3U, (*
        chartInstance->c6_T_out)[c6_i5]);
    }
  }

  if (covrtIsSigCovEnabledFcn(chartInstance->c6_covrtInstance, 4U) != 0U) {
    for (c6_i6 = 0; c6_i6 < 16; c6_i6++) {
      covrtSigUpdateFcnAssumingCovEnabled(chartInstance->c6_covrtInstance, 4U, (*
        chartInstance->c6_U_out)[c6_i6]);
    }
  }

  covrtSigUpdateFcn(chartInstance->c6_covrtInstance, 5U, (real_T)
                    *chartInstance->c6_info);
}

static void ext_mode_exec_c6_vtg_r24b(SFc6_vtg_r24bInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void c6_update_jit_animation_c6_vtg_r24b(SFc6_vtg_r24bInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static void c6_do_animation_call_c6_vtg_r24b(SFc6_vtg_r24bInstanceStruct
  *chartInstance)
{
  (void)chartInstance;
}

static const mxArray *get_sim_state_c6_vtg_r24b(SFc6_vtg_r24bInstanceStruct
  *chartInstance)
{
  const mxArray *c6_b_y = NULL;
  const mxArray *c6_c_y = NULL;
  const mxArray *c6_d_y = NULL;
  const mxArray *c6_st;
  const mxArray *c6_y = NULL;
  c6_st = NULL;
  c6_st = NULL;
  c6_y = NULL;
  sf_mex_assign(&c6_y, sf_mex_createcellmatrix(3, 1), false);
  c6_b_y = NULL;
  sf_mex_assign(&c6_b_y, sf_mex_create("y", *chartInstance->c6_T_out, 0, 0U, 1,
    0U, 2, 4, 4), false);
  sf_mex_setcell(c6_y, 0, c6_b_y);
  c6_c_y = NULL;
  sf_mex_assign(&c6_c_y, sf_mex_create("y", *chartInstance->c6_U_out, 0, 0U, 1,
    0U, 2, 4, 4), false);
  sf_mex_setcell(c6_y, 1, c6_c_y);
  c6_d_y = NULL;
  sf_mex_assign(&c6_d_y, sf_mex_create("y", chartInstance->c6_info, 6, 0U, 0, 0U,
    0), false);
  sf_mex_setcell(c6_y, 2, c6_d_y);
  sf_mex_assign(&c6_st, c6_y, false);
  return c6_st;
}

static void set_sim_state_c6_vtg_r24b(SFc6_vtg_r24bInstanceStruct *chartInstance,
  const mxArray *c6_st)
{
  const mxArray *c6_u;
  real_T c6_dv[16];
  real_T c6_dv1[16];
  int32_T c6_i;
  int32_T c6_i1;
  chartInstance->c6_doneDoubleBufferReInit = true;
  c6_u = sf_mex_dup(c6_st);
  c6_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c6_u, 0)),
                      "T_out", c6_dv);
  for (c6_i = 0; c6_i < 16; c6_i++) {
    (*chartInstance->c6_T_out)[c6_i] = c6_dv[c6_i];
  }

  c6_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c6_u, 1)),
                      "U_out", c6_dv1);
  for (c6_i1 = 0; c6_i1 < 16; c6_i1++) {
    (*chartInstance->c6_U_out)[c6_i1] = c6_dv1[c6_i1];
  }

  *chartInstance->c6_info = c6_c_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c6_u, 2)), "info");
  sf_mex_destroy(&c6_u);
  sf_mex_destroy(&c6_st);
}

const mxArray *sf_c6_vtg_r24b_get_eml_resolved_functions_info(void)
{
  const mxArray *c6_nameCaptureInfo = NULL;
  c6_nameCaptureInfo = NULL;
  sf_mex_assign(&c6_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1, 0U, 2, 0, 1), false);
  return c6_nameCaptureInfo;
}

static void c6_emlrt_marshallIn(SFc6_vtg_r24bInstanceStruct *chartInstance,
  const mxArray *c6_nullptr, const char_T *c6_identifier, real_T c6_y[16])
{
  emlrtMsgIdentifier c6_thisId;
  c6_thisId.fIdentifier = (const char_T *)c6_identifier;
  c6_thisId.fParent = NULL;
  c6_thisId.bParentIsCell = false;
  c6_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_nullptr), &c6_thisId, c6_y);
  sf_mex_destroy(&c6_nullptr);
}

static void c6_b_emlrt_marshallIn(SFc6_vtg_r24bInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId, real_T c6_y[16])
{
  real_T c6_dv[16];
  int32_T c6_i;
  (void)chartInstance;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), c6_dv, 1, 0, 0U, 1, 0U, 2, 4, 4);
  for (c6_i = 0; c6_i < 16; c6_i++) {
    c6_y[c6_i] = c6_dv[c6_i];
  }

  sf_mex_destroy(&c6_u);
}

static int32_T c6_c_emlrt_marshallIn(SFc6_vtg_r24bInstanceStruct *chartInstance,
  const mxArray *c6_nullptr, const char_T *c6_identifier)
{
  emlrtMsgIdentifier c6_thisId;
  int32_T c6_y;
  c6_thisId.fIdentifier = (const char_T *)c6_identifier;
  c6_thisId.fParent = NULL;
  c6_thisId.bParentIsCell = false;
  c6_y = c6_d_emlrt_marshallIn(chartInstance, sf_mex_dup(c6_nullptr), &c6_thisId);
  sf_mex_destroy(&c6_nullptr);
  return c6_y;
}

static int32_T c6_d_emlrt_marshallIn(SFc6_vtg_r24bInstanceStruct *chartInstance,
  const mxArray *c6_u, const emlrtMsgIdentifier *c6_parentId)
{
  int32_T c6_i;
  int32_T c6_y;
  (void)chartInstance;
  sf_mex_import(c6_parentId, sf_mex_dup(c6_u), &c6_i, 1, 6, 0U, 0, 0U, 0);
  c6_y = c6_i;
  sf_mex_destroy(&c6_u);
  return c6_y;
}

static void init_dsm_address_info(SFc6_vtg_r24bInstanceStruct *chartInstance)
{
  (void)chartInstance;
}

static void init_simulink_io_address(SFc6_vtg_r24bInstanceStruct *chartInstance)
{
  chartInstance->c6_covrtInstance = (CovrtStateflowInstance *)
    sfrtGetCovrtInstance(chartInstance->S);
  chartInstance->c6_fEmlrtCtx = (void *)sfrtGetEmlrtCtx(chartInstance->S);
  chartInstance->c6_T = (real_T (*)[16])ssGetInputPortSignal_wrapper
    (chartInstance->S, 0);
  chartInstance->c6_T_out = (real_T (*)[16])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c6_U = (real_T (*)[16])ssGetInputPortSignal_wrapper
    (chartInstance->S, 1);
  chartInstance->c6_select = (boolean_T (*)[8])ssGetInputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c6_U_out = (real_T (*)[16])ssGetOutputPortSignal_wrapper
    (chartInstance->S, 2);
  chartInstance->c6_info = (int32_T *)ssGetOutputPortSignal_wrapper
    (chartInstance->S, 3);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* SFunction Glue Code */
void sf_c6_vtg_r24b_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(573417550U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3754478699U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(1410053707U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(92103561U);
}

mxArray *sf_c6_vtg_r24b_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c6_vtg_r24b_jit_fallback_info(void)
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

mxArray *sf_c6_vtg_r24b_updateBuildInfo_args_info(void)
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

static const mxArray *sf_get_sim_state_info_c6_vtg_r24b(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  mxArray *mxVarInfo = sf_mex_decode(
    "eNpjYPT0ZQACPiBewcTAwAakOYCYiQECWKF8RiBmhtIQcRa4uAIQl1QWpILEi4uSPVOAdF5iLpi"
    "fWFrhmZeWDzbfggFhPhsW8xmRzOeEikPAB3vK9Is4oOtnwaKfFUm/AJQfEp9fWgINH1g4DZw/FM"
    "j2R+ig8ocS2B8GBPzBguIPFoZMYEKCuR8A704YwQ=="
    );
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c6_vtg_r24b_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static const char* sf_get_instance_specialization(void)
{
  return "sH7ekigJx9f62vzR54PhaMB";
}

static void sf_opaque_initialize_c6_vtg_r24b(void *chartInstanceVar)
{
  initialize_params_c6_vtg_r24b((SFc6_vtg_r24bInstanceStruct*) chartInstanceVar);
  initialize_c6_vtg_r24b((SFc6_vtg_r24bInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c6_vtg_r24b(void *chartInstanceVar)
{
  enable_c6_vtg_r24b((SFc6_vtg_r24bInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c6_vtg_r24b(void *chartInstanceVar)
{
  disable_c6_vtg_r24b((SFc6_vtg_r24bInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c6_vtg_r24b(void *chartInstanceVar)
{
  sf_gateway_c6_vtg_r24b((SFc6_vtg_r24bInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c6_vtg_r24b(SimStruct* S)
{
  return get_sim_state_c6_vtg_r24b((SFc6_vtg_r24bInstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c6_vtg_r24b(SimStruct* S, const mxArray *st)
{
  set_sim_state_c6_vtg_r24b((SFc6_vtg_r24bInstanceStruct*)
    sf_get_chart_instance_ptr(S), st);
}

static void sf_opaque_cleanup_runtime_resources_c6_vtg_r24b(void
  *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc6_vtg_r24bInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_vtg_r24b_optimization_info();
    }

    mdl_cleanup_runtime_resources_c6_vtg_r24b((SFc6_vtg_r24bInstanceStruct*)
      chartInstanceVar);
    utFree(chartInstanceVar);
    if (ssGetUserData(S)!= NULL) {
      sf_free_ChartRunTimeInfo(S);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_mdl_start_c6_vtg_r24b(void *chartInstanceVar)
{
  mdl_start_c6_vtg_r24b((SFc6_vtg_r24bInstanceStruct*) chartInstanceVar);
  if (chartInstanceVar) {
    sf_reset_warnings_ChartRunTimeInfo(((SFc6_vtg_r24bInstanceStruct*)
      chartInstanceVar)->S);
  }
}

static void sf_opaque_mdl_terminate_c6_vtg_r24b(void *chartInstanceVar)
{
  mdl_terminate_c6_vtg_r24b((SFc6_vtg_r24bInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c6_vtg_r24b(SimStruct *S)
{
  mdlProcessParamsCommon(S);
  if (sf_machine_global_initializer_called()) {
    initialize_params_c6_vtg_r24b((SFc6_vtg_r24bInstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

const char* sf_c6_vtg_r24b_get_post_codegen_info(void)
{
  int i;
  const char* encStrCodegen [21] = {
    "eNrdWFtv40QUdppstQtL2ZWQ2AckKp54QYLuBZC4tM1lm1VDo026IB6oJvaJPcp4xjuXXFbijX/",
    "BH+AnVUL8Bx55QeKM46TBCYntSNsullz32P7mnPP53CZOqdly8NjD8/KB4+zi9TaeO870uJXIpY",
    "Vzer/ifJXI7bccxw2I1E3eF07+wxUe+MA7pt+n45xYbsI2kSRUBfRyEsJzUIIZTQXPZzzlfZDAX",
    "VwgElLn0qtoaBjlg4bhrtWsvg+oG3QCYZh3jAsS74yzyX/pjYxuo8YaleDqBoCnAymMHzQY8dez",
    "IPWoGoA7UCbMzZUC3TGRdVW1DNM0YlAfg9vkShNkQW3wt6OJhqoe544QqjoztAgjRgnPznVAVAc",
    "ijA4N55GHf8+MRvYy6kV9PcqJFpISVg9Z1UZ4RmyboZ0tDGuWm2cd6hr0jO9T7lt2pQmBo/8YJx",
    "m46lfFECTx4YznzEHrXX0cf+B5XGbPwaYNy0I5aMLpV1GFsLHe+hAZUgX1NlxeJYypfNiuiE5hC",
    "CzWXyOaFMBO9ecAK0W9rnhBpM2CnJlkOH1pIMFWBfdo9i88TKHigvsdFs8McBrakAIPaZ6bPl9o",
    "U0wapUVYxTSqnZ5m1LeMbXINsk9cyFz7JKEK0OA4rnLq9agiPWbRyJKOvcy8AvDCUEf1Da+NhBw",
    "gx3mL7BVXNhPyocHzoQYa4oJRx+h+QZjJaHOosMLZ8DhXWLHy6UWszZ9CYJe4AXi2n1AGLVB2AZ",
    "W5PmMfOUJvh1RPaqBcSaOsmWQUeNhILEvdSQTnfMDFiDekCDvJRLAmrgCwahDJsS0cY1uSkwYan",
    "81qCS+7NrKKjGch0Yz0bGw8BY6dxfpqOyFxMavqHEc3NGgbbIe+wtbOFVUax6lJPc4BL55HH5Ty",
    "zaP3E/nhPJeaqivxSxFswxwnpaNePOxBl4YQ3+gQnCmmYnJYvZ86V3rv7KzXu4P/lQrinC1xhwu",
    "4ygp+3l7A3Utk98nFUPsX8uBRb6X+uxl4zoJzlnBX/M6uHy/gSyv0OgvXTTyVl3gqO6VSaYmnd1",
    "J6KincbsLV1+LvX34v/fzT5a8nT/efvfvHNnHxQzlfHO8l8gezuWzeuYZLxd2+e7IhDt5PxYGV1",
    "cnnMKD+s/GX/ScHw1fPHz9qB6R1HK/32856e8spe2f39/HUWNjiOindppfssaxMzHT2t+t/sWDv",
    "7gY+7izEk+P8+e12+PcO0/hVfN1K8WXl7oWIdw6L8Xt9fuwX9uP8Rvnx0WE6r1b5UfmXHxW79xZ",
    "7b1C9vq7+cJ12Zukj5deMc14zblv/8vbHN/39dXXASb1/7wb7kb4WnZNuml+XTr455sNE/mb+20",
    "U1oMxbsXtKHuMGp7/q6f8kvv/Kyd9sbqtb/pIfX398eMQJm+B2abodTW63pf3db/5IAlGr96TX0",
    "Yey7lfupvLbyiPKPTFSn3x28Phgm772D0v1BuI=",
    ""
  };

  static char newstr [1465] = "";
  newstr[0] = '\0';
  for (i = 0; i < 21; i++) {
    strcat(newstr, encStrCodegen[i]);
  }

  return newstr;
}

static void mdlSetWorkWidths_c6_vtg_r24b(SimStruct *S)
{
  const char* newstr = sf_c6_vtg_r24b_get_post_codegen_info();
  sf_set_work_widths(S, newstr);
  ssSetChecksum0(S,(2231201597U));
  ssSetChecksum1(S,(1585250779U));
  ssSetChecksum2(S,(1195940824U));
  ssSetChecksum3(S,(3708766752U));
}

static void mdlRTW_c6_vtg_r24b(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlSetupRuntimeResources_c6_vtg_r24b(SimStruct *S)
{
  SFc6_vtg_r24bInstanceStruct *chartInstance;
  chartInstance = (SFc6_vtg_r24bInstanceStruct *)utMalloc(sizeof
    (SFc6_vtg_r24bInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc6_vtg_r24bInstanceStruct));
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c6_vtg_r24b;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c6_vtg_r24b;
  chartInstance->chartInfo.mdlStart = sf_opaque_mdl_start_c6_vtg_r24b;
  chartInstance->chartInfo.mdlTerminate = sf_opaque_mdl_terminate_c6_vtg_r24b;
  chartInstance->chartInfo.mdlCleanupRuntimeResources =
    sf_opaque_cleanup_runtime_resources_c6_vtg_r24b;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c6_vtg_r24b;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c6_vtg_r24b;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c6_vtg_r24b;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c6_vtg_r24b;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c6_vtg_r24b;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c6_vtg_r24b;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c6_vtg_r24b;
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

  mdl_setup_runtime_resources_c6_vtg_r24b(chartInstance);
}

void c6_vtg_r24b_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_SETUP_RUNTIME_RESOURCES:
    mdlSetupRuntimeResources_c6_vtg_r24b(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c6_vtg_r24b(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c6_vtg_r24b(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c6_vtg_r24b_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
