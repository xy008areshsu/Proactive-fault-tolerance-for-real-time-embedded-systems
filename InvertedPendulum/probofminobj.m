function [ cost ] = probofminobj(u, x0)
%PROBOFMINOBJ Summary of this function goes here
%   Detailed explanation goes here

x_des = [0;0;0;0];

A = load('A.csv');
B = load('B.csv');


Ts = 0.01;

x_dot = A * x0 + B * u;
x_new  = x0 + Ts * x_dot;


cost = 1/(2 * size(x0, 1)) * sum((x_new - x_des).^2);

end

