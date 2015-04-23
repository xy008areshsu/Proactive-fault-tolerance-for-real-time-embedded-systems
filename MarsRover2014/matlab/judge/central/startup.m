function startup()
%
% Parameters that can be set in text file (config.txt)
%
% PictureDirectory
% GlobalResultFile
% NumberOfTeams
% CounterTime
% Background
% BackgroundRanking
% WindowTitle
% 

fid = fopen('config.txt','r');
if (fid > 0)
    
    data = textscan(fid,'%s%s', 'Delimiter', '=', 'CommentStyle', '#');
    data = [data{:}]';    
    fclose(fid);
    
    data(:,cellfun(@isempty, data(2,:))) = [];
            
else
    
    data = {};
    
end

%% Launch GUI
judge_central( data{:} )
