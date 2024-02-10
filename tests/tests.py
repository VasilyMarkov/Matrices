import numpy as np
import time
from subprocess import Popen, PIPE, STDOUT
import logging

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
    cond = np.linalg.cond(matrix)

    return "WellcondMatrix", matrix, det, cond


def generateIllConditionMatrix(size):
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
    return "Illcond Matrix", matrix, det, cond


def serialize(matrix):
    out_matrix = np.ndarray.flatten(matrix)
    out_data = np.zeros(out_matrix.shape[0]+1)
    out_data[0] = matrix.shape[0]
    out_data[1:] = out_matrix

    data_out = str()
    for i in out_data:
            data_out += str(i) + " "

    return data_out


def runTest(app, generator, size):
    error = False
    gen_name, matrix, det, cond = generator(size)
    app_det = float(runApp(app, serialize(matrix)))
    if abs(app_det-det) > 0.1:
        error = True
    return gen_name, error, det, app_det, cond


def parseAppOut(out):
    errors = ["bad_alloc", "out_of_range", "non square matrix", "degenerate matrix", "Test"]
    err_msg = False
    for err in errors:
        if out.find(err) != -1:
            raise Exception(out)
    return out

def runApp(app, data):
    pipe = Popen([app], stdout=PIPE, stdin=PIPE)
    out = pipe.communicate(input=bytes(data, "UTF-8"))
    return parseAppOut(out[0].decode())


COND_TRESHOLD = 1e10


def end_to_end(app, n):
    print("Running tests...")
    logging.basicConfig(filename="tests/results.log", format='%(asctime)s: %(levelname)s %(message)s', datefmt='%H:%M:%S', level=logging.INFO)
    try:

        for i in range(2,n+1):
            gen_name, err, det, app_det, cond = runTest(app, generateMatrix, i)
            if err and cond >  COND_TRESHOLD:
                logging.error(f'Runing {gen_name} test. Matrix size: {i}. Ill conditional number. Error: {abs(det-app_det)}')
            elif err and not cond:
                logging.critical(f'Runing {gen_name} test. Matrix size: {i}. Well conditional number co. Det: {det}, app_det: {app_det}.')
            else:
                logging.info(f'Runing {gen_name} test. Matrix size: {i}. Test passed')

            gen_name, err, det, app_det, cond = runTest(app, generateIllConditionMatrix, i)
            if err and cond >  COND_TRESHOLD:
                logging.error(f'Runing {gen_name} test. Matrix size: {i}. Ill conditional number. Error: {abs(det-app_det)}')
            elif err and not cond:
                logging.critical(f'Runing {gen_name} test. Matrix size: {i}. Well conditional number co. Det: {det}, app_det: {app_det}.')
            else:
                logging.info(f'Runing {gen_name} test. Matrix size: {i}. Test passed')

        
    except Exception as e:
        logging.critical(f'Runing {gen_name} test. Matrix size: {i}. Error: {e}')
    
    print("Tests finished.")

if __name__ == '__main__':
    app = "./matrices"
    n = 100
    end_to_end(app, n)