clear all; close all; clc;

%% Parameter Definition
k1 = 0.23; k2 = 0.07;
tau_star = 2;
s0 = 5;
sn = 7;
vn = 20;
vrel = 5;

rho_s = 0.2;
rho_v = 0.5;
rho_u = 1.0;
gamma = 0.95;
Asys = [0 -1; k1 (-k1*tau_star-k2)];
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
Time_Gap_Comm = max(tau_star + ui, 0);
cmd_accel = k1*(sn-s0-Time_Gap_Comm*vn) + k2*vrel;

%% CARE Solution
P2 = solve_are(Asys, [Bdist, Bctrl], Csys'*Csys, Rmat);

function P = solve_are(A, B, Q, R)
Z = [A -(B/R*B'); -Q -A'];
% [U, S] = schur(Z);
% [U, S] = ordschur(U, S, 'lhp');

% --- Replacement for ordschur(U,S,'lhp') ---
[U, S] = manual_ordschur(Z);
% display(S)
% display(myS)
% 
% display(U)
% display(myU)

% if all(all((myU*myS*myU' - Z) < 1e-6))
%     disp('Correct factorization from FORTRAN');
% else
%     disp('!! Incorrect factorization from FORTRAN');
% end
% 
% if all(all((U*S*U' - Z) < 1e-6))
%     disp('Correct factorization from MATLAB');
% else
%     disp('!! Incorrect factorization from MATLAB');
% end
% --------------------------------------------

[m,n] = size(U);
U11 = U(1:(m/2), 1:(n/2));
U21 = U((m/2+1):m, 1:(n/2));
P = U21/U11;
end


function [UUS, TTS] = manual_ordschur(Z)
[UU, TT] = schur(Z);

% Settings for LAPACK dtrsen
P = size(Z,1);
JOB = 'N';
COMPQ = 'V';
SELECT0 = real(ordeig(TT)) < 0;     % Nx1 logical
SELECT0 = logical(SELECT0);
% Expand pattern: [false; flag; false; flag; ...]
N = numel(SELECT0);
SELECT = false(2*N, 1);
SELECT(2:2:end) = SELECT0;
N = P;
T = TT;
LDT = P;
QQ = UU;
LDQ = P;
WR = zeros(P,1);
WI = zeros(P,1);
M = 1 ;
S = 0;
SEP = 0;
WORK = zeros(P,1);
LWORK = P;
IWORK = zeros(P,1);
LIWORK = 1;
INFO = 0;

% Computing ordschur using LAPACK dtrsen
out = lapack('dtrsen',JOB,COMPQ,SELECT,N,T,LDT,QQ,LDQ,WR,WI,M,S,SEP,WORK,LWORK,IWORK,LIWORK,INFO);
TTS = out{5};
UUS = out{7};
end



