function [ worstU, worstCost ] = worstController(x)
%WORSTCONTROLLER Summary of this function goes here
%   Detailed explanation goes here
global A  B C D K SSS Ts tf AIneq BIneq Aeq Beq LB UB

warning off

% fprintf ('The values of function value and constraints at starting point\n');

costFunction = @(u) -probofminobj(u,x);
u0 = zeros(size(UB, 1),1); % Starting guess\
options = optimset ('MaxIter', 4000, 'MaxFunEvals', 4000);
[u, fval]=fmincon (costFunction, u0, AIneq, BIneq, Aeq, Beq, LB, UB, @nonLinCon, options);

worstCost = -fval;
worstU = u;


end

