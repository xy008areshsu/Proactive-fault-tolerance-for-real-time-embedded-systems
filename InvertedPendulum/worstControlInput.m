clc
clear all
warning off
u0 = [0.1]; % Starting guess\
fprintf ('The values of function value and constraints at starting point\n');
x0 = [0.5;0.5;0.5;0.5];

costFunction = @(u) probofminobj(u,x0);

f= -costFunction(u0)
C = [];
Ceq = [];
A = [];
B = [];
Aeq = [];
Beq = [];
LB = [-40];
UB = [40];

options = optimset ('MaxIter', 400, 'MaxFunEvals', 400);
[u, fval]=fmincon (costFunction, u0, A, B, Aeq, Beq, LB, UB, @nonLinCon, options);

worstCost = -fval
worstU = u

