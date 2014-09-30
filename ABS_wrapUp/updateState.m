function newStateVector = updateState(oldStateVector, actuatorVector)
%UPDATE Summary of this function goes here
%   Detailed explanation goes here
% 

global A B C D K Ts 

%% Car parameters
% state var: [vehicle speed; wheel speed; vehicle position]

mass_quarter_car = 250.; % kg, 1/4 of the car weight
mass_effective_wheel = 20.; % kg
g = 9.81; % m / s2
road = 1.0;

%% Update states
if oldStateVector(1) < 10   % lower than 10 m/s ABS not triggered
    newStateVector = oldStateVector;
else
    v = oldStateVector(1);
    w = oldStateVector(2);
    x = oldStateVector(3);
    s = max(0., 1. - w / v);
    force = road * mu(s) * mass_quarter_car * g;
    v = v - Ts * force / mass_quarter_car;
    x = x + Ts * v;
    w = w + Ts * (force / mass_effective_wheel - actuatorVector);
    w = max(0., w);

    newStateVector = [v;w;x];
end
    
    
end

