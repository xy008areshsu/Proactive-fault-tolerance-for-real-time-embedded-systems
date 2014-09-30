function [ taaf1, Tabs1, taaf2, Tabs2, taaf3, Tabs3 ] = ThermalStreeAdaptiveFuncWithRegions( R, C, initTabs0, Tamb, Ea, w, w_idle, k, A, step, time, t_S_N, t_S_FS)

    Tss = steady_state_T(Tamb,R,w);
    Tss_idle = steady_state_T(Tamb, R, w_idle);

    Tabs1 = zeros(size(time, 2), 1);
    alpha1 = zeros(size(time, 2), 1);
    taaf1 = zeros(size(time, 2), size(w, 2));
    initTabs1 = initTabs0;
    
    Tabs2 = zeros(size(time, 2), 1);
    alpha2 = zeros(size(time, 2), 1);
    taaf2 = zeros(size(time, 2), size(w, 2));
    initTabs2 = initTabs0;
    
    Tabs3 = zeros(size(time, 2), 1);
    alpha3 = zeros(size(time, 2), 1);
    taaf3 = zeros(size(time, 2), size(w, 2));
    initTabs3 = initTabs0;
    

    
    i = 1;

        for t = time
            if i == size(time, 2)
                break;
            end
            if find(abs(t - t_S_N) < 0.01) % Assume when it is at these moments, this processor can be turned off
                T_min = min([Tabs1(i), Tabs2(i), Tabs3(i)]);     % Scheduling, choose the coolest chip to run the task
                if T_min == Tabs1(i)
                    Tabs1(i + 1) = absolute_T(Tss,initTabs1,step, R, C);
                    alpha1(i + 1) = aging_factor(A, Ea,k,Tabs1(i));
                    taaf1(i + 1) = TAAF(A, Ea,k,Tabs1(i));
                    initTabs1 = Tabs1(i + 1);
                    
                    Tabs2(i + 1) = absolute_T(Tss_idle,initTabs2,step, R, C);
                    alpha2(i + 1) = aging_factor(A, Ea,k,Tabs2(i));
                    taaf2(i + 1) = TAAF(A, Ea,k,Tabs2(i));
                    initTabs2 = Tabs2(i + 1);
                                                            
                    Tabs3(i + 1) = absolute_T(Tss_idle,initTabs3,step, R, C);
                    alpha3(i + 1) = aging_factor(A, Ea,k,Tabs3(i));
                    taaf3(i + 1) = TAAF(A, Ea,k,Tabs3(i));
                    initTabs3 = Tabs3(i + 1);
                elseif T_min == Tabs2(i)
                    Tabs1(i + 1) = absolute_T(Tss_idle,initTabs1,step, R, C);
                    alpha1(i + 1) = aging_factor(A, Ea,k,Tabs1(i));
                    taaf1(i + 1) = TAAF(A, Ea,k,Tabs1(i));
                    initTabs1 = Tabs1(i + 1);
                    
                    Tabs2(i + 1) = absolute_T(Tss,initTabs2,step, R, C);
                    alpha2(i + 1) = aging_factor(A, Ea,k,Tabs2(i));
                    taaf2(i + 1) = TAAF(A, Ea,k,Tabs2(i));
                    initTabs2 = Tabs2(i + 1);
                                                            
                    Tabs3(i + 1) = absolute_T(Tss_idle,initTabs3,step, R, C);
                    alpha3(i + 1) = aging_factor(A, Ea,k,Tabs3(i));
                    taaf3(i + 1) = TAAF(A, Ea,k,Tabs3(i));
                    initTabs3 = Tabs3(i + 1);
                else
                    Tabs1(i + 1) = absolute_T(Tss_idle,initTabs1,step, R, C);
                    alpha1(i + 1) = aging_factor(A, Ea,k,Tabs1(i));
                    taaf1(i + 1) = TAAF(A, Ea,k,Tabs1(i));
                    initTabs1 = Tabs1(i + 1);
                    
                    Tabs2(i + 1) = absolute_T(Tss_idle,initTabs2,step, R, C);
                    alpha2(i + 1) = aging_factor(A, Ea,k,Tabs2(i));
                    taaf2(i + 1) = TAAF(A, Ea,k,Tabs2(i));
                    initTabs2 = Tabs2(i + 1);
                                                            
                    Tabs3(i + 1) = absolute_T(Tss,initTabs3,step, R, C);
                    alpha3(i + 1) = aging_factor(A, Ea,k,Tabs3(i));
                    taaf3(i + 1) = TAAF(A, Ea,k,Tabs3(i));
                    initTabs3 = Tabs3(i + 1);
                end
            elseif find(abs(t - t_S_FS) < 0.01)
                T_max = max([Tabs1(i), Tabs2(i), Tabs3(i)]);     % Scheduling, choose the hottest chip to stop running the task
                
                if T_max == Tabs1(i)
                    Tabs1(i + 1) = absolute_T(Tss_idle,initTabs1,step, R, C);
                    alpha1(i + 1) = aging_factor(A, Ea,k,Tabs1(i));
                    taaf1(i + 1) = TAAF(A, Ea,k,Tabs1(i));
                    initTabs1 = Tabs1(i + 1);
                    
                    Tabs2(i + 1) = absolute_T(Tss,initTabs2,step, R, C);
                    alpha2(i + 1) = aging_factor(A, Ea,k,Tabs2(i));
                    taaf2(i + 1) = TAAF(A, Ea,k,Tabs2(i));
                    initTabs2 = Tabs2(i + 1);
                                                            
                    Tabs3(i + 1) = absolute_T(Tss,initTabs3,step, R, C);
                    alpha3(i + 1) = aging_factor(A, Ea,k,Tabs3(i));
                    taaf3(i + 1) = TAAF(A, Ea,k,Tabs3(i));
                    initTabs3 = Tabs3(i + 1);
                elseif T_max == Tabs2(i)
                    Tabs1(i + 1) = absolute_T(Tss,initTabs1,step, R, C);
                    alpha1(i + 1) = aging_factor(A, Ea,k,Tabs1(i));
                    taaf1(i + 1) = TAAF(A, Ea,k,Tabs1(i));
                    initTabs1 = Tabs1(i + 1);
                    
                    Tabs2(i + 1) = absolute_T(Tss_idle,initTabs2,step, R, C);
                    alpha2(i + 1) = aging_factor(A, Ea,k,Tabs2(i));
                    taaf2(i + 1) = TAAF(A, Ea,k,Tabs2(i));
                    initTabs2 = Tabs2(i + 1);
                                                            
                    Tabs3(i + 1) = absolute_T(Tss,initTabs3,step, R, C);
                    alpha3(i + 1) = aging_factor(A, Ea,k,Tabs3(i));
                    taaf3(i + 1) = TAAF(A, Ea,k,Tabs3(i));
                    initTabs3 = Tabs3(i + 1);
                else
                    Tabs1(i + 1) = absolute_T(Tss,initTabs1,step, R, C);
                    alpha1(i + 1) = aging_factor(A, Ea,k,Tabs1(i));
                    taaf1(i + 1) = TAAF(A, Ea,k,Tabs1(i));
                    initTabs1 = Tabs1(i + 1);
                    
                    Tabs2(i + 1) = absolute_T(Tss,initTabs2,step, R, C);
                    alpha2(i + 1) = aging_factor(A, Ea,k,Tabs2(i));
                    taaf2(i + 1) = TAAF(A, Ea,k,Tabs2(i));
                    initTabs2 = Tabs2(i + 1);
                                                            
                    Tabs3(i + 1) = absolute_T(Tss_idle,initTabs3,step, R, C);
                    alpha3(i + 1) = aging_factor(A, Ea,k,Tabs3(i));
                    taaf3(i + 1) = TAAF(A, Ea,k,Tabs3(i));
                    initTabs3 = Tabs3(i + 1);
                end
            else
                Tabs1(i + 1) = absolute_T(Tss,initTabs1,step, R, C);
                alpha1(i + 1) = aging_factor(A, Ea,k,Tabs1(i));
                taaf1(i + 1) = TAAF(A, Ea,k,Tabs1(i));
                initTabs1 = Tabs1(i + 1);

                Tabs2(i + 1) = absolute_T(Tss,initTabs2,step, R, C);
                alpha2(i + 1) = aging_factor(A, Ea,k,Tabs2(i));
                taaf2(i + 1) = TAAF(A, Ea,k,Tabs2(i));
                initTabs2 = Tabs2(i + 1);

                Tabs3(i + 1) = absolute_T(Tss,initTabs3,step, R, C);
                alpha3(i + 1) = aging_factor(A, Ea,k,Tabs3(i));
                taaf3(i + 1) = TAAF(A, Ea,k,Tabs3(i));
                initTabs3 = Tabs3(i + 1);
            end
            i = i + 1;
        end

        
        
%         for t = time
%             if i == size(time, 2)
%                 break;
%             end
%             if find(abs(t - t_S_N .* 10) < 0.01) % Assume when it is at these moments, this processor can be turned off
%                     Tabs1(i + 1) = absolute_T(Tss_idle,initTabs1,step, R, C);
%                     alpha1(i + 1) = aging_factor(A, Ea,k,Tabs1(i));
%                     taaf1(i + 1) = TAAF(A, Ea,k,Tabs1(i));
%                     initTabs1 = Tabs1(i + 1);
%             else
%                 Tabs1(i + 1) = absolute_T(Tss,initTabs1,step, R, C);
%                 alpha1(i + 1) = aging_factor(A, Ea,k,Tabs1(i));
%                 taaf1(i + 1) = TAAF(A, Ea,k,Tabs1(i));
%                 initTabs1 = Tabs1(i + 1);
%             end
%             i = i + 1;
%         end

end

