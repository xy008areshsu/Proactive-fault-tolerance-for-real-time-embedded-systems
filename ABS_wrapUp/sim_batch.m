clear; clc; close all

addpath ./SVM/
addpath ./LG/
addpath ./NerualNetwork/
addpath ./reliability/


%% User promt
global A  B C D K SSS Ts tf AIneq BIneq Aeq Beq LB UB 
Ts = 0.01;  % sampling time period
tf = 15;  % simulation time
A = [];
B = [];
C = [];
D = [];
SSS = [];
K = [];

type = input('Is the system linear or nonlinear? 1 for linear and 2 for nonlinear\n');
if type == 1
    fprintf('Please specify A, B, C, D, SSS, K matrix\n')

    A = input('A: ');
    B = input('B: ');
    C = input('C: ');
    D = input('D: ');
    SSS = input('SSS: ');
    stateOfInterests = input('State of Interests: ');
    K = input('K: ');
    
    sys = ss(A, B, C, D);
    sys_d = c2d(sys, Ts, 'zoh');
    co_c = ctrb(sys);
    ob_c = obsv(sys);
    controllability_c = rank(co_c);
    observability_c = rank(ob_c);
    
    while (length(A) - controllability_c) > 0 || (length(A) - observability_c) > 0 
        fprintf('System not fully controlable or fully observable, try other A, B, C, D\n')
        A = input('A: ');
        B = input('B: ');
        C = input('C: ');
        D = input('D: ');
        
        sys = ss(A, B, C, D);
        sys_d = c2d(sys, Ts, 'zoh');
        co_c = ctrb(sys);
        ob_c = obsv(sys);
        controllability_c = rank(co);
        observability_c = rank(ob);
    end

    while size(B * K) ~= size(A)
        fprintf('Wrong size of K, do it again\n');
        K = input('K: ');
    end

    eig_val_c = eig(A - B * K);
    eig_val_real = real(eig_val_c);
    
    while sum(eig_val_real < 0) < size(eig_val_real, 1)
        fprintf('K cannot give a stable system, try another K\n')
        K = input('K: ');
        eig_val_c = eig(A - B * K);
        eig_val_real = real(eig_val_c);
    end
    

    while size(SSS) == 0
        fprintf('SSS cannot be empty\n')
        SSS = input('SSS: ');
    end
    
    granularity = input('Granularity of data(MUST be the same as the granularity of SSS,\n otherwise it might not give the correct results): ');
    
elseif type == 2
    fprintf('We will not check controlability, observability and stability for you! You are on your own!\n')
    fprintf('Please specify the following functions in .m files\n')
    while exist('updateState.m', 'file') ~= 2
        fprintf('updateState.m:  newStateVector = updateState(oldStateVector, actuatorVector, Ts)\n')
        pause
    end
    
    while exist('updateControlActuator.m', 'file') ~= 2
        fprintf('updateControlActuator.m:  newActuatorVector = updateControlActuator(StateVector, oldActuatorVector, Ts)\n')
        pause
    end
    
    fprintf('Please specify SSS\n')
    SSS = input('SSS: ');
    
    stateOfInterests = input('State of Interests: ');
    granularity = input('Granularity of data(MUST be the same as the granularity of SSS,\n otherwise it might not give the correct results): ');
    
else
    type = input('Undefined type of system, try again\n');
end


AIneq = [];
BIneq = [];
Aeq = [];
Beq = [];
LB = [];
UB = [];

while exist('costFunction.m', 'file')
    fprintf('Please specify the cost function of the wrong control actuator commands: cost = probofminobj(wrongAcuatorVector, stateVector)\n')
end


fprintf('Please specify the Linear Equality Constraints of the system: Aeq and Beq\n')
fprintf('Aeq * wrongAcuatorVector = Beq\n')
Aeq = input('Aeq: ');
Beq = input('Beq: ');



fprintf('Please specify the Linear Inequality Constraints of the system: AIneq and BIneq\n')
fprintf('AIneq * wrongAcuatorVector <= BIneq\n')
AIneq = input('AIneq: ');
BIneq = input('BIneq: ');



fprintf('Please specify the Upper and Lower Bounds of the systems: LB and UB\n')
fprintf('LB <= wrongAcuatorVector <= UB\n')
LB = input('LB: ');
UB = input('UB: ');


while exist('nonLinCon.m', 'file') ~= 2
    fprintf('Please specify the Non-Linear Constraints of the system: [C, Ceq] = nonLinCon(wrongAcuatorVector)\n')
    fprintf('C(wrongAcuatorVector) <= 0, Ceq(wrongAcuatorVector) = 0\n')
    pause
end


%% Generate sub spaces
% Generate S_sigma
SSS = roundn(SSS, granularity);
S_sigma = zeros(size(SSS));

count = 0;
show = true;

for i = 1 : size(SSS, 1)

    percentage = roundn((i / size(SSS, 1)) * 100, 0);
    if mod(percentage, 10) == 0 && show == true
        show = false;
        fprintf(strcat('progress for S_sigma:', int2str(percentage) , '%%\n'));
    elseif mod(percentage, 10) ~= 0 && show == false
        show = true;
    end

    initState = SSS(i, :)';
    initU = updateControlActuator(initState,0);
    u = initU;
    oldState = initState;
    fail = false;
    for t = 0 : Ts : tf
        newState = updateState(oldState,u);
        u = updateControlActuator(oldState,u);
        oldState = newState;
        
        newState = roundn(newState, granularity);
        if size(intersect(newState(stateOfInterests)', SSS(:, stateOfInterests), 'rows'), 1) == 0
            fail = true;
            break
        end

    end
    
    if fail == false
        count = count + 1;
        S_sigma(count, :) = SSS(i, :);
    end
end

S_sigma = S_sigma(1 : count, :);

% Generate S_1
S_1 = zeros(size(S_sigma));

count = 0;
for i = 1 : size(S_sigma, 1)
    oldState = S_sigma(i, :)';
    [worstU, worstC] = worstController(oldState);
    newState = updateState(oldState, worstU);

    newState = roundn(newState, granularity);
    if size(intersect(newState(stateOfInterests)', S_sigma(:, stateOfInterests), 'rows'), 1) ~= 0
        count = count + 1;
        S_1(count, :) = S_sigma(i, :);
    end
end

S_1 = S_1(1:count, :);
       
   
% Generate S_2
S_2 = zeros(size(S_sigma));

count = 0;
for i = 1 : size(S_sigma, 1)
    oldState = S_sigma(i, :)';
    zeroU = zeroController(oldState, UB);
    newState = updateState(oldState, zeroU);

    newState = roundn(newState, granularity);
    if size(intersect(newState(stateOfInterests)', S_sigma(:, stateOfInterests), 'rows'), 1) ~= 0
        count = count + 1;
        S_2(count, :) = S_sigma(i, :);
    end
end

S_2 = S_2(1:count, :);
S_2 = setdiff(S_2, S_1, 'rows');

% Generate S_3
S_3 = setdiff(S_sigma, union(S_1, S_2, 'rows'), 'rows');

S_1 = S_1(:, stateOfInterests);
S_2 = S_2(:, stateOfInterests);
S_3 = S_3(:, stateOfInterests);

% Plot sub spaces, and save data
figure
hold on

plot(S_3(:, 1), S_3(:, 2), 'rx', 'LineWidth', 1);
plot(S_2(:, 1), S_2(:, 2), 'b+', 'LineWidth', 1);
plot(S_1(:, 1), S_1(:, 2), 'g.', 'LineWidth', 1);
grid
title(strcat('Sub-spaces for ABS with road condition 1.0'));
xlabel('Vehicle speed (m/s)')
ylabel('Wheel speed (m/s)')
legend('S3', 'S2', 'S1', 'Location', 'NorthWest')
% set(gcf, 'PaperPosition', [0 0 5 5]); %Position plot at left hand corner with width 5 and height 5.
% set(gcf, 'PaperSize', [5 5]); %Set the paper to have width 5 and height 5.
% saveas(gcf, './simResults/subSpaces.pdf' , 'pdf') %Save figure


csvwrite('./simResults/s_sigma.csv', S_sigma);
csvwrite('./simResults/s1.csv', S_1);
csvwrite('./simResults/s2.csv', S_2);
csvwrite('./simResults/s3.csv', S_3);

%% Learning
% First use SVM
fprintf('Start SVM\n');
X = [S_1;S_2;S_3];
y = [ones(size(S_1, 1), 1); 0 * ones(size(S_2, 1), 1); 0 * ones(size(S_3, 1), 1)];
svm;  

% Then we try neural networks
fprintf('Start Neural Networks\n');
X = [S_1; S_2; S_3];
y = [ones(size(S_1, 1), 1); 2 * ones(size(S_2, 1), 1); 3 * ones(size(S_3, 1), 1)];
neuralNetwork;
wrong = find((y~=pred) == 1);
fprintf('predicted value: \n')
[X(wrong, :), pred(wrong)]
fprintf('actual value: \n')
[X(wrong, :), y(wrong)]

%% TAAF

t_S_N = [];
t_S_FS = [];
t_S_F = [];

initState = input('Please specify the initial states for TAAF comparison: ');
u = updateControlActuator(initState, 0);
oldState = initState;

for t = 0 : Ts : tf
    newState = updateState(oldState, u);
    u = updateControlActuator(oldState, u);
    oldState = roundn(oldState, granularity);
    [pred, ex_time] = predict(Theta1, Theta2, oldState(stateOfInterests)', threshold);
    if pred == 1
        t_S_N = [t_S_N t];
    elseif pred == 2
        t_S_FS = [t_S_FS t];
    else
        t_S_F = [t_S_F t];
    end
    oldState = newState;    
end

stop_time = tf;
ThermalStressBatch



rmpath ./SVM/
rmpath ./LG/
rmpath ./NerualNetwork/
rmpath ./reliability/


