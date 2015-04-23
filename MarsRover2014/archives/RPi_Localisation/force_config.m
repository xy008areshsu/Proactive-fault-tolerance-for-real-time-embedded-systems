% Copyright 2015 The MathWorks, Inc.
% Fix Raspberry Pi configuration parameters
% Should be done on pre-load callback of the model

% Should also add a check to see if the Pi target is installed
% First call will fail if this is the case.

h=realtime.internal.BoardParameters('Raspberry Pi');
h.setParam('hostName','169.254.0.31');
h.setParam('userName','pi');
h.setParam('password','raspberry');
h.setParam('buildDir','/home/pi');
