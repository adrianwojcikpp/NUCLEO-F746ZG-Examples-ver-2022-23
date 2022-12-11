import time
import numpy
import matplotlib.pyplot as plt
from matplotlib.widgets import Slider, Button
from light_control import *

nucleo = LightControl('COM22')

t = []
x = []

fig, ax = plt.subplots()
line, = ax.plot(t, x, lw=2)
ax.set_xlabel('Time [s]')
ax.grid()

fig.subplots_adjust(left=0.25, bottom=0.1)

axref= fig.add_axes([0.1, 0.1, 0.0225, 0.8])
ref_slider = Slider(
    ax=axref,
    label="Light [lx]",
    valmin=0,
    valmax=2000,
    valinit=1000,
    orientation="vertical"
)

def update(val):
    nucleo.set_reference(ref_slider.val)
    fig.canvas.draw_idle()

ref_slider.on_changed(update)

t_now = 0

while(True):
    m = nucleo.get_measurement()
    t = numpy.append(t, m.time/1000)
    x = numpy.append(x, m.value)
    line.set_xdata(t)
    line.set_ydata(x)
    plt.draw()
    ax.set_xlim(t[0], max([t[-1],t[0]+0.1]))
    ax.set_ylim(0, 2500)
    plt.pause(0.1)

