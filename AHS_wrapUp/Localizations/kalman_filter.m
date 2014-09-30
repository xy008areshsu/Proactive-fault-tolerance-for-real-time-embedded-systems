function [ x_new, P_new ] = kalman_filter( x, P, R, Z, u )
%KALMAN_FILTER Summary of this function goes here
%   P: prediction uncertainty matrix, in terms of std(standard deviation
%   R: measurement uncertainty matrix, aka, measurement noise
%   Z: measurement data, sensor data

global A B C D 

% fisrt prediction
x_new = A * x + B * u;
P_new = A * P * A';

% measurement update
error = Z - C * x_new;
S = C * P_new * C' + R;
K = P_new * C' * inv(S);
x_new = x_new + K * error;
P_new = (eye(size(A)) - K * C) * P_new;

end

