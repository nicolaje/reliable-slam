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
pose.add_stream('socket')
sub.append(pose_pure)
pose.frequency(sensors_freq)

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

# IMU Noisy
imu_noisy=IMU()
imu_noisy.add_stream('socket')
sub.append(imu_noisy)
imu_noisy.frequency(sensors_freq)

# Proximity Sensor(pinger)
pinger_noisy=Proximity()
pinger_noisy.add_stream('socket')
sub.append(pinger_noisy)
pinger_pure.frequency(sensors_freq)

# Velocity (Loch-Doppler): vx, vy, vz
loch_doppler_noisy=Velocity()
loch_doppler_noisy.add_stream('socket')
sub.append(loch_doppler_noisy)
loch_doppler_noisy.frequency(sensors_freq)
