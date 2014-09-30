function [ aging_factor ] = aging_factor( A, activation_energy, k, absolute_T)
%AGING_FACTOR Summary of this function goes here
%   Detailed explanation goes here
    aging_factor = A * exp(-activation_energy / (k * absolute_T));   % A, prefactor

end

