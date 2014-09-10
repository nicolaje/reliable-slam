funcprot(0);
clear;
xdel(winsid()); // close all previously opened windows
xset('window',20)

exec('particlesUtils.sce', -1)
exec('boxUtils.sce', -1)

path_in='';
path_out='';

raw_file=read_csv(path_in+'traj04.csv',';');
data=evstr(raw_file);

//raw_file2=read_csv(path_in+'0',';');
//data2=evstr(raw_file2);

fig=gcf();
fig.figure_size=[1920,1024];
fig.figure_name="Particles";
//fig.auto_resize="off"

axes=gca();
axes.data_bounds=[-200,-200,-400;200,200,2];
axes.isoview="on"

param3d1(-150,130,list(-40, 0));
    e1=gce();e1.line_mode='off';e1.mark_mode='on';e1.mark_size=1;e1.mark_foreground=0;
param3d1(-38,15,list(-200, 0));
    e1=gce();e1.line_mode='off';e1.mark_mode='on';e1.mark_size=1;e1.mark_foreground=0;
param3d1(-112,-10,list(-20, 0));
    e1=gce();e1.line_mode='off';e1.mark_mode='on';e1.mark_size=1;e1.mark_foreground=0;
param3d1(-25,-115,list(-130, 0));
    e1=gce();e1.line_mode='off';e1.mark_mode='on';e1.mark_size=1;e1.mark_foreground=0;
param3d1(40,100,list(-100, 0));
    e1=gce();e1.line_mode='off';e1.mark_mode='on';e1.mark_size=1;e1.mark_foreground=0;
param3d1(180,30,list(-300, 0));
    e1=gce();e1.line_mode='off';e1.mark_mode='on';e1.mark_size=1;e1.mark_foreground=0;
param3d1(90,-75,list(-60, 0));
    e1=gce();e1.line_mode='off';e1.mark_mode='on';e1.mark_size=1;e1.mark_foreground=0;
param3d1(130,-190,list(-255, 0));
    e1=gce();e1.line_mode='off';e1.mark_mode='on';e1.mark_size=1;e1.mark_foreground=0;

sleep(400);

//drawlater();
for i=1:10:size(data,1),
    drawlater();   
    
    param3d1(data(i,1),data(i,2),list(data(i,3), 0));
    e1=gce();e1.line_mode='off';e1.mark_mode='on';e1.mark_size=1;e1.mark_foreground=2;//azul

    drawnow();


end
//drawnow();

