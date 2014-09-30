function [ output_args ] = Fx_Pacejka( Fz, slip )
%FX_PACEJKA Summary of this function goes here
%   Detailed explanation goes here


b0 = 1.65;	 	 
b1 = 0;   	%1/MegaNewton	 	 
b2 = 1100;	 %1/K	 	 
b3 = 0;	 %1/MegaNewton	 	 
b4	= 50; 	%1/K	 	 
b5 = 0;  %	1/KN	 	 
b6 = 0;	   %1/(KN)^2	 	 
b7 = 0; 	%1/KN	 	 
b8 = -10;	 %none	 	 
b9 = 0; 	%1/KN	 	 
b10 = 0;	 %none	 	 
b11 =0;	   %N/kN	Load influence on vertical shift	NYI in Racer; values between -106..142
b12 =0;	  %N	Vertical shift at no load (0 Newton)	NYI in Racer; values between -242..350
D3_EPSILON = 0.0001;

Fz = Fz / 1000;
slipPercentage = slip * 100;

FzSquared = Fz .* Fz;
C = b0;
uP = b1 * Fz + b2;
D = uP .* Fz;
B = zeros(1, size(D, 2));
%avoid div by 0

B(D > -D3_EPSILON & D < D3_EPSILON) = 99999.0;
if (C > -D3_EPSILON && C < D3_EPSILON)
    B = 99999.0 * ones(1, size(B, 2));
end

B(B~=99999.0) = ((b3*FzSquared+b4*Fz).*exp(-b5*Fz))./(C*D);

E = b6 * FzSquared + b7 * Fz + b8;
Sh = b9 * Fz + b10;
Sv = b11 * Fz + b12;


% Max Longitudinal force possible is D + Sv
maxForce = D + Sv;

% Calculate result force

Fx=D.*sin(C*atan(B.*(1.0-E).*(slipPercentage+Sh)+E.*atan(B.*(slipPercentage+Sh))))+Sv;

output_args = [Fx; maxForce];
 

end

