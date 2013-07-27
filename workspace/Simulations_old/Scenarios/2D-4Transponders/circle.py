import time
import pymorse
import sys
from datetime import datetime
from time import sleep
from math import *

######################
# Tunable parameters #
######################
duration=30          # 30s
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
	v=5.*pi*radius/120.
	w=5.*pi/120.
	print("w: "+str(w))
	print("v: "+str(v))
#	print(simu.robots)
	motion=simu.sub.motion
	motion.publish({'v':v,'w':w}) #{'v':2*pi*radius/120, 'w':2*pi/120}) # 1 round per 2 minutes
#	sleep(10)
#	v=0
#	w=pi/20
#	motion.publish({'v':v,'w':w})
#	print("Turning")
#	sleep(10)
#	v=10
#	w=0
#	motion.publish({'v':v,'w':w})
#	print("Back")
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
