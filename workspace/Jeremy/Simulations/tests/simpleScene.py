from morse.builder import *

r=ATRV()

pose=Pose()
pose.add_interface('socket')
r.append(pose)

motion=Waypoint()
motion.add_interface('socket')
r.append(motion)

env=Environment('land-1/trees')
