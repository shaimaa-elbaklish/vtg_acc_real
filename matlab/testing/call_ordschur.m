function [T_out, U_out, info] = call_ordschur(T, U, select)
%#codegen
coder.cinclude('ordschur_wrapper.h');
n = size(T,1);
T_out = T;
U_out = U;
info = int32(0);
info = coder.ceval('ordschur_reorder', ...
    int32(n), ...
    coder.ref(T_out), ...
    coder.ref(U_out), ...
    coder.rref(select) );
% For Simulink
customDir = "C:\Users\ShaimaaElBaklish\Documents\GitHub\vtg_acc_real\simulink\mycfiles";
coder.updateBuildInfo('addIncludePaths', customDir);
coder.updateBuildInfo('addSourcePaths', customDir);
coder.updateBuildInfo('addSourceFiles', 'ordschur_wrapper.c');
end