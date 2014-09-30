function [ taaf, Tabs ] = ThermalStreeAdaptiveFunc( R, C, initTabs0, Tamb, Ea, w, w_idle, k, A, step, time)

    Tss = steady_state_T(Tamb,R,w);
    Tss_idle = steady_state_T(Tamb, R, w_idle);

    Tabs = zeros(100, 1);
    alpha = zeros(100, 1);
    taaf = zeros(100, size(w, 2));
    initTabs = initTabs0;
    i = 1;

        for t = time
            if mod(t, 2) == 0 || mod(t, 3) == 0 || mod(t, 5) == 0 || mod(t, 7) == 0 % Assume when it is at these moments, this processor can be turned off
                Tabs(i) = absolute_T(Tss_idle,initTabs,step, R, C);
                alpha(i) = aging_factor(A, Ea,k,Tabs(i));
                taaf(i) = TAAF(A, Ea,k,Tabs(i));
                %taaf(i) = alpha(i) / t;
            else
                Tabs(i) = absolute_T(Tss,initTabs,step, R, C);
                alpha(i) = aging_factor(A, Ea,k,Tabs(i));
                taaf(i) = TAAF(A, Ea,k,Tabs(i));
                %taaf(i) = alpha(i) / t;
            end
            initTabs = Tabs(i);
            i = i + 1;
        end


end

