clear; clc; close all

A = [1.1269   -0.4940    0.1129,
     1.0000         0         0,
          0    1.0000         0];

B = [-0.3832
      0.5919
      0.5191];

C = [1 0 0];

D = 0;


Plant = ss(A,[B B],C,0,-1,'inputname',{'u' 'w'},'outputname','y');

Q = 2.3; % A number greater than zero

R = 1; % A number greater than zero

[kalmf,L,~,M,Z] = kalman(Plant,Q,R);

kalmf = kalmf(1,:);

M,   % innovation gain