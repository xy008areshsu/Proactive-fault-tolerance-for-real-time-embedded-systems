function [ bestU, bestCost ] = bestController( x )
%WORSTCONTROLLER Summary of this function goes here
%   Detailed explanation goes here

warning off
u0 = [0.1]; % Starting guess\
fprintf ('The values of function value and constraints at starting point\n');

costFunction = @(u) probofminobj(u,x);

A = [];
B = [];
Aeq = [];
Beq = [];
LB = [-40];
UB = [40];

options = optimset ('MaxIter', 400, 'MaxFunEvals', 400);
[u, fval]=fmincon (costFunction, u0, A, B, Aeq, Beq, LB, UB, @nonLinCon, options);

bestCost = fval;
bestU = u;


end

