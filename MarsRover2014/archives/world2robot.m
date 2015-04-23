function [x,y]=world2robot(x_robot,y_robot,bearing_robot,x_target,y_target)
% Copyright 2015 The MathWorks, Inc.

x_dif=x_target-x_robot;
y_dif=y_target-y_robot;

x=x_dif*cosd(bearing_robot)-y_dif*sind(bearing_robot);
y=x_dif*sind(bearing_robot)+y_dif*cosd(bearing_robot);

x = -x;
y = -y;
