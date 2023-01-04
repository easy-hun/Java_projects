%%% secant.m %%%
% 할선법
% 도함수 X, 두 점을 지나는 직선과 x축 교점 (초기 두 점 필요)
% vs 뉴튼 : 도함수가 없거나 모르는 경우
% vs 가위치법 : x좌표가 갱신됨, x들의 부호 신경안씀
function [x1, iter] = secant(f, x0, x1, tolerr, maxiter)
iter=0;
u=feval(f,x0);
v=feval(f,x1);
err=abs(x1-x0);
disp('-----------------------------------------------')
disp(' iter xn f(xn) f(xn)-f(xn-1) |xn-xn-1|')
disp('-----------------------------------------------')
fprintf('%2.0f %12.6f %12.6f %12.6f %12.6f\n', iter, x1, v, v-u, err)
while(err>tolerr)&&(iter<=maxiter)&&(v-u~=0)
    x=x1-v*((x1-x0)/(v-u));
    x0 = x1;
    u = v;
    x1 =x;
    v=feval(f,x1);
    err=abs(x1-x0); 
    iter=iter+1;
    fprintf('%2.0f %12.6f %12.6f %12.6f %12.6f\n', iter, x1, v, v-u, err)
end