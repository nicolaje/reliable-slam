funcprot(0);
clear;
xdel(winsid()); // close all previously opened windows

exec('boxUtils.sce', -1)
path_in='';
path_out='';

raw_file=read_csv(path_in+'2000',';');
data=evstr(raw_file);


fig=gcf();
fig.figure_size=[1920,1024];
fig.figure_name="SIVIA";

boxSize=[0.5 0.5 0.5]; // Size of ground truth boxes

axes=gca();
axes.data_bounds=[-40,-40,-30;40,40,30];
axes.isoview="on"

drawlater();

tam=[1 1 1];
//transponders
param3d1(18, -30, list(3, -10));
param3d1(-7, 12, list(17, -10));
param3d1(0, 20, list(5, -10));
param3d1(-27, -20, list(10, -10));
sleep(4000);

bb=plotBox(data(1,1:6),'green');
bbm=plotBox(data(1,7:12),'blue');
        
drawnow();
for i=2:size(data,1),
    drawlater();
        //plotBox(data(i,1:6),'gray');
        updateBox(bb,data(i,1:6));
        updateBox(bbm,data(i,7:12));
    drawnow();
    sleep(500);
//    xs2png(gcf(),sprintf(path_out+"imgs/wrong_circle2_%04d.png",i));
end
mprintf('Fim');
