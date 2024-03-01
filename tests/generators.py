import numpy as np


def matrix(size):
    ref = np.array([-1,1])

    diag = np.array([ref[np.random.randint(2, size = 1)] for _ in range(size)]).reshape(size)
    det = np.prod(diag)
    D = np.diag(diag)
    LU = np.random.rand(size,size)
    I = np.identity(size)
    L = np.tril(LU, -1) + I
    U = np.triu(LU, 1) + I
    matrix = L @ D @ U
    cond = np.linalg.cond(matrix)

    return "Matrix", matrix, det, cond


def wellMatrix(size):
    pivot = 1.1
    det = pivot**size
    diag = np.zeros((size,size))
    np.fill_diagonal(diag, pivot)
    LU = np.random.randint(1, 3, (size,size))
    I = np.identity(size)
    L = np.tril(LU, -1) + I
    U = np.triu(LU, 1) + I
    matrix = L @ diag @ U
    cond = np.linalg.cond(matrix)

    return "Well Matrix", matrix, det, cond


def illMatrix(size):
    pivots = np.array(size)

    small_pivots = np.random.normal(0, 0.01, size//2)
    if size % 2 != 0:
        big_pivots = np.random.randint(100, 10000, (size//2)+1)
    else:
        big_pivots = np.random.randint(100, 10000, (size//2))  
    
    pivots = np.random.permutation(np.concatenate((small_pivots, big_pivots), None))
    det = np.prod(pivots)
    diag = np.zeros((size,size))
    np.fill_diagonal(diag, pivots)
    LU = np.random.randint(1, 5, (size,size))
    I = np.identity(size)
    L = np.tril(LU, -1) + I
    U = np.triu(LU, 1) + I

    matrix = matrix = L @ diag @ U
    cond = np.linalg.cond(matrix)
    return "Ill Matrix", matrix, det, cond


def degenerateMatrix(size):
    row = np.random.normal(0, 2, (size))
    coeffs = np.random.normal(0, 2, (size))
    matrix =  row * coeffs[:, None]
    return "Degen Matrix", matrix, 0, None


def nonSquareMatrix(size):
    row = np.random.randint(1, size+1)
    col = np.random.randint(1, size+1)
    if col == row:
        if col == 1:
            col += 1
        else:
            col -= 1
    matrix = np.random.normal(0, 2, (row, col))
    return "None Square Matrix", matrix, None, None

