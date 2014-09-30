% NelinSys - a program tool for analysis and synthesis of nonlinear control systems
%            based on MATLAB/Simulink 5.2
%
% (C) 2002-2005, Martin Ondera (Martin.Ondera@gmail.com) (eskimo@pobox.sk)

clear;

% V pripade viacerych moznosti rovnovaznych stavov sa bude pocitat s prvym z nich %
set(findobj(gcf,'Tag','ListboxRovnovs'),'Value',1);
vybr_ries = 1;

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

% Definicia symbolov pre stavove premenne %
for countr = 1 : n
   eval(sprintf('syms x%d', countr));
   x(countr,:) = eval(sprintf('x%d', countr));
end

% Definicia symbolu "u" pre vstup sustavy a "w" pre ziadanu hodnotu URO %
syms u w;

% Prepocet f(x) a g(x) na tvar 1 t.j. na f(x,u) %
F = F + G*u;

% Korene ziadaneho polynomu URO %
kor = get(findobj(gcf,'Tag','EditPoly'),'String');

if isempty(kor) | (length(eval(kor)) ~= n)
   error('Wrong number of desired poles - cannot continue!');
else
   kor = eval(kor);
end

% Typ programovania - vstupne, vystupne, zmiesane %
met_prog = get(findobj(gcf,'Tag','PopupTypprog'),'Value');

switch (met_prog)
case 1
   prog_param = get(findobj(gcf,'Tag','EditPracBod'),'String');
   if isempty(prog_param)
     error('Fixed operating point not specified - cannot continue!');
   end
case 2
   prog_param = char(w);
case 3
   prog_param = char(H);
case 4
   m = eval(get(findobj(gcf,'Tag','EditPracBod'),'String'));
   if (m < 0) | (m > 1)
      error('Scheduling ratio "m" must be from within <0,1> interval - cannot continue!');
   end
   
   prog_param = char(m*w+(1-m)*H);
end

% Osetrenie vystupu h(x) - musi to byt jedna zo stav. velicin %
if (length(char(H)) ~= 2) | ~strncmp(char(H),'x',1)
   error('Invalid output function of the system! System output must be equal to one of the system state variables!');
end

A = jacobian(F,x);
B = jacobian(F,u);
C = jacobian(H,x);
D = jacobian(H,u);

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
   
   for l = 1 : max(size(eval(sprintf('alfa.%s','u'))))
      rovnovs = '';
      for k = 1 : length(polozky_alfa)
         rovnovs = sprintf('%s %s = %s',rovnovs,char(polozky_alfa(k)),char(getfield(alfa,char(polozky_alfa(k)),{l})));
         if (k < length(polozky_alfa))
            rovnovs = sprintf('%s,',rovnovs);
         end
      end
      if (l < max(size(eval(sprintf('alfa.%s','u')))))
         rovnovs = sprintf('%s| ',rovnovs);
      end
   end
   
else
   
   rovnovs = '';
   for k = 1 : length(polozky_alfa)
      rovnovs = sprintf('%s %s = %s',rovnovs,char(polozky_alfa(k)),char(getfield(alfa,char(polozky_alfa(k)))));
      if (k < length(polozky_alfa))
         rovnovs = sprintf('%s,',rovnovs);
      end
   end
   
end

% Vypis rovnovaznych stavov do Listboxu %
set(findobj(gcf,'Tag','ListboxRovnovs'),'String',rovnovs,'Enable','on');

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
ch_pol = char(collect(poly(A-B*K,'s_prem'),'s_prem'));

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

% Nahradenie vystupnej premennej programovacou premennou podla typu programovania %
u0 = subs(u0, char(H), prog_param);
x0 = subs(x0, char(H), prog_param);
w0 = prog_param;

f0 = subs(f0, char(H), prog_param);
K = subs(K, char(H), prog_param);

% Vytvorenie vyrazu pre riadiaci zasah %
u = simple(u0 + f0*(w-w0) - K*(x-x0));

% Vypis riadiaceho zasahu %
set(findobj(gcf,'Tag','EditAkcZasah'),'String',char(u));

% Spristupnenie tlacidla "pretty" pre vypis do Command Window %
set(findobj(gcf,'Tag','BtnVystup'),'Enable','on');

% Spristupnenie tlacidla "Simulacia" pre otvorenie simulacnej schemy %
set(findobj(gcf,'Tag','BtnSimulacia'),'Enable','on');

% Znovunacitanie matic F,G,H kvoli simulacnej scheme %
F = get(findobj(gcf,'Tag','EditF'),'String');
G = get(findobj(gcf,'Tag','EditG'),'String');
H = get(findobj(gcf,'Tag','EditH'),'String');

F = eval(F); G = eval(G); H = eval(H);