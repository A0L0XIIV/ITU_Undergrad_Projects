#150130032
#Baran Kaya


import numpy as np
from numpy import linalg as LA
import matplotlib.pyplot as plt
import csv
from math import exp
from math import log
from random import shuffle

#Data class
class dataClass:
    def __init__(self, line):
        self.cls = int(line[len(line) - 1])
        self.features = line[0:len(line) - 1]

dataList = []
featureMatrix = []
classVector = []

#File reading
with open('dataTrain.csv') as file:
    readCSV = csv.reader(file, delimiter=',')
    iterCSV = iter(readCSV)
    next(iterCSV)   #Get rid of the first line
    for line in readCSV:
        dataList.append(dataClass(line))


#Shuffle list randomly
shuffle(dataList)

instanceSize = len(dataList)
featureSize = len(dataList[0].features)

#Get features and classes from dataList as a vector
for item in dataList:
    featureMatrix.append( list(map(int, item.features)) )
    classVector.append( item.cls )

#Feature matrix 64x3823
featureMatrix = np.matrix(featureMatrix)
featureMatrix = featureMatrix.astype(int)

#Class vector 1x3823
classVector = np.array(classVector)


#repeat until converge->i=output(10), t=instance, h=hidden unit(10)
#   for all xt rt
#       for h=1..H
#           zh = sigmoid(wh^T * xt)
#       for i=1..K
#           yi = vi^T * z
#       for i = 1..K
#           Deltavi = n(rit- yit)*z
#       for h=1..H
#           Deltawh = n(sum_i(rit-yit)*vih)zh(1-zh)xt
#       for i=1..K
#           vi = vi+Deltavi
#       for h=1..H
#           wh = wh+Deltawh

N = input("Iteration: ")
N = int(N)
eta = input("Eta value: ")
eta = float(eta)

#Initialize all v and w to rand(-0.01, 0.01) and other symbols
K = 10  #Number of outputs
H = 10  #Number of hidden layers
v = 0.02 * np.random.randn(K, H) - 0.01
w = 0.02 * np.random.randn(H, featureSize) - 0.01
z = np.zeros((instanceSize, H))
y = np.zeros((instanceSize, K))
DeltaV = np.zeros((K, H))
DeltaW = np.zeros((H, featureSize))

#Sigmoid function
def sigmoid(x):
    try:    #Math range error
        exponent = exp(-x)
    except OverflowError:
        exponent = float('inf')
    return 1/(1 + exponent)

#r and x values
r = classVector
x = featureMatrix
crossEntropy = 0

for n in range (N):#while error <= 0.001
    for t in range (instanceSize):
        for h in range (H):
            z[t][h] = sigmoid( np.dot(w[h], np.transpose(x[t])) )
        for i in range (K):
            sum = 0
            for h in range (H):
                sum += v[i][h] * z[t][h]
            y[t][i] += sum
        for i in range (K):
            for h in range (H):
                DeltaV[i][h] += eta * (r[t]- y[t][i]) *  z[t][h]
        for h in range (H):
            sum = 0
            for i in range (K):
                sum += (r[t]- y[t][i]) * v[i][h]
            for j in range (featureSize):
                DeltaW[h][j] += (eta * sum * z[t][h] * (1-z[t][h]) * x.item(t,j))
        for i in range (K):
            for h in range (H):
                v[i][h] += DeltaV[i][h]
        for h in range (H):
            for j in range (featureSize):
                w[h][j] += DeltaW[h][j]

    #crossEntropy = sum_i_t rit*log(yit)
    for a in range (instanceSize):
        for b in range (K):
            try:  # Math range error
                Log10 = log(y[t][i], 10)
            except OverflowError:
                Log10 = float('inf')
            crossEntropy += r[t] * Log10
            #crossEntropy += r[t] * log(y[t][i], 10)

print("Cross entropy error with ", N, " iteration: ", crossEntropy)