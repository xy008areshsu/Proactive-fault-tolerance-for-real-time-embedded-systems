function [ worstU, worstCost ] = worstController( x )
%WORSTCONTROLLER Summary of this function goes here
%   Detailed explanation goes here

warning off
u0 = [0]; % Starting guess\
fprintf ('The values of function value and constraints at starting point\n');

costFunction = @(u) -probofminobj(u,x);

A = [];
B = [];
Aeq = [];
Beq = [];
LB = [0];
UB = [1500];
C = [];
Ceq = [];

options = optimset ('MaxIter', 4000, 'MaxFunEvals', 4000);
[u, fval]=fmincon (costFunction, u0, A, B, Aeq, Beq, LB, UB, @nonLinCon, options);
% [u, fval]=fmincon (costFunction, u0, A, B, Aeq, Beq, LB, UB, C, Ceq, options);

if u ~= 0
    worstU = 1500;
    worstCost = costFunction(worstU);
else
    worstU = 0;
    worstCost = costFunction(worstU);
end



end

