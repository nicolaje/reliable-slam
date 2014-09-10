funcprot(0);
clear;
xdel(winsid()); // close all previously opened windows
exec('particlesUtils.sce', -1)
exec('boxUtils.sce', -1)
path_in='';
path_out='';

raw_file=read_csv(path_in+'2000',';');
data=evstr(raw_file);


fig=gcf();
fig.figure_size=[1920,1024];
fig.figure_name="Localization - Contractors";

boxSize=[0.5 0.5 0.5]; // Size of ground truth boxes

axes=gca();
axes.data_bounds=[-200,-200,-70;200,200,2];
axes.isoview="on"

drawlater();

tam=[1 1 1];
//transponders
param3d1(0, 0, list(0, -7));



box=plotBox(data(1,1:6),'green');
//robot_box_center=plotMidBox(data(1,1:6),boxSize,'red');

//e1=gce();e1.line_mode='off';e1.mark_mode='on';e1.mark_size=1;e1.mark_foreground=2;//azul
param3d1(((data(1,1)+data(1,2))/2), ((data(1,3)+data(1,4))/2), list(((data(1,5)+data(1,6))/2), 0));
     
drawnow();

sleep(40);
for i=2:size(data,1),
    drawlater();
      
    updateBox(box,data(i,1:6));
    m1=((data(i,1)+data(i,2))/2);
    m2=((data(i,3)+data(i,4))/2);
    m3=((data(i,5)+data(i,6))/2);
    e1=gce();e1.line_mode='off';e1.mark_mode='on';e1.mark_size=1;e1.mark_foreground=2;//azul
    param3d1(m1,m2,list(m3, 0));
    
   // updateMidBox(robot_box_center,data(i,1:6),boxSize);
   //plotMidBox(data(i,1:6),boxSize,'red');
        
    drawnow();
    sleep(500);

end
mprintf('Fim');
