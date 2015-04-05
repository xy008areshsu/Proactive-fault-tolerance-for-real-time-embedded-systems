clear; clc; close all

global A B C D


%% Two sensors
dt = 1;
A = [1, 0, dt, 0; 0, 1, 0, dt; 0, 0, 1, 0; 0, 0, 0, 1];
B = [0;0;1;1];
C = [1, 0, 0, 0; 0, 1, 0, 0];
D = 0;




x = [0;6;0;0];
% x = [0;0;0;0];
P = [0, 0, 0, 0;0, 0, 0, 0; 0, 0, 1000, 0; 0, 0, 0, 1000];
u = 0;


true_values = [5, 10; 6, 8; 7, 6; 8, 4; 9, 2; 10, 0; 11, -2; 12, -4; 13, -6]';
for i = 1 : 10
    true_values = [true_values, true_values(:, end) + [1; -2]];
end

% pos_x = 0 : dt: 2 * pi;
% pos_y = sin(pos_x);
% true_values = [pos_x; pos_y];
R = [5 0; 0, 1];
R2 = [1, 0; 0, 5];
noise_x = normrnd(0, R(1, 1), 1, size(true_values, 2));
noise_y = normrnd(0, R(2, 2), 1, size(true_values, 2));
noise = [noise_x;noise_y];
measurements = true_values + noise;
noise_x2 = normrnd(0, R2(1, 1), 1, size(true_values, 2));
noise_y2 = normrnd(0, R2(2, 2), 1, size(true_values, 2));
noise2 = [noise_x2;noise_y2];
measurements2 = true_values + noise2;

%   measurements(1, 1) = 1000;  % assign some nonsense
%   measurements(1, 2) = 1000;  % assign some nonsense
    measurements(1, 3) = 0;  % assign some nonsense
  measurements(1, 4) = 0;  % assign some nonsense
%   measurements(1, 5) = 1000;  % assign some nonsense
%   measurements(1, 6) = 1000;  % assign some nonsense
% measurements = measurements';
speeds = ones(2, size(measurements, 2));
speeds(2, :) = -2 * speeds(2,:);
x_true = [true_values; speeds];
x_track = zeros(size(x, 1), size(measurements, 2));



for i = 1 : size(measurements, 2)
    Z = measurements(:, i);
    Z2 = measurements2(:, i);
    %predict
    [x, P] = kalman_predict(x, P, u);
    
    %update
    [x, P] = kalman_update(x, P, R, Z);
    [x, P] = kalman_update(x, P, R2, Z2);
    
%     [x, P] = kalman_filter(x, P, R, Z, u);
    x_track(:, i) = x;
end


figure
hold on 
plot(x_true(1, :),x_true(2, :), 'r', 'LineWidth', 2)
plot(x_track(1, :), x_true(2, :),'b', 'LineWidth', 2)
% plot(measurements(1, :), measurements(2, :), 'g', 'LineWidth', 2)
% plot(measurements2(1, :), measurements2(2, :), 'k', 'LineWidth', 2)
grid
legend('True Values', 'Filtered Values', ' Sensor 1 readings', 'Sensor 2 readings')
xlabel('X')
ylabel('Y')
title('Two sensors')




%% Only one sensor

x_track_one_sensor = zeros(size(x, 1), size(measurements, 2));

x = [4;12;0;0];
% x = [0;0;0;0];
P = [0, 0, 0, 0;0, 0, 0, 0; 0, 0, 1000, 0; 0, 0, 0, 1000];


for i = 1 : size(measurements, 2)
    Z = measurements(:, i);
    Z2 = measurements2(:, i);
    %predict
    [x, P] = kalman_predict(x, P, u);
    
    %update
    [x, P] = kalman_update(x, P, R, Z);
    %[x, P] = kalman_update(x, P, R2, Z2);
    
%     [x, P] = kalman_filter(x, P, R, Z, u);
    x_track_one_sensor(:, i) = x;
end


figure
hold on 
plot(x_true(1, :), x_true(2, :),'r', 'LineWidth', 2)
plot(x_track_one_sensor(1, :),x_true(2, :), 'b', 'LineWidth', 2)
% plot(measurements(1, :), measurements(2, :), 'g', 'LineWidth', 2)
grid
legend('True Values', 'Filtered Values', 'Sensor 1 readings')
xlabel('X')
ylabel('Y')
title('One sensor')