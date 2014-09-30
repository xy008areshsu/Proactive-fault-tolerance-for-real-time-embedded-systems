function [ cost ] = probofminobj(u, x0)
%PROBOFMINOBJ Summary of this function goes here
%   Detailed explanation goes here

mass_quarter_car = 250;
g = 9.81;

newState = updateState(x0,u);
v_new = newState(1);
w_new = newState(2);

s_new = max(0., 1. - w_new / v_new);


Fx = mu(s_new) * mass_quarter_car * g;
F_max = mu(0.2) * mass_quarter_car * g;

cost = 1/(2 * size(s_new, 1)) * sum((F_max - Fx).^2);

end

