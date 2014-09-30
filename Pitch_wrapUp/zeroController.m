function [ newActuatorVector ] = zeroController( stateVector, oldActuatorVector )
%ZEROCONTROLLER Summary of this function goes here
%   Detailed explanation goes here

    global A B C D K Ts UB LB 
    
    newActuatorVector = 0 * oldActuatorVector;


end

