function [Xworld, Yworld] = image2world(t_world2im, xim, yim)
% Copyright 2015 The MathWorks, Inc.
% Inputs: xim = [nx1] vector of x-coordinate in image plane
%         yim = [nx1] vector of y-coordinate in image plane
%         
%         For the image coordinates, origin is bottom left, convention:
%         x (>), y(^)
%
% Outputs: Xworld = [nx1] vector of x-coordinates in world plane
%          Yworld = [nx1] vector of y-coordinates in world plane
%          
%          For the world coordinates, robot at (X,Y) = (0,0)
%

if size(xim, 2) > size(xim, 1)
    xim = xim' ;
end

if size(yim, 2) > size(yim, 1)
    yim = yim' ;
end
    
[Xworld,Yworld] = transformPointsInverse(t_world2im, xim, yim) ;
