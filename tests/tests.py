import numpy as np
from subprocess import Popen, PIPE, STDOUT
import logging
import generators
from os import listdir
from os.path import isfile, join

def serializeMatrix(matrix):
    out_matrix = np.ndarray.flatten(matrix)
    out_data = np.zeros(out_matrix.shape[0]+1)
    out_data[0] = matrix.shape[0]
    out_data[1:] = out_matrix

    data_out = str()
    for i in out_data:
            data_out += str(i) + " "
    return data_out

def serialize(size, array):
    data_out = str(size)
    for i in array:
            data_out += str(i) + " "

    return data_out

def runTestFromFile(app, file_path):
    file = open(file_path)
    data = file.read()
    arr = np.fromstring(data, dtype=float, sep=' ')
    
    size = int(arr[0])
    arr = arr[1:]
    matrix = np.array(1)
    error = False
    
    try:
        if size*size == arr.shape[0]:
            matrix = arr.reshape((size, size))
            det = np.linalg.det(matrix)
            app_det = float(runApp(app, serializeMatrix(matrix)))
            if abs(app_det-det) > 0.00001:
                error = True
        else:
            runApp(app, serialize(size, arr))

    except Exception as e:
        return {"name": file_path, "err": error, "except": e}
    return {"name": file_path, "err": error}


def runCornerCaseTests(app, data_path):
    file_list = [f for f in listdir(data_path) if isfile(join(data_path, f))]
    file_list.sort()
    for file in file_list:
        log(runTestFromFile(app, data_path+file))


def runTest(app, generator, size):
    error = False
    gen_name, matrix, det, cond = generator(size)
    try:
        app_det = float(runApp(app, serialize(matrix)))
        if abs(app_det-det) > 0.00001:
            error = True
    except Exception as e:
        raise  Exception(e, gen_name)
    return {"name": gen_name, "err": error, "det": det, "app_det": app_det, "cond": cond}


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


def genLog(results, i):
    logging.basicConfig(filename="tests/results.log", format='%(asctime)s: %(levelname)s %(message)s', datefmt='%H:%M:%S', level=logging.INFO)
    COND_TRESHOLD = 1e10
    
    if results["name"] == "Degen Matrix":
        if results["err"]:
            logging.critical(f'Runing {results["name"]} test. Matrix size: {i}. Test failed')
        else:
            logging.info(f'Runing {results["name"]} test. Matrix size: {i}. Test passed')
    else:
        if results["err"] and results["cond"] > COND_TRESHOLD:
            logging.error(f'Runing {results["name"]} test. Matrix size: {i}. Ill conditional number')
        elif results["err"] and not results["cond"]:
            logging.critical(f'Runing {results["name"]} test. Matrix size: {i}. Well conditional number')
        else:
            logging.info(f'Runing {results["name"]} test. Matrix size: {i}. Test passed')


def log(results):
    logging.basicConfig(filename="tests/common.log", format='%(asctime)s: %(levelname)s %(message)s', datefmt='%H:%M:%S', level=logging.INFO)
    
    if "except" in results:
        logging.error(f'Runing "{results["name"]}" test. Exception: {results["except"]}')
    elif results["err"] == False:    
        logging.info(f'Runing "{results["name"]}" test. Test passed')
    else:
        logging.critical(f'Runing "{results["name"]}" test. Test failed')


def end_to_end(app, n): 
    print("Running tests...")
    data_path = "data/"
    runCornerCaseTests(app, data_path)

    # for _, val in generators.__dict__.items():
    #     if callable(val):
    #         for i in range(2,n+1):     
    #             try:
    #                 genLog(runTest(app, val, i))
    #             except Exception as e:
    #                 ...
    #                 # log(e.args[0],e.args[1], i)
    print("Tests finished.")


if __name__ == '__main__':
    app = "./matrices"
    n = 100
    end_to_end(app, n)