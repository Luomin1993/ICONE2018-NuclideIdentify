import numpy as np
import random
from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

if __name__ == '__main__':
    data = np.loadtxt("d3.csv", dtype=np.float32, delimiter=',');
    #m = data[0:3]
    ax=plt.subplot(111,projection='3d')  

    #ax.scatter(x[:10],y[:10],z[:10],c='y') 
    #ax.scatter(x[1000:4000],y[1000:4000],z[1000:4000],c='r')
    #ax.scatter(x[4000:],y[4000:],z[4000:],c='g')    
    MARKERS = ['o','v','s','p','d'] 
    COLORS  = ['y','r','g','w','b']

    for type in range(5):   	
        for i in range(30):
            ax.scatter(data[type*10+i+3][0],data[type*10+i][1],data[type*10+i][2],c=COLORS[type],marker=MARKERS[type])


    ax.set_zlabel('Z') 
    ax.set_ylabel('Y')
    ax.set_xlabel('X')
    plt.title('The first 3 dimensions of the eigenvectors of some nuclides')
    plt.show()
