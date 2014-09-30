function [sys,x0,str,ts] = stavp_mimoz(t,x,u,flag,n,nin,nout,nz,F,G,H,E,pp)

% NelinSys - a program tool for analysis and synthesis of nonlinear control systems
%            based on MATLAB/Simulink 5.2
%
% (C) 2002-2005, Martin Ondera (Martin.Ondera@gmail.com) (eskimo@pobox.sk)

switch flag,

% =========================== Inicializacna cast s-funkcie  ============================== %
case 0

   % Definicia stavov, vstupov a vystupov nelinearneho systemu %
   sizes = simsizes;
   sizes.NumContStates = n;
   sizes.NumDiscStates = 0;
   sizes.NumOutputs = nout+n;
   sizes.NumInputs = nin+nz;
   sizes.DirFeedthrough = 0;
   sizes.NumSampleTimes = 1;
   sys = simsizes(sizes);

   % Inicializacia pociatocnych podmienok %
   x0 = pp;

   % Inicializacia "str" ako prazdna matica %
   str = [];
   
   % Sample times in TS %
   ts = [0 0];

% ========================== Vypocet podla 1. stavovej rovnice ========================== %
case 1
   sys = eval(sym(F)) + eval(sym(G)) * u(1:nin,:) + eval(sym(E));

% ========================== Vypocet podla 2. stavovej rovnice ========================== %
case 3
   sys(1:nout,:) = eval(sym(H));    % Ako vystup bloku sa berie nielen vystup systemu...  %
   sys(nout+1:nout+n,:) = x;        % ... ale aj cely stavovy vektor nelinearneho systemu %

% ================================= Nepouzite priznaky ================================== %
case {2, 4, 9}
   sys = [];
   
% ================================= Spracovanie chyby =================================== %
otherwise
   error(['Unknown flag = ',num2str(flag)]);
end