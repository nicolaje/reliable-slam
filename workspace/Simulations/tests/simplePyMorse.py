import pymorse
import time

def print_pos(pose):
	print("I'm here : %s" % pose)

with pymorse.Morse() as simu:
	simu.r.pose.subscribe(print_pos)
	simu.r.motion.publish({'x':10.0,'y':5.0,'z':0.0,'tolerance':0.5,'speed':1.0})
	time.sleep(0.1)

	while simu.r.motion.get_status() != "Arrived":
		time.sleep(0.5)

	print("Arrived !")
