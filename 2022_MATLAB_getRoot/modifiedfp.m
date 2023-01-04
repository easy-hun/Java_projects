%%% modifiedfalseposition.m %%%
function [root, err, iter]=modifiedfp(f1, a, b, tolerr, maxiter)
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
    if iter==0
    xm=(xl*f1(xh)-xh*f1(xl))/(f1(xh)-f1(xl));
    end
    
    err=abs(f1(xm));
    iter=iter+1;
    fprintf('%2.0f  %10.4f  %10.4f   %12.6f  %10.6f   %10.6f\n', iter, xl, xh,xm, feval(f1,xm), err)    
    if feval(f1, xl) * feval(f1, xm) < 0
        xh = xm;
        xm=(xl*f1(xh)-xh*f1(xl)/2)/(f1(xh)-f1(xl)/2);
    elseif feval(f1, xm) * feval(f1, xh) < 0
        xl = xm;
        xm=(xl*f1(xh)/2-xh*f1(xl))/(f1(xh)/2-f1(xl));
    else
        err=0;
    end 
    if err <= tolerr || iter >= maxiter, break, end
end
root=xm;