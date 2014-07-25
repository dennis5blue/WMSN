clear;
close all;
fg = 1;
figure(fg);
OverlappedTime = [1 2 3 4 5 6 7];
improveRatio = [0.0913 0.1014 0.0935 0.0717 0.0613 0.0637 0.0569];
ln(1) = line(OverlappedTime(:), improveRatio(1,:),'Marker','o','LineWidth',2,'MarkerFaceColor','none','MarkerSize',8,'color','r');
%end
%set(gca, 'YLim', [0.8 1.2]);
xlabel('Multiplicity (k)','FontSize',13,'Color','k');
ylabel('Improvement ratio','FontSize',13,'Color','k');
set(gca,'fontsize',13);
grid on;
box on;