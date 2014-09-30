

%% Parameters initialization
R = 1;
C = 0.3;
initTabs = 366;
Tamb = 366;
Ea = 0.4;
watts = [25 50];     % power of the tasks in watts
watt_idle = 1;      % idle power of the processor
k = 8.6173324 * (10 ^ (-5));      % Boltzmann's constant, TBD!!!!!!
%A = 2.8 * (10 ^ 6);      % prefactor, TBD!!!!!!
%A = 1;
A_preFactor = pre_factor(Tamb, Ea, k);
step = 0.01;      % time step
time = 0 : step : stop_time;
taaf_all_on = zeros(size(time, 2), size(watts, 2));

taaf_adaptive1 = zeros(size(time, 2), size(watts, 2));
taaf_adaptive2 = zeros(size(time, 2), size(watts, 2));
taaf_adaptive3 = zeros(size(time, 2), size(watts, 2));
i = 1;

%% Debug Info
T_abs_all_on = zeros(size(time, 2), size(watts, 2));
T_abs_adaptive1 = zeros(size(time, 2), size(watts,2));
T_abs_adaptive2 = zeros(size(time, 2), size(watts,2));
T_abs_adaptive3 = zeros(size(time, 2), size(watts,2));


%% Batch Job
for w = watts
    [taaf_all_on(:, i), T_abs_all_on(:, i)] = ThermalStressAllOnFunc( R, C, initTabs, Tamb, Ea, w,  watt_idle, k, A_preFactor, step, time);
%     [taaf_adaptive(:, i), T_abs_adaptive(:,i)] = ThermalStreeAdaptiveFunc(R, C, initTabs, Tamb, Ea, w, watt_idle, k, A, step, time);
    [taaf_adaptive1(:, i), T_abs_adaptive1(:,i), taaf_adaptive2(:, i), T_abs_adaptive2(:, i), taaf_adaptive3(:, i), T_abs_adaptive3(:, i)] = ThermalStreeAdaptiveFuncWithRegions(R, C, initTabs, Tamb, Ea, w, watt_idle, k, A_preFactor, step, time, t_S_N, t_S_FS);
    i = i + 1;
end

clear i;

%% Post Data processing
figure;
plot(time, taaf_adaptive1(:, 1), 'r', 'LineWidth', 1);
hold
plot(time, taaf_adaptive1(:, 2), 'b', 'LineWidth', 1);
%plot(time, taaf_adaptive(:, 3), 'g', 'LineWidth', 4);
grid
title('TAAF1 under Adaptive FT')
xlabel('Time (s)');
ylabel('TAAF1')
legend('25 watts', '50 watts')
set(gcf, 'PaperPosition', [0 0 5 5]); %Position plot at left hand corner with width 5 and height 5.
set(gcf, 'PaperSize', [5 5]); %Set the paper to have width 5 and height 5.
saveas(gcf, './simResults/TAAF_Adaptive1', 'pdf') %Save figure
% csvwrite('./reliability_results/TAAF_Adaptive1.csv', taaf_adaptive1);
fprintf('Adaptive Average TAAF1 for 25 watts: %.2f\nAdaptive Average TAAF1 for 50 watts: %.2f\n', mean(taaf_adaptive1(:, 1)), mean(taaf_adaptive1(:, 2)));

figure;
plot(time, taaf_adaptive2(:, 1), 'r', 'LineWidth', 1);
hold
plot(time, taaf_adaptive2(:, 2), 'b', 'LineWidth', 1);
%plot(time, taaf_adaptive(:, 3), 'g', 'LineWidth', 4);
grid
title('TAAF2 under Adaptive FT')
xlabel('Time (s)');
ylabel('TAAF2')
legend('25 watts', '50 watts')
set(gcf, 'PaperPosition', [0 0 5 5]); %Position plot at left hand corner with width 5 and height 5.
set(gcf, 'PaperSize', [5 5]); %Set the paper to have width 5 and height 5.
saveas(gcf, './simResults/TAAF_Adaptive2', 'pdf') %Save figure
% csvwrite('./reliability_results/TAAF_Adaptive2.csv', taaf_adaptive2);
fprintf('Adaptive Average TAAF2 for 25 watts: %.2f\nAdaptive Average TAAF2 for 50 watts: %.2f\n', mean(taaf_adaptive2(:, 1)), mean(taaf_adaptive2(:, 2)));

figure;
plot(time, taaf_adaptive3(:, 1), 'r', 'LineWidth', 1);
hold
plot(time, taaf_adaptive3(:, 2), 'b', 'LineWidth', 1);
%plot(time, taaf_adaptive(:, 3), 'g', 'LineWidth', 4);
grid
title('TAAF3 under Adaptive FT')
xlabel('Time (s)');
ylabel('TAAF3')
legend('25 watts', '50 watts')
set(gcf, 'PaperPosition', [0 0 5 5]); %Position plot at left hand corner with width 5 and height 5.
set(gcf, 'PaperSize', [5 5]); %Set the paper to have width 5 and height 5.
saveas(gcf, './simResults/TAAF_Adaptive3', 'pdf') %Save figure
% csvwrite('./reliability_results/TAAF_Adaptive3.csv', taaf_adaptive1);
fprintf('Adaptive Average TAAF3 for 25 watts: %.2f\nAdaptive Average TAAF3 for 50 watts: %.2f\n', mean(taaf_adaptive3(:, 1)), mean(taaf_adaptive3(:, 2)));

figure;
plot(time, taaf_all_on(:, 1), 'r', 'LineWidth', 1);
hold
plot(time, taaf_all_on(:, 2), 'b', 'LineWidth', 1);
%plot(time, taaf_all_on(:, 3), 'g', 'LineWidth', 4);
grid
title('TAAF under All Processors On')
xlabel('Time (s)');
ylabel('TAAF')
legend('25 watts', '50 watts')
set(gcf, 'PaperPosition', [0 0 5 5]); %Position plot at left hand corner with width 5 and height 5.
set(gcf, 'PaperSize', [5 5]); %Set the paper to have width 5 and height 5.
saveas(gcf, './simResults/TAAF_All_on', 'pdf') %Save figure
% csvwrite('./reliability_results/TAAF_All_on.csv', taaf_all_on);
fprintf('All_ON Average TAAF for 25 watts: %.2f\nAll_ON Average TAAF for 50 watts: %.2f\n', mean(taaf_all_on(:, 1)), mean(taaf_all_on(:, 2)));


    
% All in one plot
figure;
plot(time, taaf_adaptive1(:, 1), 'r', 'LineWidth', 1);
hold
plot(time, taaf_adaptive1(:, 2), 'g', 'LineWidth', 1);
%plot(time, taaf_adaptive(:, 3), 'b', 'LineWidth', 4);
plot(time, taaf_all_on(:, 1), 'm', 'LineWidth', 1);
plot(time, taaf_all_on(:, 2), 'y', 'LineWidth', 1);
%plot(time, taaf_all_on(:, 3), 'c', 'LineWidth', 4);
grid
xlabel('Time (s)');
ylabel('TAAF')
legend('25 watts Adaptive', '50 watts Adaptive', '25 watts All on', '50 watts All on', 'Location', 'NorthOutside');
set(gcf, 'PaperPosition', [0 0 5 5]); %Position plot at left hand corner with width 5 and height 5.
set(gcf, 'PaperSize', [5 5]); %Set the paper to have width 5 and height 5.
saveas(gcf, './simResults/TAAF_all_in_one_plot', 'pdf') %Save figure


    