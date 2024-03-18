clc;
close all;
% Read data from file
data = readmatrix("MannyDerivWalksAll.txt");

% Define the range of x values you want to observe
start_index = 1;  % Starting index
end_index = 748;   % Ending index

% Plot data against index number within the specified range
figure;
plot(start_index:end_index, data(start_index:end_index), '-o');
hold on;


% Add Slow walk thresholds 
xline(400, '--', 'Color', 'k', 'LineWidth', 1.5);  
% Add normal walk thresholds 
xline(600, '--', 'Color', 'k', 'LineWidth', 1.5);  

hold off;

xlabel('Sample Number');
ylabel('Derivative of Magnitude');
title('Plot of Derivative of Magnitude vs. Sample Number (Specified Range)');
