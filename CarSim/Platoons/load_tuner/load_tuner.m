function [selected_task_set] = load_tuner( candidate_list, num_of_tasks )
%LOAD_BALANCER: balancing the cpu load based on the trade-off between
%quality of control and (thermal) reliability
%Output: a complete task set, each task has (period, estimated avg and
%worst case execution time, and how many copies). the scheduling policies
%is to choose the coolest processors (cores) each time

costs = zeros(size(candidate_list, 1), 1);
for i = 1 : size(costs, 1)
    costs(i) = candidate_list(i).cost;
end

intcon = ones(1, size(candidate_list, 1));
A = zeros(1, size(candidate_list, 1));      % RM scheduling for a single core, total utilization should be less than m(2^(1/m) - 1)
b = zeros(1, 1);
Aeq = zeros(num_of_tasks, size(candidate_list, 1));   % each task just can pick one candidate: X_A1 + X_A2 + X_A3 + X_A4 = 1; X_B1 + X_B2 + X_B3 + X_B4 = 1
beq = zeros(num_of_tasks, 1);
LB = zeros(size(candidate_list, 1), 1);
UB = ones(size(candidate_list, 1), 1);

for i = 1 : num_of_tasks
    for j = (i - 1) * (size(candidate_list, 1) / num_of_tasks) + 1 : i * (size(candidate_list, 1) / num_of_tasks)
        Aeq(i, j) = 1;
    end
    beq(i, 1) = 1;
end

load_threshold = num_of_tasks * (2^(1/num_of_tasks) - 1);
for j = 1 : size(candidate_list, 1)
    cpu_utilizations = candidate_list(j).exectime ./ candidate_list(j).period;
    max_cpu_utilization = max(cpu_utilizations);
    A(1, j) = max_cpu_utilization;
end
b(1, 1) = load_threshold;
options = optimoptions('intlinprog','Display','off', 'IPPreprocess', 'advanced', 'TolGapRel', 1e-3, 'CutGeneration', 'advanced', 'CutGenMaxIter', 25);
% options = optimoptions('intlinprog','Display','off');

X = intlinprog(costs, intcon, A, b, Aeq, beq, LB, UB, options);
% X = intlinprog(costs, intcon, A, b, Aeq, beq, LB, UB);
selected_task_set = candidate_list(X == 1);

end
        

