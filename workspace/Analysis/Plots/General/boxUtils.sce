function [X,Y,Z]=box2mat(box)
// Adapted from http://usingscilab.blogspot.fr/2012/09/plot3d2-creating-cube.html
    x=box(1:2);
    X=[x(1) x(1) x(2) x(2) x(1);
     x(1) x(1) x(2) x(2) x(1);
     x(1) x(1) x(2) x(2) x(1);
     x(1) x(1) x(2) x(2) x(1)];
     
    y=box(3:4);
    Y=[y(2) y(2) y(2) y(2) y(2);
     y(2) y(1) y(1) y(2) y(2);
     y(2) y(1) y(1) y(2) y(2);
     y(2) y(2) y(2) y(2) y(2)];

    z=box(5:6);
    Z=[z(1) z(1) z(1) z(1) z(1);
     z(1) z(1) z(1) z(1) z(1);
     z(2) z(2) z(2) z(2) z(2);
     z(2) z(2) z(2) z(2) z(2)];
endfunction

function [box]=box2box(boxCenter,boxSize)
    box(1:2)=[boxCenter(1)-boxSize(1)/2 boxCenter(1)+boxSize(1)/2];
    box(3:4)=[boxCenter(2)-boxSize(2)/2 boxCenter(2)+boxSize(2)/2];
    box(5:6)=[boxCenter(3)-boxSize(3)/2 boxCenter(3)+boxSize(3)/2];
endfunction

function handle=plotBox(box,colour)
    [X,Y,Z]=box2mat(box);
    plot3d2(X,Y,Z);
    handle=gce();
    handle.color_mode=0; // Transparent facets
    handle.foreground=color(colour);
    handle.thickness=1;
endfunction

function handle=plotBox2(boxCenter,boxSize,colour)
    box=box2box(boxCenter,boxSize);
    handle=plotBox(box,colour);
endfunction

function handle=plotMidBox(box,boxSize,colour)
    boxCenter(1)=box(1)+(box(2)-box(1))/2;
    boxCenter(2)=box(3)+(box(4)-box(3))/2;
    boxCenter(3)=box(5)+(box(6)-box(5))/2;
    handle=plotBox2(boxCenter,boxSize,colour);
endfunction

function updateMidBox(handle,box,boxSize)
    boxCenter(1)=box(1)+(box(2)-box(1))/2;
    boxCenter(2)=box(3)+(box(4)-box(3))/2;
    boxCenter(3)=box(5)+(box(6)-box(5))/2;
    updateBox2(handle,boxCenter,boxSize);
endfunction

function updateBox(handle,box)
    [X,Y,Z]=box2mat(box);
    [XX,YY,ZZ]=nf3d(X,Y,Z); // rebuild facets from corners indices
    handle.data.x=XX;
    handle.data.y=YY;
    handle.data.z=ZZ;
endfunction

function updateBox2(handle,boxCenter,boxSize)
    box=box2box(boxCenter,boxSize);
    updateBox(handle,box);
endfunction
