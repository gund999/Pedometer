clc;
close all;

% Reading the Normal Walk data
Accel = readmatrix("MannyNormalWalk.txt");

x = Accel(:,1);
y = Accel(:,2);
z = Accel(:,3);
Mag = Accel(:,4);
NumSamples = (1:length(x))';

%[Atilde, Btilde] = CalibrateEllipsoidData3D(x, y, z, 20, 0);

% Plotting Mag for Normal Walk
figure(1);
plot(NumSamples, Mag);
title('Normal Walk Data');
xlabel('Sample Number');
ylabel('Magnitude of Acceleration Vector');
xlim([1, 152]); % Adjust as necessary

% Finding and plotting maxima
[pks, locs] = findpeaks(Mag, 'MinPeakProminence', 0.1);
hold on;
plot(locs, pks, 'ro');
hold off;
fprintf('Number of maxima in Normal Walk: %d\n', length(pks));


% Reading the Slow Walk data
Accel2 = readmatrix("MannySlowWalk.txt");

x2 = Accel2(:,1);
y2 = Accel2(:,2);
z2 = Accel2(:,3);
Mag2 = Accel2(:,4);
NumSamples2 = (1:length(x2))';

%[A2, B2] = CalibrateEllipsoidData3D(x2, y2, z2, 20, 0);

% Plotting Mag for Slow Walk
figure(2);
plot(NumSamples2, Mag2);
title('Slow Walk Data');
xlabel('Sample Number');
ylabel('Magnitude of Acceleration Vector');
xlim([1, 500]); % Adjust as necessary

% Finding and plotting maxima
[pks2, locs2] = findpeaks(Mag2, 'MinPeakProminence', 0.1);
hold on;
plot(locs2, pks2, 'ro');
hold off;
fprintf('Number of maxima in Slow Walk: %d\n', length(pks2));



% Reading the Fast Walk data
Accel3 = readmatrix("MannyFastWalk.txt");

x3 = Accel3(:,1);
y3 = Accel3(:,2);
z3 = Accel3(:,3);
Mag3 = Accel3(:,4);
NumSamples3 = (1:length(x3))';

%[A3, B3] = CalibrateEllipsoidData3D(x3, y3, z3, 20, 0);

% Plotting Mag for Fast Walk
figure(3);

plot(NumSamples3, Mag3);
title('Fast Walk Data');
xlabel('Sample Number');
ylabel('Magnitude of Acceleration Vector');
xlim([1, 500]); % Adjust as necessary

% Finding and plotting maxima
[pks3, locs3] = findpeaks(Mag3, 'MinPeakProminence', 0.1);
hold on;
plot(locs3, pks3, 'ro');
hold off;
fprintf('Number of maxima in Fast Walk: %d\n', length(pks3));










