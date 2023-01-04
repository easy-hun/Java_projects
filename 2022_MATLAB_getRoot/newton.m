%%% newton.m %%%
% 뉴튼-랩슨 방법
% x=a에서 접선의방정식과 x축의 교점을 반복해서 구하기
function [x0, iter] = newton(f, df, x0, tolerr, maxiter)
iter=0;
u=feval(f,x0);
v=feval(df,x0);
err=abs(feval(f,x0));
disp('-----------------------------------------------')
disp(' iter      x      f(x)      df(x)    |xn+1-xn|')
disp('-----------------------------------------------')
fprintf('%2.0f  %12.6f   %12.6f  %12.6f\n', iter, x0, u,v)
while(err>tolerr)&&(iter<=maxiter)&&(v~=0)
    x1=x0-u/v;
    err=abs(x1-x0);
    x0=x1;
    u=feval(f,x0);
    v=feval(df,x0);
    iter=iter+1;
    fprintf('%2.0f  %12.6f   %12.6f  %12.6f  %12.6f\n', iter, x0, u,v,err)
end
if(v==0)
    disp('division by zero')
end
if(iter>maxiter)
    disp('Method failed to converge')
end
