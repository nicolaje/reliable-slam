import time
import pymorse
import logging
logging.basicConfig()

def print_pos(pose):
    print("I'm currently at %s" % pose)

with pymorse.Morse() as simu:
    
    # subscribes to updates from the Pose sensor by passing a callback
    simu.r2d2.pose.subscribe(print_pos)

    # sends a destination
    simu.r2d2.motion.publish({'x' : 10.0, 'y': 5.0, 'z': 0.0, 
                              'tolerance' : 0.5, 
                              'speed' : 1.0})

    # Leave a couple of millisec to the simulator to start the action
    time.sleep(0.1)

    # waits until we reach the target
    while simu.r2d2.motion.get_status() != "Arrived":
        time.sleep(0.5)

    print("Here we are!")
