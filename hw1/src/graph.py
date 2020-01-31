import matplotlib.pyplot as plt

fig, ax = plt.subplots()
data = ['100', '10000', '1000000']
t1 = [0.15, 7.16, 721.991]
t2 = [0.005, 0.016, 1.436]
ax.plot(data, t1)
ax.set(xlabel='data', ylabel='time (s)')
ax.grid()

fig.savefig("generate.png")
plt.show()

fig2, ax2 = plt.subplots()
ax2.plot(data, t2)
ax2.set(xlabel='data', ylabel='time (s)')
ax2.grid()

fig.savefig("sorting.png")
plt.show()