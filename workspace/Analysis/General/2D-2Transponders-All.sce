//chdir(fullpath('../../Simulations/Scenarios/2D-2Transponders'))
cd /media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/Simulations/Scenarios/2D-2Transponders

raw_file=read_csv('2D-2Transponders.res',';');

// avoid the first comment line + parse strings to double
data=evstr(raw_file(2:size(raw_file,1),:));

// Data Format
// pose_pure.x; pose_pure.y; pose_pure.z;pose_noisy.x; pose_noisy.y; pose_noisy.z;pose_pure.yaw; pose_pure.pitch; pose_pure.roll;pose_noisy.yaw; pose_noisy.pitch; pose_noisy.roll;imu_pure.d²x; imu_pure.d²y; imu_pure.d²z;imu_noisy.d²x; imu_noisy.d²y; imu_noisy.d²z;imu_pure.dtheta; imu_pure.dphi; imu_pure.dpsi;imu_noisy.dtheta; imu_noisy.dphi; imu_noisy.dpsi;transponder1.pure; transponder2.pure;transponder1.noisy; transponder2.noisy;loch_doppler_pure.vx; loch_doppler_pure.vy; loch_doppler_pure.vz;loch_doppler_noisy.vx; loch_doppler_noisy.vy; loch_doppler_noisy.vz;

scf(0);

// circle
subplot(4,2,1)
plot(data(:,1),data(:,2),'b')
plot(data(:,4),data(:,5),'r--')
legend(["True trajectory";"Noisy trajectory"])

// depth
subplot(4,2,2)
plot(data(:,3),'b')
plot(data(:,6),'r--')
legend(["True depth";"Noisy depth"])

// orientations
subplot(4,2,3)
plot(data(:,7),'b')
plot(data(:,8),'g')
plot(data(:,9),'r')
plot(data(:,10),'b--')
plot(data(:,11),'g--')
plot(data(:,12),'r--')
legend(["True Yaw";"True Pitch";"True Roll";"Noisy Yaw";"Noisy Pitch";"Noisy Roll"])

// angular speed
subplot(4,2,4)
plot(data(:,19),'b')
plot(data(:,20),'g')
plot(data(:,21),'r')
plot(data(:,22),'b--')
plot(data(:,23),'g--')
plot(data(:,24),'r--')
legend(["True dPsi";"True dTheta";"True dPhi";"Noisy dPsi";"Noisy dTheta";"Noisy dPhi"])

// translation speed
subplot(4,2,5)
plot(data(:,29),'b')
plot(data(:,30),'g')
plot(data(:,31),'r')
plot(data(:,32),'b--')
plot(data(:,33),'g--')
plot(data(:,34),'r--')
legend(["True Vx";"True Vy";"True Vz";"Noisy Vx";"Noisy Vy";"Noisy Vz"])

// translation acceleration
subplot(4,2,6)
plot(data(:,13),'b')
plot(data(:,14),'g')
plot(data(:,15),'r')
plot(data(:,16),'b--')
plot(data(:,17),'g--')
plot(data(:,18),'r--')
legend(["True dVx";"True dVy";"True dVz";"Noisy dVx";"Noisy dVy";"Noisy dVz"])


// pinger distances
subplot(4,1,4)
plot(data(:,25),'b')
plot(data(:,26),'r')
plot(data(:,27),'b--')
plot(data(:,28),'r--')
legend(["True distance to pinger1";"True distance to pinger2";"Noisy distance to pinger1";"Noisy distance to pinger2"])

xs2png(0,'/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/Analysis/Plots/General/2D-2Transponders-All.png'));