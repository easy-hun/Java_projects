%%% main.m %%%

%%%% 1
fprintf('\n[201812767 이지훈]\n');
P1(2, 5, 9);

%%%% 2
fprintf('\n[201812767 이지훈]\n');
P2(1,-2, 2,1, 2,3, 6,9);

%%%% 3
fprintf('\n[201812767 이지훈]\n');
f = @(m) 2*sqrt(9.81*m)*tanh(2*sqrt(9.81/m))-36;
df = @(m) (981*tanh(2*(981/(100*m))^(1/2)))/(100*((981*m)/100)^(1/2)) + (981*(tanh(2*(981/(100*m))^(1/2))^2 - 1)*((981*m)/100)^(1/2))/(50*m^2*(981/(100*m))^(1/2));
fplot(f, [130,150]);

% 이분법
[root1, err, iter1] = bisection(f, 130, 150, 10^-4);
fprintf(" - 이분법 : root = %3.10f\n\n\n", root1);

% 수정가위치법
[root2, err, iter2] = modifiedfp(f, 130, 150, 10^-4);
fprintf(" - 수정가위치법 : root = %3.10f\n\n\n", root2);

% 고정점 반복법
[root3, iter3] = fixedpoint(f, 140, 10^-4, 100);
fprintf(" - 고정점반복법 : root = %3.10f\n\n\n", root3);

% 뉴튼 랩슨법
[root4, iter4] = newton(f, df, 140, 10^-4, 100);
fprintf(" - 뉴튼랩슨법 : root = %3.10f\n\n\n", root4);

% 할선법
[root5, iter5] = secant(f, 130, 150, 10^-4, 100);
fprintf(" - 할선법 : root = %3.10f\n\n\n", root5);

fprintf("각 알고리즘의 근 =")

syms m;
y=2*sqrt(9.81*m)*tanh(2*sqrt(9.81/m))-36;
diff(y)