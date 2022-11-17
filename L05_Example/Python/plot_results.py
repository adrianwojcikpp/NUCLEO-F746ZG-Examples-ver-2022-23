import csv
import matplotlib.pyplot as plt

def plot_results(filename):
    duty = [] # Duty cycle in Percent
    light = [] # Illuminance in Lux
    with open(filename) as csvfile:
        csvdata = csv.reader(csvfile)
        next(csvdata) # skip header
        for row in csvdata:
            duty.append(float(row[0]))
            light.append(float(row[1]))
    plt.plot(duty, light, marker="o", label="Green LED")
    #plt.xlabel("Sample number")
    plt.xlabel("Duty cycle in Percent")
    plt.ylabel("Illuminance in Lux")
    plt.grid()
    plt.legend(loc="lower right")
    plt.show()

if __name__ == '__main__':
    plot_results('sensor.csv')
