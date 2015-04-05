import numpy as np
from pylab import figure, plot, xlabel, ylabel, grid, hold, legend, title, savefig, show
from matplotlib.font_manager import FontProperties

class LinearRegression:

    def __init__(self, filename):
        self.data = np.loadtxt(open(filename), delimiter=',')
        self.features = self.data[:, 0:-1]
        self.features = np.concatenate((np.ones((np.shape(self.features)[0], 1)), self.features), 1)
        self.out = self.data[:, -1]
        self.out = np.mat(self.out).T
        self.theta = np.zeros((np.shape(self.features)[1], 1))
        
        
        

    def plotData_2D(self, x, y):
        figure()
        xlabel('features')
        ylabel('outputs')
        hold(True)
        grid(True)
        plot(x, y, 'rx', linewidth = 2)
        plot(x, self.features * self.theta, '-', linewidth = 2)
        show()

    def computeCost(self):
        m = np.shape(self.out)[0]
        J = 0

        x_val = self.features.T
        h = np.dot(self.theta.T, x_val)
        h = h.T
        J = sum(np.power((h - self.out), 2)) / (2 *m)
        return J[0,0]

    def gradientDescent(self, alpha, num_iters):
        m = np.shape(self.out)[0]
        J_history = np.zeros((num_iters, 1))

        for iter in range(num_iters):
            x_val = self.features.T
            h = np.dot(self.theta.T, x_val)
            h = h.T
            sig_sum = np.concatenate((sum(np.multiply((h - self.out), np.mat(self.features[:, 0]).T)), sum(np.multiply((h - self.out), np.mat(self.features[:, 1]).T))))
            self.theta = self.theta - (alpha / m) * sig_sum


            J_history[iter] = self.computeCost()
    



if __name__ == '__main__':
    lr = LinearRegression('ex1data1.txt')

    #print(lr.data)
    #lr.plotData_2D(lr.features[:, 1], lr.out)

    print(lr.computeCost())

    alpha = 0.01
    iterations = 1500
    
    lr.gradientDescent(alpha, iterations)

    print(lr.theta)

    lr.plotData_2D(lr.features[:, 1], lr.out)
    
