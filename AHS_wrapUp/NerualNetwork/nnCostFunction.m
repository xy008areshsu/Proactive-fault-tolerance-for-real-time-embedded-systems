function [J grad] = nnCostFunction(nn_params, ...
                                   input_layer_size, ...
                                   hidden_layer_size, ...
                                   num_labels, ...
                                   X, y, lambda)
%NNCOSTFUNCTION Implements the neural network cost function for a two layer
%neural network which performs classification
%   [J grad] = NNCOSTFUNCTON(nn_params, hidden_layer_size, num_labels, ...
%   X, y, lambda) computes the cost and gradient of the neural network. The
%   parameters for the neural network are "unrolled" into the vector
%   nn_params and need to be converted back into the weight matrices. 
% 
%   The returned parameter grad should be a "unrolled" vector of the
%   partial derivatives of the neural network.
%

% Reshape nn_params back into the parameters Theta1 and Theta2, the weight matrices
% for our 2 layer neural network
Theta1 = reshape(nn_params(1:hidden_layer_size * (input_layer_size + 1)), ...
                 hidden_layer_size, (input_layer_size + 1));

Theta2 = reshape(nn_params((1 + (hidden_layer_size * (input_layer_size + 1))):end), ...
                 num_labels, (hidden_layer_size + 1));

% Setup some useful variables
m = size(X, 1);
         
% You need to return the following variables correctly 
J = 0;
Theta1_grad = zeros(size(Theta1));
Theta2_grad = zeros(size(Theta2));

% ====================== YOUR CODE HERE ======================
% Instructions: You should complete the code by working through the
%               following parts.
%
% Part 1: Feedforward the neural network and return the cost in the
%         variable J. After implementing Part 1, you can verify that your
%         cost function computation is correct by verifying the cost
%         computed in ex4.m
%
% Part 2: Implement the backpropagation algorithm to compute the gradients
%         Theta1_grad and Theta2_grad. You should return the partial derivatives of
%         the cost function with respect to Theta1 and Theta2 in Theta1_grad and
%         Theta2_grad, respectively. After implementing Part 2, you can check
%         that your implementation is correct by running checkNNGradients
%
%         Note: The vector y passed into the function is a vector of labels
%               containing values from 1..K. You need to map this vector into a 
%               binary vector of 1's and 0's to be used with the neural network
%               cost function.
%
%         Hint: We recommend implementing backpropagation using a for-loop
%               over the training examples if you are implementing it for the 
%               first time.
%
% Part 3: Implement regularization with the cost function and gradients.
%
%         Hint: You can implement this around the code for
%               backpropagation. That is, you can compute the gradients for
%               the regularization separately and then add them to Theta1_grad
%               and Theta2_grad from Part 2.
%



for i = 1 : m
    a_1 = X(i, :)';    % activation layer 1 are the inputs for training set i
    a_1 = [1 ; a_1];   % add 1 bias unit to a1
    
    z_2 = Theta1 * a_1;
    a_2 = sigmoid(z_2);   % activation of hidden layer
    a_2 = [1 ; a_2];
    
    z_3 = Theta2 * a_2;
    a_L = sigmoid(z_3);   % activation of the output layer
    
    encoded_y = zeros(num_labels, 1);   
    encoded_y(y(i)) = 1;                % recode the labels for the purpose of training
    
    J = J + sum(-encoded_y .* log(a_L) - (1 - encoded_y) .* log(1 - a_L));
 
 %Backward propagation starts here   
    delta_L = a_L - encoded_y;       % errors in the output layer 
    delta_2 = Theta2(:, 2:end)' * delta_L .* sigmoidGradient(z_2);   % errors in the hidden layer
%     delta_2 = delta_2(2 : end);      % remove bias unit
    Theta2_grad = Theta2_grad + delta_L * a_2';
    Theta1_grad = Theta1_grad + delta_2 * a_1';
    
    
end

J = (1 / m) * J;

% Add regularization to cost function
Theta1_square = Theta1 .^ 2;
Theta1_square = Theta1_square(:, 2 : end);
Theta2_square = Theta2 .^ 2;
Theta2_square = Theta2_square(:, 2 : end);

J = J + (lambda / (2 * m)) * (sum(sum(Theta1_square, 2)) + sum(sum(Theta2_square, 2)));

Theta1_grad = Theta1_grad / m;
Theta2_grad = Theta2_grad / m;
% Add regularization to the gradients
Theta1_grad(:, 2:end) = Theta1_grad(:, 2:end) + (lambda / m) * Theta1(:, 2:end);
Theta2_grad(:, 2:end) = Theta2_grad(:, 2:end) + (lambda / m) * Theta2(:, 2:end);















% -------------------------------------------------------------

% =========================================================================

% Unroll gradients
grad = [Theta1_grad(:) ; Theta2_grad(:)];


end
