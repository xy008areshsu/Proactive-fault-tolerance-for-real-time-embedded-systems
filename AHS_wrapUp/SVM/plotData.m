
function plotData(X, y)
%PLOTDATA Plots the data points X and y into a new figure 
%   PLOTDATA(x,y) plots the data points with + for the positive examples
%   and o for the negative examples. X is assumed to be a Mx2 matrix.
%
% Note: This was slightly modified such that it expects y = 1 or y = 0

% Find Indices of Positive and Negative Examples
pos = find(y == 1); neg = find(y == 0);

% Plot Examples
plot(X(pos, 1), X(pos, 2), 'rx','LineWidth', 4)
hold on;
plot(X(neg, 1), X(neg, 2), 'gx', 'LineWidth', 4)
% plot(X(pos3, 1), X(pos3, 2), 'r.', 'LineWidth', 1)
% hold off;

end
