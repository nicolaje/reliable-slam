#! /usr/bin/env python3

import sys
import time
import curses
from datetime import datetime
import os

try:
    from pymorse import Morse
except ImportError:
    print("you need first to install pymorse, the Python bindings for MORSE!")
    sys.exit(1)

vx = 0.0
vy = 0.0
vz = 0.0
wx = 0.0
wy = 0.0
wz = 0.0

position=0
linear_speed=0
angular_speed=0

start=datetime.now()
max_duration=int(os.environ['SIMU_DURATION'])

duration=0

def pose_received(p):
    global position
    position=p
    
def speed_received(s):
    global linear_speed
    global angular_speed
    linear_speed=s["linear_velocity"]
    angular_speed=s["angular_velocity"]
    
simu=Morse()
sub=simu.sub
motion=sub.motion
pose=sub.pose_pure
velocity=sub.loch_doppler_pure

pose.subscribe(pose_received)
velocity.subscribe(speed_received)

def run(win):
    win.timeout(100)
    while duration < max_duration : #True:
        global duration
        now=datetime.now()
        duration=(now-start).seconds+(now-start).microseconds/1000000
        global motion
        global vx
        global vy
        global vz
        global wx
        global wy
        global wz
        win.addstr(0, 0, "Arrow Keys to move the robot horizontally,")
        win.addstr(1, 0, "Page Up/Down Keys to move the robot vertically")
        if position != 0 and linear_speed !=0 and angular_speed != 0 :
            win.addstr(2, 0, "Position: ")
            win.addstr(2, 15, '['+"{0:.2f}".format(position['x'])+", "+\
            "{0:.2f}".format(position['y'])+\
            ", "+"{0:.2f}".format(position['z'])+']')
            win.addstr(3, 0, "Orientation: ")
            win.addstr(3, 15, '['+"{0:.2f}".format(position['roll'])+", "+\
            "{0:.2f}".format(position['pitch'])+", "+\
            "{0:.2f}".format(position['yaw'])+']')
            win.addstr(4, 0, "Linear Speed: ")
            win.addstr(4, 15, '['+"{0:.2f}".format(linear_speed[0])+", "+\
            "{0:.2f}".format(linear_speed[1])+", "+\
            "{0:.2f}".format(linear_speed[2])+']')
            win.addstr(5, 0, "Angular Speed: ")
            win.addstr(5, 15, '['+"{0:.2f}".format(angular_speed[0])+", "+\
            "{0:.2f}".format(angular_speed[1])+", "+\
            "{0:.2f}".format(angular_speed[2])+']')
        if wz >-0.1 and wz < 0.1 :
            wz=0
        
        if position !=0 and position['z'] >= 0 and vz >=0 :
            vz=0
            
        c = win.getch()
        if c == curses.KEY_UP and vx <= 4 :
            vx+=0.1
        elif c == curses.KEY_DOWN and vx >= -1 :
            vx-=0.1
        elif c == curses.KEY_LEFT and wz <= 0.35:
            if wz >=0 and wz < 0.1: # The IMU does not correctly measure the angular speed otherwise
                wz=0.1
            else:
                wz+=0.05
        elif c == curses.KEY_RIGHT and wz >= -0.35:
            if wz <=0 and wz > -0.1 :
                wz=-0.1
            else:
                wz-=0.05
        elif c == curses.KEY_PPAGE and vz <= 1 and position['z'] <= 0:
            vz+=0.1
        elif c == curses.KEY_NPAGE and vz >= -1:
            vz-=0.1
        motion.publish({"vx": vx,"vy": vy,"vz": vz,"wx": wx,"wy": wy,"wz": wz})
        
curses.wrapper(run)
