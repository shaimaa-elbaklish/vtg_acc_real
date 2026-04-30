function [cmd_accel, Time_Gap_Comm, Pmat] = vtg_acc_fcn2(sn, vn, vrel, k1, tau_star, k2, s0, rho_u, Tmat, Umat)
cmd_accel = 0; Time_Gap_Comm= 0;
Ru = rho_u^2;
ve = vrel + vn;
s_err = sn - (s0+tau_star*ve);
v_err = vn - ve;
% --- Replacement for icare(A, B, Q, R) -----------------------------------
diagT = diag(Tmat);
Pmat = zeros(2, 2);
[m,n] = size(Umat);
U11 = Umat(1:(m/2), 1:(n/2));
U21 = Umat((m/2+1):m, 1:(n/2));
Pmat = U21/U11;
% Pmat = 0.5*(Pmat + Pmat');
% -------------------------------------------------------------------------
ui = -inv(Ru)*([0 -k1*vn]*Pmat*[s_err; v_err]);
Time_Gap_Comm = max(tau_star + double(ui), 0);
cmd_accel = k1*(sn-s0-Time_Gap_Comm*vn) + k2*vrel;
end