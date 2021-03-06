% This file contains the initialization for the helicopter assignment in
% the course TTK4115. Run this file before you execute QuaRC_ -> Build 
% to build the file heli_q8.mdl.

% Oppdatert h�sten 2006 av Jostein Bakkeheim
% Oppdatert h�sten 2008 av Arnfinn Aas Eielsen
% Oppdatert h�sten 2009 av Jonathan Ronen
% Updated fall 2010, Dominik Breu
% Updated fall 2013, Mark Haring
% Updated spring 2015, Mark Haring


%%%%%%%%%%% Calibration of the encoder and the hardware for the specific
%%%%%%%%%%% helicopter
Joystick_gain_x = 1;
Joystick_gain_y = -1;


%%%%%%%%%%% Physical constants
g = 9.81; % gravitational constant [m/s^2]
l_c = 0.46; % distance elevation axis to counterweight [m]
l_h = 0.66; % distance elevation axis to helicopter head [m]
l_p = 0.175; % distance pitch axis to motor [m]
m_c = 1.92; % Counterweight mass [kg]
m_p = 0.72; % Motor mass [kg]

J_p = 2*m_p*l_p^2;
J_e = m_c*l_c^2 + 2*m_p*l_h^2;
J_lambda = m_c*l_c + 2*m_p*(l_h^2+l_p^2);
%%%%%%%%%%% Calculated constants
k_f = 0.14689;
L_1 = k_f*l_p;
L_2 = (m_c*l_c-2*m_p*l_h)*g;
L_3 = k_f*l_h;
L_4 = L_3;
K_1 = L_1/J_p;
K_2 = L_3/J_e;
K_3 = -L_2/J_lambda;
%%%%%%%%%%% Measured Constants
vs0 = 6.8;
w0 = 4;
zeta = 1.5;

%%%%%%%%%% System
A = [0 1 0; 0 0 0; 0 0 0];
B = [0 0; 0 K_1; K_2 0];
C = [1 0 0; 0 0 1];
D = zeros(2,2);

sys = ss(A,B,C,D);
rank(ctrb(sys))

%%%%%% Regulator constants
Q = diag([10 0.0001 750]); % P P' E'
R = diag([1 1]); % Vs Vd

K = lqr(A,B,Q,R)

%%%%%% Feed forward
P = inv(C*inv(B*K-A)*B)

%%%%%% For obsrevator
A_obsv = [0 1 0 0 0 0; 0 0 0 0 0 0; 0 0 0 1 0 0; 0 0 0 0 0 0; 0 0 0 0 0 1; K_3 0 0 0 0 0];
B_obsv = [0 0; 0 K_1; 0 0; K_2 0; 0 0; 0 0];
C_obsv = [0 0 1 0 0 0; 0 0 0 0 1 0];
D_obsv = zeros(2,2);


es = eig(A-B*K);

r0 = max(abs(es));

% radial multiplier & selector
fr = 20;
%phi = pi/4;
phi = 15 * pi / 360
%r = r0*fr;
r = 3

spread = -phi:(phi/(2.5)):phi;

%poles = -r*exp(1i * spread);

poles = -0.5 * [20 21 22 23 24 25];
plot(real(es),imag(es),'or',real(poles),imag(poles),'kx');grid on; axis equal
L = place(A_obsv', C_obsv', poles).'

sys_obsv = ss(A_obsv,B_obsv,C_obsv,D_obsv);
disp('styrbarhet og observerbarhet')
rank(ctrb(sys_obsv))
rank(obsv(sys_obsv))
