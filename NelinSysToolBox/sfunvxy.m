function [sys,x0,str,ts] = sfunvxy(t,x,u,flag,ax,use_grid,varargin)
%SFUNVXY S-function that acts as a Vector X-Y scope using MATLAB plotting functions.
%   This M-file is an enhanced version of MATLAB's standard SFUNXY function used with
%   "XYGraph" Simulink block from "Sinks" library. This version is able to cope with
%   vector inputs and therefore is not limited to scalar X and Y.
%
%   See also SFUNXY
%
%   Martin Ondera 7-16-2006

%  SFUNXY's description:
%   This M-file is designed to be used in a Simulink S-function block.
%   It draws a line from the previous input point, which is stored using
%   discrete states, and the current point.  It then stores the current
%   point for use in the next invocation.
%
%   See also SFUNXYS, LORENZS.

%   Copyright 1990-2004 The MathWorks, Inc.
%   $Revision: 1.38.2.5 $
%   Andrew Grace 5-30-91.
%   Revised Wes Wang 4-28-93, 8-17-93, 12-15-93
%   Revised Craig Santos 10-28-96

% Store the block handle and check if it's valid
blockHandle = gcbh;
IsValidBlock(blockHandle, flag);

switch flag

  %%%%%%%%%%%%%%%%%%
  % Initialization %
  %%%%%%%%%%%%%%%%%%
  case 0
    [sys,x0,str,ts] = mdlInitializeSizes(ax,varargin{:});
    SetBlockCallbacks(blockHandle);

  %%%%%%%%%%
  % Update %
  %%%%%%%%%%
  case 2
    sys = mdlUpdate(t,x,u,flag,ax,blockHandle,use_grid,varargin{:});

  %%%%%%%%%
  % Start %
  %%%%%%%%%
  case 'Start'
    LocalBlockStartFcn(blockHandle)

  %%%%%%%%
  % Stop %
  %%%%%%%%
  case 'Stop'
    LocalBlockStopFcn(blockHandle)

  %%%%%%%%%%%%%%
  % NameChange %
  %%%%%%%%%%%%%%
  case 'NameChange'
    LocalBlockNameChangeFcn(blockHandle)

  %%%%%%%%%%%%%%%%%%%%%%%%
  % CopyBlock, LoadBlock %
  %%%%%%%%%%%%%%%%%%%%%%%%
  case { 'CopyBlock', 'LoadBlock' }
    LocalBlockLoadCopyFcn(blockHandle)

  %%%%%%%%%%%%%%%
  % DeleteBlock %
  %%%%%%%%%%%%%%%
  case 'DeleteBlock'
    LocalBlockDeleteFcn(blockHandle)

  %%%%%%%%%%%%%%%%
  % DeleteFigure %
  %%%%%%%%%%%%%%%%
  case 'DeleteFigure'
    LocalFigureDeleteFcn

  %%%%%%%%%%%%%%%%
  % Unused flags %
  %%%%%%%%%%%%%%%%
  case { 3, 9 }
    sys = [];

  %%%%%%%%%%%%%%%%%%%%
  % Unexpected flags %
  %%%%%%%%%%%%%%%%%%%%
  otherwise
    if ischar(flag),
      errmsg=sprintf('Unhandled flag: ''%s''', flag);
    else
      errmsg=sprintf('Unhandled flag: %d', flag);
    end

    error(errmsg);

end

% end sfunvxy

%
%=============================================================================
% mdlInitializeSizes
% Return the sizes, initial conditions, and sample times for the S-function.
%=============================================================================
%
function [sys,x0,str,ts] = mdlInitializeSizes(ax,varargin)

if length (ax)~=4
  error('Axes were not set properly.')
end

sizes = simsizes;
sizes.NumContStates  = 0;
sizes.NumDiscStates  = 0;
sizes.NumOutputs     = 0;
sizes.NumInputs      = -1;
sizes.DirFeedthrough = 0;
sizes.NumSampleTimes = 1;
sys = simsizes(sizes);

x0 = [];
str = [];

%
% initialize the array of sample times, note that in earlier
% versions of this scope, a sample time was not one of the input
% arguments, the varargs checks for this and if not present, assigns
% the sample time to -1 (inherited)
%
if ~isempty(varargin) > 0
  ts = [varargin{1} 0];
else
  ts = [-1 0];
end

% end mdlInitializeSizes

%
%=============================================================================
% mdlUpdate
% Handle discrete state updates, sample time hits, and major time step
% requirements.
%=============================================================================
%
function sys=mdlUpdate(t,x,u,flag,ax,block,use_grid,varargin)

%
% always return empty, there are no states...
%
sys = [];

%
% Locate the figure window associated with this block.  If it's not a valid
% handle (it may have been closed by the user), then return.
%
FigHandle=GetSfunVXYFigure(block);
if ~ishandle(FigHandle),
   return
end

% Get UserData of the figure.
ud = get(FigHandle,'UserData');

% At the beginning draw the first point of each line.
if isempty(ud.XData),
  x_data = [(u(1:end/2))'; (u(1:end/2))'];
  y_data = [(u(end/2+1:end))'; (u(end/2+1:end))'];

  % Create a separate plot object for each line.
  if isempty(ud.XYLines)
    for k = 1:length(u)/2
      ud.XYLines = [ud.XYLines; plot(0,0,'EraseMode','none','Parent',ud.XYAxes)];
    end
  end

% Draw line segments for each line.
else
  x_data = [ud.XData(end,:); (u(1:end/2))'];
  y_data = [ud.YData(end,:); (u(end/2+1:end))'];
end

% Define axes limits.
set(ud.XYAxes, ...
    'Visible','on',...
    'Xlim', ax(1:2),...
    'Ylim', ax(3:4));

% Display a grid if the user wishes so.
if use_grid
   set(ud.XYAxes,'XGrid','on','YGrid','on');
else
   set(ud.XYAxes,'XGrid','off','YGrid','off');
end

% Load color palette.
farby = get(ud.XYAxes,'ColorOrder'); l = 0;

% Draw a line for each column.
rozmer = size(x_data);
for k = 1 : rozmer(2)
  if (k > (l+1)*length(farby))
    l = l+1;
  end
  
  set(ud.XYLines(k), ...
     'Xdata',x_data(:,k),...
     'Ydata',y_data(:,k),...
     'LineStyle','-',...
     'Color',farby(k-l*end,:));
end

figure(FigHandle);
set(ud.XYTitle,'String','Phase-Plane Portrait');
set(FigHandle,'Color',get(FigHandle,'Color'));

%
% update the X/Y stored data points
%
ud.XData(end+1,:) = (u(1:end/2))';
ud.YData(end+1,:) = (u(end/2+1:end))';
set(FigHandle,'UserData',ud);
drawnow

% end mdlUpdate

%
%=============================================================================
% LocalBlockStartFcn
% Function that is called when the simulation starts.  Initialize the
% XY Graph scope figure.
%=============================================================================
%
function LocalBlockStartFcn(block)

%
% get the figure associated with this block, create a figure if it doesn't
% exist
%
FigHandle = GetSfunVXYFigure(block);
if ~ishandle(FigHandle),
  FigHandle = CreateSfunVXYFigure(block);
end

ud = get(FigHandle,'UserData');

% Erase the plot from the previous simulation.
for k = 1:length(ud.XYLines)
  set(ud.XYLines(k),'Erasemode','normal');
  set(ud.XYLines(k),'XData',[],'YData',[]);
  set(ud.XYLines(k),'XData',0,'YData',0,'Erasemode','none');
end

% Delete all the previous data.
ud.XYLines = [];
ud.XData   = [];
ud.YData   = [];
set(FigHandle,'UserData',ud);

% end LocalBlockStartFcn

%
%=============================================================================
% LocalBlockStopFcn
% At the end of the simulation, set the line's X and Y data to contain
% the complete set of points that were acquired during the simulation.
% Recall that during the simulation, the lines are only small segments from
% the last time step to the current one.
%=============================================================================
%
function LocalBlockStopFcn(block)

FigHandle=GetSfunVXYFigure(block);
if ishandle(FigHandle),

   % Get UserData of the figure.
   ud = get(FigHandle,'UserData');

   % Load color palette.
   farby = get(ud.XYAxes,'ColorOrder'); l = 0;

   % Draw a line for each column.
   rozmer = size(ud.XData);
   for k = 1 : rozmer(2)
      if (k > (l+1)*length(farby))
         l = l+1;
      end

      set(ud.XYLines(k), ...
         'Xdata',ud.XData(:,k),...
         'Ydata',ud.YData(:,k),...
         'LineStyle','-',...
         'Color',farby(k-l*end,:));
   end
end

% end LocalBlockStopFcn

%
%=============================================================================
% LocalBlockNameChangeFcn
% Function that handles name changes on the Graph scope block.
%=============================================================================
%
function LocalBlockNameChangeFcn(block)

%
% get the figure associated with this block, if it's valid, change
% the name of the figure
%
FigHandle = GetSfunVXYFigure(block);
if ishandle(FigHandle),
  set(FigHandle,'Name',get_param(block,'Name'));
end

% end LocalBlockNameChangeFcn

%
%================================================================================
% LocalBlockLoadCopyFcn
% This is the Vector XYGraph block's LoadFcn and CopyFcn. Initialize the block's
% UserData such that a figure is not associated with the block.
%================================================================================
%
function LocalBlockLoadCopyFcn(block)

SetSfunVXYFigure(block,-1);

% end LocalBlockLoadCopyFcn

%
%================================================================================
% LocalBlockDeleteFcn
% This is the Vector XY Graph block'DeleteFcn.  Delete the block's figure window,
% if present, upon deletion of the block.
%================================================================================
%
function LocalBlockDeleteFcn(block)

%
% Get the figure handle associated with the block, if it exists, delete
% the figure.
%
FigHandle=GetSfunVXYFigure(block);
if ishandle(FigHandle),
  delete(FigHandle);
  SetSfunVXYFigure(block,-1);
end

% end LocalBlockDeleteFcn

%
%================================================================================
% LocalFigureDeleteFcn
% This is the Vector XY Graph figure window's DeleteFcn.  The figure window is
% being deleted, update the Vector XY Graph block's UserData to reflect the change.
%================================================================================
%
function LocalFigureDeleteFcn

%
% Get the block associated with this figure and set it's figure to -1
%
ud=get(gcbf,'UserData');
SetSfunVXYFigure(ud.Block,-1)

% end LocalFigureDeleteFcn

%
%==================================================================================
% GetSfunVXYFigure
% Retrieves the figure window associated with this S-function Vector XY Graph block
% from the block's parent subsystem's UserData.
%==================================================================================
%
function FigHandle=GetSfunVXYFigure(block)

if strcmp(get_param(block,'BlockType'),'S-Function'),
  block=get_param(block,'Parent');
end

FigHandle=get_param(block,'UserData');
if isempty(FigHandle),
  FigHandle=-1;
end

% end GetSfunVXYFigure

%
%===============================================================================
% SetSfunVXYFigure
% Stores the figure window associated with this S-function Vector XY Graph block
% in the block's parent subsystem's UserData.
%===============================================================================
%
function SetSfunVXYFigure(block,FigHandle)

if strcmp(get_param(bdroot,'BlockDiagramType'),'model'),
  if strcmp(get_param(block,'BlockType'),'S-Function'),
    block=get_param(block,'Parent');
  end

  set_param(block,'UserData',FigHandle);
end

% end SetSfunVXYFigure

%
%=============================================================================
% CreateSfunVXYFigure
% Creates the figure window associated with this S-function XY Graph block.
%=============================================================================
%
function FigHandle=CreateSfunVXYFigure(block)

%
% the figure doesn't exist, create one
%
screenLoc = get(0,'ScreenSize');
windowPos = get_param(get_param(block,'Parent'),'Window');

%
% display the figure to the right of the main window
% (in case if there is not enough space, to the left)
%
if (windowPos(3) + 400 <= screenLoc(3))
   left = windowPos(3);
else
   if (windowPos(1) - 400 > 0)
      left = windowPos(1) - 400;
   else
      left = screenLoc(3) - 400;
   end
end

% use the vertical position of the main window
bottom = screenLoc(4) - windowPos(2) - 265;

FigHandle = figure('Units',          'pixel',...
                   'Position',       [left bottom 400 300],...
                   'Name',           get_param(block,'Name'),...
                   'NextPlot',       'add',...
                   'Tag',            'SIMULINK_XYGRAPH_FIGURE',...
                   'NumberTitle',    'off',...
                   'IntegerHandle',  'off',...
                   'DeleteFcn',      'sfunvxy([],[],[],''DeleteFigure'')');
%
% store the block's handle in the figure's UserData
%
ud.Block=block;

%
% define color scheme
%
farby = [0 0 1;... % blue
   1 0 0;...       % red
   0 1 0;...       % green
   1 0 1;...       % purple
   0 1 1;...       % cyan
   0 0 0;...       % black
   1 1 0;...       % yellow
   0.8 0.8 0.8];   % gray

%
% create various objects in the figure
%
ud.XYAxes   = axes('NextPlot','add','ColorOrder',farby);
ud.XYXlabel = xlabel('x1(t)');
ud.XYYlabel = ylabel('x2(t)');
ud.XYTitle  = get(ud.XYAxes,'Title');
ud.XData    = [];
ud.YData    = [];
ud.XYLines  = [];
set(ud.XYAxes,'Visible','off');

%
% Associate the figure with the block, and set the figure's UserData.
%
SetSfunVXYFigure(block,FigHandle);
set(FigHandle,'HandleVisibility','callback','UserData',ud);

% end CreateSfunVXYFigure

%
%=============================================================================
% IsValidBlock
% Check if this is a valid block
%=============================================================================
%
function IsValidBlock(block, flag)

if strcmp(get_param(block,'BlockType'),'S-Function'),
  thisBlock = get_param(block,'Parent');
else
  thisBlock = block;
end

if(~strcmp(flag,'DeleteFigure'))
  if(~strcmp(get_param(thisBlock,'MaskType'), 'Vector XY Graph for Phase-Plane Portraits'))
    error('Invalid block')
  end
end
%end IsValidBlock

%
%=============================================================================
% SetBlockCallbacks
% This sets the callbacks of the block (avoid using subroutines from SFUNXY)
%=============================================================================
%
function SetBlockCallbacks(block)

%
% the actual source of the block is the parent subsystem
%
block=get_param(block,'Parent');

%
% if the block isn't linked, issue a warning, and then set the callbacks
% for the block so that it has the proper operation
%
if strcmp(get_param(block,'LinkStatus'),'none'),
  warnmsg=sprintf(['The Vector XY Graph scope ''%s'' should be replaced with a ' ...
                   'new version from the NelinSys library'],...
                   block);
  warning(warnmsg);

  callbacks={
    'CopyFcn',       'sfunvxy([],[],[],''CopyBlock'')' ;
    'DeleteFcn',     'sfunvxy([],[],[],''DeleteBlock'')' ;
    'LoadFcn',       'sfunvxy([],[],[],''LoadBlock'')' ;
    'StartFcn',      'sfunvxy([],[],[],''Start'')' ;
    'StopFcn'        'sfunvxy([],[],[],''Stop'')' ;
    'NameChangeFcn', 'sfunvxy([],[],[],''NameChange'')' ;
  };

  for i=1:length(callbacks),
    if ~strcmp(get_param(block,callbacks{i,1}),callbacks{i,2}),
      set_param(block,callbacks{i,1},callbacks{i,2})
    end
  end
end

% end SetBlockCallbacks