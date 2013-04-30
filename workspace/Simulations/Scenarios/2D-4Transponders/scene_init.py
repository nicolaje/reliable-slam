from morse.builder import *

#########################
#			#
# Tunable parameters    #
#			#
#########################
sensors_freq=1          # 1 Hz enough for now
range_pinger=100	# the pinger can detect transponders up to 100 m
orientation_std=0.02    # 0.02 °
gyro_std=0.01           # 0.01 °/s
accelero_std=0.01*9.81  # 10 mg
pinger_std=0.3          # 0.3 m
pressure_std=0.15       # 0.15 m
loch_doppler_std=0.04   # 0.04 m/s
#########################

sub=Submarine()

#############
# Actuators #
#############

# V,W controller
motion=MotionVW()
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
pinger_noisy.frequency(sensors_freq)
pinger_noisy.properties(Range=range_pinger)
pinger_noisy.alter('', 'ProximityModifier.ProximityModifier')

# Velocity (Loch-Doppler): vx, vy, vz
loch_doppler_noisy=Velocity()
loch_doppler_noisy.add_stream('socket')
sub.append(loch_doppler_noisy)
loch_doppler_noisy.frequency(sensors_freq)
loch_doppler_noisy.alter('', 'VelocityModifier.VelocityModifier')

sub.translate(z=0.5,y=-30)

####################
# Environment      #
# trans1=[20,0,0]  #
# trans2=[-20,0,0] #
# trans3=[0,20,0]  #
# trans4=[0,-20,0] #
####################

transponder1=Robot('../../Models/Transponder.blend')
transponder1.translate(x=20)

transponder2=Robot('../../Models/Transponder.blend')
transponder2.translate(x=-20)

transponder3=Robot('../../Models/Transponder.blend')
transponder3.translate(y=20)

transponder4=Robot('../../Models/Transponder.blend')
transponder4.translate(y=-20)

env=Environment('../../Models/SimpleOceanGround.blend')
env.place_camera([-20,-20,10])
env.aim_camera([45,0,-90])
