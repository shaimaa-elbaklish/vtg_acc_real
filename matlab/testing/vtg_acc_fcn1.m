function [TT, UU, SELECT2] = vtg_acc_fcn1(vn, vrel, k1, tau_star, k2, rho_s, rho_v, rho_u, gamma)
Asys = [0 -1; k1 (-k1*tau_star-k2)];
Bdist = [1; k2];
Csys = [rho_s 0; 0 rho_v; 0 0];
Ru = rho_u^2;
Rmat = [-1/gamma^2 0; 0 inv(Ru)];
ve = vrel + vn;
Bctrl = [0; -k1*ve];
Bsys = [Bdist, Bctrl];
Qmat = Csys'*Csys;
% --- Replacement for icare(A, B, Q, R) -----------------------------------
Z = [Asys -(Bsys/Rmat*Bsys'); -Qmat -Asys']; % Hamiltonian
[UU, TT] = schur(Z);
SELECT0 = real(ordeig(TT)) < 0;
SELECT0 = logical(SELECT0);
SELECT2 = int32(SELECT0);  % Already length 4, no expansion
end