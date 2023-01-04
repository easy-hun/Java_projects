%%% 201812767 이지훈 과제 2-2 %%%
% P2.m
function P2(x11, y11, x12, y12, x21, y21, x22, y22)

% 첫 번째 직선의 기울기, y절편, 방정식
df1=(y12-y11)/(x12-x11);
t1=y11-df1*x11;
f1 = @(x) df1*x+t1;

% 두 번째 직선의 기울기, y절편, 방정식
df2=(y22-y21)/(x22-x21);
t2=y21-df2*x21;
f2 = @(x) df2*x+t2;

% 두 직선 그래프 출력
hold on;
fplot(f1, 'r');
fplot(f2, 'b');

if (df1==df2)&&(t1==t2)
    fprintf("\n 두 직선이 일치합니다.\n\n");
elseif (df1==df2)
    fprintf("\n 두 직선이 평행합니다.\n\n");
else
    fprintf("\n 두 직선의 교점입니다.\n");
    x=(t2-t1)/(df1-df2);
    fprintf("(%f,%f)\n\n", x, f1(x));
end
