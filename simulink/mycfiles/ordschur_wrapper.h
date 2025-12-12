#ifndef ORDSCHUR_WRAPPER_H
#define ORDSCHUR_WRAPPER_H

extern int ordschur_reorder(
    const int n,
    double* T,       /* n x n, input/output */
    double* Q,       /* n x n, input/output */
    const int* select_in     /* eigenvalues selector */
);

#endif
