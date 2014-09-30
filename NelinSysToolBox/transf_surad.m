function [sys,x0,str,ts] = transf_surad(t,x,u,flag,n,r,Z)

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
   sizes.NumOutputs = r;
   sizes.NumInputs = n;
   sizes.DirFeedthrough = 1;
   sizes.NumSampleTimes = 1;
   sys = simsizes(sizes);

   % Inicializacia pociatocnych podmienok %
   x0 = [];

   % Inicializacia "str" ako prazdna matica %
   str = [];
   
   % Sample times in TS %
   ts = [0 0];

% ========================= Vypocet podla transformacnej rovnice ======================== %
case 3
   sys = eval(sym(Z));
   
   for k = 1 : r
      if ~isreal(sys(k,:))
         error(['At the time instant t = ',num2str(t),'s, the state-coordinates transformation is not defined! Cannot continue the simulation!']);
         % sys(k,:) = 0;
      end
   end

% ================================= Nepouzite priznaky ================================== %
case {1, 2, 4, 9}
   sys = [];
   
% ================================= Spracovanie chyby =================================== %
otherwise
   error(['Unknown flag = ',num2str(flag)]);
end