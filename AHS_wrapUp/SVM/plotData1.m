function plotData1(X, y)
%PLOTDATA Plots the data points X and y into a new figure 
%   PLOTDATA(x,y) plots the data points with + for the positive examples
%   and o for the negative examples. X is assumed to be a Mx2 matrix.
%
% Note: This was slightly modified such that it expects y = 1 or y = 0

% Find Indices of Positive and Negative Examples
pos1 = find(y == 1); pos2 = find(y == 2); pos3 = find(y == 3);

% Plot Examples
plot(X(pos1, 1), X(pos1, 2), 'g.','LineWidth', 1)
hold on;
plot(X(pos2, 1), X(pos2, 2), 'b.', 'LineWidth', 1)
plot(X(pos3, 1), X(pos3, 2), 'r.', 'LineWidth', 1)
% hold off;

end
