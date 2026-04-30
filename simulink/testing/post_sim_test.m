3*4% Access results
scenario_name = 'stop_and_go';
t              = out.t;
sn             = out.sn;
car1_vel       = out.car1_vel; %vn
rel_vel        = out.rel_vel;
car_vel        = out.car_vel;  %vn-1
cmd_accel      = out.cmd_accel;
tau_i          = out.tau_i;
desired_gap    = out.desired_gap;
failsafe_flag  = out.failsafe_flag;
gap_error      = sn - desired_gap;
tau_star       = 1.2;
s0             = 3.0;
max_accel      = 1.5;
min_accel      = -3.0;

% ── Safety Metrics ────────────────────────────────────────────────────────
vn           = car1_vel;
TTC          = sn ./ max(-rel_vel, 0.001);
DRAC         = max(-rel_vel, 0).^2 ./ (2*max(sn, 0.001));
min_gap      = min(sn);

% ── Performance Metrics ───────────────────────────────────────────────────
tau_actual    = sn ./ max(vn, 0.001);
tau_err       = tau_actual - tau_star;
threshold     = 0.05 * mean(desired_gap);
settled_idx   = find(abs(gap_error) < threshold, 1, 'first');
settling_time = t(settled_idx);
overshoot     = max(gap_error) / mean(desired_gap) * 100;
rms_accel     = rms(cmd_accel);
jerk          = diff(cmd_accel) ./ diff(t);
max_jerk      = max(abs(jerk));
rms_jerk      = rms(jerk);

% ── Violation masks ───────────────────────────────────────────────────────
gap_violation      = sn < s0;                    % min gap violated
ttc_violation      = TTC < 1.5;                  % TTC too low
drac_violation     = DRAC > 3.35;                % DRAC too high
accel_violation    = cmd_accel > max_accel | ...
                     cmd_accel < min_accel;      % accel out of bounds
jerk_violation     = abs(jerk) > 3;              % jerk too high

% ── Print Summary ─────────────────────────────────────────────────────────
fprintf('\n═══ %s ═══\n', scenario_name);
fprintf('Safety:\n');
fprintf('  Min TTC:       %.2f s    (threshold > 1.5s)  %s\n', min(TTC),  flag(any(ttc_violation)));
fprintf('  Max DRAC:      %.2f m/s² (threshold < 3.35)  %s\n', max(DRAC), flag(any(drac_violation)));
fprintf('  Min Gap:       %.2f m    (threshold > %.1f)  %s\n', min_gap, s0, flag(any(gap_violation)));
fprintf('Performance:\n');
fprintf('  Settling Time: %.2f s\n',    settling_time);
fprintf('  Overshoot:     %.2f %%\n',   overshoot);
fprintf('  RMS Accel:     %.2f m/s²\n', rms_accel);
fprintf('  Max Jerk:      %.2f m/s³  %s\n', max_jerk, flag(any(jerk_violation)));
fprintf('  RMS Jerk:      %.2f m/s³\n', rms_jerk);

% ── Plots ─────────────────────────────────────────────────────────────────
figure('Name', scenario_name, 'Position', [100 100 800 600]);
set(gcf, 'Renderer', 'opengl');
tl = tiledlayout(3, 2, 'TileSpacing', 'compact', 'Padding', 'compact');

% 1. Gap
ax1 = nexttile(tl);
plot(t, sn, 'b', t, desired_gap, 'r--');
xlabel('Time (s)'); ylabel('Gap (m)');
legend('Actual gap','Desired gap'); grid on;
title('Gap');
highlight_violations(ax1, t, gap_violation, 'Min gap violated');

% 2. Gap Error
ax2 = nexttile(tl);
plot(t, gap_error);
ylabel('Gap error (m)'); xlabel('Time (s)'); title('Gap Error');
grid on;

% 3. Velocities
ax3 = nexttile(tl);
plot(t, car_vel, 'b', t, car1_vel, 'r--');
legend('Lead velocity', 'Ego velocity');
ylabel('Velocity (m/s)'); xlabel('Time (s)'); title('Velocities');
grid on;

% 4. Acceleration
ax4 = nexttile(tl);
plot(t, cmd_accel);
yline(max_accel,  'r--', 'Max accel');
yline(min_accel, 'r--', 'Max decel');
ylabel('cmd\_accel (m/s²)'); xlabel('Time (s)'); title('Acceleration Command');
grid on;
highlight_violations(ax4, t, accel_violation, 'Accel out of bounds');

% 5. TTC
ax5 = nexttile(tl);
plot(t, TTC);
yline(1.5, 'r--', 'Danger threshold');
ylabel('TTC (s)'); xlabel('Time (s)'); title('Time To Collision');
grid on;
ylim([0, 10]);
highlight_violations(ax5, t, ttc_violation, 'TTC < 1.5s');

% 6. DRAC
ax6 = nexttile(tl);
plot(t, DRAC);
yline(3.35, 'r--', 'Danger threshold');
ylabel('DRAC (m/s²)'); xlabel('Time (s)'); title('DRAC');
grid on;
highlight_violations(ax6, t, drac_violation, 'DRAC > 3.35');

% ── Second figure: tau_i, jerk, failsafe ──────────────────────────────────
figure('Name', [scenario_name ' - comfort'], 'Position', [100 100 1200 250]);
set(gcf, 'Renderer', 'opengl');
tl = tiledlayout(1, 3, 'TileSpacing', 'compact', 'Padding', 'compact');

ax7 = nexttile(tl);
plot(t, tau_i, 'b', t, tau_star*ones(size(t)), 'r--');
xlabel('Time (s)'); ylabel('Time Gap (s)');
legend('tau\_i','tau\_star'); grid on;
title('Time Gap Command');

ax8 = nexttile(tl);
plot(t(1:end-1), jerk);
yline(3,  'r--'); yline(-3, 'r--');
ylabel('Jerk (m/s³)'); xlabel('Time (s)'); title('Jerk');
grid on;
highlight_violations(ax8, t(1:end-1), jerk_violation, 'Jerk > 3 m/s³');

ax9 = nexttile(tl);
plot(t, failsafe_flag);
ylim([-0.5 1.5]); ylabel('Failsafe'); xlabel('Time (s)'); title('Failsafe Flag');
grid on;
highlight_violations(ax9, t, logical(failsafe_flag), 'Failsafe triggered');

% ── Local functions ───────────────────────────────────────────────────────
function highlight_violations(ax, t, mask, label)
    if ~any(mask), return; end
    hold(ax, 'on');
    ylims = ylim(ax);
    % Find contiguous violation regions
    diff_mask = diff([0; mask(:); 0]);
    starts    = find(diff_mask ==  1);
    ends      = find(diff_mask == -1) - 1;
    for i = 1:length(starts)
        t_start = t(starts(i));
        t_end   = t(min(ends(i), length(t)));
        % patch supports transparency natively
        patch(ax, ...
            [t_start t_end t_end t_start], ...
            [ylims(1) ylims(1) ylims(2) ylims(2)], ...
            'red', ...
            'FaceAlpha', 0.15, ...
            'EdgeAlpha', 0.4, ...
            'EdgeColor', 'red');
    end
    % Add label on first violation only
    text(ax, t(starts(1)), ylims(2)*0.95, label, ...
         'Color', 'r', 'FontSize', 7, 'VerticalAlignment', 'top');
    hold(ax, 'off');
end

function str = flag(condition)
    if condition
        str = '⚠ VIOLATION';
    else
        str = '✓';
    end
end