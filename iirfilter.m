% Define the filter parameters
order = 12;
fc = 300;
fs = 2000;

[b,a] = butter(order,fc/(fs/2));

% Split the filter coefficients into second-order sections
[sos, ~] = tf2sos(b, a);

freqz(b,a,[],fs)




%%
% Define the name for the C files
numeratorFilename = 'numerator_coeffs.h';


% Open the first C file for writing
fid = fopen(numeratorFilename, 'w');

% Write the numerator coefficients to the first C file
fprintf(fid, 'const double numerator_coeffs[%d][2] = {\n', size(sos, 1));
for i = 1:size(sos, 1)
    fprintf(fid, '    {%.15f, %.15f, %.15f}', sos(i,1) , sos(i, 2), sos(i, 3));
    if i < size(sos, 1)
        fprintf(fid, ',\n');
    else
        fprintf(fid, '\n');
    end
end
fprintf(fid, '};\n');

% Close the first C file
fclose(fid);

disp(['Numerator coefficients exported to ', numeratorFilename]);



% Define the name for the second C file
denominatorFilename = 'denominator_coeffs.h';

% Open the second C file for writing
fid = fopen(denominatorFilename, 'w');

% Write the denominator coefficients to the second C file
fprintf(fid, 'const double denominator_coeffs[%d][3] = {\n', size(sos, 1));
for i = 1:size(sos, 1)
    fprintf(fid, '    {%.15f, %.15f}', sos(i, 5), sos(i, 6));
    if i < size(sos, 1)
        fprintf(fid, ',\n');
    else
        fprintf(fid, '\n');
    end
end
fprintf(fid, '};\n');

% Close the second C file
fclose(fid);

disp(['Denominator coefficients exported to ', denominatorFilename]);
