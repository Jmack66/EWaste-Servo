import numpy as np
import control as ct

kappa = 0.0829
A = [0,1]
B = [kappa]

Q = [1,1]
R = 1

K,S,E = ct.lqr(A,B,Q,R)

print(K)