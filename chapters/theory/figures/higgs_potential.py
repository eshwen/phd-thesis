import numpy as np
import matplotlib
matplotlib.use('Agg')
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import cm
import matplotlib.patches as patches

phi_1 = np.arange(-1, 1, 0.02)
phi_2 = np.arange(-1, 1, 0.02)
x, y = np.meshgrid(phi_1, phi_2)

# Values for scaling plot
mH = 1.
vev = (246. / 125.) * mH
mu2 = 0.75 * mH
lam = mu2 / (vev ** 2)

potential = lam * (mu2 - (x ** 2 + y ** 2)) ** 2

fig = plt.figure()
ax = fig.gca(projection='3d')
# Adjust viewing angle
ax.view_init(30, 15)

# Plot Higgs potential
surf = ax.plot_surface(x, y, potential,
                       cmap=cm.coolwarm, alpha=0.95 , zorder=1., linewidth=0.,
                       antialiased=True, rstride=1, cstride=1)
ax.set_zlim(1.25 * potential.min(), 0.5 * potential.max())

# Plot arrowed lines for axes
x_hat, y_hat, z_hat = np.array([[-1, 0, 0], [0, -1, 0], [0, 0, -1]])
x_vec, y_vec, z_vec = np.array([[2.5, 0, 0], [0, 2.5, 0], [0, 0, 1.25]])
ax.quiver(x_hat, y_hat, z_hat, x_vec, y_vec, z_vec, arrow_length_ratio=0.01, color="black", zorder=0., linewidth=1.)

# Turn the main axis off since arrowed lines replace it
ax.grid(False)
ax.set_axis_off()

# Axis labels
ax.text(-0.05, 0.05, 0, "0", size='small')
ax.text(1.75, -0.05, 0, r"$\phi_1$")
ax.text(0.05, 1.55, 0, r"$\phi_2$")
ax.text(0., 0.05, 0.24, r"$V(\phi)$")

plt.savefig('higgs_potential.pdf', bbox_inches='tight')

ax.clear()
sphere_r = 0.1
#z_offset= (2 * sphere_r ** 2) + potential[round(len(phi_1)/2), round(len(phi_2)/2)]
phi = np.linspace(0, 2 * np.pi, 50)
theta = np.linspace(0, np.pi, 50)
sphere_x = sphere_r * np.outer(np.sin(theta), np.cos(phi))
sphere_y = sphere_r * np.outer(np.sin(theta), np.sin(phi))
sphere_z = sphere_r * np.outer(np.cos(theta), np.ones(np.size(phi)) * sphere_r)# + z_offset
ax.plot_surface(sphere_x, sphere_y, sphere_z, linewidth=0., zorder=0.5, antialiased=True, rstride=1, cstride=1)
ax.grid(False)
ax.set_axis_off()

plt.savefig('higgs_boson.pdf', bbox_inches='tight')