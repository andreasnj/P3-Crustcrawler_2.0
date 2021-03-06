  %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%
%    The inverse dynamics of the 2-dof planar robotic arm
%     
%    contact: shaoping bai, shb@m-tech.aau.dk
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

clear all; close all; clc

g = 9.801; % gravity constant
%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%  link properties
% ====================================== link 0
%======================================  link 1
L1 = 0.22; % length [m]
% %c1 = L1 * 2/3; % mass center
m1 = 0.037 + 0.153; % mass [kg] the link + the motor
% I1 = 1/12 * m1 * L1^2; % moment of inertia
mass1 = 0.037;
%======================================  link 2
L2 = 0.14; % length [m]
% %c2 = L2 * 2/3; % mass center
m2 = 0.023 + 0.135; % mass [kg] the link + the motor
% I2 = 1/12 * m2 * L2^2; % moment of inertia
mass2 = 0.023;
%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% shortenings for the torque equations
B1 = (L1^2/8)*m1+(L1^2/2)*mass1+(L1^2/2)*m2+(L1^2/2)*mass2;
B2 = (L2/8)*m2+(L2^2/2)*mass2;
B3 = ((L1*L2)/2)*m2+L1*L2*mass2;
%% %%%%%%%%%%%%%%%% wished positions of joints and time for the movements
tf = 0.33;
theta00 = 1000 * 2*pi/4096;
thetaf0 = 2048 * 2*pi/4096;
theta01 = 3072 * 2*pi/4096 ;%- pi/2; %in the graphs will be represented in radians, although input is in ticks of the motor
thetaf1 = 2048 * 2*pi/4096 ;%- pi/2;
theta02 = 2048 * 2*pi/4096 ;%+ pi;
thetaf2 = 3072 * 2*pi/4096 ;%+ pi;
%% %%%%%%%%%%%%%%%% coefficients for position, velocity and acceleration
a00 = theta00;
a10 = 0;
a20 = 3/(tf^2)*(thetaf0 - theta00);
a30 = -2/(tf^3)*(thetaf0 - theta00);

a01 = theta01;
a11 = 0;
a21 = 3/(tf^2)*(thetaf1 - theta01);
a31 = -2/(tf^3)*(thetaf1 - theta01);

a02 = theta02;
a12 = 0;
a22 = 3/(tf^2)*(thetaf2 - theta02);
a32 = -2/(tf^3)*(thetaf2 - theta02);
%% %%%%%%%%%%%%%%%%%% dynamic simulation
%%%%%%%%%%%%%%%%%%% discrete time
T = tf; % second
N = tf*100; % resolution
i = 0; 
for t = linspace(0, T, N)
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%% instantaneous time
    i = i + 1; time(i) = t; 
    %%%%%%%%%%%%%%% Joint 0: angular displacement, velocity, acceleration
    theta_1(i) = a01 + a10 * t + a20 * t^2 + a30 * t^3;
    dtheta_1(i) = a10 + 2 * a20 * t + 3 * a30 * t^2;
    ddtheta_1(i) = 2 * a20 + 6 * a30 * t;
    %%%%%%%%%%%%%%% Joint 1: angular displacement, velocity, acceleration
    theta_2(i) = a01 + a11 * t + a21 * t^2 + a31 * t^3;
    dtheta_2(i) = a11 + 2 * a21 * t + 3 * a31 * t^2;
    ddtheta_2(i) = 2 * a21 + 6 * a31 * t;
    %%%%%%%%%%%%%%% Joint 2: angular displacement, velocity, acceleration
    theta_3(i) = a02 + a12 * t + a22 * t^2 + a32 * t^3;
    dtheta_3(i) = a12 + 2 * a22 * t + 3 * a32 * t^2;
    ddtheta_3(i) = 2 * a22 + 6 * a32 * t;
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  actuator torques
    tau_1(i) = (2*B1*cos(theta_2(i))*cos(theta_2(i))+2*B2*cos(theta_2(i)+theta_3(i))+2*B3*cos(theta_2(i)+theta_3(i))*cos(theta_2(i)))*ddtheta_1(i)+(-2*B1*sin(theta_2(i))*cos(theta_2(i))-B2*sin(theta_2(i)+theta_3(i))-B3*(sin(theta_2(i)+theta_3(i))*cos(theta_2(i))+sin(theta_2(i))*cos(theta_2(i)+theta_3(i))))*dtheta_1(i);
    tau_2(i) = 2*B1+2*B2+2*B3*(sin(theta_2(i)+theta_3(i))*sin(theta_2(i))+cos(theta_2(i)+theta_3(i))*cos(theta_2(i)))*ddtheta_2(i)+2*B2*ddtheta_3(i)+(cos(theta_2(i)+theta_3(i))*sin(theta_2(i))+sin(theta_2(i)+theta_3(i))*cos(theta_2(i)-sin(theta_2(i)+theta_3(i)))*cos(theta_2(i))-cos(theta_2(i)+theta_3(i))*sin(theta_2(i)))*B3*dtheta_2(i)+L1*g*((m1/2)+mass1+m2+mass2)*cos(theta_2(i))+L2*g*((m2/2)+mass2)*cos(theta_2(i)+theta_3(i));
    tau_3(i) = 2*B2*(ddtheta_2(i)+ddtheta_3(i))+L2*g*((m2/2)+mass2)*cos(theta_2(i)+theta_3(i));
    %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  link positions
    %%%%%%%%%%%%%%%%%% link 1
    X1(i) = L1*cos(theta_1(i)); Y1(i) = L1*sin(theta_1(i)); 
    % x1(i) = 0.5*X1(i); y1(i) = 0.5*Y1(i); 
    %%%%%%%%%%%%%%%%%% link 2
    X2(i) = X1(i) + L2*cos(theta_1(i) + theta_2(i)); 
    Y2(i) = Y1(i) + L2*sin(theta_1(i) + theta_2(i)); 
    %x2(i) = X1(i) + 0.5*X2(i); %Y2(i) = Y1(i) + 0.5*Y2(i); 
    
end

torque_1 = [time; tau_1]'; torque_2 = [time; tau_2]'; 

%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% plot the motion profiles
figure(2)
clf
figure(2)
subplot(3, 1, 1)
hold on
plot(time, theta_1, 'g')
plot(time, theta_2, 'b')
plot(time, theta_3, 'r')
hold off
legend('joint 1', 'joint 2', 'joint 3')
grid on; 
xlabel('time [sec]'); ylabel('angular displacement [rad]'); 
subplot(4, 1, 2)
hold on
plot(time, dtheta_1, 'g')
plot(time, dtheta_2, 'b')
plot(time, dtheta_3, 'r')
hold off
grid on; 
xlabel('time [sec]'); ylabel('angular velocity [rad/s]'); 
subplot(4, 1, 3)
hold on
plot(time, ddtheta_1, 'g')
plot(time, ddtheta_2, 'b')
plot(time, ddtheta_3, 'r')
hold off
grid on; 
xlabel('time [sec]'); ylabel('angular acceleration [rad/s^2]');  

%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%% plot the motor torques
figure(1)
clf
figure(1)
hold on
plot(time, tau_1, 'g')
plot(time, tau_2, 'b')
plot(time, tau_3, 'r')
hold off
legend('joint 1', 'joint 2', 'joint 3')
grid on; 
xlabel('time [sec]'); ylabel('torques [Nm]'); 

%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%  plot the link
figure(3)
clf
figure(3)
hold on 
axis equal; grid on; axis([-1 1 -1 1]); 
xlabel('x [m]'); ylabel('z [m]'); 
set(gca,'NextPlot','replaceChildren');
for j = 1 : N  
    plot(0, 0, 'ko', 'MarkerSize', 6, 'Linewidth', 2)  
    plot(X1(j), Y1(j), 'bo', 'MarkerSize', 6, 'Linewidth', 2)
    plot(X2(j), Y2(j), 'ro', 'MarkerSize', 6, 'Linewidth', 2)
    line([0 X1(j)], [0 Y1(j)], 'Color', 'b', 'Linewidth', 2); 
    line([X1(j) X2(j)], [Y1(j) Y2(j)], 'Color', 'r', 'Linewidth', 2);  
    F(j) = getframe; 
end
hold off
movie(F); 