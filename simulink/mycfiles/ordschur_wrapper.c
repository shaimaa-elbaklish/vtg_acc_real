#include "ordschur_wrapper.h"
#include <lapacke.h>

int ordschur_reorder(
    const int n, 
    double* T, 
    double* Q, 
    const int* select_in
) {
    char job = 'N';
    char compq = 'V';

    lapack_logical* select = (lapack_logical*)malloc(n * sizeof(lapack_logical));
    for (lapack_int i = 0; i < n; i++) {
        select[i] = (lapack_logical)select_in[i];
    }

    double* wr = (double*)malloc(n * sizeof(double));
    double* wi = (double*)malloc(n * sizeof(double));
    lapack_int m = 0;
    double s = 0.0;
    double sep = 0.0;
    lapack_int liwork = n;
    lapack_int* iwork = (lapack_int*)malloc(liwork * sizeof(lapack_int)); // Fix 3: correct type

    /* --- Fix 1: Query optimal lwork first --- */
    double work_query;
    lapack_int lwork_query = -1;
    LAPACKE_dtrsen_work(
        LAPACK_COL_MAJOR, job, compq, select,
        n, T, n, Q, n,
        wr, wi, &m, &s, &sep,
        &work_query, lwork_query,
        iwork, liwork
    );
    lapack_int lwork = (lapack_int)work_query;
    double* work = (double*)malloc(lwork * sizeof(double));

    /* --- Actual call --- */
    int info = LAPACKE_dtrsen_work(
        LAPACK_COL_MAJOR, job, compq, select,
        n, T, n, Q, n,
        wr, wi, &m, &s, &sep,
        work, lwork,
        iwork, liwork
    );

    free(select); free(work); free(iwork); free(wr); free(wi);

    /* Fix 2: Return actual info, not hardcoded 25 */
    return (int)info;
}
