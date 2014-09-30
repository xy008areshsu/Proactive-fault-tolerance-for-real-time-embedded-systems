% PROGZOS.M - Gain Scheduling control design for SISO systems
%             (this m-file is a part of NelinSys, see details below)
%
%  The application performs state-space controller design for
%  a SISO system via Gain Scheduling. Design of related
%  parametrized linear controller is based on pole placement
%  technique.
%
%  Symbolic Math Toolbox of MATLAB is used. System state variables
%  HAVE TO BE denoted as x1, ..., xN; system input is denoted as "u"
%  and desired value as "w".
%
%  If you need to use other symbols, you have to specify them
%  to the program explicitly before you use them in an expression.
%
% NelinSys - a program tool for analysis and synthesis of nonlinear control systems
%            based on MATLAB/Simulink 5.2
%
% (C) 2002-2005, Martin Ondera (Martin.Ondera@gmail.com) (eskimo@pobox.sk)
%

clc;
clear;
disp('Gain Scheduling control for SISO systems ');
disp('---------------------------------------- ');
disp('                      .                  ');
disp('Nonlinear system: (1) x = f(x,u)         ');
disp('                      y = h(x,u)         ');
disp('                      .                  ');
disp('                  (2) x = f(x) + g(x) u  ');
disp('                      y = h(x)           ');

disp(' ');
tvar = input('Choose one of the options: ');

if (tvar < 1) | (tvar > 2)
   disp('Invalid option!')
   return;
end

disp(' ');
n = input('System order: ');
disp(' ');

% Definicia symbolov pre stavove premenne %
for k = 1 : n
   eval(sprintf('syms x%d', k));
   x(k,:) = eval(sprintf('x%d', k));
end

% Definicia symbolu "u" pre vstup sustavy a "w" pre ziadanu hodnotu URO %
syms u w;

% Definicia dalsich symbolov (ak su potrebne) %
s = input('Specify parameters'' identifiers (separated by spaces), if there are any: ', 's');
disp(' ');

if ~isempty(s)
   eval(sprintf('syms %s', s))
end;

% Vstup nelinearneho sytemu v symbolickom tvare 1 resp. 2 %
if (tvar == 1)
   F = input('System matrix function: f(x,u) = ');
   H = input('Output matrix function: h(x,u) = ');
else
   F = input('System matrix function: f(x) = ');
   G = input('Input matrix function:  g(x) = ');
   H = input('Output matrix function: h(x) = ');

   % Prepocet f(x) a g(x) na tvar 1 t.j. na f(x,u) %
   F = F + G*u;
end

% Osetrenie vystupu h(x) - musi to byt jedna zo stav. velicin %
if (length(char(H)) ~= 2) | ~strncmp(char(H),'x',1)
   disp(' ');
   disp('Invalid output function of the system!');
   disp('System output must be equal to one of the system state variables!');
   disp(' ');
   return;
end

% Vypis linearizacie - matic A,B,C,D vo vseobecnom tvare %
disp('                        .                 ');
disp('System linearization: /|x = A /|x + B /|u ');
disp('                      /|y = C /|x + D /|u ');
disp('                                          ');

A = jacobian(F,x); disp('A = '); pretty(A)
B = jacobian(F,u); disp('B = '); pretty(B)
C = jacobian(H,x); disp('C = '); pretty(C)
D = jacobian(H,u); disp('D = '); pretty(D)
disp(' ');

% Vytvorenie rovnic pre ustaleny stav systemu z matic f(x,u), h(x,u) %
unknowns = 'x1';
equations = char(F(1));

for k = 2 : n
   unknowns = sprintf('%s,x%d',unknowns,k);
   equations = sprintf('%s,%s',equations,char(F(k)));
end

% Rovnice sa budu riesit vzhladom k neznamym u,x1,...xI-1,xI+1,...,xN kde y = xI %
unknowns = strrep(unknowns,char(H),'u');

% Riesenie rovnic pre rovnovazny stav - vyjadrenie rovn. stavu 1 parametrom %
alfa = solve(equations,unknowns);

% Osetrenie pripadu ked "alfa" nie je typu struct -> preved na struct %
if ~isstruct(alfa)
   pom_alfa = alfa;
   clear alfa;
   alfa.u = pom_alfa;
   clear pom_alfa;
end

% Osetrenie pripadu viacerych rieseni rovnice pre "alfa" %
polozky_alfa = fieldnames(alfa);
if prod(size(eval(sprintf('alfa.%s','u')))) > 1
   
   % Vypis viacerych vyjadreni rovnovaznych stavov systemu pre vyber pouzivatela %
   fprintf('System equilibrium points:\n');
   
   for l = 1 : max(size(eval(sprintf('alfa.%s','u'))))
      fprintf(' (%d) ',l);
      for k = 1 : length(polozky_alfa)
         fprintf('%s = %s',char(polozky_alfa(k)),char(getfield(alfa,char(polozky_alfa(k)),{l})));
         if (k < length(polozky_alfa))
            fprintf(', ');
         else
            fprintf('\n');
         end
      end
   end
   disp(' ');
   
   % Vyber ziadaneho vyjadrenia rovnovaznych stavov %
   while 1,
      vybr_ries = input('Desired equations for system equilibrium points: ');
      
      if (vybr_ries < 1) | (vybr_ries > max(size(eval(sprintf('alfa.%s','u')))))
         disp('Invalid option! Please, select again.');
         disp(' ');
      else
         break;
      end
   end
   
else
   
   % Vypis rovnovaznych stavov systemu vyjadrenych 1 parametrom %
   fprintf('System equilibrium points: ');
   for k = 1 : length(polozky_alfa)
      fprintf('%s = %s',char(polozky_alfa(k)),char(getfield(alfa,char(polozky_alfa(k)))));
      if (k < length(polozky_alfa))
         fprintf(', ');
      else
         fprintf('\n');
      end
   end
   
   % Rovnica pre "alfa" mala len 1 riesenie, zohladni to %
   vybr_ries = 1;
end

knowns = sprintf('alfa.x1(%d)',vybr_ries);
for k = 2 : n
   knowns = sprintf('%s,alfa.x%d(%d)',knowns,k,vybr_ries);
end
knowns = strrep(knowns,char(H),'u');

% Vyjadrenie prvkov matic linearizovaneho systemu pomocou parametra alfa %
A = simple(sym(subs(A,eval(sprintf('{%s}',unknowns)),eval(sprintf('{%s}',knowns)))));
B = simple(sym(subs(B,eval(sprintf('{%s}',unknowns)),eval(sprintf('{%s}',knowns)))));
C = simple(sym(subs(C,eval(sprintf('{%s}',unknowns)),eval(sprintf('{%s}',knowns)))));
D = simple(sym(subs(D,eval(sprintf('{%s}',unknowns)),eval(sprintf('{%s}',knowns)))));

% Vektor stavovej spatnej vazby %
K = sym(zeros(1,n));

for k = 1 : n
   eval(sprintf('syms k%d', k));
   K(k) = eval(sprintf('k%d', k));
end

% Charakteristicky polynom uzavreteho regulacneho obvodu %
ch_pol = char(collect(charpoly(A-B*K,'s_prem'),'s_prem'));

% Navrh regulatora metodou pole-placement %
while 1,
   disp(' ');
   kor = input('Desired poles of the closed-loop system: ');
   
   if (length(kor) ~= n)
      disp('Wrong number of desired poles! Specify again.');
   else
      break;
   end
end

% Ziadany charakteristicky polynom URO %
w_ch_pol = fliplr(poly(kor));

% Porovnanie koeficientov polynomov pri zodpovedajucich mocninach %
unknowns = 'k1';
indx = findstr('s_prem',ch_pol);
rovnica = ch_pol(indx(end)+6:end);
ch_pol = ch_pol(1:indx(end)-2);
equations = sprintf('%s=%d',rovnica,w_ch_pol(1));

for k = 2 : n-1
   unknowns = sprintf('%s,k%d',unknowns,k);
   indx = findstr(sprintf('s_prem^%d',k),ch_pol);
   rovnica = ch_pol(indx+7+length(num2str(k)):end);
   ch_pol = ch_pol(1:indx-2);
   equations = sprintf('%s,%s=%d',equations,rovnica,w_ch_pol(k));
end

if (n > 1)
   unknowns = sprintf('%s,k%d',unknowns,n);
   rovnica = ch_pol(8+length(num2str(n)):end);
   equations = sprintf('%s,%s=%d',equations,rovnica,w_ch_pol(n));
end

% Vektor stavovej spatnej vazby - priradenie konkretnych hodnot %
vektorK = solve(equations,unknowns);

if isstruct(vektorK)
   for k = 1 : n
      K(k) = eval(sprintf('vektorK.k%d',k));
   end
else
   K = vektorK;
end

% Vypocet konstantnej zlozky akcneho zasahu (zodpoveda rovnovaznemu stavu) %
u0 = eval(sprintf('alfa.u(%d)',vybr_ries));

% Parametrizacia hodnot stavovych velicin zodpovedajucich rovnovaznemu stavu %
x0 = sym(zeros(n,1));
for k = 1 : n
   if eval(sprintf('isfield(alfa,''x%d'')',k))
      x0(k) = eval(sprintf('alfa.x%d(%d)',k,vybr_ries));
   else
      x0(k) = eval(sprintf('x%d',k));
   end
end

% Vypocet konstanty predfiltra z podmienok ekvivalencie %
% f0 = simple(diff(u0,char(H)) + K*diff(x0,char(H)));
f0 = simple(1/(C*inv(-(A-B*K))*B));

disp(' ');
disp('Controller for the system linearization: /|u = f0 /|w - K /|x');
disp('f0 = '); pretty(f0);
disp('K = '); pretty(simple(K));

% Vyber programovacej premennej - vstupne, vystupne, zmiesane programovanie %
disp('                                                               ');
disp('Gain Scheduling type: (1) no scheduling (fixed operating point)');
disp('                      (2) input scheduling (w)                 ');
disp('                      (3) output scheduling (y)                ');
disp('                      (4) mixed scheduling (m*w+(1-m)*y)       ');
met_prog = input('Selected scheduling type: ');
disp(' ');

switch (met_prog)
case 1
   prog_param = num2str(input('Fixed operating point: y0 = '));
case 2
   prog_param = char(w);
case 3
   prog_param = char(H);
case 4
   while 1,
      m = input('Scheduling ratio (0<=m<=1): m = ');
      if (m < 0) | (m > 1)
         disp('Scheduling ratio "m" must be from within <0,1> interval!');
         disp(' ');
      else
         break;
      end
   end
   
   prog_param = char(m*w+(1-m)*H);
end

% Nahradenie vystupnej premennej programovacou premennou podla typu programovania %
u0 = subs(u0, char(H), prog_param);
x0 = subs(x0, char(H), prog_param);
w0 = prog_param;

f0 = subs(f0, char(H), prog_param);
K = subs(K, char(H), prog_param);

% Vytvorenie vyrazu pre riadiaci zasah %
u = simple(u0 + f0*(w-w0) - K*(x-x0));

% Vypis riadiaceho zasahu %
disp('Control action: u = ');
pretty(u);

% Test, ci F,G,H obsahuju symbolicke konstanty %
premF = strrep(strrep(findsym(sym(F)),', ',''),',',' ');
premH = strrep(strrep(findsym(sym(H)),', ',''),',',' ');

% Premenne x1, x2, ..., xN, u su korektne, preskoc ich %
for k = 1 : n
   premF = strrep(premF, sprintf('x%d',k), '');
   premH = strrep(premH, sprintf('x%d',k), '');
end

premF = strrep(premF, 'u', '');
premH = strrep(premH, 'u', '');

% Otazka na uskutocnenie simulacie, ak F,G,H neobsahuju symbolicke konstanty %
if (isempty(premF) & isempty(premH)) & (tvar == 2)
   disp(' ');
   simul_ot = input('Do you want to run a simulation of designed control loop? (Y/N) ', 's');
   
   if (simul_ot == 'Y' | simul_ot == 'y')
      F = F-G*sym('u');
      open_system('gssiso');
   end
end