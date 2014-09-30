import unittest
from should_dsl import should, should_not
import numpy
from pylab import figure, plot, xlabel, grid, hold, legend, title, savefig, show
from matplotlib.font_manager import FontProperties

from sbft.real_time_computer import RealTimeComputer
from sbft.real_time_task import RealTimeTask

class TestRealTimeComputer(unittest.TestCase):

    def setUp(self):
        taskA = RealTimeTask(0.05, 0.01)
        taskB = RealTimeTask(0.075, 0.03)
        taskC = RealTimeTask(0.1, 0.05)

        taskList = [taskA, taskB, taskC]

        self.realTimeComputer = RealTimeComputer(taskList)

    def test_cpuUtilization(self):
        expectedU = 1.1
        self.realTimeComputer.getUtilization() |should| equal_to(expectedU)

if __name__ == '__main__':
    unittest.main()
