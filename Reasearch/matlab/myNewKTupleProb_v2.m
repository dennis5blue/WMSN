improvementRatio = zeros(1,20);
for howManyTuple = 1:20
    
magicCompressionRatio = 0.7;
useLP = 1;
corrMatrix = load('../Topology/city2000_res720_cam100_corrMatrix.txt');
indepByte = load('../Topology/city2000_res720_cam100_indepByte.txt');
cameraPos = load('../Topology/city2000_res720_cam100_pos.txt');
cameraNum = length(indepByte);
capacityMatrix = zeros(cameraNum,cameraNum);
%calculate the capacityMatrix
% -----------------------
% | C_10  C_12 ... C_1N |
% | C_21  C_20 ... C_2N |
% |   .     .        .  |
% |   .     .        .  |
% |   .     .        .  |
% | C_N1  C_N2 ... C_N0 |
% -----------------------
% diagonal element is capacity to aggregator
for i=1:cameraNum
    for j=1:cameraNum
        if i == j
            capacityMatrix(i,i) = CalChannelGainToBS(cameraPos(i,1),cameraPos(i,2));
        else
            capacityMatrix(i,j) = CalChannelGainBetweenCameras(cameraPos(i,1),cameraPos(i,2), ...
                cameraPos(j,1),cameraPos(j,2));
        end
    end
end

% Start to solve binary integer programming problem
%                    ------         ------                -------
%             H(X_1)-H(X_1)  H(X_2)-H(X_2)       H(X_100)-H(X_100)
% F_200*1 = [ -------------  -------------  ...  ----------------- 0 0 ... 0 ] 
%                  C_1            C_2                  C_100    
%  ------
%  H(X_i) means average conditional entropy of camera i ,conditioned on all
%  the cameras that camera i can overhear (not include camera i)
%
% B = [ b_1 b_2 ... b_100 b_1 b_2 ... b_100]^T
%
%       -----------------------
%       |   1   a_12 ... C_1N |
%       | a_21    1  ... C_2N |
%       |   .     .        .  |
% A  =  |   .     .        .  |   a_{ij} = 1 means i can overhear j 
%       |   .     .        .  |
%       | a_N1  a_N2 ...   1  |
%       -----------------------
%
%       ----------------------------------
%       | 2*H(X_1)  H(X_2)  ...  H(X_N)  |
%       |  H(X_1)  2*H(X_2) ...  H(X_N)  |
%       |    .        .             .    |
% H  =  |    .        .             .    |    
%       |    .        .             .    |
%       |  H(X_1)   H(X_2)  ... 2*H(X_N) |
%       ----------------------------------
%
%           ---------------------------
%           |                         |
%           |     -A            0     |
%           |                         |
% AandH  =  |                         |    
%           |      0            H     |
%           |                         |
%           ---------------------------
%
% Optimization problem is as follows
% minimize      F*B
%   s.t.        AandH*B <= KandH (componentwisely) 
%               b_i = {0,1}

% Obtain the adjacency matrix
A = zeros(cameraNum,cameraNum);
for i=1:cameraNum
    for j=1:cameraNum
        if i == j
            A(i,i) = 0;
        elseif capacityMatrix(j,i) > capacityMatrix(j,j)
            A(i,j) = 1;
        end
    end
end

% Obtain AandH
AandH = zeros(cameraNum+1,2*cameraNum);
for i=1:(cameraNum+1)
    for j=1:2*cameraNum
        if i<=cameraNum && j<=cameraNum
            AandH(i,j) = -A(i,j);
        elseif i>cameraNum && j>cameraNum
            AandH(i,j) = -indepByte(j-cameraNum);
        end
    end
end            

% Initialize F
Htemp = [indepByte' zeros(1,cameraNum)];
Hbar = zeros(1,2*cameraNum);
for i=1:cameraNum
    htemp = 0;
    canHearCamera = find(A(i,:)==1);
    for j=1:length(canHearCamera)
        htemp = htemp + corrMatrix(i,canHearCamera(j));
    end
    Hbar(i) = htemp/length(canHearCamera);
end
for i=1:cameraNum
    Htemp(i) = Htemp(i)/capacityMatrix(i,i);
    Hbar(i) = Hbar(i)/capacityMatrix(i,i);
end
F = Htemp - Hbar;

% Initialize K
K = howManyTuple*ones(cameraNum,1);

% Obtain KandH
KandH = zeros(cameraNum+1,1);
for i=1:(cameraNum+1)
    if i<=cameraNum
        KandH(i) = -K(i);
    else
        KandH(i) = -sum(indepByte)*magicCompressionRatio;
    end
end

% Equality constraint (since we wirte B multiple times)
Aeq = zeros(2*cameraNum,2*cameraNum);
for i=1:cameraNum
    Aeq(i,i) = 1;
    Aeq(i,cameraNum+i) = -1;
end
beq = zeros(2*cameraNum,1);

% Used for LP solver
lb = zeros(2*cameraNum,1);
ub = ones(2*cameraNum,1);

if useLP == 0
    % Solve the binary integer programming problem
    B = bintprog(F,AandH,KandH,Aeq,beq);
end

if useLP == 1
    B = linprog(F,AandH,KandH,Aeq,beq,lb,ub);
end

%%%%% Start to calculate total transmission time
IframeTransmitter = zeros(1,cameraNum);
for i=1:cameraNum
    IframeTransmitter(i) = binornd(1,B(i));
end
indepTransTime = zeros(1,cameraNum);
transTime = zeros(1,cameraNum);
corrMatrix2 = corrMatrix + eye(cameraNum)*max(indepByte);
for i=1:cameraNum
    indepTransTime(i) = indepByte(i)/capacityMatrix(i,i);
    if IframeTransmitter(i)==1
        transTime(i) = indepByte(i)/capacityMatrix(i,i);
    elseif IframeTransmitter(i) == 0
        transTime(i) = min(corrMatrix2(i,:))/capacityMatrix(i,i);
    end
end

totalIndepTime = sum(indepTransTime)
totalOverTime = sum(transTime)
improvementRatio(howManyTuple) = (totalIndepTime-totalOverTime)/totalIndepTime

end