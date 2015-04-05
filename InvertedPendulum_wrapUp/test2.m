% % System matrices!
% A=[2,0;1,-1]; B=[1;1];
% % Let's pick our favorite poles!
% P=[-0.5+1i,-0.5-1i];
% % Pole placement!
% K=place(A,B,P);

addpath('Localizations/')

clear; clc; close all;

global A  B C D K SSS Ts tf AIneq BIneq Aeq Beq LB UB mean std

mean = 0;
std = 1;
A = load('A.csv');
B = load('B.csv');
C = load('C.csv');
D = load('D.csv');
K = load('K.csv');
Ts = 0.01;
tf = 10;
SSS = load('SSS.csv');

AIneq = [];
BIneq = [];
Aeq = [];
Beq = [];
LB = [-25];
UB = [25];
stateOfInterests = [3,4];



% Sensor noise and uncertainty
R = [0.0001 0; 0, 0.00005];
R2 = [0.00005, 0; 0, 0.000001];
P = [0, 0, 0, 0;0, 0, 0, 0; 0, 0, 1000, 0; 0, 0, 0, 1000];


%% Two sensors

% Compute the solution!
x0 = [0;0;-0.4; 0]; t=0;
time = t : Ts : tf;
x = zeros(size(x0, 1), size(time, 2));
x(:, 1) = x0;
control = zeros(1, size(time,2));

initU = updateControlActuator(x0,0);
% initU = worstController(x0);
u = initU;
control(1) = initU;
x_track = zeros(size(x0, 1), size(time, 2));
x_track(:, 1) = x0;
measurements = x0(3);
measurements2 = x0(3);

for i = 2 : size(time, 2) - 1
    
    noise_x = normrnd(0, R(1, 1), 1, 1);
    noise_y = normrnd(0, R(2, 2), 1, 1);
    noise = [noise_x;noise_y];
    noise_x2 = normrnd(0, R2(1, 1), 1, 1);
    noise_y2 = normrnd(0, R2(2, 2), 1, 1);
    noise2 = [noise_x2;noise_y2];

    Z = C * x(:, i - 1) + noise;
    Z2 = C * x(:, i - 1) + noise2;
    measurements = [measurements, Z(2)];
    measurements2 = [measurements2, Z2(2)];
    
    %update
    [x_predict, P] = kalman_update(x_track(:, i-1), P, R, Z);
    [x_predict, P] = kalman_update(x_predict, P, R2, Z2);
    
    %predict
    [x_predict, P] = kalman_predict(x_predict, P, u);
    
    
%     [x, P] = kalman_filter(x, P, R, Z, u);
    x_track(:, i) = x_predict;

    u = updateControlActuator(x(:, i),u);
%     if i  > 1
%         u = updateControlActuator(x_track(:, i - 1),u);
%     end
%     u = worstController(x(:, i));
    x(:, i) = updateState(x(:, i) , u);
    control(i) = u;
       
end

% initU = updateControlActuator(x0,0);
% u = initU;
% oldState = x0;
% fail = false;
% for t = 0 : Ts : tf
%     newState = updateState(oldState,u);
%     u = updateControlActuator(oldState,u);
%     oldState = newState;
% 
%     newState = roundn(newState, -2);
%     if size(intersect(newState(stateOfInterests)', SSS(:, stateOfInterests), 'rows'), 1) == 0
%         fail = true;
%         break
%     end
% 
% end


% x0 = [0;0;0.03;-0.01];
% [worstU, worstC] = worstController(x0);
% newState = updateState(x0, worstU);
% [worstU, worstC] = worstController(x0);
% newState = updateState(x0, worstU);
% 
% newState = round(newState ./ granularity) * granularity;
% newState_mat = [newState + granularity, newState, newState - granularity];
% intersect(newState_mat(stateOfInterests, :)', S_sigma(:, stateOfInterests), 'rows')
% 
figure 
hold on

plot(time, x(3, :), 'r', 'LineWidth', 3);
plot(time, x_track(3, :), 'b', 'LineWidth', 1);
% plot(time, measurements, 'g', 'LineWidth', 1);
% plot(time, measurements2, 'k', 'LineWidth', 1);
legend('True angle', 'Predicted angle')
xlabel('time (s)')
title('Two sensors')

grid



%% One sensor

% Compute the solution!
x0 = [0;0;-0.4; 0]; t=0;
time = t : Ts : tf;
x = zeros(size(x0, 1), size(time, 2));
x(:, 1) = x0;
control = zeros(1, size(time,2));

initU = updateControlActuator(x0,0);
% initU = worstController(x0);
u = initU;
control(1) = initU;
x_track = zeros(size(x0, 1), size(time, 2));
x_track(:, 1) = x0;
measurements = x0(3);

for i = 2 : size(time, 2) - 1

    noise_x = normrnd(0, R(1, 1), 1, 1);
    noise_y = normrnd(0, R(2, 2), 1, 1);
    noise = [noise_x;noise_y];
    noise_x2 = normrnd(0, R2(1, 1), 1, 1);
    noise_y2 = normrnd(0, R2(2, 2), 1, 1);
    noise2 = [noise_x2;noise_y2];

    Z = C * x(:, i-1) + noise;
    Z2 = C * x(:, i-1) + noise2;
    measurements = [measurements, Z(2)];
    measurements2 = [measurements2, Z2(2)];
    %update
    [x_predict, P] = kalman_update(x_track(:, i-1), P, R, Z);
    %[x_predict, P] = kalman_update(x_predict, P, R2, Z2);
    
    %predict
    [x_predict, P] = kalman_predict(x_predict, P, u);
    
    
%     [x, P] = kalman_filter(x, P, R, Z, u);
    x_track(:, i) = x_predict;

    u = updateControlActuator(x(:, i-1),u);
%     if i  > 1
%         u = updateControlActuator(x_track(:, i - 1),u);
%     end
%     u = worstController(x(:, i));
    x(:, i) = updateState(x(:, i) , u);
    control(i) = u;
       
end

% initU = updateControlActuator(x0,0);
% u = initU;
% oldState = x0;
% fail = false;
% for t = 0 : Ts : tf
%     newState = updateState(oldState,u);
%     u = updateControlActuator(oldState,u);
%     oldState = newState;
% 
%     newState = roundn(newState, -2);
%     if size(intersect(newState(stateOfInterests)', SSS(:, stateOfInterests), 'rows'), 1) == 0
%         fail = true;
%         break
%     end
% 
% end


% x0 = [0;0;0.03;-0.01];
% [worstU, worstC] = worstController(x0);
% newState = updateState(x0, worstU);
% [worstU, worstC] = worstController(x0);
% newState = updateState(x0, worstU);
% 
% newState = round(newState ./ granularity) * granularity;
% newState_mat = [newState + granularity, newState, newState - granularity];
% intersect(newState_mat(stateOfInterests, :)', S_sigma(:, stateOfInterests), 'rows')
% 
figure 
hold on

plot(time, x(3, :), 'r', 'LineWidth', 3);
plot(time, x_track(3, :), 'b', 'LineWidth', 1);
% plot(time, measurements, 'g', 'LineWidth', 1);
legend('True angle', 'Predicted angle')
xlabel('time (s)')
title('One sensor')

grid



