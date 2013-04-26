import time
import pymorse
import sys
from datetime import datetime
from time import sleep
from math import *

# func(t) defines the trajectory
# as a function of time
#def func(t):
#	v=0.5
#	w=2*pi*t
#	return [v, cos(w*1./4.)]
	
with pymorse.Morse() as simu:
	print("Entering trajectory controller")
	motion=simu.sub.motion
	motion.publish({'v':0, 'w':pi/2/10})
	sleep(10)
	motion.publish({'v':0.5, 'w':0})
