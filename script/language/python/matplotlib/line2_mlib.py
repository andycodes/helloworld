# object-oriented plot
from matplotlib.figure import Figure
from matplotlib.backends.backend_agg import FigureCanvasAgg as FigureCanvas

fig    = Figure()
canvas = FigureCanvas(fig)

# first axes
ax1    = fig.add_axes([0.1, 0.1, 0.2, 0.2])
line,  = ax1.plot([0,1], [0,1])
ax1.set_title("ax1")

# second axes
ax2    = fig.add_axes([0.4, 0.3, 0.4, 0.5])
sca    = ax2.scatter([1,3,5],[2,1,2])
ax2.set_title("ax2")

canvas.print_figure('demo.jpg')
