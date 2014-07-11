clear;
close all;
indepBits = 1928407;

%DSk1 = [1750584 1719049 1718738 1746524 1764679 ...
%        1761940 1737807 1728894 1714332 1717130];
%DSk2 = [1745383 1729150 1749820 1777905 1747906 ...
%        1756602 1772214 1745731 1742641 1760596];
%DSk3 = [1786357 1693237 1786568 1735921 1733557 ...
%        1737140 1740269 1774170 1772403 1726872];
%DSk4 = [1736623 1799625 1721553 1720608 1731661 ...
%        1760969 1776667 1763519 1748650 1794719];
%DSk5 = [1691077 1772938 1768045 1737891 1740287 ...
%        1789106 1735188 1753471 1706234 1795443];

DSk1 = 1736200;
DSk2 = 1711300;
DSk3 = 1727200;
DSk4 = 1730300;
DSk5 = 1754400;
DSk6 = 1753500;
DSk7 = 1775400;

fg = 1;
figure(fg);
OverlappedTime = [1 2 3 4 5 6 7];
improveRatio = zeros(2,7);
improveRatio(1,:) = [0.0913 0.1014 0.0935 0.0717 0.0613 0.0637 0.0569];
for i=1:7
    eval(['improveRatio(2,' num2str(i) ')=(indepBits-DSk' num2str(i) ')/indepBits;']);
end
ln(1) = line(OverlappedTime(:), 100*improveRatio(1,:),'Marker','o','LineWidth',2,'MarkerFaceColor','none','MarkerSize',8,'color','r');
ln(2) = line(OverlappedTime(:), 100*improveRatio(2,:),'Marker','o','LineWidth',2,'MarkerFaceColor','none','MarkerSize',8,'color','b');
%end
%set(gca, 'YLim', [0.8 1.2]);
xlabel('Overlapped times (k)','FontSize',13,'Color','k');
ylabel('Improvement ratio (%)','FontSize',13,'Color','k');
legend('Mathematic solution','Graph algorithm','location','NorthEast');
set(gca,'fontsize',13);
grid on;
box on;