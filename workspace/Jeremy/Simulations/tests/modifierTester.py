from morse.builder import *

atrv = ATRV()

pose = Pose()
atrv.append(pose)
pose.alter('', 'MyModifier')

env = Environment('empty', fastmode=True)
