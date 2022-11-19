import random
import numpy as np


def matrixmult(m1, m2):
    s = 0  # сумма
    t = []  # временная матрица
    m3 = []  # конечная матрица
    if len(m2) != len(m1[0]):
        print("Матрицы не могут быть перемножены")
    else:
        r1 = len(m1)  # количество строк в первой матрице
        c1 = len(m1[0])  # Количество столбцов в 1
        r2 = c1  # и строк во 2ой матрице
        c2 = len(m2[0])  # количество столбцов во 2ой матрице
        for z in range(0, r1):
            for j in range(0, c2):
                for i in range(0, c1):
                    s = s + m1[z][i] * m2[i][j]
                t.append(s)
                s = 0
            m3.append(t)
            t = []
    return m3


def readmatrix(path):
    t = []
    m = []
    a = []
    b = np.genfromtxt(path, delimiter="   ", skip_header=0, dtype=int)
    for k in b:
        a.append(k)
    siz = int(np.size(a)**0.5)
    for i in range(0, siz):
        for j in range(0, siz):
            t.append(a[i*siz+j])
        m.append(t)
        t = []
    return m


m1 = readmatrix("C:/Users/vuong/Desktop/inputA.txt")
m2 = readmatrix("C:/Users/vuong/Desktop/inputB.txt")

print("Matrix A:")
print(m1)
print("Matrix B:")
print(m2)

m3 = matrixmult(m1, m2)
print("Matrix AxB:")
print(m3)

m4 = readmatrix("C:/Users/vuong/Desktop/output.txt")
print("Matrix test:")
print(m4)


if (np.array_equal(m3, m4)):
    print("It's alright")
else:
    print("Fatal error")

