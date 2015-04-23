function [x ] = load_balancer( state_vars, coef_control, coef_reliability )
%LOAD_BALANCER: balancing the cpu load based on the trade-off between
%quality of control and (thermal) reliability
%Output: a complete task set, each task has (period, estimated avg and
%worst case execution time, and how many copies). the scheduling policies
%is to choose the coolest processors (cores) each time
addpath(fullfile(pwd, '../production_code'));
task_versions = get_taks_versions();
task_set_candidates = generate_candidates(state_vars);    % [period, execution time, num_of_copies]
% task_set_candidates = [10, 3, 2; 10, 1, 1];
tick_scheduler = vecgcd(task_set_candidates(:, 1));
costs = get_costs(task_set_candidates, coef_control, coef_reliability);
% costs = [30; 20];
intcon = ones(1, size(task_set_candidates, 1));
lb = zeros(size(task_set_candidates, 1), 1);
ub = ones(size(task_set_candidates, 1), 1);
A = zeros(1, size(task_set_candidates, 1));
b = zeros(1, 1);
for i = 1 : size(task_set_candidates, 1)
    A(1, i) = task_set_candidates(i, 2);
end
b = tick_scheduler;

Aeq = ones(1, size(task_set_candidates, 1));
beq = 1;
x = intlinprog(costs, intcon, A, b, Aeq, beq, lb, ub);

end

function [task_set_candidates] = generate_candidates(state_vars)


end

