funcprot(0);
clear;
xdel(winsid()); // close all previously opened windows

// Personal workstation (Linux)
exec('/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/Analysis/Plots/General/boxUtils.sce', -1)
path_in='/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/Analysis/HybridSLAM/Results/BESEFast';
path_out='/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/Analysis/HybridSLAM/Results/BESEFast';

PARTICLE_NB=500;
particles=list();

for i=1:1:PARTICLE_NB,
    raw_data=read_csv(path_in+sprintf('particle_%i.csv',i),';');
    particles(i)=evstr(raw_data);
end