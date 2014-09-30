clear; clc; close all


global A  B C D K SSS Ts tf AIneq BIneq Aeq Beq LB UB mean std
std = 0;
mean = 0;
A = load('A.csv');
B = load('B.csv');
C = load('C.csv');
D = load('D.csv');
K = load('K.csv');
Ts = 0.03;
tf = 10;
SSS = load('SSS.csv');

AIneq = [];
BIneq = [];
Aeq = [];
Beq = [];
LB = [-25];
UB = [25];
stateOfInterests = [3,4];

granularity = -2;

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
%         if size(intersect(newState(stateOfInterests)', SSS(:, stateOfInterests), 'rows'), 1) == 0
%             fail = true;
%             break
%         end
        
        if newState(3) > 0.5 || newState(3) < -0.5
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

plot(S_3(:, 1), S_3(:, 2), 'rx', 'LineWidth', 4);
plot(S_2(:, 1), S_2(:, 2), 'bx', 'LineWidth', 4);
plot(S_1(:, 1), S_1(:, 2), 'gx', 'LineWidth', 4);
grid
set(gcf, 'PaperPosition', [0 0 5 5]); %Position plot at left hand corner with width 5 and height 5.
set(gcf, 'PaperSize', [5 5]); %Set the paper to have width 5 and height 5.
saveas(gcf, strcat('./simResults/subSpaces_LQR_' , num2str(Ts * 1000) , '_ms.pdf') , 'pdf') %Save figure


csvwrite(strcat('./simResults/s_sigma_LQR_', num2str(Ts * 1000) ,'_ms.csv'), S_sigma);
csvwrite(strcat('./simResults/s1_LQR_' , num2str(Ts * 1000) , '_ms.csv'), S_1);
csvwrite(strcat('./simResults/s2_LQR_' , num2str(Ts * 1000) , '_ms.csv'), S_2);
csvwrite(strcat('./simResults/s3_LQR_' , num2str(Ts * 1000) , '_ms.csv'), S_3);

