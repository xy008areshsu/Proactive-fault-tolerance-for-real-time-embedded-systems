function varargout = judge_tuning_interface(varargin)
% JUDGE_TUNING_INTERFACE MATLAB code for judge_tuning_interface.fig
%      JUDGE_TUNING_INTERFACE, by itself, creates a new JUDGE_TUNING_INTERFACE or raises the existing
%      singleton*.
%
%      H = JUDGE_TUNING_INTERFACE returns the handle to a new JUDGE_TUNING_INTERFACE or the handle to
%      the existing singleton*.
%
%      JUDGE_TUNING_INTERFACE('CALLBACK',hObject,eventData,handles,...) calls the local
%      function named CALLBACK in JUDGE_TUNING_INTERFACE.M with the given input arguments.
%
%      JUDGE_TUNING_INTERFACE('Property','Value',...) creates a new JUDGE_TUNING_INTERFACE or raises the
%      existing singleton*.  Starting from the left, property value pairs are
%      applied to the GUI before judge_tuning_interface_OpeningFcn gets called.  An
%      unrecognized property name or invalid value makes property application
%      stop.  All inputs are passed to judge_tuning_interface_OpeningFcn via varargin.
%
%      *See GUI Options on GUIDE's Tools menu.  Choose "GUI allows only one
%      instance to run (singleton)".
%
% See also: GUIDE, GUIDATA, GUIHANDLES

% Edit the above text to modify the response to help judge_tuning_interface

% Last Modified by GUIDE v2.5 20-Jun-2014 15:22:32

% Begin initialization code - DO NOT EDIT
gui_Singleton = 1;
gui_State = struct('gui_Name',       mfilename, ...
                   'gui_Singleton',  gui_Singleton, ...
                   'gui_OpeningFcn', @judge_tuning_interface_OpeningFcn, ...
                   'gui_OutputFcn',  @judge_tuning_interface_OutputFcn, ...
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


% --- Executes just before judge_tuning_interface is made visible.
function judge_tuning_interface_OpeningFcn(hObject, eventdata, handles, varargin)
% This function has no output args, see OutputFcn.
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% varargin   command line arguments to judge_tuning_interface (see VARARGIN)

% Choose default command line output for judge_tuning_interface
handles.output = hObject;

% Set interface to initial state and update handles
resetInterface(handles);




% --- Outputs from this function are returned to the command line.
function varargout = judge_tuning_interface_OutputFcn(hObject, eventdata, handles) 
% varargout  cell array for returning output args (see VARARGOUT);
% hObject    handle to figure
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Get default command line output from handles structure
varargout{1} = handles.output;


% --- Executes on button press in button_acquire_targets.
function button_acquire_targets_Callback(hObject, eventdata, handles)
% hObject    handle to button_acquire_targets (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Getting video object
videoObj = getappdata(handles.main_interface,'videoObj');

% Getting video frame
for iframe = 1 : 50
    frame = step(videoObj);
end
setappdata(handles.main_interface,'currentFrame',frame);

% Drawing binary image with default values
drawFrameGreenBW(handles);

% Turning off button; turning on sliders and validate button
set(handles.button_acquire_targets,'enable','off');
set(handles.slider_green_level,'enable','on');
set(handles.slider_noise_max_size,'enable','on');
set(handles.slider_max_eccentricity,'enable','on');
set(handles.button_validate_targets,'enable','on');



% --- Executes on button press in button_acquire_robots.
function button_acquire_robots_Callback(hObject, eventdata, handles)
% hObject    handle to button_acquire_robots (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Getting video object
videoObj = getappdata(handles.main_interface,'videoObj');

% Getting video frame
for iframe = 1 : 50
    frame = step(videoObj);
end
setappdata(handles.main_interface,'currentFrame',frame);

% Drawing binary image with default values
drawFrameBlueBW(handles);

% Turning off button; turning on sliders and validate button
set(handles.button_acquire_robots,'enable','off');
set(handles.slider_hhighthresh,'enable','on');
set(handles.slider_hlowthresh,'enable','on');
set(handles.slider_sthresh,'enable','on');
set(handles.slider_vthresh,'enable','on');
set(handles.slider_noise_max_size_blue,'enable','on');
set(handles.button_validate_robots,'enable','on');


% --- Executes on button press in button_calibrate.
function button_calibrate_Callback(hObject, eventdata, handles)
% hObject    handle to button_calibrate (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Running calibration
calibrateJudge(handles);

% --- Executes on button press in button_validate_targets.
function button_validate_targets_Callback(hObject, eventdata, handles)
% hObject    handle to button_validate_targets (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Data already stored in memory, only activating other buttons
set(handles.button_acquire_robots,'enable','on');
set(handles.slider_green_level,'enable','off');
set(handles.slider_noise_max_size,'enable','off');
set(handles.slider_max_eccentricity,'enable','off');
set(handles.button_validate_targets,'enable','off');

% % Showing final values on text laels
% greenParameters = getappdata(handles.main_interface,'greenParameters');
% set(handles.text_slider_green_level,'String',[get(handles.text_slider_green_level,'String'),' = ', num2str(greenParameters.GreenLevel)]);
% set(handles.text_slider_max_eccentricity,'String',[get(handles.text_slider_max_eccentricity,'String'),' = ', num2str(greenParameters.MaxEccentricity)]);
% set(handles.text_slider_noise_max_size,'String',[get(handles.text_slider_noise_max_size,'String'),' = ', num2str(greenParameters.NoiseMaxSize)]);

% --- Executes on button press in button_validate_robots.
function button_validate_robots_Callback(hObject, eventdata, handles)
% hObject    handle to button_validate_robots (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Data already stored in memory, only activating other buttons
set(handles.button_acquire_robots,'enable','off');
set(handles.slider_hhighthresh,'enable','off');
set(handles.slider_hlowthresh,'enable','off');
set(handles.slider_vthresh,'enable','off');
set(handles.slider_sthresh,'enable','off');
set(handles.button_validate_robots,'enable','off');
set(handles.button_calibrate,'enable','on');

% % Showing final values on text labels
% blueParameters = getappdata(handles.main_interface,'blueParameters');
% set(handles.text_slider_hhighthresh,'String',[get(handles.text_slider_hhighthresh,'String'),' = ', num2str(blueParameters.HHighThresh)]);
% set(handles.text_slider_hlowthresh,'String',[get(handles.text_slider_hlowthresh,'String'),' = ', num2str(blueParameters.HLowThresh)]);
% set(handles.text_slider_vthresh,'String',[get(handles.text_slider_vthresh,'String'),' = ', num2str(blueParameters.VThresh)]);
% set(handles.text_slider_sthresh,'String',[get(handles.text_slider_sthresh,'String'),' = ', num2str(blueParameters.SThresh)]);



% --- Executes on slider movement.
function slider_green_level_Callback(hObject, eventdata, handles)
% hObject    handle to slider_green_level (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider

% Retrieving greenParameters
greenParameters = getappdata(handles.main_interface, 'greenParameters');

% Updating parameters
greenParameters.GreenLevel = get(hObject,'Value');

% Updating data storage and visualization
setappdata(handles.main_interface,'greenParameters',greenParameters);
drawFrameGreenBW(handles);
set(handles.text_slider_green_level, 'String', ['Green level = ', num2str(greenParameters.GreenLevel)]);



% --- Executes during object creation, after setting all properties.
function slider_green_level_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider_green_level (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end
set(hObject, 'sliderstep', [5e-4, 1e-2]);


% --- Executes on slider movement.
function slider_max_eccentricity_Callback(hObject, eventdata, handles)
% hObject    handle to slider_max_eccentricity (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider

% Retrieving greenParameters
greenParameters = getappdata(handles.main_interface, 'greenParameters');

% Updating parameters
greenParameters.MaxEccentricity = get(hObject,'Value');

% Updating data storage and visualization
setappdata(handles.main_interface,'greenParameters',greenParameters);
drawFrameGreenBW(handles);
set(handles.text_slider_max_eccentricity, 'String', ['Max eccentricity = ', num2str(greenParameters.MaxEccentricity)]);


% --- Executes during object creation, after setting all properties.
function slider_max_eccentricity_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider_max_eccentricity (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end
set(hObject, 'sliderstep', [5e-4, 1e-2]);


% --- Executes on slider movement.
function slider_noise_max_size_Callback(hObject, eventdata, handles)
% hObject    handle to slider_noise_max_size (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider

% Retrieving greenParameters
greenParameters = getappdata(handles.main_interface, 'greenParameters');

% Updating parameters
value = get(hObject,'Value');
greenParameters.NoiseMaxSize = round(value * greenParameters.NoiseMaxReasonable);

% Updating data storage and visualization
setappdata(handles.main_interface,'greenParameters',greenParameters);
drawFrameGreenBW(handles);
set(handles.text_slider_noise_max_size, 'String', ['Noise max size = ', num2str(greenParameters.NoiseMaxSize)]);



% --- Executes during object creation, after setting all properties.
function slider_noise_max_size_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider_noise_max_size (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end
set(hObject, 'sliderstep', [5e-4, 1e-2]);


% --- Executes on slider movement.
function slider_hhighthresh_Callback(hObject, eventdata, handles)
% hObject    handle to slider_hhighthresh (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider

% Retrieving parameters
blueParameters = getappdata(handles.main_interface, 'blueParameters');

% Updating parameters
blueParameters.HHighThresh = get(hObject,'Value');

% Updating data storage and visualization
setappdata(handles.main_interface,'blueParameters',blueParameters);
drawFrameBlueBW(handles);
set(handles.text_slider_hhighthresh, 'String', ['HHighThresh = ', num2str(blueParameters.HHighThresh)]);


% --- Executes during object creation, after setting all properties.
function slider_hhighthresh_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider_hhighthresh (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end
set(hObject, 'sliderstep', [5e-4, 1e-2]);


% --- Executes on slider movement.
function slider_hlowthresh_Callback(hObject, eventdata, handles)
% hObject    handle to slider_hlowthresh (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider

% Retrieving parameters
blueParameters = getappdata(handles.main_interface, 'blueParameters');

% Updating parameters
blueParameters.HLowThresh = get(hObject,'Value');

% Updating data storage and visualization
setappdata(handles.main_interface,'blueParameters',blueParameters);
drawFrameBlueBW(handles);
set(handles.text_slider_hlowthresh, 'String', ['HLowThresh = ', num2str(blueParameters.HLowThresh)]);

% --- Executes during object creation, after setting all properties.
function slider_hlowthresh_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider_hlowthresh (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end
set(hObject, 'sliderstep', [5e-4, 1e-2]);


% --- Executes on slider movement.
function slider_vthresh_Callback(hObject, eventdata, handles)
% hObject    handle to slider_vthresh (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider

% Retrieving parameters
blueParameters = getappdata(handles.main_interface, 'blueParameters');

% Updating parameters
blueParameters.VThresh = get(hObject,'Value');

% Updating data storage and visualization
setappdata(handles.main_interface,'blueParameters',blueParameters);
drawFrameBlueBW(handles);
set(handles.text_slider_vthresh, 'String', ['VThresh = ', num2str(blueParameters.VThresh)]);

% --- Executes during object creation, after setting all properties.
function slider_vthresh_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider_vthresh (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end
set(hObject, 'sliderstep', [5e-4, 1e-2]);


% --- Executes on slider movement.
function slider_sthresh_Callback(hObject, eventdata, handles)
% hObject    handle to slider_sthresh (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider

% Retrieving parameters
blueParameters = getappdata(handles.main_interface, 'blueParameters');

% Updating parameters
blueParameters.SThresh = get(hObject,'Value');

% Updating data storage and visualization
setappdata(handles.main_interface,'blueParameters',blueParameters);
drawFrameBlueBW(handles);
set(handles.text_slider_sthresh, 'String', ['SThresh = ', num2str(blueParameters.SThresh)]);

% --- Executes during object creation, after setting all properties.
function slider_sthresh_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider_sthresh (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end
set(hObject, 'sliderstep', [5e-4, 1e-2]);


% --- Executes on button press in button_check_camera.
function button_check_camera_Callback(hObject, eventdata, handles)
% hObject    handle to button_check_camera (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Opening camera connection
cols = getappdata(handles.main_interface,'RESOLUTION_COLS');
rows = getappdata(handles.main_interface,'RESOLUTION_ROWS');
try
    imaqreset
    videoObj = imaq.VideoDevice('winvideo', 1, ['MJPG_',num2str(cols),'x',num2str(rows)]);
    videoObj.DeviceProperties.FocusMode = 'manual';
catch
    error('detection_initialization:noCameraConnected', ...
        'Please check your camera connection and run imaqhwinfo');
end
setappdata(handles.main_interface,'videoObj',videoObj);

% Giving 50 frames to the camera to settle, and showing on a new figure
for iframe = 1 : 50
    frame = step(videoObj);
end
% 
% Changing string on the button
set(hObject,'String','Camera OK!');
set(handles.button_acquire_targets,'enable','on');
set(handles.button_check_camera,'enable','off');
set(handles.button_save_data,'enable','on');

% --- Executes on button press in button_save_data.
function button_save_data_Callback(hObject, eventdata, handles)
% hObject    handle to button_save_data (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Retrieving parameters
greenParameters = getappdata(handles.main_interface,'greenParameters');
blueParameters = getappdata(handles.main_interface,'blueParameters');
calibrationMatrices = getappdata(handles.main_interface,'calibrationMatrices');

% Appending data to file (if not updated, saves the default values)
parameters_data.targets = greenParameters;
parameters_data.robots = blueParameters; %#ok<STRNU>
calibration_data.matrices = calibrationMatrices; %#ok<STRNU>

% % Getting file name from dialog box
% [FileName, FilePath] = uiputfile('../*.mat');

FileName = 'judge_calibration.mat';
FilePath = fileparts(fileparts(mfilename('fullpath')));
if exist(fullfile(FilePath,FileName),'file')
    save(fullfile(FilePath,FileName),'parameters_data','calibration_data','-append');
else
    save(fullfile(FilePath,FileName),'parameters_data','calibration_data');
end


function resetInterface(handles)

% Specifying application data and their default values
setappdata(handles.main_interface,'currentFrame',zeros(800,600,'double'));
setappdata(handles.main_interface,'RESOLUTION_COLS',800);
setappdata(handles.main_interface,'RESOLUTION_ROWS',600);
setappdata(handles.main_interface,'videoObj',[]);
setappdata(handles.main_interface,'robot_stat',[]);
setappdata(handles.main_interface,'target_stat',[]);

% If judge calibration data exists than load, otherwise set defaults
FileName = 'judge_calibration.mat';
FilePath = fileparts(fileparts(mfilename('fullpath')));
if exist(fullfile(FilePath,FileName),'file')
    load(fullfile(FilePath,FileName),'parameters_data','calibration_data');
    
    greenParameters = parameters_data.targets;
    blueParameters = parameters_data.robots;
    calibrationMatrices = calibration_data.matrices;
    
    setappdata(handles.main_interface,'greenParameters',greenParameters);
    setappdata(handles.main_interface,'blueParameters',blueParameters);
    setappdata(handles.main_interface,'calibrationMatrices',calibrationMatrices);
else
    % Setting default values in appdata
    greenParameters.GreenLevel = 0.1;
    greenParameters.NoiseMaxSize = 100;
    greenParameters.MaxEccentricity = 0.7;
    greenParameters.NoiseMaxReasonable = 5000;
    setappdata(handles.main_interface,'greenParameters',greenParameters);
    
    blueParameters.HHighThresh = 0.7;
    blueParameters.HLowThresh = 0.5;
    blueParameters.SThresh = 0.56;
    blueParameters.VThresh = 0.5;
    blueParameters.NoiseMaxSize = 100;
    blueParameters.NoiseMaxReasonable = 5000;
    setappdata(handles.main_interface,'blueParameters',blueParameters);
    
    calibrationMatrices.world2target = [244.9442  -13.3065  -0.0111;
        13.0302   248.0628   0.0040;
        132.1534   60.1753   1.000];
    calibrationMatrices.robot2world = [0.0036167   0.0001708   0.0000354;
        -0.0002258  0.0035380   -0.0000576;
        -0.3405429   -0.1453514   0.9986902];
    setappdata(handles.main_interface,'calibrationMatrices',calibrationMatrices);
    
end

setSliders(handles);

% Default visualization
hold(handles.axes_green,'on');
hold(handles.axes_blue,'on');
handles.imageFrameGreenBW = imshow(zeros(800,600,'double'),'Parent',handles.axes_green);
handles.targetPoints = plot(NaN, NaN, 'r+','markersize',4,'Parent',handles.axes_green);
handles.imageFrameBlueBW = imshow(zeros(800,600,'double'),'Parent',handles.axes_blue);
handles.robotPoints = plot(NaN, NaN, 'r+','markersize',4,'Parent',handles.axes_blue);

% Turning off all buttons but the check camera connection
set(handles.button_calibrate,'enable','off');
set(handles.button_acquire_targets,'enable','off');
set(handles.button_validate_targets,'enable','off');
set(handles.button_acquire_robots,'enable','off');
set(handles.button_validate_robots,'enable','off');
set(handles.slider_green_level,'enable','off');
set(handles.slider_max_eccentricity,'enable','off');
set(handles.slider_noise_max_size,'enable','off');
set(handles.slider_hhighthresh,'enable','off');
set(handles.slider_hlowthresh,'enable','off');
set(handles.slider_sthresh,'enable','off');
set(handles.slider_vthresh,'enable','off');
set(handles.slider_noise_max_size_blue,'enable','off');
set(handles.button_save_data,'enable','off');

% Update handles structure
guidata(handles.main_interface,handles);


function drawFrameGreenBW(handles)

% Getting actual green parameters
greenParameters = getappdata(handles.main_interface,'greenParameters');
frame = getappdata(handles.main_interface,'currentFrame');

% Define and cleanup green image
frame = im2double(frame);
frameGreen = frame(:,:,2) - (frame(:,:,1) + frame(:,:,3))/2;
frameGreenBW = frameGreen>greenParameters.GreenLevel;
frameGreenBW = bwareaopen(frameGreenBW, greenParameters.NoiseMaxSize);
frameGreenBW = imfill(frameGreenBW, 'holes');
frameGreenBW = imclearborder(frameGreenBW);

% Plotting BW frame
set(handles.imageFrameGreenBW,'CData',frameGreenBW);

% Counting sites and plotting
sites_stat = regionprops(frameGreenBW, {'Area','Centroid','Eccentricity'});
sites_stat = sites_stat([sites_stat.Eccentricity]<greenParameters.MaxEccentricity);
SitePositions = reshape([sites_stat.Centroid],2,[])';
set(handles.targetPoints,'xdata',SitePositions(:,1),'ydata',SitePositions(:,2));

% Counting sites
NSites = numel(sites_stat);
set(handles.text_green,'String',['Green N = ',num2str(NSites)]);

% Saving current site positions in app data
setappdata(handles.main_interface,'target_stat',sites_stat);



function drawFrameBlueBW(handles)

% Getting actual parameters
blueParameters = getappdata(handles.main_interface,'blueParameters');
greenParameters = getappdata(handles.main_interface,'greenParameters');
frame = getappdata(handles.main_interface,'currentFrame');

% HSV Thresholding
frameHSV = rgb2hsv(frame);   % img contains the camera picture
Hplane = frameHSV(:,:,1);
Splane = frameHSV(:,:,2);
Vplane = frameHSV(:,:,3);

robot_detection = (...
    Hplane > blueParameters.HLowThresh & ...
    Hplane < blueParameters.HHighThresh & ...
    Splane > blueParameters.SThresh & ...
    Vplane > blueParameters.VThresh);

robot_detection = bwareaopen(robot_detection, blueParameters.NoiseMaxSize);
robot_detection = imfill(robot_detection,'holes');

% Plotting BW frame
set(handles.imageFrameBlueBW,'CData',robot_detection);

% Detecting robots and finding positions
robot_stat = regionprops(robot_detection, {'Area', 'Centroid'});
RobotPositions = reshape([robot_stat.Centroid],2,[])';
set(handles.robotPoints,'xdata',RobotPositions(:,1),'ydata',RobotPositions(:,2));

% Counting robots
NRobots = numel(robot_stat);
set(handles.text_blue,'String',['Blue N = ',num2str(NRobots)]);

% Saving current robot positions in app data
setappdata(handles.main_interface,'robot_stat',robot_stat);

function setSliders(handles)

% Retrieving data from memory
greenParameters = getappdata(handles.main_interface, 'greenParameters');
blueParameters = getappdata(handles.main_interface, 'blueParameters');

% Setting slider positions
set(handles.slider_green_level,'value',greenParameters.GreenLevel);
set(handles.slider_noise_max_size,'value',greenParameters.NoiseMaxSize/greenParameters.NoiseMaxReasonable);
set(handles.slider_max_eccentricity,'value',greenParameters.MaxEccentricity);

set(handles.slider_hhighthresh,'value',blueParameters.HHighThresh);
set(handles.slider_hlowthresh,'value',blueParameters.HLowThresh);
set(handles.slider_sthresh,'value',blueParameters.SThresh);
set(handles.slider_vthresh,'value',blueParameters.VThresh);
set(handles.slider_noise_max_size_blue,'value',blueParameters.NoiseMaxSize/blueParameters.NoiseMaxReasonable);

% Setting corresponding text
set(handles.text_slider_green_level, 'String', ['Green level = ', num2str(greenParameters.GreenLevel)]);
set(handles.text_slider_noise_max_size, 'String', ['Noise max size = ', num2str(greenParameters.NoiseMaxSize)]);
set(handles.text_slider_max_eccentricity, 'String', ['Max eccentricity = ', num2str(greenParameters.MaxEccentricity)]);

set(handles.text_slider_hhighthresh, 'String', ['HHighThresh = ', num2str(blueParameters.HHighThresh)]);
set(handles.text_slider_hlowthresh, 'String', ['HLowThresh = ', num2str(blueParameters.HLowThresh)]);
set(handles.text_slider_sthresh, 'String', ['SThresh = ', num2str(blueParameters.SThresh)]);
set(handles.text_slider_vthresh, 'String', ['VThresh = ', num2str(blueParameters.VThresh)]);
set(handles.text_slider_noise_max_size_blue, 'String', ['Noise max size = ', num2str(blueParameters.NoiseMaxSize)]);


function calibrateJudge(handles) 

% Getting parameters from app data
robot_stat = getappdata(handles.main_interface,'robot_stat');
target_stat = getappdata(handles.main_interface,'target_stat');
imageSize.numrows = getappdata(handles.main_interface,'RESOLUTION_ROWS');

%% 0/ Checks
numPointsToUse = 4;
if numel(robot_stat) ~= numPointsToUse
    errordlg('Exactly 4 robot points are expected.')
end

if numel(target_stat) ~= numPointsToUse
    errordlg('Exactly 4 target points are expected.')
end

result = inputdlg('The world positions should be 4 points on the corners of a square of 2m x 2m, is this correct [0/1]? ');
if result{1} == 0
    errordlg('A calibration pattern with 4 points on the corners of a square of 2m x 2m is expected.')
end

%% 1/ By default, the centroid returned by regionprops is in [x(>), y(v)],
%     corresponding to Centroid(1) and Centroid(2)
%     Change the convention to x(>), y(^)
centroids_robot = reshape([robot_stat.Centroid], 2, numPointsToUse)' ;
xi_robot = centroids_robot(:, 1);
yi_robot = imageSize.numrows - centroids_robot(:, 2);

centroids_target = reshape([target_stat.Centroid], 2, numPointsToUse)' ;
xi_target = centroids_target(:, 1);
yi_target = imageSize.numrows - centroids_target(:, 2);

%% 2/ Sort out the input data points into top-left / top-right / bottom-left / bottom-right
%
% robot : 
topPtsInds_robot = yi_robot > mean(yi_robot) ;
bottomPtsInds_robot = ~topPtsInds_robot;
leftPtsInds_robot = xi_robot < mean(xi_robot) ;
rightPtsInds_robot = ~leftPtsInds_robot ;

imagePoints_robot = [xi_robot(topPtsInds_robot & leftPtsInds_robot), yi_robot(topPtsInds_robot & leftPtsInds_robot) ;       % top left
    xi_robot(topPtsInds_robot & rightPtsInds_robot), yi_robot(topPtsInds_robot & rightPtsInds_robot) ;                      % top right
    xi_robot(bottomPtsInds_robot & leftPtsInds_robot), yi_robot(bottomPtsInds_robot & leftPtsInds_robot) ;                  % bottom left
    xi_robot( bottomPtsInds_robot & rightPtsInds_robot), yi_robot(bottomPtsInds_robot & rightPtsInds_robot)];               % bottom right

% target :
topPtsInds_target = yi_target > mean(yi_target) ;
bottomPtsInds_target = ~topPtsInds_target;
leftPtsInds_target = xi_target < mean(xi_target) ;
rightPtsInds_target = ~leftPtsInds_target ;

imagePoints_target = [xi_target(topPtsInds_target & leftPtsInds_target), yi_target(topPtsInds_target & leftPtsInds_target) ;      % top left
    xi_target(topPtsInds_target & rightPtsInds_target), yi_target(topPtsInds_target & rightPtsInds_target) ;                      % top right
    xi_target(bottomPtsInds_target & leftPtsInds_target), yi_target(bottomPtsInds_target & leftPtsInds_target) ;                  % bottom left
    xi_target( bottomPtsInds_target & rightPtsInds_target), yi_target(bottomPtsInds_target & rightPtsInds_target)];               % bottom right

%% 3/ Corresponding world points
worldPoints = [0,2 ;        % top-left  
            2,2 ;           % top-right
            0,0 ;           % bottom-left
            2,0 ];          % bottom-right

%% 4a/ do the calibration : projection of the robot's head plane to world plane
data_robot = [imagePoints_robot, worldPoints] ;
% mat_im2world = calc_im2world( data_robot ) ; % code snippet from
% fitgeotrans for codegen - but we don't need it here. Use the line below.
T_world2im_robot = fitgeotrans(data_robot(:,3:4), data_robot(:,1:2), 'projective');
mat_im2world = inv(T_world2im_robot.T);

% 4b/ projection of the world plane to target/image plane
data_target = [imagePoints_target, worldPoints];
T_world2im_target = fitgeotrans(data_target(:,3:4), data_target(:,1:2), 'projective');
mat_world2im = T_world2im_target.T;

% Saving result in app data
calibrationMatrices.world2target = mat_world2im;
calibrationMatrices.robot2world = mat_im2world;
setappdata(handles.main_interface,'calibrationMatrices',calibrationMatrices);


% --- Executes on slider movement.
function slider_noise_max_size_blue_Callback(hObject, eventdata, handles)
% hObject    handle to slider_noise_max_size_blue (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)

% Hints: get(hObject,'Value') returns position of slider
%        get(hObject,'Min') and get(hObject,'Max') to determine range of slider

% Retrieving blueParameters
blueParameters = getappdata(handles.main_interface, 'blueParameters');

% Updating parameters
value = get(hObject,'Value');
blueParameters.NoiseMaxSize = round(value * blueParameters.NoiseMaxReasonable);

% Updating data storage and visualization
setappdata(handles.main_interface,'blueParameters',blueParameters);
drawFrameBlueBW(handles);
set(handles.text_slider_noise_max_size_blue, 'String', ['Noise max size = ', num2str(blueParameters.NoiseMaxSize)]);


% --- Executes during object creation, after setting all properties.
function slider_noise_max_size_blue_CreateFcn(hObject, eventdata, handles)
% hObject    handle to slider_noise_max_size_blue (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    empty - handles not created until after all CreateFcns called

% Hint: slider controls usually have a light gray background.
if isequal(get(hObject,'BackgroundColor'), get(0,'defaultUicontrolBackgroundColor'))
    set(hObject,'BackgroundColor',[.9 .9 .9]);
end
set(hObject,'sliderstep',[5e-4,1e-2]);

% --- Executes on button press in button_get_image.
function button_get_image_Callback(hObject, eventdata, handles)
% hObject    handle to button_get_image (see GCBO)
% eventdata  reserved - to be defined in a future version of MATLAB
% handles    structure with handles and user data (see GUIDATA)
% Getting video object
videoObj = getappdata(handles.main_interface,'videoObj');
frame = step(videoObj);

% try
%     getappdata(handles.main_interface,'hfig');
%     figure(hfig);
%     imshow(frame);
% catch
%     hfig = figure('Name','Still camera view');
%     setappdata(handles.main_interface,'hfig',hfig);
%     imshow(frame);
% end     
figure(100)
set(gcf, 'numbertitle', 'off', 'name', 'Still camera view')
clf
imshow(frame);
