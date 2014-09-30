function [] = demos_fp()

% NelinSys - a program tool for analysis and synthesis of nonlinear control systems
%            based on MATLAB/Simulink 5.2
%
% (C) 2002-2005, Martin Ondera (Martin.Ondera@gmail.com) (eskimo@pobox.sk)

v = menu('PHASE PLANE ANALYSIS (demo simulations)',...
   '2nd-Order Autonomous System',...
   '2nd-Order Loop with a Hard Nonlinearity',...
   'Duffing Equation');

if ~isempty(v)
   switch v,
   case 1
      open_system('demo_fp2');
      sim('demo_fp2');
   case 2
      open_system('demo_typnl');
      sim('demo_typnl');
   case 3
      open_system('demo_duffing');
      sim('demo_duffing');
   end
end