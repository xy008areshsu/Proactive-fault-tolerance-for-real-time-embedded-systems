function [ Tabs ] = absolute_T( Tss, init_Tabs, t, R, C)
%ABSOLUTE_T Summary of this function goes here
%   Detailed explanation goes here

    Tabs = Tss + (init_Tabs - Tss) * exp(-t / (R * C));

end

