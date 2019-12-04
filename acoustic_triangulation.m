%cooridinates of the soundsource, which is unknown in real case
%this file is based on the dimension of 30cm * 30cm, with 4 mics located at
%the corners
%% Setting up the board and lookup table
%positions of all non-reference sensors; the position of reference sensor is S1(0,0)

S = zeros(2,4); 
S(:,1) = [0 ; 0];
S(:,2) = [1 ; 0];
S(:,3) = [1 ; 1];
S(:,4) = [0 ; 1];
%ratio = actual dimension of the board (in meters) / 1 meter
ratio = 1;
S = S .* ratio;

%speed of sound in air
c = 340;
%loc of sound source
%X = [x ; y];


%getting the position matrix M for 25 grid position points
M = zeros(2,25);
for i = 1 : 25 
    M(1, i) = mod((i-1), 5)*0.25;
end
for j = 1 : 25
    M(2, j) = floor((j-1)/ 5)*0.25;
end

M = M.*ratio;

%range difference (with reference sensor S1)matrix for 25 grid points
RD = zeros(4,25);

%calculating the RD for all of the sensors for each grid position
for i = 1:25
    for j = 2:4
        RD(j,i) = norm(M(:,i) - S(:,j)) - norm(M(:,i) - S(:,1));
    end
end

%% test
x = 0.7;
y = 0.6;
t0 = 5;
Xt = getTimeFromCoordinate_four_mic(t0,x,y,S,c);

% Xt(1) is the smallest absolute time of arrival among all four sensors
% other sensors are numbered in counter-clockwise order

%first step: find the smallest TOA of Xt, index is min_index;
for i=1:4
    if min(Xt) == Xt(i)
        min_index = i;
        break;
    end
end

% xmm = floor((min_index+1)/4);
switch min_index
    case 1
        x_next = 2;
        x_last = 4;
    case 2
        x_next = 3;
        x_last = 1;
    case 3
        x_next = 4;
        x_last = 2;
    otherwise
        x_next = 1;
        x_last = 3;
end
    
%%

Xb = c * (Xt(x_next)-Xt(min_index));
Xc = c * (Xt(x_last)-Xt(min_index));

A = Xb^2 + Xc^2 - 1;
B = -(Xb*(1-Xb^2)+Xc*(1-Xc^2));
C = (0.5-0.5*Xb^2)^2 + (0.5-0.5*Xc^2)^2;
delta = sqrt(B^2 - 4*A*C);
r1 = (-B + delta)/(2*A);
r2 = (-B - delta)/(2*A);

x_res = 0.5-0.5*Xb^2-Xb*r2;
y_res = 0.5-0.5*Xc^2-Xc*r2;

switch min_index
    case 2
        x_res = 1 - y_res;
        y_res = x_res;
    case 3
        x_res = 1 - x_res;
        y_res = 1 - y_res;
    case 4
        x_res = y_res;
        y_res = 1 - x_res;
    otherwise
end


