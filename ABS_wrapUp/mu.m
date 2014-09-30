function [ mu ] = mu( slip )
%MU Summary of this function goes here
%   Detailed explanation goes here
mu = -1.1 * exp(-20 * slip) + 1.1 - 0.4 * slip;

end

