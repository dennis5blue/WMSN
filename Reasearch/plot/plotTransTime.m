clear;
close all;
name = { '1280*720' ; '480*360' };
x = [1,2];
%y = [34.5805 30.4015 27.5192 26.5583 21.7841 ; 9.59499 8.00277 7.5858 7.60582 6.28986];
y = [34.5805 30.4015 26.5583 21.7841 ; 9.59499 8.00277 7.60582 6.28986];
bar(x,y)
ylabel(gca,'Total transmission time (ms)');
set(gca,'xticklabel',name);
set(gca,'Box','off');
axesPosition = get(gca,'Position');
%legend('Independent encoding','Greedy','MLP','Proposed algorithm','Minimum required time')
legend('Independent encoding','Greedy','Proposed algorithm','Minimum required time')
grid on;