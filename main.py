import cpplib
import math
from datetime import datetime
from concurrent.futures import ThreadPoolExecutor
import time


def sum_sin(angle, count):
    result = 0
    for i in range(count):
        result += math.sin(angle)
    return result


def sum_cos(angle, count):
    result = 0
    for i in range(count):
        result += math.cos(angle)
    return result


def sum_tan(angle, count):
    result = 0
    for i in range(count):
        result += math.tan(angle)
    return result


def sum_ctan(angle, count):
    result = 0
    for i in range(count):
        result += 1 / math.tan(angle)
    return result


def PythonParallels(angle: float, count: int):
    with ThreadPoolExecutor(4) as executor:
        executor.submit(sum_sin, angle, count)
        executor.submit(sum_cos, angle, count)
        executor.submit(sum_tan, angle, count)
        executor.submit(sum_ctan, angle, count)


def PythonProcess(angle: float, count: int):
    result = 0
    for i in range(count):
        result += math.sin(10)

    result = 0
    for i in range(count):
        result += math.cos(10)
    result = 0
    for i in range(count):
        result += math.tan(10)
    result = 0
    for i in range(count):
        result += 1 / math.tan(10)


count = 20000000

cpp_parallels = cpplib.parallel(10, count)
print(f"Cpp parallels: {cpp_parallels}")

start_time = datetime.now()
PythonParallels(10, count)
python_time = datetime.now() - start_time
print(f"python parallels : {python_time}")

print(f"Parallels relation: {python_time / cpp_parallels}")
print()

cpp_sequence = cpplib.sequence(10, count)
print(f"Cpp sequence: {cpp_sequence}")

start_time = datetime.now()
PythonProcess(10, count)
python_time = datetime.now() - start_time
print(f"python sequence time: {python_time}")

print(f"Sequence relate: {python_time / cpp_sequence}")

x = [1, 2, 3]

print(cpplib.sum_vector(x))
