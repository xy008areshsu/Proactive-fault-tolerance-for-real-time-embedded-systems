% NelinSys - a program tool for analysis and synthesis of nonlinear control systems
%            based on MATLAB/Simulink 5.2
%
% (C) 2002-2005, Martin Ondera (Martin.Ondera@gmail.com) (eskimo@pobox.sk)

% Nacitanie symbolickych matic f(x), g(x) a h(x) %
F = get(findobj(gcf,'Tag','EditF'),'String');
G = get(findobj(gcf,'Tag','EditG'),'String');
H = get(findobj(gcf,'Tag','EditH'),'String');

n = size(sym(F));
n = n(1,1);

% Definicia symbolov pre stavove premenne %
for countr = 1 : n
   eval(sprintf('syms x%d', countr));
end

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

% Otestovanie spravnosti rozmerov matic F,G,H (podla "n") %
if ~all(size(F) == [n,1])
   error('Invalid dimensions of f(x) matrix - cannot continue!');
end
if ~all(size(G) == [n,1])
   error('Invalid dimensions of g(x) matrix - cannot continue!');
end
if ~all(size(H) == [1,1])
   error('Invalid dimensions of h(x) matrix - cannot continue!');
end

% Definicia symbolov pre vstup sustavy a vstup URO %
syms u v;

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
end

% Relativny stupen systemu %
r = 1;

% Lieove derivovanie vystupu, dovtedy kym Lg == 0 %
syms Lg; Lg(r,:) = jacobian(H,x) * G;
syms Lf; Lf(r,:) = jacobian(H,x) * F;

while (Lg(r,:) == 0)
   r = r + 1;

   Lg(r,:) = jacobian(Lf(r-1, :), x) * G;
   Lf(r,:) = jacobian(Lf(r-1, :), x) * F;
end

% Vypis transformacnych rovnic pre stavove veliciny %
trnsf = sprintf(' q1 = %s', char(H));
qx = sprintf('[%s', char(H));

for k = 2 : r
   trnsf = sprintf('%s| q%d = %s', trnsf, k, char(Lf(k-1,:)));
   qx = sprintf('%s; %s', qx, char(Lf(k-1,:)));
end,
qx = sprintf('%s]', qx);

set(findobj(gcf,'Tag','ListboxTransf'),'String',trnsf);

% Vypis nelinearnej spatnej vazby (linearizacneho vztahu) %
u = simple((1 / Lg(r,:)) * (-expand(Lf(r,:)) + v));
set(findobj(gcf,'Tag','EditLinVztah'),'String',char(u));

% Vypis varovania pre pripad existencie vnutornej dynamiky %
if (r < n)
   set(findobj(gcf,'Tag','TextVnutDyn'),'ForegroundColor',[1 0 0],'String',['Relative degree (',num2str(r),') is lower than system order (',num2str(n),')! It is essential to analyze zero dynamics stability!']);
else
   set(findobj(gcf,'Tag','TextVnutDyn'),'ForegroundColor',[0 0 0],'String','Relative degree is equal to system order, therefore, no internal dynamics is present.');
end

% Spristupnenie tlacidiel "pretty" pre vypis do Command Window %
set(findobj(gcf,'Tag','BtnVystup1'),'Enable','on');
set(findobj(gcf,'Tag','BtnVystup2'),'Enable','on');

% Spristupnenie tlacidla "Simulacia" pre otvorenie simulacnej schemy %
set(findobj(gcf,'Tag','BtnSimulacia'),'Enable','on');