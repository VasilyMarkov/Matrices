import numpy as np
import time
from subprocess import Popen, PIPE, STDOUT
import logging
import generators as gen

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
    try:
        app_det = float(runApp(app, serialize(matrix)))
        if abs(app_det-det) > 0.00001:
            error = True
    except Exception as e:
        raise  Exception(e, gen_name)
    return gen_name, error, det, app_det, cond


def parseAppOut(out):
    errors = ["bad_alloc", "out_of_range", "non square matrix", "degenerate matrix", "Division by zero", "Invalid input data"]
    for err in errors:
        if out.find(err) != -1:
            raise Exception(out)
    return out


def runApp(app, data):
    pipe = Popen([app], stdout=PIPE, stdin=PIPE)
    out = pipe.communicate(input=bytes(data, "UTF-8"))
    return parseAppOut(out[0].decode())


def end_to_end(app, n):
    COND_TRESHOLD = 1e10
    print("Running tests...")
    logging.basicConfig(filename="tests/results.log", format='%(asctime)s: %(levelname)s %(message)s', datefmt='%H:%M:%S', level=logging.INFO)
    try:

        for i in range(2,n+1):
            gen_name, err, det, app_det, cond = runTest(app, gen.wellMatrix, i)
            if err and cond >  COND_TRESHOLD:
                logging.error(f'Runing {gen_name} test. Matrix size: {i}. Ill conditional number. Error: {abs(det-app_det)}')
            elif err and not cond:
                logging.critical(f'Runing {gen_name} test. Matrix size: {i}. Well conditional number co. Det: {det}, app_det: {app_det}.')
            else:
                logging.info(f'Runing {gen_name} test. Matrix size: {i}. Test passed')

            gen_name, err, det, app_det, cond = runTest(app, gen.illMatrix, i)
            if err and cond >  COND_TRESHOLD:
                logging.error(f'Runing {gen_name} test. Matrix size: {i}. Ill conditional number. Error: {abs(det-app_det)}')
            elif err and not cond:
                logging.critical(f'Runing {gen_name} test. Matrix size: {i}. Well conditional number co. Det: {det}, app_det: {app_det}.')
            else:
                logging.info(f'Runing {gen_name} test. Matrix size: {i}. Test passed')
        print("Tests finished.")
        
    except Exception as e:
        # logging.critical(f'Runing {gen_name} test. Matrix size: {i}. Error: {e}')
        print("Tests failed.")
    

import string
import random

def id_generator(size=6, chars=string.ascii_uppercase + string.digits):
    return ''.join(random.choice(chars) for _ in range(size))


if __name__ == '__main__':
    app = "./matrices"
    n = 100
    end_to_end(app, n)