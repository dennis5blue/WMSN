clear;
close all;
name = { '1280*720' };
bar([2072590/60000 0 0 0], 'r','barwidth',0.6,'FaceColor',[0.04,0.14,0.42]);
hold on;
bar([0 1825350/60000 0 0], 'g','barwidth',0.6,'FaceColor',[0.17,0.51,0.34]);
hold on;
bar([0 0 1788990/60000 0], 'b','barwidth',0.6,'FaceColor',[0.75,0.75,0]);
hold on;
bar([0 0 0 1730100/60000], 'b','barwidth',0.6,'FaceColor',[0.75,0.75,0]);
set(gca,'xticklabel',' ');
%set(gcf,'color','none');
%set(gca,'color','none');
ylim([15.0 35.0]);
ylabel(gca,'Total transmission time (min)','FontSize',13);
legend('Independent coding','Overhear one camera before','Overhear the best camera','Minumum transmission time');
grid on;