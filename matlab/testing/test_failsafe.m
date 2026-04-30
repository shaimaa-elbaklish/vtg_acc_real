%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Test 4: Failsafe Never Triggers
% - Log diagT over full simulation run
% - Verify failsafe condition never activates
% - Monitor as Simulink signal (should always be false)
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

% ── Test 4: Failsafe Never Triggers ──────────────────────────────────────
fprintf('\n%-6s %-6s %-12s %-10s\n', 'vn', 'vrel', 'diagT(1:2)', 'Failsafe?');
fprintf('%s\n', repmat('-',1,45));

failsafe_count = 0;
total_count = 0;

for vn = vn_range
    for vrel = vrel_range

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

        % ── Check failsafe condition ───────────────────────────────────
        diagT = diag(T_out);
        n     = length(diagT)/2;
        failsafe_triggered = ~(all(diagT(1:n) < 0) && all(diagT(n+1:end) > 0));

        total_count    = total_count + 1;
        failsafe_count = failsafe_count + failsafe_triggered;

        if failsafe_triggered
            fprintf('%-6.1f %-6.1f [%-5.3f, %-5.3f] %-10s\n', ...
                 vn, vrel, diagT(1), diagT(2), string(failsafe_triggered));
        end

        assert(~failsafe_triggered, ...
               sprintf('Failsafe triggered at vn=%g vrel=%g', vn, vrel));
    end
end

fprintf('\nTest 4 PASSED: Failsafe never triggered (%d/%d operating points)\n', ...
         failsafe_count, total_count);