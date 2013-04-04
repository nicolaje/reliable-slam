import time
import pymorse
from datetime import datetime
from math import *

######################
# Tunable parameters #
######################
duration=10          # 10s
######################

# func(t) defines the trajectory
# as a function of time
def func(t):
	v=1
	w=2*pi*duration/t
	return [v, w]
	
with pymorse.Morse() as simu:
	print(simu.robots)
	print(simu.list_robots())
	#motion=simu.sub.motion
	time=datetime.now()
	delta=0
	simu.quit()
	# Control the trajectory for 
	#while delta < duration:
	#	print('T: '+t)
	#	[v, w]=func(delta)
	#	motion.set_speed(v,w)
	#	now=datetime.now()
	#	delta=delta+now.seconds+now.microseconds/1000000
