funcprot(0);
clear;
xdel(winsid()); // close all previously opened windows
stacksize('max')

// Personal workstation (Linux)
exec('/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/Analysis/Plots/General/boxUtils.sce', -1)
exec('/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/Analysis/Plots/General/particlesUtils.sce', -1)
path_in='/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/Analysis/HybridSLAM/Results/';
path_out='/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/Analysis/HybridSLAM/Results/';

PARTICLE_NB=500;
LANDMARKS_NB=4;

particles=list();

for i=0:1:PARTICLE_NB-1,
    raw_data=read_csv(path_in+sprintf('Particle_%i.res',i),';');
    particles(i)=evstr(raw_data);
end

fig=gcf();
fig.figure_size=[1920,1024];
fig.figure_name="HybridSLAM";

axes=gca();
axes.data_bounds=[-40,-40,-30;40,40,30];
axes.isoview="on"

robot=plotSwarm(particles,1,1,'black');
landmarks=list();

for i=1:LANDMARKS_NB,
    landmarks(i)=plotSwarm(particles,1,i+1,color_list(i));
end

for i=1:size(particles(1),1),
    drawlater();
    updateSwarm(robot,particles,i,1);
    for j=1:LANDMARKS_NB,
        updateSwarm(landmarks(j),particles,i,j+1);
    end
    drawnow();
end