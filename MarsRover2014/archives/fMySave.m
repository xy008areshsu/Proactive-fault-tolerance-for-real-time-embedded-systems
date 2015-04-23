function fMySave(filename,TargetPositions)
% Copyright 2015 The MathWorks, Inc.
[year,month,day,hour,minute,second] = datevec(now) ;

oldfileName = sprintf('%s_%4d_%02d_%02d_%02dH%02dM%06.3fs.bak',...
    filename ,year,month,day,hour,minute,second );
movefile(filename,oldfileName,'f');

fid = fopen(filename,'wt');
try %#ok<TRYNC>
    fprintf(fid,'%% File Autogenerate by function %s\n',mfilename);
    fprintf(fid,'%% Date %s\n',datestr(now,'dddd dd mmmm yyyy HH:MM:SS'));
    fprintf(fid,'TargetPositions = single([...\n');
    fprintf(fid,'\t%4.0f,%4.0f;...\n',TargetPositions');
    fprintf(fid,'\t]);');
end
fclose(fid);
assignin('base','TargetPositions',TargetPositions);
end