clear all; clc;

% ── Test 8: Real-Time Performance ─────────────────────────────────────────
modelName   = 'vtg_sim_r24b_testing';
sample_time = 0.05;  % replace with your actual sample time

% Open model if not loaded
if ~bdIsLoaded(modelName)
    load_system(modelName);
end

% ── Run with profiler ─────────────────────────────────────────────────────
fprintf('Running simulation with profiler...\n');
out = sim(modelName, 'Profile', 'on');

% ── Extract profiling data ────────────────────────────────────────────────
profilingData = out.SimulationMetadata.TimingInfo.ProfilerData;

% ── Generate HTML report ──────────────────────────────────────────────────
reportName = 'ACC_profiler_report.html';
generateReport(profilingData, reportName);
fprintf('HTML report saved: %s\n', reportName);

% ── Traverse UINode tree to find blocks of interest ───────────────────────
blocks_of_interest = {'vtg_acc_fcn1', 'call_ordschur', 'vtg_acc_fcn2'};
results = struct('name', {}, 'totalTime', {}, 'selfTime', {}, 'calls', {});

function results = search_nodes(node, blocks_of_interest, results)
    % Check if this node matches any block of interest
    for i = 1:length(blocks_of_interest)
        if contains(node.path, blocks_of_interest{i})
            results(end+1).name      = node.path;
            results(end).totalTime   = node.totalTime;
            results(end).selfTime    = node.selfTime;
            results(end).calls       = node.numberOfCalls;
        end
    end
    % Recurse into children
    for i = 1:length(node.children)
        results = search_nodes(node.children(i), blocks_of_interest, results);
    end
end

results = search_nodes(profilingData.rootUINode, blocks_of_interest, results);

% ── Print timing table ────────────────────────────────────────────────────
fprintf('\n═══ Test 8: Real-Time Performance ═══\n');
fprintf('Sample time budget: %.1f ms\n\n', sample_time*1000);
fprintf('%-35s %-8s %-15s %-15s %-10s\n', ...
        'Block', 'Calls', 'Self(ms/call)', 'Total(ms/call)', '% Budget');
fprintf('%s\n', repmat('-', 1, 85));

total_per_call = 0;
for i = 1:length(results)
    self_per_call  = results(i).selfTime  / results(i).calls * 1000;
    total_per_call_i = results(i).totalTime / results(i).calls * 1000;
    pct_budget     = (results(i).selfTime / results(i).calls) / sample_time * 100;
    total_per_call = total_per_call + self_per_call;

    fprintf('%-35s %-8d %-15.3f %-15.3f %-10.1f\n', ...
             results(i).name, results(i).calls, ...
             self_per_call, total_per_call_i, pct_budget);
end

fprintf('%s\n', repmat('-', 1, 85));
total_pct = total_per_call / (sample_time*1000) * 100;
fprintf('%-35s %-8s %-15.3f %-15s %-10.1f\n', ...
         'CONTROLLER TOTAL', '', total_per_call, '', total_pct);

% ── Budget assessment ─────────────────────────────────────────────────────
fprintf('\nAssessment:\n');
if total_pct > 80
    fprintf('  ⚠ CRITICAL: Controller using %.1f%% of sample time budget!\n', total_pct);
    fprintf('  Consider: static allocation in C, larger sample time\n');
elseif total_pct > 50
    fprintf('  ⚠ CAUTION: Controller using %.1f%% of budget\n', total_pct);
    fprintf('  Consider: static allocation in C before ROS deployment\n');
else
    fprintf('  ✓ Controller within budget: %.1f%% used\n', total_pct);
    fprintf('  Safe for ROS deployment\n');
end

% ── Open HTML report ──────────────────────────────────────────────────────
open(reportName);