clear;

r = .4 ;
c = [.5, .5];

% visualise circle
figure(1)
clf
viscircles(c,r, 'Color', 'blue') ;
axis([0,1,0,1]) ;
hold on; % start overlaying plots

rep =100000 ;

tic
for i=1:rep
    % draw random samples 
    N = 1000 ; 
    x = rand(N,2) ;
    % scatter(x(:,1), x(:,2))
    
    % check how many lie inside the circle
    dxc = vecnorm((x-c)');
    inside = find(dxc<r) ;
    n = length(inside) ;
    
    % estimate pi
    estPi(i) = n/N*1/r^2 ; 
end
toc
mean(estPi)


hold off; % end overlaying plots

histogram(estPi)









































%%










clear;

r = .4 ;
c = [.5, .5];

clf
figure(1)
viscircles(c,r, 'Color', 'blue') ;
axis([0,1,0,1]) ;
hold on; 

N = 10000 ;
rep = 10000; 


for i=1:rep
    
    x = rand(N,2) ;
    dxc = vecnorm((x-c)'); 
    inside = find(dxc<=r) ;
    ninside = length(inside) ;
    estArea = ninside/N ;
    
    estPi(i) = estArea/r^2 ;
    % scatter(x(:,1), x(:,2))
end

figure(2)
histogram(estPi, 100) ;

mean(estPi)

