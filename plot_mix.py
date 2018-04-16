import numpy as np
import random
from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

if __name__ == '__main__':
    data = np.loadtxt("mix.csv", dtype=np.float32, delimiter=',');
    #m = data[0:3]
    ax=plt.subplot(111,projection='3d')  

    MARKERS = ['o','v','s','p','d'] 
    COLORS  = ['y','r','g','w','b']

    for i in range(len(data)):   	
        if data[i][0]>10:
            ax.scatter(i,data[i][0],data[i][1],marker='o')#label='Right predicted lables,which are mixed nuclides.'
        else:
            ax.scatter(i,data[i][0],data[i][1],marker='v')#label='Wrong predicted lables,which are recognized as single nuclide.'


    ax.set_zlabel('The probability predicted') 
    ax.set_ylabel('The nuclides lables')
    ax.set_xlabel('The experts set')
    plt.title('The predicted results of the experts set in the test phase')
    t1 = ax.scatter(1,data[1][0],data[1][1],marker='o')
    t2 = ax.scatter(1,data[1][0],data[1][1],marker='v')
    ax.legend((t1,t2), ('Right predicted lables','Wrong predicted lables'),loc=3)
    plt.show()
