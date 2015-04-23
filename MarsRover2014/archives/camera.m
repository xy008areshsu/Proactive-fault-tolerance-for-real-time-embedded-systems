function [p_cam,l_cam]=camera(hauteur_cam)
% Copyright 2015 The MathWorks, Inc.
% hauteur camera
hauteur=[10 23 41 52];
% zone visible en profondeur
pmin=[13 34 40 50];
pmax=[100 160 240 300];
% zone visible en largeur
lmin=[20 50 62 62];
lmax=[110 205 300 360];

coef_pmin=polyfit(hauteur(2:end),pmin(2:end),1);
coef_pmax=polyfit(hauteur(2:end),pmax(2:end),1);
coef_lmin=polyfit(hauteur(2:end),lmin(2:end),1);
coef_lmax=polyfit(hauteur(2:end),lmax(2:end),1);

p_cam=[ polyval(coef_pmin,hauteur_cam) polyval(coef_pmax,hauteur_cam)];
l_cam=[ polyval(coef_lmin,hauteur_cam) polyval(coef_lmax,hauteur_cam)];

