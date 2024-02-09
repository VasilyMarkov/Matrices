import subprocess
import numpy as np
import scipy as sp
import time
from subprocess import Popen, PIPE, STDOUT
from pathlib import Path

def generateMatrix(size):
    pivot = 1.1
    det = pivot**size
    diag = np.zeros((size,size))
    np.fill_diagonal(diag, pivot)
    LU = np.random.randint(1, 2, (size,size))
    I = np.identity(size)
    L = np.tril(LU, -1) + I
    U = np.triu(LU, 1) + I
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
    n = 100
    matrix, det = generateMatrix(n)
    out = runApp(app, serialize(matrix, n))
    print(f"Ref det: {det}")
    print(out)

