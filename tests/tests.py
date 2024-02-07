import subprocess
import numpy as np
import scipy as sp
import time

n = 3
el = 1

start = time.time()
d = np.random.normal(0, 1.8, size = n)
stop = time.time()
d = np.zeros((n,n))
np.fill_diagonal(d, el)

lu = np.random.normal(loc = 0, scale = 1, size = (n,n))
i = np.identity(n)
l = np.tril(lu, -1) + i
u = np.triu(lu, 1) + i

a = l @ d @ u

print(np.linalg.det(d))
print(np.linalg.det(a))
print(a)
# print(stop-start)