
#5.1 image alignment
import cv2
import numpy as np
from numpy.linalg import solve
from scipy.linalg import lu

from assignment6 import choleskyDec

if __name__ == "__main__":

    arrA = [
        [120, 185, 0, 0, 1, 0],
        [0, 0, 120, 185, 0, 1],
        [280, 192, 0, 0, 1, 0],
        [0, 0, 280, 192, 0, 1],
        [430, 180, 0, 0, 1, 0],
        [0, 0, 430, 180, 0, 1],
        [145, 368, 0, 0, 1, 0],
        [0, 0, 145, 368, 0, 1],
        [424, 438, 0, 0, 1, 0],
        [0, 0, 424, 438, 0, 1]
    ]
    arrB = [42, 405, 187, 367, 311, 320, 110, 559, 379, 544]

    # LU
    p, l, u = lu(np.transpose(arrA) @ arrA)
    y_LU = solve(p @ l, np.transpose(arrA) @ np.transpose(arrB))
    x_LU = solve(u, y_LU)

    ## QR

    q, r = np.linalg.qr(np.transpose(arrA) @ arrA, mode="complete")
    x_QR = solve(r, q.T @ np.transpose(arrA) @ np.transpose(arrB))

    ## Cholesky
    L = choleskyDec(arrA)
    x_cholesky = solve(L @ L.T, np.transpose(arrA) @ np.transpose(arrB))

    print(x_LU)
    print(x_QR)
    print(x_cholesky)
    # image

    choosedX = x_cholesky
    arrD = [[choosedX[0], choosedX[1], choosedX[4] + 120],
            [choosedX[2], choosedX[3], choosedX[5]]]
    npArrD = np.mat(arrD)
    ajustArr = np.float32([[1, 0, 120],
                          [0, 1, 0]])

    print(npArrD)
    # read image
    img1 = cv2.imread('./1.png', cv2.IMREAD_GRAYSCALE)
    img2 = cv2.imread('./2.png', cv2.IMREAD_GRAYSCALE)
    rows, cols = img1.shape[:2]

    img1 = cv2.warpAffine(img1, npArrD, (cols + 250, rows + 250))
    img2 = cv2.warpAffine(img2, ajustArr, (cols + 250, rows + 250))
    img2 = cv2.addWeighted(img1, 0.5, img2, 0.5, 0)
    cv2.imwrite("./new.jpg", img2)
    cv2.imshow('dst', img2)
    cv2.waitKey(0)
