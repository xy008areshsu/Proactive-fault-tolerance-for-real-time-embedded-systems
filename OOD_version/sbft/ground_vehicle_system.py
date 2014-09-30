import numpy
import math

from sbft.cyber_physical_system import NonLinearCPS

class CarABSTest(NonLinearCPS):

    
    """ State Variables in the form of:
    [[Vehicle Speed],
    [Wheel Speed], 
    [Vehicle Position]] 
    """
    def __init__(self, initX, initU):
        super().__init__(initX, initU)
        self.s = []
        self.s = numpy.mat(self.s)


        
    def updateStates(self, Ts):
        
        #Car Parameters 
        mass_quarter_car = 250. # kg, 1/4 of the car weight
        mass_effective_wheel = 20. # kg
        g = 9.81 # m / s2
        road = 1.0   # road condition, friction coefficient

        #Update states
        v = self.x[0, -1]
        w = self.x[1, -1]
        pos = self.x[2, -1]
        s = max(0., 1. - w / v)       # slip ratio 
        self.s = numpy.append(self.s, numpy.mat([[s]]), 1)
        if self.x[0, -1] < 10.:   # vehicle speed lower than 10 m/s ABS not triggered
            newX = self.x[:, -1]
        else:
            force = road * self.mu(s) * mass_quarter_car * g    # friciton force
            v = v - Ts * force / mass_quarter_car
            pos = pos + Ts * v
            w = w + Ts * (force / mass_effective_wheel - self.u[:, -1])
            w = max(0., w)
            
            newX = numpy.mat([[v],
                              [w],
                              [pos]])
            
        self.x = numpy.append(self.x, newX, 1)

    

    """ Tire Model, friction coefficient generation

    Can use more accurate model here, such as Dugoff Model
    """
    def mu(self, slip):
        return (-1.1 * math.exp(-20 * slip) + 1.1 - 0.4 * slip)


 

    """ Simple ABS function

    """
    def updateControlActuator(self, Ts):
        
        # Brake parameters
        hydraulic_speed = 3300.  # in m/s3
        
        # Update brake actuators    
        #v = self.x[0, -1]  #need to determine which state to USE!!!!
        #w = self.x[1, -1]
        v = self.x[0, -2]
        w = self.x[1, -2]
        s = max(0., 1. - w / v)
        if s > 0.2:
            brake_change = -1
        else:
            brake_change = 1
            
        #      newU = max(LB, min(UB, self.u[:,-1] + Ts * brake_change * hydraulic_speed))        
        #Alternative method
        newU = max(100., min(150., self.u[0,-1] + Ts * brake_change * hydraulic_speed))
        newU = numpy.mat([[newU]])
        self.u = numpy.append(self.u, newU, 1)

