% FOV calculations
% This code calculates the wanted FOV with varying focal lengths for a
% fixed sensor size of 3 mm

% This code calculates the wanted FOV with varying the sensor size with an
% aperture and fixed focal length for focal lengths of 10 mm, 12 mm, 15 mm,
% and 20 mm

%% Fixed H
FOV = linspace(10,45,35);

H_fixed = 3; % Units[mm]

for i = 1:length(FOV)
    f_var(i) = H_fixed / (2*tand(FOV(i)/2));
end

%% Fixed f
f_fixed = 10; %Units[mm]

for i = 1:length(FOV)
    h_var(i) = 2*f_fixed*tand(FOV(i)/2);
end

%% Plotting
figure
plot(FOV,f_var)
title('Variable Focal Length @  H=3 mm')
xlabel('FOV')
ylabel('Focal Length')

figure
plot(FOV,h_var)
title('Variable Aperture Stop @ f=10 mm')
xlabel('FOV')
ylabel('Aperture size')
