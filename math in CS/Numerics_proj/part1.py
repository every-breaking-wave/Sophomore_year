
import numpy as np
from matplotlib import pyplot as plt
import scipy.integrate as si
from assignment6 import gd

if __name__ == "__main__":
    #  2 绘制正态曲线
    x = np.arange(-4, 5, 0.1)
    y_1 = gd(x, 0, 0.3)
    y_2 = gd(x, 0, 1.2)
    y_3 = gd(x, 0, 4.0)
    y_4 = gd(x, -2, 0.5)

    plt.plot(x, y_1, color='green')
    plt.plot(x, y_2, color='blue')
    plt.plot(x, y_3, color='yellow')
    plt.plot(x, y_4, color='red')
    plt.xlim(-5.0, 5.0)
    plt.ylim(-0.2, 1)

    ax = plt.gca()
    ax.spines['right'].set_color('none')
    ax.spines['top'].set_color('none')
    ax.xaxis.set_ticks_position('bottom')
    ax.spines['bottom'].set_position(('data', 0))
    ax.yaxis.set_ticks_position('left')
    ax.spines['left'].set_position(('data', 0))

    plt.legend(labels=['$\mu = 0, \sigma^2=0.2$', '$\mu = 0, \sigma^2=1.0$', '$\mu = 0, \sigma^2=5.0$',
                       '$\mu = -2, \sigma^2=0.5$'])
    plt.show()

    y_1 = lambda x: gd(x, 0, 0.3)
    y_2 = lambda x: gd(x, 0, 1.2)
    y_3 = lambda x: gd(x, 0, 4.0)
    y_4 = lambda x: gd(x, -2, 0.5)
    area_1 = si.quad(y_1, -5, 5)
    area_2 = si.quad(y_2, -5, 5)
    area_3 = si.quad(y_3, -10, 10)
    area_4 = si.quad(y_4, -7, 3)
    print(area_1)
    print(area_2)
    print(area_3)
    print(area_4)
