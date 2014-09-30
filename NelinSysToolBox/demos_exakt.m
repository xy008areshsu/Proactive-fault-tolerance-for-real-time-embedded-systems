function [] = demos_exakt()

% NelinSys - a program tool for analysis and synthesis of nonlinear control systems
%            based on MATLAB/Simulink 5.2
%
% (C) 2002-2005, Martin Ondera (Martin.Ondera@gmail.com) (eskimo@pobox.sk)

v = menu('EXACT LINEARIZATION (demo simulations)',...
   'Exact linearization of SISO system',...
   'Exact linearization of MIMO system',...
   'System with unstable zero dynamics');

if ~isempty(v)
   switch v,
   case 1
      open_system('demo_exakt_siso');
      sim('demo_exakt_siso');
   case 2
      open_system('demo_exakt_mimo');
      sim('demo_exakt_mimo');
   case 3
      open_system('demo_exakt_nestab');
      sim('demo_exakt_nestab');
   end
end