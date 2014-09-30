clear; clc; close all

addpath ./reliability/
addpath ./NerualNetwork/
addpath ./LG/

A = load('A1.csv');
B = load('B1.csv');
C = load('C1.csv');
D = load('D1.csv');

sys_ss = ss(A,B,C,D);

Ts = 0.1;  % sampling time

sys_d = c2d(sys_ss,Ts,'zoh');

co = ctrb(sys_d);
ob = obsv(sys_d);

controllability = rank(co)
observability = rank(ob)


A = sys_d.a;
B = sys_d.b;
C = sys_d.c;
D = sys_d.d;
Q = load('Q2.csv');
R = load('R1.csv');
[K] = dlqr(A,B,Q,R);

Nbar = 6.95;

Ac = (A-B*K);
Bc = B * Nbar;
Cc = C;
Dc = D;



sys_cl = ss(Ac,Bc,Cc,Dc, Ts);

time = 0:Ts:10;
r =0*ones(size(time));
theta_des = 0 *ones(size(time));

% x0 = [0;0.1;0];


% [y,t, x] = lsim(sys_cl,theta_des, time, x0);
% x0 = [0;0;0];
% [y,t,x]=lsim(sys_cl,theta_des,0 : Ts : Ts, x0);
% 
% 
% zero_K = 0 * K;
% zero_Ac = (A-B*zero_K);
% zero_Bc = Bc;
% zero_Cc = Cc;
% zero_Dc = Dc;
% sys_cl_zero = ss(zero_Ac,zero_Bc,zero_Cc,zero_Dc, Ts);
% 
% wrong_K = -K;
% wrong_Ac = (A-B*wrong_K);
% wrong_Bc = Bc;
% wrong_Cc = Cc;
% wrong_Dc = Dc;
% sys_cl_wrong = ss(wrong_Ac,wrong_Bc,wrong_Cc,wrong_Dc, Ts);
% 
% 
% 
% 
% [y,t,x1]=lsim(sys_cl_zero,[0 0],0 : Ts : Ts, x0);
% x0 = x1(end, :);
% [y,t,x]=lsim(sys_cl,theta_des,time, x0);
% x = [x1 ; x];
% t = [t;t(end)+Ts; t(end) + 2*Ts];
% 
% 
% figure
% hold
% plot(t, x(:,1), 'r', 'LineWidth', 2)
% plot(t, x(:,2), 'g', 'LineWidth', 2)
% plot(t, x(:,3), 'b', 'LineWidth', 2)
% xlabel('time (sec)');
% ylabel('pitch angle (rad)');
% title('Closed-Loop Step Response: DLQR');



%% computer parameters

% time_to_update = 0;
% wrong_cycle = 1;
wrong_K = -K;
wrong_Ac = (A-B*wrong_K);
wrong_Bc = Bc;
wrong_Cc = Cc;
wrong_Dc = Dc;
sys_cl_wrong = ss(wrong_Ac,wrong_Bc,wrong_Cc,wrong_Dc, Ts);


zero_K = 0 * K;
zero_Ac = (A-B*zero_K);
zero_Bc = Bc;
zero_Cc = Cc;
zero_Dc = Dc;
sys_cl_zero = ss(zero_Ac,zero_Bc,zero_Cc,zero_Dc, Ts);


r_N = [0 0 0];   % Noise for S_N
r_zero = [0 0 0];   % Noise for S_FS


%% SSS
alpha = 0.3;    % SSS for angle of attack
q = 0.1;        % SSS for pitch rate
theta = 0.3;    % SSS for pitch angle
SSS = load('SSS_pitch1.csv');


%% S_3
S_3 = [];

fprintf('Start S_3\n');

for i = 1 : size(SSS, 2)
        % The first cycle does not apply control force due to the control period delay
        x0 = SSS(:, i); 
        [y,t,x1]=lsim(sys_cl_zero,[0 0],0 : Ts : Ts, x0);
        if size(find(abs(x1(:, 3)) > theta), 1) == 0 && size(find(abs(x1(:, 2)) > q), 1) == 0 && size(find(abs(x1(:, 1)) > alpha), 1) == 0
%             && size(find(abs(x1(:, 4)) > theta_dot), 1) == 0
            x0 = x1(end, :);
            [y,t,x]=lsim(sys_cl,theta_des,time, x0);
            if size(find(abs(x(:, 3)) > theta), 1) == 0 && size(find(abs(x(:, 2)) > q), 1) == 0 && size(find(abs(x(:, 1)) > alpha), 1) == 0
                S_3 = [S_3 SSS(:, i)];
            end
        end
end

% plot(S_3(1, :), S_3(2, :), 'rx', 'LineWidth', 4)



%% Define S_1

fprintf('start S_1\n')

S_1 = [];
for i = 1 : size(S_3, 2)
    x0 = S_3(:, i);
    [y, t, x] = lsim(sys_cl_wrong, r_N, 0: Ts : 2 * Ts, x0);
    if size(find(abs(x(:, 3)) > theta), 1) == 0 && size(find(abs(x(:, 2)) > q), 1) == 0 && size(find(abs(x(:, 1)) > alpha), 1) == 0
        S_1 = [S_1 S_3(:, i)];
    end  
end

%% Define S_2

fprintf('start S_2\n')

S_2 = [];
for i = 1 : size(S_3, 2)
    x0 = S_3(:, i); 
    [y, t, x] = lsim(sys_cl_zero, r_zero, 0: Ts : 2 * Ts, x0);
    if size(find(abs(x(:, 3)) > theta), 1) == 0 && size(find(abs(x(:, 2)) > q), 1) == 0 && size(find(abs(x(:, 1)) > alpha), 1) == 0
        S_2 = [S_2 S_3(:, i)];
    end  
end

% plot(S_3(1, :), S_3(2, :), 'rx', 'LineWidth', 4)
% hold
% plot(S_2(1, :), S_2(2, :), 'bx', 'LineWidth', 4)
% plot(S_1(1, :), S_1(2, :), 'gx', 'LineWidth', 4)
% legend('S_3', 'S_2', 'S_1')
% title(strcat('Regions with control period of:  ', num2str(Ts), 's'))


%% Get TAAF
stop_time = 5;
t_S_N = 0.1 : 0.01 : 5;
t_S_FS = [];
t_S_F = 0 : 0.01 : 0.1;

ThermalStressBatch;

% %% Plot
% 
% figure
% plot(S_3_theta, S_3_theta_dot, 'rx', 'LineWidth', 4)
% hold
% plot(S_2_theta, S_2_theta_dot, 'bx', 'LineWidth', 4)
% 
% plot(S_1_theta, S_1_theta_dot, 'gx', 'LineWidth', 4)
% 
% grid
% xlabel('theta (rad)')
% ylabel('thetaDot (rad/sec)')


%% Traing Theta values

S_3 = setdiff(S_3', S_2', 'rows');
S_2 = setdiff(S_2', S_1', 'rows');
S_1 = S_1';
% S_1 = S_1(randi(size(S_1,1), 1308, 1), :);
% S_2 = S_2(randi(size(S_2,1), 1308, 1), :);
% S_2 = [S_2; S_2];
% S_3 = [S_3; S_3; S_3; S_3; S_3];

X = [S_1; S_2; S_3];
% X = [S_2; S_3];
% X = X(:, 1:2);
y = [ones(size(S_1, 1), 1); 2 * ones(size(S_2, 1), 1); 3 * ones(size(S_3, 1), 1)];
% y = [ones(size(S_2, 1), 1); 2 * ones(size(S_3, 1), 1)];
neuralNetwork_pitch
%sim_LG
wrong = find((y~=pred) == 1);
fprintf('predicted value: \n')
[X(wrong, :), pred(wrong)]
fprintf('actual value: \n')
[X(wrong, :), y(wrong)]

rmpath ./reliability/
rmpath ./NerualNetwork/
rmpath ./LG/