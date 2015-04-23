% Copyright 2015 The MathWorks, Inc.
%%
root_dir = fileparts(fileparts(fileparts(mfilename('fullpath'))));

proj = simulinkproject;
file_list = proj.Files;

%%
simu_files = arrayfun(@(x) ~isempty(findLabel(x,'Classification','Simulation')), file_list);
all_files  = arrayfun(@(x) ~isempty(findLabel(x,'Classification','All')), file_list);

%%
file2ignore = {file_list(~simu_files & ~all_files).Path};
file2ignore = strrep(file2ignore, root_dir, '');

file2zip = [{file_list(simu_files | all_files).Path} ...
    {'.SimulinkProject' 'MakerFaire.prj'}];
file2zip = cellfun(@(x) strrep(x,[root_dir filesep],''), file2zip, 'UniformOutput', false);

%%
zip('test.zip', file2zip)

%%
fid = fopen('simu_ignorefiles', 'wt');
fprintf(fid,'%s\n', file2ignore{:});
fclose(fid);
