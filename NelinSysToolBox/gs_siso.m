function [sys,x0,str,ts] = gs_siso(t,x,u,flag,n,vzorec)

% NelinSys - a program tool for analysis and synthesis of nonlinear control systems
%            based on MATLAB/Simulink 5.2
%
% (C) 2002-2005, Martin Ondera (Martin.Ondera@gmail.com) (eskimo@pobox.sk)

switch flag,

% =========================== Inicializacna cast s-funkcie  ============================== %
case 0

   % Definicia stavov, vstupov a vystupov systemu %
   sizes = simsizes;
   sizes.NumContStates = 0;
   sizes.NumDiscStates = 0;
   sizes.NumOutputs = 1;
   sizes.NumInputs = n+1;
   sizes.DirFeedthrough = 1;
   sizes.NumSampleTimes = 1;
   sys = simsizes(sizes);

   % Inicializacia pociatocnych podmienok %
   x0 = [];

   % Inicializacia "str" ako prazdna matica %
   str = [];
   
   % Sample times in TS %
   ts = [0 0];

% ========================== Vypocet podla linearizacnej rovnice ======================== %
case 3
   sys = eval(vzorec);
   
   if ~isreal(sys)
      error(['At the time instant t = ',num2str(t),'s, the control action of the regulator is not defined! Cannot continue the simulation!']);
   end

% ================================= Nepouzite priznaky ================================== %
case {1, 2, 4, 9}
   sys = [];
   
% ================================= Spracovanie chyby =================================== %
otherwise
   error(['Unknown flag = ',num2str(flag)]);
end