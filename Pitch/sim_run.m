clear; clc; close all

addpath ./reliability/
addpath ./NerualNetwork/

% M = 0.5;
% m = 0.2;
% b = 0.1;
% I = 0.006;
% g = 9.8;
% l = 0.3;
% 
% p = I*(M+m)+M*m*l^2; %denominator for the A and B matrices

% A = [0      1              0           0;
%      0 -(I+m*l^2)*b/p  (m^2*g*l^2)/p   0;
%      0      0              0           1;
%      0 -(m*l*b)/p       m*g*l*(M+m)/p  0];
% B = [     0;
%      (I+m*l^2)/p;
%           0;
%         m*l/p];
% C = [1 0 0 0;
%      0 0 1 0];
% D = [0;
%      0];

A = load('A.csv');
B = load('B.csv');
C = load('C.csv');
D = load('D.csv');

% states = {'x' 'x_dot' 'phi' 'phi_dot'};
% inputs = {'u'};
% outputs = {'x'; 'phi'};

% sys_ss = ss(A,B,C,D,'statename',states,'inputname',inputs,'outputname',outputs);

sys_ss = ss(A,B,C,D);

Ts = 0.1;

sys_d = c2d(sys_ss,Ts,'zoh');

co = ctrb(sys_d);
ob = obsv(sys_d);

controllability = rank(co);
observability = rank(ob);


A = sys_d.a;
B = sys_d.b;
C = sys_d.c;
D = sys_d.d;
Q = C'*C;
Q(1,1) = 5000;
Q(3, 3) = 100;
R = 1;
[K] = dlqr(A,B,Q,R);

Ac = [(A-B*K)];
Bc = [B];
Cc = [C];
Dc = [D];

% states = {'x' 'x_dot' 'phi' 'phi_dot'};
% inputs = {'r'};
% outputs = {'x'; 'phi'};

% sys_cl = ss(Ac,Bc,Cc,Dc,Ts,'statename',states,'inputname',inputs,'outputname',outputs);
sys_cl = ss(Ac,Bc,Cc,Dc, Ts);

time = 0:Ts:5;
r =0*ones(size(time));



zero_K = 0 * K;
zero_Ac = [(A-B*zero_K)];
zero_Bc = [B];
zero_Cc = [C];
zero_Dc = [D];
% sys_cl_zero = ss(zero_Ac,zero_Bc,zero_Cc,zero_Dc,'statename',states,'inputname',inputs,'outputname',outputs);
sys_cl_zero = ss(zero_Ac,zero_Bc,zero_Cc,zero_Dc);
 x0 = [0;0;-0.5;-0.5];        
[y,t,x1]=lsim(sys_cl_zero,[0 0],0 : Ts : Ts, x0);
x0 = x1(end, :);
[y,t,x]=lsim(sys_cl,r,time, x0);
x = [x1 ; x];
t = [t;t(end)+Ts; t(end) + 2*Ts];
figure
% [AX,H1,H2] = plotyy(t,x(:,2),t,x(:,4),'plot');
% set(get(AX(1),'Ylabel'),'String','pendulum position (meters)')
% set(get(AX(2),'Ylabel'),'String','pendulum rate (rad/sec)')
% title('Zero Input Response with Digital LQR Control')
% grid
plot(t, x(:,3), 'r', 'LineWidth', 4)
xlabel('Time (sec)')
ylabel('Pendulum Angle (rad)')
title('Zero Input Response with Digital LQR Control')
grid
% plot(x(:,3), x(:, 4), 'mx', 'LineWidth', 4)
% grid



%% computer parameters
% control_period = 0.36;
% time_to_update = 0;
% wrong_cycle = 1;
wrong_K = -K;
wrong_Ac = [(A-B*wrong_K)];
wrong_Bc = [B];
wrong_Cc = [C];
wrong_Dc = [D];
% sys_cl_wrong = ss(wrong_Ac,wrong_Bc,wrong_Cc,wrong_Dc,'statename',states,'inputname',inputs,'outputname',outputs);
sys_cl_wrong = ss(wrong_Ac,wrong_Bc,wrong_Cc,wrong_Dc);


zero_K = 0 * K;
zero_Ac = [(A-B*zero_K)];
zero_Bc = [B];
zero_Cc = [C];
zero_Dc = [D];
% sys_cl_zero = ss(zero_Ac,zero_Bc,zero_Cc,zero_Dc,'statename',states,'inputname',inputs,'outputname',outputs);
sys_cl_zero = ss(zero_Ac,zero_Bc,zero_Cc,zero_Dc);


r_N = [0 0 0];   % Noise for S_N
r_zero = [0 0 0];   % Noise for S_FS


%% SSS
 theta = 0.5;
theta_dot = 0.5;
SSS = load('SSS.csv');
% theta = SSS(1);
% theta_dot = SSS(2);
% step = 0.01;

%% S_sigma
S_3 = [];
% S_3_theta = [];
% S_3_theta_dot = [];

for i = 1 : size(SSS, 2)
        % The first cycle does not apply control force due to the control period delay
        x0 = [0;0;SSS(1, i); SSS(2, i)];
        [y,t,x1]=lsim(sys_cl_zero,[0 0],0 : Ts : Ts, x0);
        if size(find(abs(x1(:, 3)) > theta), 1) == 0 
%             && size(find(abs(x1(:, 4)) > theta_dot), 1) == 0
            x0 = x1(end, :);
            [y,t,x]=lsim(sys_cl,r,time, x0);
            if size(find(abs(x(:, 3)) > theta ), 1) == 0
                S_3 = [S_3 [SSS(1, i); SSS(2, i)]];
            end
        end
end

plot(S_3(1, :), S_3(2, :), 'rx', 'LineWidth', 4)



%% Define S_N
% S_1_theta = [];
% S_1_theta_dot = [];
S_1 = [];
for i = 1 : size(S_3, 2)
    x0 = [0; 0; S_3(1, i); S_3(2, i)];
    [y, t, x] = lsim(sys_cl_wrong, r_N, 0: Ts : 2 * Ts, x0);
    if size(find(abs(y(:, 2)) > theta), 1) == 0
        S_1 = [S_1 [S_3(1, i); S_3(2, i)]];
    end  
end

%% Define S_FS
S_2_theta = [];
S_2_theta_dot = [];
S_2 = [];
for i = 1 : size(S_3, 2)
    x0 = [0; 0; S_3(1, i); S_3(2, i)];
    [y, t, x] = lsim(sys_cl_zero, r_zero, 0: Ts : 2 * Ts, x0);
    if size(find(abs(y(:, 2)) > theta), 1) == 0
        S_2 = [S_2 [S_3(1, i); S_3(2, i)]];
    end  
end

plot(S_3(1, :), S_3(2, :), 'rx', 'LineWidth', 4)
hold
plot(S_2(1, :), S_2(2, :), 'bx', 'LineWidth', 4)
plot(S_1(1, :), S_1(2, :), 'gx', 'LineWidth', 4)
legend('S_3', 'S_2', 'S_1')
title(strcat('Regions with control period of:  ', num2str(Ts), 's'))


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
S_1 = [S_1_theta', S_1_theta_dot'];
S_2 = [S_2_theta', S_2_theta_dot'];
S_3 = [S_3_theta', S_3_theta_dot'];
S_3 = setdiff(S_3, S_2, 'rows');
S_2 = setdiff(S_2, S_1, 'rows');
S_1 = (S_1(abs(S_1(:, 1)) > 0.2, :));
X = [S_1; S_2; S_3];
y = [ones(size(S_1, 1), 1); 2 * ones(size(S_2, 1), 1); 3 * ones(size(S_3, 1), 1)];
neuralNetwork
wrong = find((y~=pred) == 1);
fprintf('predicted value: \n')
[X(wrong, :), pred(wrong)]
fprintf('actual value: \n')
[X(wrong, :), y(wrong)]

rmpath ./reliability/
rmpath ./NerualNetwork/