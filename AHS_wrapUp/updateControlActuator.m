function [ newActuatorVector, new_old_e, new_E ] = updateControlActuator(stateVector, oldActuatorVector, old_e, E)
%ABS_FUNC Summary of this function goes here
%   Detailed explanation goes here
global A B C D K Ts UB LB

%         newActuatorVector = -K * stateVector;
%         newActuatorVector = min(UB, max(LB, newActuatorVector));

kp = 100;
kd = 400;
ki = 1;

this_d = stateVector(3);
this_v_l = stateVector(1);
this_v_f = stateVector(2);
d_d = 40;

e = this_d - d_d;
e_dot = e - old_e;
new_E = E + e;
new_old_e = e;
newActuatorVector = kp * e + kd * e_dot + ki * new_E;

end

