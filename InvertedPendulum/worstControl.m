clear; clc; close all

addpath ./reliability/
addpath ./NerualNetwork/


A = load('A.csv');
B = load('B.csv');
C = load('C.csv');
D = load('D.csv');

% Q = C'*C;
% Q(1,1) = 5000;
% Q(3, 3) = 100;
% R = 1;
% [K] = lqr(A,B,Q,R);

sys_ss = ss(A,B,C,D);

% sys_ss = ss(A,B,C,D);

Ts = 0.01;

sys_d = c2d(sys_ss,Ts,'zoh');

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


sys_cl = ss(Ac,Bc,Cc,Dc,Ts);
% sys_ss = ss(Ac,Bc,Cc,Dc, Ts);

time = 0:Ts:5;
r =0*ones(size(time));

x0 = [0;0;-0.5;-0.5];  

x = zeros(size(time, 2), size(x0, 1));
x(1, :) = x0'; 
rr = 0;

% for i = 1 : size(time, 2) - 1
%     x_dot = Ac * x(i, :)' + Bc * rr;
%     x_new  = x(i, :)' + Ts * x_dot;
%     x(i + 1, :) = x_new';
% end

% [y,t,x]=lsim(sys_ss,r,time, x0);
% [y,t,x]=lsim(sys_d,r,time, x0);
[y,t,x]=lsim(sys_cl,r,time, x0);
figure

plot(time, x(:,3), 'r', 'LineWidth', 4)
xlabel('Time (sec)')
ylabel('Pendulum Angle (rad)')
title('Zero Input Response with Digital LQR Control')
grid






rmpath ./reliability/
rmpath ./NerualNetwork/