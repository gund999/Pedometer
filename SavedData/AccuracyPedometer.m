% Define the data
data = [70, 91, 76, 91, 92, 92, 91, 89, 91];

% Define the labels for the x-axis
labels = {'Slow', 'Normal', 'Fast', 'Incline', 'Decline', 'Hips', 'Armsleeve', 'Manny', 'Evan'};

% Define colors for each bar
colors = distinguishable_colors(length(data));

% Create bar graph
figure;
bar(60:length(data)+59, data, 0.5, 'FaceColor', 'flat');
colormap(colors);
xlabel('Type');
ylabel('Count');
title('Step Count by Type');
set(gca, 'XTickLabel', labels);
