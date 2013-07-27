#!/usr/bin/env python3
import sys
import time
import curses

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
simu=Morse()
motion=simu.robot.motion

def run(win):
    win.addstr(0, 0, "Arrow Keys to move the robot horizontally,")
    win.addstr(1, 0, "Page Up/Down Keys to move the robot vertically")
    while True:
        global motion
        global vx
        global vy
        global vz
        global wx
        global wy
        global wz
        c = win.getch()
        if c == curses.KEY_UP:
            vx+=0.1
        elif c == curses.KEY_DOWN:
            vx-=0.1
        elif c == curses.KEY_LEFT:
            wz+=0.05
        elif c == curses.KEY_RIGHT:
            wz-=0.05
        elif c == curses.KEY_NPAGE:
            vz+=0.1
        elif c == curses.KEY_PPAGE:
            vz-=0.1
        motion.publish({"v": vx,"w": wz}) # {"vx": vx,"vy": vy,"vz": vz,"wx": wx,"wy": wy,"wz": wz})
        
curses.wrapper(run)
