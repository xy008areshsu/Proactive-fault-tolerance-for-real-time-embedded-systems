function [sys,x0,str,ts] = fazrov_auton1(t,x,u,flag,skt,x10)

% NelinSys - a program tool for analysis and synthesis of nonlinear control systems
%            based on MATLAB/Simulink 5.2
%
% (C) 2002-2005, Martin Ondera (Martin.Ondera@gmail.com) (eskimo@pobox.sk)

switch flag,

% =========================== Inicializacna cast s-funkcie  ============================== %
case 0

   % Definicia stavov, vstupov a vystupov %
   sizes = simsizes;
   sizes.NumContStates = length(x10);
   sizes.NumDiscStates = 0;
   sizes.NumOutputs = 2 * sizes.NumContStates + 1;
   sizes.NumInputs = 0;
   sizes.DirFeedthrough = 0;
   sizes.NumSampleTimes = 1;
   sys = simsizes(sizes);
   
   % Nastavenie pociatocnych podmienok (PP) pre x1 %
   x0 = x10';
   
   % Rovnica pre x2 nie je diferencialna => hodnoty x2 treba ukladat inym sposobom %
   for k = 1:length(x10)
      y = x10(k);
      x20(k,:) = eval(skt);
   end
   
   % Posledny vystup je len priznak konca simulacie %
   x20(end+1,:) = 0;
   
   % Ulozenie pociatocnych podmienok pre x2 do parametrov bloku %
   set_param(get_param(gcbh,'Parent'),'UserData',x20);
   
   % Inicializacia "str" ako prazdna matica %
   str = [];
   
   % Sample times in TS %
   ts = [0 0];

% ========================== Vypocet podla 1. stavovej rovnice ========================== %
case 1
   
   % Vypocet pre systemy prveho radu - riesenie obycajnej diferencialnej rovnice %
   for k = 1:length(x10)
      y = x(k);
      sys(k,:) = eval(skt);
   end
   
   % Ak sa riesenie dostalo mimo rozsah, nekresli dalej a nastav priznak konca simulacie %
   if any(isinf(sys)) | any(isnan(sys)) | any(~isreal(sys))
      sys = zeros(size(sys));
      stop_sim = 1;
   else
      stop_sim = 0;
   end
 
   % Rovnica pre x2 je algebraicka rovnica => nemozno pouzit stavy pre ukladanie x2 %
   set_param(get_param(gcbh,'Parent'),'UserData',[sys; stop_sim]);
   
% ========================== Vypocet podla 2. stavovej rovnice ========================== %
case 3
   
   % Vystup hodnot x1 (stavove veliciny) a x2 (nacitaj z parametra bloku) %
   sys = [x; get_param(get_param(gcbh,'Parent'), 'UserData')];
   
% ================================= Nepouzite priznaky ================================== %
case {2, 4, 9}
   sys = [];

% ================================= Spracovanie chyby =================================== %
otherwise
   error(['Unknown flag = ',num2str(flag)]);
end