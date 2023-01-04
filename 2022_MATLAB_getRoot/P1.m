%%% 201812767 이지훈 과제 2-1 %%%
% P1.m
function P1(a, b, c)

if(b^2-4*a*c==0)
    fprintf("\n- 중근을 가집니다.\n")
    disp(roots([a,b,c]));
elseif(b^2-4*a*c<0)
    fprintf("\n- 두 개의 허근을 가집니다.\n")
    disp(roots([a,b,c]));
else
    fprintf("\n- 두 개의 실근을 가집니다.\n")
    disp(roots([a,b,c]));
end

fplot(@(x) a.*x.^2+b.*x+c);

