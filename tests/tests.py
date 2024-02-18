import numpy as np
import time
from subprocess import Popen, PIPE, STDOUT
import logging
import generators

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
    errors = ["bad_alloc", "out_of_range", "Invalid input data"]
    for err in errors:
        if out.find(err) != -1:
            raise Exception(out)
    return out


def runApp(app, data):
    pipe = Popen([app], stdout=PIPE, stdin=PIPE)
    out = pipe.communicate(input=bytes(data, "UTF-8"))
    return parseAppOut(out[0].decode())


def writeGenLog(gen_name, err, cond, i):
    COND_TRESHOLD = 1e10
    match gen_name:
        case "Well Matrix":
            if err and cond > COND_TRESHOLD:
                logging.error(f'Runing {gen_name} test. Matrix size: {i}. Ill conditional number')
            elif err and not cond:
                logging.critical(f'Runing {gen_name} test. Matrix size: {i}. Well conditional number')
            else:
                logging.info(f'Runing {gen_name} test. Matrix size: {i}. Test passed')
        case "Ill Matrix":
            if err and cond > COND_TRESHOLD:
                logging.error(f'Runing {gen_name} test. Matrix size: {i}. Ill conditional number')
            elif err and not cond:
                logging.critical(f'Runing {gen_name} test. Matrix size: {i}. Well conditional number')
            else:
                logging.info(f'Runing {gen_name} test. Matrix size: {i}. Test passed')
        case "Degen Matrix":
            if err:
                logging.critical(f'Runing {gen_name} test. Matrix size: {i}. Test failed')
            else:
                logging.info(f'Runing {gen_name} test. Matrix size: {i}. Test passed')


def exceptionLog(e, i):
    if e.args[0] == "Invalid input data" and e.args[1] == "None Square Matrix":  
        logging.info(f'Runing {e.args[1]} test. Matrix size: {i}. Test passed')
    else:
        logging.info(f'Runing {e.args[1]} test. Matrix size: {i}. Error: {e.args[0]}')


def end_to_end(app, n): 
    logging.basicConfig(filename="tests/results.log", format='%(asctime)s: %(levelname)s %(message)s', datefmt='%H:%M:%S', level=logging.INFO)
    
    print("Running tests...")
    for name, val in generators.__dict__.items():
        if callable(val):
            for i in range(2,n+1):     
                try:
                    gen_name, err, det, app_det, cond = runTest(app, val, i)
                    writeGenLog(gen_name, err, cond, i)
                except Exception as e:
                    exceptionLog(e, i)
    print("Tests finished.")


if __name__ == '__main__':
    app = "./matrices"
    n = 100
    end_to_end(app, n)