function [xi, yi] = apply_world2im(M, u, v)
% Copyright 2015 The MathWorks, Inc.

x = M(1,1).*u + M(2,1).*v + M(3,1);
y = M(1,2).*u + M(2,2).*v + M(3,2);
z = M(1,3).*u + M(2,3).*v + M(3,3);
                
xi = x ./ z;
yi = y ./ z;