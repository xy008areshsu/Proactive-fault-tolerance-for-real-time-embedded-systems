function newStateVector = updateState(oldStateVector, actuatorVector)
%UPDATE Summary of this function goes here
%   Detailed explanation goes here
% 

global A B C D K Ts mean std


%  newStateVector = oldStateVector + Ts .* (A - B * K) * oldStateVector;
    actuatorVector = actuatorVector + mean + std .* randn(size(actuatorVector));
%     actuatorVector = awgn(actuatorVector, 100);
  newStateVector = oldStateVector + Ts .* (A*oldStateVector + B * actuatorVector);


end

