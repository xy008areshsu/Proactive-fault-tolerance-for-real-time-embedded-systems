function [ x_new, P_new ] = kalman_update( x, P, R, Z )
%KALMAN_UPDATE Summary of this function goes here
%   Detailed explanation goes here

global A B C D

threshold = 100;



error = Z - C * x;
if error(1) > threshold || error(2) > threshold
    x_new = x;
    P_new = P;
else
    S = C * P * C' + R;
    K = P * C' * inv(S);
    x_new = x + K * error;
    P_new = (eye(size(A)) - K * C) * P;
end


end

