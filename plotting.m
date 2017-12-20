t = 1:33;

max2 = 8.4;
max3 = 6;
%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(1)
clf
figure(1)
plot(t, position);
legend('joint 2', 'joint 3')
grid on; 
xlabel('time [sec]'); ylabel('angular displacement [rad]'); 
%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(2)
clf
figure(2)
subplot(2,1,1);
plot(t, velocity2);
legend('joint 2');
grid on
xlabel('time [sec]'); ylabel('angular velocity [ticks/s]'); 
subplot(2,1,2);
plot(t, velocity3);
legend('joint 3');
grid on
xlabel('time [sec]'); ylabel('angular velocity [ticks/s]'); 
%% %%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
figure(3)
clf
figure(3)
subplot(2,1,1);
plot(t, torque2/100*max2);
legend('joint 2');
grid on
xlabel('time [sec]'); ylabel('torque [Nm]'); 
subplot(2,1,2);
plot(t, torque3/100*max3);
legend('joint 3');
grid on
xlabel('time [sec]'); ylabel('torque [Nm]'); 