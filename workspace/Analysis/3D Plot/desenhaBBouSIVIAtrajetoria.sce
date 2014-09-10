funcprot(0);
clear;
xdel(winsid()); // close all previously opened windows

exec('boxUtils.sce', -1)
path_in='';
path_out='';

raw_file=read_csv(path_in+'DeadReckoning3.res',';');
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
t_1=plotBox2([-54.845 52.115 -26.181],tam,'blue');
t_2=plotBox2([-36.739 -0.684 -27.752],tam,'blue');
t_3=plotBox2([22.7389 43.308 -29.530],tam,'blue');
t_4=plotBox2([-70.747 50.364 -27.836],tam,'blue');

drawnow();
for i=1:size(data,1),
    drawlater();
        plotBox(data(i,1:6),'gray');
        //plotBox(data(i,1:6),'green');
        //plotBox(data(i,7:12),'blue');
    drawnow();
//    xs2png(gcf(),sprintf(path_out+"imgs/wrong_circle2_%04d.png",i));
end
mprintf('Fim');
