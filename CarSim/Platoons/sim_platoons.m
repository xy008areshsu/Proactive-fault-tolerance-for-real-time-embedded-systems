clear; clc; close all


t = 5001;
init_speed_set_1 = 15 : 5 : 15;    % m/s
init_spped_set_2 = 25 : 5 : 25;   % m/s
init_spped_set_3 = 10 : 5 : 30;

station_set_1 = 30 : 5 : 30;
station_set_2 = 20 : 5 : 20;
station_set_3 = 0 : 5 : 5;

% SSS_ms = [];
% SSS_kph = [];

tic
for i = 1 : size(init_speed_set_1, 2)
    for j = 1 :size(init_spped_set_2, 2)
        for k = 1: size(station_set_1, 2)
            for l = 1 : size(station_set_2, 2)
                init_speed_1 = init_speed_set_1(i) * 3.6;    % convert to kph
                init_speed_2 = init_spped_set_2(j) * 3.6;   % convert to kph
                init_station_1 = station_set_1(k);
                init_station_2 = station_set_2(l);
                
                fh = regexp( fileread('C:\Users\Public\Documents\CarSim901_Data\Runs\Run_c108f7e0-2e71-4762-81eb-18daefdbc413_all.par'), '\n', 'split');
                fh{4716} = sprintf('SPEED %d', init_speed_1);
                fh{4717} = sprintf('SV_VXS %d', init_speed_1);
                fh{4710} = sprintf('SSTART %d', init_station_1);
                fh{4713} = sprintf('SSTOP %d', init_station_1 + 1);
                fid = fopen('C:\Users\Public\Documents\CarSim901_Data\Runs\Run_c108f7e0-2e71-4762-81eb-18daefdbc413_all.par','w');
                fprintf(fid, '%s\n', fh{:});
                fclose(fid);
                
                fh = regexp( fileread('C:\Users\Public\Documents\CarSim901_Data\Runs\Run_dce89471-5f39-4def-b570-bec30af87a16_all.par'), '\n', 'split');
                fh{4716} = sprintf('SPEED %d', init_speed_2);
                fh{4717} = sprintf('SV_VXS %d', init_speed_2);
                fh{4710} = sprintf('SSTART %d', init_station_2);
                fh{4713} = sprintf('SSTOP %d', init_station_2 + 1);
                fid = fopen('C:\Users\Public\Documents\CarSim901_Data\Runs\Run_dce89471-5f39-4def-b570-bec30af87a16_all.par','w');
                fprintf(fid, '%s\n', fh{:});
                fclose(fid);
                
                cd C:\Users\Public\Documents\CarSim901_Data
                sim('Two_cars_multi_agent');
                %             csvwrite(strcat('./AHS_data/', int2str(leading_car_init_speed), '_', int2str(following_car_init_spped), '_', int2str(init_dis),...
                %                 '.csv'), [simout.Time, simout.Data]);
                
                cd D:\Dropbox\Phd\AutomaticScriptForSubRegions\CarSim\Platoons
                if tout(end) >= 4.9
                    this_SSS_ms = [init_speed_set_1(i), init_spped_set_2(j), station_set_1(k), station_set_2(l)];
                    this_SSS_kph = [init_speed_1, init_speed_2, init_station_1, init_station_2];
                    dlmwrite('./data/SSS_ms_CTG.csv', this_SSS_ms, '-append');    % for fault tolerance
                    dlmwrite('./data/SSS_kph_CTG.csv', this_SSS_kph, '-append');
                end
%                 i
%                 j
%                 k
%                 l
            end
        end
    end
end

toc

% csvwrite('./data/SSS_ms.csv', SSS_ms);
% csvwrite('./data/SSS_kph.csv', SSS_kph);





% SSS_ms = load('./AHS_data/SSS_ms.csv');
% S_1 = [];
% S_2 = [];
% S_3 = [];
% for i = 1 : size(SSS_ms, 1)
%     leading_car_init_speed = SSS_ms(i, 1) * 3.6;    % convert to kph
%     following_car_init_spped = SSS_ms(i, 2) * 3.6;   % convert to kph
%     init_dis = SSS_ms(i, 3);
%
%     fh = regexp( fileread('C:\Users\Public\Documents\CarSim_Data\Runs\Run279_all.par'), '\n', 'split');
%     fh{3913} = sprintf('SPEED %d', following_car_init_spped);
%     fh{3914} = sprintf('SV_VXS %d', following_car_init_spped);
%     fid = fopen('C:\Users\Public\Documents\CarSim_Data\Runs\Run279_all.par','w');
%     fprintf(fid, '%s\n', fh{:});
%     fclose(fid);
%
%     fh = regexp( fileread('C:\Users\Public\Documents\CarSim_Data\Runs\Run278_all.par'), '\n', 'split');
%     fh{3913} = sprintf('SPEED %d', leading_car_init_speed);
%     fh{3914} = sprintf('SV_VXS %d', leading_car_init_speed);
%     fh{3907} = sprintf('SSTART %d', init_dis);
%     fh{3910} = sprintf('SSTOP %d', init_dis + 1);
%     fid = fopen('C:\Users\Public\Documents\CarSim_Data\Runs\Run278_all.par','w');
%     fprintf(fid, '%s\n', fh{:});
%     fclose(fid);
%
%     sim('Two_cars_multi_agent', 1.6);
%     new_s = roundn([simout.Data(end, 1) / 3.6, simout.Data(end, 5) / 3.6, simout.Data(end, 9)], 0);
%
%     sim('./Extensions/Simulink/Two_cars_multi_agent_worst', 1.6);
%     new_s1 = roundn([simout.Data(end, 1) / 3.6, simout.Data(end, 5) / 3.6, simout.Data(end, 9)], 0);
%
%     if size(intersect(new_s, SSS_ms, 'rows'), 1) ~= 0 && size(intersect(new_s1, SSS_ms, 'rows'), 1) ~= 0
%         S_1 = [S_1; [SSS_ms(i, 1),SSS_ms(i, 2), SSS_ms(i, 3)]];
%         csvwrite('S_1.csv', S_1)
%     elseif size(intersect(new_s, SSS_ms, 'rows'), 1) ~= 0 || size(intersect(new_s1, SSS_ms, 'rows'), 1) ~= 0
%         S_2 = [S_2; [SSS_ms(i, 1),SSS_ms(i, 2), SSS_ms(i, 3)]];
%         csvwrite('S_2.csv', S_2)
%     else
%         S_3 = [S_3; [SSS_ms(i, 1),SSS_ms(i, 2), SSS_ms(i, 3)]];
%         csvwrite('S_3.csv', S_3)
%     end
%     i
% end


