clear all
close all

% define s
s = tf('s');

% define 2 x 2 control matrix in s-domain (continuous)
G11 = 2/((5*s+1)*(2*s+1))*exp(-6*s);
G12 = -1/((4*s+1)*(2*s+1));
G21 = 2/((4*s+1)*(2*s+1))*exp(-4*s);
G22 = 4/((2*s+1)*(s+1)^3)*exp(-3*s);

% overall transfer function
Gc = [G11 G12;...
      G21 G22];

% get step response
figure(1)
step(Gc)

% convert to discrete form with 1 second sampling (z-domain)
Gd = c2d(Gc,1);
hold on
step(Gd)

% convert to state space
sys = absorbDelay(ss(Gd));
step(sys)

% extract A, B, C, D matrices in sparse form
[n,m] = size(sys.B);
[p,m] = size(sys.D);

[ai,aj,av] = find(sparse(sys.A));
a = [ai,aj,av]';
[bi,bj,bv] = find(sparse(sys.B));
b = [bi,bj,bv]';
[ci,cj,cv] = find(sparse(sys.C));
c = [ci,cj,cv]';
[di,dj,dv] = find(sparse(sys.D));
d = [di,dj,dv]';
if(size(d,2)==0),
    d = [1,1,0]';
end

fid = fopen('lti.apm','w');
fprintf( fid,'\n');
fprintf( fid,'Objects \n');
fprintf( fid,'  sys = lti\n');
fprintf( fid,'End Objects \n');
fprintf( fid,'\n');
fprintf( fid,'Connections\n');
fprintf( fid,'  u[1:%d] = sys.u[1:%d]\n',m,m);
fprintf( fid,'  x[1:%d] = sys.x[1:%d]\n',n,n);
fprintf( fid,'  y[1:%d] = sys.y[1:%d]\n',p,p);
fprintf( fid,'End Connections\n');
fprintf( fid,'\n');
fprintf( fid,'Model \n');
fprintf( fid,'  Parameters \n');
fprintf( fid,'    u[1:%d] = 0\n',m);
fprintf( fid,'  End Parameters \n');
fprintf( fid,'\n');
fprintf( fid,'  Variables \n');
fprintf( fid,'    x[1:%d] = 0\n',n);
fprintf( fid,'    y[1:%d] = 0\n',p);
fprintf( fid,'  End Variables \n');
fprintf( fid,'\n');
fprintf( fid,'  Equations \n');
fprintf( fid,'    ! add any additional equations here \n');
fprintf( fid,'  End Equations \n');
fprintf( fid,'End Model \n');
fprintf( fid,'\n');
fprintf( fid,'! dimensions\n');
fprintf( fid,'! (nx1) = (nxn)*(nx1) + (nxm)*(mx1)\n');
fprintf( fid,'! (px1) = (pxn)*(nx1) + (pxm)*(mx1)\n');
fprintf( fid,'!\n');
fprintf( fid,'! discrete form\n');
fprintf( fid,'! x[k+1] = A * x[k] + B * u[k]\n');
fprintf( fid,'!   y[k] = C * x[k] + D * u[k]\n');
fprintf( fid,'File sys.txt\n');
fprintf( fid,'  sparse, discrete  ! dense/sparse, continuous/discrete\n');
fprintf( fid,'  %d      ! m=number of inputs\n',m);
fprintf( fid,'  %d      ! n=number of states\n',n);
fprintf( fid,'  %d      ! p=number of outputs\n',p);
fprintf( fid,'End File\n');
fprintf( fid,'\n');
fprintf( fid,'File sys.a.txt \n');
fprintf( fid,'   %d %d %f\n', a );
fprintf( fid,'End File \n');
fprintf( fid,'\n');
fprintf( fid,'File sys.b.txt \n');
fprintf( fid,'   %d %d %f\n', b );
fprintf( fid,'End File \n');
fprintf( fid,'\n');
fprintf( fid,'File sys.c.txt \n');
fprintf( fid,'   %d %d %f\n', c );
fprintf( fid,'End File \n');
fprintf( fid,'\n');
fprintf( fid,'File sys.d.txt \n');
fprintf( fid,'   %d %d %f\n', d );
fprintf( fid,'End File \n');
fclose(fid);

save dimensions.mat n m p
