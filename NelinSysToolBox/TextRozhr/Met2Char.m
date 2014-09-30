% MET2CHAR.M - Two-Characteristics Method (Analysis of limit cycles via Harmonic Balance)
%              (this m-file is a part of NelinSys, see details below)
%
%  The application performs limit cycle analysis of a given nonlinear system
%  via harmonic balance (so-called Two-Characteristics Method). The harmonic
%  balance equation is solved graphically (by plotting the characteristics in
%  complex plane) as well as analytically (with a help of Symbolic Math Toolbox).
%
%  The axes settings as well as the range of the characteristics can be set by user.
%  Analytical solution of the harmonic-balance equation
%
%                          1       F(w)  - frequency characteristics
%               F(w) = - -------   Fe(a) - describing function of the nonlinearity
%                         Fe(a)
%
%  is carried out through the "solve" command.
%
% NelinSys - a program tool for analysis and synthesis of nonlinear control systems
%            based on MATLAB/Simulink 5.2
%
% (C) 2002-2005, Martin Ondera (Martin.Ondera@gmail.com) (eskimo@pobox.sk)
%

clc
clear all
disp('                                                                       ')
disp('HARMONIC BALANCE, ANALYSIS OF LIMIT CYCLES (Two-Characteristics Method)')
disp('                                                                       ')
disp('-------- Linear part of the system --------                            ')
disp('                                                                       ')

num = input('Transfer function - numerator: ');
den = input('Transfer function - denominator: ');

% Zobrazenie prenosovej funkcie systemu %
sys = tf(num,den)

% Nacitanie rozsahu hodnot omega, pre ktore sa bude kreslit F(iw) %
wmin = input('Minimum frequency "w": ');
wmax = input('Maximum frequency "w": ');
wstep = input('Frequency step size: ');

% Vytvorenie rovnomerne odstupnovaneho vektora w %
w = wmin:wstep:wmax;

% Vypocet frekvencnej charakteristiky F(iw) %
F = freqresp(sys,w);

disp(' ')
disp('-------------- Nonlinearity -------------')
disp(' ')
disp(' 1 - ideal relay                         ')
disp(' 2 - relay with dead-zone                ')
disp(' 3 - relay with hysteresis               ')
disp(' 4 - saturation                          ')
disp(' ')

n = input('Chosen nonlinearity: ');
disp(' ')

% ---------- Nacitanie konstant popisujucich nelinearitu -----------
switch n
   
case 1  % Idealne rele
	while 1,
		k = input('Relay gain: K = ');
   
		% Test spravnosti zadanych udajov %
		if (k <= 0)
			disp('Invalid value! K must be positive.')
			disp(' ')
		else
			break;
		end
	end
   
case 2  % Rele s necitlivostou
	while 1,
		k = input('Relay gain: K = ');
		b1 = input('Dead-zone: B = ');

		% Test spravnosti zadanych udajov %
		if (k <= 0 | b1 < 0)
			disp('Invalid value! K must be positive and B nonnegative.')
			disp(' ')
		else
			break;
		end
	end
   
case 3  % Rele s hystereziou
	while 1,
		k = input('Relay gain: K = ');
		b1 = input('Hysteresis: B = ');

		% Test spravnosti zadanych udajov %
		if (k <= 0 | b1 < 0)
			disp('Invalid value! K must be positive and B nonnegative.')
			disp(' ')
		else
			break;
		end
	end
   
case 4  % Charakteristika nasytenia (ohranicenia)
	while 1,
		k = input('Saturation value: K = ');
		b1 = input('Saturating point: B = ');

		% Test spravnosti zadanych udajov %
		if (k <= 0 | b1 <= 0)
			disp('Invalid value! Both K and B must be positive.')
			disp(' ')
		else
			break;
		end
	end
end
disp(' ')

% Nacitanie rozsahu hodnot amplitudy A, pre ktore sa bude kreslit -1/Fe(A) %
Amin = input('Minimum amplitude: ');
Amax = input('Maximum amplitude: ');
Astep = input('Amplitude step size: ');

% Vytvorenie rovnomerne odstupnovaneho vektora A %
A = Amin:Astep:Amax;

% Definovanie symbolickych premennych pre analyticky vypocet MC %
syms a v real;

% Vypocet ekvivalentneho prenosu nelinearity %
switch n,

case 1 % Idealne rele
   Re = 4*k./(A*pi);
   Im = zeros(size(A));
   
   Ga = simple(4*k/(a*pi));
   
case 2 % Rele s necitlivostou
   Re = 4*k./(A*pi).*sqrt(1-b1^2./A.^2);
   Im = zeros(size(A));
   
   Ga = simple(4*k/(a*pi)*sqrt(1-b1^2/a^2));
   
case 3 % Rele s hystereziou
   Re = 4*k./(A*pi).*sqrt(1-b1^2./A.^2);
   Im = -4*b1*k./(A.^2*pi);
   
   Ga = simple(4*k/(a*pi)*sqrt(1-b1^2/a^2) + sqrt(-1)*(-4*b1*k/(a^2*pi)));

case 4 % Charakteristika nasytenia
   Re = 2*k/pi.*(asin(b1./A)+b1./A.*sqrt(1-b1^2./A.^2));
   Im = zeros(size(A));
   
   Ga = simple(2*k/pi*(asin(b1/a)+b1/a*sqrt(1-b1^2/a^2)));
   
end

% Frekvencny prenos v analytickom tvare %
Gw = simple(poly2sym(num,sqrt(-1)*v)/poly2sym(den,sqrt(-1)*v));

% Vykreslenie (Nyquistovej) frekvencnej charakteristiky linearnej casti %
figure; hold on;
plot(reshape(real(F),length(F),1),reshape(imag(F),length(F),1),'b');

% Vykreslenie charakteristiky -1/G %
plot(-Re./(Re.^2+Im.^2),Im./(Re.^2+Im.^2),'r');

% Okomentovanie grafu, popis osi, atd. %
grid; title('Harmonic balance - limit cycle analysis');
xlabel('Re'); ylabel('Im');

disp(' ')
disp('-------- Graphical solution --------')
disp(' ')
disp('Frequency characteristic of the linear part is plotted in blue colour.')
disp('Characteristic corresponding to the nonlinearity is plotted in red colour.');
disp(' ')
disp('The number of intersections of these two characteristics determines the number of limit cycles.');
disp(' ')

% Zmena zobrazenia grafu kvoli detailom %
ot_zobr = input('Do you want to change axes settings? (Y/N) ', 's');

if (ot_zobr == 'Y') | (ot_zobr == 'y')
   while 1,
      rozsah_zobr = input('Specify new settings: [Re-min, Re-max, Im-min, Im-max] = ');
      
      if (length(rozsah_zobr) ~= 4) | (rozsah_zobr(2) < rozsah_zobr(1)) | (rozsah_zobr(4) < rozsah_zobr(3))
         disp('Invalid axes settings!')
         disp(' ');
      else
         axis(rozsah_zobr);
         figure(gcf);
         break;
      end
   end
end

% Vypis pokynov pre vyhodnotenie stability %
disp(' ')
disp('-------- Stability evaluation --------')
disp(' ')
disp('The rule: a limit cycle is stable if the characteristic corresponding to the nonlinearity');
disp('          (the red one) crosses the frequency characteristic (the blue one) from right to left');
disp('          (in terms of increasing values of "w").')
disp(' ')

FwRe = reshape(real(F),length(F),1); FwIm = reshape(imag(F),length(F),1);
GaRe = -Re./(Re.^2+Im.^2); GaIm = Im./(Re.^2+Im.^2);

fprintf('Beginning of the frequency characteristic: w = %f, Re(Fw) = %f, Im(Fw) = %f\n',wmin,FwRe(1),FwIm(1));
fprintf('End of frequency characteristic: w = %f, Re(Fw) = %f, Im(Fw) = %f\n\n',wmax,FwRe(end),FwIm(end));
fprintf('Beginning of the nonlinearity characteristic: A = %f, Re(-1/Fa) = %f, Im(-1/Fa) = %f\n',Amin,GaRe(1),GaIm(1));
fprintf('End of the nonlinearity characteristic A = %f, Re(-1/Fa) = %f, Im(-1/Fa) = %f\n\n',Amax,GaRe(end),GaIm(end));

% Analyticky vypocet medznych cyklov %
mc = solve(real(Gw*Ga)+1,imag(Gw*Ga),'v,a');

disp(' ')
disp('-------- Analytical solution --------')
disp(' ')

% Vypis vysledku analytickeho vypoctu medznych cyklov %
if ~isempty(mc)
   disp('Calculated limit cycle parameters:')
   
   l = 0;
   for k = 1 : length(mc.a)
      if (double(mc.a(k)) > 0) & (double(mc.v(k)) > 0)
         fprintf(' Amplitude: a = %.5f, Frequency: w = %.5f\n', double(mc.a(k)), double(mc.v(k)));
         l = l + 1;
      end
   end
   
   if (l == 0)
      disp('There are no limit cycles!')
   end
   
% Ak sa analyticky vypocet nepodaril %
else
   disp('Unfortunately, Symbolic Math Toolbox was unable to solve the harmonic balance equation.');
   disp(' ');
   disp('Harmonic balance - condition for existence of a limit cycle:'); pretty(subs(simple(Gw*Ga+1),'v',sym('w')))
   disp(' given expression must be equal to zero.')
end

disp(' ')