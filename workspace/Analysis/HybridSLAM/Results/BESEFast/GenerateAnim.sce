//funcprot(0);clear;stacksize('max');
//xdel(winsid()); // close all previously opened windows
//
//// Personal workstation (Linux)
//exec('/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/Analysis/Plots/General/boxUtils.sce', -1)
//exec('/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/Analysis/Plots/General/particlesUtils.sce', -1)
//path_in='/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/Analysis/HybridSLAM/Results/';
//path_out='/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/Analysis/HybridSLAM/Results/';
//
PARTICLE_NB=100;
//LANDMARKS_NB=4;
//
//particles=list();
//raw_data=read_csv(path_in+'box.res',';');
//box=evstr(raw_data);
//
//for i=0:1:PARTICLE_NB-1,
//    disp(sprintf('Loading particle: %i',i));
//    raw_data=read_csv(path_in+sprintf('Particle_%i.res',i),';');
//    particles(i)=evstr(raw_data);
//end

fig=gcf();
fig.figure_size=[1920,1024];
fig.figure_name="HybridSLAM";

axes=gca();
axes.data_bounds=[-40,-40,-30;40,40,1];
axes.isoview="on"

robot=plotSwarm(particles,1,1,'red');
robot_box=plotBox(box(1,1:6),'red');

landmarks=list();
landmarks_boxes=list();

for i=1:LANDMARKS_NB,
    landmarks(i)=plotSwarm(particles,1,i+1,color_list(i));
    landmarks_boxes(i)=plotBox(box(1,12+1+(i-1)*6:12+(i)*6),color_list(i));
end

for i=1:size(particles(1),1),
    drawlater();
    updateSwarm(robot,particles,i,1);
    updateBox(robot_box,box(i,1:6));
    for j=1:LANDMARKS_NB,
        updateSwarm(landmarks(j),particles,i,j+1);
        updateBox(landmarks_boxes(j),box(i,12+1+(j-1)*6:12+(j)*6));
    end
    drawnow();
end