import subprocess
import numpy as np
import scipy as sp
import time
from subprocess import Popen, PIPE, STDOUT
from pathlib import Path

def generateMatrix(size):
    rng = np.random.default_rng()
    l_bound = 1
    u_bound = 1.1
    # pivot = (u_bound - l_bound)*rng.random(1)+l_bound #[l_bound, u_bound) 
    pivot = 1.1
    det = np.round(pivot**size, 5)
    diag = np.zeros((size,size))
    np.fill_diagonal(diag, pivot)
    LU = np.random.normal(0, 1, (size,size))
    I = np.identity(size)
    L = np.tril(LU, -1) + I
    U = np.triu(LU, 1) + I
    # matrix = np.round(L @ diag @ U, 5)
    matrix = L @ diag @ U
    return matrix, det

def serialize(matrix, n):
    out_matrix = np.ndarray.flatten(matrix)
    out_data = np.zeros(out_matrix.shape[0]+1)
    out_data[0] = n
    out_data[1:] = out_matrix

    data_out = str()
    for i in out_data:
            data_out += str(i) + " "
    return data_out


def runApp(app, data):
    pipe = Popen([app], stdout=PIPE, stdin=PIPE)
    out = pipe.communicate(input=bytes(data, "UTF-8"))
    return out[0].decode()


if __name__ == '__main__':
    app = "/home/vasily/usr/phystech/C++/labs/matrices/matrices"
    n = 50
    matrix, det = generateMatrix(n)

    test = np.array([[2,4,1],
                     [5,2,1],
                     [2,3,4]])
    n = 3
    det = np.linalg.det(test)
    out = runApp(app, serialize(test, 3))
    # print(matrix)
    print(out)
    print(f"Ref det: {det}")

