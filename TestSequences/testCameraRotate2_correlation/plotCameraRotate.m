indep = 57636*ones(1,9);
degree = [0 10 20 30 40 50 60 70 80];
range128 = [198 50727 57700 57736 57720 57750 57740 57787 57722];
range256 = [196 44719 57705 57716 57733 57801 57796 57774 57795];
range512 = [197 44601 52187 57693 57719 57788 57785 57835 57790];

ratio128 = (indep-range128)./indep;
ratio256 = (indep-range256)./indep;
ratio512 = (indep-range512)./indep;

figure(1);
plot(degree,ratio128,'linewidth',2,'color','r');
hold on;
plot(degree,ratio256,'linewidth',2,'color','g');
hold on;
plot(degree,ratio512,'linewidth',2,'color','b');
grid on;
legend('search range = 128','search range = 256','search range = 512');
xlabel('Camera rotation (degree)');
ylabel('Compression ratio');