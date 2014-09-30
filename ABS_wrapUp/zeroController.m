function [ newActuatorVector ] = zeroController( stateVector, oldActuatorVector )
%ZEROCONTROLLER Summary of this function goes here
%   Detailed explanation goes here

    global A B C D K Ts UB LB 
    
%% Brake parameters
    hydraulic_speed = 3300.; % m / s3

%% Update brake actuators    
    v = stateVector(1);
    w = stateVector(2);

    s = max(0., 1. - w / v);

%     if s > 0.2
%     brake_change = -1;
%     else
%     brake_change = 1;
%     end

%     newActuatorVector = max(LB, min(UB, oldActuatorVector + Ts * 1 * hydraulic_speed));        % suppose hard brake
    %Alternative method
    newActuatorVector = max(100., min(UB, oldActuatorVector + Ts * 1 * hydraulic_speed));


end
