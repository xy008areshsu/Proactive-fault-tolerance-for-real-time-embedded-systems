clear; clc; close all

global sp_dis sp_dis_ub sp_dis_lb


sp_dis_set = [40];
sp_dis_ub_set = [100];
sp_dis_lb_set = [0];
following_car_init_spped_set = [95, 100];

% for i = 1 : size(sp_dis_set, 2)
%     sp_dis = sp_dis_set(i);
%     sp_dis_ub = sp_dis_ub_set(i);
%     sp_dis_lb = sp_dis_lb_set(i);
%     sim('Radar_Acc_ExtSen_CS803_Modified')
%     csvwrite(strcat(int2str(sp_dis), '_data.csv'), [simout.Time, simout.Data]);
% end

for i = 1 : size(following_car_init_spped_set, 2)
    following_car_init_spped = following_car_init_spped_set(i);
    copyfile(strcat('Radar_Acc_ExtSen_Car_2_', int2str(following_car_init_spped), '.sim'), 'Radar_Acc_ExtSen_Car_2.sim');
    sim('Radar_Acc_ExtSen_CS803_Modified');
    csvwrite(strcat(int2str(following_car_init_spped), '_following_car_init_speed.csv'), [simout.Time, simout.Data]);
end