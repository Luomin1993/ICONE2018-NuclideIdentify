import numpy as np
from numpy import linalg as la
import random
'''
Am241 1;
Co60  2;
Er175 3;
Ra226 4;
Ba133 5;
Cs137 6;
I131  7;
Rn222 8;
'''
#$Am241$,$Co60$,$Er175$,$Ra226$,$Ba133$,$Cs137$,$I131 $,$Rn222$
def getMat(path):
    mat = np.loadtxt(open(path))
    mat=np.delete(mat,1,axis=0);mat=np.delete(mat,1,axis=0);mat=np.delete(mat,-1,axis=0);mat=np.delete(mat,-1,axis=0);
    mat=mat.reshape((15,20))
    return mat

def getRandomMat(path):
    mat = np.loadtxt(open(path))
    mat = np.delete(mat,1,axis=0);mat=np.delete(mat,1,axis=0);mat=np.delete(mat,-1,axis=0);mat=np.delete(mat,-1,axis=0);
    m   = 0
    while m < 20:
        index = int(random.uniform(0,300))
        if index%2:
           mat[index] += random.uniform(0,0.7)*mat[index]
        else:
           mat[index] -= random.uniform(0,0.7)*mat[index]
        if mat[index]==0:
           mat[index] += random.uniform(0,57)
        m +=1
    mat=mat.reshape((15,20))
    return mat

def getSigma(mat):
    #return head 10 ele of the Sigma
    U,sigma,VT=la.svd(mat)
    return sigma[0:10]

def writeIntoFile(path):
    Xy = []
    for index in range(1,9):
        times = 0
        while times<30:
            mat   = getRandomMat('./Data/'+str(index)+'.csv')
            sigma = np.float32(getSigma(mat))
            sigma = np.insert(sigma,len(sigma),index)
            Xy.append(sigma)
            times += 1
    np.savetxt(path, np.array(Xy), delimiter = ',')        
    #return np.array(Xy)

def writeIntoFile_mix(path):
    Xy = []
    for index in range(1,9):
        if (index+1)%2:
           continue
        times = 0
        while times<5:
            mat_1   = getRandomMat('./Data/'+str(index)+'.csv')
            mat_2   = getRandomMat('./Data/'+str(index+1)+'.csv')
            mat = mat_1 + mat_2
            sigma = np.float32(getSigma(mat))
            sigma = np.insert(sigma,len(sigma),index*10+(index+1))
            Xy.append(sigma)
            times += 1
    np.savetxt(path, np.array(Xy), delimiter = ',')        
    #return np.array(Xy)


if __name__ == '__main__':
    #writeIntoFile('d1.csv')
    #writeIntoFile('d2.csv')
    #writeIntoFile('d3.csv')
    #writeIntoFile('d3.csv')
    writeIntoFile_mix('d_test.csv')