function cmd_accel = vtg_acc_fcn(sn, vn, vrel, k1, tau_star, k2, s0)
rho_s = 0.2;
rho_v = 0.5;
rho_u = 1.0;
gamma = 0.95;
Asys = [0 -1; k1 (-k1*Tg-k2)];
Bdist = [1; k2];
Csys = [rho_s 0; 0 rho_v; 0 0];
Ru = rho_u^2;
Rmat = [-1/gamma^2 0; 0 inv(Ru)];

ve = vrel + vn;
s_err = sn - (s0+tau_star*ve);
v_err = vn - ve;
Bctrl = [0; -k1*ve];
[P, ~, ~] = icare(Asys, [Bdist, Bctrl], Csys'*Csys, Rmat, [], [], []);
ui = -inv(Ru)*([0 -k1*vn]*P*[s_err; v_err]);
Time_Gap_Comm = max(Tg + ui, 0);
cmd_accel = k1*(sn-s0-Time_Gap_Comm*vn) + k2*vrel;

end