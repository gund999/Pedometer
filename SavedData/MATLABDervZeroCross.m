% Read data from file
data = readmatrix("MannyDerivWalk.txt");

% Extract x and y columns
y = data(:, 2);

% Define thresholds for zero crossings with hysteresis
high_threshold = 0.01; % high threshold 
low_threshold = -0.0025; % low threshold

% Define minimum number of data points between crossings
min_points_between_crossings = 5; % Set your desired minimum number of points here

% Find zero crossings with hysteresis
zero_crossings = find((y > high_threshold & circshift(y, 1) < low_threshold) | (y < -high_threshold & circshift(y, 1) > -low_threshold));

% Filter zero crossings based on minimum points between crossings
filtered_zero_crossings = [];
for i = 1:numel(zero_crossings)-1
    if zero_crossings(i+1) - zero_crossings(i) > min_points_between_crossings
        filtered_zero_crossings = [filtered_zero_crossings; zero_crossings(i)];
    end
end

% Display number of zero crossings
disp(['Number of zero crossings: ', num2str(numel(filtered_zero_crossings))]);

% Plot original data
figure;
hold on;

% Iterate through each set of 68 data points
for i = 0:(length(data)/68)-1
    % Modify x column for each set of 68 data points
    x = (0:67) + i * 68;
    
    % Plot data for current set of 68 points
    plot(x, data((1:68) + i * 68, 2), '-o');
end

% Plot filtered zero crossings
plot(data(filtered_zero_crossings, 1), data(filtered_zero_crossings, 2), 'rx');
xlabel('Sample Number');
ylabel('Acceleration Vector Magnitude');
title('Plot of Acceleration Vector Magnitude with Zero Crossings');
legend('Data', 'Filtered Zero Crossings');
