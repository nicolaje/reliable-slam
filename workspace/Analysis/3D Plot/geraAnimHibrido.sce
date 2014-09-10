funcprot(0);
clear;
xdel(winsid()); // close all previously opened windows
exec('particlesUtils.sce', -1)
exec('boxUtils.sce', -1)
path_in='amb3traj4/';
path_out='';


sleep(1000);


raw_file=read_csv(path_in+'0hibridoContratores.csv',';');
//raw_file=read_csv(path_in+'0hibridoSivia1BB.csv',';');
data=evstr(raw_file);
raw_file2=read_csv(path_in+'0hibridoContratoresFP.csv',';'); 
//raw_file2=read_csv(path_in+'0hibridoSivia1FP.csv',';');
data2=evstr(raw_file2);
raw_file3=read_csv(path_in+'0fp.csv',';');
data3=evstr(raw_file3);
raw_file4=read_csv(path_in+'logReaisAmb3Traj4.csv',';');
data4=evstr(raw_file4);

fig=gcf();
fig.figure_size=[1920,1024];
fig.figure_name="*--* ";

boxSize=[0.5 0.5 0.5]; // Size of ground truth boxes

axes=gca();
axes.data_bounds=[-200,-200,-400;200,200,2];
axes.isoview="on"

drawlater();

tam=[1 1 1];
//transponders
//param3d1(-150,130,list(-40, 0));
//    e1=gce();e1.line_mode='off';e1.mark_mode='on';e1.mark_size=1;e1.mark_foreground=0;
//param3d1(-38,15,list(-200, 0));
//    e1=gce();e1.line_mode='off';e1.mark_mode='on';e1.mark_size=1;e1.mark_foreground=0;
//param3d1(-112,-10,list(-20, 0));
//    e1=gce();e1.line_mode='off';e1.mark_mode='on';e1.mark_size=1;e1.mark_foreground=0;
//param3d1(-25,-115,list(-130, 0));
//    e1=gce();e1.line_mode='off';e1.mark_mode='on';e1.mark_size=1;e1.mark_foreground=0;
//param3d1(40,100,list(-100, 0));
//    e1=gce();e1.line_mode='off';e1.mark_mode='on';e1.mark_size=1;e1.mark_foreground=0;
//param3d1(180,30,list(-300, 0));
//    e1=gce();e1.line_mode='off';e1.mark_mode='on';e1.mark_size=1;e1.mark_foreground=0;
//param3d1(90,-75,list(-60, 0));
//    e1=gce();e1.line_mode='off';e1.mark_mode='on';e1.mark_size=1;e1.mark_foreground=0;
//param3d1(130,-190,list(-255, 0));
//    e1=gce();e1.line_mode='off';e1.mark_mode='on';e1.mark_size=1;e1.mark_foreground=0;




box=plotBox(data(1,1:6),'green');
//robot_box_center=plotMidBox(data(1,1:6),boxSize,'red');


    
drawnow();

for i=2:size(data,1),
    drawlater();
      
    updateBox(box,data(i,1:6));
    m1=((data(i,1)+data(i,2))/2);
    m2=((data(i,3)+data(i,4))/2);
    m3=((data(i,5)+data(i,6))/2);
    
  //  param3d1(m1,m2,list(m3, 0));
//    e2=gce();e2.line_mode='off';e2.mark_mode='on';e2.mark_size=1;e2.mark_foreground=3;//verde
    
  //  param3d1(data2(i,13),data2(i,14),list(data2(i,15), 0));
  //  e3=gce();e3.line_mode='off';e3.mark_mode='on';e3.mark_size=1;e3.mark_foreground=2;//azul
    
 //   param3d1(data3(i,13),data3(i,14),list(data3(i,15), 0));
 //   e5=gce();e5.line_mode='off';e5.mark_mode='on';e5.mark_size=1;e5.mark_foreground=5;//vermelho
    
    param3d1(data4(i,1),data4(i,2),list(data4(i,3), 0));
    e4=gce();e4.line_mode='off';e4.mark_mode='on';e4.mark_size=1;e4.mark_foreground=4;//ciano
    
        
    drawnow();
    sleep(50);

end
mprintf('Fim');
