function [ x_new, P_new ] = kalman_predict( x, P, u )
%KALMAN_PREDICT Summary of this function goes here
%   Detailed explanation goes here

global A B C D Ts

x_new = x + Ts .* (A * x + B * u);
P_new = A * P * A';


end

