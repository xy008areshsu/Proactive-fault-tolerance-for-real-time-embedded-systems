% Copyright 2015 The MathWorks, Inc.
[pcam,lcam]=camera(41);
targets_x = [10 45 65 55];
targets_y = [10 50 25 10];
[x,y] = world2robot(50,50,-90,targets_x,targets_y);
[dist,bearing] = isincamera(pcam,lcam,x,y);