% OPENPROJECT Initialize MATLAB path to work on project
% Copyright 2015 The MathWorks, Inc.
%
%

% Check that version of MATLAB is 8.3 (R2014a)
if verLessThan('matlab', '8.3')
    error('MATLAB 8.3 (R2014a) or higher is required.');
end

% Determine the complete path of project folder
root_dir = fileparts(fileparts(mfilename('fullpath')));

% Add to path all needed directories to work
addpath(fullfile(root_dir,'data')) % Parameters, Images
addpath(fullfile(root_dir,'lib')) % Librairy of drivers for Robot
addpath(fullfile(root_dir,'matlab'))
addpath(fullfile(root_dir,'matlab','judge'))
addpath(fullfile(root_dir,'matlab','trackingApp')) % Graphical Robot representation
addpath(fullfile(root_dir,'matlab','utilities'))
addpath(fullfile(root_dir,'matlab','calibration'))
addpath(fullfile(root_dir,'model')) % SLX files

% Create work directory if it doesn't already exist
if ~isdir(fullfile(root_dir,'work'))
    mkdir(fullfile(root_dir,'work'));
end

% Add work directory in path and set it as destination for all generated
% files from Simulink (for simulation and code generation)
addpath(fullfile(root_dir,'work'))
Simulink.fileGenControl('set', ...
    'CacheFolder',fullfile(root_dir,'work'), ...
    'CodeGenFolder',fullfile(root_dir,'work'))
     
% Clean up workspace
clear root_dir

% Display a message with a hyperlink to open model for simulation
disp('Project initialization is completed.')
disp(' ')
disp('For simulation:')
disp('	You can open <a href="matlab:SimulationModel">simulation model</a> (model/SimulationModel.slx)')
disp(' ')
disp('For robot:')
disp('	You can open <a href="matlab:ArduinoModel">robot model</a> (model/ArduinoModel.slx)')
disp(' ')
disp('To define new sites:')
disp('Use function <a href="matlab:defineSitesPosition">defineSitesPosition</a> (matlab/utilities/defineSitesPosition.m)')
disp('Or use the project shortcut (Project shortcuts tab) "defineSitesPosition"')
disp(' ')
disp('To change the sites order:')
disp('Use function <a href="matlab:changeSitesOrder">changeSitesOrder</a> (matlab/utilities/changeSitesOrder.m)')
disp('Or use the project shortcut (Project shortcuts tab) "changeSitesOrder"')
