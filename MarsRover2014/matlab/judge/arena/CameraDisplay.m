classdef CameraDisplay < hgsetget & LogMessage
% Copyright 2015 The MathWorks, Inc.    
    properties (Dependent, SetAccess = public, GetAccess = private)
        Visible;            % Window is visible or not
        Title;              % Window title
        Background;         % Image displayed as background
        ValidatedSites;     % Boolean to identify if a site was visited or not (Nx1 matrix)
        ElapsedTime;        % Elapsed time (in seconds)
        ScoreTime;          % Score time (in seconds)
        SiteString;         % Label to display number of visited sites
        TimeString;         % Label to display time
        ScoreString;        % Label to display score (time to last site)
        TeamName;           % Displayed team name
        AllSites;           % List of all sites (Nx2 matrix)
        ValidTargetAreas;   % Valid target areas visible or not
        RobotPosition;      % current XY position of the robot
        Trajectory;         % Trajectory displayed as a line
        CountDown;          % Countdown display on image
    end
    
    properties (Dependent, SetAccess = private, GetAccess = public)
        Handle;
    end
    
    properties (Constant)

        VALID_TARGET_MARKER_SIZE = 40; % TODO (Check this value, in pixels) Radius of the valid target area 
        
       % Window size is controlled from camera image size
        IMAGE_WIDTH = 800;
        IMAGE_HEIGHT = 600;
        
        ALL_VISITED_COLOR = [0 1 0];% Color for text if all sites were visited
        SITE_COLOR = [0 0 0];       % Default color for text about number of sites
        TIME_COLOR = [0 0 0];       % Default color for text about elapsed time
        
    end
          
    properties (Access = private) % Properties have to be accessed via Dependent properties
        site_str = 'Sites visités';
        time_str = 'Temps écoulé';
        score_str = 'Score';
        all_sites;
        robot_position;
    end
                
    properties (Access = protected)
        FgCamera;
        AxVideo;
        PnDisplay;
        StTeam;
        StSites;
        StTotalTime;
        StScoreTime;
        ImCamera;
        ScVisited;
        TgArea;
        RbTrajectory;
        TxCountDown;
    end
    
    methods
        
        % Constructor
        % -----------
        function obj = CameraDisplay(varargin)
            
            obj.FgCamera = figure(...
                'NumberTitle',                  'off', ...
                'Menubar',                      'none', ...
                'Toolbar',                      'none', ...
                'Name',                         'Exploration de Mars', ...
                'Units',                        'pixels', ...
                'Position',                     [0 0 obj.IMAGE_WIDTH+20 obj.IMAGE_HEIGHT+150], ...
                'Color',                        [1 1 1], ...
                'Resize',                       'off', ...
                'CloseRequestFcn',              []);
            movegui(obj.FgCamera,'center')
            
            obj.AxVideo = axes( ...
                'Parent',                       obj.FgCamera, ...
                'Units',                        'pixels', ...
                'Position',                     [10 10 obj.IMAGE_WIDTH obj.IMAGE_HEIGHT], ...
                'Box',                          'on', ...
                'XTick',                        [], ...
                'YTick',                        [], ...
                'NextPlot',                     'add', ...
                'XLim',                         [0 obj.IMAGE_WIDTH], ...
                'YLim',                         [0 obj.IMAGE_HEIGHT], ...
                'YDir',                         'reverse');
            
            obj.PnDisplay = uipanel( ...
                'Parent',                       obj.FgCamera, ...
                'Units',                        'pixels', ...
                'Position',                     [10 obj.IMAGE_HEIGHT+20 obj.IMAGE_WIDTH 110], ...
                'Title',                        '', ...
                'BackgroundColor',              get(obj.FgCamera,'Color'));
            
            obj.StTeam = uicontrol( ...
                'Parent',                       obj.PnDisplay, ...
                'Style',                        'text', ...
                'Units',                        'pixels', ...
                'Position',                     [10 65 obj.IMAGE_WIDTH-20 35], ...
                'String',                       '', ...
                'FontSize',                     14, ...
                'FontWeight',                   'bold', ...
                'HorizontalAlignment',          'center', ...
                'BackgroundColor',              get(obj.PnDisplay, 'BackgroundColor'), ...
                'ForegroundColor',              obj.SITE_COLOR);
            
            obj.StSites = uicontrol( ...
                'Parent',                       obj.PnDisplay, ...
                'Style',                        'text', ...
                'Units',                        'pixels', ...
                'Position',                     [10 20 250 35], ...
                'String',                       '', ...
                'FontSize',                     14, ...
                'FontWeight',                   'bold', ...
                'BackgroundColor',              get(obj.PnDisplay, 'BackgroundColor'), ...
                'ForegroundColor',              obj.SITE_COLOR);
            
            obj.StTotalTime = uicontrol( ...
                'Parent',                       obj.PnDisplay, ...
                'Style',                        'text', ...
                'Units',                        'pixels', ...
                'Position',                     [obj.IMAGE_WIDTH-260 20 250 55], ...
                'String',                       '', ...
                'FontSize',                     14, ...
                'FontWeight',                   'bold', ...
                'BackgroundColor',              get(obj.PnDisplay, 'BackgroundColor'), ...
                'ForegroundColor',              obj.TIME_COLOR, ...
                'HorizontalAlignment',          'right');
            
            obj.StScoreTime = uicontrol( ...
                'Parent',                       obj.PnDisplay, ...
                'Style',                        'text', ...
                'Units',                        'pixels', ...
                'Position',                     [obj.IMAGE_WIDTH-260 20 250 25], ...
                'String',                       '', ...
                'FontSize',                     14, ...
                'FontWeight',                   'bold', ...
                'BackgroundColor',              get(obj.PnDisplay, 'BackgroundColor'), ...
                'ForegroundColor',              obj.TIME_COLOR, ...
                'HorizontalAlignment',          'right');
            
            % Create empty graphical objects to get handles
            obj.ImCamera = image([], ...
                'Parent',                       obj.AxVideo);
            obj.ScVisited = plot(nan,nan,'o', ...
                'Parent',                       obj.AxVideo, ...
                'MarkerSize',                   15, ...
                'MarkerFaceColor',              [0 1 0]);

            % Lines below to define the MarkerSize Value, because it is
            % always given in points
            axesPixelsSize = get(obj.AxVideo,'Position'); % pixels
            set(obj.AxVideo,'Units','Points');
            axesPointsSize = get(obj.AxVideo,'Position'); % points
            set(obj.AxVideo,'Units','Pixels');
            pixels2points = axesPointsSize(3) / axesPixelsSize(3); 
            
            obj.TgArea = plot(NaN, NaN,'o',...
                'Parent', obj.AxVideo, ...
                'MarkerSize', obj.VALID_TARGET_MARKER_SIZE * pixels2points,...
                'Color','r','linewidth',3);
            obj.RbTrajectory = plot(NaN,NaN,'b--','linewidth',2);
            
            obj.TxCountDown = text(obj.IMAGE_WIDTH/2,obj.IMAGE_HEIGHT/2,'', ...
                'Parent',           obj.AxVideo, ...
                'FontName',         'Arial Black', ...
                'FontSize',         80, ...
                'Color',            [0 0 0]);
            
            % Apply properties given as input
            if ~isempty(varargin)
                set(obj, varargin{:});
            end
            
        end
        
        function delete(obj)
            delete(obj.FgCamera)
        end
        
        % Get functions
        % -------------
        function hdl = get.Handle(obj)
            hdl = obj.FgCamera;
        end
        
        % Set functions
        % -------------
        function set.CountDown(obj,val)
            
            if isempty(val) || isnan(val)
                set(obj.TxCountDown, 'String', '')
            else
                set(obj.TxCountDown, 'String', sprintf('%.0f',ceil(val)))
            end
            
        end
        
        function set.Visible(obj,flag)
            set(obj.FgCamera,'Visible',flag)       
            drawnow
        end
        
        function set.ValidTargetAreas(obj,flag)
            if flag
                set(obj.TgArea,'XData',obj.all_sites(:,1),'YData',obj.all_sites(:,2));
                drawnow
            end
        end
        
        function set.Title(obj,str)
            set(obj.FgCamera,'Name',str)
        end
        
        function set.Background(obj,img)
            set(obj.ImCamera,'CData',img)
        end
        
        function set.AllSites(obj,sites)
            
            obj.all_sites = sites;
            set(obj.ScVisited, 'XData', [], 'YData', [])
            
            set(obj.StSites, 'UserData',     0)
            obj.setSiteString();
            
        end
        
        function set.RobotPosition(obj, position)
            obj.robot_position = position;
            
            Xtraj = get(obj.RbTrajectory,'XData');
            Ytraj = get(obj.RbTrajectory,'YData');
            if all(~isnan(position(:)))
                set(obj.RbTrajectory,'XData', [Xtraj, position(1)]);
                set(obj.RbTrajectory,'YData', [Ytraj, position(2)]);
            else
                obj.addMessage('CameraDisplay:set:RobotPosition', ...
                    'La position du robot ne peut être mise à jour car elle contient des NaNs');
            end
        end
        
        function set.ValidatedSites(obj,visited)   
            
            if isscalar(visited) && visited == 0
                n_visited = 0;
            else
                set(obj.ScVisited, ...
                    'XData', obj.all_sites(visited,1), ...
                    'YData', obj.all_sites(visited,2))
                n_visited = nnz(visited);
            end
            
            set(obj.StSites, 'UserData', n_visited)
            obj.setSiteString();
            
        end
        
        function set.ElapsedTime(obj,time)
            set(obj.StTotalTime, 'UserData', time)
            obj.setTimeString();
        end
        
        function set.ScoreTime(obj,time)
            set(obj.StScoreTime, 'UserData', time)
            obj.setScoreString();
        end
        
        function set.SiteString(obj,str)
            obj.site_str = str;
            obj.setSiteString();
        end
        
        function set.TimeString(obj,str)
            obj.time_str = str;
            obj.setTimeString();
        end
        
        function set.ScoreString(obj,str)
            obj.score_str = str;
            obj.setScoreString();
        end
        
        function set.TeamName(obj,str)
            set(obj.StTeam, 'String', str)
        end
        
        function set.Trajectory(obj,traj)
            if ~isempty(traj)
                set(obj.RbTrajectory, 'XData', traj(:,1), 'YData', traj(:,2))
            else
                set(obj.RbTrajectory, 'XData', [], 'YData', [])
            end
        end
        
    end
    
    methods (Access = private)
       
        function setSiteString(obj)
            
            % Get number of sites and number of visited sites
            n_sites     = size(obj.all_sites,1);        % Number of sites
            n_visited   = get(obj.StSites,'UserData');  % Number of visited sites
            
            % Text color is green if all sites where visited, black instead      
            if (n_visited == n_sites)
                color = [0 1 0];
            else
                color = [0 0 0];
            end
            
            % Update displayed information (string + text color)
            set(obj.StSites, ...
                'String',           sprintf('%s = %d / %d', obj.site_str, n_visited, n_sites), ...
                'ForegroundColor',  color)
            
        end
        
        function setTimeString(obj)
            
            % Get number of sites and number of visited sites
            n_sites     = size(obj.all_sites,1);        % Number of sites
            n_visited   = get(obj.StSites,'UserData');  % Number of visited sites
            
            % Text color is green if all sites where visited, black instead      
            if (n_visited == n_sites)
                color = [0 1 0];
            else
                color = [0 0 0];
            end
            
            % Update displayed information (string + text color)
            set(obj.StTotalTime, ...
                'String',           sprintf('%s = %.1f s', obj.time_str, get(obj.StTotalTime,'UserData')), ...
                'ForegroundColor',  color)
        end
        
        function setScoreString(obj)
            
            % Get number of sites and number of visited sites
            n_sites     = size(obj.all_sites,1);        % Number of sites
            n_visited   = get(obj.StSites,'UserData');  % Number of visited sites
            
            % Text color is green if all sites where visited, black instead      
            if (n_visited == n_sites)
                color = [0 1 0];
            else
                color = [0 0 0];
            end
            
            % Update displayed information (string + text color)
            set(obj.StScoreTime, ...
                'String',           sprintf('%s = %.1f s', obj.score_str, get(obj.StScoreTime,'UserData')), ...
                'ForegroundColor',  color)
        end
        
    end
    
end