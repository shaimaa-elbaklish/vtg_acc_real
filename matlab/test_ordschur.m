clear all; close all; clc;

% Z = [1.1147    0.0394   -0.0100   -0.0094;
%     0.2061    1.0938   -0.0107   -0.0100;
%    -0.9097    0.1640    0.9097   -0.1640;
%     0.0252   -0.9272   -0.0252    0.9272];
% % SELECT = [false;false;false;false;false;true;true];
% SELECT = [false;false; ...
%     false;false; ...
%     false;true; ...
%     false;true];

Z = [0   -1.0000    0.9025    0.0632;
    0.2300   -0.5300    0.0632  -33.0581;
   -0.0400         0         0   -0.2300;
         0   -0.2500    1.0000    0.5300];
% % SELECT = [false;true;false;false;true;false];
% SELECT = [false;true; ...
%     false;false; ...
%     false;true;...
%     false;false];

% Computing the Schur factorization using MATLABs schur(A)
[UU,TT] = schur(Z);
P = size(Z,1);

% Settings for LAPACK dtrsen
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

% Setting any of following allows for the ordering of the eigenvalues according to:
%        'lhp'            left-half plane  (real(E)<0)
%        'rhp'            right-half plane (real(E)>0)
%        'udi'            interior of unit disk (abs(E)<1)
%        'udo'            exterior of unit disk (abs(E)>1)
[US,TS] = ordschur(UU,TT,'lhp');

if all(all((UUS*TTS*UUS' - Z) < 1e-6))
    disp('Correct factorization from FORTRAN');
else
    disp('!! Incorrect factorization from FORTRAN');
end

if all(all((US*TS*US' - Z) < 1e-6))
    disp('Correct factorization from MATLAB');
else
    disp('!! Incorrect factorization from MATLAB');
end