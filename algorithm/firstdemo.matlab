
S0 = [0 ; 0]; %reference sensor
S1 = [0 ; 2];
S2 = [2 ; 2];
S3 = [2 ; 0];

M = [0 0; 1 0; 2 0; 0 1; 1 1; 2 1; 0 2; 1 2; 2 2];
M = transpose(M);

RD1 = zeros(1,9);
RD2 = zeros(1,9);
RD3 = zeros(1,9);

for i = 1:9
    X = M(:,i);
    RD1(i) = norm(X - S1) - norm(X - S0);
    RD2(i) = norm(X - S2) - norm(X - S0);
    RD3(i) = norm(X - S3) - norm(X - S0);
end

X = [1.7;1.7];

RD1X = norm(X - S1) - norm(X - S0);
RD2X = norm(X - S2) - norm(X - S0);
RD3X = norm(X - S3) - norm(X - S0);

Difference = zeros(1,9);

for i = 1:9
    Difference(i) = (RD1(i)-RD1X)^2 + (RD2(i)-RD2X)^2 + (RD3(i)-RD3X)^2;
end


