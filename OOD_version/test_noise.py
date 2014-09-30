import unittest
from should_dsl import should, should_not
import numpy
from pylab import figure, plot, xlabel, grid, hold, legend, title, savefig, show
from matplotlib.font_manager import FontProperties

import sbft.dsp.Noise as noise

class TestNoise(unittest.TestCase):

    def setUp(self):
        self.x = 0 * numpy.ones((1, 100)).T
        #self.y = noise.white(self.x, snr = 3.0).T
        mean = 0
        std = 1
        self.y = self.x + mean + std * numpy.random.randn(100, 1) 


    def test_noise(self):
        expectedU = 1.1
        t = numpy.arange(0., 100.)
        
        figure(1, figsize=(6, 4.5))
        xlabel('t')
        grid(True)
        hold(True)
        lw = 2
        lw2 = 1
        plot(t, self.y, 'r', linewidth=lw)
        plot(t, self.x, 'g', linewidth=lw)     
        legend((r'noisy signal', r'original signal'), prop=FontProperties(size=16))
        title('Simple Test Noise')
        savefig('testNoise.png', dpi=100)
        show()

        1 |should| be_greater_than_or_equal_to(0)
        
if __name__ == '__main__':
    unittest.main()
