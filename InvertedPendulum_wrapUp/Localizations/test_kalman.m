clear; clc; close all

global A B C D 

dt = 0.1;
A = [1, 0, dt, 0; 0, 1, 0, dt; 0, 0, 1, 0; 0, 0, 0, 1];
B = [0;0;1;1];
C = [1, 0, 0, 0; 0, 1, 0, 0];
D = 0;


R = [0.2 0; 0, 0.2];

x = [4;12;0;0];
P = [0, 0, 0, 0;0, 0, 0, 0; 0, 0, 1000, 0; 0, 0, 0, 1000];
u = 0;


true_values = [5, 10; 6, 8; 7, 6; 8, 4; 9, 2; 10, 0]';
noise_x = normrnd(0, R(1, 1), 1, size(true_values, 2));
noise_y = normrnd(0, R(2, 2), 1, size(true_values, 2));
noise = [noise_x;noise_y];
measurements = true_values + noise;
% measurements(1, 3) = 1000;  % assign some nonsense
% measurements(1, 2) = 1000;  % assign some nonsense
 measurements(1, 3) = 1000000000;  % assign some nonsense
% measurements(1, 4) = 1000;  % assign some nonsense
% measurements(1, 5) = 1000;  % assign some nonsense
% measurements(1, 6) = 1000;  % assign some nonsense
% measurements = measurements';
x_track = zeros(size(x, 1), size(measurements, 2));


for i = 1 : size(measurements, 2)
    Z = measurements(:, i);
    %predict
    [x, P] = kalman_predict(x, P, u);
    
    %update
    [x, P] = kalman_update(x, P, R, Z);
    
%     [x, P] = kalman_filter(x, P, R, Z, u);
    x_track(:, i) = x;
end


figure
hold on 
plot(true_values(1, :), true_values(2, :), 'r', 'LineWidth', 2)
plot(x_track(1, :), x_track(2, :), 'b', 'LineWidth', 2)
grid
legend('True Values', 'Filtered Values')
xlabel('X')
ylabel('Y')

