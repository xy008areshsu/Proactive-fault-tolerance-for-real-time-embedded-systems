clear; clc; close all

%% Initial conditions
Vx = 25;  %state var
Vw = 25;  %state var
b = -1000;    % control input
h = 0.01;
time = 0;
x = 0;
states = [];
slip = [];
worstU = [];
bestU = [];

%% update states
while Vx > 0.5 && time < 10
    b = ABS_func(Vx, Vw);
    bestU = [bestU; b];
%     b = ABS_Wrong(Vx, Vw);
%     [Vx, Vw] = updateStates(Vx, Vw, b, h);
    [Vx, Vw, slipRatio] = updateStatesWithSlip(Vx, Vw, b, h);
    slip = [slip; slipRatio];
    time = time + h;
    x = x + h * Vx;
    states = [states; [Vx, Vw]];
end

