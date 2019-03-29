#150130032
#Baran Kaya


import numpy as np
from numpy import linalg as LA
import matplotlib.pyplot as plt
from numpy import mean
from numpy import cov
import csv

class dataClass:
    def __init__(self, line):
        self.cls = int(line[len(line) - 1])
        self.features = line[0:(len(line) - 1)]

dataList = []
dataMatrix = []

with open('data.txt') as file:
    readCSV = csv.reader(file, delimiter=',')
    for line in readCSV:
        dataList.append(dataClass(line))
        dataMatrix.append( line[0:len(line)-1] )

dataMatrix = np.matrix(dataMatrix)
dataMatrix = dataMatrix.astype(int)

#Mean of each column
#M = mean(matrix, axis = 0)
M = []
for i in range (0, len(dataList[0].features)):
    sum = 0
    for item in dataList:
        sum += int(item.features[i])
    M.append(sum/len(dataList))
#print(M)

#List that contains elements - mean
meanSub = []
for item in dataList:
    intFeatList = list(map(int, item.features))
    meanSub.append( np.subtract(intFeatList, M) )

#C = np.cov(matrix)
C = np.dot(np.transpose(meanSub), meanSub) / len(dataList)-1
#print(C)

#Eigenvalues and eigenvectors
eigenVals, eigenVecs = LA.eig(C)
#print(eigenVals)
#print(eigenVecs)

# We have to sort eigenvalues and their corresponding eigenvectors therefore, i make them pair in tuple
eigenValsVecs = [(np.abs(eigenVals[i]), eigenVecs[:,i]) for i in range(0, len(eigenVals))]

# Sort eigenValsVecs in decreasing order
eigenValsVecs[::-1].sort()
#print (eigenValsVecs)

#Largest eigenvalues
x=eigenValsVecs[0][1]
y=[i for i in range(0, 64)]
plt.scatter(x,y)
plt.show()

#Second largest eigenvalues
x=eigenValsVecs[1][1]
y=[i for i in range(0, 64)]
plt.scatter(x,y)
plt.show()

#Feature space will be 2D therefore, i selected largest 2 eigenvalues eigenvectors
largestEigenVecs = np.hstack((eigenValsVecs[0][1].reshape(64, 1), eigenValsVecs[1][1].reshape(64, 1)))
#print(largestEigenVecs)

#New feature space matrix is 2D -> newData = oldData * 2D larget eigenvectors
#FinalData = RowFeatureVector * RowDataAdjust
newData = np.dot(dataMatrix, largestEigenVecs)
#print(newData)

#Show new feature space data
newDataX = np.array(newData[:,0])
newDataY = np.array(newData[:,1])
plt.scatter(newDataX, newDataY)
plt.show()
