import numpy as np
from subprocess import Popen, PIPE, STDOUT
import logging
import generators
from os import listdir
from os.path import isfile, join

def createLogger(name):
    dir_path = 'tests/'
    logger = logging.getLogger(name)
    logger.setLevel(logging.DEBUG)
    file_handler = logging.FileHandler(dir_path+name)  
    formatter = logging.Formatter('%(asctime)s: %(levelname)s %(message)s')
    file_handler.setFormatter(formatter)
    logger.addHandler(file_handler)
    return logger

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


def runCornerCaseTests(app, data_path, logger):
    file_list = [f for f in listdir(data_path) if isfile(join(data_path, f))]
    file_list.sort()
    for file in file_list:
        log(runTestFromFile(app, data_path+file), logger)


def runTest(app, generator, size, retMatr = False):
    error = False
    gen_name, matrix, det, cond = generator(size)
    try:
        app_det = float(runApp(app, serializeMatrix(matrix)))
        if abs(app_det-det) > 0.001:
            error = True
    except Exception as e:
        raise  Exception(e, gen_name)
    retDict = {"name": gen_name, "err": error, "det": det, "app_det": app_det, "cond": cond}

    if retMatr:
        return retDict, matrix
    return retDict


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


def genLog(results, i, logger):
    COND_TRESHOLD = 1e10

    if results["name"] == "Degen Matrix":
        if results["err"]:
            logger.critical(f'Runing {results["name"]} test. Matrix size: {i}. Test failed')
        else:
            logger.info(f'Runing {results["name"]} test. Matrix size: {i}. Test passed')
    else:
        if results["err"] and results["cond"] > COND_TRESHOLD:
            logger.error(f'Runing {results["name"]} test. Matrix size: {i}. Ill conditional number')
        elif results["err"] and not results["cond"]:
            logger.critical(f'Runing {results["name"]} test. Matrix size: {i}. Well conditional number')
        else:
            logger.info(f'Runing {results["name"]} test. Matrix size: {i}. Test passed')


def log(results, logger):
    if "except" in results:
        logger.error(f'Runing "{results["name"]}" test. Exception: {results["except"]}')
    elif results["err"] == False:    
        logger.info(f'Runing "{results["name"]}" test. Test passed')
    else:
        logger.critical(f'Runing "{results["name"]}" test. Test failed')


def log(results, logger):
    if "except" in results:
        logger.error(f'Runing "{results["name"]}" test. Exception: {results["except"]}')
    elif results["err"] == False:    
        logger.info(f'Runing "{results["name"]}" test. Test passed')
    else:
        logger.critical(f'Runing "{results["name"]}" test. Test failed')


def end_to_end(app, n): 
    print("Running tests...")
    data_path = "data/"
    logger = createLogger("log")
    runCornerCaseTests(app, data_path, logger)
    
    perf_errors = 0
    gen_logger = createLogger("gen_log")
    print(" Perfomance tests...")
    for _, val in generators.__dict__.items():
        if callable(val):
            for i in range(2,n+1):     
                try:
                    result = runTest(app, val, i)
                    if results["err"]: 
                        perf_errors += 1
                    genLog(result, i, gen_logger)
                except Exception as e:
                    ...
    print(f" Perfomance erros: {perf_errors}")

    common_errors = 0
    error_logger = createLogger("err_log")
    print(" Common tests...")
    iterations = 1000
    matr_size = 10
    for i in range(iterations):
        results, matrix = runTest(app, generators.matrix, matr_size, retMatr=True)
        if results["err"] == True:
           error_logger.error(matrix)
           common_errors += 1

    print(f" Common erros: {common_errors}")
    print("Tests finished.")


if __name__ == '__main__':
    app = "./matrices"
    n = 100
    end_to_end(app, n)