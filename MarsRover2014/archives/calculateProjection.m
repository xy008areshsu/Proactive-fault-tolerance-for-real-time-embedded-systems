function [t_world2im] = calculateProjection(p_cam, l_cam, nrows, ncols)
% Copyright 2015 The MathWorks, Inc.
% -----------------------------------------------------------------------
% function to calculate the transformation matrix between the world and
% image planes.
% This can be done beforehand, given the setup parameters.
%
% Inputs : p = depth (profondeur), from camera.m or cameraAnalytic.m, in
%              world plane (in cm)
%          l = width (largeur), from camera.m or cameraAnalytic.m, in world
%              plane (in cm)
%          nrows = number of rows in image (240)
%          ncols = number of columns in image (320)
%         (NOTE !! the ratio between 
%          nrows and ncols is an assumption in the derivation of
%          cameraAnalyic.m = 3/4. So, the code is valid for this ratio.)
%
% Output : t_world2im = transformation matrix from world to image. Can be
% used for projection in both directions
% -----------------------------------------------------------------------

% in metres
worldPoints = [l_cam(1)/2/100, p_cam(1)/100;        % bottom right
               -l_cam(1)/2/100, p_cam(1)/100;       % bottom left
               -l_cam(2)/2/100, p_cam(2)/100;       % top left
               l_cam(2)/2/100, p_cam(2)/100];       % top right          

% pixel locations: x(>), y(^)
imagePoints = [ncols 1 ;
               1, 1;
               1, nrows;
               ncols, nrows];

% Find projection
t_world2im = fitgeotrans(worldPoints, imagePoints, 'projective');
% RmeanIm = imref2d(size(meanImage));
% world_registered = imwarp(worldImage, t_world2im, 'OutputView', RmeanIm);

% To obtain an image->world transformation, do this:
% x = 117;
% y = 135;
% [u,v] = transformPointsInverse(t_world2im, x, y)

