clear; clc; close all

addpath ./SVM/
addpath ./LG/
addpath ./NerualNetwork/
addpath ./reliability/

%% Initialization
h = 0.2;
x = [];  % state vars
u = [];  % control inputs


%% Define SSS
mass = 1500;       % mass of car
mass_wheel = 20;    % mass of one wheel
g = 9.8;
Fz = ((mass * g) / 4  + mass_wheel * g);
slip = -1 : 0.01 : 1;
longPart = Fx_Pacejka(Fz(1) * ones(1, size(slip, 2)), slip);
optSlip = slip(longPart(1, :) == min(longPart(1, :)));
safeRegion = 0.2;
slipHighThreshold = optSlip + (safeRegion);
slipLowThreshold = optSlip - (safeRegion);
SSS = [];
for Vx = 10 : 30
    for Vw = 0 : Vx
        slip = (Vw - Vx) / Vx;
        if slip <= slipHighThreshold  && slip >= slipLowThreshold 
            SSS = [SSS; [Vx, Vw]];
        end
    end
end
% safeStopDis = 55;
    
%% Generate S_3
S_3 = [];


for Vel_x = 10 : 30
    for Vel_w = 0 : Vel_x
        b = -3000;
        Vx = Vel_x;
        Vw = Vel_w;
        
        b = ABS_func(Vx, Vw);
        %     b = ABS_Wrong(Vx, Vw);
        [Vx, Vw] = updateStates(Vx, Vw, b, h);
           
        slip = (Vw - Vx) / Vx;
        if slip <= slipHighThreshold && slip >= slipLowThreshold
            S_3 = [S_3; [Vel_x, Vel_w]];
        end

        
    end
    
end






%% Generate S_1
S_1 = [];

for i = 1 : size(S_3, 1)
    
    Vx = S_3(i, 1);
    Vw = S_3(i, 2);

    b = ABS_Wrong(Vx, Vw);
  
    [new_Vx, new_Vw] = updateStates(Vx, Vw, b, h);
    
    slip = (Vw - Vx) / Vx;
    if slip <= slipHighThreshold && slip >= slipLowThreshold
        S_1 = [S_1; [Vx, Vw]];
    end
   
    
end

%% Generate S_2
S_2 = [];

for i = 1 : size(S_3, 1)
    
    Vx = S_3(i, 1);
    Vw = S_3(i, 2);

    b = ABS_Zero(Vx, Vw);
  
    [new_Vx, new_Vw] = updateStates(Vx, Vw, b, h);
    
    slip = (Vw - Vx) / Vx;
    if slip <= slipHighThreshold  && slip >= slipLowThreshold
        S_2 = [S_2; [Vx, Vw]];
    end
   
    
end
S_2 = [S_2;setdiff(SSS, [S_1; S_3], 'rows')];
% Generate S_2

% % Generate S_2
% S_3 = [S_3; setdiff(SSS, [S_1; S_2], 'rows')];

S_3 = setdiff(S_3, S_2, 'rows');
S_3 = setdiff(S_3, S_1, 'rows');
S_2 = setdiff(S_2, S_1, 'rows');
S_2 = setdiff(S_2, S_3, 'rows');
S_1 = setdiff(S_1, S_2, 'rows');
S_1 = setdiff(S_1, S_3, 'rows');

plot(S_3(:, 1), S_3(:, 2), 'rx', 'LineWidth', 4);
hold on
plot(S_2(:, 1), S_2(:, 2), 'bx', 'LineWidth', 4);
plot(S_1(:, 1), S_1(:, 2), 'gx', 'LineWidth', 4);

csvwrite('s1.csv', S_1);
csvwrite('s2.csv', S_2);
csvwrite('s3.csv', S_3);

%% Learning

fprintf('Start SVM\n');
X = [S_1;S_2;S_3];
y = [ones(size(S_1, 1), 1); 0 * ones(size(S_2, 1), 1); 0 * ones(size(S_3, 1), 1)];
svm;  % first use SVM

% Then we try neural networks
fprintf('Start Neural Networks\n');
X = [S_1; S_2; S_3];
% X = [S_2; S_3];
% X = X(:, 1:2);
y = [ones(size(S_1, 1), 1); 2 * ones(size(S_2, 1), 1); 3 * ones(size(S_3, 1), 1)];
% y = [ones(size(S_2, 1), 1); 2 * ones(size(S_3, 1), 1)];
neuralNetwork_ABS
%sim_LG
wrong = find((y~=pred) == 1);
fprintf('predicted value: \n')
[X(wrong, :), pred(wrong)]
fprintf('actual value: \n')
[X(wrong, :), y(wrong)]


%% TAAF

% Initial conditions
Vx = 25;  %state var
Vw = 25;  %state var
b = -1000;    % control input
h = 0.01;
time = 0;
x = 0;
states = [];
slip = [];
t_S_N = [];
t_S_FS = [];
t_S_F = [];

% update states
while Vx > 0.5 && time < 10
    b = ABS_func(Vx, Vw);
%     b = ABS_Wrong(Vx, Vw);
%     [Vx, Vw] = updateStates(Vx, Vw, b, h);
    [Vx, Vw, slipRatio] = updateStatesWithSlip(Vx, Vw, b, h);
    [pred, ex_time] = predict(Theta1, Theta2, [Vx, Vw], threshold);    
    slip = [slip; slipRatio];
    time = time + h;
    if pred == 1
        t_S_N = [t_S_N time];
    elseif pred == 2
        t_S_FS = [t_S_FS time];
    else
        t_S_F = [t_S_F time];
    end
    x = x + h * Vx;
    states = [states; [Vx, Vw]];
end

stop_time = time;
ThermalStressBatch








rmpath ./SVM/
rmpath ./LG/
rmpath ./NerualNetwork/
rmpath ./reliability/


