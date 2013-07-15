funcprot(0);
//clear;
xdel(winsid()); // close all previously opened windows

// Personal workstation (Linux)
exec('/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/Analysis/Plots/General/boxUtils.sce', -1)
path_in='/media/Documents/Etudes/ENSTA-Bretagne/Stages/ENSI3-UFRGS/reliable-slam/workspace/Analysis/IntervalAnalysis/Results/BESE/';
raw_file=read_csv(path_in+'DeadReckoning.res',';');
data=evstr(raw_file);

//realtimeinit(0.1);
//realtime(0);
//stacksize('max');

fig=gcf();
fig.figure_size=[1920,1024];
fig.figure_name="Box Dead Reckoning";

axes=gca();
axes.data_bounds=[-40,-40,-30;40,40,30];
drawlater();
robot_box=plotBox(data(1,1:6),'red');
pinger1_box=plotBox(data(1,13:18),'blue');
//pinger1_box.thickness=2;
pinger2_box=plotBox(data(1,19:24),'green');
pinger3_box=plotBox(data(1,25:30),'magenta');
pinger4_box=plotBox(data(1,31:36),'orange');
drawnow();
j=0;
for i=2:size(data,1),
    j=j+1;
    drawlater();
    updateBox(robot_box,data(i,1:6));
//    if(j==100) then
//        plotBox(data(i,1:6),'red');
//        j=0;
//        end
        
//    plotBox(data(i,1:6),'red');
    updateBox(pinger1_box,data(i,13:18));
    updateBox(pinger2_box,data(i,19:24));
    updateBox(pinger3_box,data(i,25:30));
    updateBox(pinger4_box,data(i,31:36));
    drawnow();
end