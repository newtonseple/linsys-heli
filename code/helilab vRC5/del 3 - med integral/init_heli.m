% This file contains the initialization for the helicopter assignment in
% the course TTK4115. Run this file before you execute QuaRC_ -> Build 
% to build the file heli_q8.mdl.

% Oppdatert høsten 2006 av Jostein Bakkeheim
% Oppdatert høsten 2008 av Arnfinn Aas Eielsen
% Oppdatert høsten 2009 av Jonathan Ronen
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

%%%%%%%%%%% Measured Constants
vs0 = 6.8;
w0 = 4;
zeta = 1.5;

%%%%%%%%%% System
A = [0 1 0 0 0; 0 0 0 0 0; 0 0 0 0 0; 1 0 0 0 0; 0 0 1 0 0];
B = [0 0; 0 K_1; K_2 0; 0 0; 0 0];
C = [1 0 0 0 0; 0 0 1 0 0];
D = zeros(2,2);

sys = ss(A,B,C,D);
rank(ctrb(sys))
%%%%%% Regulator constants
%Q: Bryson: (pi/4), (2pi), (pi/5), (pi/4), (pi/5)
%Q = diag([60 0.001 750 60 10]); % P P' E' gamma(int P) zeta(int E')
Q = diag([1/(pi/4)^2 1/(2*pi)^2 1/(pi/5)^2 1/(pi/4)^2 1/(pi/5)^2])

%R: Bryson: 9V^2 for both
%R = diag([1 1]); % Vs Vd
R = diag([1/(9^2) 1/(9^2)])

K = lqr(A,B,Q,R)

%%%%%% Feed forward
A_p = [0 1 0; 0 0 0; 0 0 0];
B_p = [0 0; 0 K_1; K_2 0];
C_p = [1 0 0; 0 0 1];
K_pp = K(:,1:3,:);
P = inv((C_p/(B_p*K_pp-A_p))*B_p)
