'''
script to generate 2 graphs from 2 txt file with data writen as :
	1,1
	23.3,4
	etc..
you can change the x_lim and y_lim by just uncommenting the # lines
and typing the desired range 
'''



import matplotlib.pyplot as plt
import numpy as np

fig = plt.figure()

ax1 = fig.add_subplot(212)
x, y = np.loadtxt('spikesTime.txt',delimiter=',' , unpack=True)
ax1.set_xlim([10000, 12000])
ax1.plot(x,y,'g')


ax2 = fig.add_subplot(211)
x2, y2 = np.loadtxt('spikesTimeOfNeuron.txt',delimiter=',' , unpack=True)
ax2.set_xlim([10000, 12000])
ax2.set_ylim([0, 50])
ax2.plot(x2,y2,'yo')


plt.show()
