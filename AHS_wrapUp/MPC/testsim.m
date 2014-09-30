clear; clc; close all

n1 = 2;
n2 = 2;
Q1=eye(n1+m1,n1+m1);
R1=0.0001*eye(m1,m1);
K_ob=lqr(A',C',Q1,R1)';
xm=zeros(n1,1);
u0=zeros(n_in,1);
y0=zeros(m1,1);
N_sim=60000;
h=0.001;
r1=ones(1,N_sim+200);
r2=zeros(1,N_sim+200);
sp=[r1;r2];
[u,y,udot,t]=cssimuob(xm,u0,y0,sp,Ap,Bp,Cp,A,B,C,N_sim,Omega,Psi,K_ob,Lzerot,h);