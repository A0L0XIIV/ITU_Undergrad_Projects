import matplotlib.pyplot as plt
import re
import math
import numpy as np

#opening file
file = open("iris.csv", "r")

#iris class and iris list
class irisClass:
    def __init__(self, X1, X2, X3, X4, Y):
        self.sepalLength = float(X1)
        self.sepalWidth = float(X2)
        self.petalLength = float(X3)
        self.petalWidth = float(X4)
        self.y = Y

irisList = []

#reading file
for line in file:
    #print(line)
    elements = line.split(',')
    #print(elements)
    irisList.append(irisClass(elements[0], elements[1], elements[2], elements[3], elements[4]))


interval = int(len(irisList)/10)

size = 0

#Spliting irisList to 10 sublists
for item in irisList:
    irisCV10 = [irisList[i:i+interval] for i in range(0, len(irisList), interval)]
    size += 1

#K -> numOfClass, d -> numOfFeatures, N -> numOfInstances
K = d = 4
N = size

for i in range(0,10):
    #Select validation set and remove it from the training set
    testList = irisCV10[i]
    trainList = irisList
    del trainList[i]

    #Train the model
    #for item in trainList:
        #print(item)


def sigmoid(x):
    return 1 / (1 + np.exp(-1*x))

def logisticRegression(trainL, a, b):
    for i in range (1,k+1):
        for j in range (1,d+1):
            w[i][j] = rand

    for a in range (0,1000):#Until converge
        for i in range(1, k + 1):
            for j in range(1, d + 1):
                deltaw[i][j] = 0

        for t in range (0, N):
            for i in range(0, K):
                o[i] = 0
                for j in range (0,d):
                    o[i] = o[i] + w[i][j]*x[j].T#transpose olacak

            for i in range (1,K):
                y[i] = exp(o[i])/sum exp(o[k])

            for i in range (0,K):
                for j in range (0,d):
                    deltaw[i][j] = deltaw[i][j] + (r[i].T - y[i])*x[i].T

        for i in range (1,K):
            for j in range (1,d):
                w[i][j] = w[i][j] + n*deltaw[i][j]

