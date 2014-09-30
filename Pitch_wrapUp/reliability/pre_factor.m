function [ A ] = pre_factor( Tamb, activation_energy, k )
%PRE_FACTOR Summary of this function goes here
%   Detailed explanation goes here

    TAAF = 1; % Under normal tempreture, TAAF should be 1
    A = TAAF / (exp(-activation_energy / (k * Tamb)));
    

end

