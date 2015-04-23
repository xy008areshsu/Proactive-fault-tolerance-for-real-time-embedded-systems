%% Connect to Pi
% Copyright 2015 The MathWorks, Inc.
C = raspberrypi('169.254.0.31','pi', 'raspberry');
C.connect();

%% Create start script
C.putFile('startModel.sh', '/home/pi');

%% Set script as executable
C.execute('chmod +x startModel.sh');

%% Include script call in rc.local
%   First, remove any auto start that might be there already
%   Use sed to match \n/home/pi/startModel.sh\n in /etc/rc.local
%   Replace with nothing
[status msg] = C.execute('sudo sed -i '':a;N;$!ba;s/\n\/home\/pi\/startModel.sh\n/\n/'' /etc/rc.local');

%   Secondly, match exit 0 and replace with \n/home/pi/startModel.sh\nexit 0
[status msg] = C.execute('sudo sed -i '':a;N;$!ba;s/\nexit 0/\n\/home\/pi\/startModel.sh\nexit 0/'' /etc/rc.local');

%% Sync the Pi so a hard reset won't lose any files

C.execute('sync');