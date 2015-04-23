% SVM Parameters
C = 10; sigma = 0.03;

% Train the SVM
model= svmTrain(X, y, C, @(x1, x2) gaussianKernel(x1, x2, sigma));
% visualizeBoundary(X, y, model);
% plot(S_3(:, 1), S_3(:, 2), 'rx', 'LineWidth', 4);
% plot(S_2(:, 1), S_2(:, 2), 'bx', 'LineWidth', 4);
% plot(S_1(:, 1), S_1(:, 2), 'gx', 'LineWidth', 4);
% grid

set(gcf, 'PaperPosition', [0 0 5 5]); %Position plot at left hand corner with width 5 and height 5.
set(gcf, 'PaperSize', [5 5]); %Set the paper to have width 5 and height 5.
saveas(gcf, './simResults/subSpaces.pdf' , 'pdf') %Save figure

save('./simResults/svmModel', 'model');


