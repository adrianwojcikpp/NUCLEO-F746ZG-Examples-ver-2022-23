import time
import numpy
import matplotlib.pyplot as plt
from matplotlib.widgets import Slider, Button
from light_control import *

nucleo = LightControl('COM14')

t = []
x = []
e_max = 0.05
r1 = []
r2 = []

fig, ax = plt.subplots()
line, = ax.plot(t, x, lw=2)
limitdown, = ax.plot(t, r1, lw=1, color='r')
limitup, = ax.plot(t, r2, lw=1,color='r')
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

while(True):
    m = nucleo.get_measurement()
    t = numpy.append(t, m.time/1000)
    r1 = numpy.append(r1, max([ref_slider.val-ref_slider.valmax*e_max/2,0,0]))
    r2 = numpy.append(r2, ref_slider.val+ref_slider.valmax*e_max/2)
    x = numpy.append(x, m.value)
    line.set_xdata(t)
    line.set_ydata(x)
    limitdown.set_xdata(t)
    limitdown.set_ydata(r1)
    limitup.set_xdata(t)
    limitup.set_ydata(r2)
    plt.draw()
    ax.set_xlim(t[0], max([t[-1],t[0]+0.1]))
    ax.set_ylim(0, 2500)
    plt.pause(0.1)

