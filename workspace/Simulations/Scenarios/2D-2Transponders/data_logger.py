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
	print("Pose Pure data: "+str(data))
	
def update_pose_noisy(data):
	print("Pose Noisy data:"+str(data))

def update_imu_pure(data):
	print("IMU Pure data: "+str(data))

def update_imu_noisy(data):
	print("IMU Noisy data: "+str(data))

def update_pinger_pure(data):
	print("Pinger pure data: "+str(data))
	
def update_pinger_noisy(data):
	print("Pinger noisy data: "+str(data))

def update_loch_doppler_pure(data):
	print("Loch Doppler pure: "+str(data))
	
def update_loch_doppler_noisy(data):
	print("Loch Doppler noisy: "+str(data))

print("Entering data logger")

if(len(sys.argv)>2):
	file_name=sys.argv[1]
	duration=int(sys.argv[2]) # Logging duration in seconds
	f=open(str(file_name), 'w')
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
#		while delta<duration:
#			pass
		sleep(10)
		
	simu.quit()
	f.close()
	print("Finished logging after %i"%delta)
		
else:
	print("Not enough argument to log data")
