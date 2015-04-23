classdef RobotDetection < matlab.System & LogMessage
% Copyright 2015 The MathWorks, Inc.    
    properties (Constant)
        
        RESOLUTION_COLS = 800;
        RESOLUTION_ROWS = 600;
    end
        
    properties       
        Nsites;   % Number of sites
    end
    
    properties (SetAccess = public, GetAccess = protected)
        
        MatIm2worldBluebox;
        MatWorld2imGround;
        
        % Detection parameters (image processing) 
        HHighThresh;
        HLowThresh;
        SThresh;
        VThresh;
        GreenLevel;
        NoiseMaxSize;
        MaxEccentricity;
        
    end
    
    properties (SetAccess = protected, GetAccess = public)
        
        SitePositions;    % Matrix Nx2 (N == Nsites) with target position on screen
        
    end
    
    properties (Dependent, SetAccess = protected, GetAccess = public)
        
        IsValid;            % Object setup is OK and detection can be runned
        
    end
    
    properties (Access = private)
        videoObj;
    end
    
    methods
        
        % Object constructor
        function obj = RobotDetection(varargin)
            
            % Target position is empty by default, it will be filled during
            % intialization
            obj.SitePositions = [];
            
            % Optional properties can be set as name-value pair arguments
            setProperties(obj,length(varargin),varargin{:});
            
        end
        
        % Object destructor
        function delete(obj)
            release(obj)
        end
        
        function flag = get.IsValid(obj)
            
            % Detection is valid if
            %   - TargetPosition is a matrix of size Nsites x 2 without
            %       any NaN
            %   - Nsites is a positive integer
            flag = ~isempty(obj.SitePositions) && ...
                ~any(isnan(obj.SitePositions(:))) && ...
                ~isempty(obj.Nsites) && ...
                obj.Nsites > 0 && ...
                size(obj.SitePositions,1) == obj.Nsites;
            
        end
        
    end
    
    methods (Access=protected)
        
        function validatePropertiesImpl(obj)
            
            % Check that target number is correctly defined
            if isempty(obj.Nsites) || obj.Nsites < 1
                error('RobotDetection:InvalidProperty:Nsites', ...
                    'Number of sites must be real positive integer')
            end
            
        end
        
        function setupImpl(obj)
            
                % Initialize target position matrix
                obj.SitePositions = nan(obj.Nsites,2);
                
                % Opening camera connection
                try
                    imaqreset
                    obj.videoObj = imaq.VideoDevice('winvideo', 1, ...
                        ['MJPG_',num2str(obj.RESOLUTION_COLS),'x',num2str(obj.RESOLUTION_ROWS)]);
                    obj.videoObj.DeviceProperties.FocusMode = 'manual';
                    %obj.videoObj.DeviceProperties.ExposureMode = 'manual'; 
                    %obj.videoObj.DeviceProperties.WhiteBalanceMode = 'manual';
                catch
                    error('detection_initialization:noCameraConnected', ...
                        'Please check your camera connection and run imaqhwinfo');
                end
                
                % Giving 10 frames to the camera to settle
                for iframe = 1 : 11
                    frame = step(obj.videoObj);
                end
                
                % Detecting green targets first
                % Define and cleanup green image
                frame = im2double(frame);
                frameGreen = frame(:,:,2) - (frame(:,:,1) + frame(:,:,3))/2;
                frameGreenBW = frameGreen>obj.GreenLevel;
                frameGreenBW = bwareaopen(frameGreenBW, obj.NoiseMaxSize);
                frameGreenBW = imfill(frameGreenBW, 'holes');
                frameGreenBW = imclearborder(frameGreenBW);
                
                % Counting sites
                sites_stat = regionprops(frameGreenBW, {'Area','Centroid','Eccentricity'});
                sites_stat = sites_stat([sites_stat.Eccentricity]<obj.MaxEccentricity);
                
                % Detect robot
                [x,y,~] = stepImpl(obj);
                
                % Set Sites Positions
                if (length(sites_stat) == obj.Nsites) && all(~isnan([x y]))
                    obj.SitePositions = reshape([sites_stat.Centroid],2,obj.Nsites)';
                elseif (length(sites_stat) ~= obj.Nsites)
                    obj.addMessage('RobotDetection:setupImpl:SitesNotFound', ...
                        sprintf('Le nombre de sites trouvés (%d) ne correspond pas au nombre de sites attendus (%d)', ...
                        length(sites_stat), obj.Nsites));
                    obj.SitePositions = reshape([sites_stat.Centroid],2,length(sites_stat))';
                else % if any(isnan([x y])) % Commented because condition is always TRUE here
                    obj.addMessage('RobotDetection:setupImpl:RobotNotFound', ...
                        'La position du robot n''a pas pu être déterminée');
                end
                
            
        end
        
        function releaseImpl(obj)
            
            % Release camera object
            if ~isempty(obj.videoObj)
                pause(0.1)
                release(obj.videoObj)
            end
            
        end
        
        % Define number of input for step function
        function numIn = getNumInputsImpl(~)
            numIn = 0;
        end
        
        function numOut = getNumOutputsImpl(~)
            numOut = 3; % Step function returns robot position (X,Y) and current camera image
        end
        
        % stepImpl method is called by the step method.
        function [robot_x,robot_y,frame] = stepImpl(obj)
            
                % Detecting frame
                frame = step(obj.videoObj);
                
                % Detecting biggest blue spot (the robot, hopefully)
                frameHSV = rgb2hsv(frame);   % img contains the camera picture
                Hplane = frameHSV(:,:,1);
                Splane = frameHSV(:,:,2);
                Vplane = frameHSV(:,:,3);
                
                robot_detection = (...
                    Hplane > obj.HLowThresh & ...
                    Hplane < obj.HHighThresh & ...
                    Splane > obj.SThresh & ...
                    Vplane > obj.VThresh);
                
                robot_detection = bwareaopen(robot_detection, obj.NoiseMaxSize);

                robot_stat = regionprops(robot_detection, {'Area', 'Centroid'});
                
                if length(robot_stat) >= 1
                    [~, robot_index] = max([robot_stat.Area]);
                    robot_x = robot_stat(robot_index).Centroid(1); % Columns in the image
                    robot_y = robot_stat(robot_index).Centroid(2); % rows in the image
                    [Xw, Yw] = apply_im2world(obj.MatIm2worldBluebox, robot_x, obj.RESOLUTION_ROWS - robot_y);
                    [xi, yi] = apply_world2im(obj.MatWorld2imGround, Xw, Yw);
                    robot_x = xi;
                    robot_y = obj.RESOLUTION_ROWS - yi;
                else
                    robot_x = NaN;
                    robot_y = NaN;
                    obj.addMessage('RobotDetection:stepImpl:RobotNotFound', ...
                        'La position du robot n''a pas pu être déterminée');
                end
        end
        
    end
    
end