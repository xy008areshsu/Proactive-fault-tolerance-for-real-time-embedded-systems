function [sys,x0,str,ts] = fazrov_typnl(t,x,u,flag,num,den,w,nelintyp,nelinpar,x1min,x1max,x1num,x2min,x2max,x2num)

% NelinSys - a program tool for analysis and synthesis of nonlinear control systems
%            based on MATLAB/Simulink 5.2
%
% (C) 2002-2005, Martin Ondera (Martin.Ondera@gmail.com) (eskimo@pobox.sk)

switch flag,

% =========================== Inicializacna cast s-funkcie  ============================== %
case 0

   % Inicializacia pociatocnych podmienok %
   if (x1num > 1)
      x1step = (x1max - x1min) / (x1num - 1);
   else
      x1step = 0;
   end

   if (x2num > 1)
      x2step = (x2max - x2min) / (x2num - 1);
   else
      x2step = 0;
   end

   % Definicia stavov, vstupov a vystupov %
   sizes = simsizes;
   sizes.NumContStates = 2 * x1num * x2num + 1;
   sizes.NumDiscStates = 0;
   sizes.NumOutputs = sizes.NumContStates;
   sizes.NumInputs = 0;
   sizes.DirFeedthrough = 0;
   sizes.NumSampleTimes = 1;
   sys = simsizes(sizes);

   % Nastavenie pociatocnych podmienok (PP) pre jednotlive stavy %
   j = 1;
   for k = 0 : (x1num - 1)
      for l = 0 : (x2num - 1)
         x0(j:j+1,:) = [x1min + k*x1step; x2min + l*x2step];
         j = j + 2;
      end
   end
   
   % Posledny stav je len priznak konca simulacie %
   x0(end+1,:) = 0;

   % Inicializacia "str" ako prazdna matica %
   str = [];

   % Sample times in TS %
   ts = [0 0];

% ========================== Vypocet podla 1. stavovej rovnice ========================== %
case 1
   
   % Vypocet pre systemy druheho radu, postupny vypocet x1,x2 pre rozne PP %
   j = 1;
   
   for k = 0 : (x1num - 1)
      for l = 0 : (x2num - 1)
         
         % Vypocet hodnoty "u" podla prevodovej charakteristiky typickej nelinearity %
         switch (nelintyp)
            
            case 1,        % Idealne rele %
               vstup = (w-x(j)<0)*nelinpar(1) + (w-x(j)>=0)*nelinpar(2);
               
            case 2,        % Nasytenie (ohranicenie) %
               tga = (nelinpar(4)-nelinpar(2))/(nelinpar(3)-nelinpar(1));
               q = nelinpar(2) - tga*nelinpar(1);
               vstup = (w-x(j)<=nelinpar(1))*nelinpar(2) + ((w-x(j)>nelinpar(1))&(w-x(j)<nelinpar(3)))*(tga*(w-x(j))+q) + (w-x(j)>=nelinpar(3))*nelinpar(4);

            case 3,        % Rele s necitlivostou %
               vstup = (w-x(j)<=nelinpar(1))*nelinpar(2) + (w-x(j)>=nelinpar(3))*nelinpar(4);
               
            case 4,        % Rele s hytereziou %
               vstup = (w-x(j)<=nelinpar(1))*nelinpar(2) + ((w-x(j)>nelinpar(1))&(w-x(j)<nelinpar(3))&(-x(j+1)>0))*nelinpar(2) + ((w-x(j)>nelinpar(1))&(w-x(j)<nelinpar(3))&(-x(j+1)<=0))*nelinpar(4) + (w-x(j)>=nelinpar(3))*nelinpar(4);
               
			end
            
         sys(j:j+1,:) = [x(j+1); (num*vstup-den(3)*x(j)-den(2)*x(j+1))/den(1)];
         j = j + 2;
      end
   end
   
   % Ak sa riesenie dostalo mimo rozsah, nekresli dalej a nastav priznak konca simulacie %
   if any(isinf(sys)) | any(isnan(sys)) | any(~isreal(sys))
      sys = zeros(size(sys));
      sys(end+1,:) = 1;
   else
      sys(end+1,:) = 0;
   end
   
% ========================== Vypocet podla 2. stavovej rovnice ========================== %
case 3
   % Vystup vektora x1 - hodnoty x1 v danom case pri roznych PP %
   for j = 1 : (x1num * x2num)
      sys(j,:) = x(2*j-1);
   end
   
   % Vystup vektora x2 - hodnoty x2 v danom case pri roznych PP %
   for j = 1 : (x1num * x2num)
      sys(j+(x1num*x2num),:) = x(2*j);
   end
   
   % "Odovzdanie" priznaku konca simulacie na vystup %
   sys(end+1,:) = x(end);

% ================================= Nepouzite priznaky ================================== %
case {2, 4, 9}
   sys = [];

% ================================= Spracovanie chyby =================================== %
otherwise
   error(['Unknown flag = ',num2str(flag)]);
end