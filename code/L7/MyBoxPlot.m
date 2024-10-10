function o = MyBoxPlot(x, y, f) 
w = (x(2) - x(1)) ;
x2 = x + w/2 ;
x2(end) = [] ;
y2 = f(x2) ;

figure(2)
clf
xr = linspace(0,1,200) ;

plot(xr, f(xr), '--b') ;
hold on;
plot(x,y, 'k') 

hold on ;

bar(x2,y2,1, 'facecolor', [.78 .3 .5], ...
        'facealpha', .4, 'edgecolor', [1 1 1]) ;

plot(x2,y2, 'or') ;    
hold off;

set(gca, 'fontsize', 18);
axis([0,1,0,Inf])
o = sum(w*y2);

