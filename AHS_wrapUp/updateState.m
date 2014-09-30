function newStateVector = updateState(oldStateVector, actuatorVector)
%UPDATE Summary of this function goes here
%   Detailed explanation goes here
% 

global A B C D K Ts 


% %  newStateVector = oldStateVector + Ts .* (A - B * K) * oldStateVector;
%   newStateVector = oldStateVector + Ts .* (A*oldStateVector + B * actuatorVector);

this_d = oldStateVector(3);
this_v_l = oldStateVector(1);
this_v_f = oldStateVector(2);
d_d = 40;

                this_d = this_d + (this_v_l - this_v_f) * Ts;
                oldStateVector(3) = this_d;
                this_v_l = estimateOtherAgentStates(oldStateVector);
%                 if this_d > 40
%                    this_v_l = this_v_l + bad_a_l * Ts;
%                 else
%                    this_v_l = this_v_l - bad_a_l * Ts;
%                 end
                
%                 e = this_d - d_d;
%                 e_dot = e - old_e;
%                 E = E + e;
%                 old_e = e;
%                 u_f = kp * e + kd * e_dot + ki * E;
                this_v_f = this_v_f + Ts * actuatorVector;
                
                newStateVector = [this_v_l; this_v_f; this_d];


end

