% EXAKT.M - Exact linearization for SISO systems
%           (this m-file is a part of NelinSys, see details below)
%
%  The application carries out computations of state-coordinates
%  transformation as well as nonlinear feedback according to
%  the rules of exact linearization for a Nth-order SISO system
%  described by state equations:  .
%                                 x = f(x) + g(x) u
%                                 y = h(x)
%
%  Symbolic Math Toolbox is used on a large scale. System state variables
%  HAVE TO BE denoted as x1, ..., xN; system input is denoted as "u".
%  The "v" symbol stands for the input of the whole linearization loop
%  i.e. for the input of the exactly linearized system.
%
%  If you need to use other symbols, you have to specify them
%  to the program explicitly before you use them in any expression.
%
% NelinSys - a program tool for analysis and synthesis of nonlinear control systems
%            based on MATLAB/Simulink 5.2
%
% (C) 2002-2005, Martin Ondera (Martin.Ondera@gmail.com) (eskimo@pobox.sk)
%

clc;
clear;
disp('Exact linearization for SISO systems     ');
disp('------------------------------------     ');
disp('                       .                 ');
disp('State-space equations: x = f(x) + g(x) u ');
disp('                       y = h(x)          ');
disp('                                         ');

n = input('System order: ');
disp(' ');

% Definicia symbolov pre stavove premenne %
for k = 1 : n
   eval(sprintf('syms x%d', k));
end

% Definicia symbolov pre vstup sustavy a vstup URO %
syms u v;

% Definicia dalsich symbolov (ak su potrebne) %
s = input('Specify parameters'' identifiers (separated by spaces), if there are any: ', 's');
disp(' ');

if not(isempty(s))
   eval(sprintf('syms %s', s));
end

F = input('System matrix: f(x) = ');
G = input('Input matrix: g(x) = ');
H = input('Output matrix: h(x) = ');
disp(' ');

% Otestovanie spravnosti rozmerov matic F,G,H (podla "n") %
if ~all(size(F) == [n,1])
   disp('ERROR: Invalid matrix dimensions: f(x) - cannot continue!');
   disp(' ');
   return;
end
if ~all(size(G) == [n,1])
   disp('ERROR: Invalid matrix dimensions: g(x) - cannot continue!');
   disp(' ');
   return;
end
if ~all(size(H) == [1,1])
   disp('ERROR: Invalid matrix dimensions: h(x) - cannot continue!');
   disp(' ');
   return;
end

% Vytvorenie vektora x ako x = [x1, x2, ..., xN] kvoli symbolickym operaciam %
x = sym(zeros(1,n));

for k = 1 : n
   x(:,k) = eval(sprintf('x%d',k));
end

% Overenie riaditelnosti systemu (1. podmienka pre pouzitie exaktnej linearizacie) %
Q = sym(zeros(n,n));
Q(:,1) = G;

for k = 2 : n
   Q(:,k) = jacobian(Q(:,k-1),x) * F - jacobian(F,x) * Q(:,k-1);
end

% Ak determinant nie je cislo ale vyraz, nechaj rozhodnutie o riaditelnosti na pouzivatela %
if ~isempty(findsym(det(Q)))
   disp('Controllability: system is controllable if the following expression is nonzero:');
   pretty(simple(det(Q)));

% Ak je determinant ciselny, nenulovy, znamena to, ze system je riaditelny %
elseif (det(Q) ~= 0)
   fprintf('Controllability: system is controllable.\n\n');
   
% Ak je determinant nulovy, system nie je riaditelny => predcasne ukoncit program %
else
   disp('ERROR: Specified system is not controllable!        ');
   disp('       Exact linearization method cannot be applied!');
   disp('                                                    ');
   return;
end

% Relativny stupen systemu - inicializacia %
r = 1;

% Lieove derivovanie vystupu, dovtedy kym Lg == 0 %
syms Lg; Lg(r,:) = jacobian(H,x) * G;
syms Lf; Lf(r,:) = jacobian(H,x) * F;

while (Lg(r,:) == 0)
   r = r + 1;
   
   % Ak r > n a stale plati Lg == 0, metodu nemozno pouzit %
   % Tato situacia by vzhladom na overenu riaditelnost nikdy nemala nastat %
   if (r > n)
      disp('ERROR: Relative degree seems to be higher than system order!');
      disp('       Specified system is possibly not controllable!       ');
      disp('                                                            ');
      return;
   end

   Lg(r,:) = jacobian(Lf(r-1, :), x) * G;
   Lf(r,:) = jacobian(Lf(r-1, :), x) * F;
end

% Vypis transformacnych rovnic pre stavove premenne %
disp('Transformation equations:       ');
disp('                                ');

fprintf(' q1 = '), disp(H);
qx = sprintf('[%s', char(H));

for k = 2 : r
   fprintf(' q%d = ', k), disp(Lf(k-1,:));
   qx = sprintf('%s; %s', qx, char(Lf(k-1,:)));
end

% Vytvorenie transformacnej matice pre pripadnu simulaciu %
qx = sprintf('%s]', qx);

fprintf('Relative degree of the system: %d\n\n', r);
fprintf('Nonlinear feedback: u = \n');

% Vypis nelinearnej spatnej vazby %
u = simple((1 / Lg(r,:)) * (-expand(Lf(r,:)) + v));
pretty(u);

% Vypis varovania pre pripad existencie vnutornej dynamiky %
if (r < n)
   disp(' ');
   disp('WARNING: Relative degree is lower than system order!!!');
   disp('         It is essential to analyze stability of internal dynamics!');
   disp('         In case of instability, results computed above must not be used!!!');
end

% Test, ci F,G,H obsahuju symbolicke konstanty %
premF = strrep(strrep(findsym(sym(F)),', ',''),',',' ');
premG = strrep(strrep(findsym(sym(G)),', ',''),',',' ');
premH = strrep(strrep(findsym(sym(H)),', ',''),',',' ');

% Premenne x1, x2, ..., xN su korektne, preskoc ich %
for k = 1 : n
   premF = strrep(premF, sprintf('x%d',k), '');
   premG = strrep(premG, sprintf('x%d',k), '');
   premH = strrep(premH, sprintf('x%d',k), '');
end

% Otazka na uskutocnenie simulacie, ak F,G,H neobsahuju symbolicke konstanty %
if (isempty(premF) & isempty(premG) & isempty(premH))
   disp(' ');
   simul_ot = input('Do you want to run a simulation of designed control loop? (Y/N) ', 's');
   
   if (simul_ot == 'Y' | simul_ot == 'y')
      open_system('exakt_siso');
   end
end