// From http://www.sky-engin.jp/en/ScilabAnimation/chap03/chap03.html
// animation_point.sce

clear; xdel(winsid());

// Create data
t = 0:0.005:1;    // Time data
x = sin(2*%pi*t); // Position data

y=cos(2*%pi*t);

// Draw initial figure
figure(1);

plot(x(1),0,'o');
h_compound = gce();

xpoly(t(1:40),y(1:40));
test=gce();

h_compound.children.mark_size = [5,1];
h_compound.children.mark_background = 3;

h_axes = gca();
h_axes.data_bounds = [-1.5,-1.5;1.5,1.5];

// Animation Loop
i = 1;
while i<=length(x)
    drawlater();
    h_compound.children.data = [x(i) 0];
    j=i+10;
    if j>size(t) then
        j=0;
    end
    test.data=[t(i:j)',y(i:j)'];
    drawnow();
    i = i+1;
    sleep(50);
end