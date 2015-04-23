function [ allocations ] = allocator( selected_task_set, core_temps )
%ALLOCATOR Summary of this function goes here
%   Detailed explanation goes here

core_temps = sortrows(core_temps, 2);
num_of_tasks = size(selected_task_set, 1);
num_of_cores = size(core_temps, 1);
num_of_copies = zeros(num_of_tasks, 1);
allocations{1, 1} = [];

for i = 1 : num_of_tasks
    num_of_copies(i) = size(selected_task_set(i).version, 2);
end

for i = 1 : num_of_cores
    allocations{i, 1} = core_temps(i, 1);
    pos = 2; 
    for j = 1 : num_of_tasks          
        if num_of_copies(j) > 0
            allocations{i, pos} = strcat(selected_task_set(j).name, ', version ', int2str(num_of_copies(j)));
            num_of_copies(j) = num_of_copies(j) - 1;
            pos = pos + 1;
        end
    end
end

end

