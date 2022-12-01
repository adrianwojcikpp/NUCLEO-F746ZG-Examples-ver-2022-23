yyaxis left
plot(time, temp);
axis([min(time) max(time) 23 38]);
ylabel('Temperature [deg C]')
yyaxis right
plot(time2, duty);
axis([min(time) max(time) -5 105]);
ylabel('Heater PWM duty cycle [%]')
hold on;
grid on;
xlabel('Time [minutes]')

