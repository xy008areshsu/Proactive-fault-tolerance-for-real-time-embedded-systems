import unittest
from should_dsl import should, should_not
import numpy
from pylab import figure, plot, xlabel, grid, hold, legend, title, savefig, show
from matplotlib.font_manager import FontProperties


from sbft.cyber_physical_system import LinearCPS
from sbft.ground_vehicle_system import CarABSTest
from sbft.inverted_pendulum import InvertedPendulumTest

class TestLinearCPS(unittest.TestCase):
    
    def setUp(self):
        self.A = numpy.mat([[2.0, 0.0],
                 [1.0, -1.0]])

        self.B = numpy.mat([[1.0],
                 [1.0]])

        self.K = numpy.mat([2.625, -0.625])
        self.Ts = 0.01
        self.tol = 0.00001

        self.initX = numpy.mat([[1.0],
                                [1.0]])
        self.initU = -self.K * self.initX
        self.cps = LinearCPS(self.A, self.B, self.K)
        self.cps2 = LinearCPS(self.A, self.B, self.K, self.initX, self.initU)

    def test_systemInitialization(self):
        self.cps.A.all() |should| equal_to(self.A.all())
        self.cps.B.all() |should| equal_to(self.B.all())
        self.cps.K.all() |should| equal_to(self.K.all())
        self.cps.x.all() |should| equal_to(numpy.mat([[0.],[0.]]).all())
        self.cps.u.all() |should| equal_to(numpy.mat([0.]).all())
        self.cps.x = self.initX
        self.cps.x.all() |should| equal_to(numpy.mat([[1.0],
                                                      [1.0]]).all())
        self.cps2.x.all() |should| equal_to(numpy.mat([[1.0],
                                                      [1.0]]).all())
        self.cps2.u.all() |should| equal_to((-self.K * self.cps2.x).all())


    def test_updateStatesForOneTimeStep(self):
        self.cps2.updateStates(self.Ts)
        newStates = numpy.mat([[1.0],[0.98]])
        tol = 0.00001
        self.cps2.x[:, -1].all() |should| be_greater_than_or_equal_to((newStates - tol).all())
        self.cps2.x[:, -1].all() |should| be_less_than_or_equal_to((newStates + tol).all())

    """    
    def test_updateControlActuator(self):
        self.cps2.updateControlActuator(self.Ts)
        newU = numpy.mat([[-2.0125]])
        tol = 0.00001
        self.cps2.u[:, -1].all() |should| be_greater_than_or_equal_to((newU - tol).all())
        self.cps2.u[:, -1].all() |should| be_less_than_or_equal_to((newU + tol).all())
    """

    def test_updateStatesForSeveralTimeSteps(self):
        time = 15.0
        self.cps2.evolveSystem(time, self.Ts)
        t,x0,x1 = numpy.loadtxt('x.dat', unpack=True)
        
        x0 = numpy.mat(x0)
        x1 = numpy.mat(x1)
        
        # vectorized version of testing
        numOfCorrect1 = sum((abs(x0 - self.cps2.x[0, :]) < self.tol).T)[0,0]
        numOfCorrect2 = sum((abs(x1 - self.cps2.x[1, :]) < self.tol).T)[0,0]
        numOfCorrect1 |should| equal_to(t.shape[0])
        numOfCorrect2 |should| equal_to(t.shape[0])
                
        figure(1, figsize=(6, 4.5))
        xlabel('t')
        grid(True)
        hold(True)
        lw = 4
        lw2 = 1
        plot(t, x0.T, 'r', linewidth=lw)
        plot(t, x1.T, 'g', linewidth=lw)
        plot(t, self.cps2.x[0, :].T, 'y', linewidth=lw2)
        plot(t, self.cps2.x[1, :].T, 'k', linewidth=lw2)        
        legend((r'$x_0$', r'$x_1$', r'$selfX_0$', r'$selfX_1$'), prop=FontProperties(size=16))
        title('Simple Test CPS')
        savefig('testCPS.png', dpi=100)
        #show()

        
class TestABS(unittest.TestCase):
    
    def setUp(self):
        self.initX = numpy.mat([[33.0],
                                [33.0],
                                [0.0]])
        self.initU = numpy.mat([[250.]])
        self.Ts = 0.01
        self.tol = 0.0001
        self.carABSTest = CarABSTest(self.initX, self.initU)

    def test_updateStatesForOneTimeStep(self):
        self.carABSTest.updateStates(self.Ts)
        newStates = numpy.mat([[33],
                               [30.5],
                               [0.3300]])
        self.carABSTest.x[:, -1].all() |should| be_greater_than_or_equal_to((newStates - self.tol).all())
        self.carABSTest.x[:, -1].all() |should| be_less_than_or_equal_to((newStates + self.tol).all())


    def test_updateStatesForSeveralTimeSteps(self):
        time = 10.0
        self.carABSTest.evolveSystem(time, self.Ts)
        t,v,w,pos = numpy.loadtxt('abs.dat', unpack=True)
        t,s = numpy.loadtxt('abs_slip.dat', unpack=True)
        
        v = numpy.mat(v)
        w = numpy.mat(w)
        pos = numpy.mat(pos)
        s = numpy.mat(s)
        
        self.carABSTest.s = numpy.append(self.carABSTest.s, numpy.mat([[s[-1, -1]]]), 1)
        
        # vectorized version of testing
        numOfCorrect1 = sum((abs(v - self.carABSTest.x[0, :]) < self.tol).T)[0,0]
        numOfCorrect2 = sum((abs(w - self.carABSTest.x[1, :]) < self.tol).T)[0,0]
        numOfCorrect3 = sum((abs(pos - self.carABSTest.x[2, :]) < self.tol).T)[0,0]
        numOfCorrect4 = sum((abs(s- self.carABSTest.s[0, :]) < self.tol).T)[0,0]
    
        numOfCorrect1 |should| equal_to(t.shape[0])
        numOfCorrect2 |should| equal_to(t.shape[0])
        numOfCorrect3 |should| equal_to(t.shape[0])
        numOfCorrect4 |should| equal_to(t.shape[0])
        

        figure(8, figsize=(6, 4.5))
        xlabel('time (s)')
        grid(True)
        hold(True)
        lw = 2
        lw2 = 1
        plot(t, v.T, 'r', linewidth=lw)
        plot(t, w.T, 'g', linewidth=lw)
        plot(t, self.carABSTest.x[0, :].T, 'y', linewidth=lw2)
        plot(t, self.carABSTest.x[1, :].T, 'k', linewidth=lw2)        
        legend((r'$v$', r'$w$', r'$self_v$', r'$self_w$'), prop=FontProperties(size=16))
        title('Test ABS')
        savefig('testABSStates.png', dpi=100)
        #show()

        figure(2, figsize=(6, 4.5))
        xlabel('time (s)')
        grid(True)
        hold(True)
        lw = 2
        lw2 = 1
        plot(t, pos.T, 'r', linewidth=lw)
        plot(t, self.carABSTest.x[2, :].T, 'y', linewidth=lw2)

        legend((r'$pos$', r'$self_pos$'), prop=FontProperties(size=16))
        title('Test ABS')
        savefig('testABSPosition.png', dpi=100)
        #show()

        figure(3, figsize=(6, 4.5))
        xlabel('time (s)')
        grid(True)
        hold(True)
        lw = 2
        lw2 = 1
        plot(t, s.T, 'r', linewidth=lw)
        plot(t, self.carABSTest.s[0, :].T, 'k', linewidth=lw2)

        legend((r'$slip$', r'$self_s$'), prop=FontProperties(size=16))
        title('Test ABS')
        savefig('testABSSlip.png', dpi=100)
        #show()


    def test_mu(self):
        slip,coe = numpy.loadtxt('abs_mu.dat', unpack=True)
        coe = numpy.mat(coe).T
        #slip = numpy.mat(numpy.arange(0., 1., 0.01)).T
        coefficient = numpy.mat(numpy.zeros((slip.shape[0], 1)))
        for i in range(slip.shape[0]):
            coefficient[i] = self.carABSTest.mu(slip[i])
            
        numOfCorrect1 = sum((abs(coe - coefficient) < self.tol))[0,0]
        numOfCorrect1 |should| equal_to(slip.shape[0])
        


        figure(10, figsize=(6, 4.5))
        xlabel('slip')
        grid(True)
        hold(True)
        lw = 2
        lw2 = 1
        plot(slip, coe, 'r', linewidth=lw)
        plot(slip, coefficient, 'k', linewidth=lw2)
 
        legend((r'$coe$', r'$self_{coe}$'), prop=FontProperties(size=16))
        title('Test ABS')
        savefig('testABSMu.png', dpi=100)
        #show()

    def test_control(self):
        time = 10.0
        self.carABSTest.evolveSystem(time, self.Ts)
        t,control = numpy.loadtxt('abs_u.dat', unpack=True)
           
        control = numpy.mat(control)
        
        numOfCorrect1 = sum((abs(control - self.carABSTest.u[0, :]) < self.tol).T)[0,0]
        numOfCorrect1 |should| equal_to(t.shape[0])

        figure(11, figsize=(6, 4.5))
        xlabel('time')
        grid(True)
        hold(True)
        lw = 2
        lw2 = 1
        plot(t[0:200], control.T[0:200], 'r', linewidth=lw)
        plot(t[0:200], self.carABSTest.u[0,:].T[0:200], 'b', linewidth=lw2)
 
        legend((r'$control$', r'$self_u$'), prop=FontProperties(size=16))
        title('Test ABS')
        savefig('testABSControl.png', dpi=100)
        #show()

        
class test_inverted_pendulum(unittest.TestCase):
    
    def setUp(self):
        self.A = numpy.mat([[0., 1.0, 0., 0.],
                            [0., -0.18182, 2.6727, 0.],
                            [0., 0., 0., 1.],
                            [0., -0.45455, 31.1820, 0.]])

        self.B = numpy.mat([[0.0],
                            [1.8182],
                            [0.],
                            [4.5455]])

        self.K = numpy.mat([-61.9930, -33.5054, 95.0600, 18.8300])
        self.Ts = 0.01
        self.tol = 0.0001

        self.initX = numpy.mat([[0.0],
                                [0.0],
                                [0.04],
                                [-0.1]])
        self.initU = -self.K * self.initX
        self.invertedPendulum = InvertedPendulumTest(self.A, self.B, self.K, self.initX, self.initU)


    def test_updateStatesForSeveralTimeSteps(self):
        time = 10.0
        self.invertedPendulum.evolveSystem(time, self.Ts)
        t,x0,x1,x2,x3 = numpy.loadtxt('inv.dat', unpack=True)
        
        x0 = numpy.mat(x0)
        x1 = numpy.mat(x1)
        
        # vectorized version of testing
        numOfCorrect1 = sum((abs(x2 - self.invertedPendulum.x[2, :]) < self.tol).T)[0,0]
        numOfCorrect2 = sum((abs(x3 - self.invertedPendulum.x[3, :]) < self.tol).T)[0,0]
       
        numOfCorrect1 |should| equal_to(t.shape[0])
        numOfCorrect2 |should| equal_to(t.shape[0])
                
        figure(12, figsize=(6, 4.5))
        xlabel('t')
        grid(True)
        hold(True)
        lw = 4
        lw2 = 1
        plot(t, x2.T, 'r', linewidth=lw)
        plot(t, x3.T, 'g', linewidth=lw)
        plot(t, self.invertedPendulum.x[2, :].T, 'y', linewidth=lw2)
        plot(t, self.invertedPendulum.x[3, :].T, 'k', linewidth=lw2)        
        legend((r'$angle (rad)$', r'$angle rate (rad/s)$', r'$self{angle} (rad)$', r'$self{angleRate} (rad/s)$'), prop=FontProperties(size=16))
        title('Simple Test Inverted Pendulum')
        savefig('inv.png', dpi=100)
        #show()


class TestPeriodDelay(unittest.TestCase):

    def setUp(self):
        self.A = numpy.mat([[0., 1.0, 0., 0.],
                            [0., -0.18182, 2.6727, 0.],
                            [0., 0., 0., 1.],
                            [0., -0.45455, 31.1820, 0.]])

        self.B = numpy.mat([[0.0],
                            [1.8182],
                            [0.],
                            [4.5455]])

        self.K = numpy.mat([-61.9930, -33.5054, 95.0600, 18.8300])
        self.Ts = 0.01
        self.tol = 0.0001

        self.initX = numpy.mat([[0.0],
                                [0.0],
                                [0.04],
                                [-0.1]])
        self.initU = -self.K * self.initX
        self.invertedPendulum = InvertedPendulumTest(self.A, self.B, self.K, self.initX, self.initU)
    

if __name__ == '__main__':
    unittest.main()
