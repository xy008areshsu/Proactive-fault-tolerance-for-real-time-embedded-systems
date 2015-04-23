% Copyright 2015 The MathWorks, Inc.
allotedRunTime = 3*60; % [sec] Time allowed for run

% starting parameters
% The timer starts once the robot has moved a certain distance from the
% starting point
startPos = [0.5, 0.5]; % [m] Starting position in arena
startingRadius = 0.1; % [m]

% Target parameters
targetBoundaryRadius = 0.07; % [m] radius considered at location
statTimeReq = 2.5; % [sec] minimum time robot must be at location
