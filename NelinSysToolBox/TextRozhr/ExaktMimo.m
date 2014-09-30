% EXAKTMIMO.M - Exact linearization for MIMO systems with the same number of inputs and outputs
%               (this m-file is a part of NelinSys, see details below)
%
%  The application carries out computations of state-coordinates
%  transformation as well as nonlinear feedback according to
%  the rules of exact linearization for a Nth-order MIMO system,
%  with the same number of inputs and outputs, described by state
%  equations:  .
%              x = f(x) + g(x) u
%              y = h(x)
%
%  Symbolic Math Toolbox is used on a large scale. System state variables
%  HAVE TO BE denoted as x1, ..., xN, system inputs as u1, ..., uM and
%  inputs of the whole linearization loop as v1, ..., vM.
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
disp('Exact linearization for MIMO systems with the same number of inputs and outputs');
disp('-------------------------------------------------------------------------------');
disp('                       .                                                       ');
disp('State-space equations: x = f(x) + g(x) u                                       ');
disp('                       y = h(x)                                                ');
disp('                                                                               ');

n = input('System order: ');
disp(' ');

% Definicia symbolov pre stavove premenne %
x = sym(zeros(1,n));

for k = 1 : n
   eval(sprintf('syms x%d', k));
   x(:,k) = eval(sprintf('x%d',k));
end

% Definicia dalsich symbolov (ak su potrebne) %
s = input('Specify parameters'' identifiers (separated by spaces), if there are any: ', 's');
disp(' ');

if not(isempty(s))
   eval(sprintf('syms %s', s))
end;

F = input('System matrix: f(x) = ');
G = input('Input matrix:  g(x) = ');
H = input('Output matrix: h(x) = ');
disp(' ');

% Dekodovanie poctu vstupov podla rozmerov matice G %
nin = size(G);
nin = nin(1,2);

% Dekodovanie poctu vystupov podla rozmerov matice H %
nout = size(H);
nout = nout(1,1);

% Ak pocet vstupov a vystupov nie je rovnaky, vyhlas chybu %
if (nin ~= nout)
   disp('ERROR: The number of system inputs is not the same as the number of outputs!');
   disp(' ');
   return;
end

% Vektorovy relativny stupen systemu - inicializacia %
r = ones(1,nout);

% Definicia symbolov pre vstup sustavy a vstup URO %
syms u v;

for k = 1 : nout
   eval(sprintf('syms v%d', k));
   v(k,:) = sprintf('v%d', k);
end

clear Lf Lg;

% Lf = [Lf(h1(x)) ... Lf(hN(x)) ; ... ; Lf^r(h1(x)) ... Lf^r(hN(x))] kde r = max {rI} %
% Lg = [Lg1Lf^(r1-1)(h1(x)) ... LgMLf^(r1-1)(h1(x)) ; ... ; Lg1Lf^(rN-1)(hN(x)) ... LgMLf^(rN-1)(hN(x))] %

% Vypocet Lieovych derivacii pre kazdy vystup h1(x) az hN(x) %
for k = 1 : nout

   % Vypocet Lg = Lieovych derivacii pre k-ty vystup vzhladom k vstupom g1(x) az gM(x) %
   for l = 1 : nin
      Lg(k,l) = jacobian(H(k), x) * G(:,l);
   end

   % Vypocet Lf = Lieovych derivacii pre k-ty vystup vzhladom k f(x) %
   Lf(r(k),k) = jacobian(H(k), x) * F;
end

% Lieove derivacie sa pocitaju dovtedy, kym je matica autonomnosti singularna %
while (det(Lg) == 0)

   % Vypocet Lieovych derivacii pre kazdy vystup h1(x) az hN(x) %
   for k = 1 : nout

      % Derivuj len vtedy, ak sa este doteraz nenarazilo na niektory vstupny signal %
      if (Lg(k,:) == zeros(1,nin))

         % Zvys prislusny relativny stupen o jednotku %
         r(k) = r(k) + 1;

         % Vypocet Lg = Lieovych derivacii vzhladom ku g1(x) az gM(x) %
         for l = 1 : nin
            Lg(k,l) = jacobian(Lf(r(k)-1,k), x) * G(:,l);
         end

         % Vypocet Lf = Lieovych derivacii pre k-ty vystup vzhladom k f(x) %
         Lf(r(k),k) = jacobian(Lf(r(k)-1,k), x) * F;
      end
   end
end

% Overenie riaditelnosti systemu (1. podmienka pre pouzitie exaktnej linearizacie) %
Q = sym(zeros(n,sum(r)));
Q(:,1) = G(:,1);
l = 1; cum_r = cumsum(r);

for k = 2 : sum(r)
   if (k > cum_r(l))
      l = l + 1;
      Q(:,k) = G(:,l);
   else
      Q(:,k) = jacobian(Q(:,k-1),x) * F - jacobian(F,x) * Q(:,k-1);
   end
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

clear b;

% Extrakcia kompenzacneho vektora z Lf %
for k = 1 : nout
   b(k,:) = Lf(r(k),k);
end

% Vypis transformacnych rovnic pre stavove premenne %
disp('Transformation equations:       ');
disp('                                ');

l = 1;
for k = 1 : nout
   if (l == 1)
      fprintf('q%d = %s\n\n', l, char(H(k)));
      qx = sprintf('[%s', char(H(k)));
      l = l + 1;
   else
      fprintf('q%d = %s\n\n', l, char(H(k)));
      qx = sprintf('%s; %s', qx, char(H(k)));
      l = l + 1;
   end

   for q = 2 : r(k)
      fprintf('q%d = %s\n\n', l, char(Lf(q-1,k)));
      qx = sprintf('%s; %s', qx, char(Lf(q-1,k)));
      l = l + 1;
   end
end

% Vytvorenie transformacnej matice pre pripadnu simulaciu %
qx = sprintf('%s]', qx);

% Vypis vektoroveho relativneho stupna systemu %
disp('                                ');
disp('Relative degrees of subsystems: ');
disp(r);

% Vypis linearizacneho vztahu u = u(x,v) %
disp('                        ');
disp('Nonlinear feedback: u = ');

% Vypis nelinearnej spatnej vazby %
u = simple(inv(Lg) * (-expand(b) + v));
pretty(u);

% Vypis varovania pre pripad existencie vnutornej dynamiky %
if (sum(r) < n)
   disp(' ');
   disp('WARNING: Total relative degree is lower than system order!!!');
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
      open_system('exakt_mimo');
   end
end