% Add path to APM libraries
addpath('./apm');

% Clear MATLAB
clear all
close all

% retrieve n,m,p sizes
% n = # of states
% m = # of inputs
% p = # of outputs
load dimensions.mat

% Select server
server = 'http://xps.apmonitor.com';

% Application
app = 'control';

% Clear previous application
apm(server,app,'clear all');

% load model variables and equations
apm_load(server,app,'lti.apm');

% load data
csv_load(server,app,'control.csv');

% Set up variable classifications for data flow

% Feedforwards - measured process disturbances
% No parameters
% apm_info(server,app,'FV','gamma[1]');
% Manipulated variables
for i = 1:m,
  v = ['u[' int2str(i) ']'];
  apm_info(server,app,'MV',v);
end
% State variables (for display only)
for i = 1:n,
  v = ['x[' int2str(i) ']'];
  apm_info(server,app,'SV',v);
end
% Controlled variables
for i = 1:p,
  v = ['y[' int2str(i) ']'];
  apm_info(server,app,'CV',v);
end

% imode = 6, switch to dynamic control
apm_option(server,app,'nlc.imode',6);
% time units (1=sec, 2=min, 3=hr, etc.)
apm_option(server,app,'nlc.ctrl_units',1);
apm_option(server,app,'nlc.hist_units',2);
% read csv file
apm_option(server,app,'nlc.csv_read',1);

% Manipulated variables
apm_option(server,app,'u[1].status',1);
apm_option(server,app,'u[1].upper',100);
apm_option(server,app,'u[1].lower',0);
apm_option(server,app,'u[1].dmax',10);
apm_option(server,app,'u[1].dcost',0.1);

apm_option(server,app,'u[2].status',1);
apm_option(server,app,'u[2].upper',100);
apm_option(server,app,'u[2].lower',0);
apm_option(server,app,'u[2].dmax',10);
apm_option(server,app,'u[2].dcost',0.1);

% Controlled variables
apm_option(server,app,'y[1].status',1);
apm_option(server,app,'y[1].fstatus',1);
apm_option(server,app,'y[1].sphi',10.1);
apm_option(server,app,'y[1].splo',9.9);
apm_option(server,app,'y[1].tau',10);
apm_option(server,app,'y[1].tr_open',10);

apm_option(server,app,'y[2].status',1);
apm_option(server,app,'y[2].fstatus',1);
apm_option(server,app,'y[2].sphi',15.1);
apm_option(server,app,'y[2].splo',14.9);
apm_option(server,app,'y[2].tau',10);
apm_option(server,app,'y[2].tr_open',10);

% Set controller mode
apm_option(server,app,'nlc.reqctrlmode',3);

% Run APMonitor
apm(server,app,'solve')

% Open web-viewer
apm_web(server,app);
