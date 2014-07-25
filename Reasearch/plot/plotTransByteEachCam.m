clear;
close all;

indep =  [82712 80658 82210 71379 70535 72939 66695 68364 70406 75013 76701 79090 63535 60752 57769 67756 62992 73657 53857 52254 55505 49849 49326 50782 ];

metric = [53145 43439 82197 53947 44959 73011 66695 41969 51482 74757 43190 54443 48746 60934 57905 47843 63088 73720 39257 52104 48475 32039 49326 50829 ];

MLS =    [43439 80658 54135 71379 70535 72939 66695 39887 50180 75013 76701 51319 63535 60752 57378 67756 62992 73657 53857 52254 55505 31839 49326 42555 ];

y = [];
for i = 1:24
    y = [y ; indep(i) MLS(i) metric(i)];
    %y = [y ; indep(i)/1024 metric(i)/1024];
end
x = 0:23;

bar(x,y);
set(gca,'xticklabel');
set(gcf,'color','none');
set(gca,'color','none');
xlim([-0.5 23.5])
%ylim([0.5 1.6]);
xlabel(gca,'Camera index');
ylabel(gca,'Transmission bytes (kb)');
legend('Independent encoding','MLS','Scheduling metric');
grid on;