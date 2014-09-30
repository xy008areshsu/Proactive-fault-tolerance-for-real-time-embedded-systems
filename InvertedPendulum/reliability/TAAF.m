function [ TAAF ] = TAAF( A, activation_energy, k, absolute_T )
%TAAF Summary of this function goes here
%   Detailed explanation goes here 
    TAAF = A * exp(-activation_energy / (k * absolute_T)); 
%     if TAAF < 1
%         TAAF = 1;
%     end
end

