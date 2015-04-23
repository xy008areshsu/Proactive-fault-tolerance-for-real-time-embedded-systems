function startup
% Copyright 2015 The MathWorks, Inc.
%
% Parameters that can be set in text file (config.txt)
%
% Nsites
% ResultFile
% SnapshotDir
% CalibrationFile
% DisplayWarnings
% Teams: List of teams separated by a comma
% 

fid = fopen('config.txt','r');
if (fid > 0)
    
    data = textscan(fid,'%s%s', 'Delimiter', '=', 'CommentStyle', '#');
    data = [data{:}]';    
    fclose(fid);
    
    data(:,cellfun(@isempty, data(2,:))) = [];
    
    if any(strcmpi(data(1,:),'Teams'))
        data(2,strcmpi(data(1,:),'Teams')) = ...
            textscan(data{2,strcmpi(data(1,:),'Teams')},'%s','Delimiter',',');        
    end
    
else
    
    data = {};
    
end

% Launch judge
judge_control(data{:})

