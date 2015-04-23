function [Xworld, Yworld] = apply_im2world(M, xim, yim)
% Copyright 2015 The MathWorks, Inc.

u = M(1,1).*xim + M(2,1).*yim + M(3,1);
v = M(1,2).*xim + M(2,2).*yim + M(3,2);
w = M(1,3).*xim + M(2,3).*yim + M(3,3);

Xworld = u./w ;
Yworld = v./w ;

