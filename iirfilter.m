% Define the filter parameters
order = 2;
cutoff = 0.3;

% Create the Butterworth filter
[b, a] = butter(order, cutoff);

% Print the filter coefficients
fprintf('a: [%s]\n', mat2str(a));
fprintf('b: [%s]\n', mat2str(b));

% Compute the frequency response
[H, w] = freqz(b, a);

% Plot the Bode plot
figure;
bode(tf(b, a));
title('Bode Plot of 2nd Order Butterworth Filter');
