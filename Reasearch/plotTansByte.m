clear;
close all;
name = { '1280*720' };
%x = [1 2];
%y = [1594736/(1024*1024) 1405764/(1024*1024) 1308490/(1024*1024) 1087365/(1024*1024); 0 0 0 0];
%bar(x,y);
bar([1594736/(1024*1024) 0 0 0], 'r','barwidth',0.6,'FaceColor',[0.04,0.14,0.42]);
hold on;
bar([0 1379700/(1024*1024) 0 0], 'g','barwidth',0.6,'FaceColor',[0.17,0.51,0.34]);
hold on;
bar([0 0 1308490/(1024*1024) 0], 'b','barwidth',0.6,'FaceColor',[0.75,0.75,0]);
hold on;
bar([0 0 0 1087365/(1024*1024)], 'y','barwidth',0.6,'FaceColor',[0.85,0.16,0]);
%set(gca,'xticklabel',{'Independent encoding','Greedy','Proposed algorithm','Minimum required time'});
set(gca,'xticklabel',' ');
set(gcf,'color','none');
set(gca,'color','none');
ylim([0.5 1.6]);
ylabel(gca,'Total transmission bytes (Mb)');
legend('Independent encoding','MLS','Proposed algorithm','Lower bound')
grid on;