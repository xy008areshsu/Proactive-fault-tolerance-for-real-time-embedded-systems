function [ newActuatorVector ] = updateControlActuator(stateVector, oldActuatorVector)
%ABS_FUNC Summary of this function goes here
%   Detailed explanation goes here
    global A B C D K Ts UB LB 

        newActuatorVector = -K * stateVector;
        newActuatorVector = min(UB, max(LB, newActuatorVector));

end

