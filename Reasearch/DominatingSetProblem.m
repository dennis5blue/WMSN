correlation =load('./Topology/paper720_30cam_LPInput.txt');
Capacity = [1.86313e+06 1.86313e+06 2.06955e+06 1.86313e+06 1.86313e+06 ...
    2.06955e+06 113231 113231 110986 113231 113231 110986 3.6668e+06 ...
    3.6668e+06 3.02487e+06 3.6668e+06 3.6668e+06 3.02487e+06 3.6668e+06 ...
    3.6668e+06 3.02487e+06 3.6668e+06 3.6668e+06 3.02487e+06 1.09184e+06 ...
    714248 257083 2.82371e+06 899747 1.09579e+07];
cameraNum = 30;
indepByte = zeros(1,cameraNum);
adjacency = ones(cameraNum,cameraNum);
magicNum = 2; %How many times a camera should be overlapped by the dominating set

for r = 1:cameraNum
    indepByte(1,r) = correlation(r,r);
    for c = 1:cameraNum
        if correlation(r,c) == -1
            correlation(r,c) = correlation(r,r);
            adjacency(r,c) = 0;
        end
    end
end

%---Objective---%  Objective function is the amount of encoded bits
f = zeros(cameraNum,1);
for i = 1:cameraNum
    f(i) = sum(correlation(:,i));
end

%---Bounds---%
lb = zeros(cameraNum,1);
ub = ones(cameraNum,1);

%---Inequalities---%
A = -adjacency; %select less than k independent transmitters 
b = -magicNum*ones(cameraNum,1);

%---Not used---%
Aeq = zeros(1,cameraNum);

x = linprog(f,A,b,Aeq,0,lb,ub);
RecordByte = [];
for avetime = 1:1
    %Approximation Algorithm for MLS
    for cam=1:cameraNum
        xBinary(cam) = binornd(1,x(cam));
    end
    IframeTx = find(xBinary==1);
    cTemp = correlation';
    for n=1:length(IframeTx)
        TxByteMatrix(n,:) = cTemp(IframeTx(n),:);
    end
    
    reqByte = 0;
    for m=1:cameraNum
        if xBinary(m)==1
            reqByte = reqByte + correlation(m,m);
        elseif xBinary(m)==0
            reqByte = reqByte + min(TxByteMatrix(:,m),[],1);
        end
    end
    RecordByte = [RecordByte sum(reqByte)];
end %end average

IndepTransByte = 0;
for cal=1:cameraNum
    IndepTransByte = IndepTransByte + correlation(cal,cal);
end

IndepTransByte;
averageOverTransByte = sum(RecordByte)/length(RecordByte);
ImproveRatio = (1928407-averageOverTransByte)/1928407

% start plotting
name = { '1280*720' };
bar([1928407/(1024*1024) 0 0 0 0], 'r','barwidth',0.6,'FaceColor',[0.04,0.14,0.42]);
hold on;
bar([0 1806000/(1024*1024) 0 0 0], 'g','barwidth',0.6,'FaceColor',[0.17,0.51,0.34]);
hold on;
bar([0 0 averageOverTransByte/(1024*1024) 0 0], 'c','barwidth',0.6,'FaceColor',[0.75,0.75,0]);
hold on;
bar([0 0 0 1616870/(1024*1024) 0], 'b','barwidth',0.6,'FaceColor',[0.75,0.75,0]);
hold on;
bar([0 0 0 0 1415236/(1024*1024)], 'y','barwidth',0.6,'FaceColor',[0.85,0.16,0]);
set(gca,'xticklabel',' ');
%set(gcf,'color','none');
%set(gca,'color','none');
ylim([1 1.9]);
ylabel(gca,'Total transmission bytes (Mb)');
legend('Independent encoding','MLS','Minimum dominating set','Scheduling metric','Lower bound')
grid on;
