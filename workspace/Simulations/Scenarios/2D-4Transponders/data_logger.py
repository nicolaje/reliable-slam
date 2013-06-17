#!/usr/bin/python
# -*- coding: iso-8859-15 -*-
import time
import sys
import pymorse
from datetime import datetime
from time import sleep

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

print("Entering data logger")

if(len(sys.argv)>3):
	file_name=sys.argv[1]
	duration=int(sys.argv[2]) # Logging duration in seconds
	frequency=int(sys.argv[3])# Logging frequency in Hz
	f=open(str(file_name), 'w')
	
	# Data format:
	f.write('# pose_pure.x; pose_pure.y; pose_pure.z;'+\
	'pose_noisy.x; pose_noisy.y; pose_noisy.z;'\
	'pose_pure.yaw; pose_pure.pitch; pose_pure.roll;'\
	'pose_noisy.yaw; pose_noisy.pitch; pose_noisy.roll;'\
	'imu_pure.d²x; imu_pure.d²y; imu_pure.d²z;'\
	'imu_noisy.d²x; imu_noisy.d²y; imu_noisy.d²z;'\
	'imu_pure.dtheta; imu_pure.dphi; imu_pure.dpsi;'\
	'imu_noisy.dtheta; imu_noisy.dphi; imu_noisy.dpsi;'\
	'loch_doppler_pure.vx; loch_doppler_pure.vy; loch_doppler_pure.vz;'\
	'loch_doppler_noisy.vx; loch_doppler_noisy.vy; loch_doppler_noisy.vz;'\
	'transponder1.pure; transponder2.pure; transponder3.pure; transponder4.pure;'\
	'transponder1.noisy; transponder2.noisy; transponder3.noisy; transponder4.noisy;\n')
	with pymorse.Morse() as simu:
		sub=simu.sub
		sub.pose_pure.subscribe(update_pose_pure)
		sub.pose_noisy.subscribe(update_pose_noisy)
		sub.imu_pure.subscribe(update_imu_pure)
		sub.imu_noisy.subscribe(update_imu_noisy)
		sub.pinger_pure.subscribe(update_pinger_pure)
		sub.pinger_noisy.subscribe(update_pinger_noisy)
		sub.loch_doppler_pure.subscribe(update_loch_doppler_pure)
		sub.loch_doppler_noisy.subscribe(update_loch_doppler_noisy)
		time=datetime.now()
		delta=0
		while delta<duration:
			print('T: %i'%delta)
			now=datetime.now()
			delta=(now-time).seconds+(now-time).microseconds/1000000
			
			# Concatenate data
			if (_pose_pure!=0) and (_pose_noisy!=0) and (_imu_pure!=0)\
			and (_imu_noisy!=0) and (_pinger_pure!=0) and (_pinger_noisy!=0)\
			and (_loch_doppler_pure!=0) and (_loch_doppler_noisy!=0):				
				linear_acceleration_pure=_imu_pure['linear_acceleration']
				linear_acceleration_noisy=_imu_noisy['linear_acceleration']
				
				angular_velocity_pure=_imu_pure['angular_velocity']
				angular_velocity_noisy=_imu_noisy['angular_velocity']
				
				loch_doppler_pure=_loch_doppler_pure['linear_velocity']
				loch_doppler_noisy=_loch_doppler_noisy['linear_velocity']
				
				transponders_pure=_pinger_pure['near_objects']
				transponders_noisy=_pinger_noisy['near_objects']
				
				s=str(_pose_pure['x'])+';'+str(_pose_pure['y'])+';'+str(_pose_pure['z'])+';'
				s=s+str(_pose_pure['yaw'])+';'+str(_pose_pure['pitch'])+';'+str(_pose_pure['roll'])+';'
				s=s+str(angular_velocity_pure[0])+";"+str(angular_velocity_pure[1])+";"+str(angular_velocity_pure[2])+";"
				s=s+str(loch_doppler_pure[0])+";"+str(loch_doppler_pure[1])+";"+str(loch_doppler_pure[2])+";"
				s=s+str(linear_acceleration_pure[0])+";"+str(linear_acceleration_pure[1])+";"+str(linear_acceleration_pure[2])+";"
				s=s+str(transponders_pure['transponder1'])+";"
				s=s+str(transponders_pure['transponder2'])+";"
				s=s+str(transponders_pure['transponder3'])+";"
				s=s+str(transponders_pure['transponder4'])+";"
				
				s=s+str(_pose_noisy['x'])+';'+str(_pose_noisy['y'])+';'+str(_pose_noisy['z'])+';'
				s=s+str(_pose_noisy['yaw'])+';'+str(_pose_noisy['pitch'])+';'+str(_pose_noisy['roll'])+';'
				s=s+str(angular_velocity_noisy[0])+";"+str(angular_velocity_noisy[1])+";"+str(angular_velocity_noisy[2])+";"
				s=s+str(loch_doppler_noisy[0])+";"+str(loch_doppler_noisy[1])+";"+str(loch_doppler_noisy[2])+";"
				s=s+str(linear_acceleration_noisy[0])+";"+str(linear_acceleration_noisy[1])+";"+str(linear_acceleration_noisy[2])+";"

				s=s+str(transponders_noisy['transponder1'])+";"
				s=s+str(transponders_noisy['transponder2'])+";"
				s=s+str(transponders_noisy['transponder3'])+";"
				s=s+str(transponders_noisy['transponder4'])+";"
				
				f.write(s+'\n')
			else:
				print("+++++++++++++++++++++++++++++++++")
				print("+++++++++++++++++++++++++++++++++")
				print("++ PB: DATA SENSORS NOT READY? ++")
				print("+++++++++++++++++++++++++++++++++")
				print("+++++++++++++++++++++++++++++++++")
			sleep(1/frequency)
		simu.quit()
	f.close()
	print("Finished logging after %i"%delta)
		
else:
	print("Not enough argument to log data")
