#!/usr/bin/env python3

import sys
import curses
import os
from math import sin, cos, atan2, sqrt, pi

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

position={"yaw":0, "roll": 0, "pitch":0,"x":0, "y":0, "z":0}
positionMotorboat={"yaw":0, "roll": 0, "pitch":0,"x":0, "y":0, "z":0}
linear_speed=0
angular_speed=0
side = -5.

def pose_motorboat_received(p):
    global positionMotorboat
    positionMotorboat=p

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
motionSUB=sub.motion
motorboat=simu.motorboat
motionMB=motorboat.motion
pose=sub.pose_pure
velocity=sub.loch_doppler_pure

pose.subscribe(pose_received)
velocity.subscribe(speed_received)
simu.motorboat.pose_pure.subscribe(pose_motorboat_received)

def run(win):
    win.timeout(100)
    doRun=True
    while doRun:
        global duration
        global motionSUB
        global vx
        global vy
        global vz
        global wx
        global wy
        global wz
        global positionMotorboat, position, side
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
            win.addstr(7,0,"Press q to quit.")

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
        elif c == 113: # q is pressed, close the loop
            doRun = False
        motionSUB.publish({"vx": vx,"vy": vy,"vz": vz,"wx": wx,"wy": wy,"wz": wz})

        x, y = sin(position["yaw"])*side + position["x"], cos(position["yaw"])*side + position["y"]

        dyaw = atan2(y-positionMotorboat['y'], x-positionMotorboat['x']) - positionMotorboat["yaw"]
        if dyaw > pi:
            dyaw -= 2*pi
        if dyaw < -pi:
            dyaw += 2*pi


        maxwz = max(abs(5.*wz),0.8)
        mwz = maxwz*dyaw/pi
        mwz = min(mwz,maxwz)
        mwz = max(mwz,-maxwz)

        d = sqrt(pow(x-positionMotorboat['x'],2) + pow(y-positionMotorboat['y'],2))

        maxvx = max(abs(5*vx),1.)
        mvx = 0.
        mvx = maxvx*d/5.
        mvx = min(mvx,maxvx)
        mvx = max(mvx,1.)
        mvx *= max(cos(dyaw),0.5)

        if d > 1.:
            motionMB.publish({"vx": mvx,"vy": 0,"vz": 0,"wx": 0,"wy": 0,"wz":  mwz})
        else:
            side = -side
            motionMB.publish({"vx": 0,"vy": 0,"vz": 0,"wx": 0,"wy": 0,"wz":  0})
        lines = []
        lines.append("dyaw:{0:.2f}".format(dyaw))
        lines.append("d:{0:.2f}".format(d))
        lines.append("side:{0:.2f}".format(side))
        lines.append("Pdyaw:{0:.2f}".format(atan2(y-positionMotorboat['y'], x-positionMotorboat['x'])))
        lines.append("yaw:{0:.2f}".format(positionMotorboat["yaw"]))
        lines.append("mvx:{0:.2f}".format(mvx))
        lines.append("mwz:{0:.2f}".format(mwz))
        lines.append("Motorboat:{0:.2f}, {1:.2f}, {2:.2f}".format(positionMotorboat["x"], positionMotorboat["y"], positionMotorboat["z"]))

        for i in range(len(lines)):
            win.addstr(9+i, 15, lines[i])

curses.wrapper(run)
