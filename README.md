# vtg_acc_real: A variable time gap Adaptive Cruise Control (ACC) controller implemented in MATLAB/Simulink.


## `VTG_ACC_Controller` Block

The `VTG_ACC_Controller` block  takes spacing, speed, and relative velocity as inputs and outputs an acceleration command alongside a variable time gap command.

### Inputs

| Port       | Value / Source | Unit  | Description                                                              |
|------------|----------------|-------|--------------------------------------------------------------------------|
| `sn`       | signal         | m     | Space gap between ego and lead vehicle                                   |
| `vn`       | signal         | m/s   | Ego vehicle speed                                                        |
| `sndot`    | signal         | m/s   | Relative velocity, defined as `v_lead - v_ego`                           |
| `k1`       | 0.23           | -     | Controller spacing gain                                                  |
| `k2`       | 0.07           | -     | Controller velocity gain                                                 |
| `s0`       | 3              | m     | Standstill distance (minimum gap at rest)                                |
| `tau_star` | 1.2 or 2.0     | s     | Desired nominal time gap                                                 |

### Outputs

| Port        | Unit            | Description                                              |
|-------------|-----------------|----------------------------------------------------------|
| `cmd_accel` | m/s<sup>2</sup> | Commanded acceleration sent to the ego vehicle           |
| `tau`       | s               | Variable time gap command computed by the controller     |

### Simulink Models

| Model                                                                   | Description                                           |
|-------------------------------------------------------------------------|-------------------------------------------------------|
| [`vtg_sim_r24b.slx`](simulink/vtg_sim_r24b.slx)                         | Car-following simulation                              |
| [`vtg_sim_r24b_testing.slx`](simulink/testing/vtg_sim_r24b_testing.slx) | Car-following simulation with Test 6 scenario harness |
| [`vtg_r24b.slx`](simulink/vtg_r24b.slx)                                 | Simulink-based ROS node                               |


## Algorithm Overview

The controller is based on a **variable time gap (VTG) policy** combined with an **H∞ optimal control** formulation, solved in real-time via Schur decomposition as a drop-in replacement for `icare` (which is not code-generation compatible).

The algorithm runs in three stages:

**Stage 1: Hamiltonian Construction (`vtg_acc_fcn1`)**  
The spacing error dynamics are linearized around the nominal policy  $s^* = s_0 + \tau^* v_e$. A Hamiltonian matrix $Z$ is built from the system matrices and cost weights, and its **Schur decomposition** $Z = UTU^\top$ is computed. </br>
The stable eigenvalues are identified for reordering in Stage 2.


**Stage 2: Schur Reordering (`call_ordschur` + `ordschur_wrapper.c`)**  
Since MATLAB's `ordschur` is not compatible with Simulink code generation, a custom C wrapper calls **LAPACK's `dtrsen`** routine directly to reorder the Schur form, placing the stable eigenvalues in the leading block of $T$. </br>
Also, optimal workspace is queried for **LAPACK's `dtrsen`** at first to avoid ill-conditioned reordering.


**Stage 3: Control Law & Failsafe (`vtg_acc_fcn2`)**  
The stabilizing Riccati solution $P = U_{21} U_{11}^{-1}$ is recovered from the  reordered Schur vectors, and used to compute the optimal time gap correction $u$. </br>
A **failsafe check** validates the decomposition at each timestep; if it fails, the controller falls back to the nominal time gap $\tau^*$. The final outputs are: </br>
$$\tau = \max(\tau^* + u,\ 0)$$
$$a_{cmd} = k_1(s_n - s_0 - \tau_i v_n) + k_2 v_{rel}$$



## Tests & Results

Objective: Validate the Schur-based ARE solution as a replacement for MATLAB's `icare`, and verify controller correctness across a range of operating conditions.

---

### Test 1: — ARE Solution Accuracy & Residual
**Platform:** MATLAB script [`test_are_accuracy.m`](matlab/testing/test_are_accuracy.m) 

The Schur-based solution $P$ was swept over a grid of realistic operating points:
- `vn` ∈ [1, 35] m/s in steps of 0.1
- `vrel` ∈ [−10, 10] m/s in steps of 0.1

| Metric                             | Value      |
|------------------------------------|------------|
| Max error vs `icare` (`max_P_err`) | 7.1463e-15 |
| Max ARE residual norm              | 5.1882e-15 |

- $P$ was symmetric at machine precision for all operating points
- All eigenvalues of $P$ were strictly positive

$\checkmark$ equivalent with `icare` across all tested operating points

<!--- Both metrics are well below the 1e-10 threshold, confirming numerical equivalence with `icare` across all tested operating points. --->

---

### Test 2: Failsafe Never Triggers
**Platform:** MATLAB script [`test_failsafe.m`](matlab/testing/test_failsafe.m) 

The failsafe condition was monitored across the same operating point sweep (`vn` ∈ [1, 35] m/s, `vrel` ∈ [−10, 10] m/s). </br>
$\checkmark$ The failsafe was never triggered across all **68,541 operating points**.

---

### Test 3: Edge Cases
**Platform:** MATLAB script [`test_edgecases.m`](matlab/testing/test_edgecases.m) 

Nine edge cases were tested covering near-zero relative velocity, extreme spacing, 
near-zero ego speed, and lead speed approaching zero. All cases passed with errors 
well below the 1e-10 threshold:

| Case                    | P_err    | ARE_res  | sym_err  | min_eig  | PD? |
|-------------------------|----------|----------|----------|----------|-----|
| Near-zero `vrel`        | 1.71e-15 | 1.25e-15 | 7.07e-16 | 7.85e-02 | $\checkmark$ |
| Large +`vrel`           | 8.14e-16 | 1.03e-15 | 4.71e-16 | 6.07e-02 | $\checkmark$ |
| Large −`vrel`           | 2.15e-16 | 4.09e-16 | 5.89e-17 | 1.02e-01 | $\checkmark$ |
| Near-zero `vn`          | 1.57e-15 | 2.44e-16 | 1.06e-15 | 2.19e-01 | $\checkmark$ |
| Very small gap          | 9.98e-16 | 9.49e-16 | 1.77e-16 | 7.85e-02 | $\checkmark$ |
| Very large gap          | 9.98e-16 | 9.49e-16 | 1.77e-16 | 7.85e-02 | $\checkmark$ |
| High speed              | 2.44e-16 | 1.26e-15 | 9.81e-18 | 4.84e-02 | $\checkmark$ |
| Low speed               | 1.52e-15 | 3.87e-16 | 1.18e-16 | 1.68e-01 | $\checkmark$ |
| `vn` + `vrel` near zero | 7.47e-15 | 7.90e-16 | 2.24e-15 | 2.20e-01 | $\checkmark$ |


---

### Test 4: Numerical Conditioning
**Platform:** MATLAB script [`test_edgecases.m`](matlab/testing/test_edgecases.m) 

The conditioning of the Hamiltonian $Z$, the Schur vector block $U_{11}$, and the  Riccati solution $P$ were monitored across the operating point grid (`vn` ∈ [0.1, 40] m/s, `vrel` ∈ [−10, 10] m/s). All cases passed with no ill-conditioning detected (threshold: `cond > 1e10`):

| Metric      | Max Value |
|-------------|-----------|
| `cond(Z)`   | 3.27e+03  |
| `cond(U11)` | 1.45e+00  |
| `cond(P)`   | 5.03e+00  |

Notably, `cond(U11)` and `cond(P)` remain very small across all operating points, confirming that the Schur decomposition produces a well-conditioned solution even as `cond(Z)` grows at higher speeds. $\checkmark$

---

### Test 5: Real-Time Performance
**Platform:** Simulink Profiler [`vtg_sim_r24b_testing.slx`](simulink/testing/vtg_sim_r24b_testing.slx) and [`perf_test.m`](simulink/testing/perf_test.m) 

The execution time of each controller block was measured over 6,013 calls with a control loop budget of 50 ms:

| Block                                    | Self (ms/call) | % Budget |
|------------------------------------------|----------------|----------|
| `vtg_acc_fcn1` (Hamiltonian + Schur)     | 0.020          | —        |
| `call_ordschur` (Schur reordering)       | 0.005          | —        |
| `vtg_acc_fcn2` (control law + failsafe)  | 0.001          | —        |
| **Controller total**                     | **0.026**      | **0.1%** |

The full pipeline completes in **0.026 ms per call**, using only **0.1% of the 50 ms sample time budget**. $\checkmark$

---

### Test 6: Scenario Tests
**Platform:** Simulink [`vtg_sim_r24b_testing.slx`](simulink/testing/vtg_sim_r24b_testing.slx) and [`post_sim_test.m`](simulink/testing/post_sim_test.m) 

Six driving scenarios were tested. Safety and performance metrics are reported for each. [Figures](simulink/testing/figures)  for timeseries can also be accessed.

#### **Normal Cruising**

| Metric | Value | Threshold | Status |
|---|---|---|---|
| Min TTC | 21.46 s | > 1.5 s | $\checkmark$ |
| Max DRAC | 0.03 m/s² | < 3.35 m/s² | $\checkmark$ |
| Min Gap | 3.26 m | > 3.0 m | $\checkmark$ |
| Settling Time | 3.65 s | — | — |
| Overshoot | 18.19 % | — | — |
| RMS Accel | 0.65 m/s² | — | — |
| RMS Jerk | 0.78 m/s³ | — | — |
<!---| Max Jerk | 7.66 m/s³ | — | ⚠️ |--->

#### **Hard Braking**

| Metric | Value | Threshold | Status |
|---|---|---|---|
| Min TTC | 1.92 s | > 1.5 s | $\checkmark$ |
| Max DRAC | 0.81 m/s² | < 3.35 m/s² | $\checkmark$ |
| Min Gap | 1.13 m | > 3.0 m | !! due to sharp deceleration (-3 m/s²) |
| RMS Accel | 1.12 m/s² | — | — |
| RMS Jerk | 0.83 m/s³ | — | — |
<!---| Settling Time | 3.75 s | — | — |--->
<!---| Overshoot | 29.02 % | — | — |--->
<!---| Max Jerk | 7.66 m/s³ | — | ⚠️ |--->

#### **Hard Braking Pulse**

| Metric | Value | Threshold | Status |
|---|---|---|---|
| Min TTC | 7.08 s | > 1.5 s | $\checkmark$ |
| Max DRAC | 0.21 m/s² | < 3.35 m/s² | $\checkmark$ |
| Min Gap | 3.26 m | > 3.0 m | $\checkmark$ |
| RMS Accel | 0.87 m/s² | — | — |
| RMS Jerk | 0.89 m/s³ | — | — |
<!---| Settling Time | 3.70 s | — | — |--->
<!---| Overshoot | 22.62 % | — | — |--->
<!---| Max Jerk | 7.66 m/s³ | — | ⚠️ |--->

#### **Stop and Go**

| Metric | Value | Threshold | Status |
|---|---|---|---|
| Min TTC | 1.94 s | > 1.5 s | $\checkmark$ |
| Max DRAC | 0.79 m/s² | < 3.35 m/s² | $\checkmark$ |
| Min Gap | 2.11 m | > 3.0 m | !! due to sharp deceleration (-2 m/s²)|
| Settling Time | 3.75 s | — | — |
| Overshoot | 78.73 % | — | — |
| RMS Accel | 1.30 m/s² | — | — |
| RMS Jerk | 1.01 m/s³ | — | — |
<!---| Max Jerk | 7.66 m/s³ | — | ⚠️ |--->

#### **Cut-in**

Simulate a vehicle cutting in at close range by stepping `sn` to a small value at `t=10s`
```
sn_actual = sn - 15*(t >= 10)   % gap suddenly drops by 15m
```

| Metric | Value | Threshold | Status |
|---|---|---|---|
| Min TTC | 21.46 s | > 1.5 s | $\checkmark$ |
| Max DRAC | 0.03 m/s² | < 3.35 m/s² | $\checkmark$ |
| Min Gap | 3.26 m | > 3.0 m | $\checkmark$ |
| RMS Accel | 0.87 m/s² | — | — |
| RMS Jerk | 2.20 m/s³ | — | — |
<!---| Settling Time | 3.65 s | — | — |--->
<!---| Overshoot | 18.19 % | — | — |--->
<!---| Max Jerk | 61.40 m/s³ | — | ⚠️ |--->

#### **Cut-out**

Lead vehicle disappears at `t=10s`, ego should accelerate back to free-flow speed. Simulate by stepping `sn` to a large value:
```
sn_actual = sn + 100*(t >= 10)   % lead vehicle effectively gone
```

| Metric | Value | Threshold | Status |
|---|---|---|---|
| Min TTC | 8.58 s | > 1.5 s | $\checkmark$ |
| Max DRAC | 0.26 m/s² | < 3.35 m/s² | $\checkmark$ |
| Min Gap | 3.26 m | > 3.0 m | $\checkmark$ |
| RMS Accel | 0.79 m/s² | — | — |
| RMS Jerk | 1.24 m/s³ | — | — |
<!---| Settling Time | 3.65 s | — | — |--->
<!---| Overshoot | 366.22 % | — | — |--->
<!---| Max Jerk | 28.60 m/s³ | — | ⚠️ |--->

