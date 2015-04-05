function controller_init(mode)

% PID-control of a DC servo process.
%
% This example shows four ways to implement a periodic controller
% activity in TrueTime. The task implements a standard
% PID-controller to control a DC-servo process (2nd order system). 

% Initialize TrueTime kernel
ttInitKernel('prioDM');

% Task attributes
starttime = 0.0;
period = 0.01;
deadline = period;

data.throttle = 0;  
data.brake = 0; 
data.old_distance1 = -ttAnalogIn(2);
data.old_distance2 = -ttAnalogIn(3);
                   

switch mode
    
    case 1
        % IMPLEMENTATION 1: using the built-in support for periodic tasks

        ttCreatePeriodicTask('cruise_control_task', starttime, period, 'cruise_code_2', data);
        
    case 2


        ttCreatePeriodicTask('cruise_control_task', starttime, period, 'cruise_code', data);


end
