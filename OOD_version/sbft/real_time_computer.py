class RealTimeComputer:

    def __init__(self, taskList):
        self.taskList = taskList

    def getUtilization(self):
        u = 0.
        for i in range(len(self.taskList)):
            u += self.taskList[i].e / self.taskList[i].p

        return u
