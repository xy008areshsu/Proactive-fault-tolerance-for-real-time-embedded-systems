clear; clc; close all

% System matrices!
A=[2,0;1,-1]; B=[1;1];
% Let's pick our favorite poles!
P=[-0.5+1i,-0.5-1i];
% P=[-0.1, 0.1];
% Pole placement!
K=place(A,B,P);

% Compute the solution!
x0 = [1;1]; t=0; tf=15; Ts = 0.01;
time = t : Ts : tf;
x = zeros(size(x0, 1), size(time, 2));
x(:, 1) = x0;
control = zeros(1, size(time,2));
control(1) = -K * x0;




for i = 1 : size(time, 2) - 1
    x(:, i + 1) = x(:, i) + Ts .* (A*x(:, i) + B * control(i));
%     control(i+1) = -K * x(:, i+1);   
    control(i+1) = -K * x(:, i);
end

figure
hold on

plot(time, x(1, :), 'r', 'LineWidth', 2);
plot(time, x(2, :), 'b', 'LineWidth', 2);
legend('theta (rad)', 'rate (rad/s)')
xlabel('time (s)')

grid
% while (t<tf);
% x=x+dt.*(A-B*K)*x;
% t=t+dt;
% plot(t, x(1));
% grid
% end; 