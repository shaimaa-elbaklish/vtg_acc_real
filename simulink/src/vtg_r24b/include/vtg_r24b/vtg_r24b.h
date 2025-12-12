//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: vtg_r24b.h
//
// Code generated for Simulink model 'vtg_r24b'.
//
// Model version                  : 1.8
// Simulink Coder version         : 24.2 (R2024b) 21-Jun-2024
// C/C++ source code generated on : Thu Dec 11 18:45:22 2025
//
// Target selection: ert.tlc
// Embedded hardware selection: Generic->Unspecified (assume 32-bit Generic)
// Code generation objectives: Unspecified
// Validation result: Not run
//
#ifndef vtg_r24b_h_
#define vtg_r24b_h_
#include "rtwtypes.h"
#include "ordschur_wrapper.h"
#include "slros_initialize.h"
#include "vtg_r24b_types.h"

extern "C"
{

#include "rt_nonfinite.h"

}

extern "C"
{

#include "rtGetNaN.h"

}

#include <stddef.h>

// Block signals (default storage)
struct B_vtg_r24b_T {
  real_T TT[16];                       // '<S8>/MATLAB Function1'
  real_T U_out[16];                    // '<S8>/MATLAB Function3'
  creal_T b[4];
  real_T Csys[6];
  creal_T etemp[2];
  real_T Asys[4];
  real_T Bsys[4];
  real_T P[4];
  real_T Y[4];
  real_T At[4];
  real_T work[4];
  real_T v[3];
  real_T tau[3];
  real_T v_m[3];
  real_T wr[2];
  real_T wi[2];
  real_T work_c[2];
  real_T a21;
  real_T a22;
  real_T b_value;
  real_T b_value_k;
  real_T b_value_c;
  real_T Y_b;
  real_T Bsys_tmp;
  real_T a22_tmp;
  real_T b_anrm;
  real_T absxk;
  real_T smlnum;
  real_T tst;
  real_T aa;
  real_T bb;
  real_T h12;
  real_T h21;
  real_T tr;
  real_T h21s;
  real_T sum;
  real_T s_tmp;
  real_T temp;
  real_T p;
  real_T bcmax;
  real_T bcmis;
  real_T scale;
  real_T z;
  real_T a;
  real_T b_p;
  real_T beta1;
  real_T A;
  real_T tst_c;
  real_T aa_f;
  real_T bb_g;
  real_T h11;
  real_T h12_g;
  real_T h22;
  real_T h21s_m;
  real_T h;
  real_T s_tmp_n;
  real_T xnorm;
  real_T a_p;
  real_T scale_l;
  real_T absxk_j;
  real_T t;
  real_T anorm;
  real_T p_d;
  real_T rte;
  real_T r;
  real_T s;
  real_T b_gamma;
  real_T bb_gu;
  real_T oldc;
  real_T b_anorm;
  real_T cfromc;
  real_T ctoc;
  real_T cfrom1;
  real_T cto1;
  real_T c;
  real_T r_l;
  real_T g;
  real_T s_d;
  real_T b_scale;
  real_T absxk_d;
  real_T t_l;
  real_T y;
  real_T y_o;
  real_T tau_b;
  real_T xnorm_n;
  real_T alpha1_tmp;
  real_T scale_b;
  real_T absxk_l;
  real_T t_h;
  real_T cfromc_b;
  real_T ctoc_d;
  real_T cfrom1_e;
  real_T sm;
  real_T adf;
  SL_Bus_vtg_r24b_std_msgs_Float64 In1;// '<S11>/In1'
  SL_Bus_vtg_r24b_std_msgs_Float64 In1_j;// '<S10>/In1'
  SL_Bus_vtg_r24b_std_msgs_Float64 In1_m;// '<S9>/In1'
  SL_Bus_vtg_r24b_std_msgs_Float64 rtb_SourceBlock_o2_d_b;
  SL_Bus_vtg_r24b_std_msgs_Float64 BusAssignment;// '<Root>/Bus Assignment'
  SL_Bus_vtg_r24b_std_msgs_Float64 BusAssignment1;// '<Root>/Bus Assignment1'
  boolean_T SELECT[8];                 // '<S8>/MATLAB Function1'
  int32_T r2;
  int32_T i;
  int32_T P_tmp;
  int32_T k;
  int32_T i_j;
  int32_T ihi;
  int32_T At_tmp;
  int32_T i_f;
  int32_T istart;
  int32_T in;
  int32_T knt;
  int32_T lastv;
  int32_T g_i;
  int32_T c_k;
  int32_T ix;
  int32_T e;
  int32_T f;
  int32_T rowleft;
  int32_T im1n_tmp;
  int32_T work_tmp;
};

// Block states (default storage) for system '<Root>'
struct DW_vtg_r24b_T {
  ros_slros_internal_block_GetP_T obj; // '<Root>/Get Parameter3'
  ros_slros_internal_block_GetP_T obj_g;// '<Root>/Get Parameter2'
  ros_slros_internal_block_GetP_T obj_n;// '<Root>/Get Parameter1'
  ros_slros_internal_block_GetP_T obj_e;// '<Root>/Get Parameter'
  ros_slroscpp_internal_block_P_T obj_a;// '<S4>/SinkBlock'
  ros_slroscpp_internal_block_P_T obj_nf;// '<S3>/SinkBlock'
  ros_slroscpp_internal_block_S_T obj_j;// '<S7>/SourceBlock'
  ros_slroscpp_internal_block_S_T obj_gv;// '<S6>/SourceBlock'
  ros_slroscpp_internal_block_S_T obj_nfc;// '<S5>/SourceBlock'
};

// Real-time Model Data Structure
struct tag_RTM_vtg_r24b_T {
  const char_T * volatile errorStatus;
  const char_T* getErrorStatus() const;
  void setErrorStatus(const char_T* const volatile aErrorStatus);
};

// Block signals (default storage)
#ifdef __cplusplus

extern "C"
{

#endif

  extern struct B_vtg_r24b_T vtg_r24b_B;

#ifdef __cplusplus

}

#endif

// Block states (default storage)
extern struct DW_vtg_r24b_T vtg_r24b_DW;

#ifdef __cplusplus

extern "C"
{

#endif

  // Model entry point functions
  extern void vtg_r24b_initialize(void);
  extern void vtg_r24b_step(void);
  extern void vtg_r24b_terminate(void);

#ifdef __cplusplus

}

#endif

// Real-time Model object
#ifdef __cplusplus

extern "C"
{

#endif

  extern RT_MODEL_vtg_r24b_T *const vtg_r24b_M;

#ifdef __cplusplus

}

#endif

extern volatile boolean_T stopRequested;
extern volatile boolean_T runModel;

//-
//  The generated code includes comments that allow you to trace directly
//  back to the appropriate location in the model.  The basic format
//  is <system>/block_name, where system is the system number (uniquely
//  assigned by Simulink) and block_name is the name of the block.
//
//  Use the MATLAB hilite_system command to trace the generated code back
//  to the model.  For example,
//
//  hilite_system('<S3>')    - opens system 3
//  hilite_system('<S3>/Kp') - opens and selects block Kp which resides in S3
//
//  Here is the system hierarchy for this model
//
//  '<Root>' : 'vtg_r24b'
//  '<S1>'   : 'vtg_r24b/Blank Message'
//  '<S2>'   : 'vtg_r24b/Blank Message1'
//  '<S3>'   : 'vtg_r24b/Publish'
//  '<S4>'   : 'vtg_r24b/Publish1'
//  '<S5>'   : 'vtg_r24b/Subscribe'
//  '<S6>'   : 'vtg_r24b/Subscribe1'
//  '<S7>'   : 'vtg_r24b/Subscribe2'
//  '<S8>'   : 'vtg_r24b/myController1'
//  '<S9>'   : 'vtg_r24b/Subscribe/Enabled Subsystem'
//  '<S10>'  : 'vtg_r24b/Subscribe1/Enabled Subsystem'
//  '<S11>'  : 'vtg_r24b/Subscribe2/Enabled Subsystem'
//  '<S12>'  : 'vtg_r24b/myController1/MATLAB Function1'
//  '<S13>'  : 'vtg_r24b/myController1/MATLAB Function3'
//  '<S14>'  : 'vtg_r24b/myController1/MATLAB Function4'

#endif                                 // vtg_r24b_h_

//
// File trailer for generated code.
//
// [EOF]
//
