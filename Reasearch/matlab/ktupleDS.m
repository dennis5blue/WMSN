%HARD CODE!!!!!
clear;
clc;
correlation =load('./Topology/paper720_30cam_LPInput.txt');
Capacity = [1.86313e+06 1.86313e+06 2.06955e+06 1.86313e+06 1.86313e+06 ...
    2.06955e+06 113231 113231 110986 113231 113231 110986 3.6668e+06 ...
    3.6668e+06 3.02487e+06 3.6668e+06 3.6668e+06 3.02487e+06 3.6668e+06 ...
    3.6668e+06 3.02487e+06 3.6668e+06 3.6668e+06 3.02487e+06 1.09184e+06 ...
    714248 257083 2.82371e+06 899747 1.09579e+07];
cameraNum = 30;
indepByte = zeros(1,cameraNum);
adjacency = ones(cameraNum,cameraNum);
magick = 7; %k-tuple dominating set
alpha = 0.6; %weighting factor for MIS generation

for r = 1:cameraNum
    indepByte(1,r) = correlation(r,r);
    for c = 1:cameraNum
        if correlation(r,c) == -1
            correlation(r,c) = correlation(r,r);
            adjacency(r,c) = 0;
        end
    end
end

v1 = find(adjacency(:,1) ==1)';
v2 = find(adjacency(:,2) ==1)';
v3 = find(adjacency(:,3) ==1)';
v4 = find(adjacency(:,4) ==1)';
v5 = find(adjacency(:,5) ==1)';
v6 = find(adjacency(:,6) ==1)';
v7 = find(adjacency(:,7) ==1)';
v8 = find(adjacency(:,8) ==1)';
v9 = find(adjacency(:,9) ==1)';
v10 = find(adjacency(:,10) ==1)';
v11 = find(adjacency(:,11) ==1)';
v12 = find(adjacency(:,12) ==1)';
v13 = find(adjacency(:,13) ==1)';
v14 = find(adjacency(:,14) ==1)';
v15 = find(adjacency(:,15) ==1)';
v16 = find(adjacency(:,16) ==1)';
v17 = find(adjacency(:,17) ==1)';
v18 = find(adjacency(:,18) ==1)';
v19 = find(adjacency(:,19) ==1)';
v20 = find(adjacency(:,20) ==1)';
v21 = find(adjacency(:,21) ==1)';
v22 = find(adjacency(:,22) ==1)';
v23 = find(adjacency(:,23) ==1)';
v24 = find(adjacency(:,24) ==1)';
v25 = find(adjacency(:,25) ==1)';
v26 = find(adjacency(:,26) ==1)';
v27 = find(adjacency(:,27) ==1)';
v28 = find(adjacency(:,28) ==1)';
v29 = find(adjacency(:,29) ==1)';
v30 = find(adjacency(:,30) ==1)';

recordTxBit = [];
for aveTime = 1:20

%-----------------------------------------------%
%MIS generation (MIS is always a dominating set)%
%-----------------------------------------------%

%Initial degree of each nodes
degree = zeros(1,cameraNum);
for i=1:cameraNum
    eval(['degree(' num2str(i) ') = length(v' num2str(i) ');'])
end
%Find the 1st node to be added in MIS
[dN dI] = sort(degree, 'ascend');
threshold = dN(1)*(1+alpha);
RCL = find(dN <= threshold);
candidate = randperm(length(RCL));
camAdd = dI(candidate(1));
MIS = [camAdd];
nodeLeft = [1:cameraNum];
nodeAlreadyRm = [];
MIScounter = 0;

while length(nodeLeft) > 0
    eval(['nodeToRemove = v' num2str(camAdd) ';']);
    nodeAlreadyRm = [nodeAlreadyRm nodeToRemove];
    nodeLeft = [];
    %find the node left after putting camAdd into the MIS
    for i=1:cameraNum
        leftIndicator = 1;
        for j=1:length(nodeAlreadyRm)
            if i == nodeAlreadyRm(j)
                leftIndicator = 0;
            end
        end
        if leftIndicator == 1
            nodeLeft = [nodeLeft i];
        end
    end
    
    %need to remove camAdd and other nodes connected with camAdd
    for i=1:length(nodeLeft)
        cam = nodeLeft(i);
        eval(['domCam = v' num2str(cam) ';'])
        tempList = [];
        for j=1:length(domCam)
            for n=1:length(nodeLeft)
                if domCam(j) == nodeLeft(n)
                    tempList = [tempList domCam(j)];
                end
            end
        end
        eval(['vAdaptive' num2str(cam) '= tempList;'])
    end
    
    %Run the algorithm
    degreeAdaptive = zeros(1,length(nodeLeft));
    for i=1:length(nodeLeft)
        eval(['degreeAdaptive(' num2str(i) ') = length(vAdaptive' num2str(nodeLeft(i)) ');'])
    end
    [dNAdaptive dIAdaptive] = sort(degreeAdaptive, 'ascend');
    if length(dNAdaptive)>0
        threshold = dNAdaptive(1)*(1+alpha);
        RCLAdaptive = find(dNAdaptive <= threshold);
        candidateAdaptive = randperm(length(RCLAdaptive));
        camAdd = dIAdaptive(candidateAdaptive(1));
        MIS = [MIS camAdd];
    end
    MIScounter = MIScounter + 1;
    if MIScounter == 15
        nodeLeft = [];
    end
end

%-------------------------------------%
%We now have MIS and going to run ICGA%
%-------------------------------------%
DSk = MIS; %Dk is the k-tuple dominating set
dominateOther = zeros(1,cameraNum);
for i=1:cameraNum
    for j=1:cameraNum
        dominateOther(i) = dominateOther(i) + adjacency(j,i);
    end
end

%Start ICGA
jumpOut = 0;
while jumpOut == 0
    %calculate domination of each node
    domination = zeros(1,cameraNum);
    for i=1:cameraNum
        for j=1:length(DSk)
            canWeAdd = 1;
            for p=1:j-1
                if DSk(j) == DSk (p)
                    canWeAdd = 0;
                end
            end
            if canWeAdd == 1
                domination(i) = domination(i)+adjacency(i,DSk(j));
            end
        end
    end
    %domination
    F = find(domination < magick);
    if length(F) > 0
        FdominateOther = zeros(1,length(F));
        for i=1:length(F)
            FdominateOther(i) = dominateOther(F(i));
        end
        [FN FI] = sort(FdominateOther,'descend');
        %F
        %FI
        if length(F) > 2
            threshold2 = FN(1);
            chooseMe = find(FN <= threshold2);
            candidate2 = randperm(length(chooseMe));
            camAdd = F(FI(candidate2(1)));
            DSk = [DSk camAdd];
        else
            candidate2 = randperm(cameraNum);
            camAdd = candidate2(1);
            DSk = [DSk camAdd];
        end
    end
    if length(F) == 0
        jumpOut = 1;
    end
end

%DSk; %DSk is the k-tuple dominating set

%Calculate the encoded bits
IframeTx = [DSk(1)];
xBinary = zeros(1,cameraNum);
xBinary(DSk(1)) = 1;
for i=2:length(DSk)
    duplicate = 0;
    for j=1:length(IframeTx)
        if DSk(i) == IframeTx(j)
            duplicate = 1;
        end
    end
    if duplicate == 0
        IframeTx = [IframeTx DSk(i)];
        xBinary(DSk(i)) = 1;
    end
end

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

recordTxBit = [recordTxBit reqByte];
end % end for average

aveBit = sum(recordTxBit)/length(recordTxBit)