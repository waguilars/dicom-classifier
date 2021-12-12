
load fcmdata.dat

[centers,U] = fcm(fcmdata,3);


maxU = max(U);
index1 = find(U(1,:) == maxU);
index2 = find(U(2,:) == maxU);
index3 = find(U(3,:) == maxU);

cluster1 = fcmdata(index1,:);
cluster2 = fcmdata(index2,:);
cluster3 = fcmdata(index3,:);
