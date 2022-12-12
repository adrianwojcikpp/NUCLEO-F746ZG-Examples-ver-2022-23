%% Simple discrete signal (sine wave) generation

%%% File info 
%
% ************************************************************************
%
%  @file     SINE_WAVE_GENERATION.m
%  @author   AW
%  @version  1.0
%  @date     10-Dec-2019 10:23:56
%  @brief    Simple sine wave generation for 12-bit DAC.
%
% ************************************************************************
%
clear n ts A A0 f DAC_REG_MAX DAC_VOL_MAX t y Y i fileID
%% Generate data
ts = 0.001;   % [s]
A = 0.5;      % [V]
A0 = 1.65;    % [V]
f = 10;       % [Hz]
n = (1/ts)/f; % [-]

DAC_REG_MAX = 4095; % [-]
DAC_VOL_MAX = 3.3;  % [V]

t = 0;      % [s]

y = zeros(n,1); % [V]
Y = zeros(n,1); % [-]

for i = 1 : n
    y(i) = A*sin(2*pi*f*t) + A0;
    Y(i) = (y(i)/DAC_VOL_MAX)*DAC_REG_MAX;
    t = t + ts;
end

%% Plot results
subplot(2,1,1);
    plot(0 : ts : (n-1)*ts, y);
    hold on; grid on; hold off;
    xlabel('Time [s]');
    ylabel('Voltage [V]');
    
subplot(2,1,2);
    plot(0 : ts : (n-1)*ts, Y);
    hold on; grid on; hold off;
    xlabel('Time [s]');
    ylabel('DAC REG <0x000-0xfff>');

%% Save to file
fileID = fopen('../Core/Inc/sine.csv','w');
for i = 1 : (n-1)
fprintf(fileID,'0x%s, \n', dec2hex(round(Y(i)), 4));
end
fprintf(fileID,'0x%s\n', dec2hex(round(Y(end)), 4));
fclose(fileID);
