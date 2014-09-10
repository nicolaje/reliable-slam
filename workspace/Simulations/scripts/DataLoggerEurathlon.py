#! /usr/bin/env python3

import time
import sys
import pymorse
import curses
import os
from datetime import datetime
from time import sleep
from pymorse import Morse
from math import atan2

readyToWrite=False
firstRun=True

_pose_pure=0
_pose_noisy=0

_pose_usv_pure=0
_pose_usv_noisy=0

_imu_pure=0
_imu_noisy=0

_pinger_pure=0
_pinger_noisy=0

_loch_doppler_pure=0
_loch_doppler_noisy=0

_gps_pure = 0
_gps_noisy = 0

_gps_motorboat_pure = 0
_gps_motorboat_noisy = 0

_motorboat_angle_pure = 0
_motorboat_angle_noisy = 0

def update_motorboat_angle_pure():
    global _motorboat_angle_pure, _pose_usv_pure, _pose_pure
    if _pose_usv_pure == 0 or _pose_pure == 0:
        return
    _motorboat_angle_pure = {
        "yaw": atan2(_pose_usv_pure["y"] - _pose_pure["y"], _pose_usv_pure["x"] - _pose_pure["x"]),
        "pitch": atan2(_pose_usv_pure["z"] - _pose_pure["z"], _pose_usv_pure["y"] - _pose_pure["y"]),
        "roll": atan2(_pose_usv_pure["z"] - _pose_pure["z"], _pose_usv_pure["x"] - _pose_pure["x"])
    }
    
def update_motorboat_angle_noisy():
    global _motorboat_angle_noisy, _pose_noisy, _pose_usv_noisy
    
    if _pose_usv_noisy == 0 or _pose_noisy == 0:
        return
    
    _motorboat_angle_noisy = {
        "yaw": atan2(_pose_usv_noisy["y"] - _pose_noisy["y"], _pose_usv_noisy["x"] - _pose_noisy["x"]),
        "pitch": atan2(_pose_usv_noisy["z"] - _pose_noisy["z"], _pose_usv_noisy["y"] - _pose_noisy["y"]),
        "roll": atan2(_pose_usv_noisy["z"] - _pose_noisy["z"], _pose_usv_noisy["x"] - _pose_noisy["x"])
    }
    
    print(_motorboat_angle_noisy)
    
    global readyToWrite
    readyToWrite=True

def update_pose_pure(data):
    global _pose_pure
    _pose_pure=data
    update_motorboat_angle_pure()

def update_pose_noisy(data):
    global _pose_noisy
    _pose_noisy=data
    update_motorboat_angle_noisy()

def update_imu_pure(data):
    global _imu_pure
    _imu_pure=data

def update_imu_noisy(data):
    global _imu_noisy
    _imu_noisy=data

def update_pinger_pure(data):
    global _pinger_pure
    _pinger_pure=data
    
def update_pinger_noisy(data):
    global _pinger_noisy
    _pinger_noisy=data

def update_loch_doppler_pure(data):
    global _loch_doppler_pure
    _loch_doppler_pure=data
    
def update_loch_doppler_noisy(data):
    global _loch_doppler_noisy
    _loch_doppler_noisy=data

def update_gps_pure(data):
    global _gps_pure
    _gps_pure=data

def update_gps_noisy(data):
    global _gps_noisy
    _gps_noisy=data

def update_usv_pose_pure(data):
    global _pose_usv_pure
    _pose_usv_pure=data
    update_motorboat_angle_pure()

def update_usv_pose_noisy(data):
    global _pose_usv_noisy
    _pose_usv_noisy=data
    
def update_usv_gps_pure(data):
    global _gps_motorboat_pure
    _gps_motorboat_pure=data

def update_usv_gps_noisy(data):
    global _gps_motorboat_noisy
    _gps_motorboat_noisy=data
    update_motorboat_angle_noisy()

# The Curses callbak
def run(win):
    win.timeout(100)
    
    doRun=True
    f=0
    if len(sys.argv) >=2: # Did we receive a file name as an argument?
        f=open(os.environ['WORKSPACE_DIR']+"/Simulations/data/"+sys.argv[1],'w')
        win.addstr(1,0,os.environ['WORKSPACE_DIR']+"/Simulations/data/"+sys.argv[1])
    else:
        f=open(str(os.environ['WORKSPACE_DIR']+"/Simulations/data/"+os.environ['OUTPUT_LOG']),'w')
        win.addstr(1,0,str(os.environ['WORKSPACE_DIR']+"/Simulations/data/"+os.environ['OUTPUT_LOG']))
    
    global readyToWrite
    global firstRun
    
    simu=Morse()
    sub=simu.sub
    sub.pose_pure.subscribe(update_pose_pure)
    sub.pose_noisy.subscribe(update_pose_noisy)
    sub.imu_pure.subscribe(update_imu_pure)
    sub.imu_noisy.subscribe(update_imu_noisy)
    sub.pinger_pure.subscribe(update_pinger_pure)
    sub.pinger_noisy.subscribe(update_pinger_noisy)
    sub.loch_doppler_pure.subscribe(update_loch_doppler_pure)
    sub.loch_doppler_noisy.subscribe(update_loch_doppler_noisy)
    sub.gps_submarine_pure.subscribe(update_gps_pure)
    sub.gps_submarine_noisy.subscribe(update_gps_noisy)
    
    motorboat=simu.motorboat
    motorboat.gps_pure.subscribe(update_usv_gps_pure)
    motorboat.gps_noisy.subscribe(update_usv_gps_noisy)
    motorboat.pose_pure.subscribe(update_usv_pose_pure)
    motorboat.pose_noisy.subscribe(update_usv_pose_noisy)
    #NEED TO SEE WHAT WE NEED!
    while not readyToWrite:
        sleep(0.1)
    sleep(1)
    start=datetime.now()
    data=""
    lines=0
    while doRun:
        win.addstr(0,0,"Data logger. Writing the log to: ")
        win.addstr(2,0,"Press q to quit.")
        time=datetime.now()
        win.addstr(4,0,"Wrote "+str(lines)+ " lines in "+str((time-start).seconds)+" seconds.")
        win.addstr(5,0,"Shift is: "+str((time-start).seconds-lines/10.0))
        c = win.getch()
        if c == 113: # if the "q" key is pressed, exit data logging
            doRun=False
            win.addstr(6,0,"Closing the file...")
            f.write(data)
            f.close()
            sleep(1)
            win.addstr(6,20,"File Closed.")
            sleep(1)
        elif readyToWrite:
            lines+=1
            linear_acceleration_pure=_imu_pure['linear_acceleration']
            linear_acceleration_noisy=_imu_noisy['linear_acceleration']
            
            angular_velocity_pure=_imu_pure['angular_velocity']
            angular_velocity_noisy=_imu_noisy['angular_velocity']
            
            loch_doppler_pure=_loch_doppler_pure['linear_velocity']
            loch_doppler_noisy=_loch_doppler_noisy['linear_velocity']
            
            transponders_pure=sorted(_pinger_pure['near_objects'].items())
            transponders_noisy=sorted(_pinger_noisy['near_objects'].items())

            if firstRun:
                firstRun=False
                dados = [
                    "time",
                    "pose_pure.x","pose_pure.y","pose_pure.z",
                    "pose_pure.yaw","pose_pure.pitch","pose_pure.roll",
                    "gps_pure.x","gps_pure.y","gps_pure.z",
                    "imu_pure.dtheta","imu_pure.dphi","imu_pure.dpsi",
                    "loch_doppler_pure.vx","loch_doppler_pure.vy","loch_doppler_pure.vz",
                    "imu_pure.ddx","imu_pure.ddy","imu_pure.ddz"
                ]
                
                for s in transponders_pure:
                    dados += [
                        s[0]+"_gps_pure.x",
                        s[0]+"_gps_pure.y",
                        s[0]+"_gps_pure.z",
                        s[0]+"_yaw_pure",
                        s[0]+"_pitch_pure",
                        s[0]+"_roll_pure",
                        s[0]+"_dist"]
                
                dados += [
                    "pose_noisy.x","pose_noisy.y","pose_noisy.z",
                    "pose_noisy.yaw","pose_noisy.pitch","pose_noisy.roll",
                    "gps_noisy.x","gps_noisy.y","gps_noisy.z",
                    "imu_noisy.dtheta","imu_noisy.dphi","imu_noisy.dpsi",
                    "loch_doppler_noisy.vx","loch_doppler_noisy.vy","loch_doppler_noisy.vz",
                    "imu_noisy.ddx","imu_noisy.ddy","imu_noisy.ddz",
                ]
                
                for s in transponders_noisy:
                    dados += [
                        s[0]+"_gps_noisy.x",
                        s[0]+"_gps_noisy.y",
                        s[0]+"_gps_noisy.z",
                        s[0]+"_yaw_noisy",
                        s[0]+"_pitch_noisy",
                        s[0]+"_roll_noisy",
                        s[0]+"_dist"]
                
                data += ";".join(dados)+"\n"
                
            # Reference data
            dados = [
                lines*0.1, #Time in seconds
                _pose_pure['x'],
                _pose_pure['y'],
                _pose_pure['z'],
                _pose_pure['roll'],
                _pose_pure['pitch'],
                _pose_pure['yaw'],
                _gps_pure['x'],
                _gps_pure['y'],
                _gps_pure['z'],
                angular_velocity_pure[0],
                angular_velocity_pure[1],
                angular_velocity_pure[2],
                loch_doppler_pure[0],
                loch_doppler_pure[1],
                loch_doppler_pure[2],
                linear_acceleration_pure[0],
                linear_acceleration_pure[1],
                linear_acceleration_pure[2],
                _gps_motorboat_pure['x'],
                _gps_motorboat_pure['y'],
                _gps_motorboat_pure['z'],
                _motorboat_angle_pure["yaw"],
                _motorboat_angle_pure["pitch"],
                _motorboat_angle_pure["roll"]
            ]
            
            for s in transponders_pure:
                dados.append(s[1])
            
            # Noisy data
            dados += [
                _pose_noisy['x'],
                _pose_noisy['y'],
                _pose_noisy['z'],
                _pose_noisy['roll'],
                _pose_noisy['pitch'],
                _pose_noisy['yaw'],
                _gps_noisy['x'],
                _gps_noisy['y'],
                _gps_noisy['z'],
                angular_velocity_noisy[0],
                angular_velocity_noisy[1],
                angular_velocity_noisy[2],
                loch_doppler_noisy[0],
                loch_doppler_noisy[1],
                loch_doppler_noisy[2],
                linear_acceleration_noisy[0],
                linear_acceleration_noisy[1],
                linear_acceleration_noisy[2],
                _gps_motorboat_noisy['x'],
                _gps_motorboat_noisy['y'],
                _gps_motorboat_noisy['z'],
                _motorboat_angle_noisy["yaw"],
                _motorboat_angle_noisy["pitch"],
                _motorboat_angle_noisy["roll"]
            ]
            for s in transponders_noisy:
                dados.append(s[1])
            data += ";".join([str(d) for d in dados])+"\n"
            
curses.wrapper(run)

