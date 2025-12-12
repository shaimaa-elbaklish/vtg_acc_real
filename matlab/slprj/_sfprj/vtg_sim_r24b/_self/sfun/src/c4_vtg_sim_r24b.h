#ifndef __c4_vtg_sim_r24b_h__
#define __c4_vtg_sim_r24b_h__

/* Forward Declarations */
#ifndef c4_typedef_c4_rtString
#define c4_typedef_c4_rtString

typedef struct c4_tag_wre2OYBVY3ybbisCmMcCuE c4_rtString;

#endif                                 /* c4_typedef_c4_rtString */

#ifndef c4_typedef_c4_b_rtString
#define c4_typedef_c4_b_rtString

typedef struct c4_tag_C0fd7vL5VXz4yRGkt4IZFG c4_b_rtString;

#endif                                 /* c4_typedef_c4_b_rtString */

#ifndef c4_typedef_c4_c_rtString
#define c4_typedef_c4_c_rtString

typedef struct c4_tag_KBWMfRQTe1jx7x607axb1 c4_c_rtString;

#endif                                 /* c4_typedef_c4_c_rtString */

/* Type Definitions */
#ifndef c4_struct_c4_tag_wre2OYBVY3ybbisCmMcCuE
#define c4_struct_c4_tag_wre2OYBVY3ybbisCmMcCuE

struct c4_tag_wre2OYBVY3ybbisCmMcCuE
{
  char_T Value[73];
};

#endif                                 /* c4_struct_c4_tag_wre2OYBVY3ybbisCmMcCuE */

#ifndef c4_typedef_c4_rtString
#define c4_typedef_c4_rtString

typedef struct c4_tag_wre2OYBVY3ybbisCmMcCuE c4_rtString;

#endif                                 /* c4_typedef_c4_rtString */

#ifndef c4_struct_c4_tag_C0fd7vL5VXz4yRGkt4IZFG
#define c4_struct_c4_tag_C0fd7vL5VXz4yRGkt4IZFG

struct c4_tag_C0fd7vL5VXz4yRGkt4IZFG
{
  char_T Value[73];
};

#endif                                 /* c4_struct_c4_tag_C0fd7vL5VXz4yRGkt4IZFG */

#ifndef c4_typedef_c4_b_rtString
#define c4_typedef_c4_b_rtString

typedef struct c4_tag_C0fd7vL5VXz4yRGkt4IZFG c4_b_rtString;

#endif                                 /* c4_typedef_c4_b_rtString */

#ifndef c4_struct_c4_tag_KBWMfRQTe1jx7x607axb1
#define c4_struct_c4_tag_KBWMfRQTe1jx7x607axb1

struct c4_tag_KBWMfRQTe1jx7x607axb1
{
  char_T Value[73];
};

#endif                                 /* c4_struct_c4_tag_KBWMfRQTe1jx7x607axb1 */

#ifndef c4_typedef_c4_c_rtString
#define c4_typedef_c4_c_rtString

typedef struct c4_tag_KBWMfRQTe1jx7x607axb1 c4_c_rtString;

#endif                                 /* c4_typedef_c4_c_rtString */

#ifndef typedef_SFc4_vtg_sim_r24bInstanceStruct
#define typedef_SFc4_vtg_sim_r24bInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  int32_T c4_sfEvent;
  boolean_T c4_doneDoubleBufferReInit;
  uint8_T c4_JITStateAnimation[1];
  uint8_T c4_JITTransitionAnimation[1];
  CovrtStateflowInstance *c4_covrtInstance;
  void *c4_fEmlrtCtx;
  real_T (*c4_T)[16];
  real_T (*c4_T_out)[16];
  real_T (*c4_U)[16];
  boolean_T (*c4_select)[8];
  real_T (*c4_U_out)[16];
  int32_T *c4_info;
} SFc4_vtg_sim_r24bInstanceStruct;

#endif                                 /* typedef_SFc4_vtg_sim_r24bInstanceStruct */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c4_vtg_sim_r24b_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c4_vtg_sim_r24b_get_check_sum(mxArray *plhs[]);
extern void c4_vtg_sim_r24b_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
