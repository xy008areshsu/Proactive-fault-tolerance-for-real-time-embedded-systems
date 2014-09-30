%% Machine Learning Online Class - Exercise 3 | Part 1: One-vs-all

%  Instructions
%  ------------
% 
%  This file contains code that helps you get started on the
%  linear exercise. You will need to complete the following functions 
%  in this exericse:
%
%     lrCostFunction.m (logistic regression cost function)
%     oneVsAll.m
%     predictOneVsAll.m
%     predict.m
%
%  For this exercise, you will not need to change any code in this file,
%  or any other files other than those mentioned above.
%

%% Initialization
% clear ; close all; clc

%% Setup the parameters you will use for this part of the exercise
input_layer_size  = 3;  % 20x20 Input Images of Digits
num_labels = 3;          % 10 labels, from 1 to 10   
                          % (note that we have mapped "0" to label 10)

%% =========== Part 1: Loading and Visualizing Data =============
%  We start the exercise by first loading and visualizing the dataset. 
%  You will be working with a dataset that contains handwritten digits.
%

% gen_regions;

fprintf('Program paused. Press enter to continue.\n');
pause;

%% ============ Part 2: Vectorize Logistic Regression ============
%  In this part of the exercise, you will reuse your logistic regression
%  code from the last exercise. You task here is to make sure that your
%  regularized logistic regression implementation is vectorized. After
%  that, you will implement one-vs-all classification for the handwritten
%  digit dataset.
%

fprintf('\nTraining One-vs-All Logistic Regression...\n')

lambda = 0;
[all_theta] = oneVsAll(X, y, num_labels, lambda);

fprintf('Program paused. Press enter to continue.\n');
pause;




%% ================ Part 3: Predict for One-Vs-All ================
%  After ...
pred = predictOneVsAll(all_theta, X);

fprintf('\nTraining Set Accuracy: %f\n', mean(double(pred(1:end) == y(1:end))) * 100);

%% Plot Decision boundary for each region
% figure
% plot(s_N_v, s_N_w, 'gx', 'LineWidth', 4)
% hold
% plot(s_FS_v, s_FS_w, 'bx', 'LineWidth', 4);
% plot(s_F_v, s_F_w, 'rx', 'LineWidth', 4)
% h = ezplot('-10.941428   + (11.581222 ) * x + (-13.016312 ) * y  = 0', [0 25 0 25]);
% set(h, 'Color', 'black', 'LineWidth', 2)
% title('Decision Boundary for class 1')
% grid
% 
% figure
% plot(s_N_v, s_N_w, 'gx', 'LineWidth', 4)
% hold
% plot(s_FS_v, s_FS_w, 'bx', 'LineWidth', 4);
% plot(s_F_v, s_F_w, 'rx', 'LineWidth', 4)
% h = ezplot('(18.518992 )  + (0.001) * x + (-2.328944 ) * y = 0', [0 25 0 25]);
% set(h, 'Color', 'black', 'LineWidth', 2)
% title('Decision Boundary for class 2')
% grid
% 
% 
% figure
% plot(s_N_v, s_N_w, 'gx', 'LineWidth', 4)
% hold
% plot(s_FS_v, s_FS_w, 'bx', 'LineWidth', 4);
% plot(s_F_v, s_F_w, 'rx', 'LineWidth', 4)
% h = ezplot('( -12.382877 )  + (5.631413) * x + (-6.078795  ) * y = 0', [0 25 0 25]);
% set(h, 'Color', 'black', 'LineWidth', 2)
% title('Decision Boundary for class 3')
% grid

% figure
% plot(s_N_v, s_N_w, 'gx', 'LineWidth', 4)
% hold
% plot(s_FS_v, s_FS_w, 'bx', 'LineWidth', 4);
% plot(s_F_v, s_F_w, 'rx', 'LineWidth', 4)
% h = ezplot(sprintf('%f + %f * x + %f * y + %f * x * x + %f * y * y + %f * (x ^ 3) + %f * (y ^ 3) + %f * (x^4) + %f * (y ^ 4)', theta(1), theta(2),theta(3),theta(4),theta(5),theta(6),theta(7),theta(8), theta(9)), [10 35 0 50]);
% set(h, 'Color', 'black', 'LineWidth', 2)
% h = ezplot(sprintf('%f + %f * x + %f * y', theta(1), theta(2),theta(3)), [10 25 0 25]);
% set(h, 'Color', 'black', 'LineWidth', 2)
% h = ezplot(sprintf('%f + %f * x + %f * y + %f * x * x + %f * y * y', theta(1), theta(2),theta(3), theta(4), theta(5)), [10 25 0 25]);
% set(h, 'Color', 'black', 'LineWidth', 2)
% h = ezplot(sprintf('%f + %f * x + %f * y + %f * x * x + %f * y * y + %f * (x ^ 3) + %f * (y ^ 3) + %f * (x^4) + %f * (y ^ 4) + %f * (x ^ 5) + %f * (y ^ 5)', theta(1), theta(2),theta(3),theta(4),theta(5),theta(6),theta(7),theta(8), theta(9), theta(10), theta(11)), [10 35 0 50]);
% set(h, 'Color', 'black', 'LineWidth', 2)
% h = ezplot(sprintf('%f + %f * x + %f * y + %f * x * x + %f * y * y + %f * (x ^ 3) + %f * (y ^ 3) + %f * (x^4) + %f * (y ^ 4)+ %f * (x ^ 5) + %f * (y ^ 5) + %f * (x * y) + %f*(x * x * y) + %f * (x * y * y)', theta(1), theta(2),theta(3),theta(4),theta(5),theta(6),theta(7),theta(8), theta(9), theta(10), theta(11), theta(12), theta(13), theta(14)), [10 35 0 50]);
% set(h, 'Color', 'black', 'LineWidth', 2)
% h = ezplot(sprintf('%f + %f * x + %f * x * x + %f * (x ^ 3) + %f * (x^4) + %f * (x ^ 5) + %f * (y ^ 5) + %f * y ', theta(1), theta(2),theta(3),theta(4),theta(5),theta(6),theta(7), theta(8)), [10 35 0 50]);
% set(h, 'Color', 'black', 'LineWidth', 2)
% h = ezplot(sprintf('%f + %f * x + %f * y + %f * (y ^ 2) + %f * (y ^ 3) + %f * (y^4) + %f * (y ^ 5) ', theta(1), theta(2),theta(3),theta(4),theta(5),theta(6),theta(7)), [10 35 0 50]);
% set(h, 'Color', 'black', 'LineWidth', 2)
% h = ezplot(sprintf('%f + %f * x + %f * y + %f * (x ^ 2) + %f * (x ^ 3) + %f * (x^4) + %f * (x ^ 5) ', theta(1), theta(2),theta(3),theta(4),theta(5),theta(6),theta(7)), [10 35 0 50]);
% set(h, 'Color', 'black', 'LineWidth', 2)
% h = ezplot(sprintf('%f + %f * x + %f * y + %f * (x ^ 2) + %f * (x * y) + %f * (y ^ 2) + %f * (x ^ 3)+ %f * (x ^ 2 * y)+ %f * (x * (y ^ 2))+ %f * (y ^ 3) + %f * (x ^ 4)+ %f * ((x ^ 3) * y)+ %f * ((x ^ 2) * (y ^ 2))+ %f * ( x * (y ^ 3)) + %f * ( y ^ 4)', theta(1) + 2, theta(2),theta(3),theta(4),theta(5),theta(6),theta(7),theta(8),theta(9),theta(10),theta(11),theta(12),theta(13),theta(14),theta(15)));
% set(h, 'Color', 'black', 'LineWidth', 2)
% h = ezplot(sprintf('%f + %f * x + %f * y + %f * (x ^ 2) + %f * (x * y) + %f * (y ^ 2) + %f * (x ^ 3)+ %f * (x ^ 2 * y)+ %f * (x * (y ^ 2))+ %f * (y ^ 3) + %f * (x ^ 4)+ %f * ((x ^ 3) * y)+ %f * ((x ^ 2) * (y ^ 2))+ %f * ( x * (y ^ 3)) + %f * ( y ^ 4) + %f * (x ^ 5) + %f * (x ^ 4 * y)+ %f * ((x ^ 3) * (y ^ 2))+ %f * ((x ^ 2) * (y ^ 3))+ %f * ( x * (y ^ 4)) + %f * ( y ^ 5)', theta(1) + 2, theta(2),theta(3),theta(4),theta(5),theta(6),theta(7),theta(8),theta(9),theta(10),theta(11),theta(12),theta(13),theta(14),theta(15),theta(16),theta(17),theta(18),theta(19),theta(20),theta(21)), [10 25 0 25]);
% set(h, 'Color', 'black', 'LineWidth', 2)
% grid
% 
% 
% 
% h = ezplot(' -0.416533     + (-0.190198 ) * x + ( -0.091136 ) * y + (-0.068909)* x * x + (0.035498 ) * y * y + (-0.013990) *(x^3) + ( 0.048264  ) * (y^3) + (  0.000144  ) * (x^4) + (-0.001283 ) *(y^4) = 0', [10 25 0 25]);
% set(h, 'Color', 'black', 'LineWidth', 2)
% h = ezplot(' -27.844428     + ( 11.760700 ) * x + (-12.437562 ) * y  = 0', [15 17 0 25]);
% set(h, 'Color', 'black', 'LineWidth', 2)
% h = ezplot('  -25.511700      + ( 6.254503  ) * x + ( -6.276468 ) * y  = 0', [18 25 0 25]);
% set(h, 'Color', 'black', 'LineWidth', 2)
% title('Decision Boundary for class 1')
% grid
% 
% fprintf('Number of testing data: %d: \n', size(y,1))
% fprintf('Number of mis-mapping from 3 to 1: %d%%: \n', size(find(y == 3 & pred == 1), 1)  / size(y, 1) * 100)
% fprintf('Fraction of mis-mapping from 2 to 1: %d%%: \n', size(find(y == 2 & pred == 1), 1) / size(y, 1) * 100)
% fprintf('Fraction of mis-mapping from 3 to 2: %d%%: \n', size(find(y == 3 & pred == 2), 1) / size(y, 1) * 100)
% fprintf('Fraction of mis-mapping from 1 to 2: %d%%: \n', size(find(y == 1 & pred == 2), 1) / size(y, 1) * 100)
% fprintf('Fraction of mis-mapping from 2 to 3: %d%%: \n', size(find(y == 2 & pred == 3), 1) / size(y, 1) * 100)
% fprintf('Fraction of mis-mapping from 1 to 3: %d%%: \n', size(find(y == 1 & pred == 3), 1) / size(y, 1) * 100)
