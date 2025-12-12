#include "ordschur_wrapper.h"
#include <lapacke.h>

int ordschur_reorder(
    const int n,
    double* T,
    double* Q,
    const int* select_in
)
{
    /* LAPACKE wants char flags */
    char job = 'N';     /* do NOT compute condition numbers */
    char compq = 'V';   /* update Q */

    lapack_logical* select = (lapack_logical*)malloc(2*n * sizeof(lapack_logical));
    for (lapack_int i = 0; i < 2*n; i++) {
        select[i] = (lapack_logical)select_in[i];
    }

    /* LAPACK workspace */
    double* wr = (double*)malloc(n * sizeof(double));
    double* wi = (double*)malloc(n * sizeof(double));
    int m = 1;          /* output: number of selected eigenvalues */
    double s = 0.0;     /* condition number (unused) */
    double sep = 0.0;
    lapack_int lwork  = n;
    double* work      = (double*)malloc(lwork * sizeof(double));

    lapack_int liwork = n;
    lapack_logical* iwork =
        (lapack_logical*)malloc(liwork * sizeof(lapack_logical));

    /* LAPACKE uses row-major by default for LAPACKE_* functions */
    int info = LAPACKE_dtrsen_work(
        LAPACK_COL_MAJOR,
        job,
        compq,
        select,
        n,
        T,
        n,
        Q,
        n,
        wr,
        wi,
        &m,
        &s,
        &sep,
        work,
        lwork,
        iwork,
        liwork
    );

    free(wr);
    free(wi);

    info = info + 2;

    return info;
}
