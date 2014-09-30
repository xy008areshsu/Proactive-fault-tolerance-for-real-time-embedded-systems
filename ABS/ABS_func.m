function [ brake ] = ABS_func(Vx, Vw)
%ABS_FUNC Summary of this function goes here
%   Detailed explanation goes here

    max_brake = -3000;
    mass = 1500;       % mass of car
    mass_wheel = 20;    % mass of one wheel
    g = 9.8;
    Fz = ((mass * g) / 4  + mass_wheel * g);
    brake_change = -1000;
    slip = -1 : 0.01 : 1;
    longPart = Fx_Pacejka(Fz(1) * ones(1, size(slip, 2)), slip);
    Fx = longPart(1,1);
    optSlip = slip(longPart(1, :) == min(longPart(1, :)));
    slip_ratio = (Vw - Vx) / Vx;
    error = slip_ratio - optSlip;
    
    gain = max_brake;
    brake = gain * error;

    brake = max(brake_change, min(0, brake));

    
    %brake = max(max_brake, brake);
end

