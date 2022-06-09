import math

import numpy as np
from matplotlib import pyplot as plt
from numpy.linalg import solve
import sympy as sy  # 用于求导积分等数学计算
from assignment6 import createMatrix, getL2Loss

typeV = 0
typeF = 1


# QR 分解
def QRdec(M, N, arrType):
    h = 1 / (M - 1)
    arr = createMatrix(M, N, arrType)
    q, r = np.linalg.qr(arr, mode="complete")
    # check QR decomposition is correct
    i = 0
    arrB = np.ones(M)
    while i < M:
        arrB[i] = 1 / (1 + (i * h) ** 2)
        i += 1
    x1 = np.linalg.lstsq(r, np.transpose(q) @ np.transpose(arrB), rcond=None)[0]
    print("when M is", M, ",N is ", N, ",least square system with QR :", x1)
    L2_norm = np.linalg.norm(arr @ x1 - arrB)
    print("loss is", L2_norm)
    return x1


# 4.1 QR 分解
# QRdec(16, 4, typeV)
# QRdec(16, 8, typeV)

# 4.2 plot gV, gF
# unsolved
if __name__ == "__main__":
    N = 8
    M = 16
    i = 0
    j = 0
    y = 0
    h = 1 / (M - 1)
    type = typeV
    # arr = QRdec(M, N, type)
    x = np.arange(0, 1, 0.01)
    loss, arr = getL2Loss(8, 8, typeV)

    if type == typeV:
        while i < N:
            y += arr[i] * (x ** i)
            i += 1
    else:
        while j < N:
            if 0 <= j < N / 2:
                y += arr[j] * np.sin((j + 1) * np.pi * x)
            else:
                y += arr[j] * np.cos((j + 1 - N / 2) * np.pi * x)
            j += 1
        else:
            i = i + 1
            j = 0


    plt.figure(num=3, figsize=(8, 5))
    # 绘制 y=x^2 的图像，设置 color 为 red，线宽度是 1，线的样式是 --
    plt.plot(x, y, color='red', linewidth=1.0, linestyle='--')
    plt.xlabel('x')
    plt.ylabel('y')
    plt.show()