clear;
close all;
name = { '1280*720' ; '480*360' };
x = [1,2];
y = [34.5805 30.4015 27.5192 26.5583 21.7841 ; 9.59499 8.00277 7.5858 7.60582 6.28986];
bar(x,y)
ylabel(gca,'Total Transmission Time(ms)');
%set(gca, 'ylim', [7000.0 7700.0]);
%set(gca, 'ylim', [40.0 65.0]);
set(gca,'xticklabel',name);
set(gca,'Box','off');
axesPosition = get(gca,'Position');
%title('Transmission Time')
legend('Independent encoding','Greedy','MLP','Proposed algorithm','Minimum required time')
grid on;
%hold on;

%z=[1,2];
%v=[100 200];
%hNewAxes = axes('Position',axesPosition,'Color','none','YLim',[0 100],'YAxisLocation','left','XTick',[],'Box','off');
%ylabel(hNewAxes, 'Improvement');
%set(gca,'yaxislocation','right');
%bar(z,v);