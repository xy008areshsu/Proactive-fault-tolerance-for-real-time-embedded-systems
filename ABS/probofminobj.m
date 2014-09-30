function [ cost ] = probofminobj(u, x0)
%PROBOFMINOBJ Summary of this function goes here
%   Detailed explanation goes here

s_des = -0.24;


h = 0.01;

[v_new, w_new] = updateStates(x0(1), x0(2), u, h);
s_new = (w_new - v_new) / v_new;

%% Vehicle parameters
mass = 1500;       % mass of car
mass_wheel = 20;    % mass of one wheel
radius = 0.3;    % wheel redius (m)
J_w = 0.6;       % wheel inertia (kgm^2)
g = 9.8;
mu_peak = 1.0;  % road friction coefficient

%% Update states
Fz = ((mass * g) / 4  + mass_wheel * g);
longForce = Fx_Pacejka(Fz, s_new);
Fx = mu_peak * longForce(1, :);
F_max = longForce(2, 1);
cost = 1/(2 * size(s_new, 1)) * sum((F_max - Fx).^2);

end

