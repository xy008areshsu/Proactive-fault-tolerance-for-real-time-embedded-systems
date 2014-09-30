function [ worstU, worstCost ] = worstController(x)
%WORSTCONTROLLER Summary of this function goes here
%   Detailed explanation goes here
global A  B C D K SSS Ts tf AIneq BIneq Aeq Beq LB UB

% warning off
% 
% % fprintf ('The values of function value and constraints at starting point\n');
% 
% costFunction = @(u) -probofminobj(u,x);
% u0 = zeros(size(UB, 1),1); % Starting guess\
% options = optimset ('MaxIter', 4000, 'MaxFunEvals', 4000);
% [u, fval]=fmincon (costFunction, u0, AIneq, BIneq, Aeq, Beq, LB, UB, @nonLinCon, options);
% 
% worstCost = -fval;
% worstU = u;
    this_v_l = x(1);
    this_v_f = x(2);
    this_d = x(3);
    bad_a_l = 10;
    d_d = 40;

    this_d = this_d + (this_v_l - this_v_f) * Ts;
    if this_d > d_d
       this_v_l = this_v_l + bad_a_l * Ts;
    else
       this_v_l = this_v_l - bad_a_l * Ts;
    end
    
    this_v_l = round(this_v_l);

    this_v_f_UB = this_v_f + Ts * UB;
    this_v_f_UB = round(this_v_f_UB);
    this_d_UB = this_d + (this_v_l - this_v_f_UB) * Ts;

    
    this_v_f_LB = this_v_f + Ts * LB;
    this_v_f_LB = round(this_v_f_LB);
    this_d_LB = this_d + (this_v_l - this_v_f_LB) * Ts;

    if abs(this_d_UB - d_d) > abs(this_d_LB - d_d)
        worstU = UB;
    else
        worstU = LB;
    end

    worstCost = 100;
    

end

