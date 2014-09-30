% SVM Parameters
C = 1000; sigma = 0.5;

% Train the SVM
model= svmTrain(X, y, C, @(x1, x2) gaussianKernel(x1, x2, sigma));
visualizeBoundary(X, y, model);

plot(S_3(:, 1), S_3(:, 2), 'rx', 'LineWidth', 1);
plot(S_2(:, 1), S_2(:, 2), 'b+', 'LineWidth', 1);
plot(S_1(:, 1), S_1(:, 2), 'g.', 'LineWidth', 1);
grid
% title(strcat('Sub-spaces for ABS with road condition 1.0'));
xlabel('Vehicle Speed (m/s)')
ylabel('Wheel Speed (m/s)')
legend('Decison Boundary','S3', 'S2', 'S1','Location', 'NorthWest')

set(gcf, 'PaperPosition', [0 0 5 5]); %Position plot at left hand corner with width 5 and height 5.
set(gcf, 'PaperSize', [5 5]); %Set the paper to have width 5 and height 5.
saveas(gcf, './simResults/subSpaces.pdf' , 'pdf') %Save figure
saveas(gcf, './simResults/subSpaces.eps' , 'eps') %Save figure

% set(gcf, 'PaperPosition', [0 0 5 5]); %Position plot at left hand corner with width 5 and height 5.
% set(gcf, 'PaperSize', [5 5]); %Set the paper to have width 5 and height 5.
% saveas(gcf, '/simResults/subSpacesWithBoundaries.pdf', 'pdf') %Save figure

% save('/simResults/svmModel', 'model');


