clc;
close all;

% Function to calculate central difference
diffFcn = @(y, x) diff(y) ./ diff(x);

% Reading the Slow Walk data
Accel = readmatrix("MannySlowWalk.txt");

x = Accel(:,1);
y = Accel(:,2);
z = Accel(:,3);
Mag = Accel(:,4);
NumSamples = (1:length(x))';

% Calculate derivative of Mag using central difference
%MagDerivative = diffFcn(Mag, NumSamples);
MagDerivative = diff(Mag) ./ diff(NumSamples);
smoothedMagDerivative = movmean(MagDerivative, 10);
% Plotting Mag and its derivative for Normal Walk
figure(1);
subplot(2,1,1);
plot(NumSamples, Mag);
title('Normal Walk Data');
xlabel('Sample Number');
ylabel('Magnitude of Acceleration Vector');
xlim([1, 1000]); % Adjust as necessary

subplot(2,1,2);
plot(NumSamples(2:end), smoothedMagDerivative);
title('Derivative of Normal Walk Data');
xlabel('Sample Number');
ylabel('Derivative');
xlim([1, 1000]); % Adjust as necessary

% Draw a line at y = 0 for easier viewing
hold on;
line(xlim, [0 0], 'Color', 'k', 'LineStyle', '--');
hold off;

% Finding and plotting maxima in derivative
[pks, locs] = findpeaks(smoothedMagDerivative, 'MinPeakProminence', 0.02);
hold on;
plot(locs, pks, 'ro');
hold off;
fprintf('Number of peaks in derivative of Normal Walk: %d\n', length(pks));
