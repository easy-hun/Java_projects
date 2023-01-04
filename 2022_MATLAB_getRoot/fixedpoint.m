%%% fixedpoint.m %%%
% 고정법 반복법
% [a,b]에서 y값도 [a,b]사이고, 기울기 절대값 1 이하
function [root, iter]=fixedpoint(g,x0,tolerr,maxiter)
iter=0;
gx=feval(g,x0);
err=abs(gx-x0);
disp('------------------------------------------')
disp(' iter x g(x) |xn+1-xn|')
disp('------------------------------------------')
fprintf('%2.0f %12.6f %12.6f %12.6f\n', iter, x0, gx, err)
while(err>tolerr)&&(iter<=maxiter)
x0 = gx;
gx=feval(g,gx); 
err=abs(gx-x0); 
iter=iter+1;
fprintf('%2.0f %12.6f %12.6f %12.8f\n', iter, x0, gx, err)
end
if(iter>maxiter)
disp('Method failed to converge')
end
root=x0