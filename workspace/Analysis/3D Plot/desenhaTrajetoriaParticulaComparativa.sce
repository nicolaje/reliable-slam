funcprot(0);
clear;
//xdel(winsid()); // close all previously opened windows
xset('window',20)

exec('particlesUtils.sce', -1)
exec('boxUtils.sce', -1)

path_in='inst/';
path_out='';

raw_file1=read_csv(path_in+'0-MELHOR',';');
data1=evstr(raw_file1);

raw_file2=read_csv(path_in+'ai-MELHOR',';');
data2=evstr(raw_file2);

raw_file3=read_csv(path_in+'fp-MELHOR',';');
data3=evstr(raw_file3);

fig=gcf();
fig.figure_size=[1920,1024];
fig.figure_name="Particles";
fig.auto_resize="off"

axes=gca();
axes.data_bounds=[-40,-40,-30;40,40,30];
axes.isoview="on"

param3d1(-54.84, 52.11, list(-26.18, -10));
ea=gce();ea.line_mode='off';ea.mark_mode='on';ea.mark_size=1;ea.mark_foreground=1;
param3d1(-36.73, -0.68, list(-27.75, -10));
eb=gce();eb.line_mode='off';eb.mark_mode='on';eb.mark_size=1;eb.mark_foreground=1;
param3d1(22.73, 43.30, list(-29.53, -10));
ec=gce();ec.line_mode='off';ec.mark_mode='on';ec.mark_size=1;ec.mark_foreground=1;
param3d1(-70.74, 50.36, list(-27.83, -10));
ed=gce();ed.line_mode='off';ed.mark_mode='on';ed.mark_size=1;ed.mark_foreground=1;
//sleep(4000);

//drawlater();
for i=1:size(data1,1),
    drawlater();   
    
    param3d1(data1(i,1), data1(i,2), list(data1(i,3), 0));//real  
    e1=gce();e1.line_mode='off';e1.mark_mode='on';e1.mark_size=1;e1.mark_foreground=2;//azul
    
    param3d1(data2(i,13), data2(i,14), list(data2(i,15), 0));//ai
    e2=gce();e2.line_mode='off';e2.mark_mode='on';e2.mark_size=1;e2.mark_foreground=5;//vermelho
    
    param3d1(data3(i,13), data3(i,14), list(data3(i,15), 0));//fp
    e3=gce();e3.line_mode='off';e3.mark_mode='on';e3.mark_size=1;e3.mark_foreground=3;//verde
    
    
//    param3d1(data(i,13), data(i,14), list(data(i,15), -11));//media
    drawnow();


end



//drawnow();

