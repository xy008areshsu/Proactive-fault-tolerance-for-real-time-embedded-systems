clear; clc; close all

iter = 4;

t = 5;
platoon_1_init_spped_set_1 = 10 : 5 : 15;
platoon_1_init_spped_set_2 = 10 : 5 : 30;
platoon_1_init_spped_set_3 = 10 : 5 : 30;
platoon_1_station_set_1 = 25 : 5 : 40;
platoon_1_station_set_2 = 5 : 5 : 25;


platoon_2_init_spped_set_1 = 15 : 5 : 20;
platoon_2_init_spped_set_2 = 10 : 5 : 30;
platoon_2_init_spped_set_3 = 10 : 5 : 30;
platoon_2_station_set_1 = 25 : 5 : 40;
platoon_2_station_set_2 = 5 : 5 : 25;

platoon_3_init_spped_set_1 = 20 : 5 : 25;
platoon_3_init_spped_set_2 = 10 : 5 : 30;
platoon_3_init_spped_set_3 = 10 : 5 : 30;
platoon_3_station_set_1 = 25 : 5 : 40;
platoon_3_station_set_2 = 5 : 5 : 25;

platoon_4_init_spped_set_1 = 25 : 5 : 30;
platoon_4_init_spped_set_2 = 10 : 5 : 30;
platoon_4_init_spped_set_3 = 10 : 5 : 30;
platoon_4_station_set_1 = 25 : 5 : 40;
platoon_4_station_set_2 = 5 : 5 : 25;

init_speed_set_1 = 10 : 5 : 40;    % m/s
init_spped_set_2 = 10 : 5 : 40;   % m/s
init_spped_set_3 = 10 : 5 : 40;

station_set_1 = 25 : 5 : 40;
station_set_2 = 5 : 5 : 25;
station_set_3 = 0 : 5 : 5;

% SSS_ms = [];
% SSS_kph = [];
m = size(init_speed_set_1, 2);
n = size(init_spped_set_2, 2);
o = size(station_set_1, 2);
p = size(station_set_2, 2);

simout = cell(1, iter);

tic
parfor i = 1 : iter
    
    if i == 1
        for j = 1 : size(platoon_1_init_spped_set_1, 2)
            for k = 1 : size(platoon_1_init_spped_set_2, 2)
                for n = 1 : size(platoon_1_init_spped_set_3, 2)
                    for l = 1 : size(platoon_1_station_set_1, 2)
                        for m = 1 : size(platoon_1_station_set_2, 2)
                            init_speed_1 = platoon_1_init_spped_set_1(j) * 3.6;    % convert to kph
                            init_speed_2 = platoon_1_init_spped_set_2(k) * 3.6;   % convert to kph
                            init_speed_3 = platoon_1_init_spped_set_3(n) * 3.6;   % convert to kph
                            init_station_1 = platoon_1_station_set_1(l);
                            init_station_2 = platoon_1_station_set_2(m);
                            
                            fh = regexp( fileread('C:\Users\Public\Documents\CarSim901_Data\Runs\Run_acf3f57a-61d7-4f53-87d2-9cc642335a0e_all.par'), '\n', 'split');
                            fh{4716} = sprintf('SPEED %d', init_speed_1);
                            fh{4717} = sprintf('SV_VXS %d', init_speed_1);
                            fh{4710} = sprintf('SSTART %d', init_station_1);
                            fh{4713} = sprintf('SSTOP %d', init_station_1 + 1);
                            fid = fopen('C:\Users\Public\Documents\CarSim901_Data\Runs\Run_acf3f57a-61d7-4f53-87d2-9cc642335a0e_all.par','w');
                            fprintf(fid, '%s\n', fh{:});
                            fclose(fid);
                            
                            fh = regexp( fileread('C:\Users\Public\Documents\CarSim901_Data\Runs\Run_b770902f-478d-40cf-ab1c-7f358445c8d7_all.par'), '\n', 'split');
                            fh{4716} = sprintf('SPEED %d', init_speed_2);
                            fh{4717} = sprintf('SV_VXS %d', init_speed_2);
                            fh{4710} = sprintf('SSTART %d', init_station_2);
                            fh{4713} = sprintf('SSTOP %d', init_station_2 + 1);
                            fid = fopen('C:\Users\Public\Documents\CarSim901_Data\Runs\Run_b770902f-478d-40cf-ab1c-7f358445c8d7_all.par','w');
                            fprintf(fid, '%s\n', fh{:});
                            fclose(fid);
                            
                            fh = regexp( fileread('C:\Users\Public\Documents\CarSim901_Data\Runs\Run_abce568e-5d07-4771-8b55-7ebdb614fde2_all.par'), '\n', 'split');
                            fh{4716} = sprintf('SPEED %d', init_speed_3);
                            fh{4717} = sprintf('SV_VXS %d', init_speed_3);
                            %                         fh{4710} = sprintf('SSTART %d', init_station_2);
                            %                         fh{4713} = sprintf('SSTOP %d', init_station_2 + 1);
                            fid = fopen('C:\Users\Public\Documents\CarSim901_Data\Runs\Run_abce568e-5d07-4771-8b55-7ebdb614fde2_all.par','w');
                            fprintf(fid, '%s\n', fh{:});
                            fclose(fid);
                            
                            cd C:\Users\Public\Documents\CarSim901_Data
                            load_system('platoon_1');
                            simout{i} = sim('platoon_1');
                            %             csvwrite(strcat('./AHS_data/', int2str(leading_car_init_speed), '_', int2str(following_car_init_spped), '_', int2str(init_dis),...
                            %                 '.csv'), [simout.Time, simout.Data]);
                            
                            cd D:\Dropbox\Phd\AutomaticScriptForSubRegions\CarSim\Platoons
                            if simout{i}(end) >= 4.9
                                this_SSS_ms = [platoon_1_init_spped_set_1(j), platoon_1_init_spped_set_2(k), platoon_1_init_spped_set_3(n), platoon_1_station_set_1(l), platoon_1_station_set_2(m)];                                
                                dlmwrite('./data/SSS_ms_CTG_parallel_1.csv', this_SSS_ms, '-append');   
                            end
                        end
                    end
                end
            end
        end
    elseif i == 2
        for j = 1 : size(platoon_2_init_spped_set_1, 2)
            for k = 1 : size(platoon_2_init_spped_set_2, 2)
                for n = 1 : size(platoon_2_init_spped_set_3, 2)
                    for l = 1 : size(platoon_2_station_set_1, 2)
                        for m = 1 : size(platoon_2_station_set_2, 2)
                            init_speed_1 = platoon_2_init_spped_set_1(j) * 3.6;    % convert to kph
                            init_speed_2 = platoon_2_init_spped_set_2(k) * 3.6;   % convert to kph
                            init_speed_3 = platoon_2_init_spped_set_3(n) * 3.6;   % convert to kph
                            init_station_1 = platoon_2_station_set_1(l);
                            init_station_2 = platoon_2_station_set_2(m);
                            
                            fh = regexp( fileread('C:\Users\Public\Documents\CarSim901_Data\Runs\Run_5ea3867a-d9e0-4139-b868-ffffe94c0e36_all.par'), '\n', 'split');
                            fh{4716} = sprintf('SPEED %d', init_speed_1);
                            fh{4717} = sprintf('SV_VXS %d', init_speed_1);
                            fh{4710} = sprintf('SSTART %d', init_station_1);
                            fh{4713} = sprintf('SSTOP %d', init_station_1 + 1);
                            fid = fopen('C:\Users\Public\Documents\CarSim901_Data\Runs\Run_5ea3867a-d9e0-4139-b868-ffffe94c0e36_all.par','w');
                            fprintf(fid, '%s\n', fh{:});
                            fclose(fid);
                            
                            fh = regexp( fileread('C:\Users\Public\Documents\CarSim901_Data\Runs\Run_52471c0a-dadf-4046-a733-1457c5d9acc3_all.par'), '\n', 'split');
                            fh{4716} = sprintf('SPEED %d', init_speed_2);
                            fh{4717} = sprintf('SV_VXS %d', init_speed_2);
                            fh{4710} = sprintf('SSTART %d', init_station_2);
                            fh{4713} = sprintf('SSTOP %d', init_station_2 + 1);
                            fid = fopen('C:\Users\Public\Documents\CarSim901_Data\Runs\Run_52471c0a-dadf-4046-a733-1457c5d9acc3_all.par','w');
                            fprintf(fid, '%s\n', fh{:});
                            fclose(fid);
                            
                            fh = regexp( fileread('C:\Users\Public\Documents\CarSim901_Data\Runs\Run_4da834e8-d5d2-4c97-b7a3-45302146c195_all.par'), '\n', 'split');
                            fh{4716} = sprintf('SPEED %d', init_speed_3);
                            fh{4717} = sprintf('SV_VXS %d', init_speed_3);
                            %                         fh{4710} = sprintf('SSTART %d', init_station_2);
                            %                         fh{4713} = sprintf('SSTOP %d', init_station_2 + 1);
                            fid = fopen('C:\Users\Public\Documents\CarSim901_Data\Runs\Run_4da834e8-d5d2-4c97-b7a3-45302146c195_all.par','w');
                            fprintf(fid, '%s\n', fh{:});
                            fclose(fid);
                            
                            cd C:\Users\Public\Documents\CarSim901_Data
                            load_system('platoon_2');
                            simout{i} = sim('platoon_2');
                            %             csvwrite(strcat('./AHS_data/', int2str(leading_car_init_speed), '_', int2str(following_car_init_spped), '_', int2str(init_dis),...
                            %                 '.csv'), [simout.Time, simout.Data]);
                            
                            cd D:\Dropbox\Phd\AutomaticScriptForSubRegions\CarSim\Platoons
                            if simout{i}(end) >= 4.9
                                this_SSS_ms = [platoon_2_init_spped_set_1(j), platoon_2_init_spped_set_2(k), platoon_2_init_spped_set_3(n), platoon_2_station_set_1(l), platoon_2_station_set_2(m)];
                                
                                dlmwrite('./data/SSS_ms_CTG_parallel_2.csv', this_SSS_ms, '-append');    % for fault tolerance

                            end
                        end
                    end
                end
            end
        end
    elseif i == 3
        for j = 1 : size(platoon_3_init_spped_set_1, 2)
            for k = 1 : size(platoon_3_init_spped_set_2, 2)
                for n = 1 : size(platoon_3_init_spped_set_3, 2)
                    for l = 1 : size(platoon_3_station_set_1, 2)
                        for m = 1 : size(platoon_3_station_set_2, 2)
                            init_speed_1 = platoon_3_init_spped_set_1(j) * 3.6;    % convert to kph
                            init_speed_2 = platoon_3_init_spped_set_2(k) * 3.6;   % convert to kph
                            init_speed_3 = platoon_3_init_spped_set_3(n) * 3.6;   % convert to kph
                            init_station_1 = platoon_3_station_set_1(l);
                            init_station_2 = platoon_3_station_set_2(m);
                            
                            fh = regexp( fileread('C:\Users\Public\Documents\CarSim901_Data\Runs\Run_fe28968d-cd49-48c6-820d-73fef265f154_all.par'), '\n', 'split');
                            fh{4716} = sprintf('SPEED %d', init_speed_1);
                            fh{4717} = sprintf('SV_VXS %d', init_speed_1);
                            fh{4710} = sprintf('SSTART %d', init_station_1);
                            fh{4713} = sprintf('SSTOP %d', init_station_1 + 1);
                            fid = fopen('C:\Users\Public\Documents\CarSim901_Data\Runs\Run_fe28968d-cd49-48c6-820d-73fef265f154_all.par','w');
                            fprintf(fid, '%s\n', fh{:});
                            fclose(fid);
                            
                            fh = regexp( fileread('C:\Users\Public\Documents\CarSim901_Data\Runs\Run_4ade659f-c420-4024-897c-7da6169550d5_all.par'), '\n', 'split');
                            fh{4716} = sprintf('SPEED %d', init_speed_2);
                            fh{4717} = sprintf('SV_VXS %d', init_speed_2);
                            fh{4710} = sprintf('SSTART %d', init_station_2);
                            fh{4713} = sprintf('SSTOP %d', init_station_2 + 1);
                            fid = fopen('C:\Users\Public\Documents\CarSim901_Data\Runs\Run_4ade659f-c420-4024-897c-7da6169550d5_all.par','w');
                            fprintf(fid, '%s\n', fh{:});
                            fclose(fid);
                            
                            fh = regexp( fileread('C:\Users\Public\Documents\CarSim901_Data\Runs\Run_715aa7b7-e137-434a-a84f-d61a4b9ed6ea_all.par'), '\n', 'split');
                            fh{4716} = sprintf('SPEED %d', init_speed_3);
                            fh{4717} = sprintf('SV_VXS %d', init_speed_3);
                            %                         fh{4710} = sprintf('SSTART %d', init_station_2);
                            %                         fh{4713} = sprintf('SSTOP %d', init_station_2 + 1);
                            fid = fopen('C:\Users\Public\Documents\CarSim901_Data\Runs\Run_715aa7b7-e137-434a-a84f-d61a4b9ed6ea_all.par','w');
                            fprintf(fid, '%s\n', fh{:});
                            fclose(fid);
                            
                            cd C:\Users\Public\Documents\CarSim901_Data
                            load_system('platoon_3');
                            simout{i} = sim('platoon_3');
                            %             csvwrite(strcat('./AHS_data/', int2str(leading_car_init_speed), '_', int2str(following_car_init_spped), '_', int2str(init_dis),...
                            %                 '.csv'), [simout.Time, simout.Data]);
                            
                            cd D:\Dropbox\Phd\AutomaticScriptForSubRegions\CarSim\Platoons
                            if simout{i}(end) >= 4.9
                                this_SSS_ms = [platoon_3_init_spped_set_1(j), platoon_3_init_spped_set_2(k), platoon_3_init_spped_set_3(n),platoon_3_station_set_1(l), platoon_3_station_set_2(m)];
                                
                                dlmwrite('./data/SSS_ms_CTG_parallel_3.csv', this_SSS_ms, '-append');    % for fault tolerance
                                
                            end
                        end
                    end
                end
            end
        end
    elseif i == 4
        for j = 1 : size(platoon_4_init_spped_set_1, 2)
            for k = 1 : size(platoon_4_init_spped_set_2, 2)
                for n = 1 : size(platoon_4_init_spped_set_3, 2)
                    for l = 1 : size(platoon_4_station_set_1, 2)
                        for m = 1 : size(platoon_4_station_set_2, 2)
                            init_speed_1 = platoon_4_init_spped_set_1(j) * 3.6;    % convert to kph
                            init_speed_2 = platoon_4_init_spped_set_2(k) * 3.6;   % convert to kph
                            init_speed_3 = platoon_4_init_spped_set_3(n) * 3.6;   % convert to kph
                            init_station_1 = platoon_4_station_set_1(l);
                            init_station_2 = platoon_4_station_set_2(m);
                            
                            fh = regexp( fileread('C:\Users\Public\Documents\CarSim901_Data\Runs\Run_07365dd5-22c3-41fd-9979-c6a8e056a6e0_all.par'), '\n', 'split');
                            fh{4716} = sprintf('SPEED %d', init_speed_1);
                            fh{4717} = sprintf('SV_VXS %d', init_speed_1);
                            fh{4710} = sprintf('SSTART %d', init_station_1);
                            fh{4713} = sprintf('SSTOP %d', init_station_1 + 1);
                            fid = fopen('C:\Users\Public\Documents\CarSim901_Data\Runs\Run_07365dd5-22c3-41fd-9979-c6a8e056a6e0_all.par','w');
                            fprintf(fid, '%s\n', fh{:});
                            fclose(fid);
                            
                            fh = regexp( fileread('C:\Users\Public\Documents\CarSim901_Data\Runs\Run_f9be78f4-3c35-4be2-af01-194c53c6072d_all.par'), '\n', 'split');
                            fh{4716} = sprintf('SPEED %d', init_speed_2);
                            fh{4717} = sprintf('SV_VXS %d', init_speed_2);
                            fh{4710} = sprintf('SSTART %d', init_station_2);
                            fh{4713} = sprintf('SSTOP %d', init_station_2 + 1);
                            fid = fopen('C:\Users\Public\Documents\CarSim901_Data\Runs\Run_f9be78f4-3c35-4be2-af01-194c53c6072d_all.par','w');
                            fprintf(fid, '%s\n', fh{:});
                            fclose(fid);
                            
                            fh = regexp( fileread('C:\Users\Public\Documents\CarSim901_Data\Runs\Run_a6ef02c2-bb93-4554-b4ed-aad2f498cad5_all.par'), '\n', 'split');
                            fh{4716} = sprintf('SPEED %d', init_speed_3);
                            fh{4717} = sprintf('SV_VXS %d', init_speed_3);
                            %                         fh{4710} = sprintf('SSTART %d', init_station_2);
                            %                         fh{4713} = sprintf('SSTOP %d', init_station_2 + 1);
                            fid = fopen('C:\Users\Public\Documents\CarSim901_Data\Runs\Run_a6ef02c2-bb93-4554-b4ed-aad2f498cad5_all.par','w');
                            fprintf(fid, '%s\n', fh{:});
                            fclose(fid);
                            
                            cd C:\Users\Public\Documents\CarSim901_Data
                            load_system('platoon_4');
                            simout{i} = sim('platoon_4');
                            %             csvwrite(strcat('./AHS_data/', int2str(leading_car_init_speed), '_', int2str(following_car_init_spped), '_', int2str(init_dis),...
                            %                 '.csv'), [simout.Time, simout.Data]);
                            
                            cd D:\Dropbox\Phd\AutomaticScriptForSubRegions\CarSim\Platoons
                            if simout{i}(end) >= 4.9
                                this_SSS_ms = [platoon_4_init_spped_set_1(j), platoon_4_init_spped_set_2(k), platoon_4_init_spped_set_3(n),platoon_4_station_set_1(l), platoon_4_station_set_2(m)];
                                
                                dlmwrite('./data/SSS_ms_CTG_parallel_4.csv', this_SSS_ms, '-append');    % for fault tolerance
                               
                            end
                        end
                    end
                end
            end
        end
    end
    
end
toc

dlmwrite('./data/SSS_ms_CTG_parallel_1.csv', [], '-append')
dlmwrite('./data/SSS_ms_CTG_parallel_2.csv', [], '-append')
dlmwrite('./data/SSS_ms_CTG_parallel_3.csv', [], '-append')
dlmwrite('./data/SSS_ms_CTG_parallel_4.csv', [], '-append')

dlmwrite('./data/sss_ms.csv', load('./data/SSS_ms_CTG_parallel_1.csv'), '-append')
dlmwrite('./data/sss_ms.csv', load('./data/SSS_ms_CTG_parallel_2.csv'), '-append')
dlmwrite('./data/sss_ms.csv', load('./data/SSS_ms_CTG_parallel_3.csv'), '-append')
dlmwrite('./data/sss_ms.csv', load('./data/SSS_ms_CTG_parallel_4.csv'), '-append')


delete('./data/SSS_ms_CTG_parallel_1.csv')
delete('./data/SSS_ms_CTG_parallel_2.csv')
delete('./data/SSS_ms_CTG_parallel_3.csv')
delete('./data/SSS_ms_CTG_parallel_4.csv')



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


