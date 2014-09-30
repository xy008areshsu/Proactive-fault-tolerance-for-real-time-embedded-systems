function [p, ex_time] = predict(Theta1, Theta2, X, threshold)
%PREDICT Predict the label of an input given a trained neural network
%   p = PREDICT(Theta1, Theta2, X) outputs the predicted label of X given the
%   trained weights of a neural network (Theta1, Theta2)

% Useful values
t = cputime;
m = size(X, 1);
num_labels = size(Theta2, 1);

% You need to return the following variables correctly 
p = zeros(size(X, 1), 1);

h1 = sigmoid([ones(m, 1) X] * Theta1');
h2 = sigmoid([ones(m, 1) h1] * Theta2');
[pred_val, p] = max(h2, [], 2);
for i = 1 : size(pred_val, 1)
    if pred_val(i) < threshold
        if p(i) < num_labels
            p(i) = num_labels;   % if it is smaller than threshold, set p(i) to the most conservative highest value
        end    
    end
end

% [dummy, p] = max(h2, [], 2);
ex_time = cputime - t;
% =========================================================================


end
