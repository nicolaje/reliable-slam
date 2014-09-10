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
fig.figure_name="Ambiente";

boxSize=[0.5 0.5 0.5]; // Size of ground truth boxes

axes=gca();
axes.data_bounds=[-200,-200,-400;200,200,0];
axes.isoview="on"

drawlater();

tam=[1 1 1];
//transponders
param3d1(100, 100, list(-50, -7));
param3d1(-100, -100, list(-50, -7));
//param3d1(100, -100, list(-50, -7));
//param3d1(-100, 100, list(-50, -7));
//param3d1(100, 100, list(-200, -7));
//param3d1(-100, -100, list(-200, -7));
param3d1(100, -100, list(-200, -7));
param3d1(-100, 100, list(-200, -7));

drawnow();


end
mprintf('Fim');
