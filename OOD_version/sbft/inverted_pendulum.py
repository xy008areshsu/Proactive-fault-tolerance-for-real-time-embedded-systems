from cyber_physical_system import LinearCPS

import numpy
import math
from pylab import figure, plot, xlabel, grid, hold, legend, title, savefig, show
from matplotlib.font_manager import FontProperties


class InvertedPendulumTest(LinearCPS):
    
    def  __init__(self, A, B, K, initX, initU):
        super().__init__(A, B, K, initX, initU)


 # to save data to a file, run: python3 inverted_pendulum.py > invertedPendulum.dat
if __name__ == '__main__': 

    """ System parameters

    These parameters, including the K matrix, are predefined. A, B matrices are system dynamics which, once defined, cannot be changed. K matrix is the control gain matrix, which determines your control force u. You can tune it during the design.  
    """
    A = numpy.mat([[0., 1.0, 0., 0.],
                   [0., -0.18182, 2.6727, 0.],
                   [0., 0., 0., 1.],
                   [0., -0.45455, 31.1820, 0.]])

    B = numpy.mat([[0.0],
                   [1.8182],
                   [0.],
                   [4.5455]])

    K = numpy.mat([-61.9930, -33.5054, 95.0600, 18.8300])

    # This is the sampling time period, you can change it to see when the system becomes unstable and would fail
    Ts = 0.01

    # This is the initial state condition, in the form of[cart position (m), cart velocity (m/s), pendulum angle (rad), pendulum angular rate (rad/s)]
    initX = numpy.mat([[0.0],
                       [0.0],
                       [-0.4],
                       [-0.1]])

    # This is the intial control force, now it is designed based on the initial state condition.
    initU = -K * initX
    
    # This is the total simulation time, 10 seconds
    time = numpy.mat(numpy.arange(0., 10, Ts)).T

    inv = InvertedPendulumTest(A, B, K, initX, initU)
    
    inv.evolveSystem(time[-1, 0], Ts)

    for i in range(time.shape[0]):
        print(time[i, 0], inv.x[0, i], inv.x[1, i], inv.x[2, i], inv.x[3, i])  # each row coresponds the state for each time step, with the first col the time, 2 to 5 col the state vars

    figure(1, figsize=(6, 4.5))
    xlabel('time (s)')
    grid(True)
    hold(True)
    lw = 4
    lw2 = 1
    plot(time, inv.x[2, 0:time.shape[0]].T, 'y', linewidth=lw2)
    #plot(time, inv.x[3, 0:time.shape[0]].T, 'k', linewidth=lw2)        
    legend((r'$angle (rad)$', r'$angleRate (rad/s)$'), prop=FontProperties(size=16))
    title('Simple Test Inverted Pendulum')
    savefig('invertedPendulum.png', dpi=100)
    show()

    
