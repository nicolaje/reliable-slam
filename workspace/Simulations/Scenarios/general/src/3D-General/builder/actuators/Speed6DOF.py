from morse.builder.creator import ActuatorCreator

class Speed6dof(ActuatorCreator):
    def __init__(self, name=None):
        ActuatorCreator.__init__(self, name, \
                                 "3D-General.actuators.Speed6DOF.Speed6dof",\
                                 "Speed6DOF")

