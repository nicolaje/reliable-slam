funcprot(0);
clear;
xdel(winsid()); // close all previously opened windows
xset('window',20)

exec('particlesUtils.sce', -1)
exec('boxUtils.sce', -1)

path_in='simulatedDataset/';
path_out='';

raw_file=read_csv(path_in+"logHybridParticles.csv",';');
data=evstr(raw_file);

raw_file2=read_csv(path_in+'logGPSPosition.csv',';');
data2=evstr(raw_file2);

raw_file3=read_csv(path_in+"logHybridContractors.csv",';');
data3=evstr(raw_file3);

fig=gcf();
fig.figure_size=[1920,1024];
fig.figure_name="Particles";
fig.auto_resize="off"

//boxSize=[0.5 0.5 0.5]; // Size of ground truth boxes

//axes=gca();
//axes.data_bounds=[-40,-40,-30;40,40,30];
//axes.isoview="on"

//sleep(4000);

//drawlater();
for i=1:size(data,1),
    drawlater();
    
    fig=clf();
    axes=gca();
    axes.data_bounds=[-40,-40,-30;40,40,30];
    axes.isoview="on"
    
    
    //param3d1(data(i,1), data(i,2), list(data(i,3), -9));//melhor
    param3d1(data(i,13), data(i,14), list(data(i,15), -11));//media
    
    param3d1(data2(i,1), data2(i,2), list(data2(i,3), -1));//real
    
    drawlater();
    plotBox(data3(i,1:6),'green');
    plotMidBox(data3(i,1:6),[1,1,1],'green');
    drawnow();
    sleep(500);
    drawnow();
    
    box = data3(i,1:6)
    boxCenter(1)=box(1)+(box(2)-box(1))/2;
    boxCenter(2)=box(3)+(box(4)-box(3))/2;
    boxCenter(3)=box(5)+(box(6)-box(5))/2;


end
//drawnow();

