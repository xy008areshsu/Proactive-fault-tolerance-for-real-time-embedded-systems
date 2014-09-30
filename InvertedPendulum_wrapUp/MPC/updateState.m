function newStateVector = updateState(oldStateVector, actuatorVector)
%UPDATE Summary of this function goes here
%   Detailed explanation goes here
% 

global Ap Bp Cp Dp K Ts mean std


%  newStateVector = oldStateVector + Ts .* (A - B * K) * oldStateVector;
  actuatorVector = actuatorVector + mean + std .* randn(size(actuatorVector));
  newStateVector = oldStateVector + Ts .* (Ap*oldStateVector + Bp * actuatorVector);


end

