#! /usr/bin/env python3

import time
import sys
import pymorse
import curses
import os
from datetime import datetime
from time import sleep
from pymorse import Morse

readyToWrite=False
firstRun=True

_pose_pure=0
_pose_noisy=0

_imu_pure=0
_imu_noisy=0

_pinger_pure=0
_pinger_noisy=0

_loch_doppler_pure=0
_loch_doppler_noisy=0

def update_pose_pure(data):
	global _pose_pure
	_pose_pure=data
	
def update_pose_noisy(data):
	global _pose_noisy
	_pose_noisy=data

def update_imu_pure(data):
	global _imu_pure
	_imu_pure=data

def update_imu_noisy(data):
	global _imu_noisy
	_imu_noisy=data

def update_pinger_pure(data):
	global _pinger_pure
	global readyToWrite
	_pinger_pure=data
	readyToWrite=True
	
def update_pinger_noisy(data):
	global _pinger_noisy
	_pinger_noisy=data

def update_loch_doppler_pure(data):
	global _loch_doppler_pure
	_loch_doppler_pure=data
	
def update_loch_doppler_noisy(data):
	global _loch_doppler_noisy
	_loch_doppler_noisy=data
	
def concat_data():
	pass

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
				tp=""
				for s in transponders_pure:
					tp+=';'+s[0]
				data+=\
				'pose_pure.x;pose_pure.y;pose_pure.z;'\
				'pose_pure.yaw;pose_pure.pitch;pose_pure.roll;'\
				'imu_pure.dtheta;imu_pure.dphi;imu_pure.dpsi;'\
				'loch_doppler_pure.vx;loch_doppler_pure.vy;loch_doppler_pure.vz;'\
				'imu_pure.ddx;imu_pure.ddy;imu_pure.ddz'+\
				tp+';'\
				'pose_noisy.x;pose_noisy.y;pose_noisy.z;'\
				'pose_noisy.yaw;pose_noisy.pitch;pose_noisy.roll;'\
				'imu_noisy.dtheta;imu_noisy.dphi;imu_noisy.dpsi;'\
				'loch_doppler_noisy.vx;loch_doppler_noisy.vy;loch_doppler_noisy.vz;'\
				'imu_noisy.ddx;imu_noisy.ddy;imu_noisy.ddz'+\
				tp+"\n"
				
			# Reference data
			data+=str(_pose_pure['x'])+';'+str(_pose_pure['y'])+';'+str(_pose_pure['z'])+';'+\
			str(_pose_pure['roll'])+';'+str(_pose_pure['pitch'])+';'+str(_pose_pure['yaw'])+';'+\
			str(angular_velocity_pure[0])+";"+str(angular_velocity_pure[1])+";"+str(angular_velocity_pure[2])+";"+\
			str(loch_doppler_pure[0])+";"+str(loch_doppler_pure[1])+";"+str(loch_doppler_pure[2])+";"+\
			str(linear_acceleration_pure[0])+";"+str(linear_acceleration_pure[1])+";"+str(linear_acceleration_pure[2])
			
			for s in transponders_pure:
				data+=';'+str(s[1])
			
			# Noisy data
			data+=';'+str(_pose_noisy['x'])+';'+str(_pose_noisy['y'])+';'+str(_pose_noisy['z'])+';'+\
			str(_pose_noisy['roll'])+';'+str(_pose_noisy['pitch'])+';'+str(_pose_noisy['yaw'])+';'+\
			str(angular_velocity_noisy[0])+";"+str(angular_velocity_noisy[1])+";"+str(angular_velocity_noisy[2])+";"+\
			str(loch_doppler_noisy[0])+";"+str(loch_doppler_noisy[1])+";"+str(loch_doppler_noisy[2])+";"+\
			str(linear_acceleration_noisy[0])+";"+str(linear_acceleration_noisy[1])+";"+str(linear_acceleration_noisy[2])
			
			for s in transponders_noisy:
				data+=';'+str(s[1])
			data+='\n'
			
curses.wrapper(run)

#f=open(str(file_name), 'w')

# Data format:
#f.write('# pose_pure.x; pose_pure.y; pose_pure.z;'\
#'pose_pure.yaw; pose_pure.pitch; pose_pure.roll;'\
#'imu_pure.dtheta; imu_pure.dphi; imu_pure.dpsi;'\
#'loch_doppler_pure.vx; loch_doppler_pure.vy; loch_doppler_pure.vz;'\
#'imu_pure.ddx; imu_pure.ddy; imu_pure.ddz;'\
#'transponder1.pure; transponder2.pure;'\
#'pose_noisy.x; pose_noisy.y; pose_noisy.z;'\
#'pose_noisy.yaw; pose_noisy.pitch; pose_noisy.roll;'\
#'imu_noisy.dtheta; imu_noisy.dphi; imu_noisy.dpsi;'\
#'loch_doppler_noisy.vx; loch_doppler_noisy.vy; loch_doppler_noisy.vz;'\
#'imu_noisy.ddx; imu_noisy.ddy; imu_noisy.ddz;'\
#'transponder1.noisy; transponder2.noisy;\n')

#with pymorse.Morse() as simu:
#	sub=simu.sub
#	sub.pose_pure.subscribe(update_pose_pure)
#	sub.pose_noisy.subscribe(update_pose_noisy)
#	sub.imu_pure.subscribe(update_imu_pure)
#	sub.imu_noisy.subscribe(update_imu_noisy)
#	sub.pinger_pure.subscribe(update_pinger_pure)
#	sub.pinger_noisy.subscribe(update_pinger_noisy)
#	sub.loch_doppler_pure.subscribe(update_loch_doppler_pure)
#	sub.loch_doppler_noisy.subscribe(update_loch_doppler_noisy)
#	time=datetime.now()
#	delta=0
#	while True: #delta<duration:
#		print('T: %f'%delta)
#		now=datetime.now()
#		delta=(now-time).seconds+(now-time).microseconds/1000000
#		
#		# Concatenate data
#		if (_pose_pure!=0) and (_pose_noisy!=0) and (_imu_pure!=0)\
#		and (_imu_noisy!=0) and (_pinger_pure!=0) and (_pinger_noisy!=0)\
#		and (_loch_doppler_pure!=0) and (_loch_doppler_noisy!=0):				
#			linear_acceleration_pure=_imu_pure['linear_acceleration']
#			linear_acceleration_noisy=_imu_noisy['linear_acceleration']
#			
#			angular_velocity_pure=_imu_pure['angular_velocity']
#			angular_velocity_noisy=_imu_noisy['angular_velocity']
#			
#			loch_doppler_pure=_loch_doppler_pure['linear_velocity']
#			loch_doppler_noisy=_loch_doppler_noisy['linear_velocity']
#			
#			transponders_pure=sorted(_pinger_pure['near_objects'].items())
#			transponders_noisy=sorted(_pinger_noisy['near_objects'].items())
#			
#			# Pure data
#			s=str(_pose_pure['x'])+';'+str(_pose_pure['y'])+';'+str(_pose_pure['z'])+';'
#			s=s+str(_pose_pure['roll'])+';'+str(_pose_pure['pitch'])+';'+str(_pose_pure['yaw'])+';'
#			s=s+str(angular_velocity_pure[0])+";"+str(angular_velocity_pure[1])+";"+str(angular_velocity_pure[2])+";"
#			s=s+str(loch_doppler_pure[0])+";"+str(loch_doppler_pure[1])+";"+str(loch_doppler_pure[2])+";"
#			s=s+str(linear_acceleration_pure[0])+";"+str(linear_acceleration_pure[1])+";"+str(linear_acceleration_pure[2])+";"
#			
#			#s=s+str(transponders_pure['transponder1'])+";"
#			#s=s+str(transponders_pure['transponder2'])+";"
#			print(sorted(_pinger_pure['near_objects'].keys()))
#			print(transponders_pure)
#			
#			# Noisy data
#			s=s+str(_pose_noisy['x'])+';'+str(_pose_noisy['y'])+';'+str(_pose_noisy['z'])+';'
#			s=s+str(_pose_noisy['roll'])+';'+str(_pose_noisy['pitch'])+';'+str(_pose_noisy['yaw'])+';'
#			s=s+str(angular_velocity_noisy[0])+";"+str(angular_velocity_noisy[1])+";"+str(angular_velocity_noisy[2])+";"
#			s=s+str(loch_doppler_noisy[0])+";"+str(loch_doppler_noisy[1])+";"+str(loch_doppler_noisy[2])+";"
#			s=s+str(linear_acceleration_noisy[0])+";"+str(linear_acceleration_noisy[1])+";"+str(linear_acceleration_noisy[2])+";"
#			#s=s+str(transponders_noisy['transponder1'])+";"
#			#s=s+str(transponders_noisy['transponder2'])+";"
#			
#			#f.write(s+'\n')
#		else:
#			print("+++++++++++++++++++++++++++++++++")
#			print("+++++++++++++++++++++++++++++++++")
#			print("++ PB: DATA SENSORS NOT READY? ++")
#			print("+++++++++++++++++++++++++++++++++")
#			print("+++++++++++++++++++++++++++++++++")
#		sleep(1) # /frequency)
#	simu.quit()
#f.close()
#print("Finished logging after %i"%delta)