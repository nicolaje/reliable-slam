from morse.builder import *

robot = Submarine()

trans1=Robot('../Models/Transponder.blend')

proximity=Proximity()

proximity.add_interface('socket')
proximity.frequency(2)

robot.append(proximity)

motion=MotionVW()
motion.add_interface('socket')
robot.append(motion)

env=Environment('../Models/water_0.95_packed.blend')
