import math

import cv2
import numpy
import numpy as np
import scipy
from cv2.cv2 import CV_32F
from matplotlib import pyplot as plt
from numpy.linalg import solve
from scipy.linalg import lu
import math
import scipy.integrate as si

typeV = 0
typeF = 1


def gd(x, mu=0, sigma=1):
    left = 1 / (np.sqrt(2 * math.pi) * np.sqrt(sigma))
    right = np.exp(-(x - mu) ** 2 / (2 * sigma))
    return left * right


# 是否正定
def is_pos_def(A):
    return np.all(np.linalg.eigvals(A) > 0)


# 生成等差数列
def arithList(first, end, step):
    x = []
    for i in np.arange(first, end, step):
        x.append(i)
    return x


# create Matrix base type
def createMatrix(M, N, arrType):
    i = 0
    j = 0
    h = 1 / (M - 1)
    arr = np.zeros((M, N))
    if arrType == typeV:
        while i < M:
            while j < N:
                arr[i][j] = (i * h) ** j
                j = j + 1
            else:
                i = i + 1
                j = 0
    else:
        while i < M:
            while j < N:
                if 0 <= j < N / 2:
                    arr[i][j] = math.sin((j + 1) * math.pi * (i * h))
                else:
                    arr[i][j] = math.cos((j + 1 - N / 2) * math.pi * (i * h))
                j += 1
            else:
                i = i + 1
                j = 0

    return arr


#  获取 L2Loss 的函数  by LU 分解
def getL2Loss(M, N, arrType):
    arrB = np.ones(N)
    arr = createMatrix(M, N, arrType)
    h = 1 / (M - 1)
    i = 0
    while i < N:
        arrB[i] = 1 / (1 + (i * h) ** 2)
        i += 1

    p, l, u = lu(arr)

    # 求解方程
    y = solve(p @ l, arrB)
    x = solve(u, y)
    print(np.allclose(np.dot(arr, x), arrB))

    # 求 L2 损失
    L2_norm = np.linalg.norm(arr @ x - arrB)
    print("when M is ", M, " N is ", N, " arr L2 norm is", L2_norm)

    return L2_norm, x


# 获取 Cond
def getCond(arr):
    return numpy.linalg.cond(arr)


# 绘制 N - L2 Cond 图
def plot_N_Cond(arrType):
    x_arr = arithList(4, 33, 2)
    y_arr = numpy.zeros(15, dtype=float, order='C')
    index = 0
    while index < 15:
        y_arr[index] = getCond(createMatrix(x_arr[index], x_arr[index], arrType))
        index += 1

    plt.plot(x_arr, y_arr)
    plt.suptitle("plot N vs. cond(V )" if arrType == typeV else "plot N vs. cond(F )",  # 标题名称
                 x=0.5,  # x轴方向位置
                 y=0.98,  # y轴方向位置
                 size=15,  # 大小
                 ha='center',  # 水平位置，相对于x,y，可选参数：{'center', 'left', right'}, default: 'center'
                 va='top',  # 垂直位置，相对于x,y，可选参数：{'top', 'center', 'bottom', 'baseline'}, default: 'top'
                 weight='bold',  # 字体粗细，以下参数可选
                 rotation=1,  ##标题旋转，传入旋转度数，也可以传入vertical', 'horizontal'
                 )
    plt.yscale("log")
    plt.show()


# Cholesky 分解
def choleskyDec(arr):
    arr = np.transpose(arr) @ arr
    L = np.linalg.cholesky(arr)
    print("cholesky assert: ", np.allclose(np.dot(L, L.T), arr))  # 验证计算
    return L


