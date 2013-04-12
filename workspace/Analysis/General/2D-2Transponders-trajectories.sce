chdir('/home/jeremy/workspace/reliable-slam/workspace')
cd Simulations/Scenarios/2D-2Transponders

raw_file=read_csv('2D-2Transponders.res',';');

// avoid the first comment line + parse strings to double
data=evstr(raw_file(2:size(raw_file,1),:));

// Data Format
// pose_pure.x; pose_pure.y; pose_pure.z;pose_noisy.x; pose_noisy.y; pose_noisy.z;pose_pure.yaw; pose_pure.pitch; pose_pure.roll;pose_noisy.yaw; pose_noisy.pitch; pose_noisy.roll;imu_pure.d²x; imu_pure.d²y; imu_pure.d²z;imu_noisy.d²x; imu_noisy.d²y; imu_noisy.d²z;imu_pure.dtheta; imu_pure.dphi; imu_pure.dpsi;imu_noisy.dtheta; imu_noisy.dphi; imu_noisy.dpsi;transponder1.pure; transponder2.pure;transponder1.noisy; transponder2.noisy;loch_doppler_pure.vx; loch_doppler_pure.vy; loch_doppler_pure.vz;loch_doppler_noisy.vx; loch_doppler_noisy.vy; loch_doppler_noisy.vz;

// plot ground truth
plot(data(:,1),data(:,2),'b');
plot(data(:,4),data(:,5),'r');
legend(['True Trajectory';'Noisy Trajectory']);