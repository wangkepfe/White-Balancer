data = load('originalRed.txt')

x = data(:,1)
y = data(:,2)

x = log(x)
y = log(y)

X = ones(length(x), 2)
X(:,2) = x

b = inv(X'*X)*X'*y

x = data(:,1)
y = data(:,2)

g = 1/b(2)

ym = y.^g

% plot(x,y,x,X*b)
% title('Linear Regression logGreen - logT')
% xlabel('logT')
% ylabel('logB')

plot(x,ym)
title('Linearized Red - T')
xlabel('T')
ylabel('B^g')

% plot(x,y)
% title('Original Blue - T')
% xlabel('T')
% ylabel('color')