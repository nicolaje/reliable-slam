import time
import pymorse
import sys
from datetime import datetime
from time import sleep
from math import *

######################
# Tunable parameters #
######################
duration=30          # 10s
radius=30            # radius of the circle the robot moves on
######################

# func(t) defines the trajectory
# as a function of time
#def func(t):
#	v=0.5
#	w=2*pi*t
#	return [v, cos(w*1./4.)]
	
with pymorse.Morse() as simu:
	print("Entering trajectory controller")
#	print(simu.robots)
	motion=simu.sub.motion
	motion.publish({'v':2*pi*radius/120, 'w':2*pi/120}) # 1 round per 2 minutes
#	sleep(60)
#	simu.quit()
#	time=datetime.now()
#	delta=0	
	# Control the trajectory
#	while delta < duration:
#		print('T: %i'%delta)
#		[v, w]=func(delta)
#		motion.publish({'v':v ,'w':w})
#		now=datetime.now()
#		delta=(now-time).seconds+(now-time).microseconds/1000000
#		print(delta)
#		sleep(0.5)
