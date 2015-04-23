function varargout = judge_central(varargin)
% JUDGE_CENTRAL MATLAB code for judge_central.fig
%      JUDGE_CENTRAL, by itself, creates a new JUDGE_CENTRAL or raises the existing
%      singleton*.
%
%      H = JUDGE_CENTRAL returns the handle to a new JUDGE_CENTRAL or the handle to
%      the existing singleton*.
%
%      JUDGE_CENTRAL('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in JUDGE_CENTRAL.M with the given input arguments.
%
%      JUDGE_CENTRAL('Property','Value',...) creates a new JUDGE_CENTRAL or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before judge_central_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to judge_central_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help judge_central

% Last Modified by GUIDE v2.5 16-Jun-2014 17:57:19

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
    'gui_Singleton',  gui_Singleton, ...
    'gui_OpeningFcn', @judge_central_OpeningFcn, ...
    'gui_OutputFcn',  @judge_central_OutputFcn, ...
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


% --- Executes just before judge_central is made visible.
function judge_central_OpeningFcn(hObject, ~, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to judge_central (see VARARGIN)

% Get current application directory
root_dir = fileparts(mfilename('fullpath'));

% Check if a background image exists and can be displayed
if exist(fullfile(root_dir,'background.jpg'),'file')
    image(imread(fullfile(root_dir,'background.jpg')),'Parent', handles.AxBackground)
elseif any(strcmpi(varargin,'Background')) && ...
        numel(varargin) > find(strcmpi(varargin,'Background')) && ...
        exist(varargin{find(strcmpi(varargin,'Background'))+1},'file')
    image(imread(varargin{find(strcmpi(varargin,'Background'))+1}),'Parent', handles.AxBackground)
end

% Check if a background image exists and can be displayed
if exist(fullfile(root_dir,'background_ranking.jpg'),'file')
    image(imread(fullfile(root_dir,'background_ranking.jpg')),'Parent', handles.AxRanking)
elseif any(strcmpi(varargin,'BackgroundRanking')) && ...
        numel(varargin) > find(strcmpi(varargin,'BackgroundRanking')) && ...
        exist(varargin{find(strcmpi(varargin,'BackgroundRanking'))+1},'file')
    image(imread(varargin{find(strcmpi(varargin,'BackgroundRanking'))+1}),'Parent', handles.AxRanking)
end

% Check if a directory name is set for pictures that must be displayed
% Save directory name in UserData property of corresponding axe
if any(strcmpi(varargin,'PictureDirectory')) && ...
        numel(varargin) > find(strcmpi(varargin,'PictureDirectory')) && ...
        isdir(varargin{find(strcmpi(varargin,'PictureDirectory'))+1})
    set(handles.AxPictures, 'UserData', varargin{find(strcmpi(varargin,'PictureDirectory'))+1})
end

% Check if list of result files is set
% Save directory name in UserData property of corresponding axe
if any(strcmpi(varargin,'GlobalResultFile')) && ...
        numel(varargin) > find(strcmpi(varargin,'GlobalResultFile'))
    rank_files.global = varargin{find(strcmpi(varargin,'GlobalResultFile'))+1};
else
    rank_files.global = fullfile(root_dir,'MakerFaireTeamResults');
end

set(handles.AxRanking, 'UserData', rank_files)

% Check if number of teams is set
if any(strcmpi(varargin,'NumberOfTeams')) && ...
        numel(varargin) > find(strcmpi(varargin,'NumberOfTeams')) && ...
        isscalar(varargin{find(strcmpi(varargin,'NumberOfTeams'))+1})
    
    nteam = varargin{find(strcmpi(varargin,'NumberOfTeams'))+1};
    
    if ischar(nteam) && ~isnan(str2double(nteam))
        nteam = str2double(nteam);
    else
        nteam = 12;
        warning('JudgeCentral:NumberOfTeams', ...
            'Invalid setting for number of teams, use defaut value (12)')
    end
        
    handles.TxRank = LocalCreateRank(handles.AxRanking, nteam);
else
    handles.TxRank = LocalCreateRank(handles.AxRanking,12); % Default number of teams is 12
end

% Change window title
if any(strcmpi(varargin,'WindowTitle')) && ...
        numel(varargin) > find(strcmpi(varargin,'WindowTitle'))
    set(handles.FgCentralJudge, 'Name', varargin{find(strcmpi(varargin,'WindowTitle'))+1})
end

if any(strcmpi(varargin,'CounterTime')) && ...
        numel(varargin) > find(strcmpi(varargin,'CounterTime'))
            
    counter_time = varargin{find(strcmpi(varargin,'CounterTime'))+1};
    
    if ischar(counter_time) && ~isnan(str2double(counter_time))
        counter_time = str2double(counter_time) * 60;
    else
        counter_time = 10*60;
        warning('JudgeCentral:CounterTime', ...
            'Invalid setting for counter time, use defaut value (10 min)')
    end
    
else
    counter_time = 10 * 60;
end

% Create digital clock
handles.DcCounter = ClockCounter(handles.AxCountDown);
handles.DcCounter.CurrentTime = counter_time;

% Create a timer to update clock
handles.TmCounter = timer( ...
    'TimerFcn',         @(obj,evt) LocalUpdateCounter(obj,handles), ...
    'Period',           0.5, ...
    'ExecutionMode',    'fixedDelay', ...
    'UserData',         counter_time);

% Create a timer to update ranking
handles.TmUpdateRanking = timer( ...
    'TimerFcn',             @(obj,evt) LocalUpdateRanking(handles), ...
    'Period',               20, ...
    'ExecutionMode',        'fixedDelay');
start(handles.TmUpdateRanking)

if ~isempty(get(handles.AxPictures, 'UserData'))
    
    % Create a timer to update picture
    handles.TmUpdatePicture = timer( ...
        'TimerFcn',             @(obj,evt) LocalUpdatePicture(handles), ...
        'Period',               10, ...
        'ExecutionMode',        'fixedDelay');
    start(handles.TmUpdatePicture)
    
else
    
    handles.TmUpdatePicture = [];
    
    %xlim = get(handles.AxRanking, 'XLim');
    %ylim = get(handles.AxRanking, 'YLim');
    
    %set(handles.FgCentralJudge, 'Position', [0 0 diff(xlim)-10 diff(ylim)-10])
    
end

set(handles.PbStop, 'Enable', 'off')

guidata(hObject,handles)

movegui(handles.FgCentralJudge,'center')

% --- Outputs from this function are returned to the command line.
function judge_central_OutputFcn(~, ~, ~)
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

function PbStart_Callback(hObject, ~, handles) %#ok<DEFNU>

% Start timer
start(handles.TmCounter)

set(hObject, 'Enable', 'off')
set(handles.PbReset, 'Enable', 'off')
set(handles.PbStop, 'Enable', 'on')

function PbReset_Callback(~, ~, handles) %#ok<DEFNU>

LocalUpdateCounter(handles.TmCounter,handles,'reset')
set(handles.PbStart, 'Enable', 'on', 'String', 'Start')

function PbStop_Callback(hObject, ~, handles) %#ok<DEFNU>

% Stop timer
stop(handles.TmCounter)

LocalUpdateCounter(handles.TmCounter,handles,'stop')

set(hObject, 'Enable', 'off')
set(handles.PbStart, 'Enable', 'on', 'String', 'Continue')
set(handles.PbReset, 'Enable', 'on')

function FgCentralJudge_CloseRequestFcn(hObject, ~, handles) %#ok<DEFNU>

% Stop and delete timer that update ranking
if ~isempty(handles.TmUpdateRanking)
    stop(handles.TmUpdateRanking)
    delete(handles.TmUpdateRanking)
end

% Stop and delete timer that update picture
if ~isempty(handles.TmUpdatePicture)
    stop(handles.TmUpdatePicture)
    delete(handles.TmUpdatePicture)
end

% Stop and delete timer that update counter
if ~isempty(handles.TmCounter)
    stop(handles.TmCounter)
    delete(handles.TmCounter)
end

% Hint: delete(hObject) closes the figure
delete(hObject);

function obj = LocalCreateRank(axHdl,n)

% Set axis limits
xlim = get(axHdl,'XLim');
ylim = get(axHdl,'YLim');

% Calculate Y position for each elements
x_pos = cumsum(diff(xlim) * [0.09 0.32 0.37 0.17 0.13]);
y_pos = linspace(ylim(1)+0.18*diff(ylim),ylim(2)-0.3*diff(ylim),n+2);

str = {'RANK','TEAM','TIME','SITE'};
for i = 1:length(str)
    text(x_pos(i),y_pos(2),str{i}, ...
        'Parent',               axHdl, ...
        'FontName',             'Arial', ...
        'FontUnit',             'points', ...
        'FontSize',             14, ...
        'HorizontalAlignment',  'center', ...
        'FontWeight',           'bold', ...
        'Color',                [1 0 0]);
end

% Preallocate obj array
obj = zeros(n,3);
for i = 1:n
    for j = 1:length(str)
        obj(i,j) = text(x_pos(j),y_pos(i+2),'', ...
            'Parent',               axHdl, ...
            'FontName',             'Arial', ...
            'FontUnit',             'points', ...
            'FontSize',             12, ...
            'HorizontalAlignment',  'center');
    end
end

function LocalUpdateRanking(handles)

% Get name of files to load to update ranking
rank_files = get(handles.AxRanking, 'UserData');
file_list = {rank_files.global}; 

% Check file that exist
existing_files = cellfun(@(x) exist(x,'file'), file_list);

% Load data from each existing files
results = cellfun(@load, file_list(existing_files~=0),'UniformOutput',false);
if isempty(results);return; end

% Concatenate tables
TeamsData = [results{1}.TeamsData];
for i_res = 2:length(results)
    TeamsData = [TeamsData; results{i_res}.TeamsData]; %#ok<AGROW>
end

% Extract best score for each team (sorted)
TeamsData = sortrows(TeamsData,{'Sites','Time','Timestamp'}, {'descend','ascend','ascend'});
[~,idx] = unique(TeamsData{:,'Team'},'stable');
TeamsData = TeamsData(idx,:);

for i_team = 1:min(size(TeamsData,1),size(handles.TxRank,1))
    set(handles.TxRank(i_team,1), 'String', num2str(i_team))
    set(handles.TxRank(i_team,2), 'String', TeamsData{i_team,'Team'})
    set(handles.TxRank(i_team,3), 'String', sprintf('%.2f',TeamsData{i_team,'Time'}))
    set(handles.TxRank(i_team,4), 'String', TeamsData{i_team,'Sites'})
end

% Save global results in a MAT-file
save(rank_files.global, 'TeamsData')

function LocalUpdatePicture(handles)

persistent i_pict;
if isempty(i_pict);i_pict = 0; end

picture_dir = get(handles.AxPictures, 'UserData');

if ~isempty(picture_dir) && isdir(picture_dir)
    
    picture_files = dir(picture_dir);
    picture_files([picture_files.isdir]==1) = [];
    
    if i_pict == numel(picture_files)
        i_pict = 1;
    else
        i_pict = i_pict+1;
    end
    
    try %#ok<TRYNC> % If fail, file is not an image
        
        img = imread(fullfile(picture_dir,picture_files(i_pict).name));
        
        if isempty(get(handles.AxPictures,'Children'))
            image(img, 'Parent', handles.AxPictures)
        else
            set(get(handles.AxPictures,'Children'), 'CData', img)
        end
        
    end
    
end

function LocalUpdateCounter(hObject,handles,varargin)

persistent elapsed_time;

persistent clock_hdl;
if isempty(clock_hdl)
    clock_hdl = tic;
    
    if isempty(elapsed_time)
        handles.DcCounter.newTeam();
    end
    
end

if isempty(elapsed_time); elapsed_time = 0; end

if any(strcmpi(varargin,'reset'))
    
    clock_hdl = [];
    elapsed_time = 0;
    handles.DcCounter.CurrentTime = get(hObject,'UserData');
    handles.DcCounter.newTeam();
    
elseif any(strcmpi(varargin,'stop'))  
    
    elapsed_time = elapsed_time + toc(clock_hdl);
    clock_hdl = [];
    
else
    
    remaining_time = get(hObject,'UserData') - toc(clock_hdl) - elapsed_time;
    
    if remaining_time <= 0
        
        handles.DcCounter.CurrentTime = get(hObject,'UserData');
        handles.DcCounter.setMode('normal')
        clock_hdl = tic;
        elapsed_time = 0;
        handles.DcCounter.newTeam();
        
    elseif remaining_time < 10%60
        
        handles.DcCounter.CurrentTime = remaining_time;
        handles.DcCounter.setMode('warning')
        
    else
        
        handles.DcCounter.CurrentTime = remaining_time;
        handles.DcCounter.setMode('normal')
        
    end
    
end
