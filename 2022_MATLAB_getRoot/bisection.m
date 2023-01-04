%%% bisection.m %%%
function [root, err, iter]=bisection(f1, a, b, tolerr, maxiter)
xl = a;
xh = b;
if nargin <3, error('insufficient arguments'), end
test = feval(f1, xl) * feval(f1,xh);
if test > 0, error('no sign change'), end
 
if nargin < 5, maxiter=100;  end
if nargin <4, tolerr=0.001;  end
 
fprintf('\n')
disp('-----------------------------------------------------------------')
disp(' iter      xl         xh          xm         f(xm)         err ')
disp('-----------------------------------------------------------------')
 
iter = 0;
while (1)    
    xm=(xl+xh)/2;
    err=abs((xl-xh)*0.5);
    iter=iter+1;
    fprintf('%2.0f  %10.4f  %10.4f   %12.6f  %10.6f   %10.6f\n', iter, xl, xh,xm, feval(f1,xm), err)    
    if feval(f1, xl) * feval(f1, xm) < 0
        xh = xm;
    elseif feval(f1, xm) * feval(f1, xh) < 0
        xl = xm;
    else
        err=0;
    end 
    if err <= tolerr || iter >= maxiter, break, end
end
root=xm;

