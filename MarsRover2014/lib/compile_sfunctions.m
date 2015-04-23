% Copyright 2015 The MathWorks, Inc.
cur_dir = fileparts(mfilename('fullpath'));
cfiles = dir(fullfile(cur_dir,'*.c'));

for i_file = 1:length(cfiles)
    mex(cfiles(i_file).name)
end

clear cur_dir cfiles i_file
