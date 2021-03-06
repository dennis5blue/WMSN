correlation =load('./Topology/paper720_30cam_LPInput.txt');
Capacity = [1.86313e+06 1.86313e+06 2.06955e+06 1.86313e+06 1.86313e+06 ...
    2.06955e+06 113231 113231 110986 113231 113231 110986 3.6668e+06 ...
    3.6668e+06 3.02487e+06 3.6668e+06 3.6668e+06 3.02487e+06 3.6668e+06 ...
    3.6668e+06 3.02487e+06 3.6668e+06 3.6668e+06 3.02487e+06 1.09184e+06 ...
    714248 257083 2.82371e+06 899747 1.09579e+07];
cameraNum = 30;
indepByte = zeros(1,cameraNum);

for r = 1:cameraNum
    indepByte(1,r) = correlation(r,r);
    for c = 1:cameraNum
        if correlation(r,c) == -1
            correlation(r,c) = correlation(r,r);
        end
    end
end

%---Objective---%  Objective function is the reduced ratio of encoded bits
f = zeros(cameraNum,1);
for i = 1:cameraNum
    f(i) = -1; %camera i's pay for letting others to overhear (i transmit independently)
    for j = 1:cameraNum
        reduce = (indepByte(j) - correlation(j,i))/indepByte(j); %reduced ratio of encoded bits for each cameras
        f(i) = f(i) + reduce;
    end
end
f = -f; %Since the optimization is minimize, while we want maximize

%---Bounds---%
lb = zeros(cameraNum,1);
ub = ones(cameraNum,1);

%---Inequalities---%
A = ones(1,cameraNum); %select less than k independent transmitters 

%---Not used---%
Aeq = zeros(1,cameraNum);

x = linprog(f,A,10,Aeq,0,lb,ub);