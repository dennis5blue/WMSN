clear;
close all;
name = { '1280*720' };
bar([1928407/(1024*1024) 0 0 0 0 0], 'r','barwidth',0.6,'FaceColor',[0.04,0.14,0.42]);
hold on;
bar([0 1806000/(1024*1024) 0 0 0 0], 'g','barwidth',0.6,'FaceColor',[0.17,0.51,0.34]);
hold on;
bar([0 0 1732867/(1024*1024) 0 0 0], 'c','barwidth',0.6,'FaceColor',[0.75,0.75,0]);
hold on;
bar([0 0 0 1711300/(1024*1024) 0 0], 'b','barwidth',0.6,'FaceColor',[0.75,0.75,0]);
hold on;
bar([0 0 0 0 1623547/(1024*1024) 0], 'b','barwidth',0.6,'FaceColor',[0.75,0.75,0]);
hold on;
bar([0 0 0 0 0 1758165/(1024*1024)], 'b','barwidth',0.6,'FaceColor',[0.75,0.75,0]);
set(gca,'xticklabel',' ');
%set(gcf,'color','none');
%set(gca,'color','none');
ylim([1.2 1.9]);
ylabel(gca,'Total transmission bytes (Mb)');
legend('Independent encoding','MLS','Dominating set (math)','Dominating set (graph)', ...
    'Proposed algorithm', 'Proposed algorithm with interlaced IP frames');
grid on;