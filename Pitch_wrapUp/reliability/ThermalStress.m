% clear; clc; close all

R = 5;
C = 0.3;
initTabs = 300;
Tamb = 300;
Ea = 0.4;
w = 75;
w_idle = 1;
k = 8.6173324 * (10 ^ (-5));      % Boltzmann's constant
A = 2.8 * (10 ^4);      % prefactor


Tss = steady_state_T(Tamb,R,w);
Tss_idle = steady_state_T(Tamb, R, w_idle);


Tabs = zeros(100, 1);
alpha = zeros(100, 1);
taaf = zeros(100, size(w, 2));
step = 0.2;
i = 1;

    for t = 0 : step : 20
        if mod(t, 3) == 0 || mod(t, 5) == 0   % Assume when mod(t, 3) == 0 or mod(t, 5) == 0, this processor can be turned off
            Tabs(i) = absolute_T(Tss_idle,initTabs,step, R, C);
            alpha(i) = aging_factor(A, Ea,k,Tabs(i));
            taaf(i) = TAAF(A, Ea,k,Tabs(i));
        else
            Tabs(i) = absolute_T(Tss,initTabs,step, R, C);
            alpha(i) = aging_factor(A, Ea,k,Tabs(i));
            taaf(i) = TAAF(A, Ea,k,Tabs(i));
        end
        initTabs = Tabs(i);
        i = i + 1;
    end



%% Data processing
t = 0 :0.2:20;   
plot(t, taaf(:, 1), 'm', 'LineWidth', 4);
grid
title('TAAF under all processors on')
xlabel('Time (s)');
ylabel('TAAF')
% legend('25 watts', '50 watts', '75 watts', '100 watts')
set(gcf, 'PaperPosition', [0 0 5 5]); %Position plot at left hand corner with width 5 and height 5.
set(gcf, 'PaperSize', [5 5]); %Set the paper to have width 5 and height 5.
saveas(gcf, './reliability/TAAF_All_on', 'pdf') %Save figure

    