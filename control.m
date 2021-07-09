kappa = 0.0829;
% 
% A=[0 1;0 0];
% B = [kappa; 0];
% Q = [1 0; 0 1];
% R = 1;
% 
% K = lqr(A,B,Q,R);

sys = tf(1,[0 kappa 0])
%step(sys)
c_pid = pidTuner(sys,'PID')
T_pid = feedback(C*sys,1);
[y,tOut] = step(T_pid)

A = [tOut(:) y(:)];
writematrix(A,'PIDTune2.csv');