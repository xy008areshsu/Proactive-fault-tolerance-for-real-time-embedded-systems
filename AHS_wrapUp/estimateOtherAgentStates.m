function [ otherAgentStates ] = estimateOtherAgentStates( oldStateVector )
%ESTIMATEOTHERAGENTSTATES Summary of this function goes here
%   Detailed explanation goes here
global A B C D K Ts 


% %  newStateVector = oldStateVector + Ts .* (A - B * K) * oldStateVector;
%   newStateVector = oldStateVector + Ts .* (A*oldStateVector + B * actuatorVector);

this_d = oldStateVector(3);
this_v_l = oldStateVector(1);
this_v_f = oldStateVector(2);
d_d = 40;
bad_a_l = 10;
if this_d > d_d
    this_v_l = this_v_l + bad_a_l * Ts;
else
    this_v_l = this_v_l - bad_a_l * Ts;
end
otherAgentStates = [this_v_l];

end

