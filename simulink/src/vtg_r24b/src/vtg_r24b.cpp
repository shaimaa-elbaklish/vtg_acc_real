//
// Academic License - for use in teaching, academic research, and meeting
// course requirements at degree granting institutions only.  Not for
// government, commercial, or other organizational use.
//
// File: vtg_r24b.cpp
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
#include "vtg_r24b.h"
#include "rtwtypes.h"
#include <math.h>

extern "C"
{

#include "rt_nonfinite.h"

}

#include <string.h>
#include "vtg_r24b_private.h"

// Block signals (default storage)
B_vtg_r24b_T vtg_r24b_B;

// Block states (default storage)
DW_vtg_r24b_T vtg_r24b_DW;

// Real-time model
RT_MODEL_vtg_r24b_T vtg_r24b_M_ = RT_MODEL_vtg_r24b_T();
RT_MODEL_vtg_r24b_T *const vtg_r24b_M = &vtg_r24b_M_;

// Forward declaration for local functions
static real_T vtg_r24b_xnrm2(int32_T n, const real_T x[16], int32_T ix0);
static real_T vtg_r24b_rt_hypotd_snf(real_T u0, real_T u1);
static void vtg_r24b_xzlarf(int32_T m, int32_T n, int32_T iv0, real_T tau,
  real_T C[16], int32_T ic0, real_T work[4]);
static real_T vtg_r24b_xnrm2_d(int32_T n, const real_T x[3]);
static real_T vtg_r24b_xzlarfg(int32_T n, real_T *alpha1, real_T x[3]);
static void vtg_r24b_xdlanv2(real_T *a, real_T *b, real_T *c, real_T *d, real_T *
  rt1r, real_T *rt1i, real_T *rt2r, real_T *rt2i, real_T *cs, real_T *sn);
static int32_T vtg_r24b_xhseqr(real_T h[16], real_T z[16]);
static void vtg_r24b_schur_l(real_T A[16], real_T V[16]);
static void vtg_r24b_xzlascl(real_T cfrom, real_T cto, int32_T m, int32_T n,
  real_T A[4], int32_T iA0, int32_T lda);
static real_T vtg_r24b_xnrm2_dm(int32_T n, const real_T x[4], int32_T ix0);
static void vtg_r24b_xzgebal(char_T job, real_T A[4], int32_T *ilo, int32_T *ihi,
  real_T scale[2]);
static void vtg_r24b_xzgehrd(real_T a[4], int32_T ilo, int32_T ihi);
static void vtg_r24b_xdlahqr(int32_T ilo, int32_T ihi, real_T h[4], int32_T
  *info, real_T wr[2], real_T wi[2]);
static void vtg_r24b_xzlascl_p(real_T cfrom, real_T cto, int32_T m, int32_T n,
  real_T A[2], int32_T iA0, int32_T lda);
static void vtg_r24b_xzlascl_p1(real_T cfrom, real_T cto, int32_T m, int32_T n,
  real_T *A);
static void vtg_r24b_xdlaev2(real_T a, real_T b, real_T c, real_T *rt1, real_T
  *rt2);
static void vtg_r24b_insertionsort(real_T x[2], int32_T xstart, int32_T xend);
static void vtg_r24b_xdlasrt(real_T d[2]);
static int32_T vtg_r24b_xdsterf(real_T d[2], real_T e);
static void vtg_r24b_ordeig(const real_T A[16], creal_T E[4]);
int32_T div_nzp_s32(int32_T numerator, int32_T denominator)
{
  uint32_T tempAbsQuotient;
  tempAbsQuotient = (numerator < 0 ? ~static_cast<uint32_T>(numerator) + 1U :
                     static_cast<uint32_T>(numerator)) / (denominator < 0 ? ~
    static_cast<uint32_T>(denominator) + 1U : static_cast<uint32_T>(denominator));
  return (numerator < 0) != (denominator < 0) ? -/*MW:OvOk*/
    (static_cast<int32_T>(tempAbsQuotient)) : static_cast<int32_T>
    (tempAbsQuotient);
}

// Function for MATLAB Function: '<S8>/MATLAB Function1'
static real_T vtg_r24b_xnrm2(int32_T n, const real_T x[16], int32_T ix0)
{
  real_T y;
  y = 0.0;
  if (n >= 1) {
    if (n == 1) {
      y = fabs(x[ix0 - 1]);
    } else {
      real_T scale;
      int32_T kend;
      scale = 3.3121686421112381E-170;
      kend = ix0 + n;
      for (int32_T k = ix0; k < kend; k++) {
        real_T absxk;
        absxk = fabs(x[k - 1]);
        if (absxk > scale) {
          real_T t;
          t = scale / absxk;
          y = y * t * t + 1.0;
          scale = absxk;
        } else {
          real_T t;
          t = absxk / scale;
          y += t * t;
        }
      }

      y = scale * sqrt(y);
    }
  }

  return y;
}

static real_T vtg_r24b_rt_hypotd_snf(real_T u0, real_T u1)
{
  real_T y;
  vtg_r24b_B.a = fabs(u0);
  vtg_r24b_B.b_p = fabs(u1);
  if (vtg_r24b_B.a < vtg_r24b_B.b_p) {
    vtg_r24b_B.a /= vtg_r24b_B.b_p;
    y = sqrt(vtg_r24b_B.a * vtg_r24b_B.a + 1.0) * vtg_r24b_B.b_p;
  } else if (vtg_r24b_B.a > vtg_r24b_B.b_p) {
    vtg_r24b_B.b_p /= vtg_r24b_B.a;
    y = sqrt(vtg_r24b_B.b_p * vtg_r24b_B.b_p + 1.0) * vtg_r24b_B.a;
  } else if (rtIsNaN(vtg_r24b_B.b_p)) {
    y = (rtNaN);
  } else {
    y = vtg_r24b_B.a * 1.4142135623730951;
  }

  return y;
}

// Function for MATLAB Function: '<S8>/MATLAB Function1'
static void vtg_r24b_xzlarf(int32_T m, int32_T n, int32_T iv0, real_T tau,
  real_T C[16], int32_T ic0, real_T work[4])
{
  int32_T b_ia;
  int32_T coltop;
  int32_T lastc;
  int32_T lastv;
  if (tau != 0.0) {
    boolean_T exitg2;
    lastv = m;
    lastc = iv0 + m;
    while ((lastv > 0) && (C[lastc - 2] == 0.0)) {
      lastv--;
      lastc--;
    }

    lastc = n;
    exitg2 = false;
    while ((!exitg2) && (lastc > 0)) {
      int32_T exitg1;
      coltop = ((lastc - 1) << 2) + ic0;
      b_ia = coltop;
      do {
        exitg1 = 0;
        if (b_ia <= (coltop + lastv) - 1) {
          if (C[b_ia - 1] != 0.0) {
            exitg1 = 1;
          } else {
            b_ia++;
          }
        } else {
          lastc--;
          exitg1 = 2;
        }
      } while (exitg1 == 0);

      if (exitg1 == 1) {
        exitg2 = true;
      }
    }

    lastc--;
  } else {
    lastv = 0;
    lastc = -1;
  }

  if (lastv > 0) {
    real_T c;
    int32_T d;
    int32_T jA;
    if (lastc + 1 != 0) {
      if (lastc >= 0) {
        memset(&work[0], 0, static_cast<uint32_T>(lastc + 1) * sizeof(real_T));
      }

      jA = (lastc << 2) + ic0;
      for (coltop = ic0; coltop <= jA; coltop += 4) {
        c = 0.0;
        d = (coltop + lastv) - 1;
        for (b_ia = coltop; b_ia <= d; b_ia++) {
          c += C[((iv0 + b_ia) - coltop) - 1] * C[b_ia - 1];
        }

        b_ia = (coltop - ic0) >> 2;
        work[b_ia] += c;
      }
    }

    if (!(-tau == 0.0)) {
      jA = ic0;
      for (coltop = 0; coltop <= lastc; coltop++) {
        c = work[coltop];
        if (c != 0.0) {
          c *= -tau;
          d = (lastv + jA) - 1;
          for (b_ia = jA; b_ia <= d; b_ia++) {
            C[b_ia - 1] += C[((iv0 + b_ia) - jA) - 1] * c;
          }
        }

        jA += 4;
      }
    }
  }
}

// Function for MATLAB Function: '<S8>/MATLAB Function1'
static real_T vtg_r24b_xnrm2_d(int32_T n, const real_T x[3])
{
  real_T y;
  y = 0.0;
  if (n >= 1) {
    if (n == 1) {
      y = fabs(x[1]);
    } else {
      vtg_r24b_B.scale_l = 3.3121686421112381E-170;
      for (int32_T k = 2; k <= n + 1; k++) {
        vtg_r24b_B.absxk_j = fabs(x[k - 1]);
        if (vtg_r24b_B.absxk_j > vtg_r24b_B.scale_l) {
          vtg_r24b_B.t = vtg_r24b_B.scale_l / vtg_r24b_B.absxk_j;
          y = y * vtg_r24b_B.t * vtg_r24b_B.t + 1.0;
          vtg_r24b_B.scale_l = vtg_r24b_B.absxk_j;
        } else {
          vtg_r24b_B.t = vtg_r24b_B.absxk_j / vtg_r24b_B.scale_l;
          y += vtg_r24b_B.t * vtg_r24b_B.t;
        }
      }

      y = vtg_r24b_B.scale_l * sqrt(y);
    }
  }

  return y;
}

// Function for MATLAB Function: '<S8>/MATLAB Function1'
static real_T vtg_r24b_xzlarfg(int32_T n, real_T *alpha1, real_T x[3])
{
  real_T tau;
  int32_T b_k;
  int32_T knt;
  tau = 0.0;
  if (n > 0) {
    vtg_r24b_B.xnorm = vtg_r24b_xnrm2_d(n - 1, x);
    if (vtg_r24b_B.xnorm != 0.0) {
      vtg_r24b_B.xnorm = vtg_r24b_rt_hypotd_snf(*alpha1, vtg_r24b_B.xnorm);
      if (*alpha1 >= 0.0) {
        vtg_r24b_B.xnorm = -vtg_r24b_B.xnorm;
      }

      if (fabs(vtg_r24b_B.xnorm) < 1.0020841800044864E-292) {
        knt = 0;
        do {
          knt++;
          for (b_k = 2; b_k <= n; b_k++) {
            x[b_k - 1] *= 9.9792015476736E+291;
          }

          vtg_r24b_B.xnorm *= 9.9792015476736E+291;
          *alpha1 *= 9.9792015476736E+291;
        } while ((fabs(vtg_r24b_B.xnorm) < 1.0020841800044864E-292) && (knt < 20));

        vtg_r24b_B.xnorm = vtg_r24b_rt_hypotd_snf(*alpha1, vtg_r24b_xnrm2_d(n -
          1, x));
        if (*alpha1 >= 0.0) {
          vtg_r24b_B.xnorm = -vtg_r24b_B.xnorm;
        }

        tau = (vtg_r24b_B.xnorm - *alpha1) / vtg_r24b_B.xnorm;
        vtg_r24b_B.a_p = 1.0 / (*alpha1 - vtg_r24b_B.xnorm);
        for (b_k = 2; b_k <= n; b_k++) {
          x[b_k - 1] *= vtg_r24b_B.a_p;
        }

        for (b_k = 0; b_k < knt; b_k++) {
          vtg_r24b_B.xnorm *= 1.0020841800044864E-292;
        }

        *alpha1 = vtg_r24b_B.xnorm;
      } else {
        tau = (vtg_r24b_B.xnorm - *alpha1) / vtg_r24b_B.xnorm;
        vtg_r24b_B.a_p = 1.0 / (*alpha1 - vtg_r24b_B.xnorm);
        for (knt = 2; knt <= n; knt++) {
          x[knt - 1] *= vtg_r24b_B.a_p;
        }

        *alpha1 = vtg_r24b_B.xnorm;
      }
    }
  }

  return tau;
}

// Function for MATLAB Function: '<S8>/MATLAB Function1'
static void vtg_r24b_xdlanv2(real_T *a, real_T *b, real_T *c, real_T *d, real_T *
  rt1r, real_T *rt1i, real_T *rt2r, real_T *rt2i, real_T *cs, real_T *sn)
{
  int32_T count;
  int32_T tmp;
  boolean_T tmp_0;
  if (*c == 0.0) {
    *cs = 1.0;
    *sn = 0.0;
  } else if (*b == 0.0) {
    *cs = 0.0;
    *sn = 1.0;
    vtg_r24b_B.temp = *d;
    *d = *a;
    *a = vtg_r24b_B.temp;
    *b = -*c;
    *c = 0.0;
  } else {
    vtg_r24b_B.temp = *a - *d;
    if ((vtg_r24b_B.temp == 0.0) && ((*b < 0.0) != (*c < 0.0))) {
      *cs = 1.0;
      *sn = 0.0;
    } else {
      vtg_r24b_B.p = 0.5 * vtg_r24b_B.temp;
      vtg_r24b_B.scale = fabs(*b);
      vtg_r24b_B.bcmis = fabs(*c);
      tmp_0 = rtIsNaN(vtg_r24b_B.bcmis);
      if ((vtg_r24b_B.scale >= vtg_r24b_B.bcmis) || tmp_0) {
        vtg_r24b_B.bcmax = vtg_r24b_B.scale;
      } else {
        vtg_r24b_B.bcmax = vtg_r24b_B.bcmis;
      }

      if ((vtg_r24b_B.scale <= vtg_r24b_B.bcmis) || tmp_0) {
        vtg_r24b_B.bcmis = vtg_r24b_B.scale;
      }

      if (!(*b < 0.0)) {
        count = 1;
      } else {
        count = -1;
      }

      if (!(*c < 0.0)) {
        tmp = 1;
      } else {
        tmp = -1;
      }

      vtg_r24b_B.bcmis = vtg_r24b_B.bcmis * static_cast<real_T>(count) *
        static_cast<real_T>(tmp);
      vtg_r24b_B.scale = fabs(vtg_r24b_B.p);
      if ((!(vtg_r24b_B.scale >= vtg_r24b_B.bcmax)) && (!rtIsNaN
           (vtg_r24b_B.bcmax))) {
        vtg_r24b_B.scale = vtg_r24b_B.bcmax;
      }

      vtg_r24b_B.z = vtg_r24b_B.p / vtg_r24b_B.scale * vtg_r24b_B.p +
        vtg_r24b_B.bcmax / vtg_r24b_B.scale * vtg_r24b_B.bcmis;
      if (vtg_r24b_B.z >= 8.8817841970012523E-16) {
        if (!(vtg_r24b_B.p < 0.0)) {
          vtg_r24b_B.temp = sqrt(vtg_r24b_B.scale) * sqrt(vtg_r24b_B.z);
        } else {
          vtg_r24b_B.temp = -(sqrt(vtg_r24b_B.scale) * sqrt(vtg_r24b_B.z));
        }

        vtg_r24b_B.z = vtg_r24b_B.p + vtg_r24b_B.temp;
        *a = *d + vtg_r24b_B.z;
        *d -= vtg_r24b_B.bcmax / vtg_r24b_B.z * vtg_r24b_B.bcmis;
        vtg_r24b_B.bcmax = vtg_r24b_rt_hypotd_snf(*c, vtg_r24b_B.z);
        *cs = vtg_r24b_B.z / vtg_r24b_B.bcmax;
        *sn = *c / vtg_r24b_B.bcmax;
        *b -= *c;
        *c = 0.0;
      } else {
        vtg_r24b_B.p = *b + *c;
        vtg_r24b_B.bcmax = fabs(vtg_r24b_B.temp);
        vtg_r24b_B.scale = fabs(vtg_r24b_B.p);
        if ((vtg_r24b_B.bcmax >= vtg_r24b_B.scale) || rtIsNaN(vtg_r24b_B.scale))
        {
          vtg_r24b_B.scale = vtg_r24b_B.bcmax;
        }

        count = 0;
        while ((vtg_r24b_B.scale >= 7.4428285367870146E+137) && (count <= 20)) {
          vtg_r24b_B.p *= 1.3435752215134178E-138;
          vtg_r24b_B.temp *= 1.3435752215134178E-138;
          vtg_r24b_B.bcmax = fabs(vtg_r24b_B.temp);
          vtg_r24b_B.scale = fabs(vtg_r24b_B.p);
          if ((vtg_r24b_B.bcmax >= vtg_r24b_B.scale) || rtIsNaN(vtg_r24b_B.scale))
          {
            vtg_r24b_B.scale = vtg_r24b_B.bcmax;
          }

          count++;
        }

        while ((vtg_r24b_B.scale <= 1.3435752215134178E-138) && (count <= 20)) {
          vtg_r24b_B.p *= 7.4428285367870146E+137;
          vtg_r24b_B.temp *= 7.4428285367870146E+137;
          vtg_r24b_B.bcmax = fabs(vtg_r24b_B.temp);
          vtg_r24b_B.scale = fabs(vtg_r24b_B.p);
          if ((vtg_r24b_B.bcmax >= vtg_r24b_B.scale) || rtIsNaN(vtg_r24b_B.scale))
          {
            vtg_r24b_B.scale = vtg_r24b_B.bcmax;
          }

          count++;
        }

        vtg_r24b_B.bcmax = vtg_r24b_rt_hypotd_snf(vtg_r24b_B.p, vtg_r24b_B.temp);
        *cs = sqrt((fabs(vtg_r24b_B.p) / vtg_r24b_B.bcmax + 1.0) * 0.5);
        if (!(vtg_r24b_B.p < 0.0)) {
          count = 1;
        } else {
          count = -1;
        }

        *sn = -(0.5 * vtg_r24b_B.temp / (vtg_r24b_B.bcmax * *cs)) * static_cast<
          real_T>(count);
        vtg_r24b_B.temp = *a * *cs + *b * *sn;
        vtg_r24b_B.p = -*a * *sn + *b * *cs;
        vtg_r24b_B.bcmax = *c * *cs + *d * *sn;
        vtg_r24b_B.scale = -*c * *sn + *d * *cs;
        *b = vtg_r24b_B.p * *cs + vtg_r24b_B.scale * *sn;
        *c = -vtg_r24b_B.temp * *sn + vtg_r24b_B.bcmax * *cs;
        vtg_r24b_B.temp = ((vtg_r24b_B.temp * *cs + vtg_r24b_B.bcmax * *sn) +
                           (-vtg_r24b_B.p * *sn + vtg_r24b_B.scale * *cs)) * 0.5;
        *a = vtg_r24b_B.temp;
        *d = vtg_r24b_B.temp;
        if (*c != 0.0) {
          if (*b != 0.0) {
            if ((*b < 0.0) == (*c < 0.0)) {
              vtg_r24b_B.bcmis = sqrt(fabs(*b));
              vtg_r24b_B.scale = sqrt(fabs(*c));
              if (!(*c < 0.0)) {
                vtg_r24b_B.p = vtg_r24b_B.bcmis * vtg_r24b_B.scale;
              } else {
                vtg_r24b_B.p = -(vtg_r24b_B.bcmis * vtg_r24b_B.scale);
              }

              vtg_r24b_B.bcmax = 1.0 / sqrt(fabs(*b + *c));
              *a = vtg_r24b_B.temp + vtg_r24b_B.p;
              *d = vtg_r24b_B.temp - vtg_r24b_B.p;
              *b -= *c;
              *c = 0.0;
              vtg_r24b_B.p = vtg_r24b_B.bcmis * vtg_r24b_B.bcmax;
              vtg_r24b_B.bcmax *= vtg_r24b_B.scale;
              vtg_r24b_B.temp = *cs * vtg_r24b_B.p - *sn * vtg_r24b_B.bcmax;
              *sn = *cs * vtg_r24b_B.bcmax + *sn * vtg_r24b_B.p;
              *cs = vtg_r24b_B.temp;
            }
          } else {
            *b = -*c;
            *c = 0.0;
            vtg_r24b_B.temp = *cs;
            *cs = -*sn;
            *sn = vtg_r24b_B.temp;
          }
        }
      }
    }
  }

  *rt1r = *a;
  *rt2r = *d;
  if (*c == 0.0) {
    *rt1i = 0.0;
    *rt2i = 0.0;
  } else {
    *rt1i = sqrt(fabs(*b)) * sqrt(fabs(*c));
    *rt2i = -*rt1i;
  }
}

// Function for MATLAB Function: '<S8>/MATLAB Function1'
static int32_T vtg_r24b_xhseqr(real_T h[16], real_T z[16])
{
  int32_T d_k;
  int32_T h_tmp;
  int32_T i;
  int32_T info;
  int32_T its;
  int32_T ix0;
  int32_T k;
  int32_T kdefl;
  int32_T l;
  int32_T m;
  int32_T n;
  int32_T nr;
  int32_T s_tmp;
  boolean_T converged;
  boolean_T exitg1;
  boolean_T exitg2;
  boolean_T exitg3;
  boolean_T tmp;
  info = 0;
  h[3] = 0.0;
  h[2] = 0.0;
  h[7] = 0.0;
  kdefl = 0;
  i = 3;
  exitg1 = false;
  while ((!exitg1) && (i + 1 >= 1)) {
    l = 1;
    converged = false;
    its = 0;
    exitg2 = false;
    while ((!exitg2) && (its <= 300)) {
      k = i;
      exitg3 = false;
      while ((!exitg3) && (k + 1 > l)) {
        d_k = ((k - 1) << 2) + k;
        vtg_r24b_B.bb_g = fabs(h[d_k]);
        if (vtg_r24b_B.bb_g <= 4.0083367200179456E-292) {
          exitg3 = true;
        } else {
          m = (k << 2) + k;
          vtg_r24b_B.aa_f = h[d_k - 1];
          vtg_r24b_B.tst_c = fabs(vtg_r24b_B.aa_f) + fabs(h[m]);
          if (vtg_r24b_B.tst_c == 0.0) {
            if (k - 1 >= 1) {
              vtg_r24b_B.tst_c = fabs(h[(((k - 2) << 2) + k) - 1]);
            }

            if (k + 2 <= 4) {
              vtg_r24b_B.tst_c += fabs(h[m + 1]);
            }
          }

          if (vtg_r24b_B.bb_g <= 2.2204460492503131E-16 * vtg_r24b_B.tst_c) {
            vtg_r24b_B.bb_g = fabs(vtg_r24b_B.aa_f - h[m]);
            vtg_r24b_B.tst_c = fabs(h[m]);
            tmp = rtIsNaN(vtg_r24b_B.bb_g);
            if ((vtg_r24b_B.tst_c >= vtg_r24b_B.bb_g) || tmp) {
              vtg_r24b_B.aa_f = vtg_r24b_B.tst_c;
            } else {
              vtg_r24b_B.aa_f = vtg_r24b_B.bb_g;
            }

            if ((vtg_r24b_B.tst_c <= vtg_r24b_B.bb_g) || tmp) {
              vtg_r24b_B.bb_g = vtg_r24b_B.tst_c;
            }

            vtg_r24b_B.tst_c = vtg_r24b_B.aa_f + vtg_r24b_B.bb_g;
            vtg_r24b_B.h11 = fabs(h[d_k]);
            vtg_r24b_B.h22 = fabs(h[m - 1]);
            vtg_r24b_B.aa_f = vtg_r24b_B.aa_f / vtg_r24b_B.tst_c *
              vtg_r24b_B.bb_g * 2.2204460492503131E-16;
            tmp = rtIsNaN(vtg_r24b_B.h22);
            if ((vtg_r24b_B.h11 <= vtg_r24b_B.h22) || tmp) {
              vtg_r24b_B.bb_g = vtg_r24b_B.h11;
            } else {
              vtg_r24b_B.bb_g = vtg_r24b_B.h22;
            }

            if ((vtg_r24b_B.h11 >= vtg_r24b_B.h22) || tmp) {
              vtg_r24b_B.h22 = vtg_r24b_B.h11;
            }

            if ((vtg_r24b_B.aa_f <= 4.0083367200179456E-292) || rtIsNaN
                (vtg_r24b_B.aa_f)) {
              vtg_r24b_B.aa_f = 4.0083367200179456E-292;
            }

            if (vtg_r24b_B.h22 / vtg_r24b_B.tst_c * vtg_r24b_B.bb_g <=
                vtg_r24b_B.aa_f) {
              exitg3 = true;
            } else {
              k--;
            }
          } else {
            k--;
          }
        }
      }

      l = k + 1;
      if (k + 1 > 1) {
        h[k + ((k - 1) << 2)] = 0.0;
      }

      if (k + 1 >= i) {
        converged = true;
        exitg2 = true;
      } else {
        kdefl++;
        if (kdefl - div_nzp_s32(kdefl, 20) * 20 == 0) {
          vtg_r24b_B.tst_c = fabs(h[(((i - 2) << 2) + i) - 1]) + fabs(h[((i - 1)
            << 2) + i]);
          vtg_r24b_B.h11 = h[(i << 2) + i] + 0.75 * vtg_r24b_B.tst_c;
          vtg_r24b_B.h12_g = -0.4375 * vtg_r24b_B.tst_c;
          vtg_r24b_B.bb_g = vtg_r24b_B.tst_c;
          vtg_r24b_B.h22 = vtg_r24b_B.h11;
        } else if (kdefl - div_nzp_s32(kdefl, 10) * 10 == 0) {
          s_tmp = (k << 2) + k;
          vtg_r24b_B.tst_c = fabs(h[(((k + 1) << 2) + k) + 2]) + fabs(h[s_tmp +
            1]);
          vtg_r24b_B.h11 = 0.75 * vtg_r24b_B.tst_c + h[s_tmp];
          vtg_r24b_B.h12_g = -0.4375 * vtg_r24b_B.tst_c;
          vtg_r24b_B.bb_g = vtg_r24b_B.tst_c;
          vtg_r24b_B.h22 = vtg_r24b_B.h11;
        } else {
          m = ((i - 1) << 2) + i;
          vtg_r24b_B.h11 = h[m - 1];
          vtg_r24b_B.bb_g = h[m];
          m = (i << 2) + i;
          vtg_r24b_B.h12_g = h[m - 1];
          vtg_r24b_B.h22 = h[m];
        }

        vtg_r24b_B.tst_c = ((fabs(vtg_r24b_B.h11) + fabs(vtg_r24b_B.h12_g)) +
                            fabs(vtg_r24b_B.bb_g)) + fabs(vtg_r24b_B.h22);
        if (vtg_r24b_B.tst_c == 0.0) {
          vtg_r24b_B.h11 = 0.0;
          vtg_r24b_B.h22 = 0.0;
          vtg_r24b_B.aa_f = 0.0;
          vtg_r24b_B.bb_g = 0.0;
        } else {
          vtg_r24b_B.h11 /= vtg_r24b_B.tst_c;
          vtg_r24b_B.h22 /= vtg_r24b_B.tst_c;
          vtg_r24b_B.aa_f = (vtg_r24b_B.h11 + vtg_r24b_B.h22) / 2.0;
          vtg_r24b_B.h11 = (vtg_r24b_B.h11 - vtg_r24b_B.aa_f) * (vtg_r24b_B.h22
            - vtg_r24b_B.aa_f) - vtg_r24b_B.h12_g / vtg_r24b_B.tst_c *
            (vtg_r24b_B.bb_g / vtg_r24b_B.tst_c);
          vtg_r24b_B.bb_g = sqrt(fabs(vtg_r24b_B.h11));
          if (vtg_r24b_B.h11 >= 0.0) {
            vtg_r24b_B.h11 = vtg_r24b_B.aa_f * vtg_r24b_B.tst_c;
            vtg_r24b_B.aa_f = vtg_r24b_B.h11;
            vtg_r24b_B.h22 = vtg_r24b_B.bb_g * vtg_r24b_B.tst_c;
            vtg_r24b_B.bb_g = -vtg_r24b_B.h22;
          } else {
            vtg_r24b_B.h11 = vtg_r24b_B.aa_f + vtg_r24b_B.bb_g;
            vtg_r24b_B.aa_f -= vtg_r24b_B.bb_g;
            if (fabs(vtg_r24b_B.h11 - vtg_r24b_B.h22) <= fabs(vtg_r24b_B.aa_f -
                 vtg_r24b_B.h22)) {
              vtg_r24b_B.h11 *= vtg_r24b_B.tst_c;
              vtg_r24b_B.aa_f = vtg_r24b_B.h11;
            } else {
              vtg_r24b_B.aa_f *= vtg_r24b_B.tst_c;
              vtg_r24b_B.h11 = vtg_r24b_B.aa_f;
            }

            vtg_r24b_B.h22 = 0.0;
            vtg_r24b_B.bb_g = 0.0;
          }
        }

        m = i - 1;
        exitg3 = false;
        while ((!exitg3) && (m >= k + 1)) {
          s_tmp = ((m - 1) << 2) + m;
          vtg_r24b_B.h12_g = h[s_tmp - 1];
          vtg_r24b_B.s_tmp_n = vtg_r24b_B.h12_g - vtg_r24b_B.aa_f;
          vtg_r24b_B.tst_c = (fabs(vtg_r24b_B.s_tmp_n) + fabs(vtg_r24b_B.bb_g))
            + fabs(h[s_tmp]);
          vtg_r24b_B.h21s_m = h[s_tmp] / vtg_r24b_B.tst_c;
          nr = (m << 2) + m;
          vtg_r24b_B.v_m[0] = (vtg_r24b_B.s_tmp_n / vtg_r24b_B.tst_c *
                               vtg_r24b_B.s_tmp_n + h[nr - 1] *
                               vtg_r24b_B.h21s_m) - vtg_r24b_B.bb_g /
            vtg_r24b_B.tst_c * vtg_r24b_B.h22;
          vtg_r24b_B.v_m[1] = (((vtg_r24b_B.h12_g + h[nr]) - vtg_r24b_B.h11) -
                               vtg_r24b_B.aa_f) * vtg_r24b_B.h21s_m;
          vtg_r24b_B.v_m[2] = h[nr + 1] * vtg_r24b_B.h21s_m;
          vtg_r24b_B.tst_c = (fabs(vtg_r24b_B.v_m[0]) + fabs(vtg_r24b_B.v_m[1]))
            + fabs(vtg_r24b_B.v_m[2]);
          vtg_r24b_B.v_m[0] /= vtg_r24b_B.tst_c;
          vtg_r24b_B.v_m[1] /= vtg_r24b_B.tst_c;
          vtg_r24b_B.v_m[2] /= vtg_r24b_B.tst_c;
          if (k + 1 == m) {
            exitg3 = true;
          } else {
            d_k = ((m - 2) << 2) + m;
            if (fabs(h[d_k - 1]) * (fabs(vtg_r24b_B.v_m[1]) + fabs
                                    (vtg_r24b_B.v_m[2])) <= ((fabs(h[d_k - 2]) +
                  fabs(h[s_tmp - 1])) + fabs(h[nr])) * (2.2204460492503131E-16 *
                 fabs(vtg_r24b_B.v_m[0]))) {
              exitg3 = true;
            } else {
              m--;
            }
          }
        }

        for (s_tmp = m; s_tmp <= i; s_tmp++) {
          nr = (i - s_tmp) + 2;
          if (nr >= 3) {
            nr = 3;
          }

          if (s_tmp > m) {
            ix0 = (((s_tmp - 2) << 2) + s_tmp) - 1;
            for (d_k = 0; d_k < nr; d_k++) {
              vtg_r24b_B.v_m[d_k] = h[ix0 + d_k];
            }
          }

          vtg_r24b_B.h11 = vtg_r24b_B.v_m[0];
          vtg_r24b_B.tst_c = vtg_r24b_xzlarfg(nr, &vtg_r24b_B.h11,
            vtg_r24b_B.v_m);
          if (s_tmp > m) {
            d_k = ((s_tmp - 2) << 2) + s_tmp;
            h[d_k - 1] = vtg_r24b_B.h11;
            h[d_k] = 0.0;
            if (s_tmp < i) {
              h[d_k + 1] = 0.0;
            }
          } else if (m > k + 1) {
            d_k = (((s_tmp - 2) << 2) + s_tmp) - 1;
            h[d_k] *= 1.0 - vtg_r24b_B.tst_c;
          }

          vtg_r24b_B.bb_g = vtg_r24b_B.v_m[1];
          vtg_r24b_B.h11 = vtg_r24b_B.tst_c * vtg_r24b_B.v_m[1];
          switch (nr) {
           case 3:
            vtg_r24b_B.h12_g = vtg_r24b_B.v_m[2];
            vtg_r24b_B.h22 = vtg_r24b_B.tst_c * vtg_r24b_B.v_m[2];
            for (nr = s_tmp; nr < 5; nr++) {
              d_k = ((nr - 1) << 2) + s_tmp;
              vtg_r24b_B.s_tmp_n = h[d_k - 1];
              vtg_r24b_B.h21s_m = h[d_k];
              vtg_r24b_B.h = h[d_k + 1];
              vtg_r24b_B.aa_f = (vtg_r24b_B.bb_g * vtg_r24b_B.h21s_m +
                                 vtg_r24b_B.s_tmp_n) + vtg_r24b_B.h12_g *
                vtg_r24b_B.h;
              h[d_k - 1] = vtg_r24b_B.s_tmp_n - vtg_r24b_B.aa_f *
                vtg_r24b_B.tst_c;
              h[d_k] = vtg_r24b_B.h21s_m - vtg_r24b_B.aa_f * vtg_r24b_B.h11;
              h[d_k + 1] = vtg_r24b_B.h - vtg_r24b_B.aa_f * vtg_r24b_B.h22;
            }

            if (s_tmp + 3 <= i + 1) {
              n = s_tmp + 3;
            } else {
              n = i + 1;
            }

            for (nr = 0; nr < n; nr++) {
              d_k = ((s_tmp - 1) << 2) + nr;
              vtg_r24b_B.s_tmp_n = h[d_k];
              ix0 = (s_tmp << 2) + nr;
              vtg_r24b_B.h21s_m = h[ix0];
              h_tmp = ((s_tmp + 1) << 2) + nr;
              vtg_r24b_B.h = h[h_tmp];
              vtg_r24b_B.aa_f = (vtg_r24b_B.bb_g * vtg_r24b_B.h21s_m +
                                 vtg_r24b_B.s_tmp_n) + vtg_r24b_B.h12_g *
                vtg_r24b_B.h;
              h[d_k] = vtg_r24b_B.s_tmp_n - vtg_r24b_B.aa_f * vtg_r24b_B.tst_c;
              h[ix0] = vtg_r24b_B.h21s_m - vtg_r24b_B.aa_f * vtg_r24b_B.h11;
              h[h_tmp] = vtg_r24b_B.h - vtg_r24b_B.aa_f * vtg_r24b_B.h22;
            }

            d_k = (s_tmp - 1) << 2;
            vtg_r24b_B.bb_g = z[d_k];
            nr = s_tmp << 2;
            vtg_r24b_B.h12_g = z[nr];
            ix0 = (s_tmp + 1) << 2;
            vtg_r24b_B.s_tmp_n = z[ix0];
            vtg_r24b_B.aa_f = (vtg_r24b_B.v_m[1] * vtg_r24b_B.h12_g +
                               vtg_r24b_B.bb_g) + vtg_r24b_B.v_m[2] *
              vtg_r24b_B.s_tmp_n;
            z[d_k] = vtg_r24b_B.bb_g - vtg_r24b_B.aa_f * vtg_r24b_B.tst_c;
            z[nr] = vtg_r24b_B.h12_g - vtg_r24b_B.aa_f * vtg_r24b_B.h11;
            z[ix0] = vtg_r24b_B.s_tmp_n - vtg_r24b_B.aa_f * vtg_r24b_B.h22;
            vtg_r24b_B.bb_g = z[d_k + 1];
            vtg_r24b_B.h12_g = z[nr + 1];
            vtg_r24b_B.s_tmp_n = z[ix0 + 1];
            vtg_r24b_B.aa_f = (vtg_r24b_B.v_m[1] * vtg_r24b_B.h12_g +
                               vtg_r24b_B.bb_g) + vtg_r24b_B.v_m[2] *
              vtg_r24b_B.s_tmp_n;
            z[d_k + 1] = vtg_r24b_B.bb_g - vtg_r24b_B.aa_f * vtg_r24b_B.tst_c;
            z[nr + 1] = vtg_r24b_B.h12_g - vtg_r24b_B.aa_f * vtg_r24b_B.h11;
            z[ix0 + 1] = vtg_r24b_B.s_tmp_n - vtg_r24b_B.aa_f * vtg_r24b_B.h22;
            vtg_r24b_B.bb_g = z[d_k + 2];
            vtg_r24b_B.h12_g = z[nr + 2];
            vtg_r24b_B.s_tmp_n = z[ix0 + 2];
            vtg_r24b_B.aa_f = (vtg_r24b_B.v_m[1] * vtg_r24b_B.h12_g +
                               vtg_r24b_B.bb_g) + vtg_r24b_B.v_m[2] *
              vtg_r24b_B.s_tmp_n;
            z[d_k + 2] = vtg_r24b_B.bb_g - vtg_r24b_B.aa_f * vtg_r24b_B.tst_c;
            z[nr + 2] = vtg_r24b_B.h12_g - vtg_r24b_B.aa_f * vtg_r24b_B.h11;
            z[ix0 + 2] = vtg_r24b_B.s_tmp_n - vtg_r24b_B.aa_f * vtg_r24b_B.h22;
            vtg_r24b_B.bb_g = z[d_k + 3];
            vtg_r24b_B.h12_g = z[nr + 3];
            vtg_r24b_B.s_tmp_n = z[ix0 + 3];
            vtg_r24b_B.aa_f = (vtg_r24b_B.v_m[1] * vtg_r24b_B.h12_g +
                               vtg_r24b_B.bb_g) + vtg_r24b_B.v_m[2] *
              vtg_r24b_B.s_tmp_n;
            z[d_k + 3] = vtg_r24b_B.bb_g - vtg_r24b_B.aa_f * vtg_r24b_B.tst_c;
            z[nr + 3] = vtg_r24b_B.h12_g - vtg_r24b_B.aa_f * vtg_r24b_B.h11;
            z[ix0 + 3] = vtg_r24b_B.s_tmp_n - vtg_r24b_B.aa_f * vtg_r24b_B.h22;
            break;

           case 2:
            for (nr = s_tmp; nr < 5; nr++) {
              d_k = ((nr - 1) << 2) + s_tmp;
              vtg_r24b_B.s_tmp_n = h[d_k - 1];
              vtg_r24b_B.h21s_m = h[d_k];
              vtg_r24b_B.aa_f = vtg_r24b_B.bb_g * vtg_r24b_B.h21s_m +
                vtg_r24b_B.s_tmp_n;
              h[d_k - 1] = vtg_r24b_B.s_tmp_n - vtg_r24b_B.aa_f *
                vtg_r24b_B.tst_c;
              h[d_k] = vtg_r24b_B.h21s_m - vtg_r24b_B.aa_f * vtg_r24b_B.h11;
            }

            for (nr = 0; nr <= i; nr++) {
              d_k = ((s_tmp - 1) << 2) + nr;
              vtg_r24b_B.s_tmp_n = h[d_k];
              ix0 = (s_tmp << 2) + nr;
              vtg_r24b_B.h21s_m = h[ix0];
              vtg_r24b_B.aa_f = vtg_r24b_B.bb_g * vtg_r24b_B.h21s_m +
                vtg_r24b_B.s_tmp_n;
              h[d_k] = vtg_r24b_B.s_tmp_n - vtg_r24b_B.aa_f * vtg_r24b_B.tst_c;
              h[ix0] = vtg_r24b_B.h21s_m - vtg_r24b_B.aa_f * vtg_r24b_B.h11;
            }

            d_k = (s_tmp - 1) << 2;
            vtg_r24b_B.bb_g = z[d_k];
            nr = s_tmp << 2;
            vtg_r24b_B.h12_g = z[nr];
            vtg_r24b_B.aa_f = vtg_r24b_B.v_m[1] * vtg_r24b_B.h12_g +
              vtg_r24b_B.bb_g;
            z[d_k] = vtg_r24b_B.bb_g - vtg_r24b_B.aa_f * vtg_r24b_B.tst_c;
            z[nr] = vtg_r24b_B.h12_g - vtg_r24b_B.aa_f * vtg_r24b_B.h11;
            vtg_r24b_B.bb_g = z[d_k + 1];
            vtg_r24b_B.h12_g = z[nr + 1];
            vtg_r24b_B.aa_f = vtg_r24b_B.v_m[1] * vtg_r24b_B.h12_g +
              vtg_r24b_B.bb_g;
            z[d_k + 1] = vtg_r24b_B.bb_g - vtg_r24b_B.aa_f * vtg_r24b_B.tst_c;
            z[nr + 1] = vtg_r24b_B.h12_g - vtg_r24b_B.aa_f * vtg_r24b_B.h11;
            vtg_r24b_B.bb_g = z[d_k + 2];
            vtg_r24b_B.h12_g = z[nr + 2];
            vtg_r24b_B.aa_f = vtg_r24b_B.v_m[1] * vtg_r24b_B.h12_g +
              vtg_r24b_B.bb_g;
            z[d_k + 2] = vtg_r24b_B.bb_g - vtg_r24b_B.aa_f * vtg_r24b_B.tst_c;
            z[nr + 2] = vtg_r24b_B.h12_g - vtg_r24b_B.aa_f * vtg_r24b_B.h11;
            vtg_r24b_B.bb_g = z[d_k + 3];
            vtg_r24b_B.h12_g = z[nr + 3];
            vtg_r24b_B.aa_f = vtg_r24b_B.v_m[1] * vtg_r24b_B.h12_g +
              vtg_r24b_B.bb_g;
            z[d_k + 3] = vtg_r24b_B.bb_g - vtg_r24b_B.aa_f * vtg_r24b_B.tst_c;
            z[nr + 3] = vtg_r24b_B.h12_g - vtg_r24b_B.aa_f * vtg_r24b_B.h11;
            break;
          }
        }

        its++;
      }
    }

    if (!converged) {
      info = i + 1;
      exitg1 = true;
    } else {
      if ((i + 1 != l) && (l == i)) {
        kdefl = i << 2;
        k = kdefl + i;
        vtg_r24b_B.h22 = h[k - 1];
        its = (i - 1) << 2;
        d_k = its + i;
        vtg_r24b_B.aa_f = h[d_k];
        vtg_r24b_B.bb_g = h[k];
        vtg_r24b_xdlanv2(&h[d_k - 1], &vtg_r24b_B.h22, &vtg_r24b_B.aa_f,
                         &vtg_r24b_B.bb_g, &vtg_r24b_B.h12_g,
                         &vtg_r24b_B.s_tmp_n, &vtg_r24b_B.h21s_m, &vtg_r24b_B.h,
                         &vtg_r24b_B.tst_c, &vtg_r24b_B.h11);
        h[k - 1] = vtg_r24b_B.h22;
        h[d_k] = vtg_r24b_B.aa_f;
        h[k] = vtg_r24b_B.bb_g;
        if (i + 1 < 4) {
          m = 3 - i;
          s_tmp = ((i + 1) << 2) + i;
          for (k = 0; k < m; k++) {
            nr = k << 2;
            d_k = nr + s_tmp;
            vtg_r24b_B.h22 = h[d_k];
            nr = (nr + s_tmp) - 1;
            vtg_r24b_B.aa_f = h[nr];
            h[d_k] = vtg_r24b_B.h22 * vtg_r24b_B.tst_c - vtg_r24b_B.aa_f *
              vtg_r24b_B.h11;
            h[nr] = vtg_r24b_B.aa_f * vtg_r24b_B.tst_c + vtg_r24b_B.h22 *
              vtg_r24b_B.h11;
          }
        }

        k = i - 2;
        if (i - 1 >= 1) {
          for (i = 0; i <= k; i++) {
            m = kdefl + i;
            vtg_r24b_B.h22 = h[m];
            s_tmp = its + i;
            vtg_r24b_B.aa_f = h[s_tmp];
            h[m] = vtg_r24b_B.h22 * vtg_r24b_B.tst_c - vtg_r24b_B.aa_f *
              vtg_r24b_B.h11;
            h[s_tmp] = vtg_r24b_B.aa_f * vtg_r24b_B.tst_c + vtg_r24b_B.h22 *
              vtg_r24b_B.h11;
          }
        }

        vtg_r24b_B.h22 = vtg_r24b_B.tst_c * z[its] + vtg_r24b_B.h11 * z[kdefl];
        z[kdefl] = vtg_r24b_B.tst_c * z[kdefl] - vtg_r24b_B.h11 * z[its];
        z[its] = vtg_r24b_B.h22;
        vtg_r24b_B.h22 = z[kdefl + 1];
        vtg_r24b_B.aa_f = z[its + 1];
        z[kdefl + 1] = vtg_r24b_B.h22 * vtg_r24b_B.tst_c - vtg_r24b_B.aa_f *
          vtg_r24b_B.h11;
        z[its + 1] = vtg_r24b_B.aa_f * vtg_r24b_B.tst_c + vtg_r24b_B.h22 *
          vtg_r24b_B.h11;
        vtg_r24b_B.h22 = z[kdefl + 2];
        vtg_r24b_B.aa_f = z[its + 2];
        z[kdefl + 2] = vtg_r24b_B.h22 * vtg_r24b_B.tst_c - vtg_r24b_B.aa_f *
          vtg_r24b_B.h11;
        z[its + 2] = vtg_r24b_B.aa_f * vtg_r24b_B.tst_c + vtg_r24b_B.h22 *
          vtg_r24b_B.h11;
        vtg_r24b_B.h22 = z[kdefl + 3];
        vtg_r24b_B.aa_f = z[its + 3];
        z[kdefl + 3] = vtg_r24b_B.h22 * vtg_r24b_B.tst_c - vtg_r24b_B.aa_f *
          vtg_r24b_B.h11;
        z[its + 3] = vtg_r24b_B.aa_f * vtg_r24b_B.tst_c + vtg_r24b_B.h22 *
          vtg_r24b_B.h11;
      }

      kdefl = 0;
      i = l - 2;
    }
  }

  for (l = 0; l < 2; l++) {
    for (i = l + 3; i < 5; i++) {
      h[(i + (l << 2)) - 1] = 0.0;
    }
  }

  return info;
}

// Function for MATLAB Function: '<S8>/MATLAB Function1'
static void vtg_r24b_schur_l(real_T A[16], real_T V[16])
{
  int32_T exitg1;
  boolean_T exitg2;
  boolean_T p;
  p = true;
  for (vtg_r24b_B.g_i = 0; vtg_r24b_B.g_i < 16; vtg_r24b_B.g_i++) {
    if (p) {
      vtg_r24b_B.A = A[vtg_r24b_B.g_i];
      if (rtIsInf(vtg_r24b_B.A) || rtIsNaN(vtg_r24b_B.A)) {
        p = false;
      }
    }
  }

  if (!p) {
    for (vtg_r24b_B.lastv = 0; vtg_r24b_B.lastv < 16; vtg_r24b_B.lastv++) {
      V[vtg_r24b_B.lastv] = (rtNaN);
    }

    vtg_r24b_B.istart = 2;
    for (vtg_r24b_B.g_i = 0; vtg_r24b_B.g_i < 3; vtg_r24b_B.g_i++) {
      if (vtg_r24b_B.istart <= 4) {
        memset(&V[((vtg_r24b_B.g_i << 2) + vtg_r24b_B.istart) + -1], 0,
               static_cast<uint32_T>(-vtg_r24b_B.istart + 5) * sizeof(real_T));
      }

      vtg_r24b_B.istart++;
    }

    for (vtg_r24b_B.lastv = 0; vtg_r24b_B.lastv < 16; vtg_r24b_B.lastv++) {
      A[vtg_r24b_B.lastv] = (rtNaN);
    }
  } else {
    vtg_r24b_B.work[0] = 0.0;
    vtg_r24b_B.work[1] = 0.0;
    vtg_r24b_B.work[2] = 0.0;
    vtg_r24b_B.work[3] = 0.0;
    for (vtg_r24b_B.g_i = 0; vtg_r24b_B.g_i < 3; vtg_r24b_B.g_i++) {
      vtg_r24b_B.im1n_tmp = vtg_r24b_B.g_i << 2;
      vtg_r24b_B.in = (vtg_r24b_B.g_i + 1) << 2;
      vtg_r24b_B.istart = (vtg_r24b_B.im1n_tmp + vtg_r24b_B.g_i) + 1;
      vtg_r24b_B.A = A[vtg_r24b_B.istart];
      if (vtg_r24b_B.g_i + 3 <= 4) {
        vtg_r24b_B.lastv = vtg_r24b_B.g_i + 3;
      } else {
        vtg_r24b_B.lastv = 4;
      }

      vtg_r24b_B.lastv += vtg_r24b_B.im1n_tmp;
      vtg_r24b_B.tau[vtg_r24b_B.g_i] = 0.0;
      vtg_r24b_B.beta1 = vtg_r24b_xnrm2(2 - vtg_r24b_B.g_i, A, vtg_r24b_B.lastv);
      if (vtg_r24b_B.beta1 != 0.0) {
        vtg_r24b_B.beta1 = vtg_r24b_rt_hypotd_snf(vtg_r24b_B.A, vtg_r24b_B.beta1);
        if (vtg_r24b_B.A >= 0.0) {
          vtg_r24b_B.beta1 = -vtg_r24b_B.beta1;
        }

        if (fabs(vtg_r24b_B.beta1) < 1.0020841800044864E-292) {
          vtg_r24b_B.knt = 0;
          vtg_r24b_B.rowleft = (vtg_r24b_B.lastv - vtg_r24b_B.g_i) + 1;
          do {
            vtg_r24b_B.knt++;
            for (vtg_r24b_B.c_k = vtg_r24b_B.lastv; vtg_r24b_B.c_k <=
                 vtg_r24b_B.rowleft; vtg_r24b_B.c_k++) {
              A[vtg_r24b_B.c_k - 1] *= 9.9792015476736E+291;
            }

            vtg_r24b_B.beta1 *= 9.9792015476736E+291;
            vtg_r24b_B.A *= 9.9792015476736E+291;
          } while ((fabs(vtg_r24b_B.beta1) < 1.0020841800044864E-292) &&
                   (vtg_r24b_B.knt < 20));

          vtg_r24b_B.beta1 = vtg_r24b_rt_hypotd_snf(vtg_r24b_B.A, vtg_r24b_xnrm2
            (2 - vtg_r24b_B.g_i, A, vtg_r24b_B.lastv));
          if (vtg_r24b_B.A >= 0.0) {
            vtg_r24b_B.beta1 = -vtg_r24b_B.beta1;
          }

          vtg_r24b_B.tau[vtg_r24b_B.g_i] = (vtg_r24b_B.beta1 - vtg_r24b_B.A) /
            vtg_r24b_B.beta1;
          vtg_r24b_B.A = 1.0 / (vtg_r24b_B.A - vtg_r24b_B.beta1);
          for (vtg_r24b_B.c_k = vtg_r24b_B.lastv; vtg_r24b_B.c_k <=
               vtg_r24b_B.rowleft; vtg_r24b_B.c_k++) {
            A[vtg_r24b_B.c_k - 1] *= vtg_r24b_B.A;
          }

          for (vtg_r24b_B.lastv = 0; vtg_r24b_B.lastv < vtg_r24b_B.knt;
               vtg_r24b_B.lastv++) {
            vtg_r24b_B.beta1 *= 1.0020841800044864E-292;
          }

          vtg_r24b_B.A = vtg_r24b_B.beta1;
        } else {
          vtg_r24b_B.tau[vtg_r24b_B.g_i] = (vtg_r24b_B.beta1 - vtg_r24b_B.A) /
            vtg_r24b_B.beta1;
          vtg_r24b_B.A = 1.0 / (vtg_r24b_B.A - vtg_r24b_B.beta1);
          vtg_r24b_B.rowleft = (vtg_r24b_B.lastv - vtg_r24b_B.g_i) + 1;
          for (vtg_r24b_B.knt = vtg_r24b_B.lastv; vtg_r24b_B.knt <=
               vtg_r24b_B.rowleft; vtg_r24b_B.knt++) {
            A[vtg_r24b_B.knt - 1] *= vtg_r24b_B.A;
          }

          vtg_r24b_B.A = vtg_r24b_B.beta1;
        }
      }

      A[vtg_r24b_B.istart] = 1.0;
      vtg_r24b_B.im1n_tmp = (vtg_r24b_B.g_i + vtg_r24b_B.im1n_tmp) + 2;
      if (vtg_r24b_B.tau[vtg_r24b_B.g_i] != 0.0) {
        vtg_r24b_B.lastv = 2 - vtg_r24b_B.g_i;
        vtg_r24b_B.knt = (vtg_r24b_B.im1n_tmp - vtg_r24b_B.g_i) + 1;
        while ((vtg_r24b_B.lastv + 1 > 0) && (A[vtg_r24b_B.knt] == 0.0)) {
          vtg_r24b_B.lastv--;
          vtg_r24b_B.knt--;
        }

        vtg_r24b_B.knt = 4;
        exitg2 = false;
        while ((!exitg2) && (vtg_r24b_B.knt > 0)) {
          vtg_r24b_B.rowleft = vtg_r24b_B.in + vtg_r24b_B.knt;
          vtg_r24b_B.c_k = vtg_r24b_B.rowleft;
          do {
            exitg1 = 0;
            if (vtg_r24b_B.c_k <= (vtg_r24b_B.lastv << 2) + vtg_r24b_B.rowleft)
            {
              if (A[vtg_r24b_B.c_k - 1] != 0.0) {
                exitg1 = 1;
              } else {
                vtg_r24b_B.c_k += 4;
              }
            } else {
              vtg_r24b_B.knt--;
              exitg1 = 2;
            }
          } while (exitg1 == 0);

          if (exitg1 == 1) {
            exitg2 = true;
          }
        }
      } else {
        vtg_r24b_B.lastv = -1;
        vtg_r24b_B.knt = 0;
      }

      if (vtg_r24b_B.lastv + 1 > 0) {
        if (vtg_r24b_B.knt != 0) {
          memset(&vtg_r24b_B.work[0], 0, static_cast<uint32_T>(vtg_r24b_B.knt) *
                 sizeof(real_T));
          vtg_r24b_B.ix = vtg_r24b_B.im1n_tmp - 1;
          vtg_r24b_B.e = ((vtg_r24b_B.lastv << 2) + vtg_r24b_B.in) + 1;
          for (vtg_r24b_B.rowleft = vtg_r24b_B.in + 1; vtg_r24b_B.rowleft <=
               vtg_r24b_B.e; vtg_r24b_B.rowleft += 4) {
            vtg_r24b_B.f = (vtg_r24b_B.rowleft + vtg_r24b_B.knt) - 1;
            for (vtg_r24b_B.c_k = vtg_r24b_B.rowleft; vtg_r24b_B.c_k <=
                 vtg_r24b_B.f; vtg_r24b_B.c_k++) {
              vtg_r24b_B.work_tmp = vtg_r24b_B.c_k - vtg_r24b_B.rowleft;
              vtg_r24b_B.work[vtg_r24b_B.work_tmp] += A[vtg_r24b_B.c_k - 1] *
                A[vtg_r24b_B.ix];
            }

            vtg_r24b_B.ix++;
          }
        }

        if (!(-vtg_r24b_B.tau[vtg_r24b_B.g_i] == 0.0)) {
          vtg_r24b_B.ix = vtg_r24b_B.in + 1;
          for (vtg_r24b_B.rowleft = 0; vtg_r24b_B.rowleft <= vtg_r24b_B.lastv;
               vtg_r24b_B.rowleft++) {
            vtg_r24b_B.beta1 = A[(vtg_r24b_B.im1n_tmp + vtg_r24b_B.rowleft) - 1];
            if (vtg_r24b_B.beta1 != 0.0) {
              vtg_r24b_B.beta1 *= -vtg_r24b_B.tau[vtg_r24b_B.g_i];
              vtg_r24b_B.e = (vtg_r24b_B.knt + vtg_r24b_B.ix) - 1;
              for (vtg_r24b_B.c_k = vtg_r24b_B.ix; vtg_r24b_B.c_k <=
                   vtg_r24b_B.e; vtg_r24b_B.c_k++) {
                A[vtg_r24b_B.c_k - 1] += vtg_r24b_B.work[vtg_r24b_B.c_k -
                  vtg_r24b_B.ix] * vtg_r24b_B.beta1;
              }
            }

            vtg_r24b_B.ix += 4;
          }
        }
      }

      vtg_r24b_xzlarf(3 - vtg_r24b_B.g_i, 3 - vtg_r24b_B.g_i,
                      vtg_r24b_B.im1n_tmp, vtg_r24b_B.tau[vtg_r24b_B.g_i], A,
                      (vtg_r24b_B.g_i + vtg_r24b_B.in) + 2, vtg_r24b_B.work);
      A[vtg_r24b_B.istart] = vtg_r24b_B.A;
    }

    memcpy(&V[0], &A[0], sizeof(real_T) << 4U);
    for (vtg_r24b_B.g_i = 2; vtg_r24b_B.g_i >= 0; vtg_r24b_B.g_i--) {
      vtg_r24b_B.in = (vtg_r24b_B.g_i + 1) << 2;
      for (vtg_r24b_B.istart = 0; vtg_r24b_B.istart <= vtg_r24b_B.g_i;
           vtg_r24b_B.istart++) {
        V[vtg_r24b_B.in + vtg_r24b_B.istart] = 0.0;
      }

      for (vtg_r24b_B.istart = vtg_r24b_B.g_i + 3; vtg_r24b_B.istart < 5;
           vtg_r24b_B.istart++) {
        vtg_r24b_B.im1n_tmp = vtg_r24b_B.in + vtg_r24b_B.istart;
        V[vtg_r24b_B.im1n_tmp - 1] = V[vtg_r24b_B.im1n_tmp - 5];
      }
    }

    V[1] = 0.0;
    V[2] = 0.0;
    V[3] = 0.0;
    V[0] = 1.0;
    vtg_r24b_B.work[0] = 0.0;
    vtg_r24b_B.work[1] = 0.0;
    vtg_r24b_B.work[2] = 0.0;
    vtg_r24b_B.work[3] = 0.0;
    for (vtg_r24b_B.g_i = 2; vtg_r24b_B.g_i >= 0; vtg_r24b_B.g_i--) {
      vtg_r24b_B.in = ((vtg_r24b_B.g_i << 2) + vtg_r24b_B.g_i) + 5;
      if (vtg_r24b_B.g_i + 1 < 3) {
        V[vtg_r24b_B.in] = 1.0;
        vtg_r24b_xzlarf(3 - vtg_r24b_B.g_i, 2 - vtg_r24b_B.g_i, vtg_r24b_B.in +
                        1, vtg_r24b_B.tau[vtg_r24b_B.g_i], V, vtg_r24b_B.in + 5,
                        vtg_r24b_B.work);
        vtg_r24b_B.im1n_tmp = (vtg_r24b_B.in - vtg_r24b_B.g_i) + 3;
        for (vtg_r24b_B.istart = vtg_r24b_B.in + 2; vtg_r24b_B.istart <=
             vtg_r24b_B.im1n_tmp; vtg_r24b_B.istart++) {
          V[vtg_r24b_B.istart - 1] *= -vtg_r24b_B.tau[vtg_r24b_B.g_i];
        }
      }

      V[vtg_r24b_B.in] = 1.0 - vtg_r24b_B.tau[vtg_r24b_B.g_i];
      for (vtg_r24b_B.istart = 0; vtg_r24b_B.istart < vtg_r24b_B.g_i;
           vtg_r24b_B.istart++) {
        V[(vtg_r24b_B.in - vtg_r24b_B.istart) - 1] = 0.0;
      }
    }

    vtg_r24b_xhseqr(A, V);
  }
}

// Function for MATLAB Function: '<S8>/MATLAB Function1'
static void vtg_r24b_xzlascl(real_T cfrom, real_T cto, int32_T m, int32_T n,
  real_T A[4], int32_T iA0, int32_T lda)
{
  real_T cfromc;
  real_T ctoc;
  boolean_T notdone;
  cfromc = cfrom;
  ctoc = cto;
  notdone = true;
  while (notdone) {
    real_T cfrom1;
    real_T cto1;
    real_T mul;
    cfrom1 = cfromc * 2.0041683600089728E-292;
    cto1 = ctoc / 4.9896007738368E+291;
    if ((fabs(cfrom1) > fabs(ctoc)) && (ctoc != 0.0)) {
      mul = 2.0041683600089728E-292;
      cfromc = cfrom1;
    } else if (fabs(cto1) > fabs(cfromc)) {
      mul = 4.9896007738368E+291;
      ctoc = cto1;
    } else {
      mul = ctoc / cfromc;
      notdone = false;
    }

    for (int32_T j = 0; j < n; j++) {
      int32_T offset;
      offset = (j * lda + iA0) - 2;
      for (int32_T b_i = 0; b_i < m; b_i++) {
        int32_T tmp;
        tmp = (b_i + offset) + 1;
        A[tmp] *= mul;
      }
    }
  }
}

// Function for MATLAB Function: '<S8>/MATLAB Function1'
static real_T vtg_r24b_xnrm2_dm(int32_T n, const real_T x[4], int32_T ix0)
{
  real_T y;
  y = 0.0;
  if (n >= 1) {
    if (n == 1) {
      y = fabs(x[ix0 - 1]);
    } else {
      int32_T kend;
      vtg_r24b_B.scale_b = 3.3121686421112381E-170;
      kend = ix0 + n;
      for (int32_T k = ix0; k < kend; k++) {
        vtg_r24b_B.absxk_l = fabs(x[k - 1]);
        if (vtg_r24b_B.absxk_l > vtg_r24b_B.scale_b) {
          vtg_r24b_B.t_h = vtg_r24b_B.scale_b / vtg_r24b_B.absxk_l;
          y = y * vtg_r24b_B.t_h * vtg_r24b_B.t_h + 1.0;
          vtg_r24b_B.scale_b = vtg_r24b_B.absxk_l;
        } else {
          vtg_r24b_B.t_h = vtg_r24b_B.absxk_l / vtg_r24b_B.scale_b;
          y += vtg_r24b_B.t_h * vtg_r24b_B.t_h;
        }
      }

      y = vtg_r24b_B.scale_b * sqrt(y);
    }
  }

  return y;
}

// Function for MATLAB Function: '<S8>/MATLAB Function1'
static void vtg_r24b_xzgebal(char_T job, real_T A[4], int32_T *ilo, int32_T *ihi,
  real_T scale[2])
{
  int32_T c_i;
  int32_T exitg1;
  int32_T exitg2;
  int32_T exitg4;
  int32_T exitg5;
  int32_T f_ix;
  int32_T ica;
  int32_T ira;
  int32_T ix0_tmp;
  int32_T kend;
  boolean_T exitg3;
  boolean_T exitg6;
  boolean_T exitg7;
  boolean_T guard1;
  boolean_T permuteOnly;
  boolean_T scaleAndpermute;
  boolean_T scaleOnly;
  boolean_T skipThisColumn;
  scale[0] = 1.0;
  scale[1] = 1.0;
  *ilo = 1;
  *ihi = 2;
  scaleOnly = (job == 'S');
  permuteOnly = (job == 'P');
  scaleAndpermute = (job == 'B');
  if (job == 'N') {
    *ilo = 1;
    *ihi = 2;
  } else {
    guard1 = false;
    if (permuteOnly || scaleAndpermute) {
      permuteOnly = true;
      do {
        exitg5 = 0;
        if (permuteOnly) {
          permuteOnly = false;
          f_ix = *ihi;
          do {
            exitg4 = 0;
            if (f_ix > 0) {
              skipThisColumn = false;
              c_i = 0;
              exitg6 = false;
              while ((!exitg6) && (c_i <= *ihi - 1)) {
                if ((c_i + 1 == f_ix) || (!(A[((c_i << 1) + f_ix) - 1] != 0.0)))
                {
                  c_i++;
                } else {
                  skipThisColumn = true;
                  exitg6 = true;
                }
              }

              if (skipThisColumn) {
                f_ix--;
              } else {
                scale[*ihi - 1] = f_ix;
                if (f_ix != *ihi) {
                  ica = (f_ix - 1) << 1;
                  kend = (*ihi - 1) << 1;
                  for (ix0_tmp = 0; ix0_tmp < *ihi; ix0_tmp++) {
                    ira = ica + ix0_tmp;
                    vtg_r24b_B.c = A[ira];
                    c_i = kend + ix0_tmp;
                    A[ira] = A[c_i];
                    A[c_i] = vtg_r24b_B.c;
                  }

                  vtg_r24b_B.c = A[f_ix - 1];
                  A[f_ix - 1] = A[*ihi - 1];
                  A[*ihi - 1] = vtg_r24b_B.c;
                  vtg_r24b_B.c = A[f_ix + 1];
                  A[f_ix + 1] = A[*ihi + 1];
                  A[*ihi + 1] = vtg_r24b_B.c;
                }

                exitg4 = 1;
              }
            } else {
              exitg4 = 2;
            }
          } while (exitg4 == 0);

          if (exitg4 == 1) {
            if (*ihi == 1) {
              *ilo = 1;
              *ihi = 1;
              exitg5 = 1;
            } else {
              *ihi = 1;
              permuteOnly = true;
            }
          }
        } else {
          permuteOnly = true;
          while (permuteOnly) {
            permuteOnly = false;
            f_ix = *ilo;
            exitg6 = false;
            while ((!exitg6) && (f_ix <= *ihi)) {
              skipThisColumn = false;
              c_i = *ilo;
              exitg7 = false;
              while ((!exitg7) && (c_i <= *ihi)) {
                if ((c_i == f_ix) || (!(A[(((f_ix - 1) << 1) + c_i) - 1] != 0.0)))
                {
                  c_i++;
                } else {
                  skipThisColumn = true;
                  exitg7 = true;
                }
              }

              if (skipThisColumn) {
                f_ix++;
              } else {
                scale[*ilo - 1] = f_ix;
                if (f_ix != *ilo) {
                  kend = (f_ix - 1) << 1;
                  ix0_tmp = (*ilo - 1) << 1;
                  for (ica = 0; ica < *ihi; ica++) {
                    ira = kend + ica;
                    vtg_r24b_B.c = A[ira];
                    c_i = ix0_tmp + ica;
                    A[ira] = A[c_i];
                    A[c_i] = vtg_r24b_B.c;
                  }

                  f_ix = (ix0_tmp + f_ix) - 1;
                  ica = (ix0_tmp + *ilo) - 1;
                  kend = 2 - *ilo;
                  for (ix0_tmp = 0; ix0_tmp <= kend; ix0_tmp++) {
                    c_i = ix0_tmp << 1;
                    ira = c_i + f_ix;
                    vtg_r24b_B.c = A[ira];
                    c_i += ica;
                    A[ira] = A[c_i];
                    A[c_i] = vtg_r24b_B.c;
                  }
                }

                (*ilo)++;
                permuteOnly = true;
                exitg6 = true;
              }
            }
          }

          exitg5 = 2;
        }
      } while (exitg5 == 0);

      if (exitg5 == 1) {
      } else {
        guard1 = true;
      }
    } else {
      guard1 = true;
    }

    if (guard1) {
      if (scaleOnly || scaleAndpermute) {
        scaleOnly = false;
        exitg3 = false;
        while ((!exitg3) && (!scaleOnly)) {
          scaleOnly = true;
          c_i = *ilo - 1;
          do {
            exitg2 = 0;
            if (c_i + 1 <= *ihi) {
              ica = (*ihi - *ilo) + 1;
              f_ix = c_i << 1;
              vtg_r24b_B.c = vtg_r24b_xnrm2_dm(ica, A, f_ix + *ilo);
              ix0_tmp = ((*ilo - 1) << 1) + c_i;
              vtg_r24b_B.r_l = 0.0;
              if (ica >= 1) {
                if (ica == 1) {
                  vtg_r24b_B.r_l = fabs(A[ix0_tmp]);
                } else {
                  vtg_r24b_B.b_scale = 3.3121686421112381E-170;
                  kend = (((ica - 1) << 1) + ix0_tmp) + 1;
                  for (ica = ix0_tmp + 1; ica <= kend; ica += 2) {
                    vtg_r24b_B.absxk_d = fabs(A[ica - 1]);
                    if (vtg_r24b_B.absxk_d > vtg_r24b_B.b_scale) {
                      vtg_r24b_B.t_l = vtg_r24b_B.b_scale / vtg_r24b_B.absxk_d;
                      vtg_r24b_B.r_l = vtg_r24b_B.r_l * vtg_r24b_B.t_l *
                        vtg_r24b_B.t_l + 1.0;
                      vtg_r24b_B.b_scale = vtg_r24b_B.absxk_d;
                    } else {
                      vtg_r24b_B.t_l = vtg_r24b_B.absxk_d / vtg_r24b_B.b_scale;
                      vtg_r24b_B.r_l += vtg_r24b_B.t_l * vtg_r24b_B.t_l;
                    }
                  }

                  vtg_r24b_B.r_l = vtg_r24b_B.b_scale * sqrt(vtg_r24b_B.r_l);
                }
              }

              ica = 0;
              if ((*ihi > 1) && (fabs(A[f_ix + 1]) > fabs(A[f_ix]))) {
                ica = 1;
              }

              vtg_r24b_B.b_scale = fabs(A[f_ix + ica]);
              kend = 3 - *ilo;
              if (3 - *ilo < 1) {
                ira = 0;
              } else {
                ira = 1;
                if (3 - *ilo > 1) {
                  vtg_r24b_B.absxk_d = fabs(A[ix0_tmp]);
                  for (ica = 2; ica <= kend; ica++) {
                    vtg_r24b_B.t_l = fabs(A[((ica - 1) << 1) + ix0_tmp]);
                    if (vtg_r24b_B.t_l > vtg_r24b_B.absxk_d) {
                      ira = ica;
                      vtg_r24b_B.absxk_d = vtg_r24b_B.t_l;
                    }
                  }
                }
              }

              vtg_r24b_B.t_l = fabs(A[(((ira + *ilo) - 2) << 1) + c_i]);
              if ((vtg_r24b_B.c == 0.0) || (vtg_r24b_B.r_l == 0.0)) {
                c_i++;
              } else {
                vtg_r24b_B.g = vtg_r24b_B.r_l / 2.0;
                vtg_r24b_B.absxk_d = 1.0;
                vtg_r24b_B.s_d = vtg_r24b_B.c + vtg_r24b_B.r_l;
                do {
                  exitg1 = 0;
                  if (vtg_r24b_B.c < vtg_r24b_B.g) {
                    if ((vtg_r24b_B.c >= vtg_r24b_B.b_scale) || rtIsNaN
                        (vtg_r24b_B.b_scale)) {
                      vtg_r24b_B.y = vtg_r24b_B.c;
                    } else {
                      vtg_r24b_B.y = vtg_r24b_B.b_scale;
                    }

                    if (vtg_r24b_B.absxk_d >= vtg_r24b_B.y) {
                      vtg_r24b_B.y = vtg_r24b_B.absxk_d;
                    }

                    if (vtg_r24b_B.y < 4.9896007738368E+291) {
                      if ((vtg_r24b_B.g <= vtg_r24b_B.t_l) || rtIsNaN
                          (vtg_r24b_B.t_l)) {
                        vtg_r24b_B.y = vtg_r24b_B.g;
                      } else {
                        vtg_r24b_B.y = vtg_r24b_B.t_l;
                      }

                      if (vtg_r24b_B.r_l <= vtg_r24b_B.y) {
                        vtg_r24b_B.y = vtg_r24b_B.r_l;
                      }

                      if (vtg_r24b_B.y > 2.0041683600089728E-292) {
                        if (rtIsNaN(((((vtg_r24b_B.c + vtg_r24b_B.absxk_d) +
                                       vtg_r24b_B.b_scale) + vtg_r24b_B.r_l) +
                                     vtg_r24b_B.g) + vtg_r24b_B.t_l)) {
                          exitg1 = 1;
                        } else {
                          vtg_r24b_B.absxk_d *= 2.0;
                          vtg_r24b_B.c *= 2.0;
                          vtg_r24b_B.b_scale *= 2.0;
                          vtg_r24b_B.r_l /= 2.0;
                          vtg_r24b_B.g /= 2.0;
                          vtg_r24b_B.t_l /= 2.0;
                        }
                      } else {
                        exitg1 = 2;
                      }
                    } else {
                      exitg1 = 2;
                    }
                  } else {
                    exitg1 = 2;
                  }
                } while (exitg1 == 0);

                if (exitg1 == 1) {
                  exitg2 = 2;
                } else {
                  vtg_r24b_B.g = vtg_r24b_B.c / 2.0;
                  exitg6 = false;
                  while ((!exitg6) && (vtg_r24b_B.g >= vtg_r24b_B.r_l)) {
                    if ((vtg_r24b_B.r_l >= vtg_r24b_B.t_l) || rtIsNaN
                        (vtg_r24b_B.t_l)) {
                      vtg_r24b_B.y = vtg_r24b_B.r_l;
                    } else {
                      vtg_r24b_B.y = vtg_r24b_B.t_l;
                    }

                    if (vtg_r24b_B.y < 4.9896007738368E+291) {
                      if ((vtg_r24b_B.absxk_d <= vtg_r24b_B.c) || rtIsNaN
                          (vtg_r24b_B.c)) {
                        vtg_r24b_B.y = vtg_r24b_B.absxk_d;
                      } else {
                        vtg_r24b_B.y = vtg_r24b_B.c;
                      }

                      if ((vtg_r24b_B.g <= vtg_r24b_B.b_scale) || rtIsNaN
                          (vtg_r24b_B.b_scale)) {
                        vtg_r24b_B.y_o = vtg_r24b_B.g;
                      } else {
                        vtg_r24b_B.y_o = vtg_r24b_B.b_scale;
                      }

                      if (vtg_r24b_B.y <= vtg_r24b_B.y_o) {
                        vtg_r24b_B.y_o = vtg_r24b_B.y;
                      }

                      if (vtg_r24b_B.y_o > 2.0041683600089728E-292) {
                        vtg_r24b_B.absxk_d /= 2.0;
                        vtg_r24b_B.c /= 2.0;
                        vtg_r24b_B.g /= 2.0;
                        vtg_r24b_B.b_scale /= 2.0;
                        vtg_r24b_B.r_l *= 2.0;
                        vtg_r24b_B.t_l *= 2.0;
                      } else {
                        exitg6 = true;
                      }
                    } else {
                      exitg6 = true;
                    }
                  }

                  if ((vtg_r24b_B.c + vtg_r24b_B.r_l >= 0.95 * vtg_r24b_B.s_d) ||
                      ((vtg_r24b_B.absxk_d < 1.0) && (scale[c_i] < 1.0) &&
                       (vtg_r24b_B.absxk_d * scale[c_i] <=
                        1.0020841800044864E-292)) || ((vtg_r24b_B.absxk_d > 1.0)
                       && (scale[c_i] > 1.0) && (scale[c_i] >=
                        9.9792015476736E+291 / vtg_r24b_B.absxk_d))) {
                  } else {
                    vtg_r24b_B.c = 1.0 / vtg_r24b_B.absxk_d;
                    scale[c_i] *= vtg_r24b_B.absxk_d;
                    ica = ix0_tmp + 1;
                    kend = (((2 - *ilo) << 1) + ix0_tmp) + 1;
                    for (ix0_tmp = ica; ix0_tmp <= kend; ix0_tmp += 2) {
                      A[ix0_tmp - 1] *= vtg_r24b_B.c;
                    }

                    ica = f_ix + *ihi;
                    for (ix0_tmp = f_ix + 1; ix0_tmp <= ica; ix0_tmp++) {
                      A[ix0_tmp - 1] *= vtg_r24b_B.absxk_d;
                    }

                    scaleOnly = false;
                  }

                  c_i++;
                }
              }
            } else {
              exitg2 = 1;
            }
          } while (exitg2 == 0);

          if (exitg2 == 1) {
          } else {
            exitg3 = true;
          }
        }
      }
    }
  }
}

// Function for MATLAB Function: '<S8>/MATLAB Function1'
static void vtg_r24b_xzgehrd(real_T a[4], int32_T ilo, int32_T ihi)
{
  int32_T alpha1_tmp_tmp_tmp;
  int32_T b_k;
  int32_T b_lastv;
  int32_T e;
  int32_T exitg1;
  int32_T f;
  int32_T i;
  int32_T in;
  int32_T ix;
  int32_T jA;
  int32_T knt;
  int32_T lastv;
  int32_T rowleft;
  boolean_T exitg2;
  if ((ihi - ilo) + 1 > 1) {
    vtg_r24b_B.work_c[0] = 0.0;
    vtg_r24b_B.work_c[1] = 0.0;
    for (i = ilo; i < ihi; i++) {
      lastv = (i - 1) << 1;
      in = i << 1;
      alpha1_tmp_tmp_tmp = lastv + i;
      vtg_r24b_B.alpha1_tmp = a[alpha1_tmp_tmp_tmp];
      if (i + 2 <= 2) {
        b_lastv = i + 2;
      } else {
        b_lastv = 2;
      }

      lastv += b_lastv;
      b_lastv = ihi - i;
      vtg_r24b_B.tau_b = 0.0;
      if (b_lastv > 0) {
        vtg_r24b_B.xnorm_n = vtg_r24b_xnrm2_dm(b_lastv - 1, a, lastv);
        if (vtg_r24b_B.xnorm_n != 0.0) {
          vtg_r24b_B.xnorm_n = vtg_r24b_rt_hypotd_snf(vtg_r24b_B.alpha1_tmp,
            vtg_r24b_B.xnorm_n);
          if (vtg_r24b_B.alpha1_tmp >= 0.0) {
            vtg_r24b_B.xnorm_n = -vtg_r24b_B.xnorm_n;
          }

          if (fabs(vtg_r24b_B.xnorm_n) < 1.0020841800044864E-292) {
            knt = 0;
            rowleft = (lastv + b_lastv) - 2;
            do {
              knt++;
              for (b_k = lastv; b_k <= rowleft; b_k++) {
                a[b_k - 1] *= 9.9792015476736E+291;
              }

              vtg_r24b_B.xnorm_n *= 9.9792015476736E+291;
              vtg_r24b_B.alpha1_tmp *= 9.9792015476736E+291;
            } while ((fabs(vtg_r24b_B.xnorm_n) < 1.0020841800044864E-292) &&
                     (knt < 20));

            vtg_r24b_B.xnorm_n = vtg_r24b_rt_hypotd_snf(vtg_r24b_B.alpha1_tmp,
              vtg_r24b_xnrm2_dm(b_lastv - 1, a, lastv));
            if (vtg_r24b_B.alpha1_tmp >= 0.0) {
              vtg_r24b_B.xnorm_n = -vtg_r24b_B.xnorm_n;
            }

            vtg_r24b_B.tau_b = (vtg_r24b_B.xnorm_n - vtg_r24b_B.alpha1_tmp) /
              vtg_r24b_B.xnorm_n;
            vtg_r24b_B.alpha1_tmp = 1.0 / (vtg_r24b_B.alpha1_tmp -
              vtg_r24b_B.xnorm_n);
            for (b_k = lastv; b_k <= rowleft; b_k++) {
              a[b_k - 1] *= vtg_r24b_B.alpha1_tmp;
            }

            for (lastv = 0; lastv < knt; lastv++) {
              vtg_r24b_B.xnorm_n *= 1.0020841800044864E-292;
            }

            vtg_r24b_B.alpha1_tmp = vtg_r24b_B.xnorm_n;
          } else {
            vtg_r24b_B.tau_b = (vtg_r24b_B.xnorm_n - vtg_r24b_B.alpha1_tmp) /
              vtg_r24b_B.xnorm_n;
            vtg_r24b_B.alpha1_tmp = 1.0 / (vtg_r24b_B.alpha1_tmp -
              vtg_r24b_B.xnorm_n);
            rowleft = (lastv + b_lastv) - 2;
            for (knt = lastv; knt <= rowleft; knt++) {
              a[knt - 1] *= vtg_r24b_B.alpha1_tmp;
            }

            vtg_r24b_B.alpha1_tmp = vtg_r24b_B.xnorm_n;
          }
        }
      }

      a[alpha1_tmp_tmp_tmp] = 1.0;
      if (vtg_r24b_B.tau_b != 0.0) {
        lastv = b_lastv;
        knt = (alpha1_tmp_tmp_tmp + b_lastv) - 2;
        while ((lastv > 0) && (a[knt + 1] == 0.0)) {
          lastv--;
          knt--;
        }

        knt = ihi;
        exitg2 = false;
        while ((!exitg2) && (knt > 0)) {
          rowleft = in + knt;
          b_k = rowleft;
          do {
            exitg1 = 0;
            if (b_k <= ((lastv - 1) << 1) + rowleft) {
              if (a[b_k - 1] != 0.0) {
                exitg1 = 1;
              } else {
                b_k += 2;
              }
            } else {
              knt--;
              exitg1 = 2;
            }
          } while (exitg1 == 0);

          if (exitg1 == 1) {
            exitg2 = true;
          }
        }
      } else {
        lastv = 0;
        knt = 0;
      }

      if (lastv > 0) {
        if (knt != 0) {
          if (knt - 1 >= 0) {
            memset(&vtg_r24b_B.work_c[0], 0, static_cast<uint32_T>(knt) * sizeof
                   (real_T));
          }

          ix = alpha1_tmp_tmp_tmp;
          e = (((lastv - 1) << 1) + in) + 1;
          for (b_k = in + 1; b_k <= e; b_k += 2) {
            f = (b_k + knt) - 1;
            for (jA = b_k; jA <= f; jA++) {
              rowleft = jA - b_k;
              vtg_r24b_B.work_c[rowleft] += a[jA - 1] * a[ix];
            }

            ix++;
          }
        }

        if (!(-vtg_r24b_B.tau_b == 0.0)) {
          jA = in + 1;
          for (rowleft = 0; rowleft < lastv; rowleft++) {
            vtg_r24b_B.xnorm_n = a[alpha1_tmp_tmp_tmp + rowleft];
            if (vtg_r24b_B.xnorm_n != 0.0) {
              vtg_r24b_B.xnorm_n *= -vtg_r24b_B.tau_b;
              ix = (knt + jA) - 1;
              for (b_k = jA; b_k <= ix; b_k++) {
                a[b_k - 1] += vtg_r24b_B.work_c[b_k - jA] * vtg_r24b_B.xnorm_n;
              }
            }

            jA += 2;
          }
        }
      }

      in = (i + in) + 1;
      if (vtg_r24b_B.tau_b != 0.0) {
        lastv = alpha1_tmp_tmp_tmp + b_lastv;
        while ((b_lastv > 0) && (a[lastv - 1] == 0.0)) {
          b_lastv--;
          lastv--;
        }

        lastv = 2 - i;
        exitg2 = false;
        while ((!exitg2) && (lastv > 0)) {
          knt = ((lastv - 1) << 1) + in;
          rowleft = knt;
          do {
            exitg1 = 0;
            if (rowleft <= (knt + b_lastv) - 1) {
              if (a[rowleft - 1] != 0.0) {
                exitg1 = 1;
              } else {
                rowleft++;
              }
            } else {
              lastv--;
              exitg1 = 2;
            }
          } while (exitg1 == 0);

          if (exitg1 == 1) {
            exitg2 = true;
          }
        }

        lastv--;
      } else {
        b_lastv = 0;
        lastv = -1;
      }

      if (b_lastv > 0) {
        if (lastv + 1 != 0) {
          if (lastv >= 0) {
            memset(&vtg_r24b_B.work_c[0], 0, static_cast<uint32_T>(lastv + 1) *
                   sizeof(real_T));
          }

          b_k = (lastv << 1) + in;
          for (knt = in; knt <= b_k; knt += 2) {
            vtg_r24b_B.xnorm_n = 0.0;
            jA = (knt + b_lastv) - 1;
            for (rowleft = knt; rowleft <= jA; rowleft++) {
              vtg_r24b_B.xnorm_n += a[(alpha1_tmp_tmp_tmp + rowleft) - knt] *
                a[rowleft - 1];
            }

            rowleft = (knt - in) >> 1;
            vtg_r24b_B.work_c[rowleft] += vtg_r24b_B.xnorm_n;
          }
        }

        if (!(-vtg_r24b_B.tau_b == 0.0)) {
          for (knt = 0; knt <= lastv; knt++) {
            vtg_r24b_B.xnorm_n = vtg_r24b_B.work_c[knt];
            if (vtg_r24b_B.xnorm_n != 0.0) {
              vtg_r24b_B.xnorm_n *= -vtg_r24b_B.tau_b;
              b_k = (b_lastv + in) - 1;
              for (rowleft = in; rowleft <= b_k; rowleft++) {
                a[rowleft - 1] += a[(alpha1_tmp_tmp_tmp + rowleft) - in] *
                  vtg_r24b_B.xnorm_n;
              }
            }

            in += 2;
          }
        }
      }

      a[alpha1_tmp_tmp_tmp] = vtg_r24b_B.alpha1_tmp;
    }
  }
}

// Function for MATLAB Function: '<S8>/MATLAB Function1'
static void vtg_r24b_xdlahqr(int32_T ilo, int32_T ihi, real_T h[4], int32_T
  *info, real_T wr[2], real_T wi[2])
{
  int32_T d_k;
  int32_T h_tmp;
  int32_T its;
  int32_T ix0;
  int32_T k;
  int32_T kdefl;
  int32_T l;
  int32_T m;
  int32_T n;
  int32_T nh;
  int32_T nr;
  int32_T s_tmp;
  boolean_T converged;
  boolean_T exitg1;
  boolean_T exitg2;
  boolean_T exitg3;
  boolean_T tmp;
  *info = 0;
  for (nh = 0; nh <= ilo - 2; nh++) {
    wr[nh] = h[(nh << 1) + nh];
    wi[nh] = 0.0;
  }

  for (nh = ihi + 1; nh < 3; nh++) {
    wr[nh - 1] = h[(((nh - 1) << 1) + nh) - 1];
    wi[nh - 1] = 0.0;
  }

  if (ilo == ihi) {
    wr[ilo - 1] = h[(((ilo - 1) << 1) + ilo) - 1];
    wi[ilo - 1] = 0.0;
  } else {
    for (nh = ilo; nh <= ihi - 3; nh++) {
      d_k = ((nh - 1) << 1) + nh;
      h[d_k + 1] = 0.0;
      h[d_k + 2] = 0.0;
    }

    if (ilo <= ihi - 2) {
      h[(ihi + ((ihi - 3) << 1)) - 1] = 0.0;
    }

    nh = (ihi - ilo) + 1;
    vtg_r24b_B.smlnum = static_cast<real_T>(nh) / 2.2204460492503131E-16 *
      2.2250738585072014E-308;
    if (nh < 10) {
      nh = 10;
    }

    nh *= 30;
    kdefl = 0;
    vtg_r24b_B.i_f = ihi - 1;
    exitg1 = false;
    while ((!exitg1) && (vtg_r24b_B.i_f + 1 >= ilo)) {
      l = ilo;
      converged = false;
      its = 0;
      exitg2 = false;
      while ((!exitg2) && (its <= nh)) {
        k = vtg_r24b_B.i_f;
        exitg3 = false;
        while ((!exitg3) && (k + 1 > l)) {
          d_k = ((k - 1) << 1) + k;
          vtg_r24b_B.bb = fabs(h[d_k]);
          if (vtg_r24b_B.bb <= vtg_r24b_B.smlnum) {
            exitg3 = true;
          } else {
            m = (k << 1) + k;
            vtg_r24b_B.aa = fabs(h[m]);
            vtg_r24b_B.tst = fabs(h[d_k - 1]) + vtg_r24b_B.aa;
            if (vtg_r24b_B.tst == 0.0) {
              if (k - 1 >= ilo) {
                vtg_r24b_B.tst = fabs(h[(((k - 2) << 1) + k) - 1]);
              }

              if (k + 2 <= ihi) {
                vtg_r24b_B.tst += fabs(h[m + 1]);
              }
            }

            if (vtg_r24b_B.bb <= 2.2204460492503131E-16 * vtg_r24b_B.tst) {
              vtg_r24b_B.bb = fabs(h[d_k - 1] - h[m]);
              tmp = rtIsNaN(vtg_r24b_B.bb);
              if ((!(vtg_r24b_B.aa >= vtg_r24b_B.bb)) && (!tmp)) {
                vtg_r24b_B.aa = vtg_r24b_B.bb;
              }

              vtg_r24b_B.tr = fabs(h[m]);
              if ((vtg_r24b_B.tr <= vtg_r24b_B.bb) || tmp) {
                vtg_r24b_B.bb = vtg_r24b_B.tr;
              }

              vtg_r24b_B.tst = vtg_r24b_B.aa + vtg_r24b_B.bb;
              vtg_r24b_B.tr = fabs(h[d_k]);
              vtg_r24b_B.h21 = fabs(h[m - 1]);
              vtg_r24b_B.aa = vtg_r24b_B.aa / vtg_r24b_B.tst * vtg_r24b_B.bb *
                2.2204460492503131E-16;
              tmp = rtIsNaN(vtg_r24b_B.h21);
              if ((vtg_r24b_B.tr <= vtg_r24b_B.h21) || tmp) {
                vtg_r24b_B.bb = vtg_r24b_B.tr;
              } else {
                vtg_r24b_B.bb = vtg_r24b_B.h21;
              }

              if ((vtg_r24b_B.tr >= vtg_r24b_B.h21) || tmp) {
                vtg_r24b_B.h21 = vtg_r24b_B.tr;
              }

              if ((vtg_r24b_B.smlnum >= vtg_r24b_B.aa) || rtIsNaN(vtg_r24b_B.aa))
              {
                vtg_r24b_B.aa = vtg_r24b_B.smlnum;
              }

              if (vtg_r24b_B.h21 / vtg_r24b_B.tst * vtg_r24b_B.bb <=
                  vtg_r24b_B.aa) {
                exitg3 = true;
              } else {
                k--;
              }
            } else {
              k--;
            }
          }
        }

        l = k + 1;
        if (k + 1 > ilo) {
          h[k + ((k - 1) << 1)] = 0.0;
        }

        if (k + 1 >= vtg_r24b_B.i_f) {
          converged = true;
          exitg2 = true;
        } else {
          kdefl++;
          if (kdefl - div_nzp_s32(kdefl, 20) * 20 == 0) {
            vtg_r24b_B.tst = fabs(h[(((vtg_r24b_B.i_f - 2) << 1) +
              vtg_r24b_B.i_f) - 1]) + fabs(h[((vtg_r24b_B.i_f - 1) << 1) +
              vtg_r24b_B.i_f]);
            vtg_r24b_B.bb = h[(vtg_r24b_B.i_f << 1) + vtg_r24b_B.i_f] + 0.75 *
              vtg_r24b_B.tst;
            vtg_r24b_B.h12 = -0.4375 * vtg_r24b_B.tst;
            vtg_r24b_B.h21 = vtg_r24b_B.tst;
            vtg_r24b_B.aa = vtg_r24b_B.bb;
          } else if (kdefl - div_nzp_s32(kdefl, 10) * 10 == 0) {
            s_tmp = (k << 1) + k;
            vtg_r24b_B.tst = fabs(h[(((k + 1) << 1) + k) + 2]) + fabs(h[s_tmp +
              1]);
            vtg_r24b_B.bb = 0.75 * vtg_r24b_B.tst + h[s_tmp];
            vtg_r24b_B.h12 = -0.4375 * vtg_r24b_B.tst;
            vtg_r24b_B.h21 = vtg_r24b_B.tst;
            vtg_r24b_B.aa = vtg_r24b_B.bb;
          } else {
            m = ((vtg_r24b_B.i_f - 1) << 1) + vtg_r24b_B.i_f;
            vtg_r24b_B.bb = h[m - 1];
            vtg_r24b_B.h21 = h[m];
            m = (vtg_r24b_B.i_f << 1) + vtg_r24b_B.i_f;
            vtg_r24b_B.h12 = h[m - 1];
            vtg_r24b_B.aa = h[m];
          }

          vtg_r24b_B.tst = ((fabs(vtg_r24b_B.bb) + fabs(vtg_r24b_B.h12)) + fabs
                            (vtg_r24b_B.h21)) + fabs(vtg_r24b_B.aa);
          if (vtg_r24b_B.tst == 0.0) {
            vtg_r24b_B.bb = 0.0;
            vtg_r24b_B.aa = 0.0;
            vtg_r24b_B.tr = 0.0;
            vtg_r24b_B.h21 = 0.0;
          } else {
            vtg_r24b_B.bb /= vtg_r24b_B.tst;
            vtg_r24b_B.aa /= vtg_r24b_B.tst;
            vtg_r24b_B.tr = (vtg_r24b_B.bb + vtg_r24b_B.aa) / 2.0;
            vtg_r24b_B.bb = (vtg_r24b_B.bb - vtg_r24b_B.tr) * (vtg_r24b_B.aa -
              vtg_r24b_B.tr) - vtg_r24b_B.h12 / vtg_r24b_B.tst * (vtg_r24b_B.h21
              / vtg_r24b_B.tst);
            vtg_r24b_B.h21 = sqrt(fabs(vtg_r24b_B.bb));
            if (vtg_r24b_B.bb >= 0.0) {
              vtg_r24b_B.bb = vtg_r24b_B.tr * vtg_r24b_B.tst;
              vtg_r24b_B.tr = vtg_r24b_B.bb;
              vtg_r24b_B.aa = vtg_r24b_B.h21 * vtg_r24b_B.tst;
              vtg_r24b_B.h21 = -vtg_r24b_B.aa;
            } else {
              vtg_r24b_B.bb = vtg_r24b_B.tr + vtg_r24b_B.h21;
              vtg_r24b_B.tr -= vtg_r24b_B.h21;
              if (fabs(vtg_r24b_B.bb - vtg_r24b_B.aa) <= fabs(vtg_r24b_B.tr -
                   vtg_r24b_B.aa)) {
                vtg_r24b_B.bb *= vtg_r24b_B.tst;
                vtg_r24b_B.tr = vtg_r24b_B.bb;
              } else {
                vtg_r24b_B.tr *= vtg_r24b_B.tst;
                vtg_r24b_B.bb = vtg_r24b_B.tr;
              }

              vtg_r24b_B.aa = 0.0;
              vtg_r24b_B.h21 = 0.0;
            }
          }

          m = vtg_r24b_B.i_f - 1;
          exitg3 = false;
          while ((!exitg3) && (m >= k + 1)) {
            s_tmp = ((m - 1) << 1) + m;
            vtg_r24b_B.h12 = h[s_tmp - 1];
            vtg_r24b_B.s_tmp = vtg_r24b_B.h12 - vtg_r24b_B.tr;
            vtg_r24b_B.tst = (fabs(vtg_r24b_B.s_tmp) + fabs(vtg_r24b_B.h21)) +
              fabs(h[s_tmp]);
            vtg_r24b_B.h21s = h[s_tmp] / vtg_r24b_B.tst;
            nr = (m << 1) + m;
            vtg_r24b_B.v[0] = (vtg_r24b_B.s_tmp / vtg_r24b_B.tst *
                               vtg_r24b_B.s_tmp + h[nr - 1] * vtg_r24b_B.h21s) -
              vtg_r24b_B.h21 / vtg_r24b_B.tst * vtg_r24b_B.aa;
            vtg_r24b_B.v[1] = (((vtg_r24b_B.h12 + h[nr]) - vtg_r24b_B.bb) -
                               vtg_r24b_B.tr) * vtg_r24b_B.h21s;
            vtg_r24b_B.v[2] = h[nr + 1] * vtg_r24b_B.h21s;
            vtg_r24b_B.tst = (fabs(vtg_r24b_B.v[0]) + fabs(vtg_r24b_B.v[1])) +
              fabs(vtg_r24b_B.v[2]);
            vtg_r24b_B.v[0] /= vtg_r24b_B.tst;
            vtg_r24b_B.v[1] /= vtg_r24b_B.tst;
            vtg_r24b_B.v[2] /= vtg_r24b_B.tst;
            if (k + 1 == m) {
              exitg3 = true;
            } else {
              d_k = ((m - 2) << 1) + m;
              if (fabs(h[d_k - 1]) * (fabs(vtg_r24b_B.v[1]) + fabs(vtg_r24b_B.v
                    [2])) <= ((fabs(h[d_k - 2]) + fabs(h[s_tmp - 1])) + fabs
                              (h[nr])) * (2.2204460492503131E-16 * fabs
                   (vtg_r24b_B.v[0]))) {
                exitg3 = true;
              } else {
                m--;
              }
            }
          }

          for (s_tmp = m; s_tmp <= vtg_r24b_B.i_f; s_tmp++) {
            nr = (vtg_r24b_B.i_f - s_tmp) + 2;
            if (nr >= 3) {
              nr = 3;
            }

            if (s_tmp > m) {
              ix0 = (((s_tmp - 2) << 1) + s_tmp) - 1;
              for (d_k = 0; d_k < nr; d_k++) {
                vtg_r24b_B.v[d_k] = h[ix0 + d_k];
              }
            }

            vtg_r24b_B.bb = vtg_r24b_B.v[0];
            vtg_r24b_B.tst = vtg_r24b_xzlarfg(nr, &vtg_r24b_B.bb, vtg_r24b_B.v);
            if (s_tmp > m) {
              d_k = ((s_tmp - 2) << 1) + s_tmp;
              h[d_k - 1] = vtg_r24b_B.bb;
              h[d_k] = 0.0;
              if (s_tmp < vtg_r24b_B.i_f) {
                h[d_k + 1] = 0.0;
              }
            } else if (m > k + 1) {
              d_k = (((s_tmp - 2) << 1) + s_tmp) - 1;
              h[d_k] *= 1.0 - vtg_r24b_B.tst;
            }

            vtg_r24b_B.bb = vtg_r24b_B.v[1];
            vtg_r24b_B.aa = vtg_r24b_B.tst * vtg_r24b_B.v[1];
            switch (nr) {
             case 3:
              vtg_r24b_B.tr = vtg_r24b_B.v[2];
              vtg_r24b_B.h21 = vtg_r24b_B.tst * vtg_r24b_B.v[2];
              for (nr = s_tmp; nr <= vtg_r24b_B.i_f + 1; nr++) {
                d_k = ((nr - 1) << 1) + s_tmp;
                vtg_r24b_B.h12 = h[d_k - 1];
                vtg_r24b_B.s_tmp = h[d_k];
                vtg_r24b_B.h21s = h[d_k + 1];
                vtg_r24b_B.sum = (vtg_r24b_B.bb * vtg_r24b_B.s_tmp +
                                  vtg_r24b_B.h12) + vtg_r24b_B.tr *
                  vtg_r24b_B.h21s;
                h[d_k - 1] = vtg_r24b_B.h12 - vtg_r24b_B.sum * vtg_r24b_B.tst;
                h[d_k] = vtg_r24b_B.s_tmp - vtg_r24b_B.sum * vtg_r24b_B.aa;
                h[d_k + 1] = vtg_r24b_B.h21s - vtg_r24b_B.sum * vtg_r24b_B.h21;
              }

              if (s_tmp + 3 <= vtg_r24b_B.i_f + 1) {
                n = s_tmp + 3;
              } else {
                n = vtg_r24b_B.i_f + 1;
              }

              for (nr = k + 1; nr <= n; nr++) {
                d_k = (((s_tmp - 1) << 1) + nr) - 1;
                vtg_r24b_B.h12 = h[d_k];
                ix0 = ((s_tmp << 1) + nr) - 1;
                vtg_r24b_B.s_tmp = h[ix0];
                h_tmp = (((s_tmp + 1) << 1) + nr) - 1;
                vtg_r24b_B.h21s = h[h_tmp];
                vtg_r24b_B.sum = (vtg_r24b_B.bb * vtg_r24b_B.s_tmp +
                                  vtg_r24b_B.h12) + vtg_r24b_B.tr *
                  vtg_r24b_B.h21s;
                h[d_k] = vtg_r24b_B.h12 - vtg_r24b_B.sum * vtg_r24b_B.tst;
                h[ix0] = vtg_r24b_B.s_tmp - vtg_r24b_B.sum * vtg_r24b_B.aa;
                h[h_tmp] = vtg_r24b_B.h21s - vtg_r24b_B.sum * vtg_r24b_B.h21;
              }
              break;

             case 2:
              for (nr = s_tmp; nr <= vtg_r24b_B.i_f + 1; nr++) {
                d_k = ((nr - 1) << 1) + s_tmp;
                vtg_r24b_B.h12 = h[d_k - 1];
                vtg_r24b_B.s_tmp = h[d_k];
                vtg_r24b_B.sum = vtg_r24b_B.bb * vtg_r24b_B.s_tmp +
                  vtg_r24b_B.h12;
                h[d_k - 1] = vtg_r24b_B.h12 - vtg_r24b_B.sum * vtg_r24b_B.tst;
                h[d_k] = vtg_r24b_B.s_tmp - vtg_r24b_B.sum * vtg_r24b_B.aa;
              }

              for (nr = k + 1; nr <= vtg_r24b_B.i_f + 1; nr++) {
                d_k = (((s_tmp - 1) << 1) + nr) - 1;
                vtg_r24b_B.h12 = h[d_k];
                ix0 = ((s_tmp << 1) + nr) - 1;
                vtg_r24b_B.s_tmp = h[ix0];
                vtg_r24b_B.sum = vtg_r24b_B.bb * vtg_r24b_B.s_tmp +
                  vtg_r24b_B.h12;
                h[d_k] = vtg_r24b_B.h12 - vtg_r24b_B.sum * vtg_r24b_B.tst;
                h[ix0] = vtg_r24b_B.s_tmp - vtg_r24b_B.sum * vtg_r24b_B.aa;
              }
              break;
            }
          }

          its++;
        }
      }

      if (!converged) {
        *info = vtg_r24b_B.i_f + 1;
        exitg1 = true;
      } else {
        if (vtg_r24b_B.i_f + 1 == l) {
          wr[vtg_r24b_B.i_f] = h[(vtg_r24b_B.i_f << 1) + vtg_r24b_B.i_f];
          wi[vtg_r24b_B.i_f] = 0.0;
        } else if (l == vtg_r24b_B.i_f) {
          kdefl = (vtg_r24b_B.i_f << 1) + vtg_r24b_B.i_f;
          vtg_r24b_B.tst = h[kdefl - 1];
          its = ((vtg_r24b_B.i_f - 1) << 1) + vtg_r24b_B.i_f;
          vtg_r24b_B.bb = h[its];
          vtg_r24b_B.aa = h[kdefl];
          vtg_r24b_xdlanv2(&h[its - 1], &vtg_r24b_B.tst, &vtg_r24b_B.bb,
                           &vtg_r24b_B.aa, &wr[vtg_r24b_B.i_f - 1],
                           &wi[vtg_r24b_B.i_f - 1], &vtg_r24b_B.tr,
                           &vtg_r24b_B.h21, &vtg_r24b_B.h12, &vtg_r24b_B.s_tmp);
          wr[vtg_r24b_B.i_f] = vtg_r24b_B.tr;
          wi[vtg_r24b_B.i_f] = vtg_r24b_B.h21;
          h[kdefl - 1] = vtg_r24b_B.tst;
          h[its] = vtg_r24b_B.bb;
          h[kdefl] = vtg_r24b_B.aa;
        }

        kdefl = 0;
        vtg_r24b_B.i_f = l - 2;
      }
    }
  }
}

// Function for MATLAB Function: '<S8>/MATLAB Function1'
static void vtg_r24b_xzlascl_p(real_T cfrom, real_T cto, int32_T m, int32_T n,
  real_T A[2], int32_T iA0, int32_T lda)
{
  boolean_T notdone;
  vtg_r24b_B.cfromc = cfrom;
  vtg_r24b_B.ctoc = cto;
  notdone = true;
  while (notdone) {
    real_T mul;
    vtg_r24b_B.cfrom1 = vtg_r24b_B.cfromc * 2.0041683600089728E-292;
    vtg_r24b_B.cto1 = vtg_r24b_B.ctoc / 4.9896007738368E+291;
    if ((fabs(vtg_r24b_B.cfrom1) > fabs(vtg_r24b_B.ctoc)) && (vtg_r24b_B.ctoc !=
         0.0)) {
      mul = 2.0041683600089728E-292;
      vtg_r24b_B.cfromc = vtg_r24b_B.cfrom1;
    } else if (fabs(vtg_r24b_B.cto1) > fabs(vtg_r24b_B.cfromc)) {
      mul = 4.9896007738368E+291;
      vtg_r24b_B.ctoc = vtg_r24b_B.cto1;
    } else {
      mul = vtg_r24b_B.ctoc / vtg_r24b_B.cfromc;
      notdone = false;
    }

    for (int32_T j = 0; j < n; j++) {
      int32_T offset;
      offset = (j * lda + iA0) - 2;
      for (int32_T b_i = 0; b_i < m; b_i++) {
        int32_T tmp;
        tmp = (b_i + offset) + 1;
        A[tmp] *= mul;
      }
    }
  }
}

// Function for MATLAB Function: '<S8>/MATLAB Function1'
static void vtg_r24b_xzlascl_p1(real_T cfrom, real_T cto, int32_T m, int32_T n,
  real_T *A)
{
  boolean_T notdone;
  vtg_r24b_B.cfromc_b = cfrom;
  vtg_r24b_B.ctoc_d = cto;
  notdone = true;
  while (notdone) {
    real_T cto1;
    real_T mul;
    vtg_r24b_B.cfrom1_e = vtg_r24b_B.cfromc_b * 2.0041683600089728E-292;
    cto1 = vtg_r24b_B.ctoc_d / 4.9896007738368E+291;
    if ((fabs(vtg_r24b_B.cfrom1_e) > fabs(vtg_r24b_B.ctoc_d)) &&
        (vtg_r24b_B.ctoc_d != 0.0)) {
      mul = 2.0041683600089728E-292;
      vtg_r24b_B.cfromc_b = vtg_r24b_B.cfrom1_e;
    } else if (fabs(cto1) > fabs(vtg_r24b_B.cfromc_b)) {
      mul = 4.9896007738368E+291;
      vtg_r24b_B.ctoc_d = cto1;
    } else {
      mul = vtg_r24b_B.ctoc_d / vtg_r24b_B.cfromc_b;
      notdone = false;
    }

    for (int32_T j = 0; j < n; j++) {
      for (int32_T i = 0; i < m; i++) {
        *A *= mul;
      }
    }
  }
}

// Function for MATLAB Function: '<S8>/MATLAB Function1'
static void vtg_r24b_xdlaev2(real_T a, real_T b, real_T c, real_T *rt1, real_T
  *rt2)
{
  real_T ab;
  real_T acmn;
  real_T acmx;
  vtg_r24b_B.sm = a + c;
  vtg_r24b_B.adf = fabs(a - c);
  ab = fabs(b + b);
  if (fabs(a) > fabs(c)) {
    acmx = a;
    acmn = c;
  } else {
    acmx = c;
    acmn = a;
  }

  if (vtg_r24b_B.adf > ab) {
    ab /= vtg_r24b_B.adf;
    vtg_r24b_B.adf *= sqrt(ab * ab + 1.0);
  } else if (vtg_r24b_B.adf < ab) {
    vtg_r24b_B.adf /= ab;
    vtg_r24b_B.adf = sqrt(vtg_r24b_B.adf * vtg_r24b_B.adf + 1.0) * ab;
  } else {
    vtg_r24b_B.adf = ab * 1.4142135623730951;
  }

  if (vtg_r24b_B.sm < 0.0) {
    *rt1 = (vtg_r24b_B.sm - vtg_r24b_B.adf) * 0.5;
    *rt2 = acmx / *rt1 * acmn - b / *rt1 * b;
  } else if (vtg_r24b_B.sm > 0.0) {
    *rt1 = (vtg_r24b_B.sm + vtg_r24b_B.adf) * 0.5;
    *rt2 = acmx / *rt1 * acmn - b / *rt1 * b;
  } else {
    *rt1 = 0.5 * vtg_r24b_B.adf;
    *rt2 = -0.5 * vtg_r24b_B.adf;
  }
}

// Function for MATLAB Function: '<S8>/MATLAB Function1'
static void vtg_r24b_insertionsort(real_T x[2], int32_T xstart, int32_T xend)
{
  for (int32_T k = xstart + 1; k <= xend; k++) {
    real_T xc;
    int32_T idx;
    boolean_T exitg1;
    xc = x[k - 1];
    idx = k - 1;
    exitg1 = false;
    while ((!exitg1) && (idx >= xstart)) {
      real_T tmp;
      tmp = x[idx - 1];
      if (xc < tmp) {
        x[idx] = tmp;
        idx--;
      } else {
        exitg1 = true;
      }
    }

    x[idx] = xc;
  }
}

// Function for MATLAB Function: '<S8>/MATLAB Function1'
static void vtg_r24b_xdlasrt(real_T d[2])
{
  vtg_r24b_insertionsort(d, 1, 2);
}

// Function for MATLAB Function: '<S8>/MATLAB Function1'
static int32_T vtg_r24b_xdsterf(real_T d[2], real_T e)
{
  int32_T exitg1;
  int32_T exitg3;
  int32_T exitg4;
  int32_T info;
  int32_T iscale;
  int32_T jtot;
  int32_T l;
  int32_T l1;
  int32_T lend;
  int32_T lendsv_tmp_tmp;
  int32_T lsv;
  int32_T m;
  int32_T n_tmp;
  boolean_T exitg2;
  info = 0;
  jtot = 0;
  l1 = 1;
  do {
    exitg1 = 0;
    if (l1 > 2) {
      vtg_r24b_xdlasrt(d);
      exitg1 = 1;
    } else {
      if (l1 > 1) {
        e = 0.0;
      }

      m = l1;
      exitg2 = false;
      while ((!exitg2) && (m < 2)) {
        if (fabs(e) <= sqrt(fabs(d[0])) * sqrt(fabs(d[1])) *
            2.2204460492503131E-16) {
          e = 0.0;
          exitg2 = true;
        } else {
          m = 2;
        }
      }

      l = l1;
      lsv = l1;
      lend = m;
      lendsv_tmp_tmp = m + 1;
      l1 = m + 1;
      if (m == l) {
      } else {
        n_tmp = m - l;
        if (n_tmp + 1 <= 0) {
          vtg_r24b_B.anorm = 0.0;
        } else {
          vtg_r24b_B.anorm = fabs(d[(l + n_tmp) - 1]);
          iscale = 0;
          exitg2 = false;
          while ((!exitg2) && (iscale <= n_tmp - 1)) {
            vtg_r24b_B.b_anorm = fabs(d[l - 1]);
            if (rtIsNaN(vtg_r24b_B.b_anorm)) {
              vtg_r24b_B.anorm = (rtNaN);
              exitg2 = true;
            } else {
              if (vtg_r24b_B.b_anorm > vtg_r24b_B.anorm) {
                vtg_r24b_B.anorm = vtg_r24b_B.b_anorm;
              }

              vtg_r24b_B.b_anorm = fabs(e);
              if (rtIsNaN(vtg_r24b_B.b_anorm)) {
                vtg_r24b_B.anorm = (rtNaN);
                exitg2 = true;
              } else {
                if (vtg_r24b_B.b_anorm > vtg_r24b_B.anorm) {
                  vtg_r24b_B.anorm = vtg_r24b_B.b_anorm;
                }

                iscale = 1;
              }
            }
          }
        }

        if (vtg_r24b_B.anorm == 0.0) {
        } else {
          iscale = 0;
          if (vtg_r24b_B.anorm > 2.2346346549904327E+153) {
            iscale = 1;
            vtg_r24b_xzlascl_p(vtg_r24b_B.anorm, 2.2346346549904327E+153, n_tmp
                               + 1, 1, d, l, 2);
            vtg_r24b_xzlascl_p1(vtg_r24b_B.anorm, 2.2346346549904327E+153, n_tmp,
                                1, &e);
          } else if (vtg_r24b_B.anorm < 3.02546243347603E-123) {
            iscale = 2;
            vtg_r24b_xzlascl_p(vtg_r24b_B.anorm, 3.02546243347603E-123, n_tmp +
                               1, 1, d, l, 2);
            vtg_r24b_xzlascl_p1(vtg_r24b_B.anorm, 3.02546243347603E-123, n_tmp,
                                1, &e);
          }

          for (n_tmp = l; n_tmp < m; n_tmp++) {
            e *= e;
          }

          if (fabs(d[m - 1]) < fabs(d[l - 1])) {
            lend = lsv;
            l = m;
          }

          if (lend >= l) {
            do {
              exitg4 = 0;
              if (l != lend) {
                m = l;
                while ((m < lend) && (!(fabs(e) <= fabs(d[m - 1]) *
                                        4.9303806576313238E-32 * fabs(d[m])))) {
                  m++;
                }
              } else {
                m = lend;
              }

              if (m < lend) {
                e = 0.0;
              }

              if (m == l) {
                l++;
                if (l > lend) {
                  exitg4 = 1;
                }
              } else if (l + 1 == m) {
                vtg_r24b_xdlaev2(d[l - 1], sqrt(e), d[l], &d[l - 1],
                                 &vtg_r24b_B.b_anorm);
                d[l] = vtg_r24b_B.b_anorm;
                e = 0.0;
                l += 2;
                if (l > lend) {
                  exitg4 = 1;
                }
              } else if (jtot == 60) {
                exitg4 = 1;
              } else {
                jtot++;
                vtg_r24b_B.rte = sqrt(e);
                vtg_r24b_B.s = d[l - 1];
                vtg_r24b_B.b_anorm = (d[l] - vtg_r24b_B.s) / (2.0 *
                  vtg_r24b_B.rte);
                vtg_r24b_B.b_gamma = vtg_r24b_rt_hypotd_snf(vtg_r24b_B.b_anorm,
                  1.0);
                if (!(vtg_r24b_B.b_anorm >= 0.0)) {
                  vtg_r24b_B.b_gamma = -vtg_r24b_B.b_gamma;
                }

                vtg_r24b_B.b_anorm = vtg_r24b_B.s - vtg_r24b_B.rte /
                  (vtg_r24b_B.b_anorm + vtg_r24b_B.b_gamma);
                vtg_r24b_B.rte = 1.0;
                vtg_r24b_B.s = 0.0;
                vtg_r24b_B.b_gamma = d[m - 1] - vtg_r24b_B.b_anorm;
                vtg_r24b_B.p_d = vtg_r24b_B.b_gamma * vtg_r24b_B.b_gamma;
                for (n_tmp = m - 1; n_tmp >= l; n_tmp--) {
                  vtg_r24b_B.bb_gu = e;
                  vtg_r24b_B.r = vtg_r24b_B.p_d + e;
                  if (m - 1 != n_tmp) {
                    e = vtg_r24b_B.s * vtg_r24b_B.r;
                  }

                  vtg_r24b_B.oldc = vtg_r24b_B.rte;
                  vtg_r24b_B.rte = vtg_r24b_B.p_d / vtg_r24b_B.r;
                  vtg_r24b_B.s = vtg_r24b_B.bb_gu / vtg_r24b_B.r;
                  vtg_r24b_B.p_d = vtg_r24b_B.b_gamma;
                  vtg_r24b_B.r = d[n_tmp - 1];
                  vtg_r24b_B.b_gamma = (vtg_r24b_B.r - vtg_r24b_B.b_anorm) *
                    vtg_r24b_B.rte - vtg_r24b_B.s * vtg_r24b_B.b_gamma;
                  d[n_tmp] = (vtg_r24b_B.r - vtg_r24b_B.b_gamma) +
                    vtg_r24b_B.p_d;
                  if (vtg_r24b_B.rte != 0.0) {
                    vtg_r24b_B.p_d = vtg_r24b_B.b_gamma * vtg_r24b_B.b_gamma /
                      vtg_r24b_B.rte;
                  } else {
                    vtg_r24b_B.p_d = vtg_r24b_B.oldc * vtg_r24b_B.bb_gu;
                  }
                }

                e = vtg_r24b_B.s * vtg_r24b_B.p_d;
                d[l - 1] = vtg_r24b_B.b_anorm + vtg_r24b_B.b_gamma;
              }
            } while (exitg4 == 0);
          } else {
            do {
              exitg3 = 0;
              m = l;
              while ((m > 1) && (!(fabs(e) <= fabs(d[m - 1]) *
                                   4.9303806576313238E-32 * fabs(d[m - 2])))) {
                m--;
              }

              if (m > 1) {
                e = 0.0;
              }

              if (m == l) {
                l--;
                if (l < 1) {
                  exitg3 = 1;
                }
              } else if (l - 1 == m) {
                vtg_r24b_xdlaev2(d[l - 1], sqrt(e), d[l - 2], &d[l - 1],
                                 &vtg_r24b_B.b_anorm);
                d[l - 2] = vtg_r24b_B.b_anorm;
                e = 0.0;
                exitg3 = 1;
              } else if (jtot == 60) {
                exitg3 = 1;
              } else {
                jtot++;
                vtg_r24b_B.rte = sqrt(e);
                vtg_r24b_B.s = d[l - 1];
                vtg_r24b_B.b_anorm = (d[l - 2] - vtg_r24b_B.s) / (2.0 *
                  vtg_r24b_B.rte);
                vtg_r24b_B.b_gamma = vtg_r24b_rt_hypotd_snf(vtg_r24b_B.b_anorm,
                  1.0);
                if (!(vtg_r24b_B.b_anorm >= 0.0)) {
                  vtg_r24b_B.b_gamma = -vtg_r24b_B.b_gamma;
                }

                vtg_r24b_B.b_anorm = vtg_r24b_B.s - vtg_r24b_B.rte /
                  (vtg_r24b_B.b_anorm + vtg_r24b_B.b_gamma);
                vtg_r24b_B.rte = 1.0;
                vtg_r24b_B.s = 0.0;
                vtg_r24b_B.b_gamma = d[m - 1] - vtg_r24b_B.b_anorm;
                vtg_r24b_B.p_d = vtg_r24b_B.b_gamma * vtg_r24b_B.b_gamma;
                for (lend = m; lend < l; lend++) {
                  vtg_r24b_B.bb_gu = e;
                  vtg_r24b_B.r = vtg_r24b_B.p_d + e;
                  if (lend != m) {
                    e = vtg_r24b_B.s * vtg_r24b_B.r;
                  }

                  vtg_r24b_B.oldc = vtg_r24b_B.rte;
                  vtg_r24b_B.rte = vtg_r24b_B.p_d / vtg_r24b_B.r;
                  vtg_r24b_B.s = vtg_r24b_B.bb_gu / vtg_r24b_B.r;
                  vtg_r24b_B.p_d = vtg_r24b_B.b_gamma;
                  vtg_r24b_B.b_gamma = (d[lend] - vtg_r24b_B.b_anorm) *
                    vtg_r24b_B.rte - vtg_r24b_B.s * vtg_r24b_B.b_gamma;
                  d[lend - 1] = (d[lend] - vtg_r24b_B.b_gamma) + vtg_r24b_B.p_d;
                  if (vtg_r24b_B.rte != 0.0) {
                    vtg_r24b_B.p_d = vtg_r24b_B.b_gamma * vtg_r24b_B.b_gamma /
                      vtg_r24b_B.rte;
                  } else {
                    vtg_r24b_B.p_d = vtg_r24b_B.oldc * vtg_r24b_B.bb_gu;
                  }
                }

                e = vtg_r24b_B.s * vtg_r24b_B.p_d;
                d[l - 1] = vtg_r24b_B.b_anorm + vtg_r24b_B.b_gamma;
              }
            } while (exitg3 == 0);
          }

          switch (iscale) {
           case 1:
            vtg_r24b_xzlascl_p(2.2346346549904327E+153, vtg_r24b_B.anorm,
                               lendsv_tmp_tmp - lsv, 1, d, lsv, 2);
            break;

           case 2:
            vtg_r24b_xzlascl_p(3.02546243347603E-123, vtg_r24b_B.anorm,
                               lendsv_tmp_tmp - lsv, 1, d, lsv, 2);
            break;
          }

          if (jtot >= 60) {
            if (e != 0.0) {
              info = 1;
            }

            exitg1 = 1;
          }
        }
      }
    }
  } while (exitg1 == 0);

  return info;
}

// Function for MATLAB Function: '<S8>/MATLAB Function1'
static void vtg_r24b_ordeig(const real_T A[16], creal_T E[4])
{
  int32_T exitg1;
  int32_T exitg2;
  boolean_T exitg3;
  boolean_T guard1;
  boolean_T scalea;
  scalea = true;
  for (vtg_r24b_B.k = 0; vtg_r24b_B.k < 16; vtg_r24b_B.k++) {
    if (scalea) {
      vtg_r24b_B.b_anrm = A[vtg_r24b_B.k];
      if (rtIsInf(vtg_r24b_B.b_anrm) || rtIsNaN(vtg_r24b_B.b_anrm)) {
        scalea = false;
      }
    }
  }

  if (!scalea) {
    E[0].re = (rtNaN);
    E[0].im = 0.0;
    E[1].re = (rtNaN);
    E[1].im = 0.0;
    E[2].re = (rtNaN);
    E[2].im = 0.0;
    E[3].re = (rtNaN);
    E[3].im = 0.0;
  } else {
    vtg_r24b_B.k = 0;
    do {
      exitg1 = 0;
      if (vtg_r24b_B.k + 1 <= 4) {
        guard1 = false;
        if (vtg_r24b_B.k + 1 != 4) {
          vtg_r24b_B.At_tmp = (vtg_r24b_B.k << 2) + vtg_r24b_B.k;
          vtg_r24b_B.b_anrm = A[vtg_r24b_B.At_tmp + 1];
          if (vtg_r24b_B.b_anrm != 0.0) {
            vtg_r24b_B.At[0] = A[vtg_r24b_B.At_tmp];
            vtg_r24b_B.At_tmp = ((vtg_r24b_B.k + 1) << 2) + vtg_r24b_B.k;
            vtg_r24b_B.At[2] = A[vtg_r24b_B.At_tmp];
            vtg_r24b_B.At[1] = vtg_r24b_B.b_anrm;
            vtg_r24b_B.At[3] = A[vtg_r24b_B.At_tmp + 1];
            scalea = true;
            if (rtIsInf(vtg_r24b_B.At[0]) || rtIsNaN(vtg_r24b_B.At[0])) {
              scalea = false;
            }

            if (scalea && (rtIsInf(vtg_r24b_B.b_anrm) || rtIsNaN
                           (vtg_r24b_B.b_anrm))) {
              scalea = false;
            }

            if (scalea && (rtIsInf(vtg_r24b_B.At[2]) || rtIsNaN(vtg_r24b_B.At[2])))
            {
              scalea = false;
            }

            if (scalea && (rtIsInf(vtg_r24b_B.At[3]) || rtIsNaN(vtg_r24b_B.At[3])))
            {
              scalea = false;
            }

            if (!scalea) {
              vtg_r24b_B.etemp[0].re = (rtNaN);
              vtg_r24b_B.etemp[0].im = 0.0;
              vtg_r24b_B.etemp[1].re = (rtNaN);
              vtg_r24b_B.etemp[1].im = 0.0;
            } else {
              scalea = true;
              vtg_r24b_B.At_tmp = 0;
              exitg3 = false;
              while ((!exitg3) && (vtg_r24b_B.At_tmp < 2)) {
                vtg_r24b_B.i_j = 0;
                do {
                  exitg2 = 0;
                  if (vtg_r24b_B.i_j <= vtg_r24b_B.At_tmp) {
                    if (!(vtg_r24b_B.At[(vtg_r24b_B.At_tmp << 1) +
                          vtg_r24b_B.i_j] == vtg_r24b_B.At[(vtg_r24b_B.i_j << 1)
                          + vtg_r24b_B.At_tmp])) {
                      scalea = false;
                      exitg2 = 1;
                    } else {
                      vtg_r24b_B.i_j++;
                    }
                  } else {
                    vtg_r24b_B.At_tmp++;
                    exitg2 = 2;
                  }
                } while (exitg2 == 0);

                if (exitg2 == 1) {
                  exitg3 = true;
                }
              }

              if (scalea) {
                vtg_r24b_B.b_anrm = 0.0;
                vtg_r24b_B.At_tmp = 0;
                exitg3 = false;
                while ((!exitg3) && (vtg_r24b_B.At_tmp < 2)) {
                  vtg_r24b_B.i_j = 0;
                  do {
                    exitg2 = 0;
                    if (vtg_r24b_B.i_j <= vtg_r24b_B.At_tmp) {
                      vtg_r24b_B.absxk = fabs(vtg_r24b_B.At[(vtg_r24b_B.At_tmp <<
                        1) + vtg_r24b_B.i_j]);
                      if (rtIsNaN(vtg_r24b_B.absxk)) {
                        vtg_r24b_B.b_anrm = (rtNaN);
                        exitg2 = 1;
                      } else {
                        if (vtg_r24b_B.absxk > vtg_r24b_B.b_anrm) {
                          vtg_r24b_B.b_anrm = vtg_r24b_B.absxk;
                        }

                        vtg_r24b_B.i_j++;
                      }
                    } else {
                      vtg_r24b_B.At_tmp++;
                      exitg2 = 2;
                    }
                  } while (exitg2 == 0);

                  if (exitg2 == 1) {
                    exitg3 = true;
                  }
                }

                if (rtIsInf(vtg_r24b_B.b_anrm) || rtIsNaN(vtg_r24b_B.b_anrm)) {
                  vtg_r24b_B.wr[0] = (rtNaN);
                  vtg_r24b_B.wr[1] = (rtNaN);
                } else {
                  scalea = false;
                  if ((vtg_r24b_B.b_anrm > 0.0) && (vtg_r24b_B.b_anrm <
                       1.0010415475915505E-146)) {
                    scalea = true;
                    vtg_r24b_B.b_anrm = 1.0010415475915505E-146 /
                      vtg_r24b_B.b_anrm;
                    vtg_r24b_xzlascl(1.0, vtg_r24b_B.b_anrm, 2, 2, vtg_r24b_B.At,
                                     1, 2);
                  } else if (vtg_r24b_B.b_anrm > 9.9895953610111751E+145) {
                    scalea = true;
                    vtg_r24b_B.b_anrm = 9.9895953610111751E+145 /
                      vtg_r24b_B.b_anrm;
                    vtg_r24b_xzlascl(1.0, vtg_r24b_B.b_anrm, 2, 2, vtg_r24b_B.At,
                                     1, 2);
                  }

                  vtg_r24b_B.wr[0] = vtg_r24b_B.At[0];
                  vtg_r24b_B.wr[1] = vtg_r24b_B.At[3];
                  vtg_r24b_B.At_tmp = vtg_r24b_xdsterf(vtg_r24b_B.wr,
                    vtg_r24b_B.At[1]);
                  if (vtg_r24b_B.At_tmp != 0) {
                    vtg_r24b_B.wr[0] = (rtNaN);
                    vtg_r24b_B.wr[1] = (rtNaN);
                  } else if (scalea) {
                    vtg_r24b_B.b_anrm = 1.0 / vtg_r24b_B.b_anrm;
                    vtg_r24b_B.wr[0] *= vtg_r24b_B.b_anrm;
                    vtg_r24b_B.wr[1] *= vtg_r24b_B.b_anrm;
                  }
                }

                vtg_r24b_B.etemp[0].re = vtg_r24b_B.wr[0];
                vtg_r24b_B.etemp[0].im = 0.0;
                vtg_r24b_B.etemp[1].re = vtg_r24b_B.wr[1];
                vtg_r24b_B.etemp[1].im = 0.0;
              } else {
                scalea = true;
                vtg_r24b_B.At_tmp = 0;
                exitg3 = false;
                while ((!exitg3) && (vtg_r24b_B.At_tmp < 2)) {
                  vtg_r24b_B.i_j = 0;
                  do {
                    exitg2 = 0;
                    if (vtg_r24b_B.i_j <= vtg_r24b_B.At_tmp) {
                      if (!(vtg_r24b_B.At[(vtg_r24b_B.At_tmp << 1) +
                            vtg_r24b_B.i_j] == -vtg_r24b_B.At[(vtg_r24b_B.i_j <<
                            1) + vtg_r24b_B.At_tmp])) {
                        scalea = false;
                        exitg2 = 1;
                      } else {
                        vtg_r24b_B.i_j++;
                      }
                    } else {
                      vtg_r24b_B.At_tmp++;
                      exitg2 = 2;
                    }
                  } while (exitg2 == 0);

                  if (exitg2 == 1) {
                    exitg3 = true;
                  }
                }

                if (scalea) {
                  vtg_r24b_xzgehrd(vtg_r24b_B.At, 1, 2);
                  vtg_r24b_xdlahqr(1, 2, vtg_r24b_B.At, &vtg_r24b_B.At_tmp,
                                   vtg_r24b_B.wr, vtg_r24b_B.wi);
                  for (vtg_r24b_B.i_j = 0; vtg_r24b_B.i_j < vtg_r24b_B.At_tmp;
                       vtg_r24b_B.i_j++) {
                    vtg_r24b_B.etemp[vtg_r24b_B.i_j].re = (rtNaN);
                    vtg_r24b_B.etemp[vtg_r24b_B.i_j].im = 0.0;
                  }

                  for (vtg_r24b_B.i_j = vtg_r24b_B.At_tmp + 1; vtg_r24b_B.i_j <
                       3; vtg_r24b_B.i_j++) {
                    vtg_r24b_B.etemp[vtg_r24b_B.i_j - 1].re = 0.0;
                    vtg_r24b_B.etemp[vtg_r24b_B.i_j - 1].im =
                      vtg_r24b_B.wi[vtg_r24b_B.i_j - 1];
                  }
                } else {
                  vtg_r24b_B.b_anrm = 0.0;
                  vtg_r24b_B.At_tmp = 0;
                  exitg3 = false;
                  while ((!exitg3) && (vtg_r24b_B.At_tmp < 4)) {
                    vtg_r24b_B.absxk = fabs(vtg_r24b_B.At[vtg_r24b_B.At_tmp]);
                    if (rtIsNaN(vtg_r24b_B.absxk)) {
                      vtg_r24b_B.b_anrm = (rtNaN);
                      exitg3 = true;
                    } else {
                      if (vtg_r24b_B.absxk > vtg_r24b_B.b_anrm) {
                        vtg_r24b_B.b_anrm = vtg_r24b_B.absxk;
                      }

                      vtg_r24b_B.At_tmp++;
                    }
                  }

                  if (rtIsInf(vtg_r24b_B.b_anrm) || rtIsNaN(vtg_r24b_B.b_anrm))
                  {
                    vtg_r24b_B.etemp[0].re = (rtNaN);
                    vtg_r24b_B.etemp[0].im = 0.0;
                    vtg_r24b_B.etemp[1].re = (rtNaN);
                    vtg_r24b_B.etemp[1].im = 0.0;
                  } else {
                    vtg_r24b_B.absxk = vtg_r24b_B.b_anrm;
                    scalea = false;
                    if ((vtg_r24b_B.b_anrm > 0.0) && (vtg_r24b_B.b_anrm <
                         6.7178761075670888E-139)) {
                      scalea = true;
                      vtg_r24b_B.absxk = 6.7178761075670888E-139;
                      vtg_r24b_xzlascl(vtg_r24b_B.b_anrm, vtg_r24b_B.absxk, 2, 2,
                                       vtg_r24b_B.At, 1, 2);
                    } else if (vtg_r24b_B.b_anrm > 1.4885657073574029E+138) {
                      scalea = true;
                      vtg_r24b_B.absxk = 1.4885657073574029E+138;
                      vtg_r24b_xzlascl(vtg_r24b_B.b_anrm, vtg_r24b_B.absxk, 2, 2,
                                       vtg_r24b_B.At, 1, 2);
                    }

                    vtg_r24b_xzgebal('\x42', vtg_r24b_B.At, &vtg_r24b_B.At_tmp,
                                     &vtg_r24b_B.ihi, vtg_r24b_B.wr);
                    vtg_r24b_xzgehrd(vtg_r24b_B.At, vtg_r24b_B.At_tmp,
                                     vtg_r24b_B.ihi);
                    vtg_r24b_xdlahqr(vtg_r24b_B.At_tmp, vtg_r24b_B.ihi,
                                     vtg_r24b_B.At, &vtg_r24b_B.i_j,
                                     vtg_r24b_B.wr, vtg_r24b_B.wi);
                    if (scalea) {
                      vtg_r24b_xzlascl_p(vtg_r24b_B.absxk, vtg_r24b_B.b_anrm, 2
                                         - vtg_r24b_B.i_j, 1, vtg_r24b_B.wr,
                                         vtg_r24b_B.i_j + 1, 2);
                      vtg_r24b_xzlascl_p(vtg_r24b_B.absxk, vtg_r24b_B.b_anrm, 2
                                         - vtg_r24b_B.i_j, 1, vtg_r24b_B.wi,
                                         vtg_r24b_B.i_j + 1, 2);
                      if (vtg_r24b_B.i_j != 0) {
                        vtg_r24b_xzlascl_p(vtg_r24b_B.absxk, vtg_r24b_B.b_anrm,
                                           vtg_r24b_B.At_tmp - 1, 1,
                                           vtg_r24b_B.wr, 1, 2);
                        vtg_r24b_xzlascl_p(vtg_r24b_B.absxk, vtg_r24b_B.b_anrm,
                                           vtg_r24b_B.At_tmp - 1, 1,
                                           vtg_r24b_B.wi, 1, 2);
                      }
                    }

                    if (vtg_r24b_B.i_j != 0) {
                      for (vtg_r24b_B.ihi = vtg_r24b_B.At_tmp; vtg_r24b_B.ihi <=
                           vtg_r24b_B.i_j; vtg_r24b_B.ihi++) {
                        vtg_r24b_B.wr[vtg_r24b_B.ihi - 1] = (rtNaN);
                        vtg_r24b_B.wi[vtg_r24b_B.ihi - 1] = 0.0;
                      }
                    }

                    vtg_r24b_B.etemp[0].re = vtg_r24b_B.wr[0];
                    vtg_r24b_B.etemp[0].im = vtg_r24b_B.wi[0];
                    vtg_r24b_B.etemp[1].re = vtg_r24b_B.wr[1];
                    vtg_r24b_B.etemp[1].im = vtg_r24b_B.wi[1];
                  }
                }
              }
            }

            E[vtg_r24b_B.k] = vtg_r24b_B.etemp[0];
            E[vtg_r24b_B.k + 1] = vtg_r24b_B.etemp[1];
            vtg_r24b_B.k += 2;
          } else {
            guard1 = true;
          }
        } else {
          guard1 = true;
        }

        if (guard1) {
          E[vtg_r24b_B.k].re = A[(vtg_r24b_B.k << 2) + vtg_r24b_B.k];
          E[vtg_r24b_B.k].im = 0.0;
          vtg_r24b_B.k++;
        }
      } else {
        exitg1 = 1;
      }
    } while (exitg1 == 0);
  }
}

// Model step function
void vtg_r24b_step(void)
{
  boolean_T b_varargout_1;

  // Outputs for Atomic SubSystem: '<Root>/Subscribe'
  // MATLABSystem: '<S5>/SourceBlock'
  b_varargout_1 = Sub_vtg_r24b_1.getLatestMessage
    (&vtg_r24b_B.rtb_SourceBlock_o2_d_b);

  // Outputs for Enabled SubSystem: '<S5>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S9>/Enable'

  // Start for MATLABSystem: '<S5>/SourceBlock'
  if (b_varargout_1) {
    // SignalConversion generated from: '<S9>/In1'
    vtg_r24b_B.In1_m = vtg_r24b_B.rtb_SourceBlock_o2_d_b;
  }

  // End of Start for MATLABSystem: '<S5>/SourceBlock'
  // End of Outputs for SubSystem: '<S5>/Enabled Subsystem'
  // End of Outputs for SubSystem: '<Root>/Subscribe'

  // Outputs for Atomic SubSystem: '<Root>/Subscribe2'
  // MATLABSystem: '<S7>/SourceBlock'
  b_varargout_1 = Sub_vtg_r24b_48.getLatestMessage
    (&vtg_r24b_B.rtb_SourceBlock_o2_d_b);

  // Outputs for Enabled SubSystem: '<S7>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S11>/Enable'

  // Start for MATLABSystem: '<S7>/SourceBlock'
  if (b_varargout_1) {
    // SignalConversion generated from: '<S11>/In1'
    vtg_r24b_B.In1 = vtg_r24b_B.rtb_SourceBlock_o2_d_b;
  }

  // End of Start for MATLABSystem: '<S7>/SourceBlock'
  // End of Outputs for SubSystem: '<S7>/Enabled Subsystem'
  // End of Outputs for SubSystem: '<Root>/Subscribe2'

  // MATLABSystem: '<Root>/Get Parameter1'
  ParamGet_vtg_r24b_19.get_parameter(&vtg_r24b_B.b_value);

  // MATLABSystem: '<Root>/Get Parameter'
  ParamGet_vtg_r24b_18.get_parameter(&vtg_r24b_B.b_value_k);

  // MATLABSystem: '<Root>/Get Parameter2'
  ParamGet_vtg_r24b_52.get_parameter(&vtg_r24b_B.b_value_c);

  // MATLAB Function: '<S8>/MATLAB Function1' incorporates:
  //   Constant: '<S8>/rho_s'
  //   Constant: '<S8>/rho_v'
  //   MATLAB Function: '<S8>/MATLAB Function3'
  //   MATLAB Function: '<S8>/MATLAB Function4'
  //   MATLABSystem: '<Root>/Get Parameter'
  //   MATLABSystem: '<Root>/Get Parameter1'
  //   MATLABSystem: '<Root>/Get Parameter2'
  //
  vtg_r24b_B.Asys[1] = vtg_r24b_B.b_value;
  vtg_r24b_B.Asys[3] = -vtg_r24b_B.b_value * vtg_r24b_B.b_value_k -
    vtg_r24b_B.b_value_c;
  vtg_r24b_B.Csys[0] = 0.2;
  vtg_r24b_B.Csys[3] = 0.0;
  vtg_r24b_B.Csys[1] = 0.0;
  vtg_r24b_B.Csys[4] = 0.5;
  vtg_r24b_B.Asys[0] = 0.0;
  vtg_r24b_B.Csys[2] = 0.0;
  vtg_r24b_B.Asys[2] = -1.0;
  vtg_r24b_B.Csys[5] = 0.0;
  vtg_r24b_B.Bsys[0] = 1.0;
  vtg_r24b_B.Bsys[1] = vtg_r24b_B.b_value_c;
  vtg_r24b_B.Bsys[2] = 0.0;
  vtg_r24b_B.Bsys_tmp = vtg_r24b_B.In1.Data + vtg_r24b_B.In1_m.Data;
  vtg_r24b_B.Bsys[3] = vtg_r24b_B.Bsys_tmp * -vtg_r24b_B.b_value;
  for (vtg_r24b_B.i = 0; vtg_r24b_B.i < 2; vtg_r24b_B.i++) {
    vtg_r24b_B.Y_b = vtg_r24b_B.Bsys[vtg_r24b_B.i] / -1.10803324099723;
    vtg_r24b_B.a21 = vtg_r24b_B.Bsys[vtg_r24b_B.i + 2] - vtg_r24b_B.Y_b * 0.0;
    vtg_r24b_B.Y_b -= vtg_r24b_B.a21 * -0.0;
    vtg_r24b_B.Y[vtg_r24b_B.i] = -(vtg_r24b_B.a21 * 0.0 + vtg_r24b_B.Y_b);
    vtg_r24b_B.Y[vtg_r24b_B.i + 2] = -(vtg_r24b_B.a21 * vtg_r24b_B.Bsys[3] +
      vtg_r24b_B.Y_b * vtg_r24b_B.b_value_c);
  }

  for (vtg_r24b_B.i = 0; vtg_r24b_B.i < 2; vtg_r24b_B.i++) {
    for (vtg_r24b_B.P_tmp = 0; vtg_r24b_B.P_tmp < 2; vtg_r24b_B.P_tmp++) {
      vtg_r24b_B.Bsys[vtg_r24b_B.i + (vtg_r24b_B.P_tmp << 1)] =
        -((vtg_r24b_B.Csys[3 * vtg_r24b_B.i + 1] * vtg_r24b_B.Csys[3 *
           vtg_r24b_B.P_tmp + 1] + vtg_r24b_B.Csys[3 * vtg_r24b_B.i] *
           vtg_r24b_B.Csys[3 * vtg_r24b_B.P_tmp]) + vtg_r24b_B.Csys[3 *
          vtg_r24b_B.i + 2] * vtg_r24b_B.Csys[3 * vtg_r24b_B.P_tmp + 2]);
      vtg_r24b_B.r2 = (vtg_r24b_B.i << 1) + vtg_r24b_B.P_tmp;
      vtg_r24b_B.TT[vtg_r24b_B.P_tmp + (vtg_r24b_B.i << 2)] =
        vtg_r24b_B.Asys[vtg_r24b_B.r2];
      vtg_r24b_B.TT[vtg_r24b_B.P_tmp + ((vtg_r24b_B.i + 2) << 2)] =
        vtg_r24b_B.Y[vtg_r24b_B.r2];
    }
  }

  vtg_r24b_B.TT[2] = vtg_r24b_B.Bsys[0];
  vtg_r24b_B.TT[10] = -0.0;
  vtg_r24b_B.TT[3] = vtg_r24b_B.Bsys[1];
  vtg_r24b_B.TT[11] = 1.0;
  vtg_r24b_B.TT[6] = vtg_r24b_B.Bsys[2];
  vtg_r24b_B.TT[14] = -vtg_r24b_B.b_value;
  vtg_r24b_B.TT[7] = vtg_r24b_B.Bsys[3];
  vtg_r24b_B.TT[15] = -vtg_r24b_B.Asys[3];
  vtg_r24b_schur_l(vtg_r24b_B.TT, vtg_r24b_B.U_out);
  vtg_r24b_ordeig(vtg_r24b_B.TT, vtg_r24b_B.b);
  for (vtg_r24b_B.i = 0; vtg_r24b_B.i < 8; vtg_r24b_B.i++) {
    vtg_r24b_B.SELECT[vtg_r24b_B.i] = false;
  }

  vtg_r24b_B.SELECT[0] = (vtg_r24b_B.b[0].re < 0.0);
  vtg_r24b_B.SELECT[1] = (vtg_r24b_B.b[1].re < 0.0);
  vtg_r24b_B.SELECT[2] = (vtg_r24b_B.b[2].re < 0.0);
  vtg_r24b_B.SELECT[3] = (vtg_r24b_B.b[3].re < 0.0);

  // End of MATLAB Function: '<S8>/MATLAB Function1'

  // MATLAB Function: '<S8>/MATLAB Function3'
  ordschur_reorder(4, &vtg_r24b_B.TT[0], &vtg_r24b_B.U_out[0],
                   &vtg_r24b_B.SELECT[0]);

  // Outputs for Atomic SubSystem: '<Root>/Subscribe1'
  // MATLABSystem: '<S6>/SourceBlock'
  b_varargout_1 = Sub_vtg_r24b_2.getLatestMessage
    (&vtg_r24b_B.rtb_SourceBlock_o2_d_b);

  // Outputs for Enabled SubSystem: '<S6>/Enabled Subsystem' incorporates:
  //   EnablePort: '<S10>/Enable'

  // Start for MATLABSystem: '<S6>/SourceBlock'
  if (b_varargout_1) {
    // SignalConversion generated from: '<S10>/In1'
    vtg_r24b_B.In1_j = vtg_r24b_B.rtb_SourceBlock_o2_d_b;
  }

  // End of Start for MATLABSystem: '<S6>/SourceBlock'
  // End of Outputs for SubSystem: '<S6>/Enabled Subsystem'
  // End of Outputs for SubSystem: '<Root>/Subscribe1'

  // MATLABSystem: '<Root>/Get Parameter3'
  ParamGet_vtg_r24b_54.get_parameter(&vtg_r24b_B.Y_b);

  // MATLAB Function: '<S8>/MATLAB Function4' incorporates:
  //   MATLABSystem: '<Root>/Get Parameter'
  //   MATLABSystem: '<Root>/Get Parameter1'
  //   MATLABSystem: '<Root>/Get Parameter2'
  //   MATLABSystem: '<Root>/Get Parameter3'
  //
  if (fabs(vtg_r24b_B.U_out[1]) > fabs(vtg_r24b_B.U_out[0])) {
    vtg_r24b_B.i = 1;
    vtg_r24b_B.r2 = 0;
  } else {
    vtg_r24b_B.i = 0;
    vtg_r24b_B.r2 = 1;
  }

  vtg_r24b_B.a21 = vtg_r24b_B.U_out[vtg_r24b_B.r2] /
    vtg_r24b_B.U_out[vtg_r24b_B.i];
  vtg_r24b_B.a22_tmp = vtg_r24b_B.U_out[vtg_r24b_B.i + 4];
  vtg_r24b_B.a22 = vtg_r24b_B.U_out[vtg_r24b_B.r2 + 4] - vtg_r24b_B.a22_tmp *
    vtg_r24b_B.a21;
  vtg_r24b_B.P_tmp = vtg_r24b_B.i << 1;
  vtg_r24b_B.P[vtg_r24b_B.P_tmp] = vtg_r24b_B.U_out[2] /
    vtg_r24b_B.U_out[vtg_r24b_B.i];
  vtg_r24b_B.r2 <<= 1;
  vtg_r24b_B.P[vtg_r24b_B.r2] = (vtg_r24b_B.U_out[6] -
    vtg_r24b_B.P[vtg_r24b_B.P_tmp] * vtg_r24b_B.a22_tmp) / vtg_r24b_B.a22;
  vtg_r24b_B.P[vtg_r24b_B.P_tmp] -= vtg_r24b_B.P[vtg_r24b_B.r2] * vtg_r24b_B.a21;
  vtg_r24b_B.P[vtg_r24b_B.P_tmp + 1] = vtg_r24b_B.U_out[3] /
    vtg_r24b_B.U_out[vtg_r24b_B.i];
  vtg_r24b_B.P[vtg_r24b_B.r2 + 1] = (vtg_r24b_B.U_out[7] -
    vtg_r24b_B.P[vtg_r24b_B.P_tmp + 1] * vtg_r24b_B.a22_tmp) / vtg_r24b_B.a22;
  vtg_r24b_B.P[vtg_r24b_B.P_tmp + 1] -= vtg_r24b_B.P[vtg_r24b_B.r2 + 1] *
    vtg_r24b_B.a21;
  vtg_r24b_B.a21 = -vtg_r24b_B.b_value * vtg_r24b_B.In1_m.Data;
  vtg_r24b_B.b_value_k -= (vtg_r24b_B.In1_j.Data - (vtg_r24b_B.b_value_k *
    vtg_r24b_B.Bsys_tmp + vtg_r24b_B.Y_b)) * (0.0 * vtg_r24b_B.P[0] +
    vtg_r24b_B.a21 * vtg_r24b_B.P[1]) + (0.0 * vtg_r24b_B.P[2] + vtg_r24b_B.a21 *
    vtg_r24b_B.P[3]) * (vtg_r24b_B.In1_m.Data - vtg_r24b_B.Bsys_tmp);
  if (!(vtg_r24b_B.b_value_k >= 0.0)) {
    vtg_r24b_B.b_value_k = 0.0;
  }

  vtg_r24b_B.b_value = ((vtg_r24b_B.In1_j.Data - vtg_r24b_B.Y_b) -
                        vtg_r24b_B.b_value_k * vtg_r24b_B.In1_m.Data) *
    vtg_r24b_B.b_value + vtg_r24b_B.b_value_c * vtg_r24b_B.In1.Data;

  // Saturate: '<S8>/Saturation'
  if (vtg_r24b_B.b_value > 1.5) {
    // BusAssignment: '<Root>/Bus Assignment'
    vtg_r24b_B.BusAssignment.Data = 1.5;
  } else if (vtg_r24b_B.b_value < -3.0) {
    // BusAssignment: '<Root>/Bus Assignment'
    vtg_r24b_B.BusAssignment.Data = -3.0;
  } else {
    // BusAssignment: '<Root>/Bus Assignment'
    vtg_r24b_B.BusAssignment.Data = vtg_r24b_B.b_value;
  }

  // End of Saturate: '<S8>/Saturation'

  // Outputs for Atomic SubSystem: '<Root>/Publish'
  // MATLABSystem: '<S3>/SinkBlock'
  Pub_vtg_r24b_9.publish(&vtg_r24b_B.BusAssignment);

  // End of Outputs for SubSystem: '<Root>/Publish'

  // BusAssignment: '<Root>/Bus Assignment1' incorporates:
  //   MATLAB Function: '<S8>/MATLAB Function4'

  vtg_r24b_B.BusAssignment1.Data = vtg_r24b_B.b_value_k;

  // Outputs for Atomic SubSystem: '<Root>/Publish1'
  // MATLABSystem: '<S4>/SinkBlock'
  Pub_vtg_r24b_75.publish(&vtg_r24b_B.BusAssignment1);

  // End of Outputs for SubSystem: '<Root>/Publish1'
}

// Model initialize function
void vtg_r24b_initialize(void)
{
  // Registration code

  // initialize non-finites
  rt_InitInfAndNaN(sizeof(real_T));

  {
    int32_T i;
    char_T b_zeroDelimTopic[16];
    char_T b_zeroDelimTopic_0[10];
    char_T b_zeroDelimName_0[9];
    char_T b_zeroDelimTopic_2[8];
    char_T b_zeroDelimTopic_1[6];
    char_T b_zeroDelimName[4];
    char_T b_zeroDelimName_1[3];
    static const char_T b_zeroDelimTopic_3[16] = "car/state/vel_x";
    static const char_T b_zeroDelimTopic_4[10] = "cmd_accel";
    static const char_T b_zeroDelimTopic_5[6] = "tau_i";
    static const char_T b_zeroDelimTopic_6[8] = "rel_vel";
    static const char_T b_zeroDelimTopic_7[10] = "lead_dist";
    static const char_T b_zeroDelimName_2[9] = "tau_star";

    // SystemInitialize for Atomic SubSystem: '<Root>/Subscribe'
    // Start for MATLABSystem: '<S5>/SourceBlock'
    vtg_r24b_DW.obj_nfc.matlabCodegenIsDeleted = false;
    vtg_r24b_DW.obj_nfc.isInitialized = 1;
    for (i = 0; i < 16; i++) {
      b_zeroDelimTopic[i] = b_zeroDelimTopic_3[i];
    }

    Sub_vtg_r24b_1.createSubscriber(&b_zeroDelimTopic[0], 1);
    vtg_r24b_DW.obj_nfc.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S5>/SourceBlock'
    // End of SystemInitialize for SubSystem: '<Root>/Subscribe'

    // SystemInitialize for Atomic SubSystem: '<Root>/Publish'
    // Start for MATLABSystem: '<S3>/SinkBlock'
    vtg_r24b_DW.obj_nf.matlabCodegenIsDeleted = false;
    vtg_r24b_DW.obj_nf.isInitialized = 1;
    for (i = 0; i < 10; i++) {
      b_zeroDelimTopic_0[i] = b_zeroDelimTopic_4[i];
    }

    Pub_vtg_r24b_9.createPublisher(&b_zeroDelimTopic_0[0], 1);
    vtg_r24b_DW.obj_nf.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S3>/SinkBlock'
    // End of SystemInitialize for SubSystem: '<Root>/Publish'

    // SystemInitialize for Atomic SubSystem: '<Root>/Publish1'
    // Start for MATLABSystem: '<S4>/SinkBlock'
    vtg_r24b_DW.obj_a.matlabCodegenIsDeleted = false;
    vtg_r24b_DW.obj_a.isInitialized = 1;
    for (i = 0; i < 6; i++) {
      b_zeroDelimTopic_1[i] = b_zeroDelimTopic_5[i];
    }

    Pub_vtg_r24b_75.createPublisher(&b_zeroDelimTopic_1[0], 1);
    vtg_r24b_DW.obj_a.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S4>/SinkBlock'
    // End of SystemInitialize for SubSystem: '<Root>/Publish1'

    // SystemInitialize for Atomic SubSystem: '<Root>/Subscribe2'
    // Start for MATLABSystem: '<S7>/SourceBlock'
    vtg_r24b_DW.obj_j.matlabCodegenIsDeleted = false;
    vtg_r24b_DW.obj_j.isInitialized = 1;
    for (i = 0; i < 8; i++) {
      b_zeroDelimTopic_2[i] = b_zeroDelimTopic_6[i];
    }

    Sub_vtg_r24b_48.createSubscriber(&b_zeroDelimTopic_2[0], 1);
    vtg_r24b_DW.obj_j.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S7>/SourceBlock'
    // End of SystemInitialize for SubSystem: '<Root>/Subscribe2'

    // SystemInitialize for Atomic SubSystem: '<Root>/Subscribe1'
    // Start for MATLABSystem: '<S6>/SourceBlock'
    vtg_r24b_DW.obj_gv.matlabCodegenIsDeleted = false;
    vtg_r24b_DW.obj_gv.isInitialized = 1;
    for (i = 0; i < 10; i++) {
      b_zeroDelimTopic_0[i] = b_zeroDelimTopic_7[i];
    }

    Sub_vtg_r24b_2.createSubscriber(&b_zeroDelimTopic_0[0], 1);
    vtg_r24b_DW.obj_gv.isSetupComplete = true;

    // End of Start for MATLABSystem: '<S6>/SourceBlock'
    // End of SystemInitialize for SubSystem: '<Root>/Subscribe1'

    // Start for MATLABSystem: '<Root>/Get Parameter1'
    vtg_r24b_DW.obj_n.matlabCodegenIsDeleted = false;
    vtg_r24b_DW.obj_n.isInitialized = 1;
    b_zeroDelimName[0] = 'k';
    b_zeroDelimName[1] = '1';
    b_zeroDelimName[2] = 'i';
    b_zeroDelimName[3] = '\x00';
    ParamGet_vtg_r24b_19.initialize(&b_zeroDelimName[0]);
    ParamGet_vtg_r24b_19.initialize_error_codes(0, 1, 2, 3);
    ParamGet_vtg_r24b_19.set_initial_value(1.1);
    vtg_r24b_DW.obj_n.isSetupComplete = true;

    // Start for MATLABSystem: '<Root>/Get Parameter'
    vtg_r24b_DW.obj_e.matlabCodegenIsDeleted = false;
    vtg_r24b_DW.obj_e.isInitialized = 1;
    for (i = 0; i < 9; i++) {
      b_zeroDelimName_0[i] = b_zeroDelimName_2[i];
    }

    ParamGet_vtg_r24b_18.initialize(&b_zeroDelimName_0[0]);
    ParamGet_vtg_r24b_18.initialize_error_codes(0, 1, 2, 3);
    ParamGet_vtg_r24b_18.set_initial_value(2.0);
    vtg_r24b_DW.obj_e.isSetupComplete = true;

    // End of Start for MATLABSystem: '<Root>/Get Parameter'

    // Start for MATLABSystem: '<Root>/Get Parameter2'
    vtg_r24b_DW.obj_g.matlabCodegenIsDeleted = false;
    vtg_r24b_DW.obj_g.isInitialized = 1;
    b_zeroDelimName[0] = 'k';
    b_zeroDelimName[1] = '2';
    b_zeroDelimName[2] = 'i';
    b_zeroDelimName[3] = '\x00';
    ParamGet_vtg_r24b_52.initialize(&b_zeroDelimName[0]);
    ParamGet_vtg_r24b_52.initialize_error_codes(0, 1, 2, 3);
    ParamGet_vtg_r24b_52.set_initial_value(0.1);
    vtg_r24b_DW.obj_g.isSetupComplete = true;

    // Start for MATLABSystem: '<Root>/Get Parameter3'
    vtg_r24b_DW.obj.matlabCodegenIsDeleted = false;
    vtg_r24b_DW.obj.isInitialized = 1;
    b_zeroDelimName_1[0] = 's';
    b_zeroDelimName_1[1] = '0';
    b_zeroDelimName_1[2] = '\x00';
    ParamGet_vtg_r24b_54.initialize(&b_zeroDelimName_1[0]);
    ParamGet_vtg_r24b_54.initialize_error_codes(0, 1, 2, 3);
    ParamGet_vtg_r24b_54.set_initial_value(0.1);
    vtg_r24b_DW.obj.isSetupComplete = true;
  }
}

// Model terminate function
void vtg_r24b_terminate(void)
{
  // Terminate for Atomic SubSystem: '<Root>/Subscribe'
  // Terminate for MATLABSystem: '<S5>/SourceBlock'
  if (!vtg_r24b_DW.obj_nfc.matlabCodegenIsDeleted) {
    vtg_r24b_DW.obj_nfc.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S5>/SourceBlock'
  // End of Terminate for SubSystem: '<Root>/Subscribe'

  // Terminate for Atomic SubSystem: '<Root>/Subscribe2'
  // Terminate for MATLABSystem: '<S7>/SourceBlock'
  if (!vtg_r24b_DW.obj_j.matlabCodegenIsDeleted) {
    vtg_r24b_DW.obj_j.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S7>/SourceBlock'
  // End of Terminate for SubSystem: '<Root>/Subscribe2'

  // Terminate for MATLABSystem: '<Root>/Get Parameter1'
  if (!vtg_r24b_DW.obj_n.matlabCodegenIsDeleted) {
    vtg_r24b_DW.obj_n.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<Root>/Get Parameter1'

  // Terminate for MATLABSystem: '<Root>/Get Parameter'
  if (!vtg_r24b_DW.obj_e.matlabCodegenIsDeleted) {
    vtg_r24b_DW.obj_e.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<Root>/Get Parameter'

  // Terminate for MATLABSystem: '<Root>/Get Parameter2'
  if (!vtg_r24b_DW.obj_g.matlabCodegenIsDeleted) {
    vtg_r24b_DW.obj_g.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<Root>/Get Parameter2'

  // Terminate for Atomic SubSystem: '<Root>/Subscribe1'
  // Terminate for MATLABSystem: '<S6>/SourceBlock'
  if (!vtg_r24b_DW.obj_gv.matlabCodegenIsDeleted) {
    vtg_r24b_DW.obj_gv.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S6>/SourceBlock'
  // End of Terminate for SubSystem: '<Root>/Subscribe1'

  // Terminate for MATLABSystem: '<Root>/Get Parameter3'
  if (!vtg_r24b_DW.obj.matlabCodegenIsDeleted) {
    vtg_r24b_DW.obj.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<Root>/Get Parameter3'

  // Terminate for Atomic SubSystem: '<Root>/Publish'
  // Terminate for MATLABSystem: '<S3>/SinkBlock'
  if (!vtg_r24b_DW.obj_nf.matlabCodegenIsDeleted) {
    vtg_r24b_DW.obj_nf.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S3>/SinkBlock'
  // End of Terminate for SubSystem: '<Root>/Publish'

  // Terminate for Atomic SubSystem: '<Root>/Publish1'
  // Terminate for MATLABSystem: '<S4>/SinkBlock'
  if (!vtg_r24b_DW.obj_a.matlabCodegenIsDeleted) {
    vtg_r24b_DW.obj_a.matlabCodegenIsDeleted = true;
  }

  // End of Terminate for MATLABSystem: '<S4>/SinkBlock'
  // End of Terminate for SubSystem: '<Root>/Publish1'
}

const char_T* RT_MODEL_vtg_r24b_T::getErrorStatus() const
{
  return (errorStatus);
}

void RT_MODEL_vtg_r24b_T::setErrorStatus(const char_T* const volatile
  aErrorStatus)
{
  (errorStatus = aErrorStatus);
}

//
// File trailer for generated code.
//
// [EOF]
//
