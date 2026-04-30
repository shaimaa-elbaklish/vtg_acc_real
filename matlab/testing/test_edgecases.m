%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Test 6: Edge Cases
% - Near-zero relative velocity (vrel = 0.001)
% - Very small spacing (sn = s0 + 0.1)
% - Very large spacing (sn = s0 + 100)
% - vn near zero (vn = 0.1)
% Test 7: Numerical Conditioning Check
% - Monitor cond(Z) throughout simulation
% - Flag if Hamiltonian is ill-conditioned (cond > 1e10)
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

fprintf('%-25s %-12s %-12s %-12s %-12s %-10s\n', ...
        'Case', 'P_err', 'ARE_res', 'sym_err', 'min_eig', 'PD?');
fprintf('%s\n', repmat('-',1,75));

% Use nominal parameters
vn_nom   = 20;
vrel_nom = 0;

edge_cases = {
% label                vn      vrel     sn
'Near-zero vrel',      20,     0.001,   27;
'Large +vrel',         20,     10,      27;
'Large -vrel',         20,    -10,      27;
'Near-zero vn',         0.1,   0,       3.5;
'Very small gap',      20,     0,       s0+0.1;
'Very large gap',      20,     0,       200;
'High speed',          40,     0,       51;
'Low speed',            2,     0,       5.4;
'vn+vrel near zero',   0.1,   -0.09,   3.5;
};

for i = 1:size(edge_cases, 1)
    label = edge_cases{i,1};
    vn    = edge_cases{i,2};
    vrel  = edge_cases{i,3};
    sn    = edge_cases{i,4};

    try
        % ── Pipeline ──────────────────────────────────────────────────
        [TT, UU, SELECT2] = vtg_acc_fcn1(vn, vrel, k1, tau_star, k2, ...
                                          rho_s, rho_v, rho_u, gamma);
        [T_out, U_out, info] = ordschur_mex(TT, UU, SELECT2);
        [cmd, tgc, P_schur] = vtg_acc_fcn2(sn, vn, vrel, k1, tau_star, ...
                                             k2, s0, rho_u, T_out, U_out);

        % ── Reconstruct matrices ───────────────────────────────────────
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

        % ── Metrics ───────────────────────────────────────────────────
        P_err        = norm(P_schur - P_icare, 'fro');
        ARE_residual = norm(Asys'*P_schur + P_schur*Asys ...
                          - P_schur*Bsys/Rmat*Bsys'*P_schur ...
                          + Qmat, 'fro');
        sym_err      = norm(P_schur - P_schur', 'fro');
        eigP         = eig(P_schur);
        min_eig      = min(eigP);
        is_PD        = all(eigP > 0);

        % ── Failsafe check ────────────────────────────────────────────
        diagT = diag(T_out);
        n     = length(diagT)/2;
        failsafe = ~(all(diagT(1:n) < 0) && all(diagT(n+1:end) > 0));

        % ── Sanity checks on control output ───────────────────────────
        assert(~isnan(cmd),    sprintf('%s: cmd_accel is NaN', label));
        assert(~isinf(cmd),    sprintf('%s: cmd_accel is Inf', label));
        assert(~isnan(tgc),    sprintf('%s: Time_Gap_Comm is NaN', label));
        assert(tgc >= 0,       sprintf('%s: Time_Gap_Comm < 0: %.2f', label, tgc));
        assert(~failsafe,      sprintf('%s: Failsafe triggered', label));
        assert(ARE_residual < 1e-10, ...
               sprintf('%s: ARE residual too large: %.2e', label, ARE_residual));
        assert(sym_err < 1e-10, ...
               sprintf('%s: P not symmetric: %.2e', label, sym_err));
        assert(is_PD, ...
               sprintf('%s: P not positive definite: min_eig=%.2e', label, min_eig));

        fprintf('%-25s %-12.2e %-12.2e %-12.2e %-12.2e %-10s\n', ...
                 label, P_err, ARE_residual, sym_err, min_eig, string(is_PD));

    catch ME
        fprintf('%-25s *** FAILED: %s ***\n', label, ME.message);
    end
end
fprintf('\nTest 6 Complete\n');

% ── Test 7: Numerical Conditioning ───────────────────────────────────────
fprintf('\n═══ Test 7: Numerical Conditioning ═══\n');
fprintf('%-25s %-12s %-12s %-12s %-10s\n', ...
        'Case', 'cond(Z)', 'cond(U11)', 'cond(P)', 'Status');
fprintf('%s\n', repmat('-',1,75));

% ── Sweep over operating points ───────────────────────────────────────────
vn_range_ext   = [0.1, 2, 5, 10, 15, 20, 25, 30, 40];   % extended range
vrel_range_ext = [-10, -5, -2, -0.001, 0, 0.001, 2, 5, 10];

% vn_range_ext = 0.1:0.1:40;
% vrel_range_ext = -10:0.1:10;

cond_Z_log   = zeros(length(vn_range_ext), length(vrel_range_ext));
cond_U11_log = zeros(length(vn_range_ext), length(vrel_range_ext));
cond_P_log   = zeros(length(vn_range_ext), length(vrel_range_ext));

for i = 1:length(vn_range_ext)
    for j = 1:length(vrel_range_ext)
        vn   = vn_range_ext(i);
        vrel = vrel_range_ext(j);
        label = sprintf('vn=%-4.1f vrel=%-5.1f', vn, vrel);

        try
            % ── Reconstruct Hamiltonian ───────────────────────────────
            Asys  = [0 -1; k1 (-k1*tau_star-k2)];
            Bdist = [1; k2];
            Csys  = [rho_s 0; 0 rho_v; 0 0];
            Ru    = rho_u^2;
            Rmat  = [-1/gamma^2 0; 0 inv(Ru)];
            ve    = vrel + vn;
            Bctrl = [0; -k1*ve];
            Bsys  = [Bdist, Bctrl];
            Qmat  = Csys'*Csys;
            Z     = [Asys -(Bsys/Rmat*Bsys'); -Qmat -Asys'];

            % ── Pipeline ──────────────────────────────────────────────
            [TT, UU, SELECT2] = vtg_acc_fcn1(vn, vrel, k1, tau_star, k2, ...
                                          rho_s, rho_v, rho_u, gamma);
            [T_out, U_out, info] = ordschur_mex(TT, UU, SELECT2);
            [cmd, tgc, P_schur] = vtg_acc_fcn2(sn, vn, vrel, k1, tau_star, ...
                                             k2, s0, rho_u, T_out, U_out);

            % ── Conditioning metrics ───────────────────────────────────
            [m, n]   = size(U_out);
            U11      = U_out(1:(m/2), 1:(n/2));
            cond_Z   = cond(Z);
            cond_U11 = cond(U11);
            cond_P   = cond(P_schur);

            cond_Z_log(i,j)   = cond_Z;
            cond_U11_log(i,j) = cond_U11;
            cond_P_log(i,j)   = cond_P;

            % ── Status ────────────────────────────────────────────────
            if cond_Z > 1e10
                status = '⚠ ILL-COND Z';
            elseif cond_U11 > 1e10
                status = '⚠ ILL-COND U11';
            elseif cond_P > 1e10
                status = '⚠ ILL-COND P';
            else
                status = '✓';
            end

            fprintf('%-25s %-12.2e %-12.2e %-12.2e %-10s\n', ...
                     label, cond_Z, cond_U11, cond_P, status);

        catch ME
            fprintf('%-25s *** FAILED: %s ***\n', label, ME.message);
        end
    end
end

% ── Summary ───────────────────────────────────────────────────────────────
fprintf('\nConditioning Summary:\n');
fprintf('  Max cond(Z):   %.2e\n', max(cond_Z_log(:)));
fprintf('  Max cond(U11): %.2e\n', max(cond_U11_log(:)));
fprintf('  Max cond(P):   %.2e\n', max(cond_P_log(:)));

% ── Heatmap visualization ─────────────────────────────────────────────────
figure('Name', 'Test 7: Conditioning Heatmap', 'Position', [100 100 1200 400]);

subplot(1,3,1);
imagesc(vrel_range_ext, vn_range_ext, log10(cond_Z_log));
colorbar; title('log10(cond(Z))');
xlabel('vrel (m/s)'); ylabel('vn (m/s)');
colormap(gca, 'jet');

subplot(1,3,2);
imagesc(vrel_range_ext, vn_range_ext, log10(cond_U11_log));
colorbar; title('log10(cond(U11))');
xlabel('vrel (m/s)'); ylabel('vn (m/s)');
colormap(gca, 'jet');

subplot(1,3,3);
imagesc(vrel_range_ext, vn_range_ext, log10(cond_P_log));
colorbar; title('log10(cond(P))');
xlabel('vrel (m/s)'); ylabel('vn (m/s)');
colormap(gca, 'jet');

fprintf('\nTest 7 Complete\n');