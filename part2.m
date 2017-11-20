data = load('whiteWorldSpecRemoved.txt');   

styles = ['.','+','x','o','s'];
color = ['k','c','y','m'];

for i = 0:4
    for j = 0:3
        for k = 1:5
            plot(data(i * 5 + k, j * 2 + 1), data(i * 5 + k, j * 2 + 2), strcat(styles(i+1), color(j+1)))
            hold on
        end
    end
end

title('White World Specularities Removed')
xlabel('R/(R+G+B)')
ylabel('G/(R+G+B)')

hold off


