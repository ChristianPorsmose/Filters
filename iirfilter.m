% Define the filter parameters
order = 2;

[b,a] = butter(order,0.6,'low');

% Split the filter coefficients into second-order sections
[sos, ~] = tf2sos(b, a);

freqz(b,a,[],fs)


%%
%script for putting num and denum in a c header
numeratorFilename = 'numerator_coeffs.h';
denominatorFilename = 'denominator_coeffs.h';


% Open the first C file for writing
fid = fopen(numeratorFilename, 'w');

fprintf(fid, 'double numerator_coeffs[%d][3] = {\n', size(sos, 1));
for i = 1:size(sos, 1)
    fprintf(fid, '    {%.15f, %.15f, %.15f}', sos(i,1) , sos(i, 2), sos(i, 3));
    if i < size(sos, 1)
        fprintf(fid, ',\n');
    else
        fprintf(fid, '\n');
    end
end
fprintf(fid, '};\n');

fclose(fid);

fid = fopen(denominatorFilename, 'w');

fprintf(fid, 'double denominator_coeffs[%d][2] = {\n', size(sos, 1));
for i = 1:size(sos, 1)
    fprintf(fid, '    {%.15f, %.15f}', sos(i, 5), sos(i, 6));
    if i < size(sos, 1)
        fprintf(fid, ',\n');
    else
        fprintf(fid, '\n');
    end
end
fprintf(fid, '};\n');


fclose(fid);

