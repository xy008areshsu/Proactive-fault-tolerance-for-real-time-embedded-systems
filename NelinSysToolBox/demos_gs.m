function [] = demos_gs()

% NelinSys - a program tool for analysis and synthesis of nonlinear control systems
%            based on MATLAB/Simulink 5.2
%
% (C) 2002-2005, Martin Ondera (Martin.Ondera@gmail.com) (eskimo@pobox.sk)

v = menu('GAIN SCHEDULING (demo simulations)',...
   'Input and output scheduling',...
   'Comparison with exact linearization');

if ~isempty(v)
   switch v,
   case 1
      open_system('demo_gs1');
      sim('demo_gs1');
   case 2
      open_system('demo_gs2');
      sim('demo_gs2');
   end
end