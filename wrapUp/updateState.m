function newStateVector = updateState(oldStateVector, actuatorVector)
%UPDATE Summary of this function goes here
%   Detailed explanation goes here
% 

global A B C D K Ts OtherId systemType




%  newStateVector = oldStateVector + Ts .* (A - B * K) * oldStateVector;
  newStateVector = oldStateVector + Ts .* (A*oldStateVector + B * actuatorVector);


end

