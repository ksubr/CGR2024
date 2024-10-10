function o = MyTrapPlot(x, y, f) 

figure(3)
clf
xr = linspace(0,1,200) ;

plot(xr, f(xr), '--b') ;
hold on;
plot(x,y, 'k') 

hold on ;
xst = x(1:end-1); 
xend = x(2:end) ;
zr = zeros(length(xst),1) ;

for i=1:length(xst)
    area([x(i) x(i) x(i+1) x(i+1)], ...
    [0 y(i) y(i+1) 0], ...
    'facecolor', [.2 .5 .2], 'facealpha', .3, ...
    'edgecolor', [1, 1, 1]) ;
end

hold off;

set(gca, 'fontsize', 18);

a = f(xst) ;
b = f(xend) ;
i = (a+b)/2*(x(2)-x(1)) ;
o = sum(i);

axis([0,1,0,Inf])