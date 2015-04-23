clear; clc; close all

A1 = Task('cruise_control', [1], [10], [5], 35);
A2 = Task('cruise_control', [2,2], [20,20], [1, 1], 45);
A3 = Task('cruise_control', [1,1], [20,20], [5, 5], 40);
A4 = Task('cruise_control', [2], [10], [1], 30);
B1 = Task('steering_control', [1,1], [15,15], [3,3], 35);
B2 = Task('steering_control', [2,2], [20,20], [1,1], 50);
B3 = Task('steering_control', [1,1], [20,20], [3,3], 65);
B4 = Task('steering_control', [2], [15], [1], 45);

candidate_list = [A1, A2, A3, A4, B1, B2, B3, B4]';

num_of_tasks = 2;


selected_task_set = load_tuner(candidate_list, num_of_tasks);

core_temps = [1 80; 2 75; 3 67; 4 85];


allocations = allocator(selected_task_set, core_temps);

