clear; clc; close all

S_1 = load('S_1_CTG.csv');
S_2 = load('S_2_CTG.csv');
S_3 = load('S_3_CTG.csv');
S_1_aux = [];
S_2_aux = [];
S_3_aux = [];

mu_dis = 0;
std_dis = 0.1;   % 10% relative noise

for i = 1 : size(S_1, 1)
    s_aux_plus = [S_1(i,1), S_1(i, 2), S_1(i, 3) + std_dis * S_1(i, 3)];
    s_aux_minus = [S_1(i, 1), S_1(i, 2), S_1(i, 3) - std_dis * S_1(i, 3)];
    if s_aux_minus(3) < 10
        S_3_aux = [S_3_aux; S_1(i, :)];
    elseif size(intersect(S_3, s_aux_plus, 'rows'), 1) ~= 0 || size(intersect(S_3, s_aux_minus, 'rows'), 1) ~= 0
        S_3_aux = [S_3_aux; S_1(i, :)];
    elseif size(intersect(S_2, s_aux_plus, 'rows'), 1) ~= 0 || size(intersect(S_2, s_aux_minus, 'rows'), 1) ~= 0
        S_2_aux = [S_2_aux; S_1(i, :)];
    else
        S_1_aux = [S_1_aux; S_1(i, :)];
    end
end

for i = 1 : size(S_2, 1)
    s_aux_plus = [S_2(i,1), S_2(i, 2), S_2(i, 3) + std_dis * S_2(i, 3)];
    s_aux_minus = [S_2(i, 1), S_2(i, 2), S_2(i, 3) - std_dis * S_2(i, 3)];
    if s_aux_minus(3) < 10
        S_3_aux = [S_3_aux; S_2(i, :)];
    elseif size(intersect(S_3, s_aux_plus, 'rows'), 1) ~= 0 || size(intersect(S_3, s_aux_minus, 'rows'), 1) ~= 0
        S_3_aux = [S_3_aux; S_2(i, :)];
    else
        S_2_aux = [S_2_aux; S_2(i, :)];
    end
end

S_3_aux = [S_3; S_3_aux];
% 
% S_1 = S_1_aux;
% S_2 = S_2_aux;
% S_3 = S_3_aux;


figure
hold on
plot3(S_3(:, 1), S_3(:, 2), S_3(:, 3), 'ko', 'MarkerFaceColor', 'r', 'MarkerSize', 10);
plot3(S_2(:, 1), S_2(:, 2), S_2(:, 3), 'ko', 'MarkerFaceColor', 'b', 'MarkerSize', 10)
plot3(S_1(:, 1), S_1(:, 2), S_1(:, 3), 'ko', 'MarkerFaceColor', 'g', 'MarkerSize', 10)
xlabel('Leading Car Speed (m/s)')
ylabel('Following Car Speed (m/s)')
zlabel('Distance (m)')
grid

figure
hold on
plot3(S_3_aux(:, 1), S_3_aux(:, 2), S_3_aux(:, 3), 'ko', 'MarkerFaceColor', 'r', 'MarkerSize', 10);
plot3(S_2_aux(:, 1), S_2_aux(:, 2), S_2_aux(:, 3), 'ko', 'MarkerFaceColor', 'b', 'MarkerSize', 10)
plot3(S_1_aux(:, 1), S_1_aux(:, 2), S_1_aux(:, 3), 'ko', 'MarkerFaceColor', 'g', 'MarkerSize', 10)
xlabel('Leading Car Speed (m/s)')
ylabel('Following Car Speed (m/s)')
zlabel('Distance (m)')
grid

% csvwrite('S_1_CTG_noise_dis.csv', S_1_aux);
% csvwrite('S_2_CTG_noise_dis.csv', S_2_aux);
% csvwrite('S_3_CTG_noise_dis.csv', S_3_aux);