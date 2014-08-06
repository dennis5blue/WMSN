clear;
close all;
fg = 1;
figure(fg);
OverlappedTime = [1:20];
improveRatio1 = [0.165178821018483,0.162814020882552,0.159875927220470,0.154711585952529,0.150969280409869,0.143973942765065,0.135552879619112,0.128153652523320,0.118808098791273,0.342574794882254,0,0,0,0,0,0,0,0,0,0];
improveRatio4 = [0.159239294066381,0.158631449234239,0.157949110442474,0.155195177344010,0.151831738320904,0.143700895669280,0.135439394154870,0.128145677301131,0.118807803413068,0.342574794882254,0,0,0,0,0,0,0,0,0,0];
ln(1) = line(OverlappedTime(:), improveRatio1(1,:),'Marker','o','LineWidth',2,'MarkerFaceColor','none','MarkerSize',8,'color','r');
ln(4) = line(OverlappedTime(:), improveRatio4(1,:),'Marker','o','LineWidth',2,'MarkerFaceColor','none','MarkerSize',8,'color','b');
%end
%set(gca, 'YLim', [0.8 1.2]);
xlabel('Multiplicity (k)','FontSize',13,'Color','k');
ylabel('Improvement ratio','FontSize',13,'Color','k');
set(gca,'fontsize',13);
grid on;
box on;