# ACC Without icare - Testing Plan

## Test 1: Unit Test: ARE Solution Accuracy
- Sweep over realistic operating points (vn, vrel ranges)
- Compare P from Schur decomposition against icare
- Log P_err and info for each operating point
- **Platform: MATLAB command window**
```
mex -I"C:\Users\ShaimaaElBaklish\Documents\GitHub\vtg_acc_real\simulink\mycfiles" ...
-lmwlapack -lmwblas ...
"C:\Users\ShaimaaElBaklish\Documents\GitHub\vtg_acc_real\simulink\mycfiles\ordschur_mex.c" ...
"C:\Users\ShaimaaElBaklish\Documents\GitHub\vtg_acc_real\simulink\mycfiles\ordschur_wrapper.c"
```

## Test 2: Unit Test: ARE Residual
- Verify P satisfies the ARE directly (don't just compare to icare)
- Check residual norm < 1e-10
- **Platform: MATLAB command window**

## Test 3: P Symmetry and Positive Definiteness
- Verify P is symmetric (norm(P - P') < 1e-10)
- Verify P is positive definite (all eigenvalues > 0)
- Note: symmetrization P = 0.5*(P+P') was removed, verify it holds naturally
- **Platform: MATLAB command window**

## Test 4: Failsafe Never Triggers
- Log diagT over full simulation run
- Verify failsafe condition never activates
- Monitor as Simulink signal (should always be false)
- **Platform: Simulink**

## Test 5: Scenario Tests in Simulink
- Cut-in: preceding vehicle suddenly appears at close range
- Cut-out: preceding vehicle suddenly disappears
- Hard braking: preceding vehicle decelerates sharply
- Slow lead vehicle: ego vehicle approaching from highway speed
- Stop and go: repeated acceleration/deceleration cycles
- For each verify: no overshoot, cmd_accel within limits, Time_Gap_Comm >= 0, smooth convergence
- **Platform: Simulink**

## Test 6: Edge Cases
- Near-zero relative velocity (vrel = 0.001)
- Very small spacing (sn = s0 + 0.1)
- Very large spacing (sn = s0 + 100)
- vn near zero (vn = 0.1)
- **Platform: MATLAB command window + Simulink**

## Test 7: Numerical Conditioning Check
- Monitor cond(Z) throughout simulation
- Flag if Hamiltonian is ill-conditioned (cond > 1e10)
- **Platform: Simulink (as logged signal)**

**Tabled: Conditioning Guards (implement after testing complete)**

- Guard 1: cond(U11) > 1e6 → use previous P
- Guard 2: Tikhonov regularization on U11: P = U21/(U11 + lambda*eye)
- Guard 3: cond(Z) > 1e8 → skip recomputing P, use previous
- Guard 4: P positive definiteness check → revert to previous P if fails
- Guard 5: ARE residual check (offline monitoring only, too expensive for real-time)
- Guard 6: NaN/Inf check on P (cheapest, always worth having)
- Recommended combo: Guards 1 + 6 + 4 with persistent Pmat_prev
- Note: verify 'persistent' keyword compatibility with Simulink codegen
```
% In vtg_acc_fcn2:
persistent Pmat_prev
if isempty(Pmat_prev)
    Pmat_prev = eye(2);  % safe initialization
end

[m, n] = size(Umat);
U11 = Umat(1:(m/2), 1:(n/2));
U21 = Umat((m/2+1):m, 1:(n/2));

% Guard 1: cond(U11)
if cond(U11) > 1e6
    Pmat = Pmat_prev;
% Guard 6: NaN/Inf
elseif any(isnan(U11(:))) || any(isnan(U21(:)))
    Pmat = Pmat_prev;
else
    Pmat = U21/U11;
    % Guard 4: positive definiteness
    if any(eig(Pmat) <= 0)
        Pmat = Pmat_prev;
    else
        Pmat_prev = Pmat;  % update only when good
    end
end
```

## Test 8: Real-Time Performance Test
- Measure execution time of each function block
- Verify pipeline completes within control loop period
- Check for memory allocation issues (malloc in C on every timestep)
- Consider pre-allocating C workspace as static arrays for real-time deployment:
  static double wr[4], wi[4], work[64];
  static lapack_int iwork[4];
  static lapack_logical select[4];
- **Platform: Simulink + ROS (future step)**