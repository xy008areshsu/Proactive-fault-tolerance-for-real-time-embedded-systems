clear; clc; close all

global UB LB

LB = [-40];
UB = [40];

Ts = 0.06;

d_d = 40;    % desired distance

kp = 100;
kd = 400;
ki = 1;

time = 0 : Ts : 10;
time = time';

bad_a_l = 10;

% d = zeros(size(time, 1), 1);
% v_l = zeros(size(time, 1), 1);
% v_f = zeros(size(time, 1), 1);
% u_f = zeros(size(time, 1), 1);
% e = zeros(size(time, 1), 1);
% e_dot = zeros(size(time, 1), 1);
% E = zeros(size(time, 1), 1);
% bad_a_l = 10;
% 
% d(1, 1) = 45;
% v_l(1, 1) = 45;
% v_f(1, 1) = 10;
% e(1, 1) = d(1, 1) - d_d;
% e_dot(1, 1) = 0;
% E(1, 1) = 0;
% 
% for i = 2 : size(time, 1)
%     d(i, 1) = d(i - 1, 1) + (v_l(i - 1, 1) - v_f(i - 1, 1)) * Ts;
%     if d(i, 1) > 40
%         v_l(i, 1) = v_l(i - 1, 1) + bad_a_l * Ts;
%     else
%         v_l(i, 1) = v_l(i - 1, 1) - bad_a_l * Ts;
%     end
%     
%     e(i, 1) = d(i, 1) - d_d;
%     e_dot(i, 1) = e(i, 1) - e(i - 1, 1);
%     E(i, 1) = E(i - 1, 1) + e(i, 1);
%     u_f(i, 1) = kp * e(i, 1) + kd * e_dot(i, 1) + ki * E(i, 1);
%     v_f(i, 1) = v_f(i - 1, 1) + Ts * u_f(i, 1);
% end
% 
% figure
% hold on
% plot(time, d, 'r', 'LineWidth', 2);
% % plot(time, u_f, 'b', 'LineWidth', 4);
% 
% grid



% S_sigma
S_sigma = [];
fail = false;
for v_l = 10 : 45
    for v_f = 10 : 45
        for d = 35 : 45
            
            this_d = d;
            this_v_l = v_l;
            this_v_f = v_f;
            old_e = this_d - d_d;
            E = 0;
            fail = false;
            %Loop starts
            for i = 2 : size(time, 1)
                this_d = this_d + (this_v_l - this_v_f) * Ts;
                if this_d > 40
                   this_v_l = this_v_l + bad_a_l * Ts;
                else
                   this_v_l = this_v_l - bad_a_l * Ts;
                end
                
                e = this_d - d_d;
                e_dot = e - old_e;
                E = E + e;
                old_e = e;
                u_f = kp * e + kd * e_dot + ki * E;
                this_v_f = this_v_f + Ts * u_f;
                
                if this_d > 45 || this_d < 35
                    fail = true;
                    break;
                end
            end
            % Loop ends
            
            if fail == false
                S_sigma = [S_sigma; [v_l, v_f, d]];
            end
            
        end
    end
end

csvwrite('S_sigma.csv', S_sigma)


%S_1
load('S_sigma.csv');
S_1 = [];
for i = 1 : size(S_sigma, 1)
    x0 = S_sigma(i, :);
    
    this_v_l = x0(1);
    this_v_f = x0(2);
    this_d = x0(3);
    old_e = this_d - d_d;
    E = 0;
    
    this_d = this_d + (this_v_l - this_v_f) * Ts;
    if this_d > 40
       this_v_l = this_v_l + bad_a_l * Ts;
    else
       this_v_l = this_v_l - bad_a_l * Ts;
    end
    
    this_v_l = round(this_v_l);
%     e = this_d - d_d;
%     e_dot = e - old_e;
%     E = E + e;
%     old_e = e;
%     u_f = kp * e + kd * e_dot + ki * E;
    this_v_f_UB = this_v_f + Ts * UB;
    this_v_f_UB = round(this_v_f_UB);
    this_d_UB = this_d + (this_v_l - this_v_f_UB) * Ts;
    this_d_UB = round(this_d_UB);
    x_new_UB = [this_v_l, this_v_f_UB, this_d_UB];
    
    this_v_f_LB = this_v_f + Ts * LB;
    this_v_f_LB = round(this_v_f_LB);
    this_d_LB = this_d + (this_v_l - this_v_f_LB) * Ts;
    this_d_LB = round(this_d_LB);
    x_new_LB = [this_v_l, this_v_f_LB, this_d_LB];
    
    if size(intersect(x_new_LB, S_sigma, 'rows'), 1) ~= 0 && size(intersect(x_new_UB, S_sigma, 'rows'), 1) ~= 0
        S_1 = [S_1; x0];
    end
    
end   
    
 
%S_2
% S_2
S_2 = [];
for i = 1 : size(S_sigma, 1)
    x0 = S_sigma(i, :);

    this_v_l = x0(1);
    this_v_f = x0(2);
    this_d = x0(3);
    
    this_d = this_d + (this_v_l - this_v_f) * Ts;
    if this_d > 40
       this_v_l = this_v_l + bad_a_l * Ts;
    else
       this_v_l = this_v_l - bad_a_l * Ts;
    end
    this_v_l = round(this_v_l);

    this_d = this_d + (this_v_l - this_v_f) * Ts;
    
    x_new = round([this_v_l, this_v_f, this_d]);
    

    if size(intersect(x_new, S_sigma, 'rows'), 1) ~= 0 
        S_2 = [S_2; x0];
    end
end
S_2 = setdiff(S_2, S_1, 'rows');


%S_3
S_3 = setdiff(S_sigma, union(S_1, S_2, 'rows'), 'rows');

csvwrite('S_sigma.csv', S_sigma)
csvwrite('S_1.csv', S_1)
csvwrite('S_2.csv', S_2)
csvwrite('S_3.csv', S_3)



load('S_1.csv');
load('S_2.csv');
load('S_3.csv');

figure
hold on
plot3(S_3(:, 1), S_3(:, 2), S_3(:, 3), 'ko', 'MarkerFaceColor', 'r', 'MarkerSize', 15);
plot3(S_2(:, 1), S_2(:, 2), S_2(:, 3), 'ko', 'MarkerFaceColor', 'b', 'MarkerSize', 15)
plot3(S_1(:, 1), S_1(:, 2), S_1(:, 3), 'ko', 'MarkerFaceColor', 'g', 'MarkerSize', 15)
xlabel('Leading Car Speed (m/s)')
ylabel('Following Car Speed (m/s)')
zlabel('Distance (m)')
grid
legend('S_3', 'S_2', 'S_1')



S_1_40 = S_1(S_1(:, 3) == 40, [1,2]);
S_2_40 = S_2(S_2(:, 3) == 40, [1,2]);
S_3_40 = S_3(S_3(:, 3) == 40, [1,2]);
csvwrite('S_1_40.csv', S_1_40)
csvwrite('S_2_40.csv', S_2_40)
csvwrite('S_3_40.csv', S_3_40)
figure
hold on
plot(S_3_40(:, 1), S_3_40(:, 2), 'rx')
plot(S_3_40(:, 1), S_3_40(:, 2), 'rx', 'LineWidth', 4)
plot(S_2_40(:, 1), S_2_40(:, 2), 'bx', 'LineWidth', 4)
plot(S_1_40(:, 1), S_1_40(:, 2), 'gx', 'LineWidth', 4)
title('Instantaneous Distance 40 m')
xlabel('Leading Car Speed (m/s)')
ylabel('Following Car Speed (m/s)')
grid


S_1_35 = S_1(S_1(:, 3) == 35, [1,2]);
S_2_35 = S_2(S_2(:, 3) == 35, [1,2]);
S_3_35 = S_3(S_3(:, 3) == 35, [1,2]);
csvwrite('S_1_35.csv', S_1_35)
csvwrite('S_2_35.csv', S_2_35)
csvwrite('S_3_35.csv', S_3_35)
figure
hold on
plot(S_3_35(:, 1), S_3_35(:, 2), 'rx')
plot(S_3_35(:, 1), S_3_35(:, 2), 'rx', 'LineWidth', 4)
plot(S_2_35(:, 1), S_2_35(:, 2), 'bx', 'LineWidth', 4)
plot(S_1_35(:, 1), S_1_35(:, 2), 'gx', 'LineWidth', 4)
title('Instantaneous Distance 35 m')
xlabel('Leading Car Speed (m/s)')
ylabel('Following Car Speed (m/s)')
grid


S_1_45 = S_1(S_1(:, 3) == 45, [1,2]);
S_2_45 = S_2(S_2(:, 3) == 45, [1,2]);
S_3_45 = S_3(S_3(:, 3) == 45, [1,2]);
csvwrite('S_1_45.csv', S_1_45)
csvwrite('S_2_45.csv', S_2_45)
csvwrite('S_3_45.csv', S_3_45)
figure
hold on
plot(S_3_45(:, 1), S_3_45(:, 2), 'rx')
plot(S_3_45(:, 1), S_3_45(:, 2), 'rx', 'LineWidth', 4)
plot(S_2_45(:, 1), S_2_45(:, 2), 'bx', 'LineWidth', 4)
plot(S_1_45(:, 1), S_1_45(:, 2), 'gx', 'LineWidth', 4)
title('Instantaneous Distance 45 m')
xlabel('Leading Car Speed (m/s)')
ylabel('Following Car Speed (m/s)')
grid