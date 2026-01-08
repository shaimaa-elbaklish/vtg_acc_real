#ifndef ORDSCHUR_WRAPPER_H
#define ORDSCHUR_WRAPPER_H

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

int ordschur_reorder(
    const int n,
    double* T,       /* n x n, input/output */
    double* Q,       /* n x n, input/output */
    const int* select_in     /* eigenvalues selector */
);
    
#ifdef __cplusplus
}
#endif

#endif
