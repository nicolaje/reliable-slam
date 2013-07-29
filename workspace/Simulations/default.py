#! /usr/bin/env morseexec

import sys
from morse.builder import *
import logging; logger = logging.getLogger("morse." + __name__)
from Simulations.builder.robots import Transponder
from Simulations.builder.actuators import Motionfull
from math import *

file_name=0

if len(sys.argv) <2:
    logger.info('Loading default landmarks positions file.')
    file_name="data/default.pos"
else:
    file_name=sys.argv[1]
    
f=open("data/"+file_name,'r')

idx=1
for line in f:
    transponder=Transponder()
    pos=line.split(';')
    transponder.translate(x=float(pos[0]), y=float(pos[1]), z=float(pos[2]))
    idx+=1
f.close()

logger.info(str(idx)+' landmarks positioned from '+file_name+' file.')

################################
#			       #
# Tunable parameters           #
#			       #
################################
sensors_freq=10                #
range_pinger=1000	       # the pinger can detect transponders up to 1000 m
orientation_std=0.02*pi/180    # 0.02 ° => 0.02*pi/180 rad
gyro_std=0.01*pi/180           # 0.01 °/s => 0.01*pi/180 rad/s
accelero_std=0.01*9.81         # 10 mg
pinger_std=0.03                # 0.03 m
pressure_std=0.15              # 0.15 m
loch_doppler_std=0.04          # 0.04 m/s
################################

sub=Submarine()

#############
# Actuators #
#############

# V,W controller
motion = Motionfull()
motion.add_stream('socket')
sub.append(motion)

###########
# Sensors #
###########

# Pose(x, y, z(depth), orientation)
pose_pure=Pose()
pose_pure.add_stream('socket')
sub.append(pose_pure)
pose_pure.frequency(sensors_freq)

# IMU(radial speed, linear accelerations)
imu_pure=IMU()
imu_pure.add_stream('socket')
sub.append(imu_pure)
imu_pure.frequency(sensors_freq)

# Proximity Sensor(pinger)
pinger_pure=Proximity()
pinger_pure.add_stream('socket')
sub.append(pinger_pure)
pinger_pure.frequency(sensors_freq)
pinger_pure.properties(Range=range_pinger)

# Velocity (Loch-Doppler): vx, vy, vz
loch_doppler_pure=Velocity()
loch_doppler_pure.add_stream('socket')
sub.append(loch_doppler_pure)
loch_doppler_pure.frequency(sensors_freq)

#################
# Noisy Sensors #
#################

# Noisy Pose
pose_noisy=Pose()
pose_noisy.add_stream('socket')
sub.append(pose_noisy)
pose_noisy.frequency(sensors_freq)
pose_noisy.alter('', 'morse.modifiers.pose_noise.PoseNoiseModifier', pos_std=pressure_std, rot_std=orientation_std)

# IMU Noisy
imu_noisy=IMU()
imu_noisy.add_stream('socket')
sub.append(imu_noisy)
imu_noisy.frequency(sensors_freq)
imu_noisy.alter('','morse.modifiers.imu_noise.IMUNoiseModifier', gyro_std=gyro_std, accel_std=accelero_std)

# Proximity Sensor(pinger)
pinger_noisy=Proximity()
pinger_noisy.add_stream('socket')
sub.append(pinger_noisy)
#pinger_noisy.frequency(sensors_freq)
#pinger_noisy.properties(Range=range_pinger)
#pinger_noisy.alter('', 'ProximityModifier.ProximityModifier')

# Velocity (Loch-Doppler): vx, vy, vz
loch_doppler_noisy=Velocity()
loch_doppler_noisy.add_stream('socket')
sub.append(loch_doppler_noisy)
#loch_doppler_noisy.frequency(sensors_freq)
#loch_doppler_noisy.alter('', 'VelocityModifier.VelocityModifier')

env=Environment('water-1/deep_water',True)
env.place_camera([-20,-20,10])
env.aim_camera([45,0,-90])
