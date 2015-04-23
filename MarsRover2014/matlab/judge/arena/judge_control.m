function varargout = judge_control(varargin)
% Copyright 2015 The MathWorks, Inc.
% JUDGE_CONTROL MATLAB code for judge_control.fig
%      JUDGE_CONTROL, by itself, creates a new JUDGE_CONTROL or raises the existing
%      singleton*.
%
%      H = JUDGE_CONTROL returns the handle to a new JUDGE_CONTROL or the handle to
%      the existing singleton*.
%
%      JUDGE_CONTROL('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in JUDGE_CONTROL.M with the given input arguments.
%
%      JUDGE_CONTROL('Property','Value',...) creates a new JUDGE_CONTROL or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before judge_control_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to judge_control_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help judge_control

% Last Modified by GUIDE v2.5 15-May-2014 15:31:16

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
    'gui_Singleton',  gui_Singleton, ...
    'gui_OpeningFcn', @judge_control_OpeningFcn, ...
    'gui_OutputFcn',  @judge_control_OutputFcn, ...
    'gui_LayoutFcn',  [] , ...
    'gui_Callback',   []);
if nargin && ischar(varargin{1})
    gui_State.gui_Callback = str2func(varargin{1});
end

if nargout
    [varargout{1:nargout}] = gui_mainfcn(gui_State, varargin{:});
else
    gui_mainfcn(gui_State, varargin{:});
end
% End initialization code - DO NOT EDIT


% --- Executes just before judge_control is made visible.
function judge_control_OpeningFcn(hObject, ~, handles, varargin)

try
    
    % Display warnings controls if warning must be raised or not
    %   During development warnings are useful to get information about
    %       invalid or default behavior
    %   In production context, warnings can be disturbing if they appears
    %       in CommandWindow
    %
    if any(strcmpi(varargin,'DisplayWarnings'))
        handles.display_warnings = varargin{find(strcmpi(varargin,'DisplayWarnings'))+1};
        
        if ischar(handles.display_warnings) && ~isnan(str2double(handles.display_warnings))
            handles.display_warnings = logical(str2double(handles.display_warnings));
        else
            handles.display_warnings = true;
        end
        
    else
        handles.display_warnings = true;
    end
    
    if any(strcmpi(varargin,'ResultFile')) && ...
            numel(varargin) > find(strcmpi(varargin,'ResultFile'))
        handles.datafile = varargin{find(strcmpi(varargin,'ResultFile'),1)+1};
    else
        handles.datafile = 'MakerFaireCompetitionResults.mat';
    end
    
    if any(strcmpi(varargin,'SnapshotDir')) && ...
            numel(varargin) > find(strcmpi(varargin,'SnapshotDir'))
        handles.snapshot_dir = varargin{find(strcmpi(varargin,'SnapshotDir'),1)+1};
    else
        handles.snapshot_dir = '.';
    end
    
    
    if any(strcmpi(varargin,'Nsites')) && ...
            numel(varargin) > find(strcmpi(varargin,'Nsites'))
        handles.nsites = varargin{find(strcmpi(varargin,'Nsites'),1)+1};
        
        if ischar(handles.nsites) && ~isnan(str2double(handles.nsites))
            handles.nsites = str2double(handles.nsites);
        else
            handles.nsites = 5;
        end
        
    else
        handles.nsites = 5;
    end
    
    if any(strcmpi(varargin,'CalibrationFile')) && ...
            numel(varargin) > find(strcmpi(varargin,'CalibrationFile'))
        calibrationFile = varargin{find(strcmpi(varargin,'CalibrationFile'),1)+1};
    else
        calibrationFile = 'judge_thresholds_calibration.mat';
    end
    
    if ~exist(calibrationFile, 'file')
        error('Default calibration file does not exist');
    end
        
    % Initialize Judge object
    judge = Judge('Nsites',handles.nsites,'CalibrationFile',calibrationFile);
    setappdata(hObject, 'Judge', judge)
    
    % Create another window to display camera and robot displacement
    handles.FgCamera = CameraDisplay( ...
        'Title',                'MakerFaire: Exploration de Mars', ...
        'SiteString',           'Sites visités', ...
        'TimeString',           'Temps écoulé', ...
        'Visible',              'off',...
        'AllSites', judge.SitePositions);
    
    % Create timer
    handles.timer_refresh_display = timer( ...
        'ExecutionMode',        'fixedSpacing', ...
        'Period',               0.1, ...
        'TimerFcn',             @(obj,evt) LocalUpdate(obj,evt,handles));
    
    % Load images for lights
    if exist('light_red.png','file') && ...
            exist('light_orange.png','file') && ...
            exist('light_green.png','file')
        
        light.red = imread('light_red.png');
        light.orange = imread('light_orange.png');
        light.green = imread('light_green.png');
        set(handles.PbSignalization, 'UserData', light)
        
    else
        LocalWarning(handles,'JudgeControl:MissingFile', ...
            'Impossible de trouver les images nécessaires pour le bon affichage de la fenêtre')
    end
    
    % Initialize image display
    LocalUpdateLight(handles,'invalid')
    
    % Load list of teams, display and save it in popupmenu    
    if any(strcmpi(varargin,'Teams')) && ...
            numel(varargin) > find(strcmpi(varargin,'Teams'))
        
        % Read team names in file (and close file)
        teams = [{''}; varargin{find(strcmpi(varargin,'Teams'),1)+1}];
        
        % Add team list in popupmenu
        set(handles.PmTeams, 'String', teams, 'Value', 1)
        
    else
        
        % Fill team list popup with an empty cell array
        set(handles.PmTeams, 'String', {''}, 'Value', 1)
        
    end
    
    % Initialize ranking listbox
    LocalUpdateRanking(handles)
    
    % Disable Stop button (is enabled only when judge is running)
    set(handles.PbStop, 'Enable', 'off')
    
    % Center window on screen
    movegui(hObject,'center')
    
    % Update handles structure
    guidata(hObject, handles);
    
catch me
    
    errordlg(sprintf('Une erreur est survenue:\n%s', me.message))
    rethrow(me)
    
end

% --- Outputs from this function are returned to the command line.
function varargout = judge_control_OutputFcn(~, ~, ~)  %#ok<STOUT>

function PbStart_Callback(~, ~, handles) %#ok<DEFNU>

try
    
    % Check that a team is selected
    selected_team = get(handles.PmTeams,'String');
    selected_team = selected_team{get(handles.PmTeams,'Value')};
    
    if isempty(selected_team)
        warnmsg = 'Impossible de lancer le juge si aucune équipe n''est sélectionnée';
        warndlg(warnmsg);
        LocalWarning(handles,'JudgeControl:InvalidTeam', warnmsg)
        return
    end
    
    % Update light
    LocalUpdateLight(handles,'wait')
    set(handles.FgJudgeControl, 'Pointer', 'watch');drawnow;
    
    % Launch detection initialization
    %   Input is a function handle to function that will be called by
    %   detection algorithm. UPDATE_ROBOT_POSITION is a function (in a
    %   separate M-file).
    %   Output a flag (is_detection_ready), if it's TRUE when can start run
    %   Also output a timer object that can be used to stop detection with
    %   command: stop(detection_fcn)
    judge = getappdata(handles.FgJudgeControl, 'Judge');
    setup(judge)
    
    if (judge.IsRunning)
        
        % Update light
        LocalUpdateLight(handles,'valid')
        set(handles.FgJudgeControl, 'Pointer', 'arrow');drawnow;
        
        % Disable start button when judge is ready and enable stop button
        set(handles.PbStart, 'Enable', 'off')
        set(handles.PbStop, 'Enable', 'on')
        
        % Disable team selection, it is not possible to change team during a run
        set(handles.PmTeams, 'Enable', 'off')
                
        % Display camera
        set(handles.FgCamera, ...
            'Visible',              'on', ...
            'AllSites',             judge.SitePositions, ...            
            'ValidatedSites',       0, ...
            'ElapsedTime',          0, ...            
            'TeamName',             selected_team, ...
            'ValidTargetAreas',     true, ...
            'Trajectory',           []);
        
        % Start timer to refresh display
        start(handles.timer_refresh_display)
        
    else
        
        % Display camera
        set(handles.FgCamera, ...
            'Visible',              'on', ...
            'AllSites',             judge.SitePositions, ...
            'Background',           judge.CurrentSnapshot, ...
            'ValidatedSites',       0, ...
            'ElapsedTime',          0, ...
            'TeamName',             'INVALID', ...
            'ValidTargetAreas',     true, ...
            'Trajectory',           []);
        
        % Update light
        LocalUpdateLight(handles,'invalid')
        set(handles.FgJudgeControl, 'Pointer', 'arrow');drawnow;
        
        % Display last message returned by judge
        warndlg(judge.LastMessage)
        
    end
    
catch me
    
    % Make sure that mouse display is an arrow
    set(handles.FgJudgeControl, 'Pointer', 'arrow');drawnow;
    
    LocalUpdateLight(handles,'invalid')
    
    % Display error message in a dialog box and rethrow error
    errordlg(sprintf('Une erreur est survenue:\n%s', me.message))
    rethrow(me)
    
end

function PbStop_Callback(~, ~, handles) %#ok<DEFNU>

try
    
    set(handles.FgJudgeControl,'Pointer','watch'); drawnow;
    
    LocalStop(handles)
    
    set(handles.FgJudgeControl,'Pointer','arrow'); drawnow;
    
catch me
    
    % Display error message and rethrow error
    errordlg(sprintf('Une erreur est survenue:\n%s', me.message))
    rethrow(me)
    
end

function FgJudgeControl_CloseRequestFcn(hObject, ~, handles) %#ok<DEFNU>

try
    
    % Start timer to refresh display
    if strcmp(handles.timer_refresh_display.Running,'on')
        stop(handles.timer_refresh_display)
    end
    delete(handles.timer_refresh_display)
    
    % Delete Judge object
    judge = getappdata(hObject, 'Judge');
    release(judge)
    delete(judge)
    
    % Delete Camera window
    delete(handles.FgCamera)
    
catch me
    LocalWarning(handles,'JudgeControl:UndefinedError', ...
        'Error occurs during window closing with message:\n%s\n', ...
        me.message)
end

% Delete current window
delete(hObject);

function LocalUpdate(~,~,handles)

% Get judge object
judge = getappdata(handles.FgJudgeControl, 'Judge');

% Camera visualization is updated
set(handles.FgCamera, ...
    'ValidatedSites',       judge.IsSiteVisited, ...
    'ElapsedTime',          judge.CurrentTime, ...
    'ScoreTime',            judge.ScoreTime, ...
    'Background',           judge.CurrentSnapshot,...
    'RobotPosition',        [judge.RobotX, judge.RobotY], ...
    'CountDown',            judge.RemainingTimeOnTarget);

if ~judge.IsRunning
    
    % Stop timer object and update display (ranking)
    LocalStop(guidata(handles.FgJudgeControl))
    
end

function LocalStop(handles)

% Stop timer object
if strcmp(handles.timer_refresh_display.Running,'on')
    stop(handles.timer_refresh_display)
end

% Get judge object
judge = getappdata(handles.FgJudgeControl, 'Judge');
release(judge)

% Load existing datafile or initialize data
if exist(handles.datafile,'file')
    results = load(handles.datafile);
else
    results = struct('TeamsData',table([],[],[],[],'VariableNames',{'Timestamp','Team' 'Time' 'Sites'}));
end

% Get team result
team = get(handles.PmTeams, 'String');
team = team{get(handles.PmTeams, 'Value')};

if ~isempty(team)
    
    current_result = table(now,{team},judge.ScoreTime,nnz(judge.IsSiteVisited), 'VariableNames',{'Timestamp','Team','Time','Sites'});
            
    % Add an item in result list
    results.TeamsData = [results.TeamsData;current_result]; %#ok<STRNU>
    
    % Save datafile (add directory name to make sure that file cannot be
    % created in whatever folfer)
    [pathname,filename] = fileparts(handles.datafile);
    if isempty(pathname)
        filename = fullfile(fileparts(mfilename('fullpath')),[filename '.mat']);
    else
        filename = fullfile(pathname,[filename '.mat']);
    end
    
    save(filename, '-struct', 'results')
          
    % Take a snapshot of result window
    filename = fullfile(handles.snapshot_dir, [team, '_', datestr(now,'HHMMSS') '.jpg']);
    print(handles.FgCamera.Handle,filename,'-djpeg')
    
    %% Get list of existing team results (sorted)
    %sorted_team_results = LocalCalculateRanking(results.TeamsData(strcmp(results.TeamsData.Team, team),:));
    
    % Display a message box with results of current run
    msgbox(sprintf('Fin de l''exploration pour l''équipe %s.\n%d sites visités en %.2f secondes.', ...
        char(current_result{1,'Team'}), char(current_result{1,'Sites'}), char(current_result{1,'Time'})), ...
        'Fin d''exploration');
    
end

% Deselect team in popupmenu
set(handles.PmTeams, 'Value', 1)

% Update light
LocalUpdateLight(handles,'invalid')

% Judge is stopped, disable stop button and enable start one
set(handles.PbStart, 'Enable', 'on')
set(handles.PbStop, 'Enable', 'off')

% Enable team selection
set(handles.PmTeams, 'Enable', 'on')

% Update ranking
LocalUpdateRanking(handles)

function LocalUpdateLight(handles,state)

% Load light images
light = get(handles.PbSignalization, 'UserData');

% Abord update if structure light is not valid
if ~all(isfield(light,{'red','green','orange'}))
    return
end

% Apply corresponding image on button
switch lower(state)
    
    case 'invalid'
        set(handles.PbSignalization, 'CData', light.red)
    case 'wait'
        set(handles.PbSignalization, 'CData', light.orange)
    case 'valid'
        set(handles.PbSignalization, 'CData', light.green)
    otherwise
        set(handles.PbSignalization, 'CData', light.red)
        
end

function LocalUpdateRanking(handles)

COLUMN_WIDTH = 19; % Column width in number of characters

% Header (title) lines
header = {LocalFormatColumns(COLUMN_WIDTH, 'Equipe', 'Temps', 'Sites visités');repmat('-',1,3*COLUMN_WIDTH)};

% Footer line(s)
footer = {''};

% Create table content
ranking = {};
if exist(handles.datafile, 'file')
    
    % Load results from MAT-file
    %   results is a structure with 1 field: 
    %       - TeamsData: variable of type table, each line is a recorded
    %           run and 4 columns: 
    %               * Timestamp (matlab numeric date format)
    %               * Team (name of team)
    %               * Time (in seconds, time to visit sites)
    %               * Sites (Number of sites that were visited)
    %
    results = load(handles.datafile);
    
    % Get team list
    teams = get(handles.PmTeams, 'String');
    
    % Remove results that does not correspond to team associated with this
    % UI. Results are not removed from the datafile, they are not displayed
    % If you want to display results for all teams in MAT-file, discarding
    % content of menu, you can comment or remove this line
    %
    results.TeamsData(~ismember(results.TeamsData{:,'Team'},teams),:) = [];
    
    ranking_data = LocalCalculateRanking(results.TeamsData);
    
    % Loop on all teams to store and display results
    % For each team (each iteration of loop), use LocalFormatColumns to
    % format string that will be displayed on the line.
    % Information on line are (in order): team name, time in seconds to
    % visit sites, number of visited sites
    %
    ranking = cell(size(ranking_data,1),1);
    for i_team = 1:size(ranking_data,1)
        ranking{i_team} = LocalFormatColumns(COLUMN_WIDTH, ...
            char(ranking_data{i_team,'Team'}), ...
            num2str(ranking_data{i_team,'Time'}), ...
            num2str(ranking_data{i_team,'Sites'}));
    end
    
end

% Create complete list content by concatenate header, ranking and footer
content = [header;ranking;footer];

% Update graphical object (listbox)
set(handles.LtRanking, ...
    'String',   content, ...
    'Value',    length(content))

function [ranking] = LocalCalculateRanking(results)

% Sort results using 3 columns (in order)
    %   - Sites (Descending): Best result is associated with the maximum
    %                           sites visited
    %   - Time (Ascending): For the same number of visited sites, the
    %                           faster is better
    %   - Timestamp (Ascending): In 99% of time, first 2 criterion are
    %                           enough to sort results But in the case of 2
    %                           results are identical (number of sites and
    %                           time), first is better
    %
    results.TeamsData = sortrows(results, [-4 3 1]);
    
    % ranking is the variable that contains the results that will be
    % displayed
    % ranking is a cell array with 1 column and as many rows as different
    % teams represented in results
    % First step is to extract list of teams in a separate variable and 
    % then preallocate memory for ranking variable
    % Using the 'stable' option for UNIQUE ensure that teams are not
    % reodered, we don't need the team names but the index of row in table
    %
    [~,team_idx] = unique(results.TeamsData{:,'Team'},'stable');    
    ranking = results.TeamsData(team_idx,:);

function [str] = LocalFormatColumns(column_width,varargin)

% Find string that are too long or too short
too_long = cellfun(@length,varargin)>column_width;
too_short = cellfun(@length,varargin)<column_width;

% Troncate too long strings
varargin(too_long) = cellfun(@(x) x(1:column_width), varargin(too_long), 'UniformOutput', false);

% Add blank at the end of the too short string
varargin(too_short) = cellfun(@(x) [x repmat(' ',1,column_width-length(x))], varargin(too_short), 'UniformOutput', false);

% Create string by concatenate inputs (of the same size)
str = sprintf('%s',varargin{:});

function LocalWarning(handles,varargin)

% Display warning if corresponding flag is set to TRUE
if handles.display_warnings
    warning(varargin{:})
end
