clear; clc; close all

%% --------------------------Model---------------------------- 
Ap = [1 1; 0 1];
Bp = [0.5; 1];
Cp = [1 0];
Dp = 0;

%% -------------------Design parameters-----------------------
Np = 40;           % Prediction horizon
Nc = 4;            % Control horizon
N_sim=20;          % Number of simulation points
r=ones(N_sim,1);   % Desired state
rw = 10;  % Weight on the control inputs

%% ----------------------MPC gain-----------------------------
[Phi_Phi,Phi_F,Phi_R,A_e, B_e,C_e] = mpcgain(Ap,Bp,Cp,Nc,Np);
[n,n_in]=size(B_e);


%% ------------Simulation process using MPC------------------
xm=[0;0];
Xf=zeros(n,1);
u=0; % u(k-1) =0
y=0;

for kk=1:N_sim;
%     DeltaU=inv(Phi_Phi+rw*eye(Nc,Nc))*(Phi_R*r(kk)-Phi_F*Xf);
    DeltaU = (Phi_Phi+rw*eye(Nc,Nc))\(Phi_R*r(kk)-Phi_F*Xf);
    deltau=DeltaU(1,1);
    u=u+deltau;
    u1(kk)=u;
    y1(kk)=y;
    xm_old=xm;
    xm=Ap*xm+Bp*u;
    y=Cp*xm;
    Xf=[xm-xm_old;y];
end


%% ----------------------------Plots---------------------------
k=0:(N_sim-1);
figure
subplot(211)
plot(k,y1, 'LineWidth', 2)
xlabel('Sampling Instant')
legend('Output')
grid
subplot(212)
plot(k,u1,  'LineWidth', 2)
xlabel('Sampling Instant')
legend('Control')
grid