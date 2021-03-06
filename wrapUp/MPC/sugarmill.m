clear; clc; close all

num11=-1;
den11=[25 1];
num12=[1 -0.005 -0.005];
den12=conv([1 0],[1 1]);
den12=conv(den12,[0.1 1]);
num21=1;
den21=[25 1];
num22=-0.0023;
den22=[1 0];
Gs=tf({num11 num12; num21 num22},{den11 den12; den21 den22});
Gs1=ss(Gs,'min');
[Ap,Bp,Cp,Dp]=ssdata(Gs1);
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
R=1*eye(2,2);
p1=0.6;
p2=0.6;
N1=6;
N2=6;
Tp1=100;
Tp2=100;
p=[p1 p2];
N=[N1 N2];
Tp=[Tp1 Tp2];
[Omega,Psi]=cmpc(A,B,p,N,Tp,Q,R);
Q1=eye(n,n);
R1=0.2*eye(m1,m1);
K_ob=lqr(A',C',Q1,R1)';
xm=zeros(n1,1);
u=zeros(n_in,1);
y=zeros(m1,1);
h=0.03;
N_sim=8*1400;
sp1=ones(1,N_sim);
sp2=[zeros(1,N_sim/2) -ones(1,N_sim/2)];
sp=[sp1;sp2]; %set-point signal
[Md,Lzerot]=Mder(p,N,n_in,0.1);
[Mu,Mu1]=Mucon(p,N,n_in,h,0.1);
M=[Mu;-Mu;Lzerot;-Lzerot];
u_max=[0;3];
u_min=[-1;-3];
Deltau_max=[0.4;0.4];
Deltau_min=[-0.4;-0.4];
[u1,y1,udot1,t]=cssimucon(xm,u,y,sp,Ap,Bp,Cp,A,B,C,N_sim,Omega,Psi,K_ob,Lzerot,h,M,u_max,u_min,Deltau_max,Deltau_min);