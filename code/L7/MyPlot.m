function o = MyPlot(x, y, f) 
figure(1)
clf

xr = linspace(0,1,200) ;

plot(xr, f(xr), '--b') ;
hold on;
% plot(x,y, 'k') 


stem(x, y, '.k', 'markersize', .1)
hold off;

set(gca, 'fontsize', 18);
axis([0,1,0,Inf])
o = 0;