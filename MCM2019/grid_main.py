import cv2
"""
from grid import xcenter,ycenter,dx,dy,xrange,yrange,img
cv2.imshow("hhhh",img)

from grid_roadfill import roadfill,roads
for i in range(1,roads.size):
    roadfill(i)
"""

from grid_roadfill import roads
roads[0,3]=roads[3,12]

from mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
from matplotlib import cm
from matplotlib.ticker import LinearLocator, FormatStrFormatter
import numpy as np

X = np.arange(0, roads.shape[1])
Y = np.arange(roads.shape[0],0,-1)
X, Y = np.meshgrid(X, Y)
Z = roads


"""
fig = plt.figure()
ax = fig.gca(projection='3d')
# Plot the surface.
surf = ax.plot_surface(X, Y, Z, cmap=cm.coolwarm,
                       linewidth=0, antialiased=False)

# Customize the z axis.
ax.set_zlim(0, 0.5)
ax.zaxis.set_major_locator(LinearLocator(10))
ax.zaxis.set_major_formatter(FormatStrFormatter('%.02f'))

# Add a color bar which maps values to colors.
fig.colorbar(surf, shrink=0.5, aspect=5)
"""

cset = plt.contourf(X, Y, Z, zdir='z', cmap=cm.coolwarm)

plt.show()
