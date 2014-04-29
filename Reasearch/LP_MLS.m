correlation3 =load('./Topology/paper720_LPInput.txt');
Capacity = [1.86313e+06 1.86313e+06 2.06955e+06 1.86313e+06 1.86313e+06 ...
    2.06955e+06 113231 113231 110986 113231 113231 110986 3.6668e+06  ...
    3.6668e+06 3.02487e+06 3.6668e+06 3.6668e+06 3.02487e+06 3.6668e+06 ...
    3.6668e+06 3.02487e+06 3.6668e+06 3.6668e+06 3.02487e+06];
cameraNum = 24;


for r = 1:cameraNum
    timeRequired(r,:) = correlation3(r,:)/Capacity(r);
    for ch = 1:cameraNum
        if timeRequired(r,ch) < 0
            timeRequired(r,ch) = inf;
        end
    end
end
cameraNum = length(correlation3(:,1));

%---Objective---%
f = zeros(cameraNum*(cameraNum+1)+1,1);
f(cameraNum*(cameraNum+1)+1,1)=1;

%---Bounds---%
lb=zeros(cameraNum*(cameraNum+1)+1,1);
lb(cameraNum*(cameraNum+1)+1,1) = -inf;
ub=ones(cameraNum*(cameraNum+1)+1,1);
ub(cameraNum*(cameraNum+1)+1,1) = inf;

%---Inequalities---%
A = zeros(cameraNum*(cameraNum+1)+cameraNum,cameraNum*(cameraNum+1)+1);
b = zeros(cameraNum*(cameraNum+1)+cameraNum,1);
%Each camera has at least one indep camera to overhear
for k=1:cameraNum
    A(k,correlation3(k,:)>0)= -1;
    b(k) = -1;
end
%v_j must indep. sent before v_i can overhear v_j
for j=1:cameraNum
    for i=1:cameraNum
        A(j*cameraNum+i,j*cameraNum+i) = 1;
        A(j*cameraNum+i,j) = -1;
    end
end
%Transmisssion time constraint y_{qp}*H(X_p|X_q)/C_{p0} - z < 0
for p=1:cameraNum
    temp_p = [];
    temp_p = find(correlation3(p,:)>0);
    for n=1:length(temp_p)
        q=temp_p(n);
        A(cameraNum*(cameraNum+1)+p,q*cameraNum+p) = correlation3(p,q)/Capacity(p);
    end
    A(cameraNum*(cameraNum+1)+p,cameraNum*(cameraNum+1)+1) = -1; % -z
end

%---Equalities---%
Aeq = zeros(2*cameraNum,cameraNum*(cameraNum+1)+1);
beq = zeros(2*cameraNum,1);
%Each camera overhear only once
for ii=1:cameraNum
    temp = [];
    temp = find(correlation3(ii,:)>0);
    for kk=1:length(temp)
        jj=temp(kk);
        Aeq(ii,jj*cameraNum+ii) = 1;
    end
    beq(ii)=1;
end
%send indep. = overhear itself
for m=1:cameraNum
    Aeq(cameraNum+m,m*cameraNum+m) = 1;
    Aeq(cameraNum+m,m) = -1;
end

% optx(1:24) is x optimal
% optx(25:48) is y_{1,1:24} optimal ...etc
[optx fval] = linprog(f,A,b,Aeq,beq,lb,ub);
X = optx(1:cameraNum);
for r=1:cameraNum
    for s=1:cameraNum
        Y(r,s) = optx(r*cameraNum+s);
    end
end

RecordImproveRatio = [];
RecordTime = [];
for avetime = 1:100
    %Approximation Algorithm for MLS
    for cam=1:cameraNum
        Xbinary(cam) = binornd(1,X(cam));
    end
    %Xbinary

    Ybinary = zeros(cameraNum,cameraNum);
    camIndep = find(Xbinary==1);
    for g=1:length(camIndep)
        Ybinary(camIndep(g),camIndep(g))=1;
    end
    camOver = find(Xbinary==0);
    for f=1:length(camOver)
        targetCam = camOver(f);
        [Cs Cp] = sort(timeRequired(targetCam,:),'ascend'); %[CameraSize CameraPosition]
        Ybinary(Cp(1),targetCam) = 1;
    end

    %calculate total transmisssion time
    originalTime = 0;
    totalTime = 0;
    for cal=1:cameraNum
        totalTime = totalTime+ timeRequired(find(Ybinary(:,cal)==1),cal);
        originalTime = originalTime + timeRequired(cal,cal);
    end
    ImproveRatio = (originalTime - totalTime) / originalTime;
    RecordTime = [RecordTime totalTime];
    RecordImproveRatio = [RecordImproveRatio ImproveRatio];
end %end average

IndepTransTime = originalTime
averageOverTransTime = sum(RecordTime)/length(RecordTime)
averageImprovement = sum(RecordImproveRatio)/length(RecordImproveRatio)