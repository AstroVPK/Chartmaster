import math
import os
import matplotlib.pyplot as plt
import sys
import pdb

try:
    import chartmaster as cm
except ImportError:
    print('chartmaster is not setup. Setup chartmaster by sourcing bin/setup.sh')
    sys.exit(1)


plt.ion()
plt.rcParams['text.usetex'] = True


import matplotlib as mpl
mpl.rcParams.update(mpl.rcParamsDefault)


def mag_to_points_sq(mag):
    return math.pow(-0.5*mag + 5.5, 2)

chartmaster_path = os.environ['CHARTMASTER']
data_path = os.path.join(chartmaster_path, 'data')
full_catalog_path = os.path.join(data_path, 'FullCatalog.dat')
full_figure_path = os.path.join(chartmaster_path, 'python', 'chartmaster', 'polar.svg')

if os.path.isfile(full_catalog_path):
    with open(full_catalog_path, 'r') as full_catalog_file:
        full_catalog_lines = full_catalog_file.readlines()

num_stars = len(full_catalog_lines)//4

ra_list = list()
dec_list = list()
mag_list = list()
r_list = list()
theta_list = list()
size_list = list()
name_list = list()
const_list = list()

projector = cm.StereographicProjector()

for i in range(num_stars):
    words = full_catalog_lines[4*i].rstrip('\n').split()
    ra = float(words[2])
    dec = float(words[3])
    mag = float(words[4])
    name_word = full_catalog_lines[4*i + 1].rstrip('\n')
    if not name_word or name_word[0:3] == 'TYC':
        if words[6] != '0':
            name_word = words[6]
        elif name_word[0:3] == 'TYC':
            name_word = ''
    const_word = full_catalog_lines[4*i + 2].rstrip('\n')

    #if dec >= 70.0 and ra >= 0.0 and ra <= 12.0 and mag < 6.5:
    if dec >= 70.0 and mag < 8.5:
        ra_list.append(ra)
        dec_list.append(dec)
        mag_list.append(mag)

        point = cm.CelestialPoint(ra, dec)
        rtheta_point = projector.project(point)
        r = rtheta_point.r()
        theta = rtheta_point.theta()*(math.pi/180.0)
        r_list.append(r)
        theta_list.append(theta)
        size_list.append(mag_to_points_sq(mag))
        name_list.append(name_word)
        const_list.append(const_word)
num_stars_plotted = len(ra_list)

fig, ax = plt.subplots(dpi=2400, figsize=(24, 24), subplot_kw={'projection': 'polar'})
for i in range(num_stars_plotted):
    ax.scatter(theta_list[i], r_list[i], s=size_list[i], c='black')
    if name_list[i]:
        ax.annotate(r'%s %s'%(name_list[i], const_list[i]), xy=(theta_list[i], r_list[i]), xytext=(2, 2), xycoords='data', textcoords='offset points', arrowprops=None, annotation_clip=None, fontsize='xx-small', alpha=0.75, color='grey', zorder=-10)
ax.grid(True)
ax.set_title('Northern Stars', va='bottom')
plt.savefig(full_figure_path, dpi='figure', format='svg')

pdb.set_trace()