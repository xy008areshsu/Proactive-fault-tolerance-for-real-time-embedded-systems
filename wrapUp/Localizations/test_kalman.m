clear; clc; close all

global A B C D

dt = 0.1;
A = [1, 0, dt, 0; 0, 1, 0, dt; 0, 0, 1, 0;0, 0, 0, 1];
B = [0;0;0;0];
C = [1, 0, 0, 0; 0, 1, 0, 0];
D = 0;


R = [0.1, 0; 0, 0.1];

x = [4;12;0;0];
P = [0, 0, 0, 0;0, 0, 0, 0; 0, 0, 1000, 0; 0, 0, 0, 1000];
u = 0;

measurements = [5, 10; 6, 8;7, 6;8, 4;9, 2;10, 0];
measurements = measurements';

for i = 1 : size(measurements, 2)
    Z = measurements(:, i);
    [x, P] = kalman_filter(x, P, R, Z, u);
end

