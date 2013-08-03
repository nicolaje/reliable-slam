color_list=['magenta';'pink';'brown';'green';'papayawhip';'linen';'azure';'moccasin';'mintcream';'lavender']

function [X,Y,Z]=fileList2Mat(fileList,line,index)
    X=[];
    Y=[];
    Z=[];
    for i=1:size(fileList),
        X=[X;fileList(i)(line,(index-1)*3+1)];
        Y=[Y;fileList(i)(line,(index-1)*3+2)];
        Z=[Z;fileList(i)(line,(index-1)*3+3)];
    end
endfunction

function handle=plotSwarm(fileList,line,index,colour)
    [X,Y,Z]=fileList2Mat(fileList,line,index);
    param3d(X,Y,Z);
    handle=gce();
    handle.line_mode="off";
    handle.mark_mode="on";
    handle.mark_foreground=color(colour);
endfunction

function updateSwarm(handle,fileList,line,index)
    [X,Y,Z]=fileList2Mat(fileList,line,index);
    handle.data=[X,Y,Z];
endfunction