import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_table("mySort_16G_monitor.log", sep="\s+", skiprows=1, header=None)
df = df.drop_duplicates()
df = df.drop(0)
df = df.iloc[:, :-1]
df.columns = ['Time','UID','PID','%usr','%system','%guest','%wait','%CPU','CPU','minflt/s','majflt/s','VSZ','RSS','%MEM','kB_rd/s','kB_wr/s','kB_ccwr/s','iodelay','Command']
x_data = df[['%CPU', 'RSS', 'kB_rd/s', 'kB_wr/s']]
x_data.loc[:,'%CPU'] = x_data.loc[:,'%CPU'].map(lambda x: x.rstrip('%'))
x_data.loc[:,'RSS'] = x_data.loc[:,'RSS'].map(lambda x: x.rstrip('GMk'))
x_data.loc[:,'kB_rd/s'] = x_data.loc[:,'kB_rd/s'].map(lambda x: x.rstrip('MBk'))
x_data.loc[:,'kB_wr/s'] = x_data.loc[:,'kB_wr/s'].map(lambda x: x.rstrip('MBk'))
x_data=x_data.astype(float)
y_data = list(range(x_data.shape[0]))

def make_patch_spines_invisible(ax):
    ax.set_frame_on(True)
    ax.patch.set_visible(False)
    for sp in ax.spines.values():
        sp.set_visible(False)


fig, host = plt.subplots(figsize=(10, 6))
fig.subplots_adjust(right=0.66)

par1 = host.twinx()
par2 = host.twinx()
par3 = host.twinx()

# Offset the right spine of par2.  The ticks and label have already been
# placed on the right by twinx above.
par2.spines["right"].set_position(("axes", 1.2))
par3.spines["right"].set_position(("axes", 1.4))
# Having been created by twinx, par2 has its frame off, so the line of its
# detached spine is invisible.  First, activate the frame but make the patch
# and spines invisible.
make_patch_spines_invisible(par2)
make_patch_spines_invisible(par3)
# Second, show the right spine.
par2.spines["right"].set_visible(True)
par3.spines["right"].set_visible(True)

p1, = host.plot(y_data, x_data.loc[:,'%CPU'], "b-", label="CPU", markersize=0.1, alpha=0.7)
p2, = par1.plot(y_data, x_data.loc[:,'RSS'], "r-", label="Memory", markersize=0.1, alpha=0.7)
p3, = par2.plot(y_data, x_data.loc[:,'kB_rd/s'], "g-", label="Read", markersize=0.1, alpha=0.7)
p4, = par3.plot(y_data, x_data.loc[:,'kB_wr/s'], "y-", label="write", markersize=0.1, alpha=0.7)

#host.set_xlim(0, 2)
host.set_ylim(0, 100)
par1.set_ylim(0, 32)
par2.set_ylim(0, 1000)
par3.set_ylim(0, 1000)

host.set_xlabel("Time(s)")
host.set_ylabel("CPU(%)")
par1.set_ylabel("Memory(G)")
par2.set_ylabel("Read(MB/s)")
par3.set_ylabel("Write(MB/s)")

host.yaxis.label.set_color(p1.get_color())
par1.yaxis.label.set_color(p2.get_color())
par2.yaxis.label.set_color(p3.get_color())
par3.yaxis.label.set_color(p4.get_color())

tkw = dict(size=4, width=1.5)
host.tick_params(axis='y', colors=p1.get_color(), **tkw)
par1.tick_params(axis='y', colors=p2.get_color(), **tkw)
par2.tick_params(axis='y', colors=p3.get_color(), **tkw)
par3.tick_params(axis='y', colors=p4.get_color(), **tkw)
host.tick_params(axis='x', **tkw)

lines = [p1, p2, p3, p4]

host.legend(lines, [l.get_label() for l in lines])

plt.show()