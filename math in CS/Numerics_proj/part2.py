import numpy as np
from matplotlib import pyplot as plt
from numpy.linalg import solve

from assignment6 import getL2Loss, typeV, typeF, plot_N_Cond, arithList, createMatrix, is_pos_def, getCond, choleskyDec

if __name__ == "__main__":
    # 3.1
    getL2Loss(8, 8, typeV)
    getL2Loss(16, 16, typeV)
    getL2Loss(8, 8, typeF)
    getL2Loss(16, 16, typeF)

    # 3.2
    plot_N_Cond(typeV)
    plot_N_Cond(typeF)

    # 3.3 get table
    col = arithList(4, 33, 2)
    col2 = arithList(20, 33, 2)
    row = ["isposdef(Av)", "isposdef(Af)", "condV", "condF"]
    vals = np.zeros((4, 7))
    i = 0
    j = 8
    while j < 15:
        while i < 4:
            arrV = createMatrix(col[j], col[j], typeV)
            arrF = createMatrix(col[j], col[j], typeF)
            Av = np.transpose(arrV) @ arrV
            Af = np.transpose(arrF) @ arrF
            if i == 0:
                vals[i][j - 8] = is_pos_def(Av)
            elif i == 1:
                vals[i][j - 8] = is_pos_def(Af)
            elif i == 2:
                vals[i][j - 8] = getCond(arrV)
            elif i == 3:
                vals[i][j - 8] = getCond(arrF)
            i += 1
        j += 1
        i = 0

    formatVals = np.round(vals, 2)
    plt.figure(figsize=(20, 8), dpi=300)
    tab = plt.table(cellText=formatVals,
                    colLabels=col2,
                    rowLabels=row,
                    loc='center',
                    cellLoc='center',
                    rowLoc='center')
    tab.scale(1, 2)
    tab.set_fontsize(20)
    plt.axis('off')
    plt.show()

    # 3.4 cholesky
    M = 8
    N = 8
    arrV = createMatrix(8, 8, typeV)
    arrF = createMatrix(8, 8, typeF)
    arrB = np.zeros(M)
    h = 1 / (M - 1)
    i = 0
    while i < M:
        arrB[i] = 1 / (1 + (i * h) ** 2)
        i += 1
    L = choleskyDec(arrV)
    y = solve(L, arrV.T @ arrB)
    x = solve(L.T, y)
    loss = np.linalg.norm(arrV @ x - arrB)
    print("V L2 norm is: ", loss)
    L = choleskyDec(arrF)
    y = solve(L, arrF.T @ arrB)
    x = solve(L.T, y)
    loss = np.linalg.norm(arrF @ x - arrB)
    print("F L2 norm is: ", loss)
