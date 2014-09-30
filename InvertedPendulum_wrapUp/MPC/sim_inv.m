clear; clc; close all
% 
% % num11=-1;
% % den11=[25 1];
% % num12=[1 -0.005 -0.005];
% % den12=conv([1 0],[1 1]);
% % den12=conv(den12,[0.1 1]);
% % num21=1;
% % den21=[25 1];
% % num22=-0.0023;
% % den22=[1 0];
% % Gs=tf({num11 num12; num21 num22},{den11 den12; den21 den22});
% % Gs1=ss(Gs,'min');
% Ap = load('../A.csv');
% Bp = load('../B.csv');
% Cp = load('../C.csv');
% Dp = load('../D.csv');
% % [Ap,Bp,Cp,Dp]=ssdata(Gs1);
% [m1,n1]=size(Cp);
% [n1,n_in]=size(Bp);
% A=zeros(n1+m1,n1+m1);
% A(1:n1,1:n1)=Ap;
% A(n1+1:n1+m1,1:n1)=Cp;
% B=zeros(n1+m1,n_in);
% B(1:n1,:)=Bp;
% C=zeros(m1,n1+m1);
% C(:,n1+1:n1+m1)=eye(m1,m1);
% n=n1+m1;
% Q=C'*C;
% R=1*eye(2,2);
% p1=60;
% p2=60;
% N1=16;
% N2=16;
% Tp1=3;
% Tp2=3;
% p=[p1 p2];
% N=[N1 N2];
% Tp=[Tp1 Tp2];
% [Omega,Psi]=cmpc(A,B,p,N,Tp,Q,R);
% Q1=eye(n,n);
% R1=0.2*eye(m1,m1);
% K_ob=lqr(A',C',Q1,R1)';
% xm=0.5 * ones(n1,1);
% u=zeros(n_in,1);
% y=0.5 *ones(m1,1);
% h=0.03;
% N_sim=8*1400;
% sp1=ones(1,N_sim);
% sp2=zeros(1,N_sim);
% sp=[sp1;sp2]; %set-point signal
% [Md,Lzerot]=Mder(p,N,n_in,0.1);
% [Mu,Mu1]=Mucon(p,N,n_in,h,0.1);
% M=[Mu;-Mu;Lzerot;-Lzerot];
% % u_max= 50;
% % u_min= -50;
% % Deltau_max= 10;
% % Deltau_min= -10;
% % [u1,y1,udot1,t]=cssimucon(xm,u,y,sp,Ap,Bp,Cp,A,B,C,N_sim,Omega,Psi,K_ob,Lzerot,h,M,u_max,u_min,Deltau_max,Deltau_min);
% [u1,y1,x,udot1,t]=cssimuob(xm,u,y,sp,Ap,Bp,Cp,A,B,C,N_sim,Omega,Psi,K_ob,Lzerot,h);


% Ap = load('../A.csv');
% Bp = load('../B.csv');
% Cp = [1,0,0,0;0,1,0,0;0,0,1,0;0,0,0,1];
% % Cp = load('../C.csv');
% Dp = load('../D.csv');
% SSS = load('../SSS.csv');
% Ts = 0.01;
% tf = 15;
% [m1,n1]=size(Cp);
% [n1,n_in]=size(Bp);
% A=zeros(n1+m1,n1+m1);
% A(1:n1,1:n1)=Ap;
% A(n1+1:n1+m1,1:n1)=Cp;
% B=zeros(n1+m1,n_in);
% B(1:n1,:)=Bp;
% C=zeros(m1,n1+m1);
% C(:,n1+1:n1+m1)=eye(m1,m1);
% n=n1+m1;
% Q=C'*C;
% R=1*eye(2,2);
% p1=60;
% p2=60;
% N1=16;
% N2=16;
% Tp1=3;
% Tp2=3;
% p=[p1 p2];
% N=[N1 N2];
% Tp=[Tp1 Tp2];
% Q(7,7) = 500;
% [Omega,Psi]=cmpc(A,B,p,N,Tp,Q,R);
% Q1=eye(n,n);
% R1=0.2*eye(m1,m1);
% Q1(7,7) = 500;
% K_ob=lqr(A',C',Q1,R1)';
% xm=0.5 * ones(n1,1);
% 
% u=zeros(n_in,1);
% y=0.5 *ones(m1,1);
% h=0.03;
% N_sim=tf / Ts;
% sp1=zeros(1,N_sim);
% sp2=zeros(1,N_sim);
% sp3=zeros(1,N_sim);
% sp4=zeros(1,N_sim);
% sp=[sp1;sp2; sp3; sp4]; %set-point signal
% [Md,Lzerot]=Mder(p,N,n_in,0.1);
% [Mu,Mu1]=Mucon(p,N,n_in,h,0.1);
% M=[Mu;-Mu;Lzerot;-Lzerot];
% 
% granularity = -2;
% 
% %% Generate sub spaces
% % Generate S_sigma
% SSS = roundn(SSS, granularity);
% S_sigma = zeros(size(SSS));
% 
% count = 0;
% show = true;
% 
% 
% initState = [0;0;0.4;-0.5];
% xm = initState;
% y = initState([1,2,3,4],1);
% X_hat=zeros(n1+m1,1);
% % X_hat = [xm;y];
% initU = 0;
% u = initU;
% oldState = initState;
% fail = false;
% x = [];
% for kk=1:N_sim;
%     Xsp=[zeros(n1,1);sp(:,kk)];
%     eta=-(Omega\Psi)*(X_hat-Xsp);
%     udot=Lzerot*eta;
%     u=u+udot*h;
%     udot1(1:n_in,kk)=udot;
%     u1(1:n_in,kk)=u;
%     y1(1:m1,kk)=y;
%     X_hat=X_hat+(A*X_hat+K_ob*(y-C*X_hat))*h+B*udot*h;
%     xm=xm+(Ap*xm+Bp*u)*h;
% 
%     x = [x, xm];
%     y=Cp*xm;
% %     X_hat = [xm; y];
% end







global Ap Bp Cp Dp SSS Ts tf AIneq BIneq Aeq Beq LB UB std mean
std = 0;   % standard deviation of noise
mean = 0;   % mean value of noise
Ap = load('../A.csv');
Bp = load('../B.csv');
% Cp = load('../C.csv');
Cp = [1,0,0,0;0,1,0,0;0,0,1,0;0,0,0,1];
Dp = load('../D.csv');
SSS = load('../SSS.csv');
Ts = 0.04;
tf = 10;
[m1,n1]=size(Cp);
[n1,n_in]=size(Bp);
A=zeros(n1+m1,n1+m1);
A(1:n1,1:n1)=Ap;
A(n1+1:n1+m1,1:n1)=Cp;
B=zeros(n1+m1,n_in);
B(1:n1,:)=Bp;
C=zeros(m1,n1+m1);
C(:,n1+1:n1+m1)=eye(m1,m1);
n=n1+m1;
Q=C'*C;
Q(7,7) = 500;
R=1*eye(2,2);
p1=60;
p2=60;
N1=16;
N2=16;
Tp1=3;
Tp2=3;
p=[p1 p2];
N=[N1 N2];
Tp=[Tp1 Tp2];
[Omega,Psi]=cmpc(A,B,p,N,Tp,Q,R);
Q1=eye(n,n);
R1=0.2*eye(m1,m1);
Q1(7,7) = 500;
K_ob=lqr(A',C',Q1,R1)';
xm=0.5 * ones(n1,1);
u=zeros(n_in,1);
y=0.5 *ones(m1,1);
h=0.04;
N_sim=floor(tf / Ts) ;
sp1=zeros(1,N_sim);
sp2=zeros(1,N_sim);
sp3=zeros(1,N_sim);
sp4=zeros(1,N_sim);
sp=[sp1;sp2; sp3; sp4]; %set-point signal

[Md,Lzerot]=Mder(p,N,n_in,0.1);
[Mu,Mu1]=Mucon(p,N,n_in,h,0.1);
M=[Mu;-Mu;Lzerot;-Lzerot];

granularity = -2;

%% Generate sub spaces
% Generate S_sigma
SSS = roundn(SSS, granularity);
S_sigma = zeros(size(SSS));

count = 0;
show = true;

for i = 1 : size(SSS,1)

    percentage = roundn((i / size(SSS, 1)) * 100, 0);
    if mod(percentage, 10) == 0 && show == true
        show = false;
        fprintf(strcat('progress for S_sigma:', int2str(percentage) , '%%\n'));
    elseif mod(percentage, 10) ~= 0 && show == false
        show = true;
    end

    initState = SSS(i, :)';
    xm = initState;
    y = initState([1,2,3,4], 1);
    X_hat=zeros(n1+m1,1);
    X = [zeros(n1, 1); y];
    initU = 0;
    u = initU;
    oldState = initState;
    fail = false;
    for kk=1:N_sim;
        Xsp=[zeros(n1,1);sp(:,kk)];
%         eta=-(Omega\Psi)*(X_hat-Xsp);
        eta=-(Omega\Psi)*(X-Xsp);
        udot=Lzerot*eta;
        u=u+udot*h;
        u = u + mean + std .* randn(1, 1);   % add guassian white noise with 0 mean.
        udot1(1:n_in,kk)=udot;
        u1(1:n_in,kk)=u;
        y1(1:m1,kk)=y;
        X_hat=X_hat+(A*X_hat+K_ob*(y-C*X_hat))*h+B*udot*h;
        x_dot = Ap*xm+Bp*u;
        xm=xm+(Ap*xm+Bp*u)*h;
        y=Cp*xm;
        X = [x_dot;y];
        newState = xm;
        
        oldState = newState;
        
        newState = roundn(newState, granularity);
%         if size(intersect(newState(stateOfInterests)', SSS(:, stateOfInterests), 'rows'), 1) == 0
%             fail = true;
%             break
%         end
        if newState(3) > 0.5 || newState(3) < -0.5
            fail = true;
            break
        end
        
    end
    
    if fail == false
        count = count + 1;
        S_sigma(count, :) = SSS(i, :);
    end
end

S_sigma = S_sigma(1 : count, :);

% Generate S_1


AIneq = [];
BIneq = [];
Aeq = [];
Beq = [];
LB = [-25];
UB = [25];
stateOfInterests = [3,4];
S_1 = zeros(size(S_sigma));

count = 0;
for i = 1 : size(S_sigma, 1)
    oldState = S_sigma(i, :)';
    [worstU, worstC] = worstController(oldState);
    newState = updateState(oldState, worstU);

    newState = roundn(newState, granularity);
    if size(intersect(newState(stateOfInterests)', S_sigma(:, stateOfInterests), 'rows'), 1) ~= 0
        count = count + 1;
        S_1(count, :) = S_sigma(i, :);
    end
end

S_1 = S_1(1:count, :);
       
   
% Generate S_2
S_2 = zeros(size(S_sigma));

count = 0;
for i = 1 : size(S_sigma, 1)
    oldState = S_sigma(i, :)';
    zeroU = zeroController(oldState, UB);
    newState = updateState(oldState, zeroU);

    newState = roundn(newState, granularity);
    if size(intersect(newState(stateOfInterests)', S_sigma(:, stateOfInterests), 'rows'), 1) ~= 0
        count = count + 1;
        S_2(count, :) = S_sigma(i, :);
    end
end

S_2 = S_2(1:count, :);
S_2 = setdiff(S_2, S_1, 'rows');

% Generate S_3
S_3 = setdiff(S_sigma, union(S_1, S_2, 'rows'), 'rows');

S_1 = S_1(:, stateOfInterests);
S_2 = S_2(:, stateOfInterests);
S_3 = S_3(:, stateOfInterests);

% Plot sub spaces, and save data
figure
hold on

plot(S_3(:, 1), S_3(:, 2), 'rx', 'LineWidth', 4);
plot(S_2(:, 1), S_2(:, 2), 'bx', 'LineWidth', 4);
plot(S_1(:, 1), S_1(:, 2), 'gx', 'LineWidth', 4);
grid

set(gcf, 'PaperPosition', [0 0 5 5]); %Position plot at left hand corner with width 5 and height 5.
set(gcf, 'PaperSize', [5 5]); %Set the paper to have width 5 and height 5.
saveas(gcf, strcat('../simResults/subSpaces_MPC_' , num2str(Ts * 1000) , '_ms.pdf') , 'pdf') %Save figure


csvwrite(strcat('../simResults/s_sigma_MPC_', num2str(Ts * 1000) ,'_ms.csv'), S_sigma);
csvwrite(strcat('../simResults/s1_MPC_' , num2str(Ts * 1000) , '_ms.csv'), S_1);
csvwrite(strcat('../simResults/s2_MPC_' , num2str(Ts * 1000) , '_ms.csv'), S_2);
csvwrite(strcat('../simResults/s3_MPC_' , num2str(Ts * 1000) , '_ms.csv'), S_3);