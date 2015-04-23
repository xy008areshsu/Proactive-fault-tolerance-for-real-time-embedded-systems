classdef Judge < matlab.System & LogMessage
% Copyright 2015 The MathWorks, Inc.
    % Judge
    %
    % One instance of this class is defined for each run.
    %    
    properties (Dependent,SetAccess = protected, GetAccess = public)
        IsRunning;    % Boolean, returns TRUE when judge is running (timer is started)
    end
    
    properties (Dependent,GetAccess = private, SetAccess = public)
        CalibrationFile;
    end
    
    properties (Dependent)        
        Nsites;    
    end
    
    properties (Access = protected)
        
        main_clock;  % ID of clock object (created with TIC) to count run duration
        site_clock;  % ID of clock object (created with TIC) to count time on a site
        
        time_last_target;
        
        timer_hdl;  % Handle to timer object (use to run step)
                
    end
    
    properties (SetAccess = protected, GetAccess = public)
               
        CurrentTime;
        ScoreTime;
        
        Trajectory;         % Vector (Mx2) each line correspond to a point of robot Trajectory
        SitePositions;      % Vector (Nx2) with SitePositions coordinates (X Y)
        IsSiteVisited;      % Vector (Nx1) of boolean, TRUE if site has be visited by robot
        
        CurrentSnapshot;
        RobotX;
        RobotY;
        
        RemainingTimeOnTarget;
        
    end
    
    properties
                        
        TimeTolerance  = 2.5;  % Tolerance (seconds) to consider that a site was visited
        SitesTolerance = 20; % Tolerance (distance) to consider that a site was visited
        StartTolerance = 2; % Tolerance (distance) to consider that robot start to run
        
        TimeOut        = 180; % Maximum time (in seconds) for a simulation
                
        DetectionObj;   % System object that detect robot
        
    end
    
    % Constructor and public methods
    methods
        
        % Object constructor
        function obj = Judge(varargin)
            
            % Instantiate RobotDetection
            obj.DetectionObj = RobotDetection();
            
            % Instantiate Timer
            obj.timer_hdl = timer( ...
                    'ExecutionMode',        'fixedSpacing', ...
                    'Period',               0.1, ...
                    'TimerFcn',             @(~,~) stepImpl(obj));
                
            % Optional properties can be set as name-value pair arguments
            setProperties(obj,length(varargin),varargin{:});
                                    
        end
               
        function delete(obj)
            delete(obj.timer_hdl)
            delete(obj.DetectionObj)
        end
        
        function time = get.RemainingTimeOnTarget(obj)
            
            if isempty(obj.site_clock)
                time = [];
            else
                time = obj.TimeTolerance - toc(obj.site_clock);
            end
            
        end
        
        function flag = get.IsRunning(obj)            
            flag = ~isempty(obj.timer_hdl) && strcmp(obj.timer_hdl.Running,'on');                        
        end
        
        function n_sites = get.Nsites(obj)
            n_sites = get(obj.DetectionObj,'Nsites');
        end
        
        function set.Nsites(obj,n_sites)
            set(obj.DetectionObj,'Nsites',n_sites)
        end
        
        function set.CalibrationFile(obj,file)
            tmp = load(file);
            set(obj.DetectionObj, 'MatIm2worldBluebox', [tmp.calibration_data.matrices.robot2world], ...
                'MatWorld2imGround', [tmp.calibration_data.matrices.world2target], ...
                'HHighThresh', [tmp.parameters_data.robots.HHighThresh], ...
                'HLowThresh', [tmp.parameters_data.robots.HLowThresh], ...
                'SThresh', [tmp.parameters_data.robots.SThresh], ...
                'VThresh', [tmp.parameters_data.robots.VThresh], ...
                'GreenLevel', [tmp.parameters_data.targets.GreenLevel], ...
                'NoiseMaxSize', [tmp.parameters_data.targets.NoiseMaxSize], ...
                'MaxEccentricity', [tmp.parameters_data.targets.MaxEccentricity]);
                       
        end
        
    end
    
    % Overload methods of matlab.System class
    methods (Access=protected)
        
        function validatePropertiesImpl(obj) %#ok<MANU>
                        
        end
        
        function setupImpl(obj)
                                        
            % Setup detection
            setup(obj.DetectionObj)
                        
            % Store SitePositions in corresponding property
            obj.SitePositions = obj.DetectionObj.SitePositions;
            
            % Initialize is_visited flags to FALSE
            obj.IsSiteVisited = false(size(obj.SitePositions,1),1);
                
            [obj.RobotX,obj.RobotY,obj.CurrentSnapshot] = step(obj.DetectionObj);
            
            % Start timer execution (only if detection setup is OK)
            if obj.DetectionObj.IsValid
                                
                obj.Trajectory = [obj.RobotX,obj.RobotY];
                
                % Start timer
                start(obj.timer_hdl)
                
            else
                
                obj.addMessage('Judge:setupImpl:DetectionInvalid', ...
                    sprintf('L''initialisation de la détection a échouée en renvoyant le message suivant:\n%s', ...
                    obj.DetectionObj.LastMessage))
                
            end
            
        end
        
        function releaseImpl(obj)
            
            % Reset main counter
            obj.main_clock = uint64([]);
            
            if isa(obj.DetectionObj,'RobotDetection')
                release(obj.DetectionObj)
            end
            
            if ~isempty(obj.timer_hdl)
                stop(obj.timer_hdl)
            end
        end
        
        % Define number of input for step function
        function numIn = getNumInputsImpl(~)
            numIn = 0; % No input
        end
        
        function numOut = getNumOutputsImpl(~)
            numOut = 0; % No output
        end
        
        % stepImpl method is called by the step method.
        function stepImpl(obj)
            
            % RobotDetection returns robot position (X and Y)
            % img is a camera screenshot
            [obj.RobotX,obj.RobotY,obj.CurrentSnapshot] = step(obj.DetectionObj);
            
            % Calculate elapsed time (in seconds)
            if ~isempty(obj.main_clock)
                obj.CurrentTime = toc(obj.main_clock);
            else
                obj.CurrentTime = 0;
            end
                        
            % Add X and Y in Trajectory
            % Particular case is when Trajectory contains only 1 point
            % (first call to step: robot initial position), to consider
            % that robot starts is run, it must move more than tolerance
            if size(obj.Trajectory,1) == 1
                
                % Start by calculating distance covered by robot, then check if
                % it's enough to start clock.
                dxy = obj.Trajectory - [obj.RobotX obj.RobotY];
                distance = sqrt(dxy(1).^2 + dxy(2).^2);
                
                if distance > obj.StartTolerance
                    obj.main_clock = tic();
                    obj.Trajectory = [obj.Trajectory; obj.RobotX obj.RobotY];
                end
                
            elseif ~isnan(obj.RobotX) && ~isnan(obj.RobotY)
                obj.Trajectory = [obj.Trajectory; obj.RobotX obj.RobotY];                              
            end
            
            % Check if robot is on a site (close enough to be consider on a
            % non-visited site)
            % There are 2 conditions to be considered on a site: be close
            % enough and site is not considered as visited            
            dxy = bsxfun(@minus,obj.SitePositions,[obj.RobotX obj.RobotY]);
            distance = sqrt(dxy(:,1).^2 + dxy(:,2).^2);
            is_on_site = (distance <= obj.SitesTolerance) & ~obj.IsSiteVisited;
            
            % Actions must be done if robot is on a site, else ensure that
            % no clock is running
            if nnz(is_on_site) == 1 % Robot cannot be on more than one site at a time
                if isempty(obj.site_clock) % No counter is running, it's the first time robot is detected on a site, launch counter
                    obj.site_clock = tic();
                elseif toc(obj.site_clock) >= obj.TimeTolerance % A counter is running and elapsed time is upper to tolerance, site must be defined as visited
                    obj.IsSiteVisited(is_on_site) = true;
                    obj.site_clock = uint64([]);
                    obj.ScoreTime = obj.CurrentTime;
                end
            else                
                obj.site_clock = uint64([]);
            end
            
            % Time for score is the time when last target was found
            % except if robot has not visited any target, in this case
            % this is elapsed time
            if ~any(obj.IsSiteVisited)
                obj.ScoreTime = obj.CurrentTime;
            end
            
            % End of run
            % Run can be stopped by 2 conditions:
            %   - All SitePositions are visited
            %   - Elapsed time is greater than timeout
            if all(obj.IsSiteVisited) || (obj.CurrentTime > obj.TimeOut)
                
                obj.releaseImpl();
                
            end
            
        end
        
    end
    
end
