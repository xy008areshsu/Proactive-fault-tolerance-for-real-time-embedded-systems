function data  = cruise_command_calc( data, vel, distance1, distance2 )
%CRUISE_COMMAND_CALC Summary of this function goes here
%   Detailed explanation goes here

L = 5; %final desired spacing
h = 1; % time gap
lambda = 1;
gain_throttle = 0.036;
gain_brake = -0.54;
adjust_throttle = 1;
adjust_brake = 1;

distance1 = -distance1;
distance2 = -distance2;
vel = 0.28 * vel;

distance1_dot = distance1 - data.old_distance1;
distance2_dot = distance2 - data.old_distance2;

e_dot1 = distance1_dot;
e_dot2 = distance2_dot;
delta1 = distance1 + L + h * vel;
leading_car_vel = vel - distance1_dot;
delta2 = distance2 + L + h * leading_car_vel;

candidate_accel1 = -1/h * (e_dot1 + lambda * delta1);
candidate_accel2 = -1/h * (e_dot2 + lambda * delta2);

if candidate_accel1 > 0
    candidate_throttle1 = min(candidate_accel1 * gain_throttle, 1);
    candidate_brake1 = 0;
else
    candidate_throttle1 = 0;
    candidate_brake1 = min(candidate_accel1 * gain_brake, 15);
end

if candidate_accel2 > 0
    candidate_throttle2 = min(candidate_accel2 * gain_throttle, 1);
    candidate_brake2 = 0;
else
    candidate_throttle2 = 0;
    candidate_brake2 = min(candidate_accel2 * gain_brake, 15);
end

if candidate_throttle2 > 0
    candidate_brake1 = candidate_brake1 * adjust_brake;
end

if candidate_brake2 > 0
    candidate_throttle1 = candidate_throttle1 * adjust_throttle;
end

data.throttle = candidate_throttle1;
data.brake = candidate_brake1;
data.old_distance1 = distance1;
data.old_distance2 = distance2;

end

