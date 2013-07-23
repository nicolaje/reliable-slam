import time
import pymorse
import sys
from datetime import datetime
from time import sleep
from math import *

######################
# Tunable parameters #
######################


# func(t) defines the trajectory
# as a function of time
#def func(t):
#	v=0.5
#	w=2*pi*t
#	return [v, cos(w*1./4.)]
	
with pymorse.Morse() as simu:
	print("Entering trajectory controller")
	v=2
	w=0
	print("w: "+str(w))
	print("v: "+str(v))
#	print(simu.robots)
	motion=simu.sub.motion
	motion.publish({'v':v,'w':w}) #{'v':2*pi*radius/120, 'w':2*pi/120}) # 1 round per 2 minutes
	sleep(10)
	print("Changing speed");
	motion.publish({'v':1.5,'w':0.1})
	sleep(10)
	print("Changing speed again");
	motion.publish({'v':2,'w':-0.5})
	sleep(10)
	print("Changing speed again");
	motion.publish({'v':1.8,'w':0.3})
	sleep(10)
	print("Changing speed again");
	motion.publish({'v':2.5,'w':0.4})
	sleep(10)
	print("Changing speed again");
	motion.publish({'v':4,'w':0.3})
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
