#include "mex.h"
#include "ordschur_wrapper.h"

void mexFunction(int nlhs, mxArray *plhs[], int nrhs, const mxArray *prhs[])
{
    /* Inputs: T (4x4), Q (4x4), select (4x1 int32) */
    int n = (int)mxGetM(prhs[0]);
    
    /* Copy inputs - dtrsen modifies in place */
    plhs[0] = mxDuplicateArray(prhs[0]);  /* T_out */
    plhs[1] = mxDuplicateArray(prhs[1]);  /* U_out */
    
    double* T      = mxGetPr(plhs[0]);
    double* Q      = mxGetPr(plhs[1]);
    int*    select = (int*)mxGetData(prhs[2]);
    
    int info = ordschur_reorder(n, T, Q, select);
    
    /* Return info as 3rd output */
    plhs[2] = mxCreateDoubleScalar((double)info);
}