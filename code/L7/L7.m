
 % f = @(x) x.^2 ; % f(x) = x^2
% f = @(x) x.^5 ; % f(x) = x^5
 f = @(x) sin(x*pi) ; 

refInt = integral(f,0,1);
display(['integral of f(x) in [0,1] is ' num2str(refInt) ]) ;

err = [] ;
Ns = [10 100 1000 10000] ;
for i=1:length(Ns)
    n = Ns(i) ;
    x = linspace(0,1,n) ;
    avg = mean(f(x)) ;
    % display(['average of f(x) is ' num2str(avg) ]) ;
    
    y=f(x) ;
    % MyPlot(x,y, f) ;
    
    w=x(2)-x(1) ;
    rcentres = x+w/2 ;
    rcentres(end) = [] ;
    boxInt = sum(w*f(rcentres)) ;
    % display(['rectangular estimate of int of f(x) is ' num2str(boxInt) ]) ;
    
    % MyBoxPlot(x,y,f); 
    
    xstart = x;
    xstart(end) = [] ;
    xend = xstart + w;
    trapInt = sum(w*(f(xstart)+f(xend))/2); 
    % display(['trapezoidal estimate of int of f(x) is ' num2str(trapInt) ]) ;
    
    % MyTrapPlot(x,y,f); 

    err(i,:) = [avg-refInt, boxInt-refInt, trapInt-refInt].^2 ;
end

clf; 
hold on
for k=1:size(err,2)
    plot(Ns, err(:,k), 'o-' );
end
set(gca, 'xscale', 'log') ;
set(gca, 'yscale', 'log') ;
hold off
legend({'avg', 'rec', 'trap'});
