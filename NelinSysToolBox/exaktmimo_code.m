% NelinSys - a program tool for analysis and synthesis of nonlinear control systems
%            based on MATLAB/Simulink 5.2
%
% (C) 2002-2005, Martin Ondera (Martin.Ondera@gmail.com) (eskimo@pobox.sk)

clear;

% Nacitanie symbolickych matic f(x), g(x) a h(x) %
F = get(findobj(gcf,'Tag','EditF'),'String');
G = get(findobj(gcf,'Tag','EditG'),'String');
H = get(findobj(gcf,'Tag','EditH'),'String');

n = size(sym(F));
n = n(1,1);

% Definicia symbolov pre stavove premenne %
x = sym(zeros(1,n));

% Definicia symbolov pre stavove premenne %
% Vytvorenie vektora x ako x = [x1, x2, ..., xN] kvoli symbolickym operaciam %
for countr = 1 : n
   eval(sprintf('syms x%d', countr));
   x(:,countr) = eval(sprintf('x%d',countr));
end,

% Zisti si symbolicke premenne, ktore vystupuju vo vyrazoch %
premF = strrep(strrep(findsym(sym(F)),', ',''),',',' ');
premG = strrep(strrep(findsym(sym(G)),', ',''),',',' ');
premH = strrep(strrep(findsym(sym(H)),', ',''),',',' ');

% Premenne x1, x2, ..., xN su korektne, preskoc ich %
for countr = 1 : n
   premF = strrep(premF, sprintf('x%d',countr), '');
   premG = strrep(premG, sprintf('x%d',countr), '');
   premH = strrep(premH, sprintf('x%d',countr), '');
end

% Ak niektory retazec nezostal prazdny, vyhlas chybu %
if ~isempty(premF)
   error('Unknown symbol in f(x) expression - cannot continue!');
end
if ~isempty(premG)
   error('Unknown symbol in g(x) expression - cannot continue!');
end
if ~isempty(premH)
   error('Unknown symbol in h(x) expression - cannot continue!');
end

% Pretypovanie retazcov na symbolicke objekty %
F = eval(F); G = eval(G); H = eval(H);

% Dekodovanie poctu vstupov podla rozmerov matice G %
nin = size(G);
nin = nin(1,2);

% Dekodovanie poctu vystupov podla rozmerov matice H %
nout = size(H);
nout = nout(1,1);

% Ak pocet vstupov a vystupov nie je rovnaky, vyhlas chybu %
if (nin ~= nout)
   error('ERROR: The number of system inputs is not the same as the number of outputs!');
end

% Otestovanie spravnosti rozmerov matic F,G,H (podla "n") %
if ~all(size(F) == [n,1])
   error('Invalid dimensions of f(x) matrix - cannot continue!');
end
if ~all(size(G) == [n,nin])
   error('Invalid dimensions of g(x) matrix - cannot continue!');
end
if ~all(size(H) == [nout,1])
   error('Invalid dimensions of h(x) matrix - cannot continue!');
end

% Definicia symbolov pre vstup sustavy a vstup URO %
syms u v;

for k = 1 : nout
   eval(sprintf('syms v%d', k));
   v(k,:) = sprintf('v%d', k);
end,

% Relativne stupne systemu %
r = ones(1,nout);

clear Lf Lg;

% Lf = [Lf(h1(x)) ... Lf(hN(x)) ; ... ; Lf^r(h1(x)) ... Lf^r(hN(x))] kde r = max {rI} %
% Lg = [Lg1Lf^(r1-1)(h1(x)) ... LgMLf^(r1-1)(h1(x)) ; ... ; Lg1Lf^(rN-1)(hN(x)) ... LgMLf^(rN-1)(hN(x))] %

% Vypocet Lieovych derivacii pre kazdy vystup h1(x) az hN(x) %
for k = 1 : nout

   % Vypocet Lg = Lieovych derivacii pre k-ty vystup vzhladom k vstupom g1(x) az gM(x) %
   for l = 1 : nin
      Lg(k,l) = jacobian(H(k), x) * G(:,l);
   end,

   % Vypocet Lf = Lieovych derivacii pre k-ty vystup vzhladom k f(x) %
   Lf(r(k),k) = jacobian(H(k), x) * F;
end,

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
         end,

         % Vypocet Lf = Lieovych derivacii pre k-ty vystup vzhladom k f(x) %
         Lf(r(k),k) = jacobian(Lf(r(k)-1,k), x) * F;
      end,
   end,
end,

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
   end,
end,

% Ak determinant nie je cislo ale vyraz, nechaj rozhodnutie o riaditelnosti na pouzivatela %
if ~isempty(findsym(det(Q)))
   set(findobj(gcf,'Tag','TextRiaditelnost'),'String','System is controllable if following expression is nonzero:');
   set(findobj(gcf,'Tag','EditRiaditelnost'),'Visible','on','String',char(simple(det(Q))));
   set(findobj(gcf,'Tag','BtnVystupR'),'Visible','on','Enable','on');

% Ak je determinant ciselny, nenulovy, znamena to, ze system je riaditelny %
elseif (det(Q) ~= 0)
   set(findobj(gcf,'Tag','TextRiaditelnost'),'String','System is controllable.');
   set(findobj(gcf,'Tag','EditRiaditelnost'),'Visible','off');
   set(findobj(gcf,'Tag','BtnVystupR'),'Visible','off','Enable','off');
   
% Ak je determinant nulovy, system nie je riaditelny => predcasne ukoncit program %
else
   set(findobj(gcf,'Tag','TextRiaditelnost'),'String','System is not controllable! The method cannot be applied.');
   set(findobj(gcf,'Tag','EditRiaditelnost'),'Visible','off');
   set(findobj(gcf,'Tag','BtnVystupR'),'Visible','off','Enable','off');

   set(findobj(gcf,'Tag','BtnVystup1'),'Enable','off');
   set(findobj(gcf,'Tag','BtnVystup2'),'Enable','off');

   set(findobj(gcf,'Tag','ListboxTransf'),'String','');
   set(findobj(gcf,'Tag','EditLinVztah'),'String','');
   set(findobj(gcf,'Tag','TextVnutDyn'),'ForegroundColor',[0 0 0],'String','');
   set(findobj(gcf,'Tag','BtnSimulacia'),'Enable','off');

   return;
end,

l = 1;
for k = 1 : nout
   if (l == 1)
      trnsf = sprintf('q%d = %s', l, char(H(k)));
      qx = sprintf('[%s', char(H(k)));
   else
      l = l + 1;
      trnsf = sprintf('%s|q%d = %s', trnsf, l, char(H(k)));
      qx = sprintf('%s; %s', qx, char(H(k)));
   end,

   for q = 2 : r(k)
      l = l + 1;
      trnsf = sprintf('%s|q%d = %s', trnsf, l, char(Lf(q-1,k)));
      qx = sprintf('%s; %s', qx, char(Lf(q-1,k)));
   end,
end,
qx = sprintf('%s]', qx);

set(findobj(gcf,'Tag','ListboxTransf'),'String',trnsf);

% Extrakcia kompenzacneho vektora z Lf %
for k = 1 : nout
   b(k,:) = Lf(r(k),k);
end,

% Vypocet nelinearnej spatnej vazby (linearizacneho vztahu) %
u = simple(inv(Lg) * (-expand(b) + v));

u_str = sprintf('[%s', char(u(1)));
for k = 2 : nin
   u_str = sprintf('%s; %s', u_str, char(u(k)));
end,
u_str = sprintf('%s]', u_str);

set(findobj(gcf,'Tag','EditLinVztah'),'String',u_str);

% Vypis varovania pre pripad existencie vnutornej dynamiky %
if (sum(r) < n)
   set(findobj(gcf,'Tag','TextVnutDyn'),'ForegroundColor',[1 0 0],'String',['Total relative degree (',num2str(sum(r)),') is lower than system order (',num2str(n),')! It is essential to analyze zero dynamics!']);
else
   set(findobj(gcf,'Tag','TextVnutDyn'),'ForegroundColor',[0 0 0],'String','Relative degree is equal to system order, therefore, no internal dynamics is present.');
end,

% Spristupnenie tlacidiel "pretty" pre vypis do Command Window %
set(findobj(gcf,'Tag','BtnVystup1'),'Enable','on');
set(findobj(gcf,'Tag','BtnVystup2'),'Enable','on');

% Spristupnenie tlacidla "Simulacia" pre otvorenie simulacnej schemy %
set(findobj(gcf,'Tag','BtnSimulacia'),'Enable','on');