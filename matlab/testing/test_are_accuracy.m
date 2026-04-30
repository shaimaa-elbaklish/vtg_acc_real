%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Test 1: Unit Test: ARE Solution Accuracy
% - Sweep over realistic operating points (vn, vrel ranges)
% - Compare P from Schur decomposition against icare
% - Log P_err and info for each operating point
% Test 2: Unit Test: ARE Residual
% - Verify P satisfies the ARE directly (don't just compare to icare)
% - Check residual norm < 1e-10
% Test 3: P Symmetry and Positive Definiteness
% - Verify P is symmetric (norm(P - P') < 1e-10)
% - Verify P is positive definite (all eigenvalues > 0)
% - Note: symmetrization P = 0.5*(P+P') was removed, verify it holds naturally
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
clear all; close all; clc;

% ── Parameters ────────────────────────────────────────────────────────────
k1      = 0.23;
k2      = 0.07;
tau_star= 1.2;
s0      = 3.0;
rho_s   = 0.2;
rho_v   = 0.5;
rho_u   = 1.0;
gamma   = 0.95;

% ── Sweep ─────────────────────────────────────────────────────────────────
% vn_range   = [5, 10, 15, 20, 25, 30];    % m/s
% vrel_range = [-5, -2, 0, 2, 5];          % m/s

vn_range   = 1:0.1:35;            % m/s
vrel_range = -10:0.1:10;          % m/s
tol = 1e-10;

fprintf('\n%-6s %-6s %-12s %-12s %-12s %-12s %-10s\n', ...
        'vn', 'vrel', 'P_err', 'ARE_residual', 'sym_err', 'min_eig', 'PD?');
fprintf('%s\n', repmat('-',1,70));

max_P_err = -1;
max_ARE_residual = -1;

for vn = vn_range
    for vrel = vrel_range
        if vrel + vn < 0
            continue
        end

        % ── Your pipeline ─────────────────────────────────────────────
        [TT, UU, SELECT2] = vtg_acc_fcn1(vn, vrel, k1, tau_star, k2, ...
                                          rho_s, rho_v, rho_u, gamma);
        [T_out, U_out, info] = ordschur_mex(TT, UU, SELECT2);
        % --- Replacement for icare(A, B, Q, R) -----------------------------------
        P_schur = zeros(2, 2);
        [m,n] = size(U_out);
        U11 = U_out(1:(m/2), 1:(n/2));
        U21 = U_out((m/2+1):m, 1:(n/2));
        P_schur = U21/U11;

        % ── icare reference ───────────────────────────────────────────
        Asys  = [0 -1; k1 (-k1*tau_star-k2)];
        Bdist = [1; k2];
        Csys  = [rho_s 0; 0 rho_v; 0 0];
        Ru    = rho_u^2;
        Rmat  = [-1/gamma^2 0; 0 inv(Ru)];
        ve    = vrel + vn;
        Bctrl = [0; -k1*ve];
        Bsys  = [Bdist, Bctrl];
        Qmat  = Csys'*Csys;
        P_icare = icare(Asys, Bsys, Qmat, Rmat, [], [], []);

        % ── Compare ───────────────────────────────────────────────────
        P_err = norm(P_schur - P_icare, 'fro');
        % fprintf('%-6.1f %-6.1f %-12.2e %-6d\n', vn, vrel, err, info);
        if P_err > max_P_err
            max_P_err = P_err;
        end

        % ── ARE Residual ───────────────────────────────────────────────
        % P must satisfy: A'P + PA - P*B*inv(R)*B'*P + Q = 0
        ARE_residual = norm(Asys'*P_schur + P_schur*Asys ...
                          - P_schur*Bsys/Rmat*Bsys'*P_schur ...
                          + Qmat, 'fro');
        if ARE_residual > max_ARE_residual
            max_ARE_residual = ARE_residual;
        end

        % ── Symmetry ──────────────────────────────────────────────────
        sym_err = norm(P_schur - P_schur', 'fro');

        % ── Positive Definiteness ─────────────────────────────────────
        eigP    = eig(P_schur);
        min_eig = min(eigP);
        is_PD   = all(eigP > 0);

        % ── Assert ────────────────────────────────────────────────────
        if P_err >= tol || ARE_residual >= tol
            fprintf('%-6.1f %-6.1f %-12.2e %-6d\n', vn, vrel, err, info);
        end
        if sym_err > tol || ~is_PD
            fprintf('%-6.1f %-6.1f %-12.2e %-12.2e %-12.2e %-12.2e %-10s\n', ...
                 vn, vrel, P_err, ARE_residual, sym_err, min_eig, string(is_PD));
        end

        assert(ARE_residual < tol, ...
               sprintf('ARE residual too large at vn=%g vrel=%g: %.2e', ...
                        vn, vrel, ARE_residual));
        assert(sym_err < 1e-10, ...
               sprintf('P not symmetric at vn=%g vrel=%g: sym_err=%.2e', ...
                        vn, vrel, sym_err));
        assert(is_PD, ...
               sprintf('P not positive definite at vn=%g vrel=%g: min_eig=%.2e', ...
                        vn, vrel, min_eig));

    end
end
fprintf('\nAll Tests 1-3 PASSED\n');
