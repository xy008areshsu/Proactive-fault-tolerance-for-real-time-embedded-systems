clear; clc; close all

global SSS Ts tf AIneq BIneq Aeq Beq LB UB

Ts = 0.01;
SSS = load('SSS.csv');

AIneq = [];
BIneq = [];
Aeq = [];
Beq = [];
LB = [0];
UB = [250];
stateOfInterests = [1,2];

% Compute the solution!
x0 = [33;33;0]; t=0; tf=10;
time = t : Ts : tf;
x = zeros(size(x0, 1), size(time, 2));
x(:, 1) = x0;
control = zeros(1, size(time,2));

% initU = updateControlActuator(x0,0);
% initU = worstController(x0);
initU = UB;
u = initU;
control(1) = initU;
slip = zeros(1, size(time,2));


for i = 1 : size(time, 2) - 1
%     x = roundn(x, -2);
%     u = roundn(u, -2);
    x(:, i + 1) = updateState(x(:, i) , u);
     u = updateControlActuator(x(:, i),u);
%     u = worstController(x(:, i));
%      u = zeroController(x(:, i), UB);
    control(i+1) = u;
    slip(i) = max(0, 1 - x(2, i) / x(1, i));   
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



% [worstU, worstC] = worstController(x0);
% newState = updateState(x0, worstU);
% 
% newState = round(newState ./ granularity) * granularity;
% newState_mat = [newState + granularity, newState, newState - granularity];
% intersect(newState_mat(stateOfInterests, :)', S_sigma(:, stateOfInterests), 'rows')
% 
% figure 
% hold on
figure
plot(time, x(3, :), 'r', 'LineWidth', 2);
% plot(time, x(4, :), 'b', 'LineWidth', 2);

xlabel('time (s)')

grid

figure
plot(time(1: 400), slip(1:400), 'r', 'LineWidth', 2);
% plot(time, x(4, :), 'b', 'LineWidth', 2);

xlabel('time (s)')

grid


figure
hold on
plot(time, x(1, :), 'r', 'LineWidth', 2);
plot(time, x(2, :), 'b', 'LineWidth', 2);

xlabel('time (s)')

grid

