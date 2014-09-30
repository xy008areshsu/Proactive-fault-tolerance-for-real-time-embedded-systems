clear; clc; close all

Am=[-1 0 0;0 -3 0;3 3 -5];
Bm=[1 0;0 1; 1 1];
Cm=[1 0 0;0 1 0];
[m1,n1]=size(Cm);
[n1,n_in]=size(Bm);
A=zeros(n1+m1,n1+m1);
A(1:n1,1:n1)=Am;
A(n1+1:n1+m1,1:n1)=Cm;
B=zeros(n1+m1,n_in);
B(1:n1,:)=Bm;
C=zeros(m1,n1+m1);
C(:,n1+1:n1+m1)=eye(m1,m1);
Q=C'*C;
R=0.2*eye(2,2);
p1=1.5;
p2=2;
N1=4;
N2=4;
p=[p1 p2];
N=[N1 N2];
Tp=10;
[Omega,Psi]=cmpc(A,B,p,N,Tp,Q,R);
[Ap1,L1]=lagc(p1,N1);
[Ap2,L2]=lagc(p2,N2);
Lzerot=zeros(2,N1+N2);
Lzerot(1,1:N1)=L1';
Lzerot(2,N1+1:N1+N2)=L2';
K_mpc=Lzerot*(Omega\Psi)
Acl=A-B*K_mpc;
eig(Acl)
[K,S,E]=lqr(A,B,Q,R)