clear; clc; close all
global AIneq BIneq Aeq Beq UB LB Ts

AIneq = [];
BIneq = [];
Aeq = [];
Beq = [];
UB = [250];
LB = [0];
Ts = 0.01;

testStates = [[25; 24; 0], [25; 10; 0], [25; 21; 0]];
worstCases = zeros(size(testStates, 2), 2);

for i = 1 : size(testStates, 2)
    [worstCases(i, 1), worstCases(i, 2)] = worstController(testStates(:, i));
end

