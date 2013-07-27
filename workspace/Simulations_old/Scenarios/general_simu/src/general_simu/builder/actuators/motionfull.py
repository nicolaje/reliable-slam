from morse.builder.creator import ActuatorCreator

class Motionfull(ActuatorCreator):
    def __init__(self, name=None):
        ActuatorCreator.__init__(self, name, \
                                 "general_simu.actuators.motionfull.Motionfull",\
                                 "motionfull")

