% clear; clc; close all
% 
% 
% t = 10001;   
% leading_car_init_speed_set = 5 : 1 : 33;    % m/s
% following_car_init_spped_set = 5 : 1 : 33;   % m/s
% 
% init_dis_set = 10 : 1 : 70;
% 
% SSS_ms = [];
% SSS_kph = [];
% 
% for i = 1 : size(leading_car_init_speed_set, 2)
%     for j = 1 :size(following_car_init_spped_set, 2)
%         for k = 1: size(init_dis_set, 2)
%             leading_car_init_speed = leading_car_init_speed_set(i) * 3.6;    % convert to kph
%             following_car_init_spped = following_car_init_spped_set(j) * 3.6;   % convert to kph
%             init_dis = init_dis_set(k);
% 
%             fh = regexp( fileread('C:\Users\Public\Documents\CarSim_Data\Runs\Run279_all.par'), '\n', 'split');
%             fh{3913} = sprintf('SPEED %d', following_car_init_spped);
%             fh{3914} = sprintf('SV_VXS %d', following_car_init_spped);
%             fid = fopen('C:\Users\Public\Documents\CarSim_Data\Runs\Run279_all.par','w');
%             fprintf(fid, '%s\n', fh{:});
%             fclose(fid);
%             
%             fh = regexp( fileread('C:\Users\Public\Documents\CarSim_Data\Runs\Run278_all.par'), '\n', 'split');
%             fh{3913} = sprintf('SPEED %d', leading_car_init_speed);
%             fh{3914} = sprintf('SV_VXS %d', leading_car_init_speed);
%             fh{3907} = sprintf('SSTART %d', init_dis);
%             fh{3910} = sprintf('SSTOP %d', init_dis + 1);
%             fid = fopen('C:\Users\Public\Documents\CarSim_Data\Runs\Run278_all.par','w');
%             fprintf(fid, '%s\n', fh{:});
%             fclose(fid);
%             
%             sim('Two_cars_multi_agent');
% %             csvwrite(strcat('./AHS_data/', int2str(leading_car_init_speed), '_', int2str(following_car_init_spped), '_', int2str(init_dis),...
% %                 '.csv'), [simout.Time, simout.Data]);
%             
%             if size(simout.Time, 1) >= t
%                 SSS_ms = [SSS_ms; [leading_car_init_speed_set(i), following_car_init_spped_set(j), init_dis_set(k)]];
%                 SSS_kph = [SSS_kph; [leading_car_init_speed, following_car_init_spped, init_dis]];
%                 csvwrite('./AHS_data/SSS_ms_CTG.csv', SSS_ms);    % for fault tolerance
%                 csvwrite('./AHS_data/SSS_kph_CTG.csv', SSS_kph);
%             end
%             i
%             j
%             k
%         end
%     end
% end
% 
% 
% 
% csvwrite('./AHS_data/SSS_ms.csv', SSS_ms);
% csvwrite('./AHS_data/SSS_kph.csv', SSS_kph);





% SSS_ms = load('./AHS_data/SSS_ms.csv');
S_1 = [];
S_2 = [];
S_3 = [];
for i = 1 : size(SSS_ms, 1)
    leading_car_init_speed = SSS_ms(i, 1) * 3.6;    % convert to kph
    following_car_init_spped = SSS_ms(i, 2) * 3.6;   % convert to kph
    init_dis = SSS_ms(i, 3);
    
    fh = regexp( fileread('C:\Users\Public\Documents\CarSim_Data\Runs\Run279_all.par'), '\n', 'split');
    fh{3913} = sprintf('SPEED %d', following_car_init_spped);
    fh{3914} = sprintf('SV_VXS %d', following_car_init_spped);
    fid = fopen('C:\Users\Public\Documents\CarSim_Data\Runs\Run279_all.par','w');
    fprintf(fid, '%s\n', fh{:});
    fclose(fid);
    
    fh = regexp( fileread('C:\Users\Public\Documents\CarSim_Data\Runs\Run278_all.par'), '\n', 'split');
    fh{3913} = sprintf('SPEED %d', leading_car_init_speed);
    fh{3914} = sprintf('SV_VXS %d', leading_car_init_speed);
    fh{3907} = sprintf('SSTART %d', init_dis);
    fh{3910} = sprintf('SSTOP %d', init_dis + 1);
    fid = fopen('C:\Users\Public\Documents\CarSim_Data\Runs\Run278_all.par','w');
    fprintf(fid, '%s\n', fh{:});
    fclose(fid);

    sim('Two_cars_multi_agent', 1.6);
    new_s = roundn([simout.Data(end, 1) / 3.6, simout.Data(end, 5) / 3.6, simout.Data(end, 9)], 0);

    sim('./Extensions/Simulink/Two_cars_multi_agent_worst', 1.6);
    new_s1 = roundn([simout.Data(end, 1) / 3.6, simout.Data(end, 5) / 3.6, simout.Data(end, 9)], 0);
    
    if size(intersect(new_s, SSS_ms, 'rows'), 1) ~= 0 && size(intersect(new_s1, SSS_ms, 'rows'), 1) ~= 0
        S_1 = [S_1; [SSS_ms(i, 1),SSS_ms(i, 2), SSS_ms(i, 3)]];
        csvwrite('S_1.csv', S_1)    
    elseif size(intersect(new_s, SSS_ms, 'rows'), 1) ~= 0 || size(intersect(new_s1, SSS_ms, 'rows'), 1) ~= 0
        S_2 = [S_2; [SSS_ms(i, 1),SSS_ms(i, 2), SSS_ms(i, 3)]];
        csvwrite('S_2.csv', S_2)
    else
        S_3 = [S_3; [SSS_ms(i, 1),SSS_ms(i, 2), SSS_ms(i, 3)]];
        csvwrite('S_3.csv', S_3)
    end
    i
end
        
   
