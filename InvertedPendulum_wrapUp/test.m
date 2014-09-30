% % System matrices!
% A=[2,0;1,-1]; B=[1;1];
% % Let's pick our favorite poles!
% P=[-0.5+1i,-0.5-1i];
% % Pole placement!
% K=place(A,B,P);

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

% Compute the solution!
x0 = [0;0;-0.4; 0]; t=0; tf=10;
time = t : Ts : tf;
x = zeros(size(x0, 1), size(time, 2));
x(:, 1) = x0;
control = zeros(1, size(time,2));

initU = updateControlActuator(x0,0);
% initU = worstController(x0);
u = initU;
control(1) = initU;

for i = 1 : size(time, 2) - 1
    x(:, i + 1) = updateState(x(:, i) , u);
    u = updateControlActuator(x(:, i),u);
%     u = worstController(x(:, i));
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

plot(time, x(3, :), 'r', 'LineWidth', 2);
% plot(time, x(4, :), 'b', 'LineWidth', 2);
% legend('theta (rad)', 'rate (rad/s)')
xlabel('time (s)')

grid
