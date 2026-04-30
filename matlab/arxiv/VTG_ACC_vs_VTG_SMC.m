clear all; close all; clc;

%% Specify driving cycle
Tg = 1.0;
s0 = 3;
L = 5;
a_max = 5;
a_min = -5;

v_eq = 30;
dt = 0.1;
Time = 0:dt:500;
V_eq = v_eq*ones(length(Time), 1);
V_eq(101/dt:200/dt, 1) = 25;
V_eq(401/dt:450/dt, 1) = 35;

Lead_Velocity = 30*ones(length(Time), 1);
Lead_Acceleration = zeros(length(Time)-1, 1);
for i = 1:length(Time)-1
    if Time(i) >= 50 && Time(i) <= 51 
        Lead_Acceleration(i:i+5, 1) = 4;
    elseif Time(i) >= 300 && Time(i) <= 301
        Lead_Acceleration(i:i+5, 1) = -4;
    else
        Lead_Acceleration(i, 1) = 0.5*(V_eq(i, 1) - Lead_Velocity(i, 1));
    end
    Lead_Velocity(i+1, 1) = Lead_Velocity(i, 1) + dt*Lead_Acceleration(i, 1);
end

n_platoon = 5;
init_spacing = (s0+L+Tg*v_eq) + 20*rand(n_platoon-1, 1)-10;
init_velocity = v_eq + 4*rand(n_platoon-1, 1)-2;

figure;
plot(Time, Lead_Velocity, '-k', 'LineWidth', 1.5);
ylim([20 40]);
xlabel('Time (s)');
ylabel('Velocity (m/s)');
grid on;
ax = gca;
ax.FontSize = 12;


%% Constant Time Gap ACC
k1 = 0.23;
k2 = 0.07;
Spacing_ACC = zeros(length(Time), n_platoon-1);
Velocity_ACC = zeros(length(Time), n_platoon);
Acceleration_ACC = zeros(length(Time)-1, n_platoon-1);

Velocity_ACC(:, 1) = Lead_Velocity;
Spacing_ACC(1, :) = init_spacing;
Velocity_ACC(1, 2:end) = init_velocity;

for i = 1:length(Time)-1
    Acceleration_ACC(i, :) = k1*(Spacing_ACC(i, :)-s0-L-Tg*Velocity_ACC(i, 2:end)) + ...
                         k2*(Velocity_ACC(i, 1:end-1) - Velocity_ACC(i, 2:end));
    Acceleration_ACC(i, :) = max(min(Acceleration_ACC(i, :), a_max), a_min);
    Spacing_ACC(i+1, :) = Spacing_ACC(i, :) + dt*(Velocity_ACC(i, 1:end-1) - Velocity_ACC(i, 2:end));
    Velocity_ACC(i+1, 2:end) = Velocity_ACC(i, 2:end) + dt*Acceleration_ACC(i, :);
end


%% VTG SMC (Zhou and Peng, 2004)
T = 0.0019;
G = 0.0448;
lam = 2;

Spacing_SMC = zeros(length(Time), n_platoon-1);
Velocity_SMC = zeros(length(Time), n_platoon);
Acceleration_SMC = zeros(length(Time)-1, n_platoon-1);

Velocity_SMC(:, 1) = Lead_Velocity;
Spacing_SMC(1, :) = init_spacing;
Velocity_SMC(1, 2:end) = init_velocity;

for i = 1:length(Time)-1
    Th = T + 2*G.*Velocity_SMC(i, 2:end);
    S_des = s0 + L + T.*Velocity_SMC(i, 2:end) + G.*Velocity_SMC(i, 2:end).^2; 
    Acceleration_SMC(i, :) = lam*(Spacing_SMC(i, :)-S_des)./Th + ...
                         (Velocity_SMC(i, 1:end-1) - Velocity_SMC(i, 2:end))./Th;
    Acceleration_SMC(i, :) = max(min(Acceleration_SMC(i, :), a_max), a_min);
    Spacing_SMC(i+1, :) = Spacing_SMC(i, :) + dt*(Velocity_SMC(i, 1:end-1) - Velocity_SMC(i, 2:end));
    Velocity_SMC(i+1, 2:end) = Velocity_SMC(i, 2:end) + dt*Acceleration_SMC(i, :);
end


%% Variable Time Gap ACC
rho_s = 0.2;
rho_v = 0.5;
rho_u = 1.0;
gamma = 0.95;
Asys = [0 -1; k1 (-k1*Tg-k2)];
Bdist = [1; k2];
Csys = [rho_s 0; 0 rho_v; 0 0];
Ru = rho_u^2;
Rmat = [-1/gamma^2 0; 0 inv(Ru)];

Spacing_Hinf = zeros(length(Time), n_platoon-1);
Velocity_Hinf = zeros(length(Time), n_platoon);
Acceleration_Hinf = zeros(length(Time)-1, n_platoon-1);
Time_Gap_Comm = zeros(length(Time)-1, n_platoon-1);

Velocity_Hinf(:, 1) = Lead_Velocity;
Spacing_Hinf(1, :) = init_spacing;
Velocity_Hinf(1, 2:end) = init_velocity;

for i = 1:length(Time)-1
    for c = 2:n_platoon
        ve = Velocity_Hinf(i, c-1);
        s_err = Spacing_Hinf(i, c-1) - (s0+L+Tg*ve);
        v_err = Velocity_Hinf(i, c) - ve;
        Bctrl = [0; -k1*ve];
        [P, ~, ~] = icare(Asys, [Bdist, Bctrl], Csys'*Csys, Rmat, [], [], []);
        ui = -inv(Ru)*([0 -k1*Velocity_Hinf(i, c)]*P*[s_err; v_err]);
        Time_Gap_Comm(i, c-1) = max(Tg + ui, 0);
        Acceleration_Hinf(i, c-1) = k1*(Spacing_Hinf(i, c-1)-s0-L-Time_Gap_Comm(i, c-1)*Velocity_Hinf(i, c)) + ...
                               k2*(Velocity_Hinf(i, c-1) - Velocity_Hinf(i, c));
        Acceleration_Hinf(i, :) = max(min(Acceleration_Hinf(i, :), a_max), a_min);
        Spacing_Hinf(i+1, c-1) = Spacing_Hinf(i, c-1) + dt*(Velocity_Hinf(i, c-1) - Velocity_Hinf(i, c));
        Velocity_Hinf(i+1, c) = Velocity_Hinf(i, c) + dt*Acceleration_Hinf(i, c-1);
    end
end

%% Plotting
F_NUM = 1;
F_STR = strcat('F', int2str(F_NUM));

fs1 = 12; fs2 = 14;
figure;
tcl = tiledlayout(1, 3);
nexttile(tcl)
hold on;
plot(Time, Velocity_ACC(:, F_NUM+1), 'LineWidth', 1.5);
plot(Time, Velocity_SMC(:, F_NUM+1), 'LineWidth', 1.5);
plot(Time, Velocity_Hinf(:, F_NUM+1), 'LineWidth', 1.5);
plot(Time, Lead_Velocity, '--k', 'LineWidth', 1.5);
hL = legend({strcat(F_STR,' - CTG ACC'), strcat(F_STR,' - VTG SMC'), strcat(F_STR,' - VTG ACC'), 'Leader'});
hL.AutoUpdate = "off";
hL.FontSize = fs1;
ax = gca;
ax.FontSize = fs1;
hold off;
grid on;
xlabel('Time (s)', 'FontSize', fs1);
ylabel('Velocity (m/s)', 'FontSize', fs1);
ylim([15 43]);

nexttile(tcl);
hold on;
plot(Time, Spacing_ACC(:, F_NUM), 'LineWidth', 1.5);
plot(Time, Spacing_SMC(:, F_NUM), 'LineWidth', 1.5);
plot(Time, Spacing_Hinf(:, F_NUM), 'LineWidth', 1.5);
%legend({strcat(F_STR,' - CTG ACC'), strcat(F_STR,' - VTG SMC'), strcat(F_STR,' - VTG ACC')});
hold off;
grid on;
ax = gca;
ax.FontSize = fs1;
xlabel('Time (s)', 'FontSize', fs1);
ylabel('Space Headway (m)', 'FontSize', fs1);
ylim([20 65]);

% subplot(2, 2, 3);
% hold on;
% plot(Time(1:end-1), Acceleration_ACC(:, F_NUM), 'LineWidth', 1.5);
% plot(Time(1:end-1), Acceleration_SMC(:, F_NUM), 'LineWidth', 1.5);
% plot(Time(1:end-1), Acceleration_Hinf(:, F_NUM), 'LineWidth', 1.5);
% legend({strcat(F_STR,' - CTG ACC'), strcat(F_STR,' - VTG SMC'), strcat(F_STR,' - VTG ACC')});
% hold off;
% grid on;
% xlabel('Time (s)');
% ylabel('Acceleration (m/s^2)');
% ylim([-4 4]);

nexttile(tcl);
hold on;
plot(Time, Spacing_ACC(:, F_NUM)./Velocity_ACC(:, F_NUM+1), 'LineWidth', 1.5);
plot(Time, Spacing_SMC(:, F_NUM)./Velocity_SMC(:, F_NUM+1), 'LineWidth', 1.5);
plot(Time, Spacing_Hinf(:, F_NUM)./Velocity_Hinf(:, F_NUM+1), 'LineWidth', 1.5);
%legend({strcat(F_STR,' - CTG ACC'), strcat(F_STR,' - VTG SMC'), strcat(F_STR,' - VTG ACC')});
hold off;
grid on;
ax = gca;
ax.FontSize = fs1;
xlabel('Time (s)', 'FontSize', fs1);
ylabel('Time Headway (s)', 'FontSize', fs1);
ylim([0.6 2]);

hL.Orientation = "horizontal";
hL.Layout.Tile = 'south';

%% Plotting Per Controller
fs1 = 12;
fs2 = 14;

figure;
tcl = tiledlayout(3, 3);

Legend_Labels = strings(1, n_platoon);
for i = 1:n_platoon-1
    Legend_Labels(i) = strcat("Follower ", num2str(i));
end
Legend_Labels(end) = "Leader";

nexttile(tcl);
hold on;
for i = 2:n_platoon
    plot(Time, Velocity_ACC(:, i), 'LineWidth', 1.5);
end
plot(Time, Lead_Velocity, '--k', 'LineWidth', 1.5);
hL = legend(Legend_Labels, 'AutoUpdate', 'off', 'Orientation', 'horizontal');
hold off;
ax = gca;
ax.FontSize = fs1;
grid on;
xlabel('Time (s)', 'FontSize', fs1);
ylabel('Velocity (m/s)', 'FontSize', fs1);
title('CTG ACC', 'FontSize', fs2);
ylim([17 42]);
yticks(15:5:40);
xlim([0 500]);
xticks(0:100:500);

nexttile(tcl);
hold on;
for i = 2:n_platoon
    plot(Time, Velocity_SMC(:, i), 'LineWidth', 1.5);
end
plot(Time, Lead_Velocity, '--k', 'LineWidth', 1.5);
hold off;
ax = gca;
ax.FontSize = fs1;
grid on;
xlabel('Time (s)', 'FontSize', fs1);
ylabel('Velocity (m/s)', 'FontSize', fs1);
title('VTG SMC', 'FontSize', fs2);
ylim([17 42]);
yticks(15:5:40);
xlim([0 500]);
xticks(0:100:500);

nexttile(tcl);
hold on;
for i = 2:n_platoon
    plot(Time, Velocity_Hinf(:, i), 'LineWidth', 1.5);
end
plot(Time, Lead_Velocity, '--k', 'LineWidth', 1.5);
hold off;
ax = gca;
ax.FontSize = fs1;
grid on;
xlabel('Time (s)', 'FontSize', fs1);
ylabel('Velocity (m/s)', 'FontSize', fs1);
title('VTG ACC', 'FontSize', fs2);
ylim([17 42]);
yticks(15:5:40);
xlim([0 500]);
xticks(0:100:500);


nexttile(tcl);
hold on;
for i = 1:n_platoon-1
    plot(Time, Spacing_ACC(:, i), 'LineWidth', 1.5);
end
hold off;
ax = gca;
ax.FontSize = fs1;
grid on;
xlabel('Time (s)', 'FontSize', fs1);
ylabel('Space Headway (m)', 'FontSize', fs1);
%title('CTG ACC', 'FontSize', fs2);
ylim([10 65]);
yticks(10:10:65);
xlim([0 500]);
xticks(0:100:500);

nexttile(tcl);
hold on;
for i = 1:n_platoon-1
    plot(Time, Spacing_SMC(:, i), 'LineWidth', 1.5);
end
hold off;
ax = gca;
ax.FontSize = fs1;
grid on;
xlabel('Time (s)', 'FontSize', fs1);
ylabel('Space Headway (m)', 'FontSize', fs1);
%title('VTG SMC', 'FontSize', fs2);
ylim([10 65]);
yticks(10:10:65);
xlim([0 500]);
xticks(0:100:500);

nexttile(tcl);
hold on;
for i = 1:n_platoon-1
    plot(Time, Spacing_Hinf(:, i), 'LineWidth', 1.5);
end
hold off;
ax = gca;
ax.FontSize = fs1;
grid on;
xlabel('Time (s)', 'FontSize', fs1);
ylabel('Space Headway (m)', 'FontSize', fs1);
%title('VTG ACC', 'FontSize', fs2);
ylim([10 65]);
yticks(10:10:65);
xlim([0 500]);
xticks(0:100:500);


nexttile(tcl);
hold on;
for i = 1:n_platoon-1
    plot(Time, Spacing_ACC(:, i)./Velocity_ACC(:, 2:end), 'LineWidth', 1.5);
end
hold off;
ax = gca;
ax.FontSize = fs1;
grid on;
xlabel('Time (s)', 'FontSize', fs1);
ylabel('Time Headway (s)', 'FontSize', fs1);
%title('CTG ACC', 'FontSize', fs2);
ylim([0.5 2.3]);
yticks(0.5:0.5:2.5);
xlim([0 500]);
xticks(0:100:500);

nexttile(tcl);
hold on;
for i = 1:n_platoon-1
    plot(Time, Spacing_SMC(:, i)./Velocity_SMC(:, 2:end), 'LineWidth', 1.5);
end
hold off;
ax = gca;
ax.FontSize = fs1;
grid on;
xlabel('Time (s)', 'FontSize', fs1);
ylabel('Time Headway (s)', 'FontSize', fs1);
%title('VTG SMC', 'FontSize', fs2);
ylim([0.5 2.3]);
yticks(0.5:0.5:2.5);
xlim([0 500]);
xticks(0:100:500);

nexttile(tcl);
hold on;
for i = 1:n_platoon-1
    plot(Time, Spacing_Hinf(:, i)./Velocity_Hinf(:, 2:end), 'LineWidth', 1.5);
end
hold off;
ax = gca;
ax.FontSize = fs1;
grid on;
xlabel('Time (s)', 'FontSize', fs1);
ylabel('Time Headway (s)', 'FontSize', fs1);
%title('VTG ACC', 'FontSize', fs2);
ylim([0.5 2.3]);
yticks(0.5:0.5:2.5);
xlim([0 500]);
xticks(0:100:500);

hL.Layout.Tile = 'south';
hL.FontSize = fs1;
tcl.TileSpacing = 'compact';

%% TTC and Energy Consumption
VF_ACC = Velocity_ACC(:, 2:end);
TTC_ACC = (Spacing_ACC - 5)./(VF_ACC - Velocity_ACC(:, 1:end-1));
TTC_ACC(VF_ACC <= Velocity_ACC(:, 1:end-1)) = NaN;
min_TTC_ACC = min(TTC_ACC, [], 1);

VF_SMC = Velocity_SMC(:, 2:end);
TTC_SMC = (Spacing_SMC - 5)./(VF_SMC - Velocity_SMC(:, 1:end-1));
TTC_SMC(VF_SMC <= Velocity_SMC(:, 1:end-1)) = NaN;
min_TTC_SMC = min(TTC_SMC, [], 1);

VF_Hinf = Velocity_Hinf(:, 2:end);
TTC_Hinf = (Spacing_Hinf - 5)./(VF_Hinf - Velocity_Hinf(:, 1:end-1));
TTC_Hinf(VF_Hinf <= Velocity_Hinf(:, 1:end-1)) = NaN;
min_TTC_Hinf = min(TTC_Hinf, [], 1);


F0 = 213; F1 = 0.0861; F2 = 0.0027; mass = 1500;

VF_ACC = Velocity_ACC(1:end-1, 2:end);
Pt_ACC = (F0 + F1.*VF_ACC + F2.*VF_ACC.^2 + 1.03.*mass.*Acceleration_ACC).*VF_ACC.*1e-03;
Pt_ACC(Pt_ACC < 0) = 0;
Ec_ACC = sum(Pt_ACC, 1) ./ (0.036 * sum(VF_ACC, 1));

VF_SMC = Velocity_SMC(1:end-1, 2:end);
Pt_SMC = (F0 + F1.*VF_SMC + F2.*VF_SMC.^2 + 1.03.*mass.*Acceleration_SMC).*VF_SMC.*1e-03;
Pt_SMC(Pt_SMC < 0) = 0;
Ec_SMC = sum(Pt_SMC, 1) ./ (0.036 * sum(VF_SMC, 1));

VF_Hinf = Velocity_Hinf(1:end-1, 2:end);
Pt_Hinf = (F0 + F1.*VF_Hinf + F2.*VF_Hinf.^2 + 1.03.*mass.*Acceleration_Hinf).*VF_Hinf.*1e-03;
Pt_Hinf(Pt_Hinf < 0) = 0;
Ec_Hinf = sum(Pt_Hinf, 1) ./ (0.036 * sum(VF_Hinf, 1));


% Estimated L2 Gains
m = 100;
est_L2_gains_ACC = estimate_L2_gain(V_eq, Velocity_ACC, m);
est_L2_gains_SMC = estimate_L2_gain(V_eq, Velocity_SMC, m);
est_L2_gains_Hinf = estimate_L2_gain(V_eq, Velocity_Hinf, m);

fs1 = 12; fs2 = 14;
figure;
tcl = tiledlayout(1, 3);

nexttile(tcl);
%bar([est_L2_gains_ACC; est_L2_gains_SMC; est_L2_gains_Hinf]');
hold on;
p = plot(1:n_platoon-1, est_L2_gains_ACC, 'diamond--', 'LineWidth', 1.0);
p.MarkerFaceColor = p.Color;
p = plot(1:n_platoon-1, est_L2_gains_SMC, 'diamond--', 'LineWidth', 1.0);
p.MarkerFaceColor = p.Color;
p = plot(1:n_platoon-1, est_L2_gains_Hinf, 'diamond--', 'LineWidth', 1.0);
p.MarkerFaceColor = p.Color;
hold off;
grid on;
ax = gca;
ax.FontSize = fs1;
xlabel("Follower Order", 'FontSize', fs1);
ylabel('$\hat{\gamma}$', 'FontSize', fs1, 'Interpreter', 'latex');
hL = legend(["CTG ACC", "VTG SMC", "VTG ACC"], 'Orientation','horizontal', 'AutoUpdate', 'off');

nexttile(tcl);
%bar([min_TTC_ACC; min_TTC_SMC; min_TTC_Hinf]');
hold on;
p = plot(1:n_platoon-1, min_TTC_ACC, 'diamond--', 'LineWidth', 1.0);
p.MarkerFaceColor = p.Color;
p = plot(1:n_platoon-1, min_TTC_SMC, 'diamond--', 'LineWidth', 1.0);
p.MarkerFaceColor = p.Color;
p = plot(1:n_platoon-1, min_TTC_Hinf, 'diamond--', 'LineWidth', 1.0);
p.MarkerFaceColor = p.Color;
hold off;
grid on;
ax = gca;
ax.FontSize = fs1;
xlabel("Follower Order", 'FontSize', fs1);
ylabel("Minimum Time To Collision (s)", 'FontSize', fs1);

nexttile(tcl);
%bar([Ec_ACC; Ec_SMC; Ec_Hinf]');
hold on;
p = plot(1:n_platoon-1, Ec_ACC, 'diamond--', 'LineWidth', 1.0);
p.MarkerFaceColor = p.Color;
p = plot(1:n_platoon-1, Ec_SMC, 'diamond--', 'LineWidth', 1.0);
p.MarkerFaceColor = p.Color;
p = plot(1:n_platoon-1, Ec_Hinf, 'diamond--', 'LineWidth', 1.0);
p.MarkerFaceColor = p.Color;
hold off;
grid on;
ax = gca;
ax.FontSize = fs1;
xlabel("Follower Order", 'FontSize', fs1);
ylabel("Tractive Energy Consumption (kWh/100km)", 'FontSize', fs1);

hL.Layout.Tile = 'south';
hL.FontSize = fs1;

%% Functions
function [eta_L2, eta_Linf] = compute_string_stability_indicator(...
    V_eq, V_platoon)
n_platoon = size(V_platoon, 2);
eta_L2 = zeros(1, n_platoon-1);
eta_Linf = zeros(1, n_platoon-1);
for i = 2:n_platoon
    V_follow = V_platoon(:, i);
    V_lead = V_platoon(:, i-1);
    L2_follow = sqrt(sum((V_follow - V_eq).^2));
    L2_lead = sqrt(sum((V_lead - V_eq).^2));
    eta_L2(i-1) = L2_follow / L2_lead;

    Linf_follow = max(abs(V_follow - V_eq));
    Linf_lead = max(abs(V_lead - V_eq));
    eta_Linf(i-1) = Linf_follow / Linf_lead;
end
end


function est_L2_gains = estimate_L2_gain(V_eq, V_platoon, m)
n_platoon = size(V_platoon, 2);
est_L2_gains = zeros(1, n_platoon-1);
for i = 2:n_platoon
    V_follow = V_platoon(:, i);
    V_lead = V_platoon(:, i-1);
    [~, Ru] = correlation_matrix(V_lead - V_eq, m);
    [~, Ry] = correlation_matrix(V_follow - V_eq, m);

    yalmip('clear');
    gainEst = sdpvar();
    obj = gainEst;
    cnst = [Ry - gainEst*Ru <= 0; gainEst >= 0];
    opts = sdpsettings('verbose', 1, 'solver', 'sedumi');
    optimize(cnst, obj, opts);

    est_L2_gains(i-1) = sqrt(value(gainEst));
end
end

function [Tm, Rm] = correlation_matrix(x, m)
N = length(x);
Tm = zeros(N+m-1, m);
for j = 1:m
    Tm(j:j+N-1, j) = x; 
end
Rm = (Tm' * Tm)/N;
end