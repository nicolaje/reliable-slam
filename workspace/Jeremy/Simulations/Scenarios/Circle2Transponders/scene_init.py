from morse.builder import *

######################
# Tunable parameters #
######################
sensors_freq=1       # 1Hz enough for now
######################

sub=Submarine()

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
pinger_pure.properties(Range=100)

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
pose_noisy.alter('', 'morse.modifiers.pose_noise.PoseNoiseModifier', pos_std=0.15, rot_std=0.01) #{'yaw':0.02, 'roll':0.01, 'pitch':0.01})

# IMU Noisy
imu_noisy=IMU()
imu_noisy.add_stream('socket')
sub.append(imu_noisy)
imu_noisy.frequency(sensors_freq)

# Proximity Sensor(pinger)
pinger_noisy=Proximity()
pinger_noisy.add_stream('socket')
sub.append(pinger_noisy)
pinger_noisy.frequency(sensors_freq)
pinger_noisy.properties(Range=100)
pinger_noisy.alter('', 'ProximityModifier.ProximityModifier')

# Velocity (Loch-Doppler): vx, vy, vz
loch_doppler_noisy=Velocity()
loch_doppler_noisy.add_stream('socket')
sub.append(loch_doppler_noisy)
loch_doppler_noisy.frequency(sensors_freq)

#############
# Actuators #
#############

# V,W controller
motion=MotionVW()
motion.add_stream('socket')
motion.add_stream('service')
sub.append(motion)

sub.translate(z=0.5,y=-30)

####################
# Environment      #
# trans1=[20,0,0]  #
# trans2=[-20,0,0] #
####################

transponder1=Robot('../../Models/Transponder.blend')
transponder1.translate(x=20)

transponder2=Robot('../../Models/Transponder.blend')
transponder2.translate(x=-20)

env=Environment('../../Models/SimpleOceanGround.blend')
