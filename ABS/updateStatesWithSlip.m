function [ new_Vx, new_Vw, slipRatio] = updateStatesWithSlip( Vx, Vw, b, h)
%UPDATE Summary of this function goes here
%   Detailed explanation goes here

%% Vehicle parameters
mass = 1500;       % mass of car
mass_wheel = 20;    % mass of one wheel
radius = 0.3;    % wheel redius (m)
J_w = 0.6;       % wheel inertia (kgm^2)
g = 9.8;
max_brake = -1000;   % torque in Nm
brake_change = -1500;
mu_peak = 1.0;  % road friction coefficient

%% Update states
Fz = ((mass * g) / 4  + mass_wheel * g);
slipRatio = (Vw - Vx) / Vx;
longForce = Fx_Pacejka(Fz, slipRatio);
Fx = mu_peak * longForce(1, :);
Vx_dot = 4 * Fx / (mass + mass_wheel);
Vw_dot = (1 / J_w) * ( b);

new_Vx = Vx + h * Vx_dot;
new_Vw = Vw + h * Vw_dot;
new_Vw = min(new_Vx, max(0, new_Vw));

end

