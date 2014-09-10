funcprot(0);
clear;
//xdel(winsid()); // close all previously opened windows
xset('window',20)

exec('particlesUtils.sce', -1)
exec('boxUtils.sce', -1)

path_in='inst/';
path_out='';

fig=gcf();
fig.figure_size=[1920,1024];
fig.figure_name="Particles";
fig.auto_resize="off"

axes=gca();
//axes.data_bounds=[-130,-60,-60;70,140,1];
axes.data_bounds=[-70,-70,-80;200,220,10];
axes.isoview="on"

//param3d1(-54.84, 52.11, list(-26.18, -10));
//ea=gce();ea.line_mode='off';ea.mark_mode='on';ea.mark_size=1;ea.mark_foreground=1;
//param3d1(-36.73, -0.68, list(-27.75, -10));
//eb=gce();eb.line_mode='off';eb.mark_mode='on';eb.mark_size=1;eb.mark_foreground=1;
//param3d1(22.73, 43.30, list(-29.53, -10));
//ec=gce();ec.line_mode='off';ec.mark_mode='on';ec.mark_size=1;ec.mark_foreground=1;
//param3d1(-70.74, 50.36, list(-27.83, -10));
//ed=gce();ed.line_mode='off';ed.mark_mode='on';ed.mark_size=1;ed.mark_foreground=1;


param3d1(0, 0, list(-10, -10));
ed=gce();ed.line_mode='off';ed.mark_mode='on';ed.mark_size=1;ed.mark_foreground=1;
param3d1(60, 0, list(-30, -10));
ed=gce();ed.line_mode='off';ed.mark_mode='on';ed.mark_size=1;ed.mark_foreground=1;
param3d1(30, 30, list(-50, -10));
ed=gce();ed.line_mode='off';ed.mark_mode='on';ed.mark_size=1;ed.mark_foreground=1;
param3d1(0, 60, list(-30, -10));
ed=gce();ed.line_mode='off';ed.mark_mode='on';ed.mark_size=1;ed.mark_foreground=1;
param3d1(60, 60, list(-10, -10));
ed=gce();ed.line_mode='off';ed.mark_mode='on';ed.mark_size=1;ed.mark_foreground=1;
param3d1(30, 90, list(-50, -10));
ed=gce();ed.line_mode='off';ed.mark_mode='on';ed.mark_size=1;ed.mark_foreground=1;
param3d1(0, 120, list(-10, -10));
ed=gce();ed.line_mode='off';ed.mark_mode='on';ed.mark_size=1;ed.mark_foreground=1;
param3d1(60, 120, list(-30, -10));
ed=gce();ed.line_mode='off';ed.mark_mode='on';ed.mark_size=1;ed.mark_foreground=1;
