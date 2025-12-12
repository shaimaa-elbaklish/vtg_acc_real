#ifndef __c6_vtg_r24b_h__
#define __c6_vtg_r24b_h__

/* Forward Declarations */
#ifndef c6_typedef_c6_rtString
#define c6_typedef_c6_rtString

typedef struct c6_tag_wre2OYBVY3ybbisCmMcCuE c6_rtString;

#endif                                 /* c6_typedef_c6_rtString */

#ifndef c6_typedef_c6_b_rtString
#define c6_typedef_c6_b_rtString

typedef struct c6_tag_C0fd7vL5VXz4yRGkt4IZFG c6_b_rtString;

#endif                                 /* c6_typedef_c6_b_rtString */

#ifndef c6_typedef_c6_c_rtString
#define c6_typedef_c6_c_rtString

typedef struct c6_tag_KBWMfRQTe1jx7x607axb1 c6_c_rtString;

#endif                                 /* c6_typedef_c6_c_rtString */

/* Type Definitions */
#ifndef c6_struct_c6_tag_wre2OYBVY3ybbisCmMcCuE
#define c6_struct_c6_tag_wre2OYBVY3ybbisCmMcCuE

struct c6_tag_wre2OYBVY3ybbisCmMcCuE
{
  char_T Value[73];
};

#endif                                 /* c6_struct_c6_tag_wre2OYBVY3ybbisCmMcCuE */

#ifndef c6_typedef_c6_rtString
#define c6_typedef_c6_rtString

typedef struct c6_tag_wre2OYBVY3ybbisCmMcCuE c6_rtString;

#endif                                 /* c6_typedef_c6_rtString */

#ifndef c6_struct_c6_tag_C0fd7vL5VXz4yRGkt4IZFG
#define c6_struct_c6_tag_C0fd7vL5VXz4yRGkt4IZFG

struct c6_tag_C0fd7vL5VXz4yRGkt4IZFG
{
  char_T Value[73];
};

#endif                                 /* c6_struct_c6_tag_C0fd7vL5VXz4yRGkt4IZFG */

#ifndef c6_typedef_c6_b_rtString
#define c6_typedef_c6_b_rtString

typedef struct c6_tag_C0fd7vL5VXz4yRGkt4IZFG c6_b_rtString;

#endif                                 /* c6_typedef_c6_b_rtString */

#ifndef c6_struct_c6_tag_KBWMfRQTe1jx7x607axb1
#define c6_struct_c6_tag_KBWMfRQTe1jx7x607axb1

struct c6_tag_KBWMfRQTe1jx7x607axb1
{
  char_T Value[73];
};

#endif                                 /* c6_struct_c6_tag_KBWMfRQTe1jx7x607axb1 */

#ifndef c6_typedef_c6_c_rtString
#define c6_typedef_c6_c_rtString

typedef struct c6_tag_KBWMfRQTe1jx7x607axb1 c6_c_rtString;

#endif                                 /* c6_typedef_c6_c_rtString */

#ifndef typedef_SFc6_vtg_r24bInstanceStruct
#define typedef_SFc6_vtg_r24bInstanceStruct

typedef struct {
  SimStruct *S;
  ChartInfoStruct chartInfo;
  int32_T c6_sfEvent;
  boolean_T c6_doneDoubleBufferReInit;
  uint8_T c6_JITStateAnimation[1];
  uint8_T c6_JITTransitionAnimation[1];
  CovrtStateflowInstance *c6_covrtInstance;
  void *c6_fEmlrtCtx;
  real_T (*c6_T)[16];
  real_T (*c6_T_out)[16];
  real_T (*c6_U)[16];
  boolean_T (*c6_select)[8];
  real_T (*c6_U_out)[16];
  int32_T *c6_info;
} SFc6_vtg_r24bInstanceStruct;

#endif                                 /* typedef_SFc6_vtg_r24bInstanceStruct */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c6_vtg_r24b_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c6_vtg_r24b_get_check_sum(mxArray *plhs[]);
extern void c6_vtg_r24b_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
