// Set parameters
a = 10;
b = 28;
c = 8/3; 

// Set initial conditions
y0 = 1d-8*[1; 1; 1];
t0 = 0; 

// Set sampling time
Tsampl = 1d-2;
t1 = 50;
t = 0:Tsampl:t1;

// Lorenz equation
function ydot = f(t, y)
ydot(1) = a*(y(2)-y(1));
ydot(2) = y(1)*(b-y(3)) - y(2);
ydot(3) = y(1)*y(2) - c*y(3);
endfunction

y = ode(y0, t0, t, f);

// Animated plot
comet3d(y(1,:),y(2,:),y(3,:))