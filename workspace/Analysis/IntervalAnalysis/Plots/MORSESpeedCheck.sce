funcprot(0);
//clear;
xdel(winsid()); // close all previously opened windows

// Personal workstation (Linux)
exec('/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/Analysis/Plots/General/boxUtils.sce', -1)
path_in='/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/Analysis/IntervalAnalysis/Results/BESE/';

// Smaller circle trajectory
//ground_truth=read_csv(path_in+'GroundTruth3.res',';');
//data_truth=evstr(ground_truth);

linspeed_generatedx=diff(data_truth(:,1))/0.1;
linspeed_generatedy=diff(data_truth(:,2))/0.1;
linspeed_generatedz=diff(data_truth(:,3))/0.1;

linspeed_generated_norm=sqrt(linspeed_generatedx^2+linspeed_generatedy^2+linspeed_generatedz^2);

linspeed_morsex=data_truth(:,7);
linspeed_morse_norm=sqrt(data_truth(:,7)^2+data_truth(:,8)^2+data_truth(:,9)^2);

angspeed_generatedx=diff(data_truth(:,4))/0.1;
angspeed_generatedy=diff(data_truth(:,5))/0.1;
angspeed_generatedz=diff(data_truth(:,6))/0.1;

angspeed_generated_norm=sqrt(angspeed_generatedx^2+angspeed_generatedy^2+angspeed_generatedz^2);

angspeed_morse_norm=sqrt(data_truth(:,10)^2+data_truth(:,11)^2+data_truth(:,12)^2);

plot(angspeed_generated_norm,'cyan')
 
plot(angspeed_morse_norm,color('purple'))
 
plot(angspeed_generatedx,'r');
 
plot(angspeed_generatedy,'g');
 
plot(angspeed_generatedz,'b');
 
plot(angspeed_generatedz,'magenta');