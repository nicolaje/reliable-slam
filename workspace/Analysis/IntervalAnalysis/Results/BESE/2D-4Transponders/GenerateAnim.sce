funcprot(0);
//clear;
xdel(winsid()); // close all previously opened windows

// Personal workstation (Linux)
exec('/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/Analysis/Plots/General/boxUtils.sce', -1)
path_in='/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/Analysis/IntervalAnalysis/Results/BESE/';
path_out='/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/Analysis/IntervalAnalysis/Results/BESE/';

// Circle trajectory
//raw_file=read_csv(path_in+'DeadReckoning.res',';');
//ground_truth=read_csv(path_in+'GroundTruth.res',';');
//data=evstr(raw_file);
//data_truth=evstr(ground_truth);

// Smaller circle trajectory
raw_file=read_csv(path_in+'DeadReckoning3.res',';');
ground_truth=read_csv(path_in+'GroundTruth3.res',';');
data=evstr(raw_file);
data_truth=evstr(ground_truth);

fig=gcf();
fig.figure_size=[1920,1024];
fig.figure_name="BoxSLAM";

boxSize=[0.5 0.5 0.5]; // Size of ground truth boxes

axes=gca();
axes.data_bounds=[-40,-40,-30;40,40,30];
drawlater();
robot_box=plotBox(data(1,1:6),'red');
robot_box_center=plotMidBox(data(1,1:6),boxSize,'red');
robot_box_true=plotBox2(data_truth(1,1:3),boxSize,'black');

pinger1_box=plotBox(data(1,13:18),'blue');
//pinger1_center=plotBox()
pinger2_box=plotBox(data(1,19:24),'green');
pinger3_box=plotBox(data(1,25:30),'magenta');
pinger4_box=plotBox(data(1,31:36),'orange');

pinger1_true=plotBox2([18 -30 3],boxSize,'blue');
pinger2_true=plotBox2([-7 12 17],boxSize,'green');
pinger3_true=plotBox2([0 20 5],boxSize,'magenta');
pinger4_true=plotBox2([-27 -20 10],boxSize,'orange');

drawnow();
for i=1:size(data,1),
    drawlater();
    updateBox(robot_box,data(i,1:6));
    updateBox2(robot_box_true,data_truth(i,1:3),boxSize);
    updateMidBox(robot_box_center,data(i,1:6),boxSize);
    
    if(modulo(i,10)==0) then
        robot_box_true_history=plotBox2(data_truth(i,1:3),boxSize,'black');
        robot_box_center_history=plotMidBox(data(i,1:6),boxSize,'red');
    end
    
//    plotBox(data(i,1:6),'red');
    updateBox(pinger1_box,data(i,13:18));
    updateBox(pinger2_box,data(i,19:24));
    updateBox(pinger3_box,data(i,25:30));
    updateBox(pinger4_box,data(i,31:36));
    drawnow();
//    xs2png(gcf(),sprintf(path_out+"imgs/wrong_circle2_%04d.png",i));
end