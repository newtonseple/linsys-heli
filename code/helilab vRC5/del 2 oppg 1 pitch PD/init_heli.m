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

%%%%%%%%%%% Calculated constants
k_f = 0.14689;
K_1 = k_f/(2*m_p*l_p);

L_1 = k_f*l_p;
L_2 = (m_c*l_c-2*m_p*l_h)*g;
L_3 = k_f*l_h;

%%%%%%%%%%% Measured Constants
vs0 = 6.8;
w0 = 4;
zeta = 1.5;
Kpp = w0^2 / K_1;
Kpd = 2*w0*zeta/K_1;

Krp = 1;


s = tf('s');
h = K_1*Kpp/(s^2 + K_1*Kpd*s + K_1*Kpp);
h0 = K_1/s^2;