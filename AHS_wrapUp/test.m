% % System matrices!
% A=[2,0;1,-1]; B=[1;1];
% % Let's pick our favorite poles!
% P=[-0.5+1i,-0.5-1i];
% % Pole placement!
% K=place(A,B,P);
clear; clc; close all
global A  B C D K SSS Ts tf AIneq BIneq Aeq Beq LB UB

A = load('A.csv');
B = load('B.csv');
C = load('C.csv');
D = load('D.csv');
sys_ss= ss(A, B, C, D);
co = ctrb(sys_ss);
controllability = rank(co)
Q = zeros(size(A));
R = 1;
Q(1, 1) = 0;
Q(2, 2) = 10;

K = lqr(A, B, Q, R);
sp = 40;

% D = load('D.csv');
% K = load('K.csv');

Ts = 0.01;
% SSS = load('SSS.csv');

AIneq = [];
BIneq = [];
Aeq = [];
Beq = [];
LB = [-20];
UB = [20];
% stateOfInterests = [3,4];

t=0; tf=10;
time = t : Ts : tf;
% x = zeros(size(A, 1), size(time, 2));

% Compute the solution!
% S_sigma
S_sigma = [];
for v = 5 : 35
    for d = 35 : 45
        x0 = [v; d];
        sys = ss(A, B, C, D);
        Nbar = rscale(sys,K)*sp/size(time, 1);
        u = 1 * ones(size(time));
        sys_cl = ss(A-B*K,B*Nbar,C,D);
        [y, t, x] = lsim(sys_cl,u,time,x0);
        if size(x(x(:, 2) < 35 | x(:, 2) > 45, 2), 1) == 0
            S_sigma = [S_sigma, x0];
        end
    end
end

% S_1
S_1 = [];
for i = 1 : size(S_sigma, 2)
    x0 = S_sigma(:, i);
%     sys = ss(A, B, C, D);
%     Nbar = rscale(sys,K)*sp/size(time, 1);
%     u = 1;
%     sys_cl = ss(A-B*(-K),-B*Nbar,C,D);
%     [y, t, x] = lsim(sys_cl,[1, 1],[0, Ts],x0);
%     x = roundn(x, 0);
    x_new_ub = x0 + Ts * (A * x0 + B * UB);
    x_new_ub = x_new_ub + Ts * (A * x_new_ub + B * UB);
    x_new_ub = x_new_ub + Ts * (A * x_new_ub + B * UB);
    x_new_ub = x_new_ub + Ts * (A * x_new_ub + B * UB);
    x_new_lb = x0 + Ts * (A * x0 + B * LB);
    x_new_lb = x_new_lb + Ts * (A * x_new_lb + B * LB);
    x_new_lb = x_new_lb + Ts * (A * x_new_lb + B * LB);
    x_new_lb = x_new_lb + Ts * (A * x_new_lb + B * LB);
    x_new_ub = ceil(x_new_ub);
    x_new_lb = ceil(x_new_lb);
    if size(intersect(x_new_lb', S_sigma', 'rows'), 1) ~= 0 && size(intersect(x_new_ub', S_sigma', 'rows'), 1) ~= 0
        S_1 = [S_1, x0];
    end
end

% S_2
S_2 = [];
for i = 1 : size(S_sigma, 2)
    x0 = S_sigma(:, i);
%     sys = ss(A, B, C, D);
%     Nbar = rscale(sys,K)*sp/size(time, 1);
%     u = 1;
%     sys_cl = ss(A-B*(-K),-B*Nbar,C,D);
%     [y, t, x] = lsim(sys_cl,[1, 1],[0, Ts],x0);
%     x = roundn(x, 0);
    x_new = x0 + Ts * (A * x0 + B * 0);
    x_new = x_new + Ts * (A * x_new + B * 0);
    x_new = x_new + Ts * (A * x_new + B * 0);
    x_new = x_new + Ts * (A * x_new + B * 0);
    x_new = ceil(x_new);

    if size(intersect(x_new', S_sigma', 'rows'), 1) ~= 0 
        S_2 = [S_2, x0];
    end
end
S_2 = setdiff(S_2', S_1', 'rows')';

%S_3
S_3 = setdiff(S_sigma', union(S_1', S_2', 'rows'), 'rows')';

figure
hold on
plot(S_3(1, :), S_3(2, :), 'rx', 'LineWidth', 4)
plot(S_2(1, :), S_2(2, :), 'bx', 'LineWidth', 4)
plot(S_1(1, :), S_1(2, :), 'gx', 'LineWidth', 4)
grid
legend('S_3', 'S_2', 'S_1')
xlabel('Speed (m/s)')
ylabel('Distance (m)')

    
% x(:, 1) = x0;

% A = A - B * K;
% B = B * Nbar;

% u = 1;
% for ti = 2 : size(time, 2)
%     x(:, ti) = x(:, ti - 1) + A * x(:,  ti - 1) + B * u;
% end  




% figure 
% hold on
% % plot(time, x(1, :), 'r', 'LineWidth', 2);
% % plot(time, x(2, :), 'b', 'LineWidth', 2);
% plot(time, x(:, 1), 'r', 'LineWidth', 2);
% plot(time, x(:, 2), 'b', 'LineWidth', 2);
% legend('speed', 'distance')
% xlabel('time (s)')
% 
% grid



% x = zeros(size(x0, 1), size(time, 2));
% x(:, 1) = x0;
% control = zeros(1, size(time,2));
% 
% initU = updateControlActuator(x0,0);
% % initU = worstController(x0);
% u = initU;
% control(1) = initU;
% 
% for i = 1 : size(time, 2) - 1
%     x(:, i + 1) = updateState(x(:, i) , u);
%     u = updateControlActuator(x(:, i),u);
% %     u = worstController(x(:, i));
%     control(i) = u;
%        
% end
% 
% % initU = updateControlActuator(x0,0);
% % u = initU;
% % oldState = x0;
% % fail = false;
% % for t = 0 : Ts : tf
% %     newState = updateState(oldState,u);
% %     u = updateControlActuator(oldState,u);
% %     oldState = newState;
% % 
% %     newState = roundn(newState, -2);
% %     if size(intersect(newState(stateOfInterests)', SSS(:, stateOfInterests), 'rows'), 1) == 0
% %         fail = true;
% %         break
% %     end
% % 
% % end
% 
% 
% 
% % [worstU, worstC] = worstController(x0);
% % newState = updateState(x0, worstU);
% % 
% % newState = round(newState ./ granularity) * granularity;
% % newState_mat = [newState + granularity, newState, newState - granularity];
% % intersect(newState_mat(stateOfInterests, :)', S_sigma(:, stateOfInterests), 'rows')
% % 
% figure 
% hold on
% 
% plot(time, x(1, :), 'r', 'LineWidth', 2);
% plot(time, x(2, :), 'b', 'LineWidth', 2);
% legend('speed', 'distance')
% xlabel('time (s)')
% 
% grid
