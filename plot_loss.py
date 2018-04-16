import numpy as np
from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

if __name__ == '__main__':
    data = np.loadtxt("mix_loss.csv", delimiter=',')
    x    = np.linspace(0,len(data),len(data))
    plt.title('Loss of the online learning system for learning mixed nuclides')  
    plt.xlabel('Read in spectrums')  
    plt.ylabel('Loss')
    plt.plot(x, data,'r',label='broadcast') 
    plt.axis([0,len(data)+10,0,5])
    plt.show()