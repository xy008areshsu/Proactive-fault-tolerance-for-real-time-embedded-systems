function [ taaf, Tabs] = ThermalStressAllOnFunc( R, C, initTabs0, Tamb, Ea, w,  w_idle, k, A, step, time )

    Tss = steady_state_T(Tamb,R,w);
    Tss_idle = steady_state_T(Tamb, R, w_idle);

    Tabs = zeros(size(time, 2), 1);
    alpha = zeros(size(time, 2), 1);
    taaf = zeros(size(time, 2), size(w, 2));
    initTabs = initTabs0;
    i = 1;

    for t = time
        Tabs(i) = absolute_T(Tss,initTabs,step, R, C);
        alpha(i) = aging_factor(A, Ea,k,Tabs(i));
        taaf(i) = TAAF(A, Ea,k,Tabs(i));
        %taaf(i) = alpha(i) / t;
        initTabs = Tabs(i);
        i = i + 1;
    end

end

