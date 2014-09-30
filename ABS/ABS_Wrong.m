function [ brake ] = ABS_Wrong(Vx, Vw)
%ABS_FUNC Summary of this function goes here
%   Detailed explanation goes here
    
    brake = -ABS_func(Vx, Vw);
    
    %brake = max(max_brake, brake);
end
